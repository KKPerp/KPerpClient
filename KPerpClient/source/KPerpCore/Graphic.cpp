
#include <KPerpCore/Graphic.hpp>

namespace kp {
	Graphic::Graphic() {

	}
	Graphic::Graphic(const Drawing::VertexArray& Tvertexarray) {
		vertexarray.create(Tvertexarray.getType(), Tvertexarray.getSize());
		vertexarray = Tvertexarray;
	}
	Graphic::Graphic(const Drawing::VertexArray& Tvertexarray, const Texture& Ttexture) {
		vertexarray.create(Tvertexarray.getType(), Tvertexarray.getSize());
		vertexarray = Tvertexarray;

		texture = (Texture*)&Ttexture;
	}

	Drawing::VertexArray& Graphic::getVertexArray() {
		return vertexarray;
	}
	Texture& Graphic::getTexture() {
		return *texture;
	}

	Drawing::VertexArray Graphic::getVertexArray() const {
		return vertexarray;
	}
	Texture Graphic::getTexture() const {
		return *texture;
	}

	VertexColor::VertexColor() {
		a = Vec4(1, 1, 1, 1);
		b = Vec4(1, 1, 1, 1);
		c = Vec4(1, 1, 1, 1);
		d = Vec4(1, 1, 1, 1);
	}
	VertexColor::VertexColor(Color Tcolor) {
		a = Tcolor;
		b = Tcolor;
		c = Tcolor;
		d = Tcolor;
	}
	VertexColor::VertexColor(Vec4 Tvec4) {
		a = Tvec4;
		b = Tvec4;
		c = Tvec4;
		d = Tvec4;
	}
	VertexColor::VertexColor(Color Tcolora, Color Tcolorb, Color Tcolorc, Color Tcolord) {
		a = Tcolora;
		b = Tcolorb;
		c = Tcolorc;
		d = Tcolord;
	}
	VertexColor::VertexColor(Vec4 Tvec4a, Vec4 Tvec4b, Vec4 Tvec4c, Vec4 Tvec4d) {
		a = Tvec4a;
		b = Tvec4b;
		c = Tvec4c;
		d = Tvec4d;
	}

	Transform::Transform() {
		origin = Vec2(0, 0);
		scale = Vec2(1, 1);
		angle = 0;
	}
	Transform::Transform(Vec2 Torigin) {
		origin = Torigin;
		scale = Vec2(1, 1);
		angle = 0;
	}
	Transform::Transform(Vec2 Torigin, Vec2 Tscale) {
		origin = Torigin;
		scale = Tscale;
		angle = 0;
	}
	Transform::Transform(Vec2 Torigin, Vec2 Tscale, float Tangle) {
		origin = Torigin;
		scale = Tscale;
		angle = Tangle;
	}

	Sprite::Sprite() {
		rect.c1 = Vec4(1, 1, 1, 1);
		rect.c2 = Vec4(1, 1, 1, 1);
		rect.c3 = Vec4(1, 1, 1, 1);
		rect.c4 = Vec4(1, 1, 1, 1);
		rect.t1 = Vec2(0, 0);
		rect.t2 = Vec2(1, 0);
		rect.t3 = Vec2(0, 1);
		rect.t4 = Vec2(1, 1);
	}
	Sprite::Sprite(Texture& Ttex) {
		texture = &Ttex;
		rect.c1 = Vec4(1, 1, 1, 1);
		rect.c2 = Vec4(1, 1, 1, 1);
		rect.c3 = Vec4(1, 1, 1, 1);
		rect.c4 = Vec4(1, 1, 1, 1);
		rect.t1 = Vec2(0, 0);
		rect.t2 = Vec2(1, 0);
		rect.t3 = Vec2(0, 1);
		rect.t4 = Vec2(1, 1);
	}
	Sprite::Sprite(Texture& Ttex, Vec2 Tpos) {
		texture = &Ttex;
		rect.a.x = Tpos.x;
		rect.a.y = Tpos.y;
		rect.c.x = Tpos.x + texture->getSize().x;
		rect.c.y = Tpos.y + texture->getSize().y;
		rect.c1 = Vec4(1, 1, 1, 1);
		rect.c2 = Vec4(1, 1, 1, 1);
		rect.c3 = Vec4(1, 1, 1, 1);
		rect.c4 = Vec4(1, 1, 1, 1);
		rect.t1 = Vec2(0, 0);
		rect.t2 = Vec2(1, 0);
		rect.t3 = Vec2(0, 1);
		rect.t4 = Vec2(1, 1);
	}
	Sprite::Sprite(Texture& Ttex, Rectangle<float> Trect) {
		texture = &Ttex;
		rect.a.x = Trect.a.x;
		rect.a.y = Trect.a.y;
		rect.c.x = Trect.c.x + texture->getSize().x;
		rect.c.y = Trect.c.y + texture->getSize().y;
		rect.c1 = Vec4(1, 1, 1, 1);
		rect.c2 = Vec4(1, 1, 1, 1);
		rect.c3 = Vec4(1, 1, 1, 1);
		rect.c4 = Vec4(1, 1, 1, 1);
		rect.t1 = Vec2(0, 0);
		rect.t2 = Vec2(1, 0);
		rect.t3 = Vec2(0, 1);
		rect.t4 = Vec2(1, 1);

	}
	Sprite::Sprite(Texture& Ttex, float Tx, float Ty) {
		texture = &Ttex;
		rect.a.x = Tx;
		rect.a.y = Ty;
		rect.c.x = Tx + texture->getSize().x;
		rect.c.y = Ty + texture->getSize().y;
		rect.c1 = Vec4(1, 1, 1, 1);
		rect.c2 = Vec4(1, 1, 1, 1);
		rect.c3 = Vec4(1, 1, 1, 1);
		rect.c4 = Vec4(1, 1, 1, 1);
		rect.t1 = Vec2(0, 0);
		rect.t2 = Vec2(1, 0);
		rect.t3 = Vec2(0, 1);
		rect.t4 = Vec2(1, 1);
	}
	Sprite::Sprite(Texture& Ttex, float Tx1, float Ty1, float Tx2, float Ty2) {
		texture = &Ttex;
		rect.a.x = Tx1;
		rect.a.y = Ty1;
		rect.c.x = Tx2;
		rect.c.y = Ty2;
		rect.c1 = Vec4(1, 1, 1, 1);
		rect.c2 = Vec4(1, 1, 1, 1);
		rect.c3 = Vec4(1, 1, 1, 1);
		rect.c4 = Vec4(1, 1, 1, 1);
		rect.t1 = Vec2(0, 0);
		rect.t2 = Vec2(1, 0);
		rect.t3 = Vec2(0, 1);
		rect.t4 = Vec2(1, 1);
	}
	Sprite::Sprite(Texture& Ttex, Rectangle<float> Tcrop, Vec2 Tpos) {
		texture = &Ttex;
		float _w = (float)Ttex.getSize().x;
		float _h = (float)Ttex.getSize().y;
		rect.a.x = Tpos.x;
		rect.a.y = Tpos.y;
		rect.c.x = Tpos.x + (Tcrop.c.x - Tcrop.a.x);
		rect.c.y = Tpos.y + (Tcrop.c.y - Tcrop.a.y);
		rect.c1 = Vec4(1, 1, 1, 1);
		rect.c2 = Vec4(1, 1, 1, 1);
		rect.c3 = Vec4(1, 1, 1, 1);
		rect.c4 = Vec4(1, 1, 1, 1);
		rect.t1 = Vec2(Tcrop.a.x / _w, Tcrop.a.y / _h);
		rect.t2 = Vec2(Tcrop.c.x / _w, Tcrop.a.y / _h);
		rect.t3 = Vec2(Tcrop.a.x / _w, Tcrop.c.y / _h);
		rect.t4 = Vec2(Tcrop.c.x / _w, Tcrop.c.y / _h);
	}
	Sprite::Sprite(Texture& Ttex, Rectangle<float> Tcrop, Rectangle<float> Trect) {
		texture = &Ttex;
		float _w = (float)Ttex.getSize().x;
		float _h = (float)Ttex.getSize().y;
		rect.a.x = Trect.a.x;
		rect.a.y = Trect.a.y;
		rect.c.x = Trect.c.x;
		rect.c.y = Trect.c.y;
		rect.c1 = Vec4(1, 1, 1, 1);
		rect.c2 = Vec4(1, 1, 1, 1);
		rect.c3 = Vec4(1, 1, 1, 1);
		rect.c4 = Vec4(1, 1, 1, 1);
		rect.t1 = Vec2(Tcrop.a.x / _w, Tcrop.a.y / _h);
		rect.t2 = Vec2(Tcrop.c.x / _w, Tcrop.a.y / _h);
		rect.t3 = Vec2(Tcrop.a.x / _w, Tcrop.c.y / _h);
		rect.t4 = Vec2(Tcrop.c.x / _w, Tcrop.c.y / _h);
	}
	Sprite::Sprite(Texture& Ttex, Rectangle<float> Tcrop, float Tx, float Ty) {
		texture = &Ttex;
		float _w = (float)Ttex.getSize().x;
		float _h = (float)Ttex.getSize().y;
		rect.a.x = Tx;
		rect.a.y = Ty;
		rect.c.x = Tx + texture->getSize().x;
		rect.c.y = Ty + texture->getSize().y;
		rect.c1 = Vec4(1, 1, 1, 1);
		rect.c2 = Vec4(1, 1, 1, 1);
		rect.c3 = Vec4(1, 1, 1, 1);
		rect.c4 = Vec4(1, 1, 1, 1);
		rect.t1 = Vec2(Tcrop.a.x / _w, Tcrop.a.y / _h);
		rect.t2 = Vec2(Tcrop.c.x / _w, Tcrop.a.y / _h);
		rect.t3 = Vec2(Tcrop.a.x / _w, Tcrop.c.y / _h);
		rect.t4 = Vec2(Tcrop.c.x / _w, Tcrop.c.y / _h);
	}
	Sprite::Sprite(Texture& Ttex, Rectangle<float> Tcrop, float Tx1, float Ty1, float Tx2, float Ty2) {
		texture = &Ttex;
		float _w = (float)Ttex.getSize().x;
		float _h = (float)Ttex.getSize().y;
		rect.a.x = Tx1;
		rect.a.y = Ty1;
		rect.c.x = Tx2;
		rect.c.y = Ty2;
		rect.c1 = Vec4(1, 1, 1, 1);
		rect.c2 = Vec4(1, 1, 1, 1);
		rect.c3 = Vec4(1, 1, 1, 1);
		rect.c4 = Vec4(1, 1, 1, 1);
		rect.t1 = Vec2(Tcrop.a.x / _w, Tcrop.a.y / _h);
		rect.t2 = Vec2(Tcrop.c.x / _w, Tcrop.a.y / _h);
		rect.t3 = Vec2(Tcrop.a.x / _w, Tcrop.c.y / _h);
		rect.t4 = Vec2(Tcrop.c.x / _w, Tcrop.c.y / _h);
	}
	Sprite::Sprite(Texture& Ttex, float Tcx1, float Tcy1, float Tcx2, float Tcy2, Vec2 Tpos) {
		texture = &Ttex;
		float _w = (float)Ttex.getSize().x;
		float _h = (float)Ttex.getSize().y;
		rect.a.x = Tpos.x;
		rect.a.y = Tpos.y;
		rect.c.x = Tpos.x + (Tcx2 - Tcx1);
		rect.c.y = Tpos.y + (Tcy2 - Tcy1);
		rect.c1 = Vec4(1, 1, 1, 1);
		rect.c2 = Vec4(1, 1, 1, 1);
		rect.c3 = Vec4(1, 1, 1, 1);
		rect.c4 = Vec4(1, 1, 1, 1);
		rect.t1 = Vec2(Tcx1 / _w, Tcy1 / _h);
		rect.t2 = Vec2(Tcx2 / _w, Tcy1 / _h);
		rect.t3 = Vec2(Tcx1 / _w, Tcy2 / _h);
		rect.t4 = Vec2(Tcx2 / _w, Tcy2 / _h);
	}
	Sprite::Sprite(Texture& Ttex, float Tcx1, float Tcy1, float Tcx2, float Tcy2, Rectangle<float> Trect) {
		texture = &Ttex;
		float _w = (float)Ttex.getSize().x;
		float _h = (float)Ttex.getSize().y;
		rect.a.x = Trect.a.x;
		rect.a.y = Trect.a.y;
		rect.c.x = Trect.a.x + (Tcx2 - Tcx1);
		rect.c.y = Trect.a.y + (Tcy2 - Tcy1);
		rect.c1 = Vec4(1, 1, 1, 1);
		rect.c2 = Vec4(1, 1, 1, 1);
		rect.c3 = Vec4(1, 1, 1, 1);
		rect.c4 = Vec4(1, 1, 1, 1);
		rect.t1 = Vec2(Tcx1 / _w, Tcy1 / _h);
		rect.t2 = Vec2(Tcx2 / _w, Tcy1 / _h);
		rect.t3 = Vec2(Tcx1 / _w, Tcy2 / _h);
		rect.t4 = Vec2(Tcx2 / _w, Tcy2 / _h);
	}
	Sprite::Sprite(Texture& Ttex, float Tcx1, float Tcy1, float Tcx2, float Tcy2, float Tx, float Ty) {
		texture = &Ttex;
		float _w = (float)Ttex.getSize().x;
		float _h = (float)Ttex.getSize().y;
		rect.a.x = Tx;
		rect.a.y = Ty;
		rect.c.x = Tx + (Tcx2 - Tcx1);
		rect.c.y = Ty + (Tcy2 - Tcy1);
		rect.c1 = Vec4(1, 1, 1, 1);
		rect.c2 = Vec4(1, 1, 1, 1);
		rect.c3 = Vec4(1, 1, 1, 1);
		rect.c4 = Vec4(1, 1, 1, 1);
		rect.t1 = Vec2(Tcx1 / _w, Tcy1 / _h);
		rect.t2 = Vec2(Tcx2 / _w, Tcy1 / _h);
		rect.t3 = Vec2(Tcx1 / _w, Tcy2 / _h);
		rect.t4 = Vec2(Tcx2 / _w, Tcy2 / _h);
	}
	Sprite::Sprite(Texture& Ttex, float Tcx1, float Tcy1, float Tcx2, float Tcy2, float Tx1, float Ty1, float Tx2, float Ty2) {
		texture = &Ttex;
		float _w = (float)Ttex.getSize().x;
		float _h = (float)Ttex.getSize().y;
		rect.a.x = Tx1;
		rect.a.y = Ty1;
		rect.c.x = Tx2;
		rect.c.y = Ty2;
		rect.c1 = Vec4(1, 1, 1, 1);
		rect.c2 = Vec4(1, 1, 1, 1);
		rect.c3 = Vec4(1, 1, 1, 1);
		rect.c4 = Vec4(1, 1, 1, 1);
		rect.t1 = Vec2(Tcx1 / _w, Tcy1 / _h);
		rect.t2 = Vec2(Tcx2 / _w, Tcy1 / _h);
		rect.t3 = Vec2(Tcx1 / _w, Tcy2 / _h);
		rect.t4 = Vec2(Tcx2 / _w, Tcy2 / _h);
	}

	Sprite& Sprite::operator*(VertexColor Tvc) {
		rect.c1 = Tvc.a;
		rect.c2 = Tvc.b;
		rect.c3 = Tvc.c;
		rect.c4 = Tvc.d;

		return *this;
	}
	Sprite& Sprite::operator*(Transform Ttrans) {
		trans = Ttrans;

		return *this;
	}
						
	Text::Text() {

	}
	Text::Text(Font& Tfont, Vec2 Tpos, char Tchar) {
		font = &Tfont;
	}
	Text::Text(Font& Tfont, Vec2 Tpos, const char* Tstring) {
		font = &Tfont;
		pos = Tpos;
		string = Tstring;
	}
	Text::Text(Font& Tfont, Vec2 Tpos, const std::string& Tstring) {
		font = &Tfont;
		pos = Tpos;
		string = Tstring;
	}

	enum TextFunc {
		None,
		Func,
		ColorTag,
		ColorHex
	};

	float Text::getWidth() {
		int _length = string.length();
		float _Twidth = 0;
		float _TTwidth = 0;

		TextFunc _Tfunc = TextFunc::None;
		bool _Tdraw = 0;

		for (int i = 0;i < _length;i++) {
			if (string[i] == '\n') {
				_Twidth = (_Twidth > _TTwidth ? _Twidth : _TTwidth);
			}
			if (string[i] == '~') {
				if (_Tfunc == TextFunc::ColorTag) {
					_Tfunc = TextFunc::None;
				}
				else {
					_Tfunc = TextFunc::ColorTag;
				}
			}

			_Tdraw = _Tfunc == (TextFunc::None);
			if ((string[i] != ' ') && (string[i] != '\n') && (_Tdraw)) {

				_TTwidth = _TTwidth + (font->getWidth(string[i]) + font->getSepWidth());
			}
			else {
				if (string[i] == ' ') {
					_TTwidth = _TTwidth + font->getFullWidth();
				}
				if (_Tfunc == TextFunc::ColorTag) {
					if (string[i] != '~') {
						_Tfunc = TextFunc::None;
					}
				}
			}
		}

		_Twidth = (_Twidth > _TTwidth ? _Twidth : _TTwidth);

		return _Twidth;
	}

	


}