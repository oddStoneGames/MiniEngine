#ifndef ENGINE_H
#define ENGINE_H

#include "../Platforms/Windows/WindowsWindow.h"

namespace MiniEngine
{
	class Engine
	{
	public:
		Engine();
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
}

#endif