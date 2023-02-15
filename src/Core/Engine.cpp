#include "Engine.h"
#include <iostream>
#include <stdexcept>

namespace MiniEngine
{
	Engine::Engine()
	{
		m_Window = WindowsWindow::Create();
	}

	void Engine::Run()
	{
		if (!Init()) throw std::runtime_error("Failed to Initialize Engine!\n");
		RenderLoop();
	}

	bool Engine::Init()
	{
		std::cout << "Initialized Engine!\n";
		return true;
	}

	void Engine::RenderLoop()
	{
		while (m_Running)
		{
			if (!m_Running) { Cleanup(); break; }
			// Keep on running the engine!
			m_Window->OnUpdate();
		}
	}

	void Engine::Cleanup()
	{
		std::cout << "Cleaning Up!\n";
	}
}