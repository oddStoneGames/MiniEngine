#ifndef LINUXWINDOWS_H
#define LINUXWINDOWS_H

#include <X11/Xlib.h>
#include <unordered_set>
#include "../../Core/MiniWindow.h"

namespace MiniEngine
{
    class LinuxWindow : public MiniWindow
    {
	public:
		LinuxWindow(const WindowProperties& windowProps);
		LinuxWindow(const LinuxWindow&) = delete;
		LinuxWindow& operator=(const LinuxWindow&) = delete;
		virtual ~LinuxWindow() {}

		virtual void OnUpdate() override;
		virtual void OnDraw() override;
		virtual void OnClose() override;

		virtual uint32_t GetWidth() const override { return m_Data.Width; };
		virtual uint32_t GetHeight() const override { return m_Data.Height; };
	private:
		bool Init(const WindowProperties& windowProps);
	private:
		Display* m_Display;
		int m_Screen;
		Window m_RootWindow, m_Window;
		XEvent m_Event;
		// To ignore key events from repeating.
		std::unordered_set<char> m_RepeatKeys;
		struct WindowData
		{
			const char* Title;
			uint32_t Width, Height;
		}m_Data;
    };
}

#endif // !LINUXWINDOWS_H