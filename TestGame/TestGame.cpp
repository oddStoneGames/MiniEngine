#include <MiniEngine.h>
#include "EntryPoint.h"

using namespace MiniEngine;

class TestGame : public Game
{
public:
	TestGame()
	{
		AddWindowEventListener(WindowEvents::WindowResize, TestGame::OnWindowEvent, this);
		AddWindowEventListener(WindowEvents::WindowClose, TestGame::OnWindowEvent, this);

		m_MouseMovedEventHandle = AddMouseEventListener(MouseEvents::MouseMoved, TestGame::OnMouseEvent, this);
		AddMouseEventListener(MouseEvents::MouseButtonDown, TestGame::OnMouseEvent, this);
		AddMouseEventListener(MouseEvents::MouseButtonUp, TestGame::OnMouseEvent, this);

		AddKeyEventListener(KeyEvents::KeyDown, TestGame::OnKeyEvent, this);
		AddKeyEventListener(KeyEvents::KeyUp, TestGame::OnKeyEvent, this);
	}
	~TestGame() {}

	void OnWindowEvent(const Event<WindowEvents>& e)
	{
		if (e.GetType() == WindowEvents::WindowClose)
		{
			LogInfo("Window Close Event!");
		}
		else if (e.GetType() == WindowEvents::WindowResize)
		{
			auto windowResizeEvent = e.ToType<WindowResizeEvent>();
			LogInfo("Window Resize Event! New Dimensions: %d x %d", windowResizeEvent.width, windowResizeEvent.height);
		}
	}

	void OnMouseEvent(const Event<MouseEvents>& e)
	{
		if (e.GetType() == MouseEvents::MouseMoved)
		{
			auto mouseMovedEvent = e.ToType<MouseMovedEvent>();
			LogInfo("Mouse Moved Event! Mouse Position: (%d, %d)", mouseMovedEvent.x, mouseMovedEvent.y);
		}
		else if (e.GetType() == MouseEvents::MouseButtonDown)
		{
			auto mouseButtonDownEvent = e.ToType<MouseButtonDownEvent>();
			LogInfo("Mouse Button Down Event! Mouse Button Down: %d", mouseButtonDownEvent.button);
		}
		else if (e.GetType() == MouseEvents::MouseButtonUp)
		{
			auto mouseButtonUpEvent = e.ToType<MouseButtonUpEvent>();
			LogInfo("Mouse Button Up Event! Mouse Button Up: %d", mouseButtonUpEvent.button);
		}
	}

	void OnKeyEvent(const Event<KeyEvents>& e)
	{
		if (e.GetType() == KeyEvents::KeyDown)
		{
			auto keyDownEvent = e.ToType<KeyDownEvent>();
			LogInfo("Key Down Event! Keycode: %d", keyDownEvent.keycode);

			if (keyDownEvent.keycode == 32)
			{
				// Space Pressed!
				RemoveMouseEventListener(m_MouseMovedEventHandle);
			}
		}
		else if (e.GetType() == KeyEvents::KeyUp)
		{
			auto keyUpEvent = e.ToType<KeyUpEvent>();
			LogInfo("Key Up Event! Keycode: %d", keyUpEvent.keycode);
		}
	}

private:
	int m_MouseMovedEventHandle = 0;
};

MiniEngine::Game* MiniEngine::CreateGame()
{
	return new TestGame();
}