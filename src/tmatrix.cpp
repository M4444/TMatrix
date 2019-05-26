/*
 * Copyright (C) 2018-2019 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <csignal>
#include <string_view>
#include <thread>
#include <vector>
#include "Parser.h"
#include "Rain.h"
#include "Terminal.h"
#include "tmatrix.h"

using namespace std::chrono_literals;

std::atomic<bool> resizeTriggered {false};

void resizeHandler(int)
{
	resizeTriggered = true;
}

std::condition_variable renderingConditionVariable;
std::mutex mutexOfRenderingConditionVariable;

void render(const RainProperties &rainProperties)
{
	Terminal::getInstance(rainProperties.Color, rainProperties.BackgroundColor);

	Rain rain {rainProperties};
	std::unique_lock<std::mutex> mutexLock(mutexOfRenderingConditionVariable);
	while (true) {
		renderingConditionVariable.wait(mutexLock);
		if (resizeTriggered) {
			Terminal::Reset();
			rain.Reset();
			resizeTriggered = false;
		}
		rain.Update();
		Terminal::Flush();
	}
}

int main(int argc, char *argv[])
{
	bool paused {false};
	int stepsPerSecond {DEFAULT_STEPS_PER_SECOND};
	RainProperties rainProperties;

	if (Parser::ParseCmdLineArgs(std::vector<std::string_view>(argv+1, argv+argc),
				     stepsPerSecond, rainProperties)) {
		std::signal(SIGWINCH, resizeHandler);

		std::thread rendering_thread([&]{ render(rainProperties); });

		std::unique_lock<std::mutex> mutexLock(mutexOfRenderingConditionVariable);
		while (true) {
			Parser::ParseRuntimeInput(Terminal::ReadInputChar(), paused);
			mutexLock.unlock();
			if (!paused) {
				renderingConditionVariable.notify_one();
			}
			std::this_thread::sleep_for(1.0s/stepsPerSecond);
			mutexLock.lock();
		}
	}
}
