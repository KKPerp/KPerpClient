#include <ft2build.h>
#include FT_FREETYPE_H
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

	bool operator==(const Transform& Tltrans, const Transform& Trtrans) {
		return !memcmp(&Tltrans, &Trtrans, sizeof(Sprite));
	}
	bool operator!=(const Transform& Tltrans, const Transform& Trtrans) {
		return !memcmp(&Tltrans, &Trtrans, sizeof(Sprite));
	}

	Sprite::Sprite() {
		texture = NULL;
		rect.a.z = 0;
		rect.c.z = 0;
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
		rect.a.z = 0;
		rect.c.z = 0;
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
		rect.c.x = Trect.c.x;
		rect.c.y = Trect.c.y;
		rect.a.z = 0;
		rect.c.z = 0;
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
		rect.a.z = 0;
		rect.c.z = 0;
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
		rect.a.z = 0;
		rect.c.z = 0;
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
		rect.a.z = 0;
		rect.c.z = 0;
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
		rect.a.z = 0;
		rect.c.z = 0;
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
		rect.a.z = 0;
		rect.c.z = 0;
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
		rect.a.z = 0;
		rect.c.z = 0;
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
		rect.a.z = 0;
		rect.c.z = 0;
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
		rect.a.z = 0;
		rect.c.z = 0;
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
		rect.a.z = 0;
		rect.c.z = 0;
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
		rect.a.z = 0;
		rect.c.z = 0;
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

	bool operator==(const Sprite& Tlsprite, const Sprite& Trsprite) {
		return !memcmp(&Tlsprite, &Trsprite, sizeof(Sprite));
	}
	bool operator!=(const Sprite& Tlsprite, const Sprite& Trsprite) {
		return (memcmp(&Tlsprite, &Trsprite, sizeof(Sprite)) != 0);
	}
						
	Text::Text() {

	}
	Text::Text(Font& Tfont, Vec2 Tpos, char Tchar, Align Talign, Align Tvalign, float Twarp, char Twarpchar, bool Tmnomonic) {
		font = &Tfont;
		pos = Tpos;
		string = Tchar;
		align = Talign;
		valign = Tvalign;

		warp = Twarp;
		warpchar = Twarpchar;

		//mnomonic = true;
	}
	Text::Text(Font& Tfont, Vec2 Tpos, const char* Tstring, Align Talign, Align Tvalign, float Twarp, char Twarpchar, bool Tmnomonic) {
		font = &Tfont;
		pos = Tpos;
		string = Tstring;
		align = Talign;
		valign = Tvalign;

		warp = Twarp;
		warpchar = Twarpchar;
	}
	Text::Text(Font& Tfont, Vec2 Tpos, const std::string& Tstring, Align Talign, Align Tvalign, float Twarp, char Twarpchar, bool Tmnomonic) {
		font = &Tfont;
		pos = Tpos;
		string = Tstring;
		align = Talign;
		valign = Tvalign;

		warp = Twarp;
		warpchar = Twarpchar;
	}

	static enum TextFunc {
		None,
		Func,
		ColorTag,
		ColorHex
	};

	Vec2 Text::getSize() const {
		int _length = string.length();
		float _Twidth = 0;
		float _Theight = 0;
		float _TTwidth = 0;

		int _hexl = 0;

		TextFunc _Tfunc = TextFunc::None;
		bool _Tdraw = 0;

		for (int i = 0;i < _length;i++) {
			if (!i) {
				_Theight = 1;
			}
			if (string[i] == '\n') {
				_Twidth = (_Twidth > _TTwidth ? _Twidth : _TTwidth);
				_TTwidth = 0;
				_Theight += 1;
			}
			if (warp) {
				if (_TTwidth > warp) {
					if (warpchar) {
						if (string[i] == warpchar) {
							_Twidth = (_Twidth > _TTwidth ? _Twidth : _TTwidth);
							_TTwidth = 0;
							_Theight += 1;
						}
					}
					else {
						_Twidth = (_Twidth > _TTwidth ? _Twidth : _TTwidth);
						_TTwidth = 0;
						_Theight += 1;
					}
				}
			}
			if (string[i] == '~') {
				if (_Tfunc == TextFunc::Func) {
					_Tfunc = TextFunc::None;
				}
				else {
					_Tfunc = TextFunc::Func;
				}
			}

			_Tdraw = _Tfunc == (TextFunc::None);
			if ((string[i] != ' ') && (string[i] != '\n') && (_Tdraw)) {

				_TTwidth = _TTwidth + (font->getWidth(string[i]) + font->getSepWidth());
			}
			else {
				if (string[i] == ' ') {
					_TTwidth = _TTwidth + font->getSpaceWidth();
				}
				if (_Tfunc == TextFunc::ColorTag) {
					if (string[i] != '~') {
						_Tfunc = TextFunc::None;
					}
				}
				if (_Tfunc == TextFunc::Func) {
					switch (string[i]) {
					default: {
						_Tfunc = TextFunc::None;
						break;
					}
					case '~': {
						break;
					}
					case 'r': {
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
					switch (string[i]) {
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

		_Twidth = (_Twidth > _TTwidth ? _Twidth : _TTwidth);

		return { _Twidth,_Theight*(font->getFullHeight() + font->getSepWidth()) };
	}

	Vec2 Text::getCharLength() const {
		int _length = string.length();
		float _Twidth = 0;
		float _Theight = 0;
		float _TTwidth = 0;

		int _hexl = 0;

		TextFunc _Tfunc = TextFunc::None;
		bool _Tdraw = 0;

		for (int i = 0;i < _length;i++) {
			if (!i) {
				_Theight = 1;
			}
			if (string[i] == '\n') {
				_Twidth = (_Twidth > _TTwidth ? _Twidth : _TTwidth);
				_TTwidth = 0;
				_Theight += 1;
			}
			if (string[i] == '~') {
				if (_Tfunc == TextFunc::Func) {
					_Tfunc = TextFunc::None;
				}
				else {
					_Tfunc = TextFunc::Func;
				}
			}

			_Tdraw = _Tfunc == (TextFunc::None);
			if ((string[i] != ' ') && (string[i] != '\n') && (_Tdraw)) {

				_TTwidth;
			}
			else {
				if (string[i] == ' ') {
					_TTwidth++;
				}
				if (_Tfunc == TextFunc::ColorTag) {
					if (string[i] != '~') {
						_Tfunc = TextFunc::None;
					}
				}
				if (_Tfunc == TextFunc::Func) {
					switch (string[i]) {
					default: {
						_Tfunc = TextFunc::None;
						break;
					}
					case '~': {
						break;
					}
					case 'r': {
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
					switch (string[i]) {
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

		_Twidth = (_Twidth > _TTwidth ? _Twidth : _TTwidth);

		return { _Twidth,_Theight };
	}

	float Text::LineWidth(int Tpos) const {
		int _length = string.length();
		float _Twidth = 0;

		int _hexl = 0;

		TextFunc _Tfunc = TextFunc::None;
		bool _Tdraw = 0;

		for (int i = Tpos;i < _length;i++) {
			if (string[i] == '\n') {
				return _Twidth;
			}
			if (string[i] == '~') {
				if (_Tfunc == TextFunc::Func) {
					_Tfunc = TextFunc::None;
				}
				else {
					_Tfunc = TextFunc::Func;
				}
			}

			_Tdraw = _Tfunc == (TextFunc::None);
			if ((string[i] != ' ') && (_Tdraw)) {

				_Twidth += (font->getWidth(string[i]) + font->getSepWidth());
			}
			else {
				if (string[i] == ' ') {
					_Twidth += font->getSpaceWidth();
				}
				if (_Tfunc == TextFunc::ColorTag) {
					if (string[i] != '~') {
						_Tfunc = TextFunc::None;
					}
				}
				if (_Tfunc == TextFunc::Func) {
					switch (string[i]) {
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
					switch (string[i]) {
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

		return _Twidth;
	}
	float Text::LineLength(int Tpos) const {
		int _length = string.length();
		float _Twidth = 0;

		int _hexl = 0;

		TextFunc _Tfunc = TextFunc::None;
		bool _Tdraw = 0;

		for (int i = Tpos;i < _length;i++) {
			if (string[i] == '\n') {
				return _Twidth;
			}
			if (string[i] == '~') {
				if (_Tfunc == TextFunc::Func) {
					_Tfunc = TextFunc::None;
				}
				else {
					_Tfunc = TextFunc::Func;
				}
			}

			_Tdraw = _Tfunc == (TextFunc::None);
			if ((string[i] != ' ') && (_Tdraw)) {
				_Twidth++;
			}
			else {
				if (string[i] == ' ') {
					_Twidth++;
				}
				if (_Tfunc == TextFunc::ColorTag) {
					if (string[i] != '~') {
						_Tfunc = TextFunc::None;
					}
				}
				if (_Tfunc == TextFunc::Func) {
					switch (string[i]) {
					default: {
						_Tfunc = TextFunc::None;
						break;
					}
					case '~': {
						break;
					}
					case 'r': {
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
					switch (string[i]) {
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

		return _Twidth;
	}

	int Text::NextChar(int Tpos, char Tchar) const {
		int _length = string.length();

		for (int i = Tpos;i < _length;i++) {
			if (string[i] == Tchar) {
				return i;
			}
		}

		return -1;
	}
	int Text::PrevChar(int Tpos, char Tchar) const {
		for (int i = Tpos;i >= 0;i--) {
			if (string[i] == Tchar) {
				return i;
			}
		}

		return -1;
	}

	int Text::LineIndex(int Tpos, float Tx) const {
		int _length = string.length();
		float _Twidth = 0;

		if (Tx < 0) {
			return 0;
		}

		int _hexl = 0;

		TextFunc _Tfunc = TextFunc::None;
		bool _Tdraw = 0;

		for (int i = Tpos;i < _length;i++) {
			if (string[i] == '\n') {
				return i;
			}
			if (string[i] == '~') {
				if (_Tfunc == TextFunc::Func) {
					_Tfunc = TextFunc::None;
				}
				else {
					_Tfunc = TextFunc::Func;
				}
			}

			_Tdraw = _Tfunc == (TextFunc::None);
			if ((string[i] != ' ') && (_Tdraw)) {
				float _TPwidth = _Twidth;
				_Twidth += (font->getWidth(string[i]) + font->getSepWidth());
				if (Tx < _TPwidth + ((font->getWidth(string[i]) + font->getSepWidth()) / 2.0f)) {
					return i;
				}
			}
			else {
				if (string[i] == ' ') {
					float _TPwidth = _Twidth;
					_Twidth += (font->getSpaceWidth());
					if (Tx < _TPwidth + ((font->getSpaceWidth()) / 2.0f)) {
						return i;
					}
				}
				if (_Tfunc == TextFunc::ColorTag) {
					if (string[i] != '~') {
						_Tfunc = TextFunc::None;
					}
				}
				if (_Tfunc == TextFunc::Func) {
					switch (string[i]) {
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
					switch (string[i]) {
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

		return _length;
	}
	
	Vec2 Text::LinePos(int Tpos) const {
		int _length = string.length();
		float _Twidth = 0;
		float _Theight = 0;
		float _TTwidth = 0;

		int _hexl = 0;

		TextFunc _Tfunc = TextFunc::None;
		bool _Tdraw = 0;

		for (int i = 0;i < _length;i++) {
			if (string[i] == '\n') {
				if (i == Tpos) {
					return { _TTwidth,_Theight*(font->getFullHeight() + font->getSepWidth()) };
				}
				_Twidth = (_Twidth > _TTwidth ? _Twidth : _TTwidth);
				_TTwidth = 0;
				_Theight += 1;
			}
			if (warp) {
				if (_TTwidth > warp) {
					if (warpchar) {
						if (string[i] == warpchar) {
							_Twidth = (_Twidth > _TTwidth ? _Twidth : _TTwidth);
							_TTwidth = 0;
							_Theight += 1;
						}
					}
					else {
						_Twidth = (_Twidth > _TTwidth ? _Twidth : _TTwidth);
						_TTwidth = 0;
						_Theight += 1;
					}
				}
			}
			if (string[i] == '~') {
				if (_Tfunc == TextFunc::Func) {
					_Tfunc = TextFunc::None;
				}
				else {
					_Tfunc = TextFunc::Func;
				}
			}

			_Tdraw = _Tfunc == (TextFunc::None);
			if ((string[i] != ' ') && (string[i] != '\n') && (_Tdraw)) {

				if (i == Tpos) {
					return { _TTwidth,_Theight*(font->getFullHeight() + font->getSepWidth()) };
				}
				_TTwidth = _TTwidth + (font->getWidth(string[i]) + font->getSepWidth());
			}
			else {
				if (string[i] == ' ') {
					if (i == Tpos) {
						return { _TTwidth,_Theight*(font->getFullHeight() + font->getSepWidth()) };
					}
					_TTwidth = _TTwidth + font->getSpaceWidth();
				}
				if (_Tfunc == TextFunc::ColorTag) {
					if (string[i] != '~') {
						_Tfunc = TextFunc::None;
					}
				}
				if (_Tfunc == TextFunc::Func) {
					switch (string[i]) {
					default: {
						_Tfunc = TextFunc::None;
						break;
					}
					case '~': {
						break;
					}
					case 'r': {
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
					switch (string[i]) {
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

		//_TTwidth = _TTwidth + (font->getWidth(string[string.size() - 1]) + font->getSepWidth());
		_Twidth = (_Twidth > _TTwidth ? _Twidth : _TTwidth);

		return { _TTwidth,_Theight*(font->getFullHeight() + font->getSepWidth()) };
	}

	bool operator==(const Text& Tltext, const Text& Trtext) {
		return (Tltext.string == Trtext.string &&
			Tltext.align == Trtext.align &&
			Tltext.font == Trtext.font &&
			Tltext.mnemonic == Trtext.mnemonic &&
			Tltext.pos == Trtext.pos &&
			Tltext.trans == Trtext.trans &&
			Tltext.valign == Trtext.valign &&
			Tltext.warp == Trtext.warp &&
			Tltext.warpchar == Trtext.warpchar);
	}
	ModernText::ModernText(ModernFont& Tfont, Vec2 Tsize, Vec2 Tpos, wchar_t Tchar, Color Tcolor, float Tscale) {
		font = &Tfont;
		color = Tcolor;
		size = Tsize;
		scale = Tscale;
		harfbuzzInit();
	}
	ModernText::ModernText(ModernFont& Tfont, Vec2 Tsize, Vec2 Tpos, const wchar_t* Tstring, Color Tcolor, float Tscale) {
		font = &Tfont;
		pos = Tpos;
		string = Tstring;
		color = Tcolor;
		size = Tsize;
		scale = Tscale;
		harfbuzzInit();
	}
	ModernText::ModernText(ModernFont& Tfont, Vec2 Tsize, Vec2 Tpos, const std::wstring& Tstring, Color Tcolor, float Tscale) {
		font = &Tfont;
		pos = Tpos;
		string = Tstring;
		color = Tcolor;
		size = Tsize;
		scale = Tscale;
		harfbuzzInit();
	}

	void ModernText::harfbuzzInit()
	{
		
		hb_font_t * harfbuzzFace = hb_ft_font_create(*(font->face), NULL);
		hb_buffer_t * harfbuzzBuffer = hb_buffer_create();

		hb_buffer_allocation_successful(harfbuzzBuffer);

		hb_buffer_set_direction(harfbuzzBuffer, HB_DIRECTION_LTR);
		hb_buffer_set_script(harfbuzzBuffer, HB_SCRIPT_THAI);
		hb_buffer_add_utf16(harfbuzzBuffer, (unsigned short*)(string.c_str()), string.length(), 0, string.length());

		hb_shape(harfbuzzFace, harfbuzzBuffer, features.empty() ? NULL : &features[0], features.size());

		glyphCount = hb_buffer_get_length(harfbuzzBuffer);
		glyphInfo = hb_buffer_get_glyph_infos(harfbuzzBuffer, &glyphCount);
		glyphPos = hb_buffer_get_glyph_positions(harfbuzzBuffer, &glyphCount);
		
		for (int i = 0; i < glyphCount; ++i)
			Tglyph.push_back(font->rasterizeGlyph(glyphInfo[i].codepoint));
		
		hb_buffer_destroy(harfbuzzBuffer);
		hb_font_destroy(harfbuzzFace);
	}

	void ModernText::setText(std::wstring str)
	{
		string = str;
		free();
		harfbuzzInit();
	}

	void ModernText::free() const
	{
		
	}

	void ModernText::addFeature(hb_feature_t fea)
	{
		features.push_back(fea);
	}

	ModernText::~ModernText()
	{
		free();
	}


}