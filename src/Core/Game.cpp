#include "Game.h"
#include "MiniTime.h"
#include "Log/Log.h"

#include <iostream>
#include <stdexcept>
#include <chrono>

#include "Events/EventHandler.h"

namespace MiniEngine
{
	Game::Game()
	{
		m_Window = MiniWindow::Create();
		m_StartTime = 0.0f;
	}

	void Game::Run()
	{
		if (!Init()) throw std::runtime_error("Failed to Initialize Game!\n");
		RenderLoop();
	}

	bool Game::Init()
	{
		Log::Init();
		LogEngineInfo("Initialized Game!");
		m_StartTime = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch().count() / 1000000.0f;
		// Subscribe to Window Close Event.
		AddWindowEventListener(WindowEvents::WindowClose, Game::OnWindowEvent, this);
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

			//LogEngineTrace("Time Format: %s\n\t\t\t   Delta Time: %f\n\t\t\t   Unscaled Delta Time: %f\n\t\t\t   Time Scale: %f\n\t\t\t   Time: %f\n\t\t\t   Real Time Since Startup: %f\n\t\t\t   Frame Count: %d",
			//	MiniTime::GetLocalTimeFormat().c_str(), MiniTime::deltaTime(), MiniTime::unscaledDeltaTime(), MiniTime::timeScale, MiniTime::time(), MiniTime::realTimeSinceStartup(),
			//	MiniTime::frameCount());
		}
	}

	void Game::Cleanup()
	{
		LogEngineInfo("Cleaning Up!");

		// Close the window.
		m_Window->OnClose();
	}

    void Game::OnWindowEvent(const Event<WindowEvents> &e)
    {
		if (e.GetType() == WindowEvents::WindowClose)
		{
			// Tell the game to stop executing.
			m_Running = false;
		}
    }
}
