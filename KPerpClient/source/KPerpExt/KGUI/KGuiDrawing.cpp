#include <KPerpCore/Renderer.hpp>
#include <KPerpExt/KGUI/Element.hpp>

#include <KPerpExt/KGUI/Button.hpp>
#include <KPerpExt/KGUI/Label.hpp>
#include <KPerpExt/KGUI/Textbox.hpp>

namespace kp {
	using namespace KGui;
	Renderer& Renderer::operator<< (Instance& Tinst) {
		switch (Tinst.type) {
		case Type::Button: {
			Button& _button = *((Button*)&Tinst);
			_button.backgroundsprite.rect.a.x = _button.rect.a.x;
			_button.backgroundsprite.rect.a.y = _button.rect.a.y;
			_button.backgroundsprite.rect.c.x = _button.rect.c.x;
			_button.backgroundsprite.rect.c.y = _button.rect.c.y;

			if (_button.backgroundsprite.texture == NULL) {
				UseSolidTexture();
			}

			*this << _button.backgroundsprite;

			if (_button.borderthickness != 0) {
				UseSolidTexture();
				for (int i = 0;i < _button.borderthickness;i++) {
					*this << Drawing::Rectangle(
						{ _button.backgroundsprite.rect.a.x - (i),_button.backgroundsprite.rect.a.y - (i),0 },
						{ _button.backgroundsprite.rect.c.x + (i),_button.backgroundsprite.rect.c.y + (i),0 },
						_button.bordercolor, _button.bordercolor, _button.bordercolor, _button.bordercolor,
						_button.backgroundsprite.rect.t1, _button.backgroundsprite.rect.t2,
						_button.backgroundsprite.rect.t3, _button.backgroundsprite.rect.t4, 0
					);
				}
			}

			if (_button.text.align == Text::Left) {
				_button.text.pos.x = (_button.backgroundsprite.rect.a.x + _button.padding.a.x);// +((_button.backgroundsprite.rect.c.x - _button.backgroundsprite.rect.a.x) / 2);
			}
			else {
				if (_button.text.align == Text::Center) {
					_button.text.pos.x = (_button.backgroundsprite.rect.a.x + _button.padding.a.x) + (((_button.backgroundsprite.rect.c.x - _button.backgroundsprite.rect.a.x) - _button.padding.a.x - _button.padding.c.x) / 2);
				}
				else {
					if (_button.text.align == Text::Right) {
						_button.text.pos.x = (_button.backgroundsprite.rect.c.x - _button.padding.a.x - _button.padding.c.x);
					}
				}
			}
			if (_button.text.valign == Text::Top) {
				_button.text.pos.y = (_button.backgroundsprite.rect.a.y + _button.padding.a.y);// +((_button.backgroundsprite.rect.c.x - _button.backgroundsprite.rect.a.x) / 2);
			}
			else {
				if (_button.text.valign == Text::Center) {
					_button.text.pos.y = (_button.backgroundsprite.rect.a.y + _button.padding.a.y) + (((_button.backgroundsprite.rect.c.y - _button.backgroundsprite.rect.a.y) - _button.padding.a.y - _button.padding.c.y) / 2);
				}
				else {
					if (_button.text.valign == Text::Bottom) {
						_button.text.pos.y = (_button.backgroundsprite.rect.c.y - _button.padding.a.y - _button.padding.c.y);
					}
				}
			}
			//_button.text.pos.y = _button.backgroundsprite.rect.a.y;// +((_button.backgroundsprite.rect.c.y - _button.backgroundsprite.rect.a.y) / 2);

			_button.text.warp = (_button.backgroundsprite.rect.c.x - _button.backgroundsprite.rect.a.x) - 4 - (_button.borderthickness * 2) - _button.padding.a.x - _button.padding.c.x;
			*this << _button.text;

			break;
		}
		case Type::Label: {
			Label& _label = *((Label*)&Tinst);
			_label.backgroundsprite.rect.a.x = _label.rect.a.x;
			_label.backgroundsprite.rect.a.y = _label.rect.a.y;
			_label.backgroundsprite.rect.c.x = _label.rect.c.x;
			_label.backgroundsprite.rect.c.y = _label.rect.c.y;

			if (_label.backgroundsprite.texture == NULL) {
				UseSolidTexture();
			}

			*this << _label.backgroundsprite;

			if (_label.borderthickness != 0) {
				UseSolidTexture();
				for (int i = 0;i < _label.borderthickness;i++) {
					*this << Drawing::Rectangle(
						{ _label.backgroundsprite.rect.a.x - (i),_label.backgroundsprite.rect.a.y - (i),0 },
						{ _label.backgroundsprite.rect.c.x + (i),_label.backgroundsprite.rect.c.y + (i),0 },
						_label.bordercolor, _label.bordercolor, _label.bordercolor, _label.bordercolor,
						_label.backgroundsprite.rect.t1, _label.backgroundsprite.rect.t2,
						_label.backgroundsprite.rect.t3, _label.backgroundsprite.rect.t4, 0
					);
				}
			}

			if (_label.text.align == Text::Left) {
				_label.text.pos.x = (_label.backgroundsprite.rect.a.x + _label.padding.a.x);// +((_label.backgroundsprite.rect.c.x - _label.backgroundsprite.rect.a.x) / 2);
			}
			else {
				if (_label.text.align == Text::Center) {
					_label.text.pos.x = (_label.backgroundsprite.rect.a.x + _label.padding.a.x) + (((_label.backgroundsprite.rect.c.x - _label.backgroundsprite.rect.a.x) - _label.padding.a.x - _label.padding.c.x) / 2);
				}
				else {
					if (_label.text.align == Text::Right) {
						_label.text.pos.x = (_label.backgroundsprite.rect.c.x - _label.padding.c.x);
					}
				}
			}
			if (_label.text.valign == Text::Top) {
				_label.text.pos.y = (_label.backgroundsprite.rect.a.y + _label.padding.a.y);// +((_label.backgroundsprite.rect.c.x - _label.backgroundsprite.rect.a.x) / 2);
			}
			else {
				if (_label.text.valign == Text::Center) {
					_label.text.pos.y = (_label.backgroundsprite.rect.a.y + _label.padding.a.y) + (((_label.backgroundsprite.rect.c.y - _label.backgroundsprite.rect.a.y) - _label.padding.a.y - _label.padding.c.y) / 2);
				}
				else {
					if (_label.text.valign == Text::Bottom) {
						_label.text.pos.y = (_label.backgroundsprite.rect.c.y - _label.padding.c.y);
					}
				}
			}
			//_label.text.pos.y = _label.backgroundsprite.rect.a.y;// +((_label.backgroundsprite.rect.c.y - _label.backgroundsprite.rect.a.y) / 2);

			_label.text.warp = (_label.backgroundsprite.rect.c.x - _label.backgroundsprite.rect.a.x) - 4 - (_label.borderthickness * 2) - _label.padding.a.x - _label.padding.c.x;
			*this << _label.text;

			break;
		}
		case Type::Textbox: {
			Textbox& _textbox = *((Textbox*)&Tinst);
			_textbox.backgroundsprite.rect.a.x = _textbox.rect.a.x;
			_textbox.backgroundsprite.rect.a.y = _textbox.rect.a.y;
			_textbox.backgroundsprite.rect.c.x = _textbox.rect.c.x;
			_textbox.backgroundsprite.rect.c.y = _textbox.rect.c.y;

			if (_textbox.backgroundsprite.texture == NULL) {
				UseSolidTexture();
			}

			*this << _textbox.backgroundsprite;

			if (_textbox.borderthickness != 0) {
				UseSolidTexture();
				for (int i = 0;i < _textbox.borderthickness;i++) {
					*this << Drawing::Rectangle(
						{ _textbox.backgroundsprite.rect.a.x - (i),_textbox.backgroundsprite.rect.a.y - (i),0 },
						{ _textbox.backgroundsprite.rect.c.x + (i),_textbox.backgroundsprite.rect.c.y + (i),0 },
						_textbox.bordercolor, _textbox.bordercolor, _textbox.bordercolor, _textbox.bordercolor,
						_textbox.backgroundsprite.rect.t1, _textbox.backgroundsprite.rect.t2,
						_textbox.backgroundsprite.rect.t3, _textbox.backgroundsprite.rect.t4, 0
					);
				}
			}

			if (_textbox.text.align == Text::Left) {
				_textbox.text.pos.x = (_textbox.backgroundsprite.rect.a.x + _textbox.padding.a.x);// +((_textbox.backgroundsprite.rect.c.x - _textbox.backgroundsprite.rect.a.x) / 2);
			}
			else {
				if (_textbox.text.align == Text::Center) {
					_textbox.text.pos.x = (_textbox.backgroundsprite.rect.a.x + _textbox.padding.a.x) + (((_textbox.backgroundsprite.rect.c.x - _textbox.backgroundsprite.rect.a.x) - _textbox.padding.a.x - _textbox.padding.c.x) / 2);
				}
				else {
					if (_textbox.text.align == Text::Right) {
						_textbox.text.pos.x = (_textbox.backgroundsprite.rect.c.x - _textbox.padding.c.x);
					}
				}
			}
			if (_textbox.text.valign == Text::Top) {
				_textbox.text.pos.y = (_textbox.backgroundsprite.rect.a.y + _textbox.padding.a.y);// +((_textbox.backgroundsprite.rect.c.x - _textbox.backgroundsprite.rect.a.x) / 2);
			}
			else {
				if (_textbox.text.valign == Text::Center) {
					_textbox.text.pos.y = (_textbox.backgroundsprite.rect.a.y + _textbox.padding.a.y) + (((_textbox.backgroundsprite.rect.c.y - _textbox.backgroundsprite.rect.a.y) - _textbox.padding.a.y - _textbox.padding.c.y) / 2);
				}
				else {
					if (_textbox.text.valign == Text::Bottom) {
						_textbox.text.pos.y = (_textbox.backgroundsprite.rect.c.y - _textbox.padding.c.y);
					}
				}
			}
			//_textbox.text.pos.y = _textbox.backgroundsprite.rect.a.y;// +((_textbox.backgroundsprite.rect.c.y - _textbox.backgroundsprite.rect.a.y) / 2);

			_textbox.text.warp = (_textbox.backgroundsprite.rect.c.x - _textbox.backgroundsprite.rect.a.x) - 4 - (_textbox.borderthickness * 2) - _textbox.padding.a.x - _textbox.padding.c.x;
			*this << _textbox.text;

			break;
		}
		}

		return *this;
	}
	Renderer& Renderer::operator<< (Instance* Tinst) {
		*this << *Tinst;
		return *this;
	}
}