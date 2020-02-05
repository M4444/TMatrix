/*
 * Copyright (C) 2018-2020 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <csignal>
#include <memory>
#include <string_view>
#include <thread>
#include <vector>
#include <ncurses.h>
#include "Parser.h"
#include "Rain.h"
#include "Terminal.h"
#include "tmatrix.h"

using namespace std::chrono_literals;

std::atomic<bool> resizeTriggered {false};

void resizeHandler(int)
{
	resizeTriggered.store(true);
}

std::condition_variable renderingConditionVariable;
std::mutex mutexOfRenderingConditionVariable;

void render(const RainProperties &rainProperties)
{
	Color color = rainProperties.CharacterColor;
	Color background_color = rainProperties.BackgroundColor;
	std::shared_ptr<Terminal> terminal {
		rainProperties.Fade
			? std::static_pointer_cast<Terminal>(
				std::make_shared<ColorTerminal<true>>(color, background_color))
			: std::static_pointer_cast<Terminal>(
				std::make_shared<ColorTerminal<false>>(color, background_color))
	};

	std::shared_ptr<Rain> rain {
		rainProperties.Fade
			? std::static_pointer_cast<Rain>(
				std::make_shared<FadingRain>(rainProperties, terminal.get()))
			: std::static_pointer_cast<Rain>(
				std::make_shared<NonFadingRain>(rainProperties, terminal.get()))
	};
	std::unique_lock<std::mutex> mutexLock(mutexOfRenderingConditionVariable);
	while (true) {
		renderingConditionVariable.wait(mutexLock);
		if (resizeTriggered.exchange(false)) {
			terminal->Reset();
			rain->Reset();
		}
		rain->Update();
		terminal->Flush();
	}
}

int main(int argc, char *argv[])
{
	int stepsPerSecond {DEFAULT_STEPS_PER_SECOND};
	RainProperties rainProperties;
	std::wstring title;

	if (Parser::ParseCmdLineArgs(std::vector<std::string_view>(argv+1, argv+argc),
				     {stepsPerSecond, rainProperties, title})) {
		std::signal(SIGWINCH, resizeHandler);

		std::thread rendering_thread([&]{ render(rainProperties); });

		bool paused {false};
		std::unique_lock<std::mutex> mutexLock(mutexOfRenderingConditionVariable);
		while (true) {
			Parser::ParseRuntimeInput(getch(), paused);
			mutexLock.unlock();
			if (!paused) {
				renderingConditionVariable.notify_one();
			}
			std::this_thread::sleep_for(1.0s/stepsPerSecond);
			mutexLock.lock();
		}
	}
}
