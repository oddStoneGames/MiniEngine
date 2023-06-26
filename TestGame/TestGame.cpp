#include <MiniEngine.h>
#include "EntryPoint.h"

using namespace MiniEngine;

class TestGame : public Game
{
public:
	TestGame()
	{
		ADD_WINDOW_EVENT_LISTENER(WindowEvents::WindowResize, TestGame::OnWindowEvent, this);
		ADD_WINDOW_EVENT_LISTENER(WindowEvents::WindowClose, TestGame::OnWindowEvent, this);

		ADD_MOUSE_EVENT_LISTENER(MouseEvents::MouseMoved, TestGame::OnMouseEvent, this);
		ADD_MOUSE_EVENT_LISTENER(MouseEvents::MouseButtonDown, TestGame::OnMouseEvent, this);
		ADD_MOUSE_EVENT_LISTENER(MouseEvents::MouseButtonUp, TestGame::OnMouseEvent, this);

		ADD_KEY_EVENT_LISTENER(KeyEvents::KeyDown, TestGame::OnKeyEvent, this);
		ADD_KEY_EVENT_LISTENER(KeyEvents::KeyUp, TestGame::OnKeyEvent, this);
	}
	~TestGame() {}

	void OnWindowEvent(const Event<WindowEvents>& e)
	{
		if (e.GetType() == WindowEvents::WindowClose)
		{
			DEBUG_INFO("Window Close Event!");
		}
		else if (e.GetType() == WindowEvents::WindowResize)
		{
			auto windowResizeEvent = e.ToType<WindowResizeEvent>();
			DEBUG_INFO("Window Resize Event! New Dimensions: %d x %d", windowResizeEvent.width, windowResizeEvent.height);
		}
	}

	void OnMouseEvent(const Event<MouseEvents>& e)
	{
		if (e.GetType() == MouseEvents::MouseMoved)
		{
			auto mouseMovedEvent = e.ToType<MouseMovedEvent>();
			DEBUG_INFO("Mouse Moved Event! Mouse Position: (%d, %d)", mouseMovedEvent.x, mouseMovedEvent.y);
		}
		else if (e.GetType() == MouseEvents::MouseButtonDown)
		{
			auto mouseButtonDownEvent = e.ToType<MouseButtonDownEvent>();
			DEBUG_INFO("Mouse Button Down Event! Mouse Button Down: %d", mouseButtonDownEvent.button);
		}
		else if (e.GetType() == MouseEvents::MouseButtonUp)
		{
			auto mouseButtonUpEvent = e.ToType<MouseButtonUpEvent>();
			DEBUG_INFO("Mouse Button Up Event! Mouse Button Up: %d", mouseButtonUpEvent.button);
		}
	}

	void OnKeyEvent(const Event<KeyEvents>& e)
	{
		if (e.GetType() == KeyEvents::KeyDown)
		{
			auto keyDownEvent = e.ToType<KeyDownEvent>();
			DEBUG_INFO("Key Down Event! Keycode: %d", keyDownEvent.keycode);
		}
		else if (e.GetType() == KeyEvents::KeyUp)
		{
			auto keyUpEvent = e.ToType<KeyUpEvent>();
			DEBUG_INFO("Key Up Event! Keycode: %d", keyUpEvent.keycode);
		}
	}
};

MiniEngine::Game* MiniEngine::CreateGame()
{
	return new TestGame();
}