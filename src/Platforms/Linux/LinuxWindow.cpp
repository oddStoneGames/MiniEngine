#include <X11/Xutil.h>
#include <X11/XKBlib.h>

#include "LinuxWindow.h"
#include "../../Core/Events/EventHandler.h"
#include "../../Core/Log/Log.h"

namespace MiniEngine
{
    std::unique_ptr<MiniWindow> MiniWindow::Create(const WindowProperties& props)
	{
		return std::make_unique<LinuxWindow>(props);
	}

    LinuxWindow::LinuxWindow(const WindowProperties &windowProps)
    {
        Init(windowProps);
    }

    void LinuxWindow::OnUpdate()
    {
        Atom wmDeleteMessage = XInternAtom(m_Display, "WM_DELETE_WINDOW", False);
        XSetWMProtocols(m_Display, m_Window, &wmDeleteMessage, 1);

        if(XNextEvent(m_Display, &m_Event) == 0)
        {
            switch(m_Event.type)
            {
                case ClientMessage:
                {
                    if (m_Event.xclient.data.l[0] == wmDeleteMessage)
                    {
                        // Send Window Close Event.
                        WindowCloseEvent wc;
                        SendWindowEvent(wc);
                    }
                    break;
                }
                case ConfigureNotify:
                {
                    XConfigureEvent xce = m_Event.xconfigure;
                    /* This event type is generated for a variety of
                    happenings, so check whether the window has been
                    resized. */
                    if (xce.width != m_Data.Width || xce.height != m_Data.Height)
                    {
                        m_Data.Width = xce.width;
                        m_Data.Height = xce.height;

                        // Send Window Resize Event.
                        WindowResizeEvent wr;
                        wr.width = m_Data.Width;
                        wr.height = m_Data.Height;
                        SendWindowEvent(wr);
                    }
                    break;
                }
                case MotionNotify:
                {
                    MouseMovedEvent mm;
                    mm.x = m_Event.xmotion.x;
                    mm.y = m_Event.xmotion.y;
                    SendMouseEvent(mm);
                    break;
                }
                case ButtonPress:
                {
                    MouseButtonDownEvent mb;
                    mb.button = m_Event.xbutton.button;
                    SendMouseEvent(mb);
                    break;
                }
                case ButtonRelease:
                {
                    MouseButtonUpEvent mu;
                    mu.button = m_Event.xbutton.button;
                    SendMouseEvent(mu);
                    break;
                }
                case KeyPress:
                {
                    KeySym key;
                    char text;
                    if(XLookupString(&m_Event.xkey, &text, 1, &key,0) == 1)
                    {
                        KeyDownEvent kd;
                        kd.keycode = text;
                        if(m_RepeatKeys.count(text) == 0)
                        {
                            SendKeyEvent(kd);
                            m_RepeatKeys.insert(text);
                        }
                    }
                    break;
                }
                case KeyRelease:
                {
                    KeySym key;
                    char text;
                    if(XLookupString(&m_Event.xkey, &text, 1, &key,0) == 1)
                    {
                        KeyUpEvent ku;
                        ku.keycode = text;
                        if(m_RepeatKeys.count(text) >= 0)
                        {
                            SendKeyEvent(ku);
                            m_RepeatKeys.erase(text);
                        }
                    }
                    break;
                }
            }
        }
    }

    void LinuxWindow::OnDraw()
    {

    }

    void LinuxWindow::OnClose()
    {
        // Unmap the window, destroy the window 
        // & close the connection with X Server.
        XUnmapWindow(m_Display, m_Window);
        XDestroyWindow(m_Display, m_Window);
        XCloseDisplay(m_Display);
    }

    bool LinuxWindow::Init(const WindowProperties &windowProps)
    {
        m_Data.Width = windowProps.Width;
        m_Data.Height = windowProps.Height;

        if((m_Display = XOpenDisplay(NULL)) == nullptr)
        {
            LogEngineError("Failed to establish connection with X server.");
            return false;
        }

        // Get Default display & Root window.
        m_Screen = DefaultScreen(m_Display);
        m_RootWindow = RootWindow(m_Display, m_Screen);
        
        // Creating a simple window.
        m_Window = XCreateSimpleWindow(m_Display, m_RootWindow, 0, 0, 
        windowProps.Width, windowProps.Height, 15, BlackPixel(m_Display, m_Screen), BlackPixel(m_Display, m_Screen));

        if(m_Window == 0)
        {
            LogEngineError("Failed to create window.");
            return false;   
        }

        XSetStandardProperties(m_Display, m_Window, m_Data.Title, m_Data.Title, None, NULL, 0, NULL);
        XSelectInput(m_Display, m_Window, ExposureMask | StructureNotifyMask
                     | PointerMotionMask | ButtonPressMask | ButtonReleaseMask
                     | KeyPressMask | KeyReleaseMask);

        // Disable auto-repeat for the window
        XkbSetDetectableAutoRepeat(m_Display, true, nullptr);

        // Map window to display server
        XMapWindow(m_Display, m_Window);

        return true;
    }
}