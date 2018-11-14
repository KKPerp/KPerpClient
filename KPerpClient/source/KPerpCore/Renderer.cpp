
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

//#include "Window.hpp"
//#include "Ext/KGui/Element.hpp"

#include "Ext/KGui/Textbox.hpp"
#include "Ext/DesignSection.hpp"

#include <map>
#include <vector>

#define _kp_userdefault ((int)0xEFFFFFFF)
//#define _break goto WinProcBreak;

static unsigned int lshiftscancode = MapVirtualKeyW(VK_LSHIFT, MAPVK_VK_TO_VSC);

namespace kp {
	WNDCLASSEXW winclass;

	const int lastestopengl = 46;

	int windowcount = 0;
	const wchar_t* winclassname = L"KPerpWindow";

	int _requestredrawmessage = RegisterWindowMessageW(L"RequestRedraw");
	int _mousewheelchanged = RegisterWindowMessageW(L"MouseWheelChanged");

	Renderer* currentrenderer;
	Renderer* fullscreen;

	LRESULT CALLBACK WinProc(HWND Thwnd, UINT Tmsg, WPARAM Twparam, LPARAM Tlparam) {
		Renderer* _renderer = (Renderer*)GetPropW(Thwnd, L"__KPerpRendererClass");
		Input* _input = (Input*)GetPropW(Thwnd, L"__KPerpRendererInput");
		void** _prop = (void**)GetPropW(Thwnd, L"__KPerpRendererProp");

		

		if (_renderer != NULL) {
			_renderer->mousewheeldelta = 0;

			switch (Tmsg) {
			case WM_CLOSE: {
				_renderer->putEvent({ Event::Type::Close });
				return 0;
			}
			case WM_DESTROY: {
				
				break;
			}
			//case WM_PAINT: {
				//std::cout << "Draw!\n";
				//break;
			//}
			// Non-Client Area Painting HDC
			//HDC hdc;
			//hdc = GetDCEx(hwnd, (HRGN)wParam, DCX_WINDOW | DCX_INTERSECTRGN);
			//case WM_NCPAINT: {
				//std::cout << "Non-Client Draw!\n";
				//break;
			//}
			case WM_TIMER: {
				switch (Twparam) {
				case 1000: {
					_renderer->toggletextboxmarkerblink();
					//_renderer->drawcurrentfocus();
					_renderer->requestredrawcurrentfocus();
					//std::cout << "TOGGLE\n";
					break;
				}
				}
				break;
			}
			case WM_SETFOCUS: {
				Event _event;
				_event.type = Event::Type::GetFocus;
				_renderer->putEvent(_event);

				//if (_renderer->)
				PostMessageW(Thwnd, _requestredrawmessage, 0, 0);
				break;
			}
			case WM_KILLFOCUS: {
				Event _event;
				_event.type = Event::Type::LoseFocus;
				_renderer->putEvent(_event);

				_renderer->resetalltextboxfocus();
				_renderer->requestredrawcurrentfocusall();

				if (!_renderer->destructing) {
					PostMessageW(Thwnd, _requestredrawmessage, 0, 0);
				}
				break;
			}
			//case WM_CHAR: {
				
			//	break;
			//}
			case WM_NCLBUTTONDOWN: {
				PostMessageW(Thwnd, _requestredrawmessage, 0, 0);
			}
			case WM_LBUTTONDOWN: {
				Event _event;
				_event.type = Event::Type::MouseLeftPressed;
				_event.mouse = Mouse::LeftButton;
				//smouse
				short _loword = LOWORD(Twparam);
				_event.mousekeys.leftbutton = _loword & MK_LBUTTON;
				_event.mousekeys.rightbutton = _loword & MK_RBUTTON;
				_event.mousekeys.middlebutton = _loword & MK_MBUTTON;
				_event.mousekeys.shift = _loword & MK_SHIFT;
				_event.mousekeys.control = _loword & MK_CONTROL;
				_event.mousekeys.x1 = _loword & MK_XBUTTON1;
				_event.mousekeys.x2 = _loword & MK_XBUTTON2;
				_event.mousepos = {
					LOWORD(Tlparam),
					HIWORD(Tlparam)
				};
				_renderer->putEvent(_event);
				break;
			}
			case WM_LBUTTONUP: {
				Event _event;
				_event.type = Event::Type::MouseLeftReleased;
				_event.mouse = Mouse::LeftButton;
				//smouse
				short _loword = LOWORD(Twparam);
				_event.mousekeys.leftbutton = _loword & MK_LBUTTON;
				_event.mousekeys.rightbutton = _loword & MK_RBUTTON;
				_event.mousekeys.middlebutton = _loword & MK_MBUTTON;
				_event.mousekeys.shift = _loword & MK_SHIFT;
				_event.mousekeys.control = _loword & MK_CONTROL;
				_event.mousekeys.x1 = _loword & MK_XBUTTON1;
				_event.mousekeys.x2 = _loword & MK_XBUTTON2;
				_event.mousepos = {
					LOWORD(Tlparam),
					HIWORD(Tlparam)
				};
				_renderer->putEvent(_event);
				break;
			}
			case WM_LBUTTONDBLCLK: {
				Event _event;
				_event.type = Event::Type::MouseLeftDoubleClick;
				_event.mouse = Mouse::LeftButton;
				//smouse
				short _loword = LOWORD(Twparam);
				_event.mousekeys.leftbutton = _loword & MK_LBUTTON;
				_event.mousekeys.rightbutton = _loword & MK_RBUTTON;
				_event.mousekeys.middlebutton = _loword & MK_MBUTTON;
				_event.mousekeys.shift = _loword & MK_SHIFT;
				_event.mousekeys.control = _loword & MK_CONTROL;
				_event.mousekeys.x1 = _loword & MK_XBUTTON1;
				_event.mousekeys.x2 = _loword & MK_XBUTTON2;
				_event.mousepos = {
					LOWORD(Tlparam),
					HIWORD(Tlparam)
				};
				_renderer->putEvent(_event);
				break;
			}
			case WM_RBUTTONDOWN: {
				Event _event;
				_event.type = Event::Type::MouseRightPressed;
				_event.mouse = Mouse::RightButton;
				//smouse
				short _loword = LOWORD(Twparam);
				_event.mousekeys.leftbutton = _loword & MK_LBUTTON;
				_event.mousekeys.rightbutton = _loword & MK_RBUTTON;
				_event.mousekeys.middlebutton = _loword & MK_MBUTTON;
				_event.mousekeys.shift = _loword & MK_SHIFT;
				_event.mousekeys.control = _loword & MK_CONTROL;
				_event.mousekeys.x1 = _loword & MK_XBUTTON1;
				_event.mousekeys.x2 = _loword & MK_XBUTTON2;
				_event.mousepos = {
					LOWORD(Tlparam),
					HIWORD(Tlparam)
				};
				_renderer->putEvent(_event);
				break;
			}
			case WM_RBUTTONUP: {
				Event _event;
				_event.type = Event::Type::MouseRightReleased;
				_event.mouse = Mouse::RightButton;
				//smouse
				short _loword = LOWORD(Twparam);
				_event.mousekeys.leftbutton = _loword & MK_LBUTTON;
				_event.mousekeys.rightbutton = _loword & MK_RBUTTON;
				_event.mousekeys.middlebutton = _loword & MK_MBUTTON;
				_event.mousekeys.shift = _loword & MK_SHIFT;
				_event.mousekeys.control = _loword & MK_CONTROL;
				_event.mousekeys.x1 = _loword & MK_XBUTTON1;
				_event.mousekeys.x2 = _loword & MK_XBUTTON2;
				_event.mousepos = {
					LOWORD(Tlparam),
					HIWORD(Tlparam)
				};
				_renderer->putEvent(_event);
				break;
			}
			case WM_RBUTTONDBLCLK: {
				Event _event;
				_event.type = Event::Type::MouseRightDoubleClick;
				_event.mouse = Mouse::RightButton;
				//smouse
				short _loword = LOWORD(Twparam);
				_event.mousekeys.leftbutton = _loword & MK_LBUTTON;
				_event.mousekeys.rightbutton = _loword & MK_RBUTTON;
				_event.mousekeys.middlebutton = _loword & MK_MBUTTON;
				_event.mousekeys.shift = _loword & MK_SHIFT;
				_event.mousekeys.control = _loword & MK_CONTROL;
				_event.mousekeys.x1 = _loword & MK_XBUTTON1;
				_event.mousekeys.x2 = _loword & MK_XBUTTON2;
				_event.mousepos = {
					LOWORD(Tlparam),
					HIWORD(Tlparam)
				};
				_renderer->putEvent(_event);
				break;
			}
			case WM_MBUTTONDOWN: {
				Event _event;
				_event.type = Event::Type::MouseMiddlePressed;
				_event.mouse = Mouse::MiddleButton;
				//smouse
				short _loword = LOWORD(Twparam);
				_event.mousekeys.leftbutton = _loword & MK_LBUTTON;
				_event.mousekeys.rightbutton = _loword & MK_RBUTTON;
				_event.mousekeys.middlebutton = _loword & MK_MBUTTON;
				_event.mousekeys.shift = _loword & MK_SHIFT;
				_event.mousekeys.control = _loword & MK_CONTROL;
				_event.mousekeys.x1 = _loword & MK_XBUTTON1;
				_event.mousekeys.x2 = _loword & MK_XBUTTON2;
				_event.mousepos = {
					LOWORD(Tlparam),
					HIWORD(Tlparam)
				};
				_renderer->putEvent(_event);
				break;
			}
			case WM_MBUTTONUP: {
				Event _event;
				_event.type = Event::Type::MouseMiddleReleased;
				_event.mouse = Mouse::MiddleButton;
				//smouse
				short _loword = LOWORD(Twparam);
				_event.mousekeys.leftbutton = _loword & MK_LBUTTON;
				_event.mousekeys.rightbutton = _loword & MK_RBUTTON;
				_event.mousekeys.middlebutton = _loword & MK_MBUTTON;
				_event.mousekeys.shift = _loword & MK_SHIFT;
				_event.mousekeys.control = _loword & MK_CONTROL;
				_event.mousekeys.x1 = _loword & MK_XBUTTON1;
				_event.mousekeys.x2 = _loword & MK_XBUTTON2;
				_event.mousepos = {
					LOWORD(Tlparam),
					HIWORD(Tlparam)
				};
				_renderer->putEvent(_event);
				break;
			}
			case WM_MBUTTONDBLCLK: {
				Event _event;
				_event.type = Event::Type::MouseMiddleDoubleClick;
				_event.mouse = Mouse::MiddleButton;
				//smouse
				short _loword = LOWORD(Twparam);
				_event.mousekeys.leftbutton = _loword & MK_LBUTTON;
				_event.mousekeys.rightbutton = _loword & MK_RBUTTON;
				_event.mousekeys.middlebutton = _loword & MK_MBUTTON;
				_event.mousekeys.shift = _loword & MK_SHIFT;
				_event.mousekeys.control = _loword & MK_CONTROL;
				_event.mousekeys.x1 = _loword & MK_XBUTTON1;
				_event.mousekeys.x2 = _loword & MK_XBUTTON2;
				_event.mousepos = {
					LOWORD(Tlparam),
					HIWORD(Tlparam)
				};
				_renderer->putEvent(_event);
				break;
			}
			case WM_KEYDOWN: {
				//GetKeyboardState(input->keys);
				_renderer->textboxtyping(Twparam);

				//std::cout << Twparam << "\n";
				Event _event;
				if (Twparam == VK_SHIFT) {
					_event.key = (((Tlparam & (255 << 16)) >> 16) == lshiftscancode) ? Key::LeftShift : Key::RightShift;
				}
				else {
					if (Twparam == VK_CONTROL) {
						_event.key = (HIWORD(Tlparam) & KF_EXTENDED) ? Key::RightControl : Key::LeftControl;
					}
					else {
						if (Twparam == VK_MENU) {
							_event.key = (HIWORD(Tlparam) & KF_EXTENDED) ? Key::RightAlt : Key::LeftAlt;
						}
						else {
							_event.key = (Key)Twparam;
						}
					}

				}
				_event.keyinfo.repeats = LOWORD(Tlparam);
				_event.keyinfo.previous = Tlparam & KF_REPEAT;
				_event.type = Event::Type::KeyPressed;

				_renderer->putEvent(_event);
				break;
			}
			case WM_KEYUP: {
				//GetKeyboardState(input->keys);
				Event _event;
				if (Twparam == VK_SHIFT) {
					_event.key = (((Tlparam & (255 << 16)) >> 16) == lshiftscancode) ? Key::LeftShift : Key::RightShift;
				}
				else {
					if (Twparam == VK_CONTROL) {
						_event.key = (HIWORD(Tlparam) & KF_EXTENDED) ? Key::RightControl : Key::LeftControl;
					}
					else {
						if (Twparam == VK_MENU) {
							_event.key = (HIWORD(Tlparam) & KF_EXTENDED) ? Key::RightAlt : Key::LeftAlt;
						}
						else {
							_event.key = (Key)Twparam;
						}
					}

				}
				_event.keyinfo.repeats = 1;
				_event.keyinfo.previous = 1;
				_event.type = Event::Type::KeyReleased;

				_renderer->putEvent(_event);
				break;
			}
			case WM_SYSKEYDOWN: {
				//GetKeyboardState(input->keys);
				Event _event;
				if (Twparam == VK_SHIFT) {
					_event.key = (((Tlparam & (255 << 16)) >> 16) == lshiftscancode) ? Key::LeftShift : Key::RightShift;
				}
				else {
					if (Twparam == VK_CONTROL) {
						_event.key = (HIWORD(Tlparam) & KF_EXTENDED) ? Key::RightControl : Key::LeftControl;
					}
					else {
						if (Twparam == VK_MENU) {
							_event.key = (HIWORD(Tlparam) & KF_EXTENDED) ? Key::RightAlt : Key::LeftAlt;
						}
						else {
							_event.key = (Key)Twparam;
						}
					}

				}
				_event.keyinfo.repeats = LOWORD(Tlparam);
				_event.keyinfo.previous = Tlparam & KF_REPEAT;
				_event.type = Event::Type::GlobalKeyPressed;

				_renderer->putEvent(_event);
				break;
			}
			case WM_SYSKEYUP: {
				//GetKeyboardState(input->keys);
				Event _event;
				if (Twparam == VK_SHIFT) {
					_event.key = (((Tlparam & (255 << 16)) >> 16) == lshiftscancode) ? Key::LeftShift : Key::RightShift;
				}
				else {
					if (Twparam == VK_CONTROL) {
						_event.key = (HIWORD(Tlparam) & KF_EXTENDED) ? Key::RightControl : Key::LeftControl;
					}
					else {
						if (Twparam == VK_MENU) {
							_event.key = (HIWORD(Tlparam) & KF_EXTENDED) ? Key::RightAlt : Key::LeftAlt;
						}
						else {
							_event.key = (Key)Twparam;
						}
					}

				}
				_event.keyinfo.repeats = 1;
				_event.keyinfo.previous = 1;
				_event.type = Event::Type::GlobalKeyReleased;
				break;
			}

			case WM_MOUSEWHEEL: {
				Event _event;
				_event.type = Event::Type::MouseWheelMoved;
				//smouse
				short _loword = LOWORD(Twparam);
				_event.mousekeys.leftbutton = _loword & MK_LBUTTON;
				_event.mousekeys.rightbutton = _loword & MK_RBUTTON;
				_event.mousekeys.middlebutton = _loword & MK_MBUTTON;
				_event.mousekeys.shift = _loword & MK_SHIFT;
				_event.mousekeys.control = _loword & MK_CONTROL;
				_event.mousekeys.x1 = _loword & MK_XBUTTON1;
				_event.mousekeys.x2 = _loword & MK_XBUTTON2;
				_event.mousepos = {
					LOWORD(Tlparam),
					HIWORD(Tlparam)
				};
				_event.wheelinfo.delta = HIWORD(Twparam);
				_event.wheelinfo.type = Mouse::Vertical;
				_renderer->putEvent(_event);

				_renderer->mousewheeldelta = _event.wheelinfo.delta;
				_renderer->scrolltextbox(_event.wheelinfo.delta);

				PostMessage(Thwnd, _mousewheelchanged, 0, 0);
				break;
			}
			case WM_HSCROLL: {
				Event _event;
				_event.type = Event::Type::MouseWheelMoved;
				//smouse
				short _loword = LOWORD(Twparam);
				_event.mousekeys.leftbutton = _loword & MK_LBUTTON;
				_event.mousekeys.rightbutton = _loword & MK_RBUTTON;
				_event.mousekeys.middlebutton = _loword & MK_MBUTTON;
				_event.mousekeys.shift = _loword & MK_SHIFT;
				_event.mousekeys.control = _loword & MK_CONTROL;
				_event.mousekeys.x1 = _loword & MK_XBUTTON1;
				_event.mousekeys.x2 = _loword & MK_XBUTTON2;
				_event.mousepos = {
					LOWORD(Tlparam),
					HIWORD(Tlparam)
				};
				_event.wheelinfo.delta = HIWORD(Twparam);
				_event.wheelinfo.type = Mouse::Horizontal;
				_renderer->putEvent(_event);
				break;
			}
			case WM_MOUSEMOVE: {
				Event _event;
				_event.type = Event::Type::MouseMove;
				short _loword = LOWORD(Twparam);
				_event.mousekeys.leftbutton = _loword & MK_LBUTTON;
				_event.mousekeys.rightbutton = _loword & MK_RBUTTON;
				_event.mousekeys.middlebutton = _loword & MK_MBUTTON;
				_event.mousekeys.shift = _loword & MK_SHIFT;
				_event.mousekeys.control = _loword & MK_CONTROL;
				_event.mousekeys.x1 = _loword & MK_XBUTTON1;
				_event.mousekeys.x2 = _loword & MK_XBUTTON2;
				_event.mousepos = {
					LOWORD(Tlparam),
					HIWORD(Tlparam)
				};
				_renderer->putEvent(_event);
				
				break;
			}

			case WM_MOUSELEAVE: {
				Event _event;
				_event.type = Event::Type::MouseLeaveClient;
				_renderer->putEvent(_event);
				break;
			}
			case WM_MOUSEHOVER: {
				Event _event;
				_event.type = Event::Type::MouseEnterClient;
				_renderer->putEvent(_event);
				break;
			}
			case WM_SIZING: {
				//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				//std::cout << _renderer->resizing << " size ";
				//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				//std::cout << _renderer->getEventQueueSize() << " size ";
				//Event _event;
				//_event.type = Event::Type::WindowSizing;
				//_renderer->putEvent(_event);
				//return 1;
			}
			case WM_SIZE: {
				//std::cout << _renderer->getEventQueueSize() << " ";
				//if (_renderer->getEventQueueSize() > 100) {
				//	int fuck = 0;
				//}
				if (*(bool*)(_prop[7]) == 0) {
					if (*(int*)(_prop[6]) == 1) {
						if (Twparam == SIZE_RESTORED) {
							Event _event;
							_event.windowchange = (Event::WindowChange)Twparam;
							_event.mousepos = {
								LOWORD(Tlparam),
								HIWORD(Tlparam)
							};
							_event.type = Event::Type::WindowRestored;
							_renderer->putEvent(_event);
							_renderer->minimized = 0;
							if (_renderer->fullscreened == 0) {
								_renderer->cminimized = 0;
							}
						}
						if (Twparam == SIZE_MAXIMIZED) {
							Event _event;
							_event.windowchange = (Event::WindowChange)Twparam;
							_event.mousepos = {
								LOWORD(Tlparam),
								HIWORD(Tlparam)
							};
							_event.type = Event::Type::WindowMaximized;
							_renderer->putEvent(_event);
							_renderer->minimized = 2;
							if (_renderer->fullscreened == 0) {
								_renderer->cminimized = 2;
							}
							if (_renderer->hglrc == NULL) {

							}
						}
					}
					else {
						if (*(int*)(_prop[6]) == 2) {
							if (Twparam == SIZE_RESTORED) {
								Event _event;
								_event.windowchange = (Event::WindowChange)Twparam;
								_event.mousepos = {
									LOWORD(Tlparam),
									HIWORD(Tlparam)
								};
								_event.type = Event::Type::WindowRestored;
								_renderer->putEvent(_event);
								_renderer->minimized = 0;
								if (_renderer->fullscreened == 0) {
									_renderer->cminimized = 0;
								}
							}
							if (Twparam == SIZE_MINIMIZED) {
								Event _event;
								_event.windowchange = (Event::WindowChange)Twparam;
								_event.mousepos = {
									LOWORD(Tlparam),
									HIWORD(Tlparam)
								};
								_event.type = Event::Type::WindowMinimized;
								_renderer->putEvent(_event);
								_renderer->minimized = 1;
								if (_renderer->fullscreened == 0) {
									_renderer->cminimized = 1;
								}
							}
						}
						if (Twparam == SIZE_MINIMIZED) {
							Event _event;
							_event.windowchange = (Event::WindowChange)Twparam;
							_event.mousepos = {
								LOWORD(Tlparam),
								HIWORD(Tlparam)
							};
							_event.type = Event::Type::WindowMinimized;
							_renderer->putEvent(_event);
							_renderer->minimized = 1;
							if (_renderer->fullscreened == 0) {
								_renderer->cminimized = 1;
							}
						}
						if (Twparam == SIZE_MAXIMIZED) {
							Event _event;
							_event.windowchange = (Event::WindowChange)Twparam;
							_event.mousepos = {
								LOWORD(Tlparam),
								HIWORD(Tlparam)
							};
							_event.type = Event::Type::WindowMaximized;
							_renderer->putEvent(_event);
							_renderer->minimized = 2;
							if (_renderer->fullscreened == 0) {
								_renderer->cminimized = 2;
							}
						}
					}

					if (Twparam == SIZE_MINIMIZED || Twparam == SIZE_RESTORED || Twparam == SIZE_MAXIMIZED) {
						if (Twparam == SIZE_RESTORED || Twparam == SIZE_MAXIMIZED) {
							Event _event;
							_event.windowchange = (Event::WindowChange)Twparam;
							_event.mousepos = {
								LOWORD(Tlparam),
								HIWORD(Tlparam)
							};
							_event.type = Event::Type::WindowNonMinimizedChange;
							_renderer->putEvent(_event);
						}
						Event _event;
						_event.windowchange = (Event::WindowChange)Twparam;
						_event.mousepos = {
							LOWORD(Tlparam),
							HIWORD(Tlparam)
						};
						_event.type = Event::Type::WindowSizeChanged;
						_renderer->putEvent(_event);
						_event.windowchange = (Event::WindowChange)Twparam;
						_event.mousepos = {
							LOWORD(Tlparam),
							HIWORD(Tlparam)
						};
						_event.type = Event::Type::WindowChanged;
						_renderer->putEvent(_event);
					}

					//RECT _winrect;
					//GetWindowRect(Thwnd, &_winrect);
					//ClipCursor(&_winrect);


				}
				RECT _winrect;
				GetWindowRect(Thwnd, &_winrect);
				if (((*(Rectangle<long>*)(_prop[0])).c.x) - ((*(Rectangle<long>*)(_prop[0])).a.x) == (_winrect.right - _winrect.left) &&
					((*(Rectangle<long>*)(_prop[0])).c.y) - ((*(Rectangle<long>*)(_prop[0])).a.y) == (_winrect.bottom - _winrect.top)) {
					Event _event;
					_event.windowchange = (Event::WindowChange)Twparam;
					_event.mousepos = {
						LOWORD(Tlparam),
						HIWORD(Tlparam)
					};
					_event.type = Event::Type::WindowMoving;
					_renderer->putEvent(_event);
				}
				else {
					Event _event;
					_event.windowchange = (Event::WindowChange)Twparam;
					_event.mousepos = {
						LOWORD(Tlparam),
						HIWORD(Tlparam)
					};
					_event.type = Event::Type::WindowChangingSize;
					_renderer->putEvent(_event);
				}

				(*(Rectangle<long>*)(_prop[0])).a.x = _winrect.left;
				(*(Rectangle<long>*)(_prop[0])).a.y = _winrect.top;
				(*(Rectangle<long>*)(_prop[0])).c.x = _winrect.right;
				(*(Rectangle<long>*)(_prop[0])).c.y = _winrect.bottom;

				if (_renderer->fullscreened == 0) {
					_renderer->crect.a.x = _winrect.left;
					_renderer->crect.a.y = _winrect.top;
					_renderer->crect.c.x = _winrect.right;
					_renderer->crect.c.y = _winrect.bottom;
				}

				GetClientRect(Thwnd, &_winrect);

				(*(long*)(_prop[4])) = (_winrect.right - _winrect.left);
				(*(long*)(_prop[5])) = (_winrect.bottom - _winrect.top);
				(*(long*)(_prop[8])) = (*(int*)(_prop[4]));
				(*(long*)(_prop[9])) = (*(int*)(_prop[5]));

				Event _event;
				_event.windowchange = (Event::WindowChange)Twparam;
				_event.mousepos = {
					LOWORD(Tlparam),
					HIWORD(Tlparam)
				};
				//_event.type = Event::Type::WindowMovingBorder;
				//_renderer->putEvent(_event);

				if (_renderer->winchangecallback) {
					_renderer->winchangecallback((*(Rectangle<long>*)(_prop[0])), _renderer->crect, (Event::WindowChange)Twparam);
				}

				return 0;
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
						Event _event;
						_event.windowchange = (Event::WindowChange)Twparam;
						_event.mousepos = {
							LOWORD(Tlparam),
							HIWORD(Tlparam)
						};
						_event.type = Event::Type::WindowMoved;
						_renderer->putEvent(_event);
						//_renderer->putEvent(Event::WindowChanged);
					}
					else {
						Event _event;
						_event.windowchange = (Event::WindowChange)Twparam;
						_event.mousepos = {
							LOWORD(Tlparam),
							HIWORD(Tlparam)
						};
						_event.type = Event::Type::WindowSizeChanged;
						_renderer->putEvent(_event);
						//_renderer->putEvent(Event::WindowChanged);
					}

					(*(Rectangle<long>*)(_prop[0])).a.x = _winrect.left;
					(*(Rectangle<long>*)(_prop[0])).a.y = _winrect.top;
					(*(Rectangle<long>*)(_prop[0])).c.x = _winrect.right;
					(*(Rectangle<long>*)(_prop[0])).c.y = _winrect.bottom;

					if (_renderer->fullscreened == 0) {
						_renderer->crect.a.x = _winrect.left;
						_renderer->crect.a.y = _winrect.top;
						_renderer->crect.c.x = _winrect.right;
						_renderer->crect.c.y = _winrect.bottom;
					}

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
				Event _event;
				_event.windowchange = (Event::WindowChange)Twparam;
				_event.mousepos = {
					LOWORD(Tlparam),
					HIWORD(Tlparam)
				};
				_event.type = Event::Type::WindowChanged;
				_renderer->putEvent(_event);
				break;
			}

			default: {
				//return DefWindowProc(Thwnd, Tmsg, Twparam, Tlparam);
			}
			}
		}

		//WinProcBreak:

		return DefWindowProcW(Thwnd, Tmsg, Twparam, Tlparam);
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

	WindowStyle operator|(const WindowStyle& Tlstyle, const WindowStyle& Trstyle) {
		return (WindowStyle)((unsigned int)Tlstyle | (unsigned int)Trstyle);
	}

	Input::Input() {

	}
	Input::~Input() {

	}

	Renderer::Renderer() {
		designsectionclass = NULL;
		designsection = NULL;
	}

	struct DesignSectionClassData {
		unsigned int exsize;
		Renderer* renderer;

		DesignSectionProcedure dsproc;
		bool enablestep;

		DesignSectionDrawFunc backdrawfunc;
		DesignSectionDrawFunc foredrawfunc;
	};

	struct DesignSectionData {
		DesignSectionData() {
			texture = NULL;
		}
		~DesignSectionData() {
			if (texture) {
				delete texture;
			}
		}

		DesignSectionClassData* dsclass;

		Rectangle<int> rect;

		bool mouseentered;
		bool pressed[3];

		Texture* texture;
		Sprite sprite;

		bool painting;

		unsigned int uint;
		
		bool mouseover;
	};

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
			running = create_opengl(_kp_userdefault, _kp_userdefault, Topengl, Tw, Th, L"", WindowStyle::OverlappedWindow);
		}
	}

	void Renderer::Destroy() {
		HDC _hdc = wglGetCurrentDC();
		HGLRC _hglrc = wglGetCurrentContext();
		bool _current = 1;
		if (hdc != _hdc || hglrc != _hglrc) {
			makeCurrent();
			_current = 0;
		}

		destructing = 1;

		if (designsectionclass) {
			delete (std::map<std::string, DesignSectionClassData>*)designsectionclass;
			designsectionclass = NULL;
		}
		if (designsection) {
			delete (std::map<std::string, DesignSectionData>*)designsection;
			designsection = NULL;
		}

		// Software
		if (buffer != NULL && hbmp == NULL) {
			delete[] buffer;
			buffer = NULL;
		}
		// Software + Window
		if (hbmp != NULL) {
			DeleteObject(hbmp); // Delete HandleBitmap will also delete surface
			hbmp = NULL;
			buffer = NULL;
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

			if (shader != NULL) {
				delete shader;
				shader = NULL;
			}

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

		destructing = 0;
		running = 0;

		if (!_current) {
			wglMakeCurrent(_hdc, _hglrc);
		}
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

	int Renderer::getOpenGL() {
		return opengl;
	}

	Event Renderer::getEvent() {
		return { Event::Type::None };
	}
	Event Renderer::waitEvent() {
		return { Event::Type::None };
	}
	int Renderer::waitPullEvent(Event& Tevent) {
		return 0;
	}
	int Renderer::pullEvent(Event& Tevent) {
		return 0;
	}
	int Renderer::getEventQueueSize() {
		return 0;
	}
	Event Renderer::putEvent(Event Tevent) {
		return { Event::Type::None };
	}
	Event Renderer::popEvent() {
		return { Event::Type::None };
	}

	bool Renderer::getResizing() {
		return resizing;
	}

	void Renderer::setWindowChangeCallBack(WindowChangeCallback Twinchangecallback) {
		winchangecallback = Twinchangecallback;
	}

	int Renderer::keyPress(Key Tkey) {
		return 0;
	}
	int Renderer::keyPress(unsigned char Tkey) {
		return 0;
	}

	int Renderer::keyHold(Key Tkey) {
		return 0;
	}
	int Renderer::keyHold(unsigned char Tkey) {
		return 0;
	}

	int Renderer::keyPressed(Key Tkey) {
		return 0;
	}
	int Renderer::keyPressed(unsigned char Tkey) {
		return 0;
	}
	int Renderer::keyReleased(Key Tkey) {
		return 0;
	}
	int Renderer::keyReleased(unsigned char Tkey) {
		return 0;
	}

	int Renderer::mousePress(Mouse Tmousebutton) {
		return 0;
	}
	int Renderer::mousePressed(Mouse Tmousebutton) {
		return 0;
	}
	int Renderer::mouseReleased(Mouse Tmousebutton) {
		return 0;
	}
	int Renderer::mouseHold(Mouse Tmousebutton) {
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
	Point<long> Renderer::ViewMousePos() {
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

	Point<long> Renderer::WindowSize() {
		Point<long> _point;
		_point.x = rect.c.x - rect.a.x;
		_point.y = rect.c.y - rect.c.y;
		return _point;
	}

	Point<long> Renderer::ClientSize() {
		if (fullscreened == 0) {
			Point<long> _point;
			_point.x = width;
			_point.y = height;
			return _point;
		}
		else {
			Point<long> _point;
			_point.x = rect.c.x - rect.a.x;
			_point.y = rect.c.y - rect.c.y;
			return _point;
		}
	}

	Rectangle<long> Renderer::WindowRect() {
		Rectangle<long> _rect;
		GetWindowRect(hwnd,(RECT*)&_rect);
		return _rect;
	}
	Rectangle<long> Renderer::ClientRect() {
		POINT _a = { clientrect.a.x,clientrect.a.y };
		POINT _c = { clientrect.c.x,clientrect.c.y };
		ClientToScreen(hwnd, &_a);
		ClientToScreen(hwnd, &_c);
		return { _a.x,_a.y,_c.x,_c.y };
	}

	void Renderer::EnableBlending(BlendFactor TSourceFac, BlendFactor TDestFac) {
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

	void Renderer::DisableBlending() {
		if (hglrc != NULL) {
			glDisable(GL_BLEND);
		}
	}

	void Renderer::setTarget(Texture& Ttex) {
		if (hglrc != NULL) {
			glBindFramebuffer(GL_FRAMEBUFFER, tframebuffer);
			Ttex._makeframebuffer();
			glViewport(0, 0, Ttex.getSize().x, Ttex.getSize().y);

			renderwidth = Ttex.getSize().x;
			renderheight = Ttex.getSize().y;

			targettexture = &Ttex;

			if (useview) {
				viewmatrix = Ortho(Rectangle<float> {  0.0f, 0.0f, (float)renderwidth, (float)renderheight });
			}
			if (hglrc != NULL) {
				shader->setUniform(viewmatrixlocation, viewmatrix);
				shader->setUniform(transmatrixlocation, transmatrix);
				if (cshader != NULL) {
					cshader->setUniform(shaderviewmatrixlocation, viewmatrix);
					cshader->setUniform(shadertransmatrixlocation, transmatrix);
				}
			}
		}
		else {
			renderwidth = Ttex.getSize().x;
			renderheight = Ttex.getSize().y;

			targettexture = &Ttex;

			renderer.settarget(renderwidth, renderheight, (unsigned int*)Ttex.buffer);
		}
	}
	void Renderer::setTarget(const View& Tview) {
		if (hglrc != NULL) {
			if (targettexture != NULL) {
				resetTarget();
			}
			glViewport(Tview.port.a.x, (height - (Tview.port.c.y)), Tview.port.c.x - Tview.port.a.x, Tview.port.c.y);

			renderwidth = Tview.port.c.x - Tview.port.a.x;
			renderheight = Tview.port.c.y - Tview.port.a.y;

			if (useview) {
				if (view->view.a.x != Tview.view.a.x || view->view.a.y != Tview.view.a.y || view->view.c.x != Tview.view.c.x || view->view.c.y != Tview.view.c.y) {
					viewmatrix = Ortho(Tview.view);
				}
			}

			*view = Tview;

			//viewmatrix = Scale(viewmatrix, Vec4(Tview.zoom.x, Tview.zoom.y, 1, 1));
			//viewmatrix = Matrix<float, 4, 4>();
			//viewmatrix = Translate(viewmatrix, Vec3(10, 10, 0));
			//Matrix<float, 4, 4> _viewmatrix = Translate(Matrix<float, 4, 4>(), Vec3(1, 1, 0));

			//viewmatrix = viewmatrix * _viewmatrix;
			transmatrix = Matrix<float, 4, 4>();
			if (Tview.zoom != Vec2(1, 1)) {
				transmatrix = Scale(transmatrix, Vec4(Tview.zoom.x, Tview.zoom.y, 1, 1));
			}
			if (Tview.angle != 0) {
				transmatrix = Rotate(transmatrix, radians_const(Tview.angle), Vec3(0, 0, 1));
			}

			if (hglrc != NULL) {
				shader->setUniform(viewmatrixlocation, viewmatrix);
				shader->setUniform(transmatrixlocation, transmatrix);
				if (cshader != NULL) {
					cshader->setUniform(shaderviewmatrixlocation, viewmatrix);
					cshader->setUniform(shadertransmatrixlocation, transmatrix);
				}
			}
		}
		else {
			renderwidth = Tview.port.c.x - Tview.port.a.x;
			renderheight = Tview.port.c.y - Tview.port.a.y;

			*view = Tview;
		}

		//targettexture = &Ttex;
	}
	void Renderer::resetTarget() {
		if (hglrc != NULL) {
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
					shader->setUniform(viewmatrixlocation, viewmatrix);
					shader->setUniform(transmatrixlocation, transmatrix);
					if (cshader != NULL) {
						cshader->setUniform(shaderviewmatrixlocation, viewmatrix);
						cshader->setUniform(shadertransmatrixlocation, transmatrix);
					}
				}
			}
		}
		else {
			renderwidth = defview->port.c.x - defview->port.a.x;
			renderheight = defview->port.c.y - defview->port.a.y;

			*view = *defview;

			targettexture = NULL;

			renderer.settarget(((BITMAPINFO*)(&bmpinfo))->bmiHeader.biWidth, -(((BITMAPINFO*)(&bmpinfo))->bmiHeader.biHeight), buffer);
		}
	}

	void Renderer::restoreView() {
		if (hglrc != NULL) {
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
				shader->setUniform(viewmatrixlocation, viewmatrix);
				shader->setUniform(transmatrixlocation, transmatrix);
				if (cshader != NULL) {
					cshader->setUniform(shaderviewmatrixlocation, viewmatrix);
					cshader->setUniform(shadertransmatrixlocation, transmatrix);
				}
			}
		}
		else {
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

			renderwidth = view->port.c.x - view->port.a.x;
			renderheight = view->port.c.y - view->port.a.y;
		}
	}
	void Renderer::updateView() {
		if (hglrc != NULL) {
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
				shader->setUniform(viewmatrixlocation, viewmatrix);
				shader->setUniform(transmatrixlocation, transmatrix);
				if (cshader != NULL) {
					cshader->setUniform(shaderviewmatrixlocation, viewmatrix);
					cshader->setUniform(shadertransmatrixlocation, transmatrix);
				}
			}
		}
		else {
			renderwidth = view->port.c.x - view->port.a.x;
			renderheight = view->port.c.y - view->port.a.y;
		}
	}
	void Renderer::updateViewPosition() {
		if (hglrc != NULL) {
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
		else {
			view->port = {
				0,
				0,
				(float)width,
				(float)height
			};
			renderwidth = view->port.c.x - view->port.a.x;
			renderheight = view->port.c.y - view->port.a.y;
		}
	}

	void Renderer::useView(bool Tuse) {
		if (hglrc != NULL) {
			useview = Tuse;
			if (!useview) {
				viewmatrix = Matrix<float, 4, 4>();
				shader->setUniform(viewmatrixlocation, viewmatrix);
				if (cshader != NULL) {
					cshader->setUniform(shadermatrixlocation, matrix);
				}
			}
			else {
				updateView();
			}
		}
		else {
			if (!useview) {

			}
			else {
				updateView();
			}
		}
	}

	bool Renderer::isDestructing() {
		return destructing;
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
	void Renderer::UseDefaultShader() {
		shader->Use();
		shader->setUniform(matrixlocation, matrix);
		shader->setUniform(viewmatrixlocation, viewmatrix);
		shader->setUniform(transmatrixlocation, transmatrix);

		cshader = NULL;
	}
	OpenGL::Shader* Renderer::getShader() {
		return cshader;
	}
	bool Renderer::isShaderDefault() {
		return !cshader;
	}

	void Renderer::getShaderMatrixLocation(unsigned int* Tmatrixloc, unsigned int* Tviewmatrixloc, unsigned int* Ttransmatrixloc) {
		*Tmatrixloc = shadermatrixlocation;
		*Tviewmatrixloc = shaderviewmatrixlocation;
		*Ttransmatrixloc = shadertransmatrixlocation;
	}
	void Renderer::getShaderMatrixLocation(unsigned int* Tloc) {
		Tloc[0] = shadermatrixlocation;
		Tloc[1] = shaderviewmatrixlocation;
		Tloc[2] = shadertransmatrixlocation;
	}

	Matrix<float, 4, 4> Renderer::getViewMatrix() {
		return viewmatrix;
	}
	void Renderer::setViewMatrix(Matrix<float, 4, 4> Tmatrix) {
		viewmatrix = Tmatrix;
	}
	void Renderer::restoreViewMatrix() {
		viewmatrix = Ortho(view->view);
	}

	void Renderer::processInput() {
		
	}
	void Renderer::processMouseInput() {

	}
	void Renderer::processKeyInput() {

	}

	Renderer::~Renderer() {
		// Software
		destructing = 1;
		if (buffer != NULL && hbmp == NULL) {
			delete[] buffer;
			buffer = NULL;
		}
		// Software + Window
		if (hbmp != NULL) {
			DeleteObject(hbmp); // Delete HandleBitmap will also delete surface
			hbmp = NULL;
			buffer = NULL;
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

			if (shader != NULL) {
				delete shader;
				shader = NULL;
			}

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

		destructing = 0;
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

		shader = new Shader;
		Shader& shader = *this->shader;

		shader.Create(NULL, NULL);

		shader.Begin(Shader::Vertex, 1);

		shader += "#version 330 core";
		shader << "layout (location = 0) in vec3 _kp_Pos;";
		shader << "layout (location = 1) in vec4 _kp_Color;";
		shader << "layout (location = 2) in vec2 _kp_TexCoord;";
		shader << "out vec2 _kp_outTexCoord;";
		shader << "out vec4 _kp_outColor;";
		//shader << "out vec4 _kp_outPos;";
		shader << "uniform mat4 _kp_matrix;";
		shader << "uniform mat4 _kp_view;";
		shader << "uniform mat4 _kp_transview;";
		shader << "void main() {";
		shader << "    gl_Position = _kp_transview * _kp_view * _kp_matrix * vec4(_kp_Pos.x, _kp_Pos.y, _kp_Pos.z, 1.0);";
		//shader << "    gl_Position = _kp_outPos;";
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
		//shader << "in vec4 _kp_outPos;";
		shader << "uniform sampler2D _kp_Tex;";
		shader << "void main() {";
		shader << "    FragColor = texture(_kp_Tex,_kp_outTexCoord) * _kp_outColor;";// 
		shader << "}";

		shader.Submit();

		shader.End();

		shader.Compile();

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

		destructing = 0;

		rect.a.x = 0;
		rect.a.y = 0;
		rect.c.x = Tw;
		rect.c.y = Th;

		crect.a.x = 0;
		crect.a.y = 0;
		crect.c.x = Tw;
		crect.c.y = Th;

		width = Tw;
		height = Th;

		buffer = new unsigned int[Tw*Th];

		renderer.settarget(width, height, buffer);

		return 1;
	}

	void Renderer::framebuffer_init() {
		glGenFramebuffers(1, &tframebuffer);
	}

	void Renderer::view_init() {
		viewmatrix = Matrix<float, 4, 4>();
		if (hglrc != NULL) {
			shader->setUniform("_kp_view", viewmatrix);
			matrixlocation = shader->getLocation("_kp_matrix");
			viewmatrixlocation = shader->getLocation("_kp_view");
			transmatrixlocation = shader->getLocation("_kp_transview");
			//shader.setUniform("transview", transview);
		}
		restoreView();
	}

	bool Renderer::create_software_window(int Tx, int Ty, int Tw, int Th, const wchar_t* Ttext, WindowStyle Twinstyle) {
		if (Tw*Th < 1) {
			setLastError(Error::InvalidWindowSize);
			return 0;
		}

		winchangecallback = NULL;

		destructing = 0;

		RegisterWindowClass();

		rect.a.x = 0;
		rect.a.y = 0;
		rect.c.x = Tw;
		rect.c.y = Th;

		crect.a.x = 0;
		crect.a.y = 0;
		crect.c.x = Tw;
		crect.c.y = Th;

		width = Tw;
		height = Th;

		style = Twinstyle;

		RECT _rect;
		GetWindowRect(GetDesktopWindow(), &_rect);

		memset(&bmpinfo, 0, sizeof(bmpinfo));
		((BITMAPINFO*)(&bmpinfo))->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		((BITMAPINFO*)(&bmpinfo))->bmiHeader.biWidth = _rect.right;
		((BITMAPINFO*)(&bmpinfo))->bmiHeader.biHeight = -_rect.bottom; // Set it negative for flip image vertically 
		((BITMAPINFO*)(&bmpinfo))->bmiHeader.biPlanes = 1;
		((BITMAPINFO*)(&bmpinfo))->bmiHeader.biBitCount = 32;
		((BITMAPINFO*)(&bmpinfo))->bmiHeader.biCompression = BI_RGB;

		minimized = 0;
		cminimized = 0;

		if (((unsigned int)Twinstyle >> 30) == 1) {
			minimized = 1;
			cminimized = 1;
		}
		if (((unsigned int)Twinstyle >> 25) == 1) {
			minimized = 2;
			cminimized = 2;
		}

		hbmp = CreateDIBSection(GetDC(0), ((BITMAPINFO*)&bmpinfo), DIB_RGB_COLORS, (void**)&buffer, 0, 0);
		
		BITMAP _bmp;
		GetObjectW(hbmp, sizeof(_bmp), &_bmp);

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
		
		

		hwnd = CreateWindowExW(0, winclassname, Ttext, (unsigned long)Twinstyle, _winx, _winy, _winfull.right - _winfull.left, _winfull.bottom - _winfull.top, NULL, NULL, GetModuleHandleW(NULL), NULL);
		if (hwnd == NULL) {
			setLastError(Error::WindowCreationFailed);
			return 0;
		}

		fullscreened = 0;
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

		crect.a.x = _winrect.left;
		crect.a.y = _winrect.top;
		crect.c.x = _winrect.right;
		crect.c.y = _winrect.bottom;

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

		renderer.settarget(_rect.right, _rect.bottom, buffer);

		designsectionclass = new std::map<std::string, DesignSectionClassData>;
		designsection = new std::map<std::string, DesignSectionData>;

		return 1;
	}
	bool Renderer::create_opengl(int Tx, int Ty, int Topengl, int Tw, int Th, const wchar_t* Ttext, WindowStyle Twinstyle) {
		// OpenGL

		if (Tw*Th < 1) {
			setLastError(Error::InvalidWindowSize);
			return 0;
		}

		winchangecallback = NULL;

		RegisterWindowClass();

		destructing = 0;

		opengl = Topengl; // Set the OpenGL version

		rect.a.x = 0;
		rect.a.y = 0;
		rect.c.x = Tw;
		rect.c.y = Th;

		crect.a.x = 0;
		crect.a.y = 0;
		crect.c.x = Tw;
		crect.c.y = Th;

		width = Tw;
		height = Th;

		style = Twinstyle;

		RECT _winfull = { 0,0,Tw,Th };
		AdjustWindowRectEx(&_winfull, (unsigned long)Twinstyle, 0, 0);

		minimized = 0;
		cminimized = 0;

		if (((unsigned int)Twinstyle & WS_MINIMIZE) == 1) {
			minimized = 1;
			cminimized = 1;
		}
		if (((unsigned int)Twinstyle & WS_MAXIMIZE) == 1) {
			minimized = 2;
			cminimized = 2;
		}

		RECT _desktoprect;

		GetWindowRect(GetDesktopWindow(), &_desktoprect);

		int _winx = (Tx == _kp_userdefault ? CW_USEDEFAULT : (Tx < (-_desktoprect.right) ? (-_desktoprect.right) + 1 : (Tx >(_desktoprect.right) ? (_desktoprect.right - 1) : Tx)));
		int _winy = (Ty == _kp_userdefault ? CW_USEDEFAULT : (Ty < (-_desktoprect.bottom) ? (-_desktoprect.bottom) + 1 : (Ty >(_desktoprect.right) ? (_desktoprect.bottom - 1) : Ty)));

		hwnd = CreateWindowExW(0, winclassname, Ttext, (unsigned long)Twinstyle, _winx, _winy, _winfull.right - _winfull.left, _winfull.bottom - _winfull.top, NULL, NULL, GetModuleHandleW(NULL), NULL);
		if (hwnd == NULL) {
			setLastError(Error::WindowCreationFailed);
			return 0;
		}

		fullscreened = 0;
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

		crect.a.x = _winrect.left;
		crect.a.y = _winrect.top;
		crect.c.x = _winrect.right;
		crect.c.y = _winrect.bottom;

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

		cshader = NULL;

		renderwidth = width;
		renderheight = height;

		currentrenderer = this;

		view = new View({ 0, 0, (float)width, (float)height }, { 0, 0, (float)width, (float)height });
		defview = new View(*view);
		useview = 1;
		LoadIdentity();
		view_init();

		designsectionclass = new std::map<std::string, DesignSectionClassData>;
		designsection = new std::map<std::string, DesignSectionData>;

		return 1;
	}

	void Renderer::toggletextboxmarkerblink() {
		KGui::Textbox::textboxmarker = !KGui::Textbox::textboxmarker;
	}
	void Renderer::drawcurrentfocus() {
		KGui::Textbox::getCurrentFocus()->redraw();
	}
	void Renderer::requestredrawcurrentfocus() {
		KGui::Textbox::getCurrentFocus()->requestRedraw();
	}
	void Renderer::resetalltextboxfocus() {
		KGui::Textbox* _textbox = KGui::Textbox::getCurrentFocus();
		if (_textbox) {
			KGui::Textbox::killCurrentFocus();
			_textbox->redraw();
			KGui::Textbox::textboxmarker = 0;
		}
	}

	static bool clipboardset(const std::string &Tstring) {
		OpenClipboard(0);
		EmptyClipboard();
		HANDLE _handle = GlobalAlloc(GMEM_MOVEABLE, Tstring.size() + 1);
		if (!_handle) {
			CloseClipboard();
			return 0;
		}
		void* _text = GlobalLock(_handle);
		memcpy(_text, Tstring.c_str(), Tstring.size() + 1);
		GlobalUnlock(_handle);
		SetClipboardData(CF_TEXT, _handle);
		CloseClipboard();
		GlobalFree(_handle);

		return 1;
	}
	static std::string clipboardget() {
		OpenClipboard(0);

		HANDLE _handle = GetClipboardData(CF_TEXT);
		if (_handle) {
			char* _text = (char*)GlobalLock(_handle);
			if (_text) {
				std::string _string(_text);

				GlobalUnlock(_handle);
				CloseClipboard();

				return _string;
			}

			GlobalUnlock(_handle);
		}

		CloseClipboard();
		return std::string("");
	}

	void Renderer::textboxtyping(char Tchar) {
		if (KGui::Textbox::getCurrentFocus()) {
			using namespace KGui;
			//std::cout << !(((GetKeyState(VK_CAPITAL) & 0x0001)) || (GetKeyState(VK_SHIFT) & 0x8000)) << "gg \n";
			Textbox& _textbox = *(Textbox::getCurrentFocus());

			if (_textbox.readonly) {
				return;
			}
			if (Textbox::selecting) {
				return;
			}

			int _beginselect = 0;
			int _endselect = 0;
			bool _selected = Textbox::selectpos != -1;
			if (_selected) {
				_beginselect = (_textbox.position < Textbox::selectpos ? _textbox.position : Textbox::selectpos);
				_endselect = (_textbox.position > Textbox::selectpos ? _textbox.position : Textbox::selectpos);
			}

			std::string::iterator _it_beginselect = _textbox.text.string.begin() + _beginselect;
			std::string::iterator _it_endselect = _textbox.text.string.begin() + _endselect;

			std::string::iterator _it_position = _textbox.text.string.begin() + _textbox.position;

			if (GetKeyState(VK_CONTROL) & 0x8000) {
				//std::cout << (int)Tchar << "CTRL\n";
				switch (Tchar) {
				case 'C': {
					if (_selected) {
						clipboardset(_textbox.text.string.substr(_beginselect, _endselect- _beginselect));
					}
					_textbox.requestRedraw();
					break;
				}
				case 'V': {
					if (_selected) {
						_textbox.text.string.erase(_it_beginselect, _it_endselect);
						Textbox::selectpos = -1;
					}
					std::string _string = clipboardget();
					_textbox.text.string.insert(_selected ? _beginselect : _textbox.position, _string);

					_textbox.position = (_selected ? _beginselect : _textbox.position) + _string.size();

					int _width = (_textbox.rect.c.x - _textbox.rect.a.x) - (_textbox.padding.a.x + _textbox.padding.c.x);
					if (_textbox.text.LinePos(_textbox.position).x > _width) {
						_textbox.xseek = _textbox.text.LinePos(_textbox.position).x - _width;
					}
					_textbox.requestRedraw();
					break;
				}
				case 'X': {
					if (_selected) {
						clipboardset(_textbox.text.string.substr(_beginselect, _endselect - _beginselect));
					}
					if (_selected) {
						_textbox.text.string.erase(_it_beginselect, _it_endselect);
						//_textbox.position = _beginselect + 1;
						Textbox::selectpos = -1;
					}
					else {
						_textbox.text.string.erase(_textbox.text.string.begin() + _textbox.position - 1);
					}
					_textbox.requestRedraw();
					break;
				}
				case 'A': {
					Textbox::selectpos = 0;
					_textbox.position = _textbox.text.string.size();
					_textbox.requestRedraw();
					break;
				}

				}
				return;
			}

			//std::cout << (int)Tchar << "\n";
			if (Tchar >= 'A' && Tchar <= 'Z') {
				if (_textbox.maxlength == -1 || _textbox.text.string.size() < _textbox.maxlength) {
					if (_selected) {
						_textbox.text.string.erase(_it_beginselect, _it_endselect);
						Textbox::selectpos = -1;
					}

					_textbox.text.string.insert(_selected ? _it_beginselect : _it_position, Tchar + ((((!(GetKeyState(VK_CAPITAL) & 0x0001)) == !(GetKeyState(VK_SHIFT) & 0x8000))) * 32));
					if (_selected) {
						_textbox.position = _beginselect;
					}

					//std::string::iterator _itertor = _textbox.text.string.begin() + _textbox.position;
					_textbox.position++;
					//std::cout << _textbox.text.string.c_str() << "\n";
					//_textbox.redraw();
					int _width = (_textbox.rect.c.x - _textbox.rect.a.x) - (_textbox.padding.a.x + _textbox.padding.c.x);
					if (_textbox.text.LinePos(_textbox.position).x > _width) {
						_textbox.xseek = _textbox.text.LinePos(_textbox.position).x - _width;
					}
					_textbox.requestRedraw();
				}
			}
			else {
				switch (Tchar) {
				case 8: {
					if (_textbox.text.string.size()) {
						if (_textbox.position || (_selected)) {
							//std::cout << _textbox.text.string[_textbox.position - 1] << " CHAR\n";
							//char _char = (_textbox.text.string[_textbox.position - 1]);
							
							if (_selected) {
								_textbox.text.string.erase(_it_beginselect, _it_endselect);
								_textbox.position = _beginselect+1;
								Textbox::selectpos = -1;
							}
							else {
								_textbox.text.string.erase(_textbox.text.string.begin() + _textbox.position - 1);
							}

							//std::string::iterator _itertor = _textbox.text.string.begin() + _textbox.position;
							_textbox.position--;
							int _fullcharheight = _textbox.text.font->getFullHeight();
							int _line = std::count(_textbox.text.string.begin(), _textbox.text.string.end(), '\n') + 1;
							int _height = (_textbox.rect.c.y - _textbox.rect.a.y) - (_textbox.padding.a.y + _textbox.padding.c.y);
							int _pline = std::count(_textbox.text.string.begin(), _textbox.text.string.begin() + _textbox.position, '\n');

							if (_pline < ((_textbox.yseek / _fullcharheight))) {
								_textbox.yseek -= _fullcharheight;

								if (_textbox.yseek < 0) {
									_textbox.yseek = 0;
								}
								if (_textbox.yseek >((_fullcharheight*_line) - _height)) {
									//if (((_fullcharheight*_line) - _height) > 0) {
									_textbox.yseek = ((_fullcharheight*_line) - _height);
									//}
								}
								if (_textbox.yseek < 0) {
									_textbox.yseek = 0;
								}
							}
							//std::cout << _textbox.text.string.c_str() << "\n";
							
							//_textbox.redraw();
							if (_textbox.text.LinePos(_textbox.position).x < _textbox.xseek) {
								_textbox.xseek = _textbox.text.LinePos(_textbox.position).x;
							}
							_textbox.requestRedraw();
						}
					}
					break;
				}
				case 46: {
					if (_textbox.position < _textbox.text.string.size()) {
						//_textbox.text.string.erase(_textbox.text.string.begin() + _textbox.position);
						if (_selected) {
							_textbox.text.string.erase(_it_beginselect, _it_endselect);
							//_textbox.position = _beginselect + 1;
							Textbox::selectpos = -1;
						}
						else {
							_textbox.text.string.erase(_textbox.text.string.begin() + _textbox.position - 1);
						}

						//std::string::iterator _itertor = _textbox.text.string.begin() + _textbox.position;
						//_textbox.position--;
						//std::cout << _textbox.text.string.c_str() << "\n";
						//_textbox.redraw();
						_textbox.requestRedraw();
					}
					break;
				}
				case 37: {
					if (_textbox.position) {
						_textbox.position--;
						Textbox::textboxmarker = 1;
						if (_textbox.text.string[_textbox.position] == '\n') {
							int _fullcharheight = _textbox.text.font->getFullHeight();
							int _line = std::count(_textbox.text.string.begin(), _textbox.text.string.end(), '\n') + 1;
							int _height = (_textbox.rect.c.y - _textbox.rect.a.y) - (_textbox.padding.a.y + _textbox.padding.c.y);
							int _pline = std::count(_textbox.text.string.begin(), _textbox.text.string.begin() + _textbox.position, '\n');
							//int _bline = _height / _fullcharheight;
						//_textbox.text.LinePos
							if (_pline < ((_textbox.yseek / _fullcharheight))) {
								_textbox.yseek -= _fullcharheight;

								if (_textbox.yseek < 0) {
									_textbox.yseek = 0;
								}
								if (_textbox.yseek >((_fullcharheight*_line) - _height)) {
									//if (((_fullcharheight*_line) - _height) > 0) {
									_textbox.yseek = ((_fullcharheight*_line) - _height);
									//}
								}
								if (_textbox.yseek < 0) {
									_textbox.yseek = 0;
								}
							}
						}
						//int _width = (_textbox.rect.c.x - _textbox.rect.a.x) - (_textbox.padding.a.x + _textbox.padding.c.x);
						if (_textbox.text.LinePos(_textbox.position).x < _textbox.xseek) {
							_textbox.xseek = _textbox.text.LinePos(_textbox.position).x;
						}
						_textbox.requestRedraw();
					}
					break;
				}
				case 39: {
					if (_textbox.position < _textbox.text.string.size()) {
						char _char = _textbox.text.string[_textbox.position];
						_textbox.position++;
						Textbox::textboxmarker = 1;
						_textbox.requestRedraw();
						if (_char == '\n') {
							int _fullcharheight = _textbox.text.font->getFullHeight();
							int _line = std::count(_textbox.text.string.begin(), _textbox.text.string.end(), '\n') + 1;
							int _height = (_textbox.rect.c.y - _textbox.rect.a.y) - (_textbox.padding.a.y + _textbox.padding.c.y);
							int _pline = std::count(_textbox.text.string.begin(), _textbox.text.string.begin() + _textbox.position, '\n');
							int _bline = (_height / _fullcharheight) - 1;
							if (_pline > (_bline + (_textbox.yseek / _fullcharheight))) {
								_textbox.yseek += _fullcharheight;

								if (_textbox.yseek < 0) {
									_textbox.yseek = 0;
								}
								if (_textbox.yseek >((_fullcharheight*_line) - _height)) {
									//if (((_fullcharheight*_line) - _height) > 0) {
									_textbox.yseek = ((_fullcharheight*_line) - _height);
									//}
								}
								if (_textbox.yseek < 0) {
									_textbox.yseek = 0;
								}
							}
						}
						int _width = (_textbox.rect.c.x - _textbox.rect.a.x) - (_textbox.padding.a.x + _textbox.padding.c.x);
						if (_textbox.text.LinePos(_textbox.position).x > _width) {
							_textbox.xseek = _textbox.text.LinePos(_textbox.position).x - _width;
						}
					}
					break;
				}
				case 38: {
					if (_textbox.multiline) {
						if (_textbox.position) {
							int _pos = _textbox.position;
							int _length = _textbox.text.PrevChar(_textbox.position - 1, '\n');
							if (_length == -1) {
								break;
								//_length = _textbox.position - 1;
							}
							_length = _textbox.position - _length;
							_textbox.position = _textbox.text.PrevChar(_textbox.position - 1, '\n');
							_textbox.position = _textbox.text.PrevChar(_textbox.position - 1, '\n')+1;
							
							_textbox.position = _textbox.text.LineIndex(_textbox.position, _textbox.text.LinePos(_pos).x);
							
							int _fullcharheight = _textbox.text.font->getFullHeight();
							int _line = std::count(_textbox.text.string.begin(), _textbox.text.string.end(), '\n') + 1;
							int _height = (_textbox.rect.c.y - _textbox.rect.a.y) - (_textbox.padding.a.y + _textbox.padding.c.y);
							int _pline = std::count(_textbox.text.string.begin(), _textbox.text.string.begin() + _textbox.position, '\n');
							//int _bline = _height / _fullcharheight;
							if (_pline < ((_textbox.yseek / _fullcharheight))) {
								_textbox.yseek -= _fullcharheight;

								if (_textbox.yseek < 0) {
									_textbox.yseek = 0;
								}
								if (_textbox.yseek >((_fullcharheight*_line) - _height)) {
									//if (((_fullcharheight*_line) - _height) > 0) {
									_textbox.yseek = ((_fullcharheight*_line) - _height);
									//}
								}
								if (_textbox.yseek < 0) {
									_textbox.yseek = 0;
								}
							}
							//std::cout << std::count(_textbox.text.string.begin(), _textbox.text.string.begin() + _textbox.position, '\n') << "MARKERPOSY\n";
							//std::cout << _height / _fullcharheight << "LINECOUNT\n";
							if (_textbox.text.LinePos(_textbox.position).x < _textbox.xseek) {
								_textbox.xseek = _textbox.text.LinePos(_textbox.position).x;
							}
							
							//_textbox.position = _textbox.text.LineIndex(_textbox.text.LinePos(_pos))
							//if (_textbox.position == -1) {
							//	_textbox.position = _length;
							//}
						}
						//std::cout << "thisline: " << _textbox.text.LineLength(_textbox.position) << "\n";
						//std::cout << "thisline-1: " << _textbox.text.LineLength(_textbox.position-1) << "\n";
						Textbox::textboxmarker = 1;
						_textbox.requestRedraw();
					}
					break;
				}
				case 40: {
					if (_textbox.multiline) {
						if (_textbox.position < _textbox.text.string.size()) {
							int _pos = _textbox.position;
							
							int _nextlength = _textbox.text.NextChar(_textbox.position, '\n');
							if (_nextlength == -1) {
								return;
							}
							//int _length = _textbox.text.PrevChar(_textbox.position - 1, '\n');
							//if (_length == -1) {
							//	break;
								//_length = _textbox.position - 1;
							//}
							//_length = _textbox.position - _length;
							_textbox.position = _textbox.text.NextChar(_textbox.position, '\n')+1;
							//_textbox.position = _textbox.text.PrevChar(_textbox.position - 1, '\n') + 1;
							_textbox.position = _textbox.text.LineIndex(_textbox.position, _textbox.text.LinePos(_pos).x);
							
							int _fullcharheight = _textbox.text.font->getFullHeight();
							int _line = std::count(_textbox.text.string.begin(), _textbox.text.string.end(), '\n') + 1;
							int _height = (_textbox.rect.c.y - _textbox.rect.a.y) - (_textbox.padding.a.y + _textbox.padding.c.y);
							int _pline = std::count(_textbox.text.string.begin(), _textbox.text.string.begin() + _textbox.position, '\n');
							int _bline = (_height / _fullcharheight)-1;
							if (_pline > (_bline + (_textbox.yseek / _fullcharheight))) {
								_textbox.yseek += _fullcharheight;

								if (_textbox.yseek < 0) {
									_textbox.yseek = 0;
								}
								if (_textbox.yseek >((_fullcharheight*_line) - _height)) {
									//if (((_fullcharheight*_line) - _height) > 0) {
									_textbox.yseek = ((_fullcharheight*_line) - _height);
									//}
								}
								if (_textbox.yseek < 0) {
									_textbox.yseek = 0;
								}
							}
							if (_textbox.text.LinePos(_textbox.position).x < _textbox.xseek) {
								_textbox.xseek = _textbox.text.LinePos(_textbox.position).x;
							}

							//_textbox.position = _textbox.text.LineIndex(_textbox.text.LinePos(_pos))
							//if (_textbox.position == -1) {
							//	_textbox.position = _length;
							//}
						}
						Textbox::textboxmarker = 1;
						_textbox.requestRedraw();
					}
					break;
				}
				case 13: {
					if (_textbox.multiline) {
						if (_textbox.maxlength == -1 || _textbox.text.string.size() < _textbox.maxlength) {
							if (_selected) {
								_textbox.text.string.erase(_it_beginselect, _it_endselect);
								Textbox::selectpos = -1;
							}

							_textbox.text.string.insert(_selected ? _it_beginselect : _it_position, '\n');
							if (_selected) {
								_textbox.position = _beginselect;
							}
							//std::string::iterator _itertor = _textbox.text.string.begin() + _textbox.position;
							_textbox.position++;
							//std::cout << _textbox.text.string.c_str() << "\n";
							//_textbox.redraw();
							int _pos = _textbox.position;

							//int _nextlength = _textbox.text.NextChar(_textbox.position, '\n');
							//if (_nextlength == -1) {
							//	return;
							//}
							//int _length = _textbox.text.PrevChar(_textbox.position - 1, '\n');
							//if (_length == -1) {
							//	break;
							//_length = _textbox.position - 1;
							//}
							//_length = _textbox.position - _length;
							//_textbox.position = _textbox.text.NextChar(_textbox.position, '\n') + 1;
							//_textbox.position = _textbox.text.PrevChar(_textbox.position - 1, '\n') + 1;
							//_textbox.position = _textbox.text.LineIndex(_textbox.position, _textbox.text.LinePos(_pos).x);

							int _fullcharheight = _textbox.text.font->getFullHeight();
							int _line = std::count(_textbox.text.string.begin(), _textbox.text.string.end(), '\n') + 1;
							int _height = (_textbox.rect.c.y - _textbox.rect.a.y) - (_textbox.padding.a.y + _textbox.padding.c.y);
							int _pline = std::count(_textbox.text.string.begin(), _textbox.text.string.begin() + _textbox.position, '\n');
							int _bline = (_height / _fullcharheight) - 1;
							if (_pline > (_bline + (_textbox.yseek / _fullcharheight))) {
								_textbox.yseek += _fullcharheight;

								if (_textbox.yseek < 0) {
									_textbox.yseek = 0;
								}
								if (_textbox.yseek >((_fullcharheight*_line) - _height)) {
									//if (((_fullcharheight*_line) - _height) > 0) {
									_textbox.yseek = ((_fullcharheight*_line) - _height);
									//}
								}
								if (_textbox.yseek < 0) {
									_textbox.yseek = 0;
								}
							}
							if (_textbox.text.LinePos(_textbox.position).x < _textbox.xseek) {
								_textbox.xseek = _textbox.text.LinePos(_textbox.position).x;
							}
							_textbox.requestRedraw();
						}
					}
					break;
				}
				case 36: {
					if (_textbox.multiline) {
						_textbox.position = _textbox.text.PrevChar(_textbox.position-1, '\n')+1;
					}
					else {
						_textbox.position = 0;
					}

					if (_textbox.text.LinePos(_textbox.position).x < _textbox.xseek) {
						_textbox.xseek = _textbox.text.LinePos(_textbox.position).x;
					}
					
					_textbox.requestRedraw();
					break;
				}
				case 35: {
					if (_textbox.multiline) {
						_textbox.position = _textbox.text.NextChar(_textbox.position,'\n');
						if (_textbox.position == -1) {
							_textbox.position = _textbox.text.string.size();
						}
					}
					else {
						_textbox.position = _textbox.text.string.size();
					}

					int _width = (_textbox.rect.c.x - _textbox.rect.a.x) - (_textbox.padding.a.x + _textbox.padding.c.x);
					if (_textbox.text.LinePos(_textbox.position).x > _width) {
						_textbox.xseek = _textbox.text.LinePos(_textbox.position).x - _width;
					}

					_textbox.requestRedraw();
					break;
				}
				default: {
					switch (Tchar) {
					case (char)Key::Numpad0: {
						Tchar = '0';
						break;
					}
					case (char)Key::Numpad1: {
						Tchar = '1';
						break;
					}
					case (char)Key::Numpad2: {
						Tchar = '2';
						break;
					}
					case (char)Key::Numpad3: {
						Tchar = '3';
						break;
					}
					case (char)Key::Numpad4: {
						Tchar = '4';
						break;
					}
					case (char)Key::Numpad5: {
						Tchar = '5';
						break;
					}
					case (char)Key::Numpad6: {
						Tchar = '6';
						break;
					}
					case (char)Key::Numpad7: {
						Tchar = '7';
						break;
					}
					case (char)Key::Numpad8: {
						Tchar = '8';
						break;
					}
					case (char)Key::Numpad9: {
						Tchar = '9';
						break;
					}
					case (char)Key::NumpadAdd: {
						Tchar = '+';
						break;
					}
					case (char)Key::NumpadSubtract: {
						Tchar = '-';
						break;
					}
					case (char)Key::NumpadMultiply: {
						Tchar = '*';
						break;
					}
					case (char)Key::NumpadDivide: {
						Tchar = '/';
						break;
					}
					case (char)Key::NumpadDecimal: {
						Tchar = '.';
						break;
					}
					default: {
						if (GetKeyState(VK_SHIFT) & 0x8000) {
							switch (Tchar) {
							case (char)Key::SemiColon: {
								Tchar = ':';
								break;
							}
							case (char)Key::Equal: {
								Tchar = '+';
								break;
							}
							case (char)Key::Comma: {
								Tchar = '<';
								break;
							}
							case (char)Key::Subtract: {
								Tchar = '_';
								break;
							}
							case (char)Key::Period: {
								Tchar = '>';
								break;
							}
							case (char)Key::Slash: {
								Tchar = '?';
								break;
							}
							case (char)Key::BackTick: {
								Tchar = '~';
								break;
							}
							case (char)Key::LeftSquareBracket: {
								Tchar = '{';
								break;
							}
							case (char)Key::BackSlash: {
								Tchar = '|';
								break;
							}
							case (char)Key::RightSquareBracket: {
								Tchar = '}';
								break;
							}
							case (char)Key::Quote: {
								Tchar = '"';
								break;
							}
							case '1': {
								Tchar = '!';
								break;
							}
							case '2': {
								Tchar = '@';
								break;
							}
							case '3': {
								Tchar = '#';
								break;
							}
							case '4': {
								Tchar = '$';
								break;
							}
							case '5': {
								Tchar = '%';
								break;
							}
							case '6': {
								Tchar = '^';
								break;
							}
							case '7': {
								Tchar = '&';
								break;
							}
							case '8': {
								Tchar = '*';
								break;
							}
							case '9': {
								Tchar = '(';
								break;
							}
							case '0': {
								Tchar = ')';
								break;
							}
							}
						}
						else {
							switch (Tchar) {
							case (char)Key::SemiColon: {
								Tchar = ';';
								break;
							}
							case (char)Key::Equal: {
								Tchar = '=';
								break;
							}
							case (char)Key::Comma: {
								Tchar = ',';
								break;
							}
							case (char)Key::Subtract: {
								Tchar = '-';
								break;
							}
							case (char)Key::Period: {
								Tchar = '.';
								break;
							}
							case (char)Key::Slash: {
								Tchar = '/';
								break;
							}
							case (char)Key::BackTick: {
								Tchar = '`';
								break;
							}
							case (char)Key::LeftSquareBracket: {
								Tchar = '[';
								break;
							}
							case (char)Key::BackSlash: {
								Tchar = '\\';
								break;
							}
							case (char)Key::RightSquareBracket: {
								Tchar = ']';
								break;
							}
							case (char)Key::Quote: {
								Tchar = '\'';
								break;
							}
							}
						}
					}
					}
					
					if (Tchar > 31 && Tchar < 128) {
						if (_textbox.maxlength == -1 || _textbox.text.string.size() < _textbox.maxlength) {
							//std::cout << "PASSED " << Tchar << "\n";
							if (_selected) {
								_textbox.text.string.erase(_it_beginselect, _it_endselect);
								Textbox::selectpos = -1;
							}

							_textbox.text.string.insert(_selected ? _it_beginselect : _it_position, Tchar);
							if (_selected) {
								_textbox.position = _beginselect;
							}
							//std::string::iterator _itertor = _textbox.text.string.begin() + _textbox.position;
							_textbox.position++;
							//std::cout << _textbox.text.string.c_str() << "\n";
							//_textbox.redraw();
							int _width = (_textbox.rect.c.x - _textbox.rect.a.x) - (_textbox.padding.a.x + _textbox.padding.c.x);
							if (_textbox.text.LinePos(_textbox.position).x > _width) {
								_textbox.xseek = _textbox.text.LinePos(_textbox.position).x - _width;
							}
							_textbox.requestRedraw();
						}
					}
				}
				}
			}
		}
	}
	void Renderer::requestredrawcurrentfocusall() {
		KGui::Textbox::requestredrawall = 1;
	}
	void Renderer::scrolltextbox(int Tdelta) {
		//Tdelta = (Tdelta > 0) - (Tdelta < 0);
		if (KGui::Textbox::getCurrentFocus()) {
			KGui::Textbox& _textbox = *(KGui::Textbox::getCurrentFocus());
			//std::cout << (_textbox.rect.c.y ) << "," << ( _textbox.rect.a.y) << "LOL\n";
			int _fullcharheight = _textbox.text.font->getFullHeight();
			int _line = std::count(_textbox.text.string.begin(), _textbox.text.string.end(), '\n')+1;
			int _height = (_textbox.rect.c.y - _textbox.rect.a.y) - (_textbox.padding.a.y + _textbox.padding.c.y);
			//if (_fullcharheight*_line > _height) {
			//	std::cout << (_fullcharheight*_line) << "H\n";
			//}
			_textbox.yseek -= _fullcharheight*(Tdelta/120);
			//std::cout << (_textbox.yseek) << "YSEEK\n";
			//std::cout << std::count(_textbox.text.string.begin(), _textbox.text.string.begin()+_textbox.position,'\n') << "MARKERPOSY\n";
			//std::cout << _height / _fullcharheight << "LINECOUNT\n";
			//int lol[5] = { 1,2,3,4,5 };

			if (_textbox.yseek < 0) {
				_textbox.yseek = 0;
			}
			if (_textbox.yseek > ((_fullcharheight*_line) - _height)) {
				//if (((_fullcharheight*_line) - _height) > 0) {
					_textbox.yseek = ((_fullcharheight*_line) - _height);
				//}
			}
			if (_textbox.yseek < 0) {
				_textbox.yseek = 0;
			}

			_textbox.requestredraw = 1;
		}
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

		fullscreened = 1;

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
			SetWindowLongPtr(hwnd, GWL_STYLE, (ULONG)Tstyle | (WS_MINIMIZE * (cminimized == 1)) | (WS_MAXIMIZE * (cminimized == 2)));

			int _changedisplay = ChangeDisplaySettingsW(NULL, CDS_RESET);
			if (_changedisplay != DISP_CHANGE_SUCCESSFUL) {
				setLastError(Error::LeaveFullscreenFailed);
				return 0;
			}

			fullscreened = 0;

			SetWindowPos(hwnd, HWND_NOTOPMOST, crect.a.x, crect.a.y, crect.c.x - crect.a.x, crect.c.y - crect.a.y, SWP_SHOWWINDOW);
			ShowWindow(hwnd, (cminimized == 1 ? SW_MINIMIZE : cminimized == 2 ? SW_MAXIMIZE : SW_RESTORE));

			fullscreen = NULL;

			return 1;
		}

		return 0;
	}

	void* Renderer::getdesignsectionclass() {
		return designsectionclass;
	}
	void* Renderer::getdesignsection() {
		return designsection;
	}

	void* Renderer::createdesignsectionclass(void* Tdsclass) {
		std::map<std::string, DesignSectionClassData>& _dsclass = *((std::map<std::string, DesignSectionClassData>*)designsectionclass);
		DesignSectionClass& _tdsclass = *((DesignSectionClass*)Tdsclass);

		if (!_dsclass.count(_tdsclass.name)) {
			_dsclass[_tdsclass.name].exsize = _tdsclass.exsize;
			_dsclass[_tdsclass.name].renderer = this;
			_dsclass[_tdsclass.name].dsproc = _tdsclass.dsproc;
			_dsclass[_tdsclass.name].enablestep = _tdsclass.enablestep;
			_dsclass[_tdsclass.name].backdrawfunc = _tdsclass.bgdrawfunc;
			_dsclass[_tdsclass.name].foredrawfunc = _tdsclass.fgdrawfunc;
			void* lol = &_dsclass[_tdsclass.name];
			return &_dsclass[_tdsclass.name];
		}

		return NULL;
	}
	void* Renderer::createdesignsection(void* Tdshclass, std::string Tname, Rectangle<int> Trect) {
		std::map<std::string, DesignSectionData>& _ds = *((std::map<std::string, DesignSectionData>*)designsection);

		if (!_ds.count(Tname)) {
			_ds[Tname].rect = Trect;
			_ds[Tname].dsclass = (DesignSectionClassData*)Tdshclass;
			_ds[Tname].mouseentered = 0;
			if ((Trect.c.x - Trect.a.x)*(Trect.c.y - Trect.a.y)) {
				_ds[Tname].texture = new Texture(*this, (Trect.c.x - Trect.a.x), (Trect.c.y - Trect.a.y));
			}
			_ds[Tname].painting = 0;
			_ds[Tname].uint = 0;
			_ds[Tname].mouseover = 0;
			_ds[Tname].sprite = Sprite(*_ds[Tname].texture, 0, 0);
			return &_ds[Tname];
		}

		return NULL;
	}

	void* Renderer::createdesignsection(std::string Tclass, std::string Tname, Rectangle<int> Trect) {
		std::map<std::string, DesignSectionClassData>& _dsclass = *((std::map<std::string, DesignSectionClassData>*)designsectionclass);

		if (_dsclass.count(Tclass)) {
			return createdesignsection(&_dsclass[Tclass], Tname, Trect);
		}

		return NULL;
	}

	unsigned int Renderer::processeventdesignsection(void* Tdshandle) {
		std::map<std::string, DesignSectionData>& _ds = *((std::map<std::string, DesignSectionData>*)designsection);
		DesignSectionData& _tds = *((DesignSectionData*)Tdshandle);

		using Event = DesignSection::Event;

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

		mousepos = ViewMousePos();
		bool _passevent = 0;
		Point<int> _mousepos;

		if (_tds.dsclass->dsproc) {
			if (mousepos.x >= _tds.rect.a.x &&
				mousepos.y >= _tds.rect.a.y &&
				mousepos.x <= _tds.rect.c.x &&
				mousepos.y <= _tds.rect.c.y
				) {
				_tds.mouseover = 1;
				_mousepos = { mousepos.x - _tds.rect.a.x,mousepos.y - _tds.rect.a.y };
				_passevent = 1;
				_tds.dsclass->dsproc(&_tds, Event::MouseOn, (unsigned int)&_mousepos, 0);//mouseentered
				if (!_tds.mouseentered) {
					_tds.dsclass->dsproc(&_tds, Event::MouseEnter, (unsigned int)&_mousepos, 0);
					_tds.mouseentered = 1;
				}
				if (leftpress) {
					_tds.dsclass->dsproc(&_tds, Event::OnClick, (unsigned int)&_mousepos, (int)Mouse::LeftButton);
				}
				if (rightpress) {
					_tds.dsclass->dsproc(&_tds, Event::OnClick, (unsigned int)&_mousepos, (int)Mouse::RightButton);
				}
				if (middlepress) {
					_tds.dsclass->dsproc(&_tds, Event::OnClick, (unsigned int)&_mousepos, (int)Mouse::MiddleButton);
				}
				if (leftpressed) {
					//_pressonotherwidgets = 1;
					_tds.dsclass->dsproc(&_tds, Event::OnPressed, (unsigned int)&_mousepos, (int)Mouse::LeftButton);
					_tds.pressed[0] = 1;
				}
				if (rightpressed) {
					_tds.dsclass->dsproc(&_tds, Event::OnPressed, (unsigned int)&_mousepos, (int)Mouse::RightButton);
					_tds.pressed[1] = 1;
				}
				if (middlepressed) {
					_tds.dsclass->dsproc(&_tds, Event::OnPressed, (unsigned int)&_mousepos, (int)Mouse::MiddleButton);
					_tds.pressed[2] = 1;
				}
				if (leftreleased) {
					_tds.dsclass->dsproc(&_tds, Event::OnReleased, (unsigned int)&_mousepos, (int)Mouse::LeftButton);
					if (_tds.pressed[0]) {
						_tds.dsclass->dsproc(&_tds, Event::OnClicked, (unsigned int)&_mousepos, (int)Mouse::LeftButton);
						_tds.pressed[0] = 0;
					}
				}
				if (rightreleased) {
					_tds.dsclass->dsproc(&_tds, Event::OnReleased, (unsigned int)&_mousepos, (int)Mouse::RightButton);
					if (_tds.pressed[1]) {
						_tds.dsclass->dsproc(&_tds, Event::OnClicked, (unsigned int)&_mousepos, (int)Mouse::LeftButton);
						_tds.pressed[1] = 0;
					}
				}
				if (middlereleased) {
					_tds.dsclass->dsproc(&_tds, Event::OnReleased, (unsigned int)&_mousepos, (int)Mouse::MiddleButton);
					if (_tds.pressed[2]) {
						_tds.dsclass->dsproc(&_tds, Event::OnClicked, (unsigned int)&_mousepos, (int)Mouse::LeftButton);
						_tds.pressed[2] = 0;
					}
				}
			}
			else {
				_tds.mouseover = 0;
				if (_tds.mouseentered) {
					_tds.dsclass->dsproc(&_tds, Event::MouseLeave, (unsigned int)&_mousepos, 0);
					_tds.mouseentered = 0;
					_tds.pressed[0] = 0;
					_tds.pressed[1] = 0;
					_tds.pressed[2] = 0;
				}
			}

			if (_tds.dsclass->enablestep) {
				if (!_passevent) {
					_mousepos = { mousepos.x - _tds.rect.a.x,mousepos.y - _tds.rect.a.y };
				}
				DesignSectionEventInfo dseventinfo;
				dseventinfo.mouseover = _tds.mouseover;
				_tds.dsclass->dsproc(&_tds, Event::Step, (unsigned int)&_mousepos, (unsigned int)&dseventinfo);
			}
		}

		return 0;
	}

	void* Renderer::beginpaint(DesignSectionHandle Tdshandle) {
		if (Tdshandle->texture) {
			setTarget(*Tdshandle->texture);
			Tdshandle->painting = 1;
			DesignSectionPaint dspaint;
			dspaint.renderer = this;
			dspaint.dshandle = Tdshandle;
			return &dspaint;
		}
		return NULL;
	}
	bool Renderer::endpaint(DesignSectionHandle Tdshandle) {
		if (Tdshandle->painting) {
			resetTarget();
			Tdshandle->painting = 0;
			return 1;
		}
		return 0;
	}

	bool Renderer::setunsignedint(DesignSectionHandle Tdshandle, unsigned int Tuint) {
		Tdshandle->uint = Tuint;
		return 1;
	}
	unsigned int Renderer::getunsignedint(DesignSectionHandle Tdshandle) {
		return Tdshandle->uint;
	}

	bool Renderer::setpos(DesignSectionHandle Tdshandle, Point<int> Tpoint) {
		Tdshandle->rect.c.x = Tpoint.x + (Tdshandle->rect.c.x - Tdshandle->rect.a.x);
		Tdshandle->rect.c.y = Tpoint.y + (Tdshandle->rect.c.y - Tdshandle->rect.a.y);
		Tdshandle->rect.a.x = Tpoint.x;
		Tdshandle->rect.a.y = Tpoint.y;
		return 1;
	}
	bool Renderer::resize(DesignSectionHandle Tdshandle, Point<int> Tpoint) {
		if (Tpoint.x || Tpoint.y) {
			Tdshandle->rect.c.x = Tdshandle->rect.a.x + Tpoint.x;
			Tdshandle->rect.c.y = Tdshandle->rect.a.y + Tpoint.y;

			if (Tdshandle->texture) {
				delete Tdshandle->texture;
				Tdshandle->texture = NULL;
			}
			if ((Tdshandle->rect.c.x - Tdshandle->rect.a.x)*(Tdshandle->rect.c.y - Tdshandle->rect.a.y)) {
				Tdshandle->texture = new Texture(*this, (Tdshandle->rect.c.x - Tdshandle->rect.a.x), (Tdshandle->rect.c.y - Tdshandle->rect.a.y));
			}
		}
		return 1;
	}
	bool Renderer::move(DesignSectionHandle Tdshandle, Point<int> Tpoint) {
		Tdshandle->rect.a.x += Tpoint.x;
		Tdshandle->rect.a.y += Tpoint.y;
		Tdshandle->rect.c.x += Tpoint.x;
		Tdshandle->rect.c.y += Tpoint.y;
		return 1;
	}
	bool Renderer::addsize(DesignSectionHandle Tdshandle, Point<int> Tpoint) {
		if (Tpoint.x || Tpoint.y) {
			Tdshandle->rect.c.x += Tpoint.x;
			Tdshandle->rect.c.y += Tpoint.y;

			if (Tdshandle->texture) {
				delete Tdshandle->texture;
				Tdshandle->texture = NULL;
			}
			if ((Tdshandle->rect.c.x - Tdshandle->rect.a.x)*(Tdshandle->rect.c.y - Tdshandle->rect.a.y)) {
				Tdshandle->texture = new Texture(*this, (Tdshandle->rect.c.x - Tdshandle->rect.a.x), (Tdshandle->rect.c.y - Tdshandle->rect.a.y));
			}
		}
		return 1;
	}
	bool Renderer::setrect(DesignSectionHandle Tdshandle, Rectangle<int> Trect) {
		if (Tdshandle->rect.a.x != Trect.a.x || 
			Tdshandle->rect.a.y != Trect.a.y ||
			Tdshandle->rect.c.x != Trect.c.x ||
			Tdshandle->rect.c.y != Trect.c.y) {
			Tdshandle->rect = Trect;

			if (Tdshandle->texture) {
				delete Tdshandle->texture;
				Tdshandle->texture = NULL;
			}
			if ((Tdshandle->rect.c.x - Tdshandle->rect.a.x)*(Tdshandle->rect.c.y - Tdshandle->rect.a.y)) {
				Tdshandle->texture = new Texture(*this, (Tdshandle->rect.c.x - Tdshandle->rect.a.x), (Tdshandle->rect.c.y - Tdshandle->rect.a.y));
			}
		}
		return 1;
	}

	Rectangle<int> Renderer::getrect(DesignSectionHandle Tdshandle) {
		return Tdshandle->rect;
	}

	bool Renderer::setsprite(DesignSectionHandle Tdshandle, Sprite Tsprite) {
		Tsprite.texture = Tdshandle->texture;
		Tdshandle->sprite = Tsprite;
		Tdshandle->sprite.rect.t1 = Vec2(0, 0);
		Tdshandle->sprite.rect.t2 = Vec2(1, 0);
		Tdshandle->sprite.rect.t3 = Vec2(0, 1);
		Tdshandle->sprite.rect.t4 = Vec2(1, 1);
		return 1;
	}
	Sprite Renderer::getsprite(DesignSectionHandle Tdshandle) {
		Sprite _sprite = Tdshandle->sprite;
		_sprite.texture = NULL;
		return _sprite;
	}

	Renderer* getCurrentRenderer() {
		return currentrenderer;
	}
}