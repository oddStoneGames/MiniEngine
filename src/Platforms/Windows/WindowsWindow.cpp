#include <windowsx.h>
#include <tchar.h>
#include "WindowsWindow.h"
#include "../../Core/Events/EventHandler.h"

namespace MiniEngine
{
	LRESULT WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
		case WM_KEYDOWN:
		{
			if ((HIWORD(lParam) & KF_REPEAT) != KF_REPEAT)
			{
				// Key Down Event without repeating.
				KeyDownEvent kd;
				kd.keycode = (int)wParam;
				SendKeyEvent(kd);
			}
			break;
		}
		case WM_KEYUP:
		{
			// Key Up Event.
			KeyUpEvent ku;
			ku.keycode = (int)wParam;
			SendKeyEvent(ku);
			break;
		}
		case WM_MOUSEMOVE:
		{
			// Mouse Move Event.
			MouseMovedEvent me;
			me.x = GET_X_LPARAM(lParam);
			me.y = GET_Y_LPARAM(lParam);
			SendMouseEvent(me);
			break;
		}
		case WM_LBUTTONDOWN:
		case WM_MBUTTONDOWN:
		case WM_RBUTTONDOWN:
		{
			// Mouse Button Down Event.
			MouseButtonDownEvent md;
			// To make sure the input is synonymous in both linux & windows.
			// 1 - LMB, 2 - MMB, 3 - RMB
			md.button = (uMsg == WM_RBUTTONDOWN) ? 3 : (uMsg == WM_MBUTTONDOWN ? 2 : 1);
			SendMouseEvent(md);
			break;
		}
		case WM_LBUTTONUP:
		case WM_MBUTTONUP:
		case WM_RBUTTONUP:
		{
			// Mouse Button Up Event.
			MouseButtonUpEvent mu;
			mu.button = (uMsg == WM_RBUTTONUP) ? 3 : (uMsg == WM_MBUTTONUP ? 2 : 1);
			SendMouseEvent(mu);
			break;
		}
		case WM_SIZE:
		{
			// Window Resize Event.
			WindowResizeEvent wr;
			wr.width = LOWORD(lParam);	// Macro to get the low-order word.
			wr.height = HIWORD(lParam); // Macro to get the high-order word.

			// Send Resize Event.
			SendWindowEvent(wr);
			break;
		}
		case WM_PAINT:
		{
			// Paint all the area again.
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			SetDCBrushColor(hdc, RGB(10, 20, 30));
			// All painting occurs here, between BeginPaint and EndPaint.
			FillRect(hdc, &ps.rcPaint, (HBRUSH)(GetStockObject(DC_BRUSH)));
			EndPaint(hWnd, &ps);
			break;
		}
		case WM_CLOSE:
		{
			// Window Close Event.
			WindowCloseEvent wc;
			SendWindowEvent(wc);
			break;
		}
		case WM_DESTROY:
			return 0;
		}
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	std::unique_ptr<MiniWindow> MiniWindow::Create(const WindowProperties& props)
	{
		return std::make_unique<WindowsWindow>(props);
	}

	WindowsWindow::WindowsWindow(const WindowProperties& windowProps)
		: m_hInstance(GetModuleHandle(nullptr))
	{
		Init(windowProps);
	}

	void WindowsWindow::OnUpdate()
	{
		if (!ProcessMessages())	return;
	}

	void WindowsWindow::OnDraw()
	{

	}

	void WindowsWindow::OnClose()
	{
		// Free the resources.
		DestroyWindow(m_hWnd);
		PostQuitMessage(0);
		UnregisterClass(m_Classname, m_hInstance);
	}

	bool WindowsWindow::Init(const WindowProperties& windowProps)
	{
		m_Data.Title = windowProps.Title;
		m_Data.Width = windowProps.Width;
		m_Data.Height = windowProps.Height;

		WNDCLASS wndClass = {};
		wndClass.lpszClassName = m_Classname;
		wndClass.hInstance = m_hInstance;
		wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndClass.lpfnWndProc = WindowProc;

		DWORD style = WS_OVERLAPPEDWINDOW;

		RECT rect;
		rect.left = 250;
		rect.bottom = 250;
		rect.right = rect.left + m_Data.Width;
		rect.top = rect.bottom + m_Data.Height;

		// To make sure that our window size is the whole canvas and not the outer border.
		AdjustWindowRect(&rect, style, false);

		if (!RegisterClass(&wndClass))
			return GetLastError();

		m_Data.Width = rect.right - rect.left;
		m_Data.Height = rect.top - rect.bottom;
		printf("WIDTH & HEIGHT of Rect: %d\t%d\n", m_Data.Width, m_Data.Height);

		m_hWnd = CreateWindowEx(0, m_Classname, TEXT(m_Data.Title), style, rect.left, rect.bottom, m_Data.Width, m_Data.Height, NULL, NULL, m_hInstance, NULL);

		if (!m_hWnd)
			return GetLastError();

		ShowWindow(m_hWnd, SW_SHOW);

		return true;
	}

	bool WindowsWindow::ProcessMessages()
	{
		MSG msg = {};
		while (PeekMessage(&msg, m_hWnd, 0u, 0u, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)	return false;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		return true;
	}
}