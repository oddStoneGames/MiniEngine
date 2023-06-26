#include "WindowsWindow.h"
#include <iostream>
#include "../../Core/Log/Log.h"

namespace MiniEngine
{
	std::unique_ptr<MiniWindow> MiniWindow::Create(const WindowProperties & props)
	{
		return std::make_unique<WindowsWindow>(props);
	}

	WindowsWindow::WindowsWindow(const WindowProperties& windowProps)
	{
		Init(windowProps);
	}

	void WindowsWindow::OnUpdate()
	{
		DEBUG_ENGINE_TRACE("Window OnUpdate()");
	}

	void WindowsWindow::OnDraw()
	{

	}

	void WindowsWindow::OnClose()
	{

	}

	bool WindowsWindow::Init(const WindowProperties& windowProps)
	{
		m_Data.Title = windowProps.Title;
		m_Data.Width = windowProps.Width;
		m_Data.Height = windowProps.Height;

		return true;
	}
}