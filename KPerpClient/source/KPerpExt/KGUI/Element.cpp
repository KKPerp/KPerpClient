#include <KPerpExt/KGUI/Element.hpp>
#include <KPerpCore/CritSection.hpp>

#include <KPerpExt/KGUI/Button.hpp>
#include <KPerpExt/KGUI/Label.hpp>
#include <KPerpExt/KGUI/Textbox.hpp>

#include <time.h>

namespace kp {
	namespace KGui {
		Dock::Dock() {
			point = Auto;
			element = NULL;
			pos = { 0,0 };
			autopoint = 0;
		}
		Dock::Dock(Corner Tauto) {
			if (Tauto == Dock::Auto) {
				point = Dock::Auto;
				element = Dock::Window;

				autopoint = 1;
			}
		}
		Dock::Dock(Corner Tauto, unsigned int Telement) {
			if (Tauto == Dock::Auto) {
				point = Dock::Auto;
				element = Telement;

				autopoint = 1;
			}
		}
		Dock::Dock(Corner Tauto, Corner Tcorner) {
			if (Tauto == Dock::Auto) {
				point = Tcorner;
				element = Dock::Window;

				autopoint = 1;
			}
		}
		Dock::Dock(Corner Tauto, Corner Tcorner, unsigned int Telement) {
			if (Tauto == Dock::Auto) {
				point = Tcorner;
				element = Dock::Window;

				autopoint = 1;
			}
		}
		Dock::Dock(Point<int> Tpos) {
			point = Auto;
			element = Dock::Window;
			pos = Tpos;
			autopoint = 0;
		}
		Dock::Dock(unsigned int Telement, Point<int> Tpos) {
			point = Auto;
			element = Telement;
			pos = Tpos;
			autopoint = 0;
		}
		Dock::Dock(Corner Tcorner, unsigned int Telement, Point<int> Tpos) {
			point = Tcorner;
			element = Telement;
			pos = Tpos;
			autopoint = 0;
		}

		Element::Element() {
			drawable = 0;
		}

		void Element::create() {

		}
		void Element::destroy() {

		}
		void Element::step() {

		}
		void Element::draw() {

		}

		void Instance::initsurface() {
			surface = new Texture(*manager->getrenderer(),(rect.c.x - rect.a.x)+1, (rect.c.y - rect.a.y) + 1);
			redraw();
		}

		void Instance::redraw() {
			if (surface != NULL) {
				if (manager->getrenderer()->isDestructing()) {
					return;
				}
				manager->getrenderer()->setTarget(*surface);
				(*manager->getrenderer()) << 0;
				switch (type) {
				case Type::Button: {
					Button& _button = *((Button*)this);
					Rectangle<int> _ppos = _button.rect;

					_button.backgroundsprite.rect.a.x = _button.rect.a.x;
					_button.backgroundsprite.rect.a.y = _button.rect.a.y;
					_button.backgroundsprite.rect.c.x = _button.rect.c.x;
					_button.backgroundsprite.rect.c.y = _button.rect.c.y;
					
					Sprite _sprite = _button.getSprite();

					_sprite.rect.a.x = 0;
					_sprite.rect.a.y = 0;
					_sprite.rect.c.x = _button.rect.c.x - _button.rect.a.x;
					_sprite.rect.c.y = _button.rect.c.y - _button.rect.a.y;

					if (_sprite.texture == NULL) {
						manager->getrenderer()->UseSolidTexture();
					}

					if (_button.bgcolor.a() != 0) {
						(*manager->getrenderer()) << _sprite;
					}

					if (_button.borderthickness != 0) {
						manager->getrenderer()->UseSolidTexture();
						for (int i = 0;i < _button.borderthickness;i++) {
							(*manager->getrenderer()) << Drawing::Rectangle(
								{ _sprite.rect.a.x - (i),_sprite.rect.a.y - (i),0 },
								{ _sprite.rect.c.x + (i),_sprite.rect.c.y + (i),0 },
								_button.bordercolor, _button.bordercolor, _button.bordercolor, _button.bordercolor,
								_sprite.rect.t1, _sprite.rect.t2,
								_sprite.rect.t3, _sprite.rect.t4, 0
							);
						}
					}

					if (_button.text.align == Text::Left) {
						_button.text.pos.x = _button.padding.a.x;// +((_button.rect.c.x - _button.rect.a.x) / 2);
					}
					else {
						if (_button.text.align == Text::Center) {
							_button.text.pos.x = _button.padding.a.x + (((_button.rect.c.x - _button.rect.a.x) - _button.padding.a.x - _button.padding.c.x) / 2);
						}
						else {
							if (_button.text.align == Text::Right) {
								_button.text.pos.x = ((_button.rect.c.x - _button.rect.a.x) - _button.padding.c.x);
							}
						}
					}
					if (_button.text.valign == Text::Top) {
						_button.text.pos.y = _button.padding.a.y;//_button.rect.a.y;// +((_button.rect.c.x - _button.rect.a.x) / 2);
					}
					else {
						if (_button.text.valign == Text::Center) {
							_button.text.pos.y = _button.padding.a.y + (((_button.rect.c.y - _button.rect.a.y) - _button.padding.a.y - _button.padding.c.y) / 2);
						}
						else {
							if (_button.text.valign == Text::Bottom) {
								_button.text.pos.y = ((_button.rect.c.y - _button.rect.a.y) - _button.padding.c.y);
							}
						}
					}

					_button.text.warp = (_sprite.rect.c.x - _sprite.rect.a.x) - 4 - (_button.borderthickness * 2) - _button.padding.a.x - _button.padding.c.x;
					(*manager->getrenderer()) << _button.text;
					break;
				}
				case Type::Label: {
					Label& _label = *((Label*)this);
					Rectangle<int> _ppos = _label.rect;

					_label.backgroundsprite.rect.a.x = _label.rect.a.x;
					_label.backgroundsprite.rect.a.y = _label.rect.a.y;
					_label.backgroundsprite.rect.c.x = _label.rect.c.x;
					_label.backgroundsprite.rect.c.y = _label.rect.c.y;
					
					Sprite _sprite = _label.getSprite();

					_sprite.rect.a.x = 0;
					_sprite.rect.a.y = 0;
					_sprite.rect.c.x = _label.rect.c.x - _label.rect.a.x;
					_sprite.rect.c.y = _label.rect.c.y - _label.rect.a.y;

					if (_sprite.texture == NULL) {
						manager->getrenderer()->UseSolidTexture();
					}

					if (_label.bgcolor.a() != 0) {
						(*manager->getrenderer()) << _sprite;
					}

					if (_label.borderthickness != 0) {
						manager->getrenderer()->UseSolidTexture();
						for (int i = 0;i < _label.borderthickness;i++) {
							(*manager->getrenderer()) << Drawing::Rectangle(
								{ _sprite.rect.a.x - (i),_sprite.rect.a.y - (i),0 },
								{ _sprite.rect.c.x + (i),_sprite.rect.c.y + (i),0 },
								_label.bordercolor, _label.bordercolor, _label.bordercolor, _label.bordercolor,
								_sprite.rect.t1, _sprite.rect.t2,
								_sprite.rect.t3, _sprite.rect.t4, 0
							);
						}
					}

					if (_label.text.align == Text::Left) {
						_label.text.pos.x = _label.padding.a.x;// +((_label.rect.c.x - _label.rect.a.x) / 2);
					}
					else {
						if (_label.text.align == Text::Center) {
							_label.text.pos.x = _label.padding.a.x + (((_label.rect.c.x - _label.rect.a.x) - _label.padding.a.x - _label.padding.c.x) / 2);
						}
						else {
							if (_label.text.align == Text::Right) {
								_label.text.pos.x = ((_label.rect.c.x - _label.rect.a.x) - _label.padding.c.x);
							}
						}
					}
					if (_label.text.valign == Text::Top) {
						_label.text.pos.y = _label.padding.a.y;//_label.rect.a.y;// +((_label.rect.c.x - _label.rect.a.x) / 2);
					}
					else {
						if (_label.text.valign == Text::Center) {
							_label.text.pos.y = _label.padding.a.y + (((_label.rect.c.y - _label.rect.a.y) - _label.padding.a.y - _label.padding.c.y) / 2);
						}
						else {
							if (_label.text.valign == Text::Bottom) {
								_label.text.pos.y = ((_label.rect.c.y - _label.rect.a.y) - _label.padding.c.y);
							}
						}
					}

					_label.text.warp = (_sprite.rect.c.x - _sprite.rect.a.x) - 4 - (_label.borderthickness * 2) - _label.padding.a.x - _label.padding.c.x;
					(*manager->getrenderer()) << _label.text;
					break;
				}
				case Type::Textbox: {
					Textbox& _textbox = *((Textbox*)this);
					Rectangle<int> _ppos = _textbox.rect;

					_textbox.backgroundsprite.rect.a.x = _textbox.rect.a.x;
					_textbox.backgroundsprite.rect.a.y = _textbox.rect.a.y;
					_textbox.backgroundsprite.rect.c.x = _textbox.rect.c.x;
					_textbox.backgroundsprite.rect.c.y = _textbox.rect.c.y;

					Sprite _sprite = _textbox.getSprite();

					_sprite.rect.a.x = 0;
					_sprite.rect.a.y = 0;
					_sprite.rect.c.x = _textbox.rect.c.x - _textbox.rect.a.x;
					_sprite.rect.c.y = _textbox.rect.c.y - _textbox.rect.a.y;
					
					if (_sprite.texture == NULL) {
						manager->getrenderer()->UseSolidTexture();
					}

					if (_textbox.bgcolor.a() != 0) {
						(*manager->getrenderer()) << _sprite;
					}

					if (_textbox.borderthickness != 0) {
						manager->getrenderer()->UseSolidTexture();
						for (int i = 0;i < _textbox.borderthickness;i++) {
							(*manager->getrenderer()) << Drawing::Rectangle(
								{ _sprite.rect.a.x - (i),_sprite.rect.a.y - (i),0 },
								{ _sprite.rect.c.x + (i),_sprite.rect.c.y + (i),0 },
								_textbox.bordercolor, _textbox.bordercolor, _textbox.bordercolor, _textbox.bordercolor,
								_sprite.rect.t1, _sprite.rect.t2,
								_sprite.rect.t3, _sprite.rect.t4, 0
							);
						}
					}

					if (_textbox.text.align == Text::Left) {
						_textbox.text.pos.x = _textbox.padding.a.x;// +((_textbox.rect.c.x - _textbox.rect.a.x) / 2);
					}
					else {
						if (_textbox.text.align == Text::Center) {
							_textbox.text.pos.x = _textbox.padding.a.x + (((_textbox.rect.c.x - _textbox.rect.a.x) - _textbox.padding.a.x - _textbox.padding.c.x) / 2);
						}
						else {
							if (_textbox.text.align == Text::Right) {
								_textbox.text.pos.x = ((_textbox.rect.c.x - _textbox.rect.a.x) - _textbox.padding.c.x);
							}
						}
					}
					if (_textbox.text.valign == Text::Top) {
						_textbox.text.pos.y = _textbox.padding.a.y;//_textbox.rect.a.y;// +((_textbox.rect.c.x - _textbox.rect.a.x) / 2);
					}
					else {
						if (_textbox.text.valign == Text::Center) {
							_textbox.text.pos.y = _textbox.padding.a.y + (((_textbox.rect.c.y - _textbox.rect.a.y) - _textbox.padding.a.y - _textbox.padding.c.y) / 2);
						}
						else {
							if (_textbox.text.valign == Text::Bottom) {
								_textbox.text.pos.y = ((_textbox.rect.c.y - _textbox.rect.a.y) - _textbox.padding.c.y);
							}
						}
					}

					_textbox.text.pos.x -= _textbox.xseek;
					_textbox.text.pos.y -= _textbox.yseek;
					std::cout << "Drawing...\n";
					_textbox.text.warp = (_textbox.wordwrap) ?
						(_sprite.rect.c.x - _sprite.rect.a.x) - 4 - (_textbox.borderthickness * 2) - _textbox.padding.a.x - _textbox.padding.c.x :
						0;
					//(*manager->getrenderer()) << _textbox.text;
					_textbox.drawtext();

					if (Textbox::textboxmarker) {
						std::cout << "Draw Line\n";
						//manager->getrenderer()->;
					}

					break;
				}
				}
				manager->getrenderer()->resetTarget();
			}
		}

		void Instance::reset() {
			if (surface != NULL) {
				delete surface;
				surface = NULL;
				surface = new Texture(*manager->getrenderer(), (rect.c.x - rect.a.x) + 1, (rect.c.y - rect.a.y) + 1);
			}
		}

		Instance::Instance() {
			drawable = 1;
		}

		Rectangle<int> Instance::getRect() {
			return rect;
		}

		Instance::~Instance() {
			if (surface != NULL) {
				delete surface;
				surface = NULL;
			}
		}

		void Instance::create() {

		}
		void Instance::destroy() {

		}
		void Instance::step() {

		}
		void Instance::draw() {

		}
	}
}