#include <KPerpCore/Window.hpp>
#include <KPerpCore/Renderer.hpp>
#include <KPerpCore/Error.hpp>



#include "Ext/KGui.hpp"
#include "Ext/KGui/Button.hpp"
#include "Ext/KGui/Label.hpp"
#include "Ext/KGui/Textbox.hpp"

#ifdef APIENTRY
#undef APIENTRY
#endif

#include <windows.h>


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
		int _namesize = MultiByteToWideChar(CP_UTF8, 0, Ttext, -1, NULL, 0);
		wchar_t* _name = new wchar_t[_namesize];
		memset(_name, 0, sizeof(wchar_t)*_namesize);
		MultiByteToWideChar(CP_UTF8, 0, Ttext, -1, _name, _namesize);

		running = create_software_window(Tx, Ty, Tw, Th, _name, Tstyle);

		delete[] _name;

		if (running == 1) {
			events = new std::queue<Event>;
			((std::queue<Event>*)events)->push({ Event::Type::Construct });
			
			elementmanager = new KGui::ElementManager(*this);
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
				int _namesize = MultiByteToWideChar(CP_UTF8, 0, Ttext, -1, NULL, 0);
				wchar_t* _name = new wchar_t[_namesize];
				memset(_name, 0, sizeof(wchar_t)*_namesize);
				MultiByteToWideChar(CP_UTF8, 0, Ttext, -1, _name, _namesize);

				running = create_software_window(Tx, Ty, Tw, Th, _name, Tstyle);

				delete[] _name;

				if (running == 1) {
					events = new std::queue<Event>;
					((std::queue<Event>*)events)->push({ Event::Type::Construct });

					elementmanager = new KGui::ElementManager(*this);
				}
			}
		}
		else {
			// OpenGL
			int _namesize = MultiByteToWideChar(CP_UTF8, 0, Ttext, -1, NULL, 0);
			wchar_t* _name = new wchar_t[_namesize];
			memset(_name, 0, sizeof(wchar_t)*_namesize);
			MultiByteToWideChar(CP_UTF8, 0, Ttext, -1, _name, _namesize);
			running = create_opengl(Tx, Ty, Topengl, Tw, Th, _name, Tstyle);
			delete[] _name;
			if (running == 1) {
				events = new std::queue<Event>;

				elementmanager = new KGui::ElementManager(*this);
			}
		}
	}
	Window::Window(int Tw, int Th, const char* Ttext, WindowStyle Tstyle) {
		// Software
		int _namesize = MultiByteToWideChar(CP_UTF8, 0, Ttext, -1, NULL, 0);
		wchar_t* _name = new wchar_t[_namesize];
		memset(_name, 0, sizeof(wchar_t)*_namesize);
		MultiByteToWideChar(CP_UTF8, 0, Ttext, -1, _name, _namesize);

		running = create_software_window(_kp_userdefault, _kp_userdefault, Tw, Th, _name, Tstyle);

		delete[] _name;

		if (running == 1) {
			events = new std::queue<Event>;

			elementmanager = new KGui::ElementManager(*this);
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
				int _namesize = MultiByteToWideChar(CP_UTF8, 0, Ttext, -1, NULL, 0);
				wchar_t* _name = new wchar_t[_namesize];
				memset(_name, 0, sizeof(wchar_t)*_namesize);
				MultiByteToWideChar(CP_UTF8, 0, Ttext, -1, _name, _namesize);

				running = create_software_window(_kp_userdefault, _kp_userdefault, Tw, Th, _name, Tstyle);

				delete[] _name;

				if (running == 1) {
					events = new std::queue<Event>;

					elementmanager = new KGui::ElementManager(*this);
				}
			}
		}
		else {
			// OpenGL
			int _namesize = MultiByteToWideChar(CP_UTF8, 0, Ttext, -1, NULL, 0);
			wchar_t* _name = new wchar_t[_namesize];
			memset(_name, 0, sizeof(wchar_t)*_namesize);
			MultiByteToWideChar(CP_UTF8, 0, Ttext, -1, _name, _namesize);
			running = create_opengl(_kp_userdefault, _kp_userdefault, Topengl, Tw, Th, _name, Tstyle);
			delete[] _name;
			if (running == 1) {
				events = new std::queue<Event>;

				elementmanager = new KGui::ElementManager(*this);
			}
		}
	}

	Window::Window(int Tx, int Ty, int Tw, int Th, const wchar_t* Ttext, WindowStyle Tstyle) {
		// Software
		running = create_software_window(Tx, Ty, Tw, Th, Ttext, Tstyle);

		if (running == 1) {
			events = new std::queue<Event>;
			((std::queue<Event>*)events)->push({ Event::Type::Construct });

			elementmanager = new KGui::ElementManager(*this);
		}
	}
	Window::Window(int Topengl, int Tx, int Ty, int Tw, int Th, const wchar_t* Ttext, WindowStyle Tstyle) {
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
					((std::queue<Event>*)events)->push({ Event::Type::Construct });

					elementmanager = new KGui::ElementManager(*this);
				}
			}
		}
		else {
			// OpenGL
			running = create_opengl(Tx, Ty, Topengl, Tw, Th, Ttext, Tstyle);
			if (running == 1) {
				events = new std::queue<Event>;

				elementmanager = new KGui::ElementManager(*this);
			}
		}
	}
	Window::Window(int Tw, int Th, const wchar_t* Ttext, WindowStyle Tstyle) {
		// Software
		running = create_software_window(_kp_userdefault, _kp_userdefault, Tw, Th, Ttext, Tstyle);
		if (running == 1) {
			events = new std::queue<Event>;

			elementmanager = new KGui::ElementManager(*this);
		}
	}
	Window::Window(int Topengl, int Tw, int Th, const wchar_t* Ttext, WindowStyle Tstyle) {
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

					elementmanager = new KGui::ElementManager(*this);
				}
			}
		}
		else {
			// OpenGL
			running = create_opengl(_kp_userdefault, _kp_userdefault, Topengl, Tw, Th, Ttext, Tstyle);
			if (running == 1) {
				events = new std::queue<Event>;

				elementmanager = new KGui::ElementManager(*this);
			}
		}
	}

	void Window::Destroy() {
		Renderer::Destroy();
		if (events != NULL) {
			delete (std::queue<Event>*)events;
			events = NULL;
		}
		if (elementmanager != NULL) {
			delete (KGui::ElementManager*)elementmanager;
			elementmanager = NULL;
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
		if (PeekMessageW((MSG*)(&msg), hwnd, 0, 0, 1)) {

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
						((std::queue<Event>*)events)->push({ Event::Type::MouseEnterClientFast });
						mouseinside = 1;
					}

					((std::queue<Event>*)events)->push({ Event::Type::MouseMoveInside, mousepos });
				}
				else {
					if (mouseinside == 1) {
						((std::queue<Event>*)events)->push({ Event::Type::MouseLeaveClientFast });
						mouseinside = 0;
					}
				}
				mousepos = _mousepos;
			}
			else {
				mousepos = _mousepos;
			}
		}

		//if (((MSG*)(&msg))->message == WM_QUIT || !IsWindow(hwnd)) {
		//	((std::queue<Event>*)events)->push({ Event::Type::Close });
		//}

		if (((std::queue<Event>*)events)->size() > 0) {
			return ((std::queue<Event>*)events)->front();
		}



		return { Event::Type::None };
	}
	Event Window::waitEvent() {

		memset(msg, 0, sizeof(MSG));
		GetMessageW((MSG*)(&msg), hwnd, 0, 0);

		TranslateMessage((MSG*)(&msg));
		DispatchMessageW((MSG*)(&msg));

		//if (((MSG*)(&msg))->message == WM_QUIT || !IsWindow(hwnd)) {
		//	((std::queue<Event>*)events)->push({ Event::Type::Close });
		//}

		if (((std::queue<Event>*)events)->size() > 0) {
			return ((std::queue<Event>*)events)->front();
		}
		return { Event::Type::None };
	}
	int Window::waitPullEvent(Event& Tevent) {
		if (hwnd) {
			int lol = ((std::queue<Event>*)events)->size();
			if (((std::queue<Event>*)events)->size() == 0) {
				if (GetMessageW((MSG*)(&msg), hwnd, 0, 0) > 0) {
					TranslateMessage((MSG*)(&msg));
					DispatchMessageW((MSG*)(&msg));
				}
			}
			if (((std::queue<Event>*)events)->size() > 0) {
				Tevent = ((std::queue<Event>*)events)->front();
				((std::queue<Event>*)events)->pop();
				return (((std::queue<Event>*)events)->size() + 1);
			}
		}
		Tevent = { Event::Type::None };
		return 0;
	}
	int Window::pullEvent(Event& Tevent) {
		std::queue<Event>& _events = *((std::queue<Event>*)events);
		if (hwnd) {
			//int lol = ((std::queue<Event>*)events)->size();
			if (((std::queue<Event>*)events)->size() == 0) {
				if (PeekMessageW((MSG*)(&msg), hwnd, 0, 0, 1) > 0) {
					TranslateMessage((MSG*)(&msg));
					DispatchMessageW((MSG*)(&msg));

					if (((MSG*)&msg)->message == WM_SIZE) {
						
					}
				}
			}
			if (((std::queue<Event>*)events)->size() > 0) {
				Tevent = ((std::queue<Event>*)events)->front();
				((std::queue<Event>*)events)->pop();
				return (((std::queue<Event>*)events)->size() + 1);
			}
		}
		Tevent = { Event::Type::None };
		return 0;
	}
	int Window::getEventQueueSize() {
		return ((std::queue<Event>*)events)->size();
	}
	Event Window::putEvent(Event Tevent) {
		Event _pevent = { Event::Type::None };
		if (((std::queue<Event>*)events)->size() > 0) {
			((std::queue<Event>*)events)->back();
		}
		((std::queue<Event>*)events)->push(Tevent);
		return _pevent;
	}
	Event Window::popEvent() {

		if (((std::queue<Event>*)events)->size() > 0) {
			Event _pevent = ((std::queue<Event>*)events)->front();

			if (_pevent.type == Event::Type::MouseWheelMoved) {
				mousewheeldelta = 0;
			}

			((std::queue<Event>*)events)->pop();
			return _pevent;
		}

		return { Event::Type::None };
	}

	int Window::keyPress(Key Tkey) {
		return GetAsyncKeyState((int)Tkey);
	}
	int Window::keyPress(unsigned char Tkey) {
		if (Tkey >= 'a' && Tkey <= 'z') {
			Tkey -= 32;
		}
		return GetAsyncKeyState(Tkey);
	}

	int Window::keyPressLocal(Key Tkey) {
		return GetKeyState((int)Tkey);
	}
	int Window::keyPressLocal(unsigned char Tkey) {
		if (Tkey >= 'a' && Tkey <= 'z') {
			Tkey -= 32;
		}
		return GetKeyState(Tkey);
	}

	int Window::keyHold(Key Tkey) {
		return pressed[(int)Tkey] == 2;
	}
	int Window::keyHold(unsigned char Tkey) {
		if (Tkey >= 'a' && Tkey <= 'z') {
			Tkey -= 32;
		}
		return pressed[(int)Tkey] == 2;
	}

	int Window::keyPressed(Key Tkey) {
		return pressed[(int)Tkey] == 1;
	}
	int Window::keyPressed(unsigned char Tkey) {
		if (Tkey >= 'a' && Tkey <= 'z') {
			Tkey -= 32;
		}
		return pressed[(int)Tkey] == 1;
	}
	int Window::keyReleased(Key Tkey) {
		return pressed[(int)Tkey] == 3;
	}
	int Window::keyReleased(unsigned char Tkey) {
		if (Tkey >= 'a' && Tkey <= 'z') {
			Tkey -= 32;
		}
		return pressed[(int)Tkey] == 3;
	}

	int Window::mousePress(Mouse Tmousebutton) {
		return GetAsyncKeyState((int)Tmousebutton);
	}
	int Window::mousePressLocal(Mouse Tmousebutton) {
		return GetKeyState((int)Tmousebutton);
	}
	int Window::mousePressed(Mouse Tmousebutton) {
		return pressed[(int)Tmousebutton] == 1;
	}
	int Window::mouseReleased(Mouse Tmousebutton) {
		return pressed[(int)Tmousebutton] == 3;
	}
	int Window::mouseHold(Mouse Tmousebutton) {
		return pressed[(int)Tmousebutton] == 2;
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

		_mousepos.x += (float)view->view.a.x;
		_mousepos.y += (float)view->view.a.y;

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

		_mousepos.x = (long)(((float)_mousepos.x)*((view->view.c.x - view->view.a.x) / (view->port.c.x - view->port.a.x)));
		_mousepos.y = (long)(((float)_mousepos.y)*((view->view.c.y - view->view.a.y) / (view->port.c.y - view->port.a.y)));

		_mousepos.x -= (long)view->port.a.x;
		_mousepos.y -= (long)view->port.a.y;

		_mousepos.x += view->view.a.x;
		_mousepos.y += view->view.a.y;

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
		if (hglrc != NULL) {
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
	}

	void Window::DisableBlending() {
		if (hglrc != NULL) {
			glDisable(GL_BLEND);
		}
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

	static enum stylepos {
		None = 0,
		Overlapped = 0,
		Popup = 31,
		Minimized = 30,
		Maximized = 25,
		Visible = 28,
		Disabled = 27,
		Caption = 23,
		Border = 23,
		SysMenu = 19,
		ThickFrame = 18,
		MinimizeBox = 17,
		MaximizeBox = 16,

		FullScreen = 5,
	};

	static unsigned int getStylePos(WindowStyle Tstyle) {
		switch (Tstyle) {
		case WindowStyle::Overlapped: {
			return 0;
			break;
		}
		case WindowStyle::Popup: {
			return 31;
			break;
		}
		case WindowStyle::Minimized: {
			return 30;
			break;
		}
		case WindowStyle::Maximized: {
			return 25;
			break;
		}
		case WindowStyle::Visible: {
			return 28;
			break;
		}
		case WindowStyle::Disabled: {
			return 27 ;
			break;
		}
		case WindowStyle::Caption: {
			return 23;
			break;
		}
		case WindowStyle::Border: {
			return 23;
			break;
		}
		case WindowStyle::SysMenu: {
			return 19;
			break;
		}
		case WindowStyle::ThickFrame: {
			return 18;
			break;
		}
		case WindowStyle::MinimizeBox: {
			return 17;
			break;
		}
		case WindowStyle::MaximizeBox: {
			return 16;
			break;
		}

		case WindowStyle::FullScreen: {
			return 5;
			break;
		}
		}

		return 0;
	}

	WindowStyle Window::getStyle(WindowStyle Tstyle) {
		return (WindowStyle)(((unsigned int)style >> getStylePos(Tstyle)) * (unsigned int)Tstyle);
	}
	bool Window::isStyle(WindowStyle Tstyle) {
		return ((unsigned int)style >> getStylePos(Tstyle));
	}

	bool Window::getMinimized() {
		return (minimized == 1);
	}
	bool Window::getMaximized() {
		return (minimized == 2);
	}

	void Window::processInput() {
		unsigned char _key[256];
		GetKeyboardState(_key);

		//_asm mov eax, 0
		//_asm mov ebx, 0
		for (unsigned char i = 0;i < 223;i++) {
			if (_key[i] >> 7) {
				if (pressed[i] > 0) {
					pressed[i] = 2;
				}
				else {
					pressed[i] = 1;
				}
			}
			else {
				if (pressed[i] == 1 || pressed[i] == 2) {
					pressed[i] = 3;
				}
				else {
					pressed[i] = 0;
				}
			}
		}
	}
	void Window::processKeyInput() {
		unsigned char _key[256];
		GetKeyboardState(_key);

		//_asm mov eax, 0
		//_asm mov ebx, 0
		for (unsigned char i = 0;i < 223;i++) {
			if (_key[i] >> 7) {
				if (pressed[i] > 0) {
					pressed[i] = 2;
				}
				else {
					pressed[i] = 1;
				}
			}
			else {
				if (pressed[i] == 1 || pressed[i] == 2) {
					pressed[i] = 3;
				}
				else {
					pressed[i] = 0;
				}
			}
		}
	}
	void Window::processMouseInput() {
		unsigned char _key[256];
		GetKeyboardState(_key);

		if (_key[(int)Mouse::LeftButton] >> 7) {
			if (pressed[(int)Mouse::LeftButton]) {
				pressed[(int)Mouse::LeftButton] = 2;
			}
			else {
				pressed[(int)Mouse::LeftButton] = 1;
			}
		}
		else {
			if (pressed[(int)Mouse::LeftButton] == 1 || pressed[(int)Mouse::LeftButton] == 2) {
				pressed[(int)Mouse::LeftButton] = 3;
			}
			else {
				pressed[(int)Mouse::LeftButton] = 0;
			}
		}
		if (_key[(int)Mouse::RightButton]) {
			if (pressed[(int)Mouse::RightButton]) {
				pressed[(int)Mouse::RightButton] = 2;
			}
			else {
				pressed[(int)Mouse::RightButton] = 1;
			}
		}
		else {
			if (pressed[(int)Mouse::RightButton] == 1 || pressed[(int)Mouse::RightButton] == 2) {
				pressed[(int)Mouse::RightButton] = 3;
			}
			else {
				pressed[(int)Mouse::RightButton] = 0;
			}
		}
		if (_key[(int)Mouse::MiddleButton]) {
			if (pressed[(int)Mouse::MiddleButton]) {
				pressed[(int)Mouse::MiddleButton] = 2;
			}
			else {
				pressed[(int)Mouse::MiddleButton] = 1;
			}
		}
		else {
			if (pressed[(int)Mouse::MiddleButton] == 1 || pressed[(int)Mouse::MiddleButton] == 2) {
				pressed[(int)Mouse::MiddleButton] = 3;
			}
			else {
				pressed[(int)Mouse::MiddleButton] = 0;
			}
		}
		if (_key[(int)Mouse::X1]) {
			if (pressed[(int)Mouse::X1]) {
				pressed[(int)Mouse::X1] = 2;
			}
			else {
				pressed[(int)Mouse::X1] = 1;
			}
		}
		else {
			if (pressed[(int)Mouse::X1] == 2) {
				pressed[(int)Mouse::X1] = 3;
			}
			else {
				pressed[(int)Mouse::X1] = 0;
			}
		}
		if (_key[(int)Mouse::X2]) {
			if (pressed[(int)Mouse::X2]) {
				pressed[(int)Mouse::X2] = 2;
			}
			else {
				pressed[(int)Mouse::X2] = 1;
			}
		}
		else {
			if (pressed[(int)Mouse::X2] == 2) {
				pressed[(int)Mouse::X2] = 3;
			}
			else {
				pressed[(int)Mouse::X2] = 0;
			}
		}
	}
	void Window::processKeyInputGlobal() {

		for (unsigned char i = 0;i < 223;i++) {
			if (GetAsyncKeyState(i) >> 7) {
				if (pressed[i] > 0) {
					pressed[i] = 2;
				}
				else {
					pressed[i] = 1;
				}
			}
			else {
				if (pressed[i] == 1 || pressed[i] == 2) {
					pressed[i] = 3;
				}
				else {
					pressed[i] = 0;
				}
			}
		}
	}
	void Window::processInputGlobal() {
		for (unsigned char i = 0;i < 223;i++) {
			
			if (GetAsyncKeyState(i) >> 7) {
				if (pressed[i] > 0) {
					pressed[i] = 2;
				}
				else {
					pressed[i] = 1;
				}
			}
			else {
				if (pressed[i] == 1 || pressed[i] == 2) {
					pressed[i] = 3;
				}
				else {
					pressed[i] = 0;
				}
			}
		}
	}
	void Window::processMouseInputGlobal() {
		if (GetAsyncKeyState((int)Mouse::LeftButton) >> 7) {
			if (pressed[(int)Mouse::LeftButton]) {
				pressed[(int)Mouse::LeftButton] = 2;
			}
			else {
				pressed[(int)Mouse::LeftButton] = 1;
			}
		}
		else {
			if (pressed[(int)Mouse::LeftButton] == 1 || pressed[(int)Mouse::LeftButton] == 2) {
				pressed[(int)Mouse::LeftButton] = 3;
			}
			else {
				pressed[(int)Mouse::LeftButton] = 0;
			}
		}
		if (GetAsyncKeyState((int)Mouse::RightButton)) {
			if (pressed[(int)Mouse::RightButton]) {
				pressed[(int)Mouse::RightButton] = 2;
			}
			else {
				pressed[(int)Mouse::RightButton] = 1;
			}
		}
		else {
			if (pressed[(int)Mouse::RightButton] == 1 || pressed[(int)Mouse::RightButton] == 2) {
				pressed[(int)Mouse::RightButton] = 3;
			}
			else {
				pressed[(int)Mouse::RightButton] = 0;
			}
		}
		if (GetAsyncKeyState((int)Mouse::MiddleButton)) {
			if (pressed[(int)Mouse::MiddleButton]) {
				pressed[(int)Mouse::MiddleButton] = 2;
			}
			else {
				pressed[(int)Mouse::MiddleButton] = 1;
			}
		}
		else {
			if (pressed[(int)Mouse::MiddleButton] == 1 || pressed[(int)Mouse::MiddleButton] == 2) {
				pressed[(int)Mouse::MiddleButton] = 3;
			}
			else {
				pressed[(int)Mouse::MiddleButton] = 0;
			}
		}
		if (GetAsyncKeyState((int)Mouse::X1)) {
			if (pressed[(int)Mouse::X1]) {
				pressed[(int)Mouse::X1] = 2;
			}
			else {
				pressed[(int)Mouse::X1] = 1;
			}
		}
		else {
			if (pressed[(int)Mouse::X1] == 2) {
				pressed[(int)Mouse::X1] = 3;
			}
			else {
				pressed[(int)Mouse::X1] = 0;
			}
		}
		if (GetAsyncKeyState((int)Mouse::X2)) {
			if (pressed[(int)Mouse::X2]) {
				pressed[(int)Mouse::X2] = 2;
			}
			else {
				pressed[(int)Mouse::X2] = 1;
			}
		}
		else {
			if (pressed[(int)Mouse::X2] == 2) {
				pressed[(int)Mouse::X2] = 3;
			}
			else {
				pressed[(int)Mouse::X2] = 0;
			}
		}
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

	Window::~Window() {
		Destroy();
	}

	Window& operator<=(Window& Twindow, KGui::Element* Telement) {
		if (Telement != NULL) {
			KGui::ElementManager& elementmanager = *((KGui::ElementManager*)Twindow.elementmanager);

			elementmanager.add(0, Telement);
		}

		return Twindow;
	}

	void Window::ProcessWidget() {
		using namespace KGui;
		using Event = KGui::Instance::Event;

		ElementManager& elementmanager = *((ElementManager*)this->elementmanager);

		bool _pressonotherwidgets = 0;

		int _size = elementmanager.getSize();
		//return pressed[(int)Tmousebutton] == 1
		int leftpress = GetAsyncKeyState((int)Mouse::LeftButton);
		int rightpress = GetAsyncKeyState((int)Mouse::RightButton);
		int middlepress = GetAsyncKeyState((int)Mouse::MiddleButton);
		int leftpressed = pressed[(int)Mouse::LeftButton] == 1;
		int rightpressed = pressed[(int)Mouse::RightButton] == 1;
		int middlepressed = pressed[(int)Mouse::MiddleButton] == 1;
		int leftreleased = pressed[(int)Mouse::LeftButton] == 3;
		int rightreleased = pressed[(int)Mouse::RightButton] == 3;
		int middlereleased = pressed[(int)Mouse::MiddleButton] == 3;

		for (int i = 0;i < _size;i++) {
			mousepos = ViewMousePos();

			Element& _element = *(elementmanager[i]);

			if (_element.drawable) {
				Instance& _inst = *((Instance*)&_element);

				switch (_inst.type) {
				case Type::Button: {
					Button& _button = *((Button*)&_inst);
					Rectangle<int> _ppos = _button.rect;

					if (_button.tl.element != NULL) {
						if (((unsigned int)_button.tl.element) == Dock::Window) {
							switch (_button.tl.point) {
							case Dock::TopLeft: {
								if (!_button.tl.autopoint) {
									_button.rect.a.x = _button.tl.pos.x;
									_button.rect.a.y = _button.tl.pos.y;
								}
								else {
									_button.tl.pos.x = _ppos.a.x;
									_button.tl.pos.y = _ppos.a.y;
									_button.tl.autopoint = 0;
								}
								break;
							}
							case Dock::TopRight: {
								if (!_button.tl.autopoint) {
									_button.rect.a.x = width + _button.tl.pos.x;
									_button.rect.a.y = _button.tl.pos.y;
								}
								else {
									_button.tl.pos.x = _ppos.a.x - width;
									_button.tl.pos.y = _ppos.a.y;
									_button.tl.autopoint = 0;
								}
								break;
							}
							case Dock::BottomLeft: {
								if (!_button.tl.autopoint) {
									_button.rect.a.x = _button.tl.pos.x;
									_button.rect.a.y = height + _button.tl.pos.y;
								}
								else {
									_button.tl.pos.x = _ppos.a.x;
									_button.tl.pos.y = _ppos.a.y - height;
									_button.tl.autopoint = 0;
								}
								break;
							}
							case Dock::BottomRight: {
								if (!_button.tl.autopoint) {
									_button.rect.a.x = width + _button.tl.pos.x;
									_button.rect.a.y = height + _button.tl.pos.y;
								}
								else {
									_button.tl.pos.x = _ppos.a.x - width;
									_button.tl.pos.y = _ppos.a.y - height;
									_button.tl.autopoint = 0;
								}
								break;
							}
							case Dock::Left: {
								if (!_button.tl.autopoint) {
									_button.rect.a.x = _button.tl.pos.x;
								}
								else {
									_button.tl.pos.x = _ppos.a.x;
									_button.tl.autopoint = 0;
								}
								break;
							}
							case Dock::Right: {
								if (!_button.tl.autopoint) {
									_button.rect.a.x = width + _button.tl.pos.x;
								}
								else {
									_button.tl.pos.x = _ppos.a.x - width;
									_button.tl.autopoint = 0;
								}
								break;
							}
							case Dock::Top: {
								if (!_button.tl.autopoint) {
									_button.rect.a.y = height + _button.tl.pos.y;
								}
								else {
									_button.tl.pos.y = _ppos.a.y - height;
									_button.tl.autopoint = 0;
								}
								break;
							}
							case Dock::Bottom: {
								if (!_button.tl.autopoint) {
									_button.rect.a.y = height + _button.tl.pos.y;
								}
								else {
									_button.tl.pos.y = _ppos.a.y - height;
									_button.tl.autopoint = 0;
								}
								break;
							}
							}
						}
					}
					if (_button.tr.element != NULL) {
						if (((unsigned int)_button.tr.element) == Dock::Window) {
							switch (_button.tr.point) {
							case Dock::TopLeft: {
								if (!_button.tr.autopoint) {
									_button.rect.c.x = _button.tr.pos.x;
									_button.rect.a.y = _button.tr.pos.y;
								}
								else {
									_button.tr.pos.x = _ppos.c.x;
									_button.tr.pos.y = _ppos.a.y;
									_button.tr.autopoint = 0;
								}
								break;
							}
							case Dock::TopRight: {
								if (!_button.tr.autopoint) {
									_button.rect.c.x = width + _button.tr.pos.x;
									_button.rect.a.y = _button.tr.pos.y;
								}
								else {
									_button.tr.pos.x = _ppos.c.x - width;
									_button.tr.pos.y = _ppos.a.y;
									_button.tr.autopoint = 0;
								}
								break;
							}
							case Dock::BottomLeft: {
								if (!_button.tr.autopoint) {
									_button.rect.c.x = _button.tr.pos.x;
									_button.rect.a.y = height + _button.tr.pos.y;
								}
								else {
									_button.tr.pos.x = _ppos.a.x;
									_button.tr.pos.y = _ppos.c.y - height;
									_button.tr.autopoint = 0;
								}
								break;
							}
							case Dock::BottomRight: {
								if (!_button.tr.autopoint) {
									_button.rect.c.x = width + _button.tr.pos.x;
									_button.rect.a.y = height + _button.tr.pos.y;
								}
								else {
									_button.tr.pos.x = _ppos.c.x - width;
									_button.tr.pos.y = _ppos.a.y - height;
									_button.tr.autopoint = 0;
								}
								break;
							}
							case Dock::Left: {
								if (!_button.tr.autopoint) {
									_button.rect.c.x = _button.tr.pos.x;
								}
								else {
									_button.tr.pos.x = _ppos.c.x;
									_button.tr.autopoint = 0;
								}
								break;
							}
							case Dock::Right: {
								if (!_button.tr.autopoint) {
									_button.rect.c.x = width + _button.tr.pos.x;
								}
								else {
									_button.tr.pos.x = _ppos.c.x - width;
									_button.tr.autopoint = 0;
								}
								break;
							}
							case Dock::Top: {
								if (!_button.tr.autopoint) {
									_button.rect.a.y = height + _button.tr.pos.y;
								}
								else {
									_button.tr.pos.y = _ppos.a.y - height;
									_button.tr.autopoint = 0;
								}
								break;
							}
							case Dock::Bottom: {
								if (!_button.tr.autopoint) {
									_button.rect.a.y = height + _button.tr.pos.y;
								}
								else {
									_button.tr.pos.y = _ppos.a.y - height;
									_button.tr.autopoint = 0;
								}
								break;
							}
							}
						}
					}
					if (_button.bl.element != NULL) {
						if (((unsigned int)_button.bl.element) == Dock::Window) {
							switch (_button.bl.point) {
							case Dock::TopLeft: {
								if (!_button.bl.autopoint) {
									_button.rect.a.x = _button.bl.pos.x;
									_button.rect.c.y = _button.bl.pos.y;
								}
								else {
									_button.bl.pos.x = _ppos.a.x;
									_button.bl.pos.y = _ppos.c.y;
									_button.bl.autopoint = 0;
								}
								break;
							}
							case Dock::TopRight: {
								if (!_button.bl.autopoint) {
									_button.rect.a.x = width + _button.bl.pos.x;
									_button.rect.c.y = _button.bl.pos.y;
								}
								else {
									_button.bl.pos.x = _ppos.a.x - width;
									_button.bl.pos.y = _ppos.c.y;
									_button.bl.autopoint = 0;
								}
								break;
							}
							case Dock::BottomLeft: {
								if (!_button.bl.autopoint) {
									_button.rect.a.x = _button.bl.pos.x;
									_button.rect.c.y = height + _button.bl.pos.y;
								}
								else {
									_button.bl.pos.x = _ppos.a.x;
									_button.bl.pos.y = _ppos.c.y - height;
									_button.bl.autopoint = 0;
								}
								break;
							}
							case Dock::BottomRight: {
								if (!_button.bl.autopoint) {
									_button.rect.a.x = width + _button.bl.pos.x;
									_button.rect.c.y = height + _button.bl.pos.y;
								}
								else {
									_button.bl.pos.x = _ppos.a.x - width;
									_button.bl.pos.y = _ppos.c.y - height;
									_button.bl.autopoint = 0;
								}
								break;
							}
							case Dock::Left: {
								if (!_button.bl.autopoint) {
									_button.rect.a.x = _button.bl.pos.x;
								}
								else {
									_button.bl.pos.x = _ppos.a.x;
									_button.bl.autopoint = 0;
								}
								break;
							}
							case Dock::Right: {
								if (!_button.bl.autopoint) {
									_button.rect.a.x = width + _button.bl.pos.x;
								}
								else {
									_button.bl.pos.x = _ppos.a.x - width;
									_button.bl.autopoint = 0;
								}
								break;
							}
							case Dock::Top: {
								if (!_button.bl.autopoint) {
									_button.rect.c.y = height + _button.bl.pos.y;
								}
								else {
									_button.bl.pos.y = _ppos.c.y - height;
									_button.bl.autopoint = 0;
								}
								break;
							}
							case Dock::Bottom: {
								if (!_button.bl.autopoint) {
									_button.rect.c.y = height + _button.bl.pos.y;
								}
								else {
									_button.bl.pos.y = _ppos.c.y - height;
									_button.bl.autopoint = 0;
								}
								break;
							}
							}
						}
					}
					if (_button.br.element != NULL) {
						if (((unsigned int)_button.br.element) == Dock::Window) {
							switch (_button.br.point) {
							case Dock::TopLeft: {
								if (!_button.br.autopoint) {
									_button.rect.c.x = _button.br.pos.x;
									_button.rect.c.y = _button.br.pos.y;
								}
								else {
									_button.br.pos.x = _ppos.c.x;
									_button.br.pos.y = _ppos.c.y;
									_button.br.autopoint = 0;
								}
								break;
							}
							case Dock::TopRight: {
								if (!_button.br.autopoint) {
									_button.rect.c.x = width + _button.br.pos.x;
									_button.rect.c.y = _button.br.pos.y;
								}
								else {
									_button.br.pos.x = _ppos.c.x - width;
									_button.br.pos.y = _ppos.c.y;
									_button.br.autopoint = 0;
								}
								break;
							}
							case Dock::BottomLeft: {
								if (!_button.br.autopoint) {
									_button.rect.c.x = _button.br.pos.x;
									_button.rect.c.y = height + _button.br.pos.y;
								}
								else {
									_button.br.pos.x = _ppos.c.x;
									_button.br.pos.y = _ppos.c.y - height;
									_button.br.autopoint = 0;
								}
								break;
							}
							case Dock::BottomRight: {
								if (!_button.br.autopoint) {
									_button.rect.c.x = width + _button.br.pos.x;
									_button.rect.c.y = height + _button.br.pos.y;
								}
								else {
									_button.br.pos.x = _ppos.c.x - width;
									_button.br.pos.y = _ppos.c.y - height;
									_button.br.autopoint = 0;
								}
								break;
							}
							case Dock::Left: {
								if (!_button.br.autopoint) {
									_button.rect.c.x = _button.br.pos.x;
								}
								else {
									_button.br.pos.x = _ppos.c.x;
									_button.br.autopoint = 0;
								}
								break;
							}
							case Dock::Right: {
								if (!_button.br.autopoint) {
									_button.rect.c.x = width + _button.br.pos.x;
								}
								else {
									_button.br.pos.x = _ppos.c.x - width;
									_button.br.autopoint = 0;
								}
								break;
							}
							case Dock::Top: {
								if (!_button.br.autopoint) {
									_button.rect.c.y = height + _button.br.pos.y;
								}
								else {
									_button.br.pos.y = _ppos.c.y - height;
									_button.br.autopoint = 0;
								}
								break;
							}
							case Dock::Bottom: {
								if (!_button.br.autopoint) {
									_button.rect.c.y = height + _button.br.pos.y;
								}
								else {
									_button.br.pos.y = _ppos.c.y - height;
									_button.br.autopoint = 0;
								}
								break;
							}
							}
						}
					}

					if (((_button.rect.c.x - _button.rect.a.x) != (_ppos.c.x - _ppos.a.x))
						|| ((_button.rect.c.x - _button.rect.a.x) != (_ppos.c.x - _ppos.a.x))) {
						_button.reset();
						_button.redraw();
					}

					if (_button.callback != NULL) {
						if (mousepos.x >= _button.rect.a.x &&
							mousepos.y >= _button.rect.a.y &&
							mousepos.x <= _button.rect.c.x &&
							mousepos.y <= _button.rect.c.y
						) {
							_button.callback(_button, Event::MouseOn, { mousepos.x - _inst.rect.a.x,mousepos.y - _inst.rect.a.y }, 0);//mouseentered
							if (!_button.mouseentered) {
								_button.callback(_button, Event::MouseEnter, { mousepos.x - _inst.rect.a.x,mousepos.y - _inst.rect.a.y }, 0);
								_button.mouseentered = 1;
							}
							if (leftpress) {
								_button.callback(_button, Event::OnClick, { mousepos.x - _inst.rect.a.x,mousepos.y - _inst.rect.a.y }, (int)Mouse::LeftButton);
							}
							if (rightpress) {
								_button.callback(_button, Event::OnClick, { mousepos.x - _inst.rect.a.x,mousepos.y - _inst.rect.a.y }, (int)Mouse::RightButton);
							}
							if (middlepress) {
								_button.callback(_button, Event::OnClick, { mousepos.x - _inst.rect.a.x,mousepos.y - _inst.rect.a.y }, (int)Mouse::MiddleButton);
							}
							if (leftpressed) {
								_pressonotherwidgets = 1;
								_button.callback(_button, Event::OnPressed, { mousepos.x - _inst.rect.a.x,mousepos.y - _inst.rect.a.y }, (int)Mouse::LeftButton);
								_button.pressed[0] = 1;
							}
							if (rightpressed) {
								_button.callback(_button, Event::OnPressed, { mousepos.x - _inst.rect.a.x,mousepos.y - _inst.rect.a.y }, (int)Mouse::RightButton);
								_button.pressed[1] = 1;
							}
							if (middlepressed) {
								_button.callback(_button, Event::OnPressed, { mousepos.x - _inst.rect.a.x,mousepos.y - _inst.rect.a.y }, (int)Mouse::MiddleButton);
								_button.pressed[2] = 1;
							}
							if (leftreleased) {
								_button.callback(_button, Event::OnReleased, { mousepos.x - _inst.rect.a.x,mousepos.y - _inst.rect.a.y }, (int)Mouse::LeftButton);
								if (_button.pressed[0]) {
									_button.callback(_button, Event::OnClicked, { mousepos.x - _inst.rect.a.x,mousepos.y - _inst.rect.a.y }, (int)Mouse::LeftButton);
									_button.pressed[0] = 0;
								}
							}
							if (rightreleased) {
								_button.callback(_button, Event::OnReleased, { mousepos.x - _inst.rect.a.x,mousepos.y - _inst.rect.a.y }, (int)Mouse::RightButton);
								if (_button.pressed[1]) {
									_button.callback(_button, Event::OnClicked, { mousepos.x - _inst.rect.a.x,mousepos.y - _inst.rect.a.y }, (int)Mouse::LeftButton);
									_button.pressed[1] = 0;
								}
							}
							if (middlereleased) {
								_button.callback(_button, Event::OnReleased, { mousepos.x - _inst.rect.a.x,mousepos.y - _inst.rect.a.y }, (int)Mouse::MiddleButton);
								if (_button.pressed[2]) {
									_button.callback(_button, Event::OnClicked, { mousepos.x - _inst.rect.a.x,mousepos.y - _inst.rect.a.y }, (int)Mouse::LeftButton);
									_button.pressed[2] = 0;
								}
							}
						}
						else {
							if (_button.mouseentered) {
								_button.callback(_button, Event::MouseLeave, { mousepos.x - _inst.rect.a.x,mousepos.y - _inst.rect.a.y }, 0);
								_button.mouseentered = 0;
								_button.pressed[0] = 0;
								_button.pressed[1] = 0;
								_button.pressed[2] = 0;
							}
						}
					}
					break;
				}
				case Type::Label: {
					Label& _label = *((Label*)&_inst);
					Rectangle<int> _ppos = _label.rect;

					if (_label.tl.element != NULL) {
						if (((unsigned int)_label.tl.element) == Dock::Window) {
							switch (_label.tl.point) {
							case Dock::TopLeft: {
								if (!_label.tl.autopoint) {
									_label.rect.a.x = _label.tl.pos.x;
									_label.rect.a.y = _label.tl.pos.y;
								}
								else {
									_label.tl.pos.x = _ppos.a.x;
									_label.tl.pos.y = _ppos.a.y;
									_label.tl.autopoint = 0;
								}
								break;
							}
							case Dock::TopRight: {
								if (!_label.tl.autopoint) {
									_label.rect.a.x = width + _label.tl.pos.x;
									_label.rect.a.y = _label.tl.pos.y;
								}
								else {
									_label.tl.pos.x = _ppos.a.x - width;
									_label.tl.pos.y = _ppos.a.y;
									_label.tl.autopoint = 0;
								}
								break;
							}
							case Dock::BottomLeft: {
								if (!_label.tl.autopoint) {
									_label.rect.a.x = _label.tl.pos.x;
									_label.rect.a.y = height + _label.tl.pos.y;
								}
								else {
									_label.tl.pos.x = _ppos.a.x;
									_label.tl.pos.y = _ppos.a.y - height;
									_label.tl.autopoint = 0;
								}
								break;
							}
							case Dock::BottomRight: {
								if (!_label.tl.autopoint) {
									_label.rect.a.x = width + _label.tl.pos.x;
									_label.rect.a.y = height + _label.tl.pos.y;
								}
								else {
									_label.tl.pos.x = _ppos.a.x - width;
									_label.tl.pos.y = _ppos.a.y - height;
									_label.tl.autopoint = 0;
								}
								break;
							}
							case Dock::Left: {
								if (!_label.tl.autopoint) {
									_label.rect.a.x = _label.tl.pos.x;
								}
								else {
									_label.tl.pos.x = _ppos.a.x;
									_label.tl.autopoint = 0;
								}
								break;
							}
							case Dock::Right: {
								if (!_label.tl.autopoint) {
									_label.rect.a.x = width + _label.tl.pos.x;
								}
								else {
									_label.tl.pos.x = _ppos.a.x - width;
									_label.tl.autopoint = 0;
								}
								break;
							}
							case Dock::Top: {
								if (!_label.tl.autopoint) {
									_label.rect.a.y = height + _label.tl.pos.y;
								}
								else {
									_label.tl.pos.y = _ppos.a.y - height;
									_label.tl.autopoint = 0;
								}
								break;
							}
							case Dock::Bottom: {
								if (!_label.tl.autopoint) {
									_label.rect.a.y = height + _label.tl.pos.y;
								}
								else {
									_label.tl.pos.y = _ppos.a.y - height;
									_label.tl.autopoint = 0;
								}
								break;
							}
							}
						}
					}
					if (_label.tr.element != NULL) {
						if (((unsigned int)_label.tr.element) == Dock::Window) {
							switch (_label.tr.point) {
							case Dock::TopLeft: {
								if (!_label.tr.autopoint) {
									_label.rect.c.x = _label.tr.pos.x;
									_label.rect.a.y = _label.tr.pos.y;
								}
								else {
									_label.tr.pos.x = _ppos.c.x;
									_label.tr.pos.y = _ppos.a.y;
									_label.tr.autopoint = 0;
								}
								break;
							}
							case Dock::TopRight: {
								if (!_label.tr.autopoint) {
									_label.rect.c.x = width + _label.tr.pos.x;
									_label.rect.a.y = _label.tr.pos.y;
								}
								else {
									_label.tr.pos.x = _ppos.c.x - width;
									_label.tr.pos.y = _ppos.a.y;
									_label.tr.autopoint = 0;
								}
								break;
							}
							case Dock::BottomLeft: {
								if (!_label.tr.autopoint) {
									_label.rect.c.x = _label.tr.pos.x;
									_label.rect.a.y = height + _label.tr.pos.y;
								}
								else {
									_label.tr.pos.x = _ppos.a.x;
									_label.tr.pos.y = _ppos.c.y - height;
									_label.tr.autopoint = 0;
								}
								break;
							}
							case Dock::BottomRight: {
								if (!_label.tr.autopoint) {
									_label.rect.c.x = width + _label.tr.pos.x;
									_label.rect.a.y = height + _label.tr.pos.y;
								}
								else {
									_label.tr.pos.x = _ppos.c.x - width;
									_label.tr.pos.y = _ppos.a.y - height;
									_label.tr.autopoint = 0;
								}
								break;
							}
							case Dock::Left: {
								if (!_label.tr.autopoint) {
									_label.rect.c.x = _label.tr.pos.x;
								}
								else {
									_label.tr.pos.x = _ppos.c.x;
									_label.tr.autopoint = 0;
								}
								break;
							}
							case Dock::Right: {
								if (!_label.tr.autopoint) {
									_label.rect.c.x = width + _label.tr.pos.x;
								}
								else {
									_label.tr.pos.x = _ppos.c.x - width;
									_label.tr.autopoint = 0;
								}
								break;
							}
							case Dock::Top: {
								if (!_label.tr.autopoint) {
									_label.rect.a.y = height + _label.tr.pos.y;
								}
								else {
									_label.tr.pos.y = _ppos.a.y - height;
									_label.tr.autopoint = 0;
								}
								break;
							}
							case Dock::Bottom: {
								if (!_label.tr.autopoint) {
									_label.rect.a.y = height + _label.tr.pos.y;
								}
								else {
									_label.tr.pos.y = _ppos.a.y - height;
									_label.tr.autopoint = 0;
								}
								break;
							}
							}
						}
					}
					if (_label.bl.element != NULL) {
						if (((unsigned int)_label.bl.element) == Dock::Window) {
							switch (_label.bl.point) {
							case Dock::TopLeft: {
								if (!_label.bl.autopoint) {
									_label.rect.a.x = _label.bl.pos.x;
									_label.rect.c.y = _label.bl.pos.y;
								}
								else {
									_label.bl.pos.x = _ppos.a.x;
									_label.bl.pos.y = _ppos.c.y;
									_label.bl.autopoint = 0;
								}
								break;
							}
							case Dock::TopRight: {
								if (!_label.bl.autopoint) {
									_label.rect.a.x = width + _label.bl.pos.x;
									_label.rect.c.y = _label.bl.pos.y;
								}
								else {
									_label.bl.pos.x = _ppos.a.x - width;
									_label.bl.pos.y = _ppos.c.y;
									_label.bl.autopoint = 0;
								}
								break;
							}
							case Dock::BottomLeft: {
								if (!_label.bl.autopoint) {
									_label.rect.a.x = _label.bl.pos.x;
									_label.rect.c.y = height + _label.bl.pos.y;
								}
								else {
									_label.bl.pos.x = _ppos.a.x;
									_label.bl.pos.y = _ppos.c.y - height;
									_label.bl.autopoint = 0;
								}
								break;
							}
							case Dock::BottomRight: {
								if (!_label.bl.autopoint) {
									_label.rect.a.x = width + _label.bl.pos.x;
									_label.rect.c.y = height + _label.bl.pos.y;
								}
								else {
									_label.bl.pos.x = _ppos.a.x - width;
									_label.bl.pos.y = _ppos.c.y - height;
									_label.bl.autopoint = 0;
								}
								break;
							}
							case Dock::Left: {
								if (!_label.bl.autopoint) {
									_label.rect.a.x = _label.bl.pos.x;
								}
								else {
									_label.bl.pos.x = _ppos.a.x;
									_label.bl.autopoint = 0;
								}
								break;
							}
							case Dock::Right: {
								if (!_label.bl.autopoint) {
									_label.rect.a.x = width + _label.bl.pos.x;
								}
								else {
									_label.bl.pos.x = _ppos.a.x - width;
									_label.bl.autopoint = 0;
								}
								break;
							}
							case Dock::Top: {
								if (!_label.bl.autopoint) {
									_label.rect.c.y = height + _label.bl.pos.y;
								}
								else {
									_label.bl.pos.y = _ppos.c.y - height;
									_label.bl.autopoint = 0;
								}
								break;
							}
							case Dock::Bottom: {
								if (!_label.bl.autopoint) {
									_label.rect.c.y = height + _label.bl.pos.y;
								}
								else {
									_label.bl.pos.y = _ppos.c.y - height;
									_label.bl.autopoint = 0;
								}
								break;
							}
							}
						}
					}
					if (_label.br.element != NULL) {
						if (((unsigned int)_label.br.element) == Dock::Window) {
							switch (_label.br.point) {
							case Dock::TopLeft: {
								if (!_label.br.autopoint) {
									_label.rect.c.x = _label.br.pos.x;
									_label.rect.c.y = _label.br.pos.y;
								}
								else {
									_label.br.pos.x = _ppos.c.x;
									_label.br.pos.y = _ppos.c.y;
									_label.br.autopoint = 0;
								}
								break;
							}
							case Dock::TopRight: {
								if (!_label.br.autopoint) {
									_label.rect.c.x = width + _label.br.pos.x;
									_label.rect.c.y = _label.br.pos.y;
								}
								else {
									_label.br.pos.x = _ppos.c.x - width;
									_label.br.pos.y = _ppos.c.y;
									_label.br.autopoint = 0;
								}
								break;
							}
							case Dock::BottomLeft: {
								if (!_label.br.autopoint) {
									_label.rect.c.x = _label.br.pos.x;
									_label.rect.c.y = height + _label.br.pos.y;
								}
								else {
									_label.br.pos.x = _ppos.c.x;
									_label.br.pos.y = _ppos.c.y - height;
									_label.br.autopoint = 0;
								}
								break;
							}
							case Dock::BottomRight: {
								if (!_label.br.autopoint) {
									_label.rect.c.x = width + _label.br.pos.x;
									_label.rect.c.y = height + _label.br.pos.y;
								}
								else {
									_label.br.pos.x = _ppos.c.x - width;
									_label.br.pos.y = _ppos.c.y - height;
									_label.br.autopoint = 0;
								}
								break;
							}
							case Dock::Left: {
								if (!_label.br.autopoint) {
									_label.rect.c.x = _label.br.pos.x;
								}
								else {
									_label.br.pos.x = _ppos.c.x;
									_label.br.autopoint = 0;
								}
								break;
							}
							case Dock::Right: {
								if (!_label.br.autopoint) {
									_label.rect.c.x = width + _label.br.pos.x;
								}
								else {
									_label.br.pos.x = _ppos.c.x - width;
									_label.br.autopoint = 0;
								}
								break;
							}
							case Dock::Top: {
								if (!_label.br.autopoint) {
									_label.rect.c.y = height + _label.br.pos.y;
								}
								else {
									_label.br.pos.y = _ppos.c.y - height;
									_label.br.autopoint = 0;
								}
								break;
							}
							case Dock::Bottom: {
								if (!_label.br.autopoint) {
									_label.rect.c.y = height + _label.br.pos.y;
								}
								else {
									_label.br.pos.y = _ppos.c.y - height;
									_label.br.autopoint = 0;
								}
								break;
							}
							}
						}
					}

					if (((_label.rect.c.x - _label.rect.a.x) != (_ppos.c.x - _ppos.a.x))
						|| ((_label.rect.c.x - _label.rect.a.x) != (_ppos.c.x - _ppos.a.x))) {
						_label.reset();
						_label.redraw();
					}

					if (_label.callback != NULL) {
						if (mousepos.x >= _label.rect.a.x &&
							mousepos.y >= _label.rect.a.y &&
							mousepos.x <= _label.rect.c.x &&
							mousepos.y <= _label.rect.c.y
							) {
							_label.callback(_label, Event::MouseOn, { mousepos.x - _inst.rect.a.x,mousepos.y - _inst.rect.a.y }, 0);//mouseentered
							if (!_label.mouseentered) {
								_label.callback(_label, Event::MouseEnter, { mousepos.x - _inst.rect.a.x,mousepos.y - _inst.rect.a.y }, 0);
								_label.mouseentered = 1;
							}
							if (leftpress) {
								_label.callback(_label, Event::OnClick, { mousepos.x - _inst.rect.a.x,mousepos.y - _inst.rect.a.y }, (int)Mouse::LeftButton);
							}
							if (rightpress) {
								_label.callback(_label, Event::OnClick, { mousepos.x - _inst.rect.a.x,mousepos.y - _inst.rect.a.y }, (int)Mouse::RightButton);
							}
							if (middlepress) {
								_label.callback(_label, Event::OnClick, { mousepos.x - _inst.rect.a.x,mousepos.y - _inst.rect.a.y }, (int)Mouse::MiddleButton);
							}
							if (leftpressed) {
								_pressonotherwidgets = 1;
								_label.callback(_label, Event::OnPressed, { mousepos.x - _inst.rect.a.x,mousepos.y - _inst.rect.a.y }, (int)Mouse::LeftButton);
								_label.pressed[0] = 1;
							}
							if (rightpressed) {
								_label.callback(_label, Event::OnPressed, { mousepos.x - _inst.rect.a.x,mousepos.y - _inst.rect.a.y }, (int)Mouse::RightButton);
								_label.pressed[1] = 1;
							}
							if (middlepressed) {
								_label.callback(_label, Event::OnPressed, { mousepos.x - _inst.rect.a.x,mousepos.y - _inst.rect.a.y }, (int)Mouse::MiddleButton);
								_label.pressed[2] = 1;
							}
							if (leftreleased) {
								_label.callback(_label, Event::OnReleased, { mousepos.x - _inst.rect.a.x,mousepos.y - _inst.rect.a.y }, (int)Mouse::LeftButton);
								if (_label.pressed[0]) {
									_label.callback(_label, Event::OnClicked, { mousepos.x - _inst.rect.a.x,mousepos.y - _inst.rect.a.y }, (int)Mouse::LeftButton);
									_label.pressed[0] = 0;
								}
							}
							if (rightreleased) {
								_label.callback(_label, Event::OnReleased, { mousepos.x - _inst.rect.a.x,mousepos.y - _inst.rect.a.y }, (int)Mouse::RightButton);
								if (_label.pressed[1]) {
									_label.callback(_label, Event::OnClicked, { mousepos.x - _inst.rect.a.x,mousepos.y - _inst.rect.a.y }, (int)Mouse::LeftButton);
									_label.pressed[1] = 0;
								}
							}
							if (middlereleased) {
								_label.callback(_label, Event::OnReleased, { mousepos.x - _inst.rect.a.x,mousepos.y - _inst.rect.a.y }, (int)Mouse::MiddleButton);
								if (_label.pressed[2]) {
									_label.callback(_label, Event::OnClicked, { mousepos.x - _inst.rect.a.x,mousepos.y - _inst.rect.a.y }, (int)Mouse::LeftButton);
									_label.pressed[2] = 0;
								}
							}
						}
						else {
							if (_label.mouseentered) {
								_label.callback(_label, Event::MouseLeave, { mousepos.x - _inst.rect.a.x,mousepos.y - _inst.rect.a.y }, 0);
								_label.mouseentered = 0;
								_label.pressed[0] = 0;
								_label.pressed[1] = 0;
								_label.pressed[2] = 0;
							}
						}
					}
					break;
				}
				case Type::Textbox: {
					Textbox& _textbox = *((Textbox*)&_inst);
					Rectangle<int> _ppos = _textbox.rect;

					bool _requestredraw = 0;

					if (Textbox::selecting) {
						if (Textbox::currentfocus == &_textbox) {
							Textbox::selectpos = _textbox.getPosition({ mousepos.x - _inst.rect.a.x - _textbox.padding.a.x + _textbox.xseek, mousepos.y - _inst.rect.a.y - _textbox.padding.a.y + _textbox.yseek });
							std::cout << Textbox::selectpos << " : SELECTING\n";
							std::cout << _textbox.position << " : POSITION\n";

							_requestredraw = 1;

							if (leftreleased) {
								if (Textbox::selectpos == _textbox.position) {
									Textbox::selectpos = -1;
								}
								Textbox::selecting = 0;
							}
						}
					}


					if (_textbox.tl.element != NULL) {
						if (((unsigned int)_textbox.tl.element) == Dock::Window) {
							switch (_textbox.tl.point) {
							case Dock::TopLeft: {
								if (!_textbox.tl.autopoint) {
									_textbox.rect.a.x = _textbox.tl.pos.x;
									_textbox.rect.a.y = _textbox.tl.pos.y;
								}
								else {
									_textbox.tl.pos.x = _ppos.a.x;
									_textbox.tl.pos.y = _ppos.a.y;
									_textbox.tl.autopoint = 0;
								}
								break;
							}
							case Dock::TopRight: {
								if (!_textbox.tl.autopoint) {
									_textbox.rect.a.x = width + _textbox.tl.pos.x;
									_textbox.rect.a.y = _textbox.tl.pos.y;
								}
								else {
									_textbox.tl.pos.x = _ppos.a.x - width;
									_textbox.tl.pos.y = _ppos.a.y;
									_textbox.tl.autopoint = 0;
								}
								break;
							}
							case Dock::BottomLeft: {
								if (!_textbox.tl.autopoint) {
									_textbox.rect.a.x = _textbox.tl.pos.x;
									_textbox.rect.a.y = height + _textbox.tl.pos.y;
								}
								else {
									_textbox.tl.pos.x = _ppos.a.x;
									_textbox.tl.pos.y = _ppos.a.y - height;
									_textbox.tl.autopoint = 0;
								}
								break;
							}
							case Dock::BottomRight: {
								if (!_textbox.tl.autopoint) {
									_textbox.rect.a.x = width + _textbox.tl.pos.x;
									_textbox.rect.a.y = height + _textbox.tl.pos.y;
								}
								else {
									_textbox.tl.pos.x = _ppos.a.x - width;
									_textbox.tl.pos.y = _ppos.a.y - height;
									_textbox.tl.autopoint = 0;
								}
								break;
							}
							case Dock::Left: {
								if (!_textbox.tl.autopoint) {
									_textbox.rect.a.x = _textbox.tl.pos.x;
								}
								else {
									_textbox.tl.pos.x = _ppos.a.x;
									_textbox.tl.autopoint = 0;
								}
								break;
							}
							case Dock::Right: {
								if (!_textbox.tl.autopoint) {
									_textbox.rect.a.x = width + _textbox.tl.pos.x;
								}
								else {
									_textbox.tl.pos.x = _ppos.a.x - width;
									_textbox.tl.autopoint = 0;
								}
								break;
							}
							case Dock::Top: {
								if (!_textbox.tl.autopoint) {
									_textbox.rect.a.y = height + _textbox.tl.pos.y;
								}
								else {
									_textbox.tl.pos.y = _ppos.a.y - height;
									_textbox.tl.autopoint = 0;
								}
								break;
							}
							case Dock::Bottom: {
								if (!_textbox.tl.autopoint) {
									_textbox.rect.a.y = height + _textbox.tl.pos.y;
								}
								else {
									_textbox.tl.pos.y = _ppos.a.y - height;
									_textbox.tl.autopoint = 0;
								}
								break;
							}
							}
						}
					}
					if (_textbox.tr.element != NULL) {
						if (((unsigned int)_textbox.tr.element) == Dock::Window) {
							switch (_textbox.tr.point) {
							case Dock::TopLeft: {
								if (!_textbox.tr.autopoint) {
									_textbox.rect.c.x = _textbox.tr.pos.x;
									_textbox.rect.a.y = _textbox.tr.pos.y;
								}
								else {
									_textbox.tr.pos.x = _ppos.c.x;
									_textbox.tr.pos.y = _ppos.a.y;
									_textbox.tr.autopoint = 0;
								}
								break;
							}
							case Dock::TopRight: {
								if (!_textbox.tr.autopoint) {
									_textbox.rect.c.x = width + _textbox.tr.pos.x;
									_textbox.rect.a.y = _textbox.tr.pos.y;
								}
								else {
									_textbox.tr.pos.x = _ppos.c.x - width;
									_textbox.tr.pos.y = _ppos.a.y;
									_textbox.tr.autopoint = 0;
								}
								break;
							}
							case Dock::BottomLeft: {
								if (!_textbox.tr.autopoint) {
									_textbox.rect.c.x = _textbox.tr.pos.x;
									_textbox.rect.a.y = height + _textbox.tr.pos.y;
								}
								else {
									_textbox.tr.pos.x = _ppos.a.x;
									_textbox.tr.pos.y = _ppos.c.y - height;
									_textbox.tr.autopoint = 0;
								}
								break;
							}
							case Dock::BottomRight: {
								if (!_textbox.tr.autopoint) {
									_textbox.rect.c.x = width + _textbox.tr.pos.x;
									_textbox.rect.a.y = height + _textbox.tr.pos.y;
								}
								else {
									_textbox.tr.pos.x = _ppos.c.x - width;
									_textbox.tr.pos.y = _ppos.a.y - height;
									_textbox.tr.autopoint = 0;
								}
								break;
							}
							case Dock::Left: {
								if (!_textbox.tr.autopoint) {
									_textbox.rect.c.x = _textbox.tr.pos.x;
								}
								else {
									_textbox.tr.pos.x = _ppos.c.x;
									_textbox.tr.autopoint = 0;
								}
								break;
							}
							case Dock::Right: {
								if (!_textbox.tr.autopoint) {
									_textbox.rect.c.x = width + _textbox.tr.pos.x;
								}
								else {
									_textbox.tr.pos.x = _ppos.c.x - width;
									_textbox.tr.autopoint = 0;
								}
								break;
							}
							case Dock::Top: {
								if (!_textbox.tr.autopoint) {
									_textbox.rect.a.y = height + _textbox.tr.pos.y;
								}
								else {
									_textbox.tr.pos.y = _ppos.a.y - height;
									_textbox.tr.autopoint = 0;
								}
								break;
							}
							case Dock::Bottom: {
								if (!_textbox.tr.autopoint) {
									_textbox.rect.a.y = height + _textbox.tr.pos.y;
								}
								else {
									_textbox.tr.pos.y = _ppos.a.y - height;
									_textbox.tr.autopoint = 0;
								}
								break;
							}
							}
						}
					}
					if (_textbox.bl.element != NULL) {
						if (((unsigned int)_textbox.bl.element) == Dock::Window) {
							switch (_textbox.bl.point) {
							case Dock::TopLeft: {
								if (!_textbox.bl.autopoint) {
									_textbox.rect.a.x = _textbox.bl.pos.x;
									_textbox.rect.c.y = _textbox.bl.pos.y;
								}
								else {
									_textbox.bl.pos.x = _ppos.a.x;
									_textbox.bl.pos.y = _ppos.c.y;
									_textbox.bl.autopoint = 0;
								}
								break;
							}
							case Dock::TopRight: {
								if (!_textbox.bl.autopoint) {
									_textbox.rect.a.x = width + _textbox.bl.pos.x;
									_textbox.rect.c.y = _textbox.bl.pos.y;
								}
								else {
									_textbox.bl.pos.x = _ppos.a.x - width;
									_textbox.bl.pos.y = _ppos.c.y;
									_textbox.bl.autopoint = 0;
								}
								break;
							}
							case Dock::BottomLeft: {
								if (!_textbox.bl.autopoint) {
									_textbox.rect.a.x = _textbox.bl.pos.x;
									_textbox.rect.c.y = height + _textbox.bl.pos.y;
								}
								else {
									_textbox.bl.pos.x = _ppos.a.x;
									_textbox.bl.pos.y = _ppos.c.y - height;
									_textbox.bl.autopoint = 0;
								}
								break;
							}
							case Dock::BottomRight: {
								if (!_textbox.bl.autopoint) {
									_textbox.rect.a.x = width + _textbox.bl.pos.x;
									_textbox.rect.c.y = height + _textbox.bl.pos.y;
								}
								else {
									_textbox.bl.pos.x = _ppos.a.x - width;
									_textbox.bl.pos.y = _ppos.c.y - height;
									_textbox.bl.autopoint = 0;
								}
								break;
							}
							case Dock::Left: {
								if (!_textbox.bl.autopoint) {
									_textbox.rect.a.x = _textbox.bl.pos.x;
								}
								else {
									_textbox.bl.pos.x = _ppos.a.x;
									_textbox.bl.autopoint = 0;
								}
								break;
							}
							case Dock::Right: {
								if (!_textbox.bl.autopoint) {
									_textbox.rect.a.x = width + _textbox.bl.pos.x;
								}
								else {
									_textbox.bl.pos.x = _ppos.a.x - width;
									_textbox.bl.autopoint = 0;
								}
								break;
							}
							case Dock::Top: {
								if (!_textbox.bl.autopoint) {
									_textbox.rect.c.y = height + _textbox.bl.pos.y;
								}
								else {
									_textbox.bl.pos.y = _ppos.c.y - height;
									_textbox.bl.autopoint = 0;
								}
								break;
							}
							case Dock::Bottom: {
								if (!_textbox.bl.autopoint) {
									_textbox.rect.c.y = height + _textbox.bl.pos.y;
								}
								else {
									_textbox.bl.pos.y = _ppos.c.y - height;
									_textbox.bl.autopoint = 0;
								}
								break;
							}
							}
						}
					}
					if (_textbox.br.element != NULL) {
						if (((unsigned int)_textbox.br.element) == Dock::Window) {
							switch (_textbox.br.point) {
							case Dock::TopLeft: {
								if (!_textbox.br.autopoint) {
									_textbox.rect.c.x = _textbox.br.pos.x;
									_textbox.rect.c.y = _textbox.br.pos.y;
								}
								else {
									_textbox.br.pos.x = _ppos.c.x;
									_textbox.br.pos.y = _ppos.c.y;
									_textbox.br.autopoint = 0;
								}
								break;
							}
							case Dock::TopRight: {
								if (!_textbox.br.autopoint) {
									_textbox.rect.c.x = width + _textbox.br.pos.x;
									_textbox.rect.c.y = _textbox.br.pos.y;
								}
								else {
									_textbox.br.pos.x = _ppos.c.x - width;
									_textbox.br.pos.y = _ppos.c.y;
									_textbox.br.autopoint = 0;
								}
								break;
							}
							case Dock::BottomLeft: {
								if (!_textbox.br.autopoint) {
									_textbox.rect.c.x = _textbox.br.pos.x;
									_textbox.rect.c.y = height + _textbox.br.pos.y;
								}
								else {
									_textbox.br.pos.x = _ppos.c.x;
									_textbox.br.pos.y = _ppos.c.y - height;
									_textbox.br.autopoint = 0;
								}
								break;
							}
							case Dock::BottomRight: {
								if (!_textbox.br.autopoint) {
									_textbox.rect.c.x = width + _textbox.br.pos.x;
									_textbox.rect.c.y = height + _textbox.br.pos.y;
								}
								else {
									_textbox.br.pos.x = _ppos.c.x - width;
									_textbox.br.pos.y = _ppos.c.y - height;
									_textbox.br.autopoint = 0;
								}
								break;
							}
							case Dock::Left: {
								if (!_textbox.br.autopoint) {
									_textbox.rect.c.x = _textbox.br.pos.x;
								}
								else {
									_textbox.br.pos.x = _ppos.c.x;
									_textbox.br.autopoint = 0;
								}
								break;
							}
							case Dock::Right: {
								if (!_textbox.br.autopoint) {
									_textbox.rect.c.x = width + _textbox.br.pos.x;
								}
								else {
									_textbox.br.pos.x = _ppos.c.x - width;
									_textbox.br.autopoint = 0;
								}
								break;
							}
							case Dock::Top: {
								if (!_textbox.br.autopoint) {
									_textbox.rect.c.y = height + _textbox.br.pos.y;
								}
								else {
									_textbox.br.pos.y = _ppos.c.y - height;
									_textbox.br.autopoint = 0;
								}
								break;
							}
							case Dock::Bottom: {
								if (!_textbox.br.autopoint) {
									_textbox.rect.c.y = height + _textbox.br.pos.y;
								}
								else {
									_textbox.br.pos.y = _ppos.c.y - height;
									_textbox.br.autopoint = 0;
								}
								break;
							}
							}
						}
					}
					
					if (_textbox.callback != NULL) {
						if (mousepos.x >= _textbox.rect.a.x &&
							mousepos.y >= _textbox.rect.a.y &&
							mousepos.x <= _textbox.rect.c.x &&
							mousepos.y <= _textbox.rect.c.y
							) {
							_textbox.callback(_textbox, Event::MouseOn, { mousepos.x - _inst.rect.a.x,mousepos.y - _inst.rect.a.y }, 0);//mouseentered
							if (!_textbox.mouseentered) {
								_textbox.callback(_textbox, Event::MouseEnter, { mousepos.x - _inst.rect.a.x,mousepos.y - _inst.rect.a.y }, 0);
								_textbox.mouseentered = 1;
							}
							if (leftpress) {
								_textbox.callback(_textbox, Event::OnClick, { mousepos.x - _inst.rect.a.x,mousepos.y - _inst.rect.a.y }, (int)Mouse::LeftButton);
							}
							if (rightpress) {
								_textbox.callback(_textbox, Event::OnClick, { mousepos.x - _inst.rect.a.x,mousepos.y - _inst.rect.a.y }, (int)Mouse::RightButton);
							}
							if (middlepress) {
								_textbox.callback(_textbox, Event::OnClick, { mousepos.x - _inst.rect.a.x,mousepos.y - _inst.rect.a.y }, (int)Mouse::MiddleButton);
							}
							if (leftpressed) {
								_textbox.callback(_textbox, Event::OnPressed, { mousepos.x - _inst.rect.a.x,mousepos.y - _inst.rect.a.y }, (int)Mouse::LeftButton);
								_textbox.pressed[0] = 1;

								_textbox.gainFocus();
								_textbox.position = _textbox.getPosition({ mousepos.x - _inst.rect.a.x - _textbox.padding.a.x + _textbox.xseek, mousepos.y - _inst.rect.a.y - _textbox.padding.a.y + _textbox.yseek });// << "\n";
								Textbox::textboxmarker = 1;

								Textbox::selectpos = -1;
								Textbox::selecting = 1;
								//std::cout << Textbox::selecting << '\n';
								_requestredraw = 1;
							}
							if (rightpressed) {
								_textbox.callback(_textbox, Event::OnPressed, { mousepos.x - _inst.rect.a.x,mousepos.y - _inst.rect.a.y }, (int)Mouse::RightButton);
								_textbox.pressed[1] = 1;
							}
							if (middlepressed) {
								_textbox.callback(_textbox, Event::OnPressed, { mousepos.x - _inst.rect.a.x,mousepos.y - _inst.rect.a.y }, (int)Mouse::MiddleButton);
								_textbox.pressed[2] = 1;
							}
							if (leftreleased) {
								_textbox.callback(_textbox, Event::OnReleased, { mousepos.x - _inst.rect.a.x,mousepos.y - _inst.rect.a.y }, (int)Mouse::LeftButton);
								if (_textbox.pressed[0]) {
									_textbox.callback(_textbox, Event::OnClicked, { mousepos.x - _inst.rect.a.x,mousepos.y - _inst.rect.a.y }, (int)Mouse::LeftButton);
									_textbox.pressed[0] = 0;
								}
							}
							if (rightreleased) {
								_textbox.callback(_textbox, Event::OnReleased, { mousepos.x - _inst.rect.a.x,mousepos.y - _inst.rect.a.y }, (int)Mouse::RightButton);
								if (_textbox.pressed[1]) {
									_textbox.callback(_textbox, Event::OnClicked, { mousepos.x - _inst.rect.a.x,mousepos.y - _inst.rect.a.y }, (int)Mouse::LeftButton);
									_textbox.pressed[1] = 0;
								}
							}
							if (middlereleased) {
								_textbox.callback(_textbox, Event::OnReleased, { mousepos.x - _inst.rect.a.x,mousepos.y - _inst.rect.a.y }, (int)Mouse::MiddleButton);
								if (_textbox.pressed[2]) {
									_textbox.callback(_textbox, Event::OnClicked, { mousepos.x - _inst.rect.a.x,mousepos.y - _inst.rect.a.y }, (int)Mouse::LeftButton);
									_textbox.pressed[2] = 0;
								}
							}
						}
						else {
							if (_textbox.mouseentered) {
								_textbox.callback(_textbox, Event::MouseLeave, { mousepos.x - _inst.rect.a.x,mousepos.y - _inst.rect.a.y }, 0);
								_textbox.mouseentered = 0;
								_textbox.pressed[0] = 0;
								_textbox.pressed[1] = 0;
								_textbox.pressed[2] = 0;
							}
						}
					}
					if (_requestredraw) {
						_textbox.redraw();
					}
					else {
						if (((_textbox.rect.c.x - _textbox.rect.a.x) != (_ppos.c.x - _ppos.a.x))
							|| ((_textbox.rect.c.x - _textbox.rect.a.x) != (_ppos.c.x - _ppos.a.x))) {
							_textbox.reset();
							_textbox.redraw();
						}
					}
					break;
				}
				}
			}
		}

		if (_pressonotherwidgets) {
			Textbox::killCurrentFocus();
		}

	}

	void Window::DrawAllWidgets() {
		using namespace KGui;
		using Event = KGui::Instance::Event;

		ElementManager& elementmanager = *((ElementManager*)this->elementmanager);

		int _size = elementmanager.getSize();
		//return pressed[(int)Tmousebutton] == 1
		int leftpress = GetAsyncKeyState((int)Mouse::LeftButton);
		int rightpress = GetAsyncKeyState((int)Mouse::RightButton);
		int middlepress = GetAsyncKeyState((int)Mouse::MiddleButton);
		int leftpressed = pressed[(int)Mouse::LeftButton] == 1;
		int rightpressed = pressed[(int)Mouse::RightButton] == 1;
		int middlepressed = pressed[(int)Mouse::MiddleButton] == 1;
		int leftreleased = pressed[(int)Mouse::LeftButton] == 3;
		int rightreleased = pressed[(int)Mouse::RightButton] == 3;
		int middlereleased = pressed[(int)Mouse::MiddleButton] == 3;

		if (leftpressed) {
			int lol = 0;
		}

		for (int i = 0;i < _size;i++) {
			mousepos = ViewMousePos();

			Element& _element = *(elementmanager[i]);

			if (_element.drawable) {
				Instance& _inst = *((Instance*)&_element);

				switch (_inst.type) {
				case Type::Button: {
					Button& _button = *((Button*)&_inst);
					Rectangle<int> _ppos = _button.rect;

					
				}
				}

				*this << _inst;
			}
		}
	}

	void Window::DrawAllWidgetSurfaces() {
		using namespace KGui;
		using Event = KGui::Instance::Event;

		ElementManager& elementmanager = *((ElementManager*)this->elementmanager);

		int _size = elementmanager.getSize();
		//return pressed[(int)Tmousebutton] == 1
		int leftpress = GetAsyncKeyState((int)Mouse::LeftButton);
		int rightpress = GetAsyncKeyState((int)Mouse::RightButton);
		int middlepress = GetAsyncKeyState((int)Mouse::MiddleButton);
		int leftpressed = pressed[(int)Mouse::LeftButton] == 1;
		int rightpressed = pressed[(int)Mouse::RightButton] == 1;
		int middlepressed = pressed[(int)Mouse::MiddleButton] == 1;
		int leftreleased = pressed[(int)Mouse::LeftButton] == 3;
		int rightreleased = pressed[(int)Mouse::RightButton] == 3;
		int middlereleased = pressed[(int)Mouse::MiddleButton] == 3;

		for (int i = 0;i < _size;i++) {
			mousepos = ViewMousePos();

			Element& _element = *(elementmanager[i]);

			if (!hglrc) {
				if (_element.drawable) {
					Instance& _inst = *((Instance*)&_element);

					switch (_inst.type) {
					case Type::Button: {
						Button& _button = *((Button*)&_inst);
						Rectangle<int> _ppos = _button.rect;

						break;
					}
					case Type::Label: {
						Label& _label = *((Label*)&_inst);
						Rectangle<int> _ppos = _label.rect;


						break;
					}
					case Type::Textbox: {
						Textbox& _textbox = *((Textbox*)&_inst);
						//if (Textbox::requestredrawall) {
						//	Textbox.
						//	_textbox.redraw();
						//}
						//else {
							if (Textbox::requestredrawall || _textbox.requestredraw) {
								_textbox.redraw();
								_textbox.requestredraw = 0;
							}
						//}

						break;
					}
					}

					renderer.blittransparent(*_inst.surface, _inst.rect.a.x, _inst.rect.a.y);
				}
			}
			else {
				if (_element.drawable) {
					Instance& _inst = *((Instance*)&_element);

					*this << Sprite(*_inst.surface, _inst.rect.a.x, _inst.rect.a.y);
				}
			}
		}

		Textbox::requestredrawall = 0;
	}

	int RegisterMessage(const char* Tname) {
		int _namesize = MultiByteToWideChar(CP_UTF8, 0, Tname, -1, NULL, 0);
		wchar_t* _name = new wchar_t[_namesize];
		memset(_name, 0, sizeof(wchar_t)*_namesize);
		MultiByteToWideChar(CP_UTF8, 0, Tname, -1, _name, _namesize);

		return RegisterWindowMessageW(_name);
	}
	int RegisterMessage(const wchar_t* Tname) {
		return RegisterWindowMessageW(Tname);
	}

	int PushMessage(Window& Twindow, int Tmessage) {
		return PostMessageW(Twindow.hwnd, Tmessage, 0, 0);
	}
}