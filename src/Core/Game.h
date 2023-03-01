#ifndef GAME_H
#define GAME_H

#include "../Platforms/Windows/WindowsWindow.h"

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
	private:
		bool m_Running = true;
		std::unique_ptr<MiniWindow> m_Window;
		float m_StartTime;
	};

	Game* CreateGame();
}

#endif