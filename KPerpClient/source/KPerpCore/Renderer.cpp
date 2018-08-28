
#include <KPerpCore/Renderer.hpp>

#ifdef APIENTRY
#undef APIENTRY
#endif

#include <windows.h>

#include <KPerpCore/Error.hpp>

//#ifdef _WIN32
//	#undef APIENTRY
//#endif

#include <iostream>

#define _kp_userdefault ((int)0xEFFFFFFF)
//#define _break goto WinProcBreak;

namespace kp {
	WNDCLASSEXW winclass;

	const int lastestopengl = 46;

	int windowcount = 0;
	const wchar_t* winclassname = L"KPerpWindow";

	Renderer* currentrenderer;
	Renderer* fullscreen;

	LRESULT CALLBACK WinProc(HWND Thwnd, UINT Tmsg, WPARAM Twparam, LPARAM Tlparam) {
		Renderer* _renderer = (Renderer*)GetPropW(Thwnd, L"__KPerpRendererClass");
		Input* _input = (Input*)GetPropW(Thwnd, L"__KPerpRendererInput");
		void** _prop = (void**)GetPropW(Thwnd, L"__KPerpRendererProp");
		if (_renderer != NULL) {
			switch (Tmsg) {
			case WM_CLOSE: {
				//_renderer->putEvent(Event::Close);
				break;
			}
			case WM_DESTROY: {
				PostQuitMessage(0);
				break;
			}
			case WM_SETFOCUS: {
				_renderer->putEvent(Event::KeyDown);
				break;
			}

			case WM_KEYDOWN: {
				//GetKeyboardState(input->keys);
				_renderer->putEvent(Event::KeyDown);
				break;
			}
			case WM_KEYUP: {
				//GetKeyboardState(input->keys);
				_renderer->putEvent(Event::KeyUp);
				break;
			}
			case WM_SYSKEYDOWN: {
				//GetKeyboardState(input->keys);
				_renderer->putEvent(Event::GlobalKeyDown);
				break;
			}
			case WM_SYSKEYUP: {
				//GetKeyboardState(input->keys);
				_renderer->putEvent(Event::GlobalKeyUp);
				break;
			}

			case WM_MOUSEWHEEL: {
				*(short*)(_prop[1]) = HIWORD(Twparam);
				_renderer->putEvent(Event::MouseWheelMoved);
				break;
			}

			case WM_MOUSEMOVE: {
				break;
			}

			case WM_MOUSELEAVE: {
				break;
			}
			case WM_SIZE: {
				//std::cout << "SIZE";
				if (*(bool*)(_prop[7]) == 0) {
					if (*(int*)(_prop[6]) == 1) {
						if (Twparam == SIZE_RESTORED) {
							_renderer->putEvent(Event::WindowRestored);
						}
						if (Twparam == SIZE_MAXIMIZED) {
							_renderer->putEvent(Event::WindowMaximized);
						}
					}
					else {
						if (*(int*)(_prop[6]) == 2) {
							if (Twparam == SIZE_RESTORED) {
								_renderer->putEvent(Event::WindowRestored);
							}
							if (Twparam == SIZE_MINIMIZED) {
								_renderer->putEvent(Event::WindowMinimized);
							}
						}
						if (Twparam == SIZE_MINIMIZED) {
							_renderer->putEvent(Event::WindowMinimized);
						}
						if (Twparam == SIZE_MAXIMIZED) {
							_renderer->putEvent(Event::WindowMaximized);
						}
					}

					if (Twparam == SIZE_MINIMIZED || Twparam == SIZE_RESTORED || Twparam == SIZE_MAXIMIZED) {
						if (Twparam == SIZE_RESTORED || Twparam == SIZE_MAXIMIZED) {
							_renderer->putEvent(Event::WindowNonMinimizedChange);
						}
						_renderer->putEvent(Event::WindowSizeChanged);
						_renderer->putEvent(Event::WindowChanged);
					}

					//RECT _winrect;
					//GetWindowRect(Thwnd, &_winrect);
					//ClipCursor(&_winrect);


				}
				RECT _winrect;
				GetWindowRect(Thwnd, &_winrect);
				if (((*(Rectangle<long>*)(_prop[0])).c.x) - ((*(Rectangle<long>*)(_prop[0])).a.x) == (_winrect.right - _winrect.left) &&
					((*(Rectangle<long>*)(_prop[0])).c.y) - ((*(Rectangle<long>*)(_prop[0])).a.y) == (_winrect.bottom - _winrect.top)) {
					_renderer->putEvent(Event::WindowMoving);
				}
				else {
					_renderer->putEvent(Event::WindowChangingSize);
				}
				(*(Rectangle<long>*)(_prop[0])).a.x = _winrect.left;
				(*(Rectangle<long>*)(_prop[0])).a.y = _winrect.top;
				(*(Rectangle<long>*)(_prop[0])).c.x = _winrect.right;
				(*(Rectangle<long>*)(_prop[0])).c.y = _winrect.bottom;

				GetClientRect(Thwnd, &_winrect);

				(*(long*)(_prop[4])) = (_winrect.right - _winrect.left);
				(*(long*)(_prop[5])) = (_winrect.bottom - _winrect.top);
				(*(long*)(_prop[8])) = (*(int*)(_prop[4]));
				(*(long*)(_prop[9])) = (*(int*)(_prop[5]));
				break;
			}
			case WM_ENTERSIZEMOVE: {
				RECT _winrect;
				GetWindowRect(Thwnd, &_winrect);
				((*(Point<long>*)(_prop[10]))) = { (_winrect.right - _winrect.left) ,(_winrect.bottom - _winrect.top) };
				//std::cout << "ENTER";
				*(bool*)(_prop[7]) = 1;
				ClipCursor(NULL);
				break;
			}
			case WM_EXITSIZEMOVE: {
				//std::cout << "EXIT";
				if (Twparam != SIZE_MINIMIZED) {
					RECT _winrect;
					GetWindowRect(Thwnd, &_winrect);
					if ((*(Point<long>*)(_prop[10])).x == (_winrect.right - _winrect.left) &&
						(*(Point<long>*)(_prop[10])).y == (_winrect.bottom - _winrect.top)) {
						_renderer->putEvent(Event::WindowMoved);
						//_renderer->putEvent(Event::WindowChanged);
					}
					else {
						_renderer->putEvent(Event::WindowSizeChanged);
						//_renderer->putEvent(Event::WindowChanged);
					}
					(*(Rectangle<long>*)(_prop[0])).a.x = _winrect.left;
					(*(Rectangle<long>*)(_prop[0])).a.y = _winrect.top;
					(*(Rectangle<long>*)(_prop[0])).c.x = _winrect.right;
					(*(Rectangle<long>*)(_prop[0])).c.y = _winrect.bottom;

					GetClientRect(Thwnd, &_winrect);

					(*(long*)(_prop[4])) = (_winrect.right - _winrect.left);
					(*(long*)(_prop[5])) = (_winrect.bottom - _winrect.top);
					(*(long*)(_prop[8])) = (*(int*)(_prop[4]));
					(*(long*)(_prop[9])) = (*(int*)(_prop[5]));
				}
				//RECT _winrect;
				//GetWindowRect(Thwnd, &_winrect);
				//ClipCursor(&_winrect);
				*(bool*)(_prop[7]) = 0;
				_renderer->putEvent(Event::WindowChanged);
				break;
			}

			default: {
				return DefWindowProc(Thwnd, Tmsg, Twparam, Tlparam);
			}
			}
		}

		//WinProcBreak:

		return DefWindowProc(Thwnd, Tmsg, Twparam, Tlparam);
	}

	bool winclassregistered = 0;
	bool RegisterWindowClass() {
		if (winclassregistered == 0) {

			memset(&winclass, 0, sizeof(winclass));
			winclass.cbSize = sizeof(WNDCLASSEXW);
			winclass.lpfnWndProc = (WNDPROC)(WinProc);
			winclass.hInstance = GetModuleHandleW(NULL);
			winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
			winclass.lpszClassName = winclassname;
			winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
			winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

			if (!RegisterClassExW((WNDCLASSEXW*)&winclass)) {
				int _winlasterror = GetLastError();
				if (_winlasterror == 1410) {
					setLastError(Error::WinClassRegisterFailedBecauseItsAlreadyExists);
				}
				else {
					setLastError(Error::WinClassRegisterFailed);
				}

				return 0;
			}

			winclassregistered = 1;
			return 1;
		}
		return 0;
	}
	bool UnregisterWindowClass() {
		if (!UnregisterClassW(winclassname, GetModuleHandleW(NULL))) {
			return 0;
		}

		winclassregistered = 0;
		return 1;
	}

	Input::Input() {

	}
	Input::~Input() {

	}

	Renderer::Renderer() {

	}

	Renderer::Renderer(int Tw, int Th) {
		// Software
		running = create_software(Tw, Th);
	}
	Renderer::Renderer(int Topengl, int Tw, int Th) {
		if (Topengl < 1 || Topengl > lastestopengl) {
			if (Topengl > lastestopengl) {
				// No OpenGL version higher than 4.6
				setLastError(Error::InvalidOpenGL);
			}
			if (Topengl < 1) {
				// Software
				running = create_software(Tw, Th);
			}
		}
		else {
			// OpenGL
			running = create_opengl(_kp_userdefault, _kp_userdefault, Topengl, Tw, Th, "", WindowStyle::OverlappedWindow);
		}
	}

	void Renderer::Destroy() {
		// Software
		if (buffer != NULL && hbmp == NULL) {
			delete[] buffer;
			buffer = NULL;
		}
		// Software + Window
		if (hbmp != NULL) {
			DeleteObject(hbmp); // Delete HandleBitmap will also delete surface
			hbmp = NULL;
		}
		// OpenGL
		if (hglrc != NULL) {
			glDeleteVertexArrays(1, &linevao);
			glDeleteBuffers(1, &linevbo);
			glDeleteBuffers(1, &lineebo);

			glDeleteVertexArrays(1, &trianglevao);
			glDeleteBuffers(1, &trianglevbo);
			glDeleteBuffers(1, &triangleebo);

			glDeleteVertexArrays(1, &rectvao);
			glDeleteBuffers(1, &rectvbo);
			glDeleteBuffers(1, &rectebo);

			glDeleteFramebuffers(1, &tframebuffer);

			wglMakeCurrent(NULL, NULL);
			wglDeleteContext((HGLRC)hglrc);
		}
		// Window
		if (hwnd != NULL) {
			if (fullscreen == this) {
				leavefullscreen(WindowStyle::OverlappedWindow);
			}
			if (chdc != NULL) {
				DeleteDC(chdc);
			}
			if (hdc != NULL) {
				ReleaseDC(hwnd, hdc);
			}
			if (IsWindow(hwnd)) {
				DestroyWindow(hwnd);
				hwnd = NULL;
				windowcount--;
			}
		}

		if (windowcount == 0) {
			UnregisterWindowClass();
		}

		if (view != NULL) {
			delete view;
			view = NULL;
		}
		if (defview != NULL) {
			delete defview;
			defview = NULL;
		}

		running = 0;
	}

	void Renderer::Update() {
		if (opengl >= 1 && hdc != NULL) {
			::SwapBuffers(hdc);
		}
		else {
			if (hdc != NULL) {
				BitBlt(hdc, 0, 0, width, height, chdc, 0, 0, SRCCOPY);
			}
		}
	}

	void Renderer::makeCurrent() {
		if (hdc != NULL && hglrc != NULL) {
			wglMakeCurrent(hdc, hglrc);
			currentrenderer = this;
		}
	}

	Event Renderer::getEvent() {
		return Event::None;
	}
	Event Renderer::waitEvent() {
		return Event::None;
	}
	Event Renderer::putEvent(Event Tevent) {
		return Event::None;
	}
	Event Renderer::popEvent() {
		return Event::None;
	}

	int Renderer::keyPressed(Key Tkey) {
		return 0;
	}
	int Renderer::keyPressed(unsigned char Tkey) {
		return 0;
	}

	int Renderer::mousePressed(Mouse Tmousebutton) {
		return 0;
	}
	short Renderer::MouseWheel() {
		return mousewheeldelta;
	}

	Point<long> Renderer::MousePos() {
		POINT _mousepos;
		GetCursorPos(&_mousepos);
		ScreenToClient(hwnd, &_mousepos);

		return *((Point<long>*)&_mousepos);
	}

	Point<long> Renderer::WindowSize() {
		Point<long> _point;
		_point.x = rect.c.x - rect.a.x;
		_point.y = rect.c.y - rect.c.y;
		return _point;
	}

	Point<long> Renderer::ClientSize() {
		Point<long> _point;
		_point.x = width;
		_point.y = height;
		return _point;
	}

	void Renderer::EnableBlending(BlendFactor TSourceFac, BlendFactor TDestFac) {
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

	void Renderer::DisableBlending() {
		glDisable(GL_BLEND);
	}

	void Renderer::setTarget(Texture& Ttex) {
		glBindFramebuffer(GL_FRAMEBUFFER, tframebuffer);
		Ttex._makeframebuffer();
		glViewport(0, 0, Ttex.getSize().x, Ttex.getSize().y);

		renderwidth = Ttex.getSize().x;
		renderheight = Ttex.getSize().y;

		targettexture = &Ttex;
	}
	void Renderer::setTarget(const View& Tview) {
		if (targettexture != NULL) {
			resetTarget();
		}

		glViewport(Tview.port.a.x, (height - (Tview.port.c.y)), Tview.port.c.x - Tview.port.a.x, Tview.port.c.y);

		renderwidth = Tview.port.c.x - Tview.port.a.x;
		renderheight = Tview.port.c.y - Tview.port.a.y;

		*view = Tview;
		
		if (useview) {
			viewmatrix = Ortho(Tview.view);
		}
		//viewmatrix = Scale(viewmatrix, Vec4(Tview.zoom.x, Tview.zoom.y, 1, 1));
		//viewmatrix = Matrix<float, 4, 4>();
		//viewmatrix = Translate(viewmatrix, Vec3(10, 10, 0));
		//Matrix<float, 4, 4> _viewmatrix = Translate(Matrix<float, 4, 4>(), Vec3(1, 1, 0));
		
		//viewmatrix = viewmatrix * _viewmatrix;
		transmatrix = Matrix<float, 4, 4>();
		transmatrix = Scale(transmatrix, Vec4(Tview.zoom.x, Tview.zoom.y, 1, 1));
		transmatrix = Rotate(transmatrix, radians_const(Tview.angle), Vec3(0, 0, 1));

		if (hglrc != NULL) {
			shader.setUniform(viewmatrixlocation, viewmatrix);
			shader.setUniform(transmatrixlocation, transmatrix);
			if (cshader != NULL) {
				cshader->setUniform(shaderviewmatrixlocation, viewmatrix);
				cshader->setUniform(shadertransmatrixlocation, transmatrix);
			}
		}

		//targettexture = &Ttex;
	}
	void Renderer::resetTarget() {
		if (targettexture != NULL) {
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glViewport(0, 0, width, height);

			renderwidth = width;
			renderheight = height;

			targettexture = NULL;

			restoreView();

			return;
		}
		if (targettexture == NULL) {
			glViewport(defview->port.a.x, defview->port.a.y, defview->port.c.x, defview->port.c.y);

			renderwidth = defview->port.c.x - defview->port.a.x;
			renderheight = defview->port.c.y - defview->port.a.y;

			*view = *defview;
			if (useview) {
				viewmatrix = Ortho(view->view);
			}
			//viewmatrix = Scale(viewmatrix, Vec4(Tview.zoom.x, Tview.zoom.y, 1, 1));
			//viewmatrix = Matrix<float, 4, 4>();
			//viewmatrix = Translate(viewmatrix, Vec3(10, 10, 0));
			//Matrix<float, 4, 4> _viewmatrix = Translate(Matrix<float, 4, 4>(), Vec3(1, 1, 0));
			//viewmatrix = Rotate(viewmatrix, radians_const(Tview.angle), Vec3(0, 0, 1));
			//viewmatrix = viewmatrix * _viewmatrix;

			if (hglrc != NULL) {
				shader.setUniform(viewmatrixlocation, viewmatrix);
				shader.setUniform(transmatrixlocation, transmatrix);
				if (cshader != NULL) {
					cshader->setUniform(shaderviewmatrixlocation, viewmatrix);
					cshader->setUniform(shadertransmatrixlocation, transmatrix);
				}
			}
		}
	}

	void Renderer::restoreView() {
		view->view = {
			0,
			0,
			(float)width,
			(float)height
		};
		view->port = {
			0,
			0,
			(float)width,
			(float)height
		};

		glViewport(view->port.a.x, view->port.a.y, view->port.c.x, view->port.c.y);

		renderwidth = view->port.c.x - view->port.a.x;
		renderheight = view->port.c.y - view->port.a.y;

		if (useview) {
			viewmatrix = Ortho(view->view);
		}
		//viewmatrix = Scale(viewmatrix, Vec4(Tview.zoom.x, Tview.zoom.y, 1, 1));
		//viewmatrix = Matrix<float, 4, 4>();
		//viewmatrix = Translate(viewmatrix, Vec3(10, 10, 0));
		//Matrix<float, 4, 4> _viewmatrix = Translate(Matrix<float, 4, 4>(), Vec3(1, 1, 0));
		//viewmatrix = Rotate(viewmatrix, radians_const(Tview.angle), Vec3(0, 0, 1));
		//viewmatrix = viewmatrix * _viewmatrix;

		if (hglrc != NULL) {
			shader.setUniform(viewmatrixlocation, viewmatrix);
			shader.setUniform(transmatrixlocation, transmatrix);
			if (cshader != NULL) {
				cshader->setUniform(shaderviewmatrixlocation, viewmatrix);
				cshader->setUniform(shadertransmatrixlocation, transmatrix);
			}
		}
	}
	void Renderer::updateView() {
		glViewport(view->port.a.x, view->port.a.y, view->port.c.x, view->port.c.y);

		renderwidth = view->port.c.x - view->port.a.x;
		renderheight = view->port.c.y - view->port.a.y;

		if (useview) {
			viewmatrix = Ortho(view->view);
		}
		//viewmatrix = Scale(viewmatrix, Vec4(Tview.zoom.x, Tview.zoom.y, 1, 1));
		//viewmatrix = Matrix<float, 4, 4>();
		//viewmatrix = Translate(viewmatrix, Vec3(10, 10, 0));
		//Matrix<float, 4, 4> _viewmatrix = Translate(Matrix<float, 4, 4>(), Vec3(1, 1, 0));
		//viewmatrix = Rotate(viewmatrix, radians_const(Tview.angle), Vec3(0, 0, 1));
		//viewmatrix = viewmatrix * _viewmatrix;

		if (hglrc != NULL) {
			shader.setUniform(viewmatrixlocation, viewmatrix);
			shader.setUniform(transmatrixlocation, transmatrix);
			if (cshader != NULL) {
				cshader->setUniform(shaderviewmatrixlocation, viewmatrix);
				cshader->setUniform(shadertransmatrixlocation, transmatrix);
			}
		}
	}
	void Renderer::updateViewPosition() {
		//View _view;
		view->port = {
			0,
			0,
			(float)width,
			(float)height
		};

		glViewport(view->port.a.x, height - view->port.c.y, view->port.c.x, view->port.c.y);

		renderwidth = view->port.c.x - view->port.a.x;
		renderheight = view->port.c.y - view->port.a.y;
	}

	void Renderer::useView(bool Tuse) {
		useview = Tuse;
		if (!useview) {
			viewmatrix = Matrix<float, 4, 4>();
			shader.setUniform(viewmatrixlocation, viewmatrix);
			if (cshader != NULL) {
				cshader->setUniform(shadermatrixlocation, matrix);
			}
		}
		else {
			updateView();
		}
	}

	Matrix<float, 4, 4> Renderer::GetMatrix() {
		return matrix;
	}
	Matrix<float, 4, 4> Renderer::GetViewMatrix() {
		return viewmatrix;
	}
	Matrix<float, 4, 4> Renderer::GetTransformMatrix() {
		return transmatrix;
	}
	void Renderer::UseShader(OpenGL::Shader& Tshader, unsigned int Tmatrixloc, unsigned int Tviewmatrixloc, unsigned int Ttransmatrixloc) {
		shadermatrixlocation = Tmatrixloc;
		shaderviewmatrixlocation = Tviewmatrixloc;
		shadertransmatrixlocation = Ttransmatrixloc;

		Tshader.Use();

		Tshader.setUniform(shadermatrixlocation, matrix);
		Tshader.setUniform(shaderviewmatrixlocation, viewmatrix);
		Tshader.setUniform(shadertransmatrixlocation, transmatrix);

		cshader = &Tshader;
	}

	Renderer::~Renderer() {
		// Software
		if (buffer != NULL && hbmp == NULL) {
			delete[] buffer;
			buffer = NULL;
		}
		// Software + Window
		if (hbmp != NULL) {
			DeleteObject(hbmp); // Delete HandleBitmap will also delete surface
			hbmp = NULL;
		}
		// OpenGL
		if (hglrc != NULL) {
			glDeleteVertexArrays(1, &linevao);
			glDeleteBuffers(1, &linevbo);
			glDeleteBuffers(1, &lineebo);

			glDeleteVertexArrays(1, &trianglevao);
			glDeleteBuffers(1, &trianglevbo);
			glDeleteBuffers(1, &triangleebo);

			glDeleteVertexArrays(1, &rectvao);
			glDeleteBuffers(1, &rectvbo);
			glDeleteBuffers(1, &rectebo);

			glDeleteFramebuffers(1, &tframebuffer);

			wglMakeCurrent(NULL, NULL);
			wglDeleteContext((HGLRC)hglrc);
		}
		// Window
		if (hwnd != NULL) {
			if (fullscreen == this) {
				leavefullscreen(WindowStyle::OverlappedWindow);
			}
			if (chdc != NULL) {
				DeleteDC(chdc);
			}
			if (hdc != NULL) {
				ReleaseDC(hwnd, hdc);
			}
			if (IsWindow(hwnd)) {
				DestroyWindow(hwnd);
				hwnd = NULL;
				windowcount--;
			}
		}

		if (windowcount == 0) {
			UnregisterWindowClass();
		}

		if (view != NULL) {
			delete view;
			view = NULL;
		}
		if (defview != NULL) {
			delete defview;
			defview = NULL;
		}

		running = 0;
	}

	typedef void(*_GLADproc)();
	//Convert from __stdcall to _cdecl
	_GLADproc _GetProcAddress(const char* Tname) {
		_GLADproc proc = (_GLADproc)wglGetProcAddress(Tname);

		if (proc != NULL) {
			return proc;
		}

		HINSTANCE _opengllib;
		_opengllib = LoadLibraryA("opengl32.dll");
		proc = (_GLADproc)GetProcAddress(_opengllib, Tname);
		FreeLibrary(_opengllib);
		if (strcmp(Tname, "glClear") == 0) {
			return proc;
		}

		if (proc != NULL) {
			return proc;
		}
		return proc;
	}

	void Renderer::vao_init() {
		beginvertex = 0;

		// (x, y, z, r, g, b, a, s, t) * 2

		glGenVertexArrays(1, &linevao);
		glGenBuffers(1, &linevbo);
		glGenBuffers(1, &lineebo);

		glBindVertexArray(linevao);
		glBindBuffer(GL_ARRAY_BUFFER, linevbo);

		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 18, NULL, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lineebo);

		unsigned int _indices_line[] = {
			0, 1
		};

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices_line), _indices_line, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void*)(0 * sizeof(float)));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void*)(7 * sizeof(float)));
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		// (x, y, z, r, g, b, a, s, t) * 3

		glGenVertexArrays(1, &trianglevao);
		glGenBuffers(1, &trianglevbo);
		glGenBuffers(1, &triangleebo);

		glBindVertexArray(trianglevao);
		glBindBuffer(GL_ARRAY_BUFFER, trianglevbo);

		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 27, NULL, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangleebo);

		unsigned int _indices_triangle[] = {
			0, 1, 2
		};

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices_triangle), _indices_triangle, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void*)(0 * sizeof(float)));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void*)(7 * sizeof(float)));
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		// (x, y, z, r, g, b, a, s, t) * 4

		glGenVertexArrays(1, &rectvao);
		glGenBuffers(1, &rectvbo);
		glGenBuffers(1, &rectebo);

		glBindVertexArray(rectvao);
		glBindBuffer(GL_ARRAY_BUFFER, rectvbo);

		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 36, NULL, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rectebo);

		unsigned int _indices_rect[] = {
			0, 1, 2,
			1, 2, 3
		};

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices_rect), _indices_rect, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void*)(0 * sizeof(float)));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void*)(7 * sizeof(float)));
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		// (x, y, z, r, g, b, a, s, t) * ...

		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);

		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void*)(0 * sizeof(float)));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void*)(7 * sizeof(float)));
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void Renderer::shader_init() {
		using namespace OpenGL;

		shader.Create(NULL, NULL);

		shader.Begin(Shader::Vertex, 1);

		shader += "#version 330 core";
		shader << "layout (location = 0) in vec3 _kp_Pos;";
		shader << "layout (location = 1) in vec4 _kp_Color;";
		shader << "layout (location = 2) in vec2 _kp_TexCoord;";
		shader << "out vec2 _kp_outTexCoord;";
		shader << "out vec4 _kp_outColor;";
		shader << "uniform mat4 _kp_matrix;";
		shader << "uniform mat4 _kp_view;";
		shader << "uniform mat4 _kp_transview;";
		shader << "void main() {";
		shader << "    gl_Position = _kp_transview * _kp_view * _kp_matrix * vec4(_kp_Pos.x, _kp_Pos.y, _kp_Pos.z, 1.0);";
		shader << "    _kp_outTexCoord = _kp_TexCoord;";
		shader << "    _kp_outColor = _kp_Color;";
		shader << "}";


		shader.Submit();

		shader.End();

		shader.Begin(Shader::Fragment, 1);

		shader += "#version 330 core";
		shader << "out vec4 FragColor;";
		shader << "in vec2 _kp_outTexCoord;";
		shader << "in vec4 _kp_outColor;";
		shader << "uniform sampler2D _kp_Tex;";
		shader << "void main() {";
		shader << "    FragColor = texture(_kp_Tex,_kp_outTexCoord) * _kp_outColor;";// 
		shader << "}";

		shader.Submit();

		shader.End();

		shader.Compile();

		moderntext_shader.Create(NULL, NULL);

		moderntext_shader.Begin(Shader::Vertex, 1);

		moderntext_shader += "#version 330 core";
		moderntext_shader << "layout (location = 0) in vec3 _kp_Pos;";
		moderntext_shader << "layout (location = 1) in vec4 _kp_Color;";
		moderntext_shader << "layout (location = 2) in vec2 _kp_TexCoord;";
		moderntext_shader << "out vec2 _kp_outTexCoord;";
		moderntext_shader << "out vec4 _kp_outColor;";
		moderntext_shader << "uniform mat4 _kp_matrix;";
		moderntext_shader << "uniform mat4 _kp_view;";
		moderntext_shader << "uniform mat4 _kp_transview;";
		moderntext_shader << "void main() {";
		moderntext_shader << "    gl_Position = _kp_transview * _kp_view * _kp_matrix * vec4(_kp_Pos.x, _kp_Pos.y, _kp_Pos.z, 1.0);";
		moderntext_shader << "    _kp_outTexCoord = _kp_TexCoord;";
		moderntext_shader << "    _kp_outColor = _kp_Color;";
		moderntext_shader << "}";

		moderntext_shader.Submit();

		moderntext_shader.End();


		moderntext_shader.Begin(Shader::Fragment, 1);

		moderntext_shader += "#version 330 core";

		/*moderntext_shader << "in vec2 _kp_outTexCoord;";
		moderntext_shader << "out vec4 color;";

		moderntext_shader << "uniform sampler2D text;";
		moderntext_shader << "uniform vec4 textColor;";

		moderntext_shader << "void main()";
		moderntext_shader << "{";
		moderntext_shader << "	vec4 sampled = vec4(0,0,1,1);//vec4(1.0, 1.0, 1.0, texture(text, _kp_outTexCoord).r);";
		moderntext_shader << "	FragColor = textColor * sampled;";
		moderntext_shader << "}";*/

		moderntext_shader << "out vec4 FragColor;";
		moderntext_shader << "in vec2 _kp_outTexCoord;";
		moderntext_shader << "in vec4 _kp_outColor;";
		moderntext_shader << "uniform sampler2D _kp_Tex;";
		moderntext_shader << "void main() {";
		moderntext_shader << "    FragColor = vec4(1,1,1,texture(_kp_Tex,_kp_outTexCoord).r) * _kp_outColor;";// 
		moderntext_shader << "}";

		moderntext_shader.Submit();

		moderntext_shader.End();

		moderntext_shader.Compile();

		modernmatrixlocation = moderntext_shader.getLocation("_kp_matrix");
		modernviewmatrixlocation = moderntext_shader.getLocation("_kp_view");
		moderntransmatrixlocation = moderntext_shader.getLocation("_kp_transview");

		shader.Use();

		LoadIdentity();
	}

	void Renderer::color_tex_init() {
		glGenTextures(1, &white);
		glGenTextures(1, &black);

		unsigned int _white = 0xFFFFFFFF;
		unsigned int _black = 0x00000000;

		glBindTexture(GL_TEXTURE_2D, white);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &_white);

		glBindTexture(GL_TEXTURE_2D, black);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &_black);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	bool Renderer::create_software(int Tw, int Th) {
		if (Tw*Th < 1) {
			setLastError(Error::InvalidSurfaceSize);
			return 0;
		}

		rect.a.x = 0;
		rect.a.y = 0;
		rect.c.x = Tw;
		rect.c.y = Th;

		width = Tw;
		height = Th;

		buffer = new unsigned int[Tw*Th];
		return 1;
	}

	void Renderer::framebuffer_init() {
		glGenFramebuffers(1, &tframebuffer);
	}

	void Renderer::view_init() {
		viewmatrix = Matrix<float, 4, 4>();
		if (hglrc != NULL) {
			shader.setUniform("_kp_view", viewmatrix);
			matrixlocation = shader.getLocation("_kp_matrix");
			viewmatrixlocation = shader.getLocation("_kp_view");
			transmatrixlocation = shader.getLocation("_kp_transview");
			//shader.setUniform("transview", transview);
		}
		restoreView();
	}

	bool Renderer::create_software_window(int Tx, int Ty, int Tw, int Th, const char* Ttext, WindowStyle Twinstyle) {
		if (Tw*Th < 1) {
			setLastError(Error::InvalidWindowSize);
			return 0;
		}

		RegisterWindowClass();

		rect.a.x = 0;
		rect.a.y = 0;
		rect.c.x = Tw;
		rect.c.y = Th;

		width = Tw;
		height = Th;

		style = Twinstyle;

		memset(&bmpinfo, 0, sizeof(bmpinfo));
		((BITMAPINFO*)(&bmpinfo))->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		((BITMAPINFO*)(&bmpinfo))->bmiHeader.biWidth = Tw;
		((BITMAPINFO*)(&bmpinfo))->bmiHeader.biHeight = -Th; // Set it negative for flip image vertically 
		((BITMAPINFO*)(&bmpinfo))->bmiHeader.biPlanes = 1;
		((BITMAPINFO*)(&bmpinfo))->bmiHeader.biBitCount = 32;
		((BITMAPINFO*)(&bmpinfo))->bmiHeader.biCompression = BI_RGB;

		hbmp = CreateDIBSection(GetDC(0), ((BITMAPINFO*)&bmpinfo), DIB_RGB_COLORS, (void**)&buffer, 0, 0);

		if (hbmp == NULL) {
			setLastError(Error::DIBSectionCreationFailed);
			return 0;
		}

		RECT _winfull = { 0,0,Tw,Th };
		AdjustWindowRectEx(&_winfull, (unsigned long)Twinstyle, 0, 0);

		RECT _desktoprect;

		GetWindowRect(GetDesktopWindow(), &_desktoprect);

		int _winx = (Tx == _kp_userdefault ? CW_USEDEFAULT : (Tx < (-_desktoprect.right) ? (-_desktoprect.right) + 1 : (Tx >(_desktoprect.right) ? (_desktoprect.right - 1) : Tx)));
		int _winy = (Ty == _kp_userdefault ? CW_USEDEFAULT : (Ty < (-_desktoprect.bottom) ? (-_desktoprect.bottom) + 1 : (Ty >(_desktoprect.right) ? (_desktoprect.bottom - 1) : Ty)));

		hwnd = CreateWindowExW(0, winclassname, (wchar_t*)Ttext, (unsigned long)Twinstyle, 0, 0, 300, 300, NULL, NULL, GetModuleHandleW(NULL), NULL);

		if (hwnd == NULL) {
			setLastError(Error::WindowCreationFailed);
			return 0;
		}

		if (Twinstyle == WindowStyle::FullScreen) {
			enterfullscreen(width, height);
			Twinstyle = WindowStyle::Popup;
		}

		RECT _winrect;
		RECT _winclirect;

		GetWindowRect(hwnd, &_winrect);
		GetClientRect(hwnd, &_winclirect);

		SetWindowPos(hwnd, HWND_NOTOPMOST, _winrect.left, _winrect.top, _winrect.right - _winrect.left, _winrect.bottom - _winrect.top, SWP_SHOWWINDOW);

		GetWindowRect(hwnd, &_winrect);
		GetClientRect(hwnd, &_winclirect);

		rect.a.x = _winrect.left;
		rect.a.y = _winrect.top;
		rect.c.x = _winrect.right;
		rect.c.y = _winrect.bottom;

		clientrect.a.x = _winclirect.left;
		clientrect.a.y = _winclirect.top;
		clientrect.c.x = _winclirect.right;
		clientrect.c.y = _winclirect.bottom;

		SetPropW(hwnd, L"__KPerpRendererClass", this);
		SetPropW(hwnd, L"__KPerpRendererInput", &input);
		SetPropW(hwnd, L"__KPerpRendererProp", &prop);

		prop[0] = &rect;
		prop[1] = &mousewheeldelta;
		prop[2] = &mouseinsidetemp;
		prop[3] = &mousepos;
		prop[4] = &width;
		prop[5] = &height;
		prop[6] = &minimized;
		prop[7] = &resizing;
		prop[8] = &renderwidth;
		prop[9] = &renderheight;
		prop[10] = &defsize;

		windowcount++;

		hdc = GetDC(hwnd);

		chdc = CreateCompatibleDC(hdc);
		SelectObject(chdc, hbmp);

		view = new View({ 0, 0, (float)width, (float)height }, { 0, 0, (float)width, (float)height });
		defview = new View(*view);

		view_init();

		return 1;
	}
	bool Renderer::create_opengl(int Tx, int Ty, int Topengl, int Tw, int Th, const char* Ttext, WindowStyle Twinstyle) {
		// OpenGL

		if (Tw*Th < 1) {
			setLastError(Error::InvalidWindowSize);
			return 0;
		}

		RegisterWindowClass();

		opengl = Topengl; // Set the OpenGL version

		rect.a.x = 0;
		rect.a.y = 0;
		rect.c.x = Tw;
		rect.c.y = Th;

		width = Tw;
		height = Th;

		style = Twinstyle;

		RECT _winfull = { 0,0,Tw,Th };
		AdjustWindowRectEx(&_winfull, (unsigned long)Twinstyle, 0, 0);

		RECT _desktoprect;

		GetWindowRect(GetDesktopWindow(), &_desktoprect);

		int _winx = (Tx == _kp_userdefault ? CW_USEDEFAULT : (Tx < (-_desktoprect.right) ? (-_desktoprect.right) + 1 : (Tx >(_desktoprect.right) ? (_desktoprect.right - 1) : Tx)));
		int _winy = (Ty == _kp_userdefault ? CW_USEDEFAULT : (Ty < (-_desktoprect.bottom) ? (-_desktoprect.bottom) + 1 : (Ty >(_desktoprect.right) ? (_desktoprect.bottom - 1) : Ty)));

		hwnd = CreateWindowExW(0, winclassname, (wchar_t*)Ttext, (unsigned long)Twinstyle, _winx, _winy, _winfull.right - _winfull.left, _winfull.bottom - _winfull.top, NULL, NULL, GetModuleHandleW(NULL), NULL);
		if (hwnd == NULL) {
			setLastError(Error::WindowCreationFailed);
			return 0;
		}

		if (Twinstyle == WindowStyle::FullScreen) {
			enterfullscreen(width, height);
			Twinstyle = WindowStyle::Popup;
		}

		RECT _winrect;
		RECT _winclirect;

		GetWindowRect((HWND)hwnd, &_winrect);
		GetClientRect((HWND)hwnd, &_winclirect);

		SetWindowPos((HWND)hwnd, HWND_NOTOPMOST, _winrect.left, _winrect.top, _winrect.right - _winrect.left, _winrect.bottom - _winrect.top, SWP_SHOWWINDOW);
		//SetWindowLongPtr(hwnd, GWL_STYLE, (unsigned long)Twinstyle | WS_VISIBLE);

		GetClientRect((HWND)hwnd, &_winclirect);

		GetWindowRect(hwnd, &_winrect);
		GetClientRect(hwnd, &_winclirect);

		rect.a.x = _winrect.left;
		rect.a.y = _winrect.top;
		rect.c.x = _winrect.right;
		rect.c.y = _winrect.bottom;

		clientrect.a.x = _winclirect.left;
		clientrect.a.y = _winclirect.top;
		clientrect.c.x = _winclirect.right;
		clientrect.c.y = _winclirect.bottom;

		hdc = GetDC(hwnd);

		// Time for the OpenGL Context

		PIXELFORMATDESCRIPTOR _pfd;
		int _pf;

		memset(&_pfd, 0, sizeof(_pfd));
		_pfd.nSize = sizeof(_pfd);
		_pfd.nVersion = 1;
		_pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		_pfd.iPixelType = PFD_TYPE_RGBA;
		_pfd.cColorBits = 24;
		_pfd.cDepthBits = 16;
		_pfd.iLayerType = PFD_MAIN_PLANE;
		_pf = ChoosePixelFormat((HDC)hdc, &_pfd);
		SetPixelFormat((HDC)hdc, _pf, &_pfd);

		hglrc = wglCreateContext((HDC)hdc);
		wglMakeCurrent((HDC)hdc, (HGLRC)hglrc);

		gladLoadGLLoader((GLADloadproc)_GetProcAddress);

		glViewport(0, 0, Tw, Th);

		SetPropW(hwnd, L"__KPerpRendererClass", this);
		SetPropW(hwnd, L"__KPerpRendererInput", &input);
		SetPropW(hwnd, L"__KPerpRendererProp", &prop);

		prop[0] = &rect;
		prop[1] = &mousewheeldelta;
		prop[2] = &mouseinsidetemp;
		prop[3] = &mousepos;
		prop[4] = &width;
		prop[5] = &height;
		prop[6] = &minimized;
		prop[7] = &resizing;
		prop[8] = &renderwidth;
		prop[9] = &renderheight;
		prop[10] = &defsize;

		windowcount++;

		vao_init();
		shader_init();
		color_tex_init();
		framebuffer_init();

		renderwidth = width;
		renderheight = height;

		currentrenderer = this;

		view = new View({ 0, 0, (float)width, (float)height }, { 0, 0, (float)width, (float)height });
		defview = new View(*view);
		useview = 1;
		LoadIdentity();
		view_init();

		return 1;
	}

	bool Renderer::enterfullscreen(int Tw, int Th) {
		DEVMODEW _devmode;
		_devmode.dmSize = sizeof(DEVMODEW);
		_devmode.dmPelsWidth = Tw;
		_devmode.dmPelsHeight = Th;
		_devmode.dmBitsPerPel = 32;
		_devmode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;

		long _changedisplay = ChangeDisplaySettingsW(&_devmode, CDS_FULLSCREEN);

		if (fullscreen != NULL) {
			setLastError(Error::EnterFullscreenFailedBecauseItsAlreadyFullScreen);
			return 0;
		}
		if (_changedisplay != DISP_CHANGE_SUCCESSFUL) {
			setLastError(Error::EnterFullscreenFailed);
			return 0;
		}

		SetWindowLongW(hwnd, GWL_STYLE, WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS);
		SetWindowLongW(hwnd, GWL_EXSTYLE, WS_EX_APPWINDOW);

		RECT _screenrect;
		GetWindowRect(GetDesktopWindow(), &_screenrect);

		SetWindowPos(hwnd, HWND_TOP, 0, 0, Tw, Th, SWP_FRAMECHANGED);
		ShowWindow(hwnd, SW_SHOW);

		fullscreen = this;

		return 1;
	}

	bool Renderer::leavefullscreen(WindowStyle Tstyle) {
		if (fullscreen == this) {
			SetWindowLongPtr(hwnd, GWL_EXSTYLE, WS_EX_LEFT);
			SetWindowLongPtr(hwnd, GWL_STYLE, (ULONG)Tstyle);

			int _changedisplay = ChangeDisplaySettingsW(NULL, CDS_RESET);
			if (_changedisplay != DISP_CHANGE_SUCCESSFUL) {
				setLastError(Error::LeaveFullscreenFailed);
				return 0;
			}
			SetWindowPos(hwnd, HWND_NOTOPMOST, rect.a.x, rect.a.y, rect.c.x - rect.a.x, rect.c.y - rect.a.y, SWP_SHOWWINDOW);
			ShowWindow(hwnd, SW_RESTORE);

			

			fullscreen = NULL;

			return 1;
		}

		return 0;
	}

	Renderer* getCurrentRenderer() {
		return currentrenderer;
	}
}