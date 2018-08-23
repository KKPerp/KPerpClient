#include "Window.hpp"

#include "Renderer.hpp"

#ifdef APIENTRY
#undef APIENTRY
#endif

#include <windows.h>

#include "Error.hpp"

//#ifdef _WIN32
//#ifdef APIENTRY
//#undef APIENTRY
//#endif
//#endif

#include <iostream>

#include <queue>

#define _kp_userdefault ((int)0xEFFFFFFF)

namespace kp {

	const int win_lastestopengl = 46;

	Window::Window() {

	}

	Window::Window(int Tx, int Ty, int Tw, int Th, const char* Ttext, WindowStyle Tstyle) {
		// Software
		running = create_software_window(Tx, Ty, Tw, Th, Ttext, Tstyle);
		if (running == 1) {
			events = new std::queue<Event>;
		}
	}
	Window::Window(int Topengl, int Tx, int Ty, int Tw, int Th, const char* Ttext, WindowStyle Tstyle) {
		if (Topengl < 1 || Topengl > win_lastestopengl) {
			if (Topengl > win_lastestopengl) {
				// No OpenGL version higher than 4.6
				setLastError(Error::InvalidOpenGL);
			}
			if (Topengl < 1) {
				// Software
				running = create_software_window(Tx, Ty, Tw, Th, Ttext, Tstyle);
				if (running == 1) {
					events = new std::queue<Event>;
				}
			}
		}
		else {
			// OpenGL
			running = create_opengl(Tx, Ty, Topengl, Tw, Th, Ttext, Tstyle);
			if (running == 1) {
				events = new std::queue<Event>;
			}
		}
	}
	Window::Window(int Tw, int Th, const char* Ttext, WindowStyle Tstyle) {
		// Software
		running = create_software_window(_kp_userdefault, _kp_userdefault, Tw, Th, Ttext, Tstyle);
		if (running == 1) {
			events = new std::queue<Event>;
		}
	}
	Window::Window(int Topengl, int Tw, int Th, const char* Ttext, WindowStyle Tstyle) {
		if (Topengl < 1 || Topengl > win_lastestopengl) {
			if (Topengl > win_lastestopengl) {
				// No OpenGL version higher than 4.6
				setLastError(Error::InvalidOpenGL);
			}
			if (Topengl < 1) {
				// Software
				running = create_software_window(_kp_userdefault, _kp_userdefault, Tw, Th, Ttext, Tstyle);
				if (running == 1) {
					events = new std::queue<Event>;
				}
			}
		}
		else {
			// OpenGL
			running = create_opengl(_kp_userdefault, _kp_userdefault, Topengl, Tw, Th, Ttext, Tstyle);
			if (running == 1) {
				events = new std::queue<Event>;
			}
		}
	}

	void Window::Destroy() {
		Renderer::Destroy();
		if (events != NULL) {
			delete events;
			events = NULL;
		}
	}

	bool Window::isActive() {
		return (running && (hwnd != NULL));
	}

	void Window::makeCurrent() {
		wglMakeCurrent(hdc, hglrc);
	}

	Event Window::getEvent() {
		//MSG _msg;
		memset(msg, 0, sizeof(MSG));
		PeekMessageW((MSG*)(&msg), hwnd, 0, 0, 1);

		TranslateMessage((MSG*)(&msg));
		DispatchMessageW((MSG*)(&msg));

		//mouseinsidetemp = 0;

		GetCursorPos((POINT*)&_mousepos);
		//std::cout << _mousepos.x << "," << _mousepos.y << "\n";
		//std::cout << mousepos.x << "," << mousepos.y << "\n";
		if ((mousepos.x != _mousepos.x) || (mousepos.y != _mousepos.y)) {
			if ((_mousepos.x > rect.a.x) &&
				(_mousepos.y > rect.a.y) &&
				(_mousepos.x < rect.c.x) &&
				(_mousepos.y < rect.c.y)) {
				if (mouseinside == 0) {
					((std::queue<Event>*)events)->push(Event::MouseEnterClient);
					mouseinside = 1;
				}

				((std::queue<Event>*)events)->push(Event::MouseMove);
			}
			else {
				if (mouseinside == 1) {
					((std::queue<Event>*)events)->push(Event::MouseLeaveClient);
					mouseinside = 0;
				}
			}
			mousepos = _mousepos;
		}
		else {
			mousepos = _mousepos;
		}


		if (((MSG*)(&msg))->message == WM_QUIT || !IsWindow(hwnd)) {
			((std::queue<Event>*)events)->push(Event::Close);
		}
		if (((MSG*)(&msg))->message == WM_SETFOCUS || !IsWindow(hwnd)) {
			((std::queue<Event>*)events)->push(Event::GetFocus);
		}

		if (((std::queue<Event>*)events)->size() > 0) {
			return ((std::queue<Event>*)events)->front();
		}

		return Event::None;
	}
	Event Window::waitEvent() {
		GetMessage((MSG*)(&msg), hwnd, 0, 0);

		TranslateMessage((MSG*)(&msg));
		DispatchMessage((MSG*)(&msg));

		if (((MSG*)(&msg))->message == WM_QUIT || !IsWindow(hwnd)) {
			((std::queue<Event>*)events)->push(Event::Close);
		}
		if (((MSG*)(&msg))->message == WM_SETFOCUS || !IsWindow(hwnd)) {
			((std::queue<Event>*)events)->push(Event::GetFocus);
		}

		if (((std::queue<Event>*)events)->size() > 0) {
			return ((std::queue<Event>*)events)->front();
		}
		return Event::None;
	}
	Event Window::putEvent(Event Tevent) {
		Event _pevent = Event::None;
		if (((std::queue<Event>*)events)->size() > 0) {
			((std::queue<Event>*)events)->back();
		}
		((std::queue<Event>*)events)->push(Tevent);
		return _pevent;
	}
	Event Window::popEvent() {

		if (((std::queue<Event>*)events)->size() > 0) {
			Event _pevent = ((std::queue<Event>*)events)->front();

			if (_pevent == Event::MouseWheelMoved) {
				mousewheeldelta = 0;
			}

			((std::queue<Event>*)events)->pop();
			return _pevent;
		}

		return Event::None;
	}

	int Window::keyPressed(Key Tkey) {
		return GetAsyncKeyState((int)Tkey);
	}
	int Window::keyPressed(unsigned char Tkey) {
		if (Tkey >= 'a' && Tkey <= 'z') {
			Tkey -= 32;
		}
		return GetAsyncKeyState(Tkey);
	}

	int Window::mousePressed(Mouse Tmousebutton) {
		return GetAsyncKeyState((int)Tmousebutton);
	}
	short Window::MouseWheel() {
		return mousewheeldelta;
	}

	Point<long> Window::MousePos() {
		POINT _mousepos;
		GetCursorPos(&_mousepos);
		ScreenToClient(hwnd, &_mousepos);

		return *((Point<long>*)&_mousepos);
	}
	Point<long> Window::ViewMousePos() {
		POINT _mousepos;
		GetCursorPos(&_mousepos);
		ScreenToClient(hwnd, &_mousepos);

		_mousepos.x *= (view->view.c.x - view->view.a.x) / (view->port.c.x - view->port.a.x);
		_mousepos.y *= (view->view.c.y - view->view.a.y) / (view->port.c.y - view->port.a.y);

		_mousepos.x -= (long)view->port.a.x;
		_mousepos.y -= (long)view->port.a.y;

		return *((Point<long>*)&_mousepos);
	}
	Point<float> Window::MousePosFloat() {
		POINT _mousepos;
		GetCursorPos(&_mousepos);
		ScreenToClient(hwnd, &_mousepos);

		return { (float)_mousepos.x,(float)_mousepos.y };
	}
	Point<float> Window::ViewMousePosFloat() {
		POINT _mousepos;
		GetCursorPos(&_mousepos);
		ScreenToClient(hwnd, &_mousepos);

		_mousepos.x -= (long)view->port.a.x;
		_mousepos.y -= (long)view->port.a.y;

		_mousepos.x = (long)(((float)_mousepos.x)*((view->view.c.x - view->view.a.x) / (view->port.c.x - view->port.a.x)));
		_mousepos.y = (long)(((float)_mousepos.y)*((view->view.c.y - view->view.a.y) / (view->port.c.y - view->port.a.y)));

		return { (float)_mousepos.x,(float)_mousepos.y };
	}

	Point<long> Window::WindowSize() {
		Point<long> _point;
		_point.x = rect.c.x - rect.a.x;
		_point.y = rect.c.y - rect.a.y;
		return _point;
	}

	Point<long> Window::ClientSize() {
		Point<long> _point;
		_point.x = width;
		_point.y = height;
		return _point;
	}

	void Window::EnableBlending(BlendFactor TSourceFac, BlendFactor TDestFac) {
		int _TSF;
		int _TDF;
		switch (TSourceFac) {
		case BlendFactor::Zero: {
			_TSF = GL_ZERO;
			break;
		}
		case BlendFactor::One: {
			_TSF = GL_ONE;
			break;
		}
		case BlendFactor::SourceAlpha: {
			_TSF = GL_SRC_ALPHA;
			break;
		}
		case BlendFactor::SourceColor: {
			_TSF = GL_SRC_COLOR;
			break;
		}
		case BlendFactor::DestAlpha: {
			_TSF = GL_DST_ALPHA;
			break;
		}
		case BlendFactor::DestColor: {
			_TSF = GL_DST_COLOR;
			break;
		}
		case BlendFactor::OneMinusDestAlpha: {
			_TSF = GL_ONE_MINUS_DST_ALPHA;
			break;
		}
		case BlendFactor::OneMinusDestColor: {
			_TSF = GL_ONE_MINUS_DST_COLOR;
			break;
		}
		case BlendFactor::OneMinusSourceAlpha: {
			_TSF = GL_ONE_MINUS_SRC_ALPHA;
			break;
		}
		case BlendFactor::OneMinusSourceColor: {
			_TSF = GL_ONE_MINUS_SRC_COLOR;
			break;
		}
		default: {
			_TSF = GL_ONE;
			break;
		}
		}
		switch (TDestFac) {
		case BlendFactor::Zero: {
			_TDF = GL_ZERO;
			break;
		}
		case BlendFactor::One: {
			_TDF = GL_ONE;
			break;
		}
		case BlendFactor::SourceAlpha: {
			_TDF = GL_SRC_ALPHA;
			break;
		}
		case BlendFactor::SourceColor: {
			_TDF = GL_SRC_COLOR;
			break;
		}
		case BlendFactor::DestAlpha: {
			_TDF = GL_DST_ALPHA;
			break;
		}
		case BlendFactor::DestColor: {
			_TDF = GL_DST_COLOR;
			break;
		}
		case BlendFactor::OneMinusDestAlpha: {
			_TDF = GL_ONE_MINUS_DST_ALPHA;
			break;
		}
		case BlendFactor::OneMinusDestColor: {
			_TDF = GL_ONE_MINUS_DST_COLOR;
			break;
		}
		case BlendFactor::OneMinusSourceAlpha: {
			_TDF = GL_ONE_MINUS_SRC_ALPHA;
			break;
		}
		case BlendFactor::OneMinusSourceColor: {
			_TDF = GL_ONE_MINUS_SRC_COLOR;
			break;
		}
		default: {
			_TDF = GL_ZERO;
			break;
		}
		}

		glEnable(GL_BLEND);
		glBlendFunc(_TSF, _TDF);
	}

	void Window::DisableBlending() {
		glDisable(GL_BLEND);
	}

	bool Window::EnterFullscreen(bool Tscreen) {
		// Tscreen : Using screen size or not
		if (Tscreen == 0) {
			return enterfullscreen(width, height);
		}
		else {
			RECT _desktoprect;

			GetWindowRect(GetDesktopWindow(), &_desktoprect);
			return enterfullscreen(_desktoprect.right, _desktoprect.bottom);
		}
	}
	bool Window::ExitFullScreen(WindowStyle Tstyle) {
		return leavefullscreen(Tstyle);
	}

	void Window::Update() {
		if (opengl >= 1 && hdc != NULL) {
			if (beginvertex == 1) {
				glEnd();
			}

			::SwapBuffers(hdc);
		}
		else {
			if (hdc != NULL) {
				BitBlt(hdc, 0, 0, width, height, chdc, 0, 0, SRCCOPY);
			}
		}
	}
}