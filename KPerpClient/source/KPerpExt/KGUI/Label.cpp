#include <KPerpExt/KGUI/Label.hpp>
#include <KPerpCore/Graphic.hpp>

namespace kp {
	namespace KGui {
		Label::Label() {

		}
		Label::Label(Element* Tparent, Rectangle<int> Trect, Text Ttext, Callback<Label> Tcallback,
			Color Tbackcolor, Color Tbordercolor, int Tborderthickness, const Sprite& Tsprite,
			Rectangle<int> Tpadding, Dock Ttldock, Dock Ttrdock, Dock Tbldock, Dock Tbrdock) {
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

			mouseentered = 0;
			pressed[0] = 0;
			pressed[1] = 0;
			pressed[2] = 0;

			type = Type::Label;

			create();
		}

		Label::~Label() {
			destroy();
		}

		void Label::create() {

		}
		void Label::destroy() {

		}
		void Label::step() {

		}
		void Label::draw() {

		}

		Text Label::getText() {
			return text;
		}
		void Label::setText(Text Ttext) {
			if (text != Ttext) {
				text = Ttext;
				redraw();
			}
		}
		void Label::setTextString(std::string Tstring) {
			if (text.string != Tstring) {
				text.string = Tstring;
				redraw();
			}
		}

		Sprite Label::getSprite() {
			return backgroundsprite;
		}
		void Label::setSprite(Sprite Tsprite) {
			if (backgroundsprite != Tsprite) {
				backgroundsprite = Tsprite;
				redraw();
			}
		}

		Color Label::getBackgroundColor() {
			return bgcolor;
		}
		void Label::setBackgroundColor(Color Tcolor) {
			if (bgcolor != Tcolor) {
				bgcolor = Tcolor;
				redraw();
			}
		}

		int Label::getBorderThickness() {
			return borderthickness;
		}
		void Label::setBorderThickness(int Tint) {
			if (borderthickness != Tint) {
				borderthickness = Tint;
				redraw();
			}
		}

		Color Label::getBorderColor() {
			return bordercolor;
		}
		void Label::setBorderColor(Color Tcolor) {
			if (bordercolor != Tcolor) {
				bordercolor = Tcolor;
				redraw();
			}
		}

		bool Label::getMouseEntered() {
			return mouseentered;
		}
	}
}