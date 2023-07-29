#ifndef GAME_H
#define GAME_H

#ifdef PLATFORM_WINDOWS
#include "../Platforms/Windows/WindowsWindow.h"
#else
#include "../Platforms/Linux/LinuxWindow.h"
#endif // PLATFORM_WINDOWS

#include "Events/EventHandler.h"

namespace MiniEngine
{
	class Game
	{
	public:
		Game();
		virtual ~Game(){}
		void Run();
	private:
		bool Init();
		void RenderLoop();
		void Cleanup();
		void OnWindowEvent(const Event<WindowEvents>& e);
	private:
		bool m_Running = true;
		std::unique_ptr<MiniWindow> m_Window;
		float m_StartTime;
	};

	Game* CreateGame();
}

#endif