#include "Game.h"
#include "MiniTime.h"
#include "Log/Log.h"

#include <iostream>
#include <stdexcept>
#include <chrono>

namespace MiniEngine
{
	Game::Game()
	{
		m_Window = WindowsWindow::Create();
		m_StartTime = 0.0f;
	}

	void Game::Run()
	{
		if (!Init()) throw std::runtime_error("Failed to Initialize Game!\n");
		RenderLoop();
	}

	bool Game::Init()
	{
		std::cout << "Initialized Game!\n";
		Log::Init();
		m_StartTime = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch().count() / 1000000.0f;
		return true;
	}

	void Game::RenderLoop()
	{
		MiniTime::timeScale = 1.0f;
		while (m_Running)
		{
			if (MiniTime::timeScale < 0.0f) MiniTime::timeScale = 0.0f;
			auto startTime = std::chrono::high_resolution_clock::now();
			if (!m_Running) { Cleanup(); break; }
			// Keep on running the engine!
			m_Window->OnUpdate();
			auto endTime = std::chrono::high_resolution_clock::now();
			auto start = std::chrono::time_point_cast<std::chrono::microseconds>(startTime).time_since_epoch().count();
			auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTime).time_since_epoch().count();

			MiniTime::_unscaledDeltaTime = (float)(end - start) / 1000.0f;
			MiniTime::_deltaTime = MiniTime::_unscaledDeltaTime * MiniTime::timeScale;

			MiniTime::_realTimeSinceStartup = end / 1000000.0f - m_StartTime;
			MiniTime::_time = MiniTime::_realTimeSinceStartup * MiniTime::timeScale;
			MiniTime::_frameCount++;

			DEBUG_ENGINE_DEBUG("Hiiii this should be green!");
			DEBUG_ENGINE_ERROR("Hiiii this should be green!");

			DEBUG_WARN("Hiiii this should be green!");

			/*printf("MiniTime Format: %s\tDelta MiniTime: %f\tUnscaled Delta MiniTime: %f\tTime Scale: %f\tTime: %f\tReal MiniTime Since Startup: %f\tFrame Count: %d\n",
				MiniTime::GetLocalTimeFormat().c_str(), MiniTime::deltaTime(), MiniTime::unscaledDeltaTime(), MiniTime::timeScale, MiniTime::time(), MiniTime::realTimeSinceStartup(), 
				MiniTime::frameCount());*/
		}
	}

	void Game::Cleanup()
	{
		std::cout << "Cleaning Up!\n";
	}
}
