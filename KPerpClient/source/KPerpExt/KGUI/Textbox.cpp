#include <KPerpExt/KGUI/Textbox.hpp>
#include <KPerpCore/Graphic.hpp>

#include <time.h>
#include <windows.h>

namespace kp {
	namespace KGui {
		Textbox* Textbox::currentfocus = NULL;
		bool Textbox::textboxmarker = 0;

		bool Textbox::requestredrawall = 0;

		bool Textbox::selecting = 0;
		int Textbox::selectpos = -1;

		static const int textboxmarkerblinkelapse = 530;

		//void CALLBACK textboxmarkerblink(HWND Thwnd, unsigned int Ttimerindex, unsigned int Twparam, unsigned long Tlparam) {
		//	int _textbixindex = Ttimerindex - 1000;
			//Textbox::textboxmarker = !Textbox::textboxmarker;
		//}

		Textbox::Textbox() {

		}
		Textbox::Textbox(Element* Tparent, Rectangle<int> Trect, Text Ttext, Callback<Textbox> Tcallback,
			Color Tbackcolor, Color Tbordercolor, int Tborderthickness, const Sprite& Tsprite,
			Rectangle<int> Tpadding, Dock Ttldock, Dock Ttrdock, Dock Tbldock, Dock Tbrdock,
			bool Tmultiline, std::string Tfilter, int Tmaxlength, char Tcoverchar, bool Treadonly, int Ttab, bool Twordwrap) {
			parent = Tparent;

			rect = Trect;

			text = Ttext;

			callback = Tcallback;
			bgcolor = Tbackcolor;
			bordercolor = Tbordercolor;
			borderthickness = Tborderthickness;

			backgroundsprite = Tsprite;

			padding = Tpadding;

			backgroundsprite.rect.a = { (float)Trect.a.x,(float)Trect.a.y,0.0f };
			backgroundsprite.rect.c = { (float)Trect.c.x,(float)Trect.c.y,0.0f };

			backgroundsprite.rect.c1 = Tbackcolor;
			backgroundsprite.rect.c2 = Tbackcolor;
			backgroundsprite.rect.c3 = Tbackcolor;
			backgroundsprite.rect.c4 = Tbackcolor;

			tl = Ttldock;
			tr = Ttrdock;
			bl = Tbldock;
			br = Tbrdock;

			if (tl.autopoint) {
				tl.pos = Trect.a;
			}
			if (tl.point == Dock::Auto) {
				tl.point = Dock::TopLeft;
			}
			if (tr.point == Dock::Auto) {
				tr.point = Dock::TopRight;
				if (!tl.autopoint) {
					tr.pos.x = -tr.pos.x;
				}
			}
			if (bl.point == Dock::Auto) {
				bl.point = Dock::BottomLeft;
				if (!tl.autopoint) {
					bl.pos.y = -bl.pos.y;
				}
			}
			if (br.point == Dock::Auto) {
				br.point = Dock::BottomRight;
				if (!tl.autopoint) {
					br.pos.x = -br.pos.x;
					br.pos.y = -br.pos.y;
				}
			}

			requestredraw = 0;
			position = text.string.size();

			mouseentered = 0;
			pressed[0] = 0;
			pressed[1] = 0;
			pressed[2] = 0;

			multiline = Tmultiline;
			filter = Tfilter;
			maxlength = Tmaxlength;
			coverchar = Tcoverchar;
			readonly = Treadonly;

			tab = Ttab;
			wordwrap = Twordwrap;

			xseek = 0;
			yseek = 0;

			type = Type::Textbox;

			create();
		}

		Textbox::~Textbox() {
			destroy();

			if (focus) {
				KillTimer(manager->getrenderer()->hwnd, 1000);

				currentfocus = NULL;
				focus = 0;
			}
		}

		void Textbox::create() {

		}
		void Textbox::destroy() {

		}
		void Textbox::step() {

		}
		void Textbox::draw() {

		}

		static enum TextFunc {
			None,
			Func,
			ColorTag,
			ColorHex
		};

		static unsigned char hexchar(char Tchar) {
			return ((Tchar == '0') ? 0 :
				(Tchar == '1') ? 1 :
				(Tchar == '2') ? 2 :
				(Tchar == '3') ? 3 :
				(Tchar == '4') ? 4 :
				(Tchar == '5') ? 5 :
				(Tchar == '6') ? 6 :
				(Tchar == '7') ? 7 :
				(Tchar == '8') ? 8 :
				(Tchar == '9') ? 9 :
				(Tchar == 'A') ? 10 :
				(Tchar == 'B') ? 11 :
				(Tchar == 'C') ? 12 :
				(Tchar == 'D') ? 13 :
				(Tchar == 'E') ? 14 :
				(Tchar == 'F') ? 15 :
				(Tchar == 'a') ? 10 :
				(Tchar == 'b') ? 11 :
				(Tchar == 'c') ? 12 :
				(Tchar == 'd') ? 13 :
				(Tchar == 'e') ? 14 :
				(Tchar == 'f') ? 15 : 16);
		}

		const unsigned int _white = Color::Cyan.uint();
		const unsigned int _selectedtextbgcolor_rgb = Color(0, 120, 215).uint();
		const unsigned int _selectedtextbgcolor_bgr = Color(0, 120, 215).ruint();

		void Textbox::drawtext() {
			Renderer& _renderer = *(manager->getrenderer());

			int _length = text.string.length();
			TextFunc _Tfunc = TextFunc::None;
			int _Tpos = 0;
			int _Tline = 0;
			int _Tex = 0;

			unsigned int _colort;

			std::string _collecttext;
			int _hexl = 0;

			Color _Tcolor(255, 255, 255, 255);
			Vec4 _color = _Tcolor;

			int _Txpos = 0;

			bool _Tdraw = 0;

			bool _allowbackslash = 0;

			int _cursorposx = 0;
			int _cursorposy = 0;
			bool _cursorposymarked = 0;

			if (_renderer.hglrc != NULL) {
				text.font->getTex()->Bind();
			}

			char _thischar;

			float _bottomheight = (text.font->getFullHeight() - text.font->getHeight());

			int _texty = 0;
			if (text.valign == Text::Middle) {
				_texty = (text.getSize().y - _bottomheight) / 2;
			}
			if (text.valign == Text::Bottom) {
				_texty = (text.getSize().y - _bottomheight);
			}

			int _beginselect;
			int _endselect;
			bool _selected = Textbox::selectpos != -1;
			if (_selected) {
				_beginselect = (position < Textbox::selectpos ? position : Textbox::selectpos);
				_endselect = (position > Textbox::selectpos ? position : Textbox::selectpos);
			}

			bool printrectangle;

			if (text.pos.y + (_Tline * (text.font->getFullHeight() + text.font->getSepWidth()) - _texty) + text.font->getSpaceWidth() < (rect.c.y - rect.a.y)) {
				printrectangle = 1;
			}
			else {
				printrectangle = 0;
			}

			if (text.align == Text::Left) {
				for (int i = 0;i < _length;i++) {
					if (text.string[i] == '\n') {
						
						//_Tex++;

						if (position == i) {
							_cursorposx = _Txpos;
							_cursorposy = _Tline*(text.font->getFullHeight() + text.font->getSepWidth());
							_cursorposymarked = 1;
						}

						_Tline++;

						if (text.pos.y + (_Tline * (text.font->getFullHeight() + text.font->getSepWidth()) - _texty) + text.font->getSpaceWidth() < (rect.c.y - rect.a.y)) {
							printrectangle = 1;
						}
						else {
							printrectangle = 0;
						}

						_Tpos = 0;
						_Txpos = 0;
					}
					if (text.warp) {
						if (_Txpos > text.warp) {
							if (text.warpchar) {
								if (text.string[i] == text.warpchar) {
									_Tline++;
									//_Tex++;
									_Tpos = 0;
									_Txpos = 0;
								}
							}
							else {
								_Tline++;
								//_Tex++;
								_Tpos = 0;
								_Txpos = 0;
							}
						}
					}
					if (text.string[i] == '~') {
						if (_Tfunc == TextFunc::Func) {
							_Tfunc = TextFunc::None;
						}
						else {
							_Tfunc = TextFunc::Func;
						}
					}
					_Tdraw = _Tfunc == (TextFunc::None);
					if ((text.string[i] != ' ') && (text.string[i] != '\n') && (_Tdraw)) {
						_thischar = (coverchar ? coverchar : text.string[i]);
						if (_renderer.hglrc != NULL) {
							float Rx = text.pos.x + _Txpos;
							float Ry = text.pos.y + (_Tline*(text.font->getFullHeight() + text.font->getSepWidth())) - _texty;
							//Shader MShader("Texture.vs", "Texture.fs");
							//std::cout << (TSH) << "," << (DrawTargetHeight) << "," << DrawTarget << "," << (float(DrawTargetHeight) / (ScreenH)) << "\n";
							float Rw = float(((text.font->getWidth(_thischar))));
							float Rh = float(((text.font->getFullHeight())));
							float RTx = float(((_thischar - text.font->getStartChar()) % 16) * text.font->getFullWidth()) / text.font->getTex()->getSize().x;
							float RTy = float(int((_thischar - text.font->getStartChar()) / 16) * text.font->getFullHeight()) / text.font->getTex()->getSize().y;
							float RTw = float(text.font->getWidth(_thischar)) / text.font->getTex()->getSize().x;
							float RTh = (float(text.font->getFullHeight()) / text.font->getTex()->getSize().y);

							float _buffer[] = {
								// positions				// colors					// texture coords
								(Rx),  Ry,				0, _color.x, _color.y, _color.z, _color.w,	RTx		 ,1.0f - (RTy),					// top left
								((Rx + Rw)), Ry,		0, _color.x, _color.y, _color.z, _color.w,	RTx + RTw,1.0f - (RTy),				// top right
								(Rx),  Ry + Rh,			0, _color.x, _color.y, _color.z, _color.w,	RTx		 ,1.0f - (RTy + RTh),		// bottom left
								((Rx + Rw)), Ry + Rh,	0, _color.x, _color.y, _color.z, _color.w,	RTx + RTw,1.0f - (RTy + RTh)	// bottom right

							};
							//*this << Sprite(*text.font->getTex(), ((_thischar - text.font->getStartChar()) % 16) * text.font->getFullWidth(), int((_thischar - text.font->getStartChar()) / 16) * text.font->getFullHeight(), text.font->getWidth(_thischar), text.font->getFullHeight(), Rx, Ry, Rw, Rh);
							glBindVertexArray(_renderer.rectvao);
							glBindBuffer(GL_ARRAY_BUFFER, _renderer.rectvbo);

							memcpy(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY), _buffer, sizeof(_buffer));
							glUnmapBuffer(GL_ARRAY_BUFFER);

							glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

						}
						else {
							//if (i == 1) {
							if (_selected) {
								if (i >= _beginselect && i < _endselect) {
									if (printrectangle) {
										if (text.pos.x + _Txpos + text.font->getSpaceWidth() < (rect.c.x - rect.a.x)) {
											_renderer.renderer.rectangle(text.pos.x + _Txpos, text.pos.y + _Tline * (text.font->getFullHeight() + text.font->getSepWidth()) - _texty, text.pos.x + _Txpos + text.font->getWidth(_thischar), text.font->getFullHeight() + (text.pos.y + _Tline * (text.font->getFullHeight() + text.font->getSepWidth()) - _texty), _renderer.hwnd ? _selectedtextbgcolor_rgb : _selectedtextbgcolor_bgr);
										}
									}
									_colort = _white;
								}
								else {
									if (_renderer.hwnd == NULL) {
										_colort = (unsigned int)(_color.x * 255) + (unsigned int)(_color.y * (65280U)) + (unsigned int)(_color.z * 16711680U) + (unsigned int)(_color.w * 4278190080U);
									}
									else {
										_colort = (unsigned int)(_color.z * 255) + (unsigned int)(_color.y * (65280U)) + (unsigned int)(_color.x * 16711680U) + (unsigned int)(_color.w * 4278190080U);
									}
								}
							}
							else {
								if (_renderer.hwnd == NULL) {
									_colort = (unsigned int)(_color.x * 255) + (unsigned int)(_color.y * (65280U)) + (unsigned int)(_color.z * 16711680U) + (unsigned int)(_color.w * 4278190080U);
								}
								else {
									_colort = (unsigned int)(_color.z * 255) + (unsigned int)(_color.y * (65280U)) + (unsigned int)(_color.x * 16711680U) + (unsigned int)(_color.w * 4278190080U);
								}
							}
							_renderer.renderer.blitrectcolor(*text.font->getTex(), text.pos.x + _Txpos, text.pos.y + _Tline * (text.font->getFullHeight() + text.font->getSepWidth()) - _texty, ((_thischar - text.font->getStartChar()) % 16) * text.font->getFullWidth(), int((_thischar - text.font->getStartChar()) / 16) * text.font->getFullHeight(), text.font->getWidth(_thischar), text.font->getFullHeight(), _colort);
							//}
						}

						if (Textbox::textboxmarker) {
							if (position == i) {
								if (_thischar != '\n') {
									_cursorposx = _Txpos;
									_cursorposy = _Tline*(text.font->getFullHeight() + text.font->getSepWidth());

									_cursorposymarked = 1;
								}
								//_cursorposy = _Typos;
								//_renderer.renderer.line(_Txpos, padding.a.y - 2, _Txpos, (rect.c.y - rect.a.y) - padding.c.y + 2, Color(255, 255, 255, 255).uint());
							}
						}

						_Txpos = _Txpos + (text.font->getWidth(_thischar) + text.font->getSepWidth());
						_Tpos++;

						_collecttext += text.string[i];

					}
					else {
						if (text.string[i] == ' ') {
							if (Textbox::textboxmarker) {
								if (position == i) {
									_cursorposx = _Txpos;
									_cursorposy = _Tline * (text.font->getFullHeight() + text.font->getSepWidth()) - _texty;
									
									_cursorposymarked = 1;
									//_renderer.renderer.line(_Txpos, padding.a.y - 2, _Txpos, (rect.c.y - rect.a.y) - padding.c.y + 2, Color(255, 255, 255, 255).uint());
								}
							}
							if (_selected) {
								if (printrectangle) {
									if (i >= _beginselect && i < _endselect) {
										if (text.pos.x + _Txpos + text.font->getSpaceWidth() < (rect.c.x - rect.a.x)) {
											_renderer.renderer.rectangle(text.pos.x + _Txpos, text.pos.y + _Tline * (text.font->getFullHeight() + text.font->getSepWidth()) - _texty, text.pos.x + _Txpos + text.font->getSpaceWidth(), text.font->getFullHeight() + (text.pos.y + _Tline * (text.font->getFullHeight() + text.font->getSepWidth()) - _texty), _renderer.hwnd ? _selectedtextbgcolor_rgb : _selectedtextbgcolor_bgr);
										}
									}
								}
							}
							_Txpos = _Txpos + text.font->getSpaceWidth();
							_Tpos++;
							_collecttext += text.string[i];
							//_Tfunc = _Tfunc + text[i];
							//_Tex++;
						}
						if (_Tfunc == TextFunc::Func) {
							switch (text.string[i]) {
							default: {
								_Tfunc = TextFunc::None;
								break;
							}
							case '~': {
								break;
							}
							case 'r': {
								_color = Color(255, 255, 255, 255);
								_Tfunc = TextFunc::None;
								break;
							}
							case '&': {
								_Tfunc = TextFunc::ColorTag;
								break;
							}
									  //hex input
							case '#': {
								_Tfunc = TextFunc::ColorHex;
								break;
							}
							}
							continue;
						}
						if (_Tfunc == TextFunc::ColorTag) {
							switch (text.string[i]) {
							default: {
								_color = Color(255, 255, 255, 255);
								_Tfunc = TextFunc::None;
								break;
							}
							case '0': {
								_color = Color(0, 0, 0, 255);
								_Tfunc = TextFunc::None;
								break;
							}
							case '~': {
								break;
							}
							case '1': {
								_color = Color(255, 255, 0, 255);
								_Tfunc = TextFunc::None;
								break;
							}
							case '2': {
								_color = Color(0, 255, 0, 255);
								_Tfunc = TextFunc::None;
								break;
							}
							case '3': {
								_color = Color(0, 255, 255, 255);
								_Tfunc = TextFunc::None;
								break;
							}
							case '4': {
								_color = Color(0, 0, 255, 255);
								_Tfunc = TextFunc::None;
								break;
							}
							case '5': {
								_color = Color(255, 0, 255, 255);
								_Tfunc = TextFunc::None;
								break;
							}
							case '6': {
								_color = Color(255, 0, 0, 255);
								_Tfunc = TextFunc::None;
								break;
							}
							case '7': {
								_color = Color(63, 63, 63, 255);
								_Tfunc = TextFunc::None;
								break;
							}
							case '8': {
								_color = Color(127, 127, 127, 255);
								_Tfunc = TextFunc::None;
								break;
							}
							case '9': {
								_color = Color(191, 191, 191, 255);
								_Tfunc = TextFunc::None;
								break;
							}
							case 'r': {
								_color = Color(255, 255, 255, 255);
								_Tfunc = TextFunc::None;
								break;
							}
							case 'G': {
								_color = Color(0, 255, 0, 255);
								_Tfunc = TextFunc::None;
								break;
							}
							}
							//_color = _Tcolor;
							continue;
						}
						if (_Tfunc == TextFunc::ColorHex) {
							if (_hexl == 0) {
								_Tcolor = Color(0, 0, 0, 255);
							}
							_hexl++;
							if (_hexl == 1) {
								_Tcolor.r() += hexchar(text.string[i]) * 16;
							}
							if (_hexl == 2) {
								_Tcolor.r() += hexchar(text.string[i]) * 1;
							}
							if (_hexl == 3) {
								_Tcolor.g() += hexchar(text.string[i]) * 16;
							}
							if (_hexl == 4) {
								_Tcolor.g() += hexchar(text.string[i]) * 1;
							}
							if (_hexl == 5) {
								_Tcolor.b() += hexchar(text.string[i]) * 16;
							}
							if (_hexl == 6) {
								_Tcolor.b() += hexchar(text.string[i]) * 1;
								_Tfunc = TextFunc::None;
								_hexl = 0;
								_color = _Tcolor;
							}
						}
					}
				}
				if (Textbox::textboxmarker) {
					if (!_cursorposx) {
						if (position == text.string.size()) {
							_cursorposx = _Txpos;
						}
					}
					if (!_cursorposymarked) {
						_cursorposy = _Tline * (text.font->getFullHeight() + text.font->getSepWidth());
					}
					_renderer.renderer.line(_cursorposx + text.pos.x, padding.a.y - 2 + (_cursorposy) - (yseek), _cursorposx + text.pos.x, (padding.a.y)+text.font->getFullHeight() + (_cursorposy)-(yseek), Color(255, 255, 255, 255).uint());
					//_renderer.renderer.rectangle(_cursorposx + text.pos.x, padding.a.y - 2 + (_cursorposy), _cursorposx + text.pos.x + 6, (padding.a.y) + text.font->getFullHeight() + (_cursorposy), Color(255, 255, 255, 255).uint());
				}
				return;
			}
			if (text.align == Text::Right) {
				int _textx = 0;

				for (int i = 0;i < _length;i++) {
					if (text.warp) {
						if (_Txpos > text.warp) {
							if (text.warpchar) {
								if (text.string[i] == text.warpchar) {
									_Tline++;
									//_Tex++;
									_Tpos = 0;
									_Txpos = 0;
								}
							}
							else {
								_Tline++;
								//_Tex++;
								_Tpos = 0;
								_Txpos = 0;
							}
						}
					}
					if (!_Txpos) {
						float _linewidth = text.LineWidth(i);
						if (_linewidth > text.warp) {
							_textx = text.pos.x - (text.warp);
						}
						else {
							_textx = text.pos.x - (_linewidth);
						}

					}
					if (text.string[i] == '\n') {
						_Tline++;
						//_Tex++;
						_Tpos = 0;
						_Txpos = 0;
					}
					if (text.string[i] == '~') {
						if (_Tfunc == TextFunc::Func) {
							_Tfunc = TextFunc::None;
						}
						else {
							_Tfunc = TextFunc::Func;
						}
					}
					_Tdraw = _Tfunc == (TextFunc::None);
					if ((text.string[i] != ' ') && (text.string[i] != '\n') && (_Tdraw)) {

						if (_renderer.hglrc != NULL) {
							float Rx = _textx + _Txpos;
							float Ry = text.pos.y + _Tline * (text.font->getFullHeight() + text.font->getSepWidth()) - _texty;
							//Shader MShader("Texture.vs", "Texture.fs");
							//std::cout << (TSH) << "," << (DrawTargetHeight) << "," << DrawTarget << "," << (float(DrawTargetHeight) / (ScreenH)) << "\n";
							float Rw = float(((text.font->getWidth(text.string[i]))));
							float Rh = float(((text.font->getFullHeight())));
							float RTx = float(((text.string[i] - text.font->getStartChar()) % 16) * text.font->getFullWidth()) / text.font->getTex()->getSize().x;
							float RTy = float(int((text.string[i] - text.font->getStartChar()) / 16) * text.font->getFullHeight()) / text.font->getTex()->getSize().y;
							float RTw = float(text.font->getWidth(text.string[i])) / text.font->getTex()->getSize().x;
							float RTh = (float(text.font->getFullHeight()) / text.font->getTex()->getSize().y);

							float _buffer[] = {
								// positions				// colors					// texture coords
								(Rx),  Ry,				0, _color.x, _color.y, _color.z, _color.w,	RTx		 ,1.0f - (RTy),					// top left
								((Rx + Rw)), Ry,		0, _color.x, _color.y, _color.z, _color.w,	RTx + RTw,1.0f - (RTy),				// top right
								(Rx),  Ry + Rh,			0, _color.x, _color.y, _color.z, _color.w,	RTx		 ,1.0f - (RTy + RTh),		// bottom left
								((Rx + Rw)), Ry + Rh,	0, _color.x, _color.y, _color.z, _color.w,	RTx + RTw,1.0f - (RTy + RTh)	// bottom right

							};
							//*this << Sprite(*text.font->getTex(), ((text.string[i] - text.font->getStartChar()) % 16) * text.font->getFullWidth(), int((text.string[i] - text.font->getStartChar()) / 16) * text.font->getFullHeight(), text.font->getWidth(text.string[i]), text.font->getFullHeight(), Rx, Ry, Rw, Rh);
							glBindVertexArray(_renderer.rectvao);
							glBindBuffer(GL_ARRAY_BUFFER, _renderer.rectvbo);

							memcpy(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY), _buffer, sizeof(_buffer));
							glUnmapBuffer(GL_ARRAY_BUFFER);

							glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

						}
						else {
							//if (i == 1) {
							//_textx +
							/*
							renderer.blitrect(*text.font->getTex(),
							(_Txpos) + (text.font->getWidth(text.string[i])),
							(text.pos.y + (_size.y - ((_Tline) * (text.font->getFullHeight() + text.font->getSepWidth())))),
							(((text.string[i] - text.font->getStartChar()) % 16) * text.font->getFullWidth()),
							(int((text.string[i] - text.font->getStartChar()) / 16) * text.font->getFullHeight()),
							(text.font->getWidth(text.string[i])),
							(text.font->getFullHeight()));
							*/
							if (_renderer.hwnd == NULL) {
								_colort = (unsigned int)(_color.x * 255) + (unsigned int)(_color.y * (65280U)) + (unsigned int)(_color.z * 16711680U) + (unsigned int)(_color.w * 4278190080U);
							}
							else {
								_colort = (unsigned int)(_color.z * 255) + (unsigned int)(_color.y * (65280U)) + (unsigned int)(_color.x * 16711680U) + (unsigned int)(_color.w * 4278190080U);
							}
							_renderer.renderer.blitrectcolor(*text.font->getTex(), _textx + _Txpos, text.pos.y + _Tline * (text.font->getFullHeight() + text.font->getSepWidth()) - _texty, ((text.string[i] - text.font->getStartChar()) % 16) * text.font->getFullWidth(), int((text.string[i] - text.font->getStartChar()) / 16) * text.font->getFullHeight(), text.font->getWidth(text.string[i]), text.font->getFullHeight(), _colort);
							//}
						}

						_Txpos = _Txpos + (text.font->getWidth(text.string[i]) + text.font->getSepWidth());
						_Tpos++;

						_collecttext += text.string[i];

					}
					else {
						if (text.string[i] == ' ') {
							_Txpos = _Txpos + text.font->getSpaceWidth();
							_Tpos++;
							_collecttext += text.string[i];
							//_Tfunc = _Tfunc + text[i];
							//_Tex++;
						}
						if (_Tfunc == TextFunc::Func) {
							switch (text.string[i]) {
							default: {
								_Tfunc = TextFunc::None;
								break;
							}
							case '~': {
								break;
							}
							case 'r': {
								_color = Color(255, 255, 255, 255);
								_Tfunc = TextFunc::None;
								break;
							}
							case '&': {
								_Tfunc = TextFunc::ColorTag;
								break;
							}
									  //hex input
							case '#': {
								_Tfunc = TextFunc::ColorHex;
								break;
							}
							}
							continue;
						}
						if (_Tfunc == TextFunc::ColorTag) {
							switch (text.string[i]) {
							default: {
								_color = Color(255, 255, 255, 255);
								_Tfunc = TextFunc::None;
								break;
							}
							case '0': {
								_color = Color(0, 0, 0, 255);
								_Tfunc = TextFunc::None;
								break;
							}
							case '~': {
								break;
							}
							case '1': {
								_color = Color(255, 255, 0, 255);
								_Tfunc = TextFunc::None;
								break;
							}
							case '2': {
								_color = Color(0, 255, 0, 255);
								_Tfunc = TextFunc::None;
								break;
							}
							case '3': {
								_color = Color(0, 255, 255, 255);
								_Tfunc = TextFunc::None;
								break;
							}
							case '4': {
								_color = Color(0, 0, 255, 255);
								_Tfunc = TextFunc::None;
								break;
							}
							case '5': {
								_color = Color(255, 0, 255, 255);
								_Tfunc = TextFunc::None;
								break;
							}
							case '6': {
								_color = Color(255, 0, 0, 255);
								_Tfunc = TextFunc::None;
								break;
							}
							case '7': {
								_color = Color(63, 63, 63, 255);
								_Tfunc = TextFunc::None;
								break;
							}
							case '8': {
								_color = Color(127, 127, 127, 255);
								_Tfunc = TextFunc::None;
								break;
							}
							case '9': {
								_color = Color(191, 191, 191, 255);
								_Tfunc = TextFunc::None;
								break;
							}
							case 'r': {
								_color = Color(255, 255, 255, 255);
								_Tfunc = TextFunc::None;
								break;
							}
							case 'G': {
								_color = Color(0, 255, 0, 255);
								_Tfunc = TextFunc::None;
								break;
							}
							}
							//_color = _Tcolor;
							continue;
						}
						if (_Tfunc == TextFunc::ColorHex) {
							if (_hexl == 0) {
								_Tcolor = Color(0, 0, 0, 255);
							}
							_hexl++;
							if (_hexl == 1) {
								_Tcolor.r() += hexchar(text.string[i]) * 16;
							}
							if (_hexl == 2) {
								_Tcolor.r() += hexchar(text.string[i]) * 1;
							}
							if (_hexl == 3) {
								_Tcolor.g() += hexchar(text.string[i]) * 16;
							}
							if (_hexl == 4) {
								_Tcolor.g() += hexchar(text.string[i]) * 1;
							}
							if (_hexl == 5) {
								_Tcolor.b() += hexchar(text.string[i]) * 16;
							}
							if (_hexl == 6) {
								_Tcolor.b() += hexchar(text.string[i]) * 1;
								_Tfunc = TextFunc::None;
								_hexl = 0;
								_color = _Tcolor;
							}
						}
					}
				}
				return;
			}
			if (text.align == Text::Center) {
				int _textx = 0;

				for (int i = 0;i < _length;i++) {
					if (text.warp) {
						if (_Txpos > text.warp) {
							if (text.warpchar) {
								if (text.string[i] == text.warpchar) {
									_Tline++;
									//_Tex++;
									_Tpos = 0;
									_Txpos = 0;
								}
							}
							else {
								_Tline++;
								//_Tex++;
								_Tpos = 0;
								_Txpos = 0;
							}
						}
					}
					if (!_Txpos) {
						float _linewidth = text.LineWidth(i);
						if (_linewidth > text.warp) {
							_textx = text.pos.x - (text.warp / 2);
						}
						else {
							_textx = text.pos.x - (_linewidth / 2);
						}

					}
					if (text.string[i] == '\n') {
						_Tline++;
						//_Tex++;
						_Tpos = 0;
						_Txpos = 0;
					}
					if (text.string[i] == '~') {
						if (_Tfunc == TextFunc::Func) {
							_Tfunc = TextFunc::None;
						}
						else {
							_Tfunc = TextFunc::Func;
						}
					}
					_Tdraw = _Tfunc == (TextFunc::None);
					if ((text.string[i] != ' ') && (text.string[i] != '\n') && (_Tdraw)) {

						if (_renderer.hglrc != NULL) {
							float Rx = _textx + _Txpos;
							float Ry = text.pos.y + _Tline * (text.font->getFullHeight() + text.font->getSepWidth()) - _texty;
							//Shader MShader("Texture.vs", "Texture.fs");
							//std::cout << (TSH) << "," << (DrawTargetHeight) << "," << DrawTarget << "," << (float(DrawTargetHeight) / (ScreenH)) << "\n";
							float Rw = float(((text.font->getWidth(text.string[i]))));
							float Rh = float(((text.font->getFullHeight())));
							float RTx = float(((text.string[i] - text.font->getStartChar()) % 16) * text.font->getFullWidth()) / text.font->getTex()->getSize().x;
							float RTy = float(int((text.string[i] - text.font->getStartChar()) / 16) * text.font->getFullHeight()) / text.font->getTex()->getSize().y;
							float RTw = float(text.font->getWidth(text.string[i])) / text.font->getTex()->getSize().x;
							float RTh = (float(text.font->getFullHeight()) / text.font->getTex()->getSize().y);

							float _buffer[] = {
								// positions				// colors					// texture coords
								(Rx),  Ry,				0, _color.x, _color.y, _color.z, _color.w,	RTx		 ,1.0f - (RTy),					// top left
								((Rx + Rw)), Ry,		0, _color.x, _color.y, _color.z, _color.w,	RTx + RTw,1.0f - (RTy),				// top right
								(Rx),  Ry + Rh,			0, _color.x, _color.y, _color.z, _color.w,	RTx		 ,1.0f - (RTy + RTh),		// bottom left
								((Rx + Rw)), Ry + Rh,	0, _color.x, _color.y, _color.z, _color.w,	RTx + RTw,1.0f - (RTy + RTh)	// bottom right

							};
							//*this << Sprite(*text.font->getTex(), ((text.string[i] - text.font->getStartChar()) % 16) * text.font->getFullWidth(), int((text.string[i] - text.font->getStartChar()) / 16) * text.font->getFullHeight(), text.font->getWidth(text.string[i]), text.font->getFullHeight(), Rx, Ry, Rw, Rh);
							glBindVertexArray(_renderer.rectvao);
							glBindBuffer(GL_ARRAY_BUFFER, _renderer.rectvbo);

							memcpy(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY), _buffer, sizeof(_buffer));
							glUnmapBuffer(GL_ARRAY_BUFFER);

							glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

						}
						else {
							//if (i == 1) {
							//_textx +
							/*
							renderer.blitrect(*text.font->getTex(),
							(_Txpos) + (text.font->getWidth(text.string[i])),
							(text.pos.y + (_size.y - ((_Tline) * (text.font->getFullHeight() + text.font->getSepWidth())))),
							(((text.string[i] - text.font->getStartChar()) % 16) * text.font->getFullWidth()),
							(int((text.string[i] - text.font->getStartChar()) / 16) * text.font->getFullHeight()),
							(text.font->getWidth(text.string[i])),
							(text.font->getFullHeight()));
							*/
							if (_renderer.hwnd == NULL) {
								_colort = (unsigned int)(_color.x * 255) + (unsigned int)(_color.y * (65280U)) + (unsigned int)(_color.z * 16711680U) + (unsigned int)(_color.w * 4278190080U);
							}
							else {
								_colort = (unsigned int)(_color.z * 255) + (unsigned int)(_color.y * (65280U)) + (unsigned int)(_color.x * 16711680U) + (unsigned int)(_color.w * 4278190080U);
							}
							_renderer.renderer.blitrectcolor(*text.font->getTex(), _textx + _Txpos, text.pos.y + _Tline * (text.font->getFullHeight() + text.font->getSepWidth()) - _texty, ((text.string[i] - text.font->getStartChar()) % 16) * text.font->getFullWidth(), int((text.string[i] - text.font->getStartChar()) / 16) * text.font->getFullHeight(), text.font->getWidth(text.string[i]), text.font->getFullHeight(), _colort);
							//}
						}

						_Txpos = _Txpos + ((text.font->getWidth(text.string[i]) + text.font->getSepWidth()));
						_Tpos++;

						_collecttext += text.string[i];

					}
					else {
						if (text.string[i] == ' ') {
							_Txpos = _Txpos + text.font->getSpaceWidth();
							_Tpos++;
							_collecttext += text.string[i];
							//_Tfunc = _Tfunc + text[i];
							//_Tex++;
						}
						if (_Tfunc == TextFunc::Func) {
							switch (text.string[i]) {
							default: {
								_Tfunc = TextFunc::None;
								break;
							}
							case '~': {
								break;
							}
							case 'r': {
								_color = Color(255, 255, 255, 255);
								_Tfunc = TextFunc::None;
								break;
							}
							case '&': {
								_Tfunc = TextFunc::ColorTag;
								break;
							}
									  //hex input
							case '#': {
								_Tfunc = TextFunc::ColorHex;
								break;
							}
							}
							continue;
						}
						if (_Tfunc == TextFunc::ColorTag) {
							switch (text.string[i]) {
							default: {
								_color = Color(255, 255, 255, 255);
								_Tfunc = TextFunc::None;
								break;
							}
							case '0': {
								_color = Color(0, 0, 0, 255);
								_Tfunc = TextFunc::None;
								break;
							}
							case '~': {
								break;
							}
							case '1': {
								_color = Color(255, 255, 0, 255);
								_Tfunc = TextFunc::None;
								break;
							}
							case '2': {
								_color = Color(0, 255, 0, 255);
								_Tfunc = TextFunc::None;
								break;
							}
							case '3': {
								_color = Color(0, 255, 255, 255);
								_Tfunc = TextFunc::None;
								break;
							}
							case '4': {
								_color = Color(0, 0, 255, 255);
								_Tfunc = TextFunc::None;
								break;
							}
							case '5': {
								_color = Color(255, 0, 255, 255);
								_Tfunc = TextFunc::None;
								break;
							}
							case '6': {
								_color = Color(255, 0, 0, 255);
								_Tfunc = TextFunc::None;
								break;
							}
							case '7': {
								_color = Color(63, 63, 63, 255);
								_Tfunc = TextFunc::None;
								break;
							}
							case '8': {
								_color = Color(127, 127, 127, 255);
								_Tfunc = TextFunc::None;
								break;
							}
							case '9': {
								_color = Color(191, 191, 191, 255);
								_Tfunc = TextFunc::None;
								break;
							}
							case 'r': {
								_color = Color(255, 255, 255, 255);
								_Tfunc = TextFunc::None;
								break;
							}
							case 'G': {
								_color = Color(0, 255, 0, 255);
								_Tfunc = TextFunc::None;
								break;
							}
							}
							//_color = _Tcolor;
							continue;
						}
						if (_Tfunc == TextFunc::ColorHex) {
							if (_hexl == 0) {
								_Tcolor = Color(0, 0, 0, 255);
							}
							_hexl++;
							if (_hexl == 1) {
								_Tcolor.r() += hexchar(text.string[i]) * 16;
							}
							if (_hexl == 2) {
								_Tcolor.r() += hexchar(text.string[i]) * 1;
							}
							if (_hexl == 3) {
								_Tcolor.g() += hexchar(text.string[i]) * 16;
							}
							if (_hexl == 4) {
								_Tcolor.g() += hexchar(text.string[i]) * 1;
							}
							if (_hexl == 5) {
								_Tcolor.b() += hexchar(text.string[i]) * 16;
							}
							if (_hexl == 6) {
								_Tcolor.b() += hexchar(text.string[i]) * 1;
								_Tfunc = TextFunc::None;
								_hexl = 0;
								_color = _Tcolor;
							}
						}
					}
				}
				return;
			}
		}

		Text Textbox::getText() {
			return text;
		}
		void Textbox::setText(Text text) {
			if (text != text) {
				text = text;
				redraw();
			}
		}
		void Textbox::setTextString(std::string Tstring) {
			if (text.string != Tstring) {
				text.string = Tstring;
				redraw();
			}
		}

		Sprite Textbox::getSprite() {
			return backgroundsprite;
		}
		void Textbox::setSprite(Sprite Tsprite) {
			if (backgroundsprite != Tsprite) {
				backgroundsprite = Tsprite;
				redraw();
			}
		}

		Color Textbox::getBackgroundColor() {
			return bgcolor;
		}
		void Textbox::setBackgroundColor(Color Tcolor) {
			if (bgcolor != Tcolor) {
				bgcolor = Tcolor;
				redraw();
			}
		}

		int Textbox::getBorderThickness() {
			return borderthickness;
		}
		void Textbox::setBorderThickness(int Tint) {
			if (borderthickness != Tint) {
				borderthickness = Tint;
				redraw();
			}
		}

		Color Textbox::getBorderColor() {
			return bordercolor;
		}
		void Textbox::setBorderColor(Color Tcolor) {
			if (bordercolor != Tcolor) {
				bordercolor = Tcolor;
				redraw();
			}
		}

		bool Textbox::getMultiline() {
			return multiline;
		}
		void Textbox::setMultiline(bool Tbool) {
			multiline = Tbool;
		}
		std::string Textbox::getFilter() {
			return filter;
		}
		void Textbox::setFilter(std::string Tstring) {
			filter = Tstring;
		}
		int Textbox::getMaxlength() {
			return maxlength;
		}
		void Textbox::setMaxlength(int Tint) {
			maxlength = Tint;
		}
		char Textbox::getCoverchar() {
			return coverchar;
		}
		void Textbox::setCoverchar(char Tchar) {
			coverchar = Tchar;
		}
		bool Textbox::getReadonly() {
			return readonly;
		}
		void Textbox::setReadonly(bool Tbool) {
			readonly = Tbool;
		}

		int Textbox::getTabIndex() {
			return tab;
		}
		void Textbox::setTabIndex(int Tint) {
			tab = Tint;
		}
		bool Textbox::getWordwrap() {
			return wordwrap;
		}
		void Textbox::setWordwrap(bool Tbool) {
			wordwrap = Tbool;
		}

		bool Textbox::getMouseEntered() {
			return mouseentered;
		}

		void Textbox::requestRedraw() {
			requestredraw = 1;
		}

		void Textbox::gainFocus() {
			if (!focus) {
				if (currentfocus) {
					currentfocus->focus = 0;
				}

				SetTimer(manager->getrenderer()->hwnd, 1000, textboxmarkerblinkelapse, NULL);

				focus = 1;
				currentfocus = this;
			}
		}
		void Textbox::killFocus() {
			KillTimer(manager->getrenderer()->hwnd, 1000);

			focus = 0;
			currentfocus = NULL;
		}
		bool Textbox::getFocus() {
			return focus;
		}

		int Textbox::getPosition(Point<int> Tpoint) {
			int _length = text.string.length();
			float _Twidth = 0;
			float _Theight = 0;

			int _index = 0;

			bool skipline = 0;

			if (Tpoint.x < 0) {
				return 0;
			}

			int _hexl = 0;

			TextFunc _Tfunc = TextFunc::None;
			bool _Tdraw = 0;

			if ((Tpoint.y > _Theight + ((text.font->getFullHeight() + text.font->getSepWidth()))) ||
				(Tpoint.y < _Theight)) {
				skipline = 1;
			}
			else {
				skipline = 0;
			}

			int _line = 0;

			bool _check = 0;

			for (int i = 0;i < _length;i++) {
				if (text.string[i] == '\n') {
					if (!skipline) {
						std::cout << "SKIPPED\n";
						return i;
					}
					_Twidth = 0;
					float _TPheight = _Theight;
					_Theight += (text.font->getFullHeight() + text.font->getSepWidth());
					if ((Tpoint.y > _Theight + ((text.font->getFullHeight() + text.font->getSepWidth()))) ||
						(Tpoint.y < _Theight)) {
						skipline = 1;
					}
					else {
						skipline = 0;
					}

					i++;
					_line++;
					//return i;
				}
				if (skipline) {
					continue;
				}
				if (text.string[i] == '~') {
					if (_Tfunc == TextFunc::Func) {
						_Tfunc = TextFunc::None;
					}
					else {
						_Tfunc = TextFunc::Func;
					}
				}

				_Tdraw = _Tfunc == (TextFunc::None);
				if ((text.string[i] != ' ') && (_Tdraw)) {
					float _TPwidth = _Twidth;
					_Twidth += (text.font->getWidth(text.string[i]) + text.font->getSepWidth());
					if (Tpoint.x < _TPwidth + ((text.font->getWidth(text.string[i]) + text.font->getSepWidth()) / 2.0f)) {
						return i;
					}
					_index = i;
				}
				else {
					if (text.string[i] == ' ') {
						float _TPwidth = _Twidth;
						_Twidth += (text.font->getSpaceWidth());
						if (Tpoint.x < _TPwidth + ((text.font->getSpaceWidth()) / 2.0f)) {
							return i;
							_index = i;
						}
					}
					if (_Tfunc == TextFunc::ColorTag) {
						if (text.string[i] != '~') {
							_Tfunc = TextFunc::None;
						}
					}
					if (_Tfunc == TextFunc::Func) {
						switch (text.string[i]) {
						default: {
							_Tfunc = TextFunc::None;
							break;
						}
						case '~': {
							break;
						}
						case '&': {
							_Tfunc = TextFunc::ColorTag;
							break;
						}
								  //hex input
						case '#': {
							_Tfunc = TextFunc::ColorHex;
							break;
						}
						}
						continue;
					}
					if (_Tfunc == TextFunc::ColorTag) {
						switch (text.string[i]) {
						default:
						case '0':
						case '1':
						case '2':
						case '3':
						case '4':
						case '5':
						case '6':
						case '7':
						case '8':
						case '9':
						case 'r':
						case 'G': {
							_Tfunc = TextFunc::None;
							break;
						}
						case '~': {
							break;
						}
						}
						continue;
					}
					if (_Tfunc == TextFunc::ColorHex) {
						_hexl++;
						if (_hexl == 6) {
							_Tfunc = TextFunc::None;
							_hexl = 0;
						}
					}
				}
			}

			

			if (!skipline) {
				//std::cout << "SKIPPED\n";
				return _length;
			}

			return _index;
		}

		void Textbox::setFocusTo(Textbox* Ttextbox) {
			if (!Ttextbox->focus) {
				if (currentfocus) {
					currentfocus->focus = 0;
				}

				SetTimer(Ttextbox->manager->getrenderer()->hwnd, 1000, textboxmarkerblinkelapse, NULL);

				Ttextbox->focus = 1;
				currentfocus = Ttextbox;
			}
		}
		void Textbox::requestRedrawAll() {
			requestredrawall = 1;
		}
		Textbox* Textbox::getCurrentFocus() {
			return currentfocus;
		}
		void Textbox::killCurrentFocus() {
			if (currentfocus) {
				KillTimer(currentfocus->manager->getrenderer()->hwnd, 1000);

				currentfocus->focus = 0;
				currentfocus = NULL;
			}
		}
	}
}