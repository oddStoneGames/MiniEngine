#ifndef WINDOWSWINDOW_H
#define WINDOWSWINDOW_H

#include <Windows.h>
#include "../../Core/MiniWindow.h"

namespace MiniEngine
{
	LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	class WindowsWindow : public MiniWindow
	{
	public:
		WindowsWindow(const WindowProperties& windowProps);
		WindowsWindow(const WindowsWindow&) = delete;
		WindowsWindow& operator=(const WindowsWindow&) = delete;
		virtual ~WindowsWindow() {}

		virtual void OnUpdate() override;
		virtual void OnDraw() override;
		virtual void OnClose() override;

		virtual uint32_t GetWidth() const override { return m_Data.Width; };
		virtual uint32_t GetHeight() const override { return m_Data.Height; };
	private:
		bool Init(const WindowProperties& windowProps);
		bool ProcessMessages();
	private:
		HINSTANCE m_hInstance;
		HWND m_hWnd;
		const TCHAR* m_Classname = TEXT("MiniEngine");
		struct WindowData
		{
			const char* Title;
			uint32_t Width, Height;
		}m_Data;
	};
}

#endif // !WINDOWSWINDOW_H