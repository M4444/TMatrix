/*
 * Copyright (C) 2018-2021 Miloš Stojanović
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

static std::atomic<bool> resizeTriggered {false};
static std::condition_variable renderingConditionVariable;
static std::mutex mutexOfRenderingConditionVariable;

[[noreturn]] static void render(const RainProperties &rainProperties, int stepsPerSecond)
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
	int maxStep = FRAMES_PER_SECOND/stepsPerSecond;
	int step = 0;
	std::unique_lock<std::mutex> mutexLock(mutexOfRenderingConditionVariable);
	while (true) {
		renderingConditionVariable.wait(mutexLock);
		if (resizeTriggered.exchange(false)) {
			step = 0;
			terminal->Reset();
			rain->Reset();
			rain->Update();
		}
		terminal->Flush();
		if (step >= maxStep - 1) {
			rain->Update();
			step = 0;
		}
		step++;
	}
}

int main(int argc, char *argv[])
{
	int stepsPerSecond {DEFAULT_STEPS_PER_SECOND};
	RainProperties rainProperties;
	std::wstring title;

	if (Parser::ParseCmdLineArgs(std::vector<std::string_view>(argv+1, argv+argc),
				     {stepsPerSecond, rainProperties, title})) {
		std::signal(SIGWINCH, [](int) { resizeTriggered.store(true); });

		std::thread rendering_thread([&]{ render(rainProperties, stepsPerSecond); });

		bool paused {false};
		std::unique_lock<std::mutex> mutexLock(mutexOfRenderingConditionVariable);
		while (true) {
			Parser::ParseRuntimeInput(static_cast<char>(getch()), paused);
			mutexLock.unlock();
			if (!paused) {
				renderingConditionVariable.notify_one();
			}
			std::this_thread::sleep_for(1.0s/FRAMES_PER_SECOND);
			mutexLock.lock();
		}
	}
}
