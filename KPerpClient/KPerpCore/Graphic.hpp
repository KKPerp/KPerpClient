#ifndef _KPerpCore_Graphic_hpp_
#define _KPerpCore_Graphic_hpp_

#include "Resource.hpp"
#include "Drawing.hpp"

#include "Win32Handles.hpp"
#include "Font.hpp"

namespace kp {
	namespace Drawing {
		class VertexArray;
	}

	class Texture;

	class Graphic {
	public:
		Graphic();
		Graphic(const Drawing::VertexArray& Tvertexarray);
		Graphic(const Drawing::VertexArray& Tvertexarray, const Texture& Ttexture);
	
		Drawing::VertexArray& getVertexArray();
		Texture& getTexture();
		Drawing::VertexArray getVertexArray() const;
		Texture getTexture() const;

	private:

		Drawing::VertexArray vertexarray;
		Texture* texture;
	};

	class VertexColor {
	public:
		VertexColor();
		VertexColor(Color Tcolor);
		VertexColor(Vec4 Tvec4);
		VertexColor(Color Tcolora, Color Tcolorb, Color Tcolorc, Color Tcolord);
		VertexColor(Vec4 Tvec4a, Vec4 Tvec4b, Vec4 Tvec4c, Vec4 Tvec4d);

		Vec4 a;
		Vec4 b;
		Vec4 c;
		Vec4 d;
	};

	class Transform {
	public:
		Transform();
		Transform(Vec2 Torigin);
		Transform(Vec2 Torigin, Vec2 Tscale);
		Transform(Vec2 Torigin, Vec2 Tscale, float Tangle);

		Vec2 origin;
		Vec2 scale;
		float angle;
	};

	bool operator==(const Transform& Tltrans, const Transform& Trtrans);
	bool operator!=(const Transform& Tltrans, const Transform& Trtrans);

	class Sprite {
	public:
		Sprite();
		Sprite(Texture& Ttex);
		Sprite(Texture& Ttex, Vec2 Tpos);
		Sprite(Texture& Ttex, Rectangle<float> Trect);
		Sprite(Texture& Ttex, float Tx, float Ty);
		Sprite(Texture& Ttex, float Tx1, float Ty1, float Tx2, float Ty2);
		Sprite(Texture& Ttex, Rectangle<float> Tcrop, Vec2 Tpos);
		Sprite(Texture& Ttex, Rectangle<float> Tcrop, Rectangle<float> Trect);
		Sprite(Texture& Ttex, Rectangle<float> Tcrop, float Tx, float Ty);
		Sprite(Texture& Ttex, Rectangle<float> Tcrop, float Tx1, float Ty1, float Tx2, float Ty2);
		Sprite(Texture& Ttex, float Tcx1, float Tcy1, float Tcx2, float Tcy2, Vec2 Tpos);
		Sprite(Texture& Ttex, float Tcx1, float Tcy1, float Tcx2, float Tcy2, Rectangle<float> Trect);
		Sprite(Texture& Ttex, float Tcx1, float Tcy1, float Tcx2, float Tcy2, float Tx, float Ty);
		Sprite(Texture& Ttex, float Tcx1, float Tcy1, float Tcx2, float Tcy2, float Tx1, float Ty1, float Tx2, float Ty2);

		Sprite& operator*(VertexColor Tvc);
		Sprite& operator*(Transform Ttrans);

		Texture* texture;
		Drawing::Rectangle rect;
		Transform trans;
	};

	bool operator==(const Sprite& Tlsprite, const Sprite& Trsprite);
	bool operator!=(const Sprite& Tlsprite, const Sprite& Trsprite);

	class Font;

	class Text {
	public:
		enum Align {
			Left,
			Center,
			Right,

			Top,
			Middle = Center,
			Bottom
		};

		Text();
		Text(Font& Tfont, Vec2 Tpos, char Tchar, Align Talign = Left, Align Tvalign = Top, float Twarp = 0, char Twarpchar = 0, bool Tmnemonic = 0);
		Text(Font& Tfont, Vec2 Tpos, const char* Tstring, Align Talign = Left, Align Tvalign = Top, float Twarp = 0, char Twarpchar = 0, bool Tmnemonic = 0);
		Text(Font& Tfont, Vec2 Tpos, const std::string& Tstring, Align Talign = Left, Align Tvalign = Top, float Twarp = 0, char Twarpchar = 0, bool Tmnemonic = 0);

		Vec2 getSize() const;
		Vec2 getCharLength() const;

		float LineWidth(int Tpos) const;
		float LineLength(int Tpos) const;

		int NextChar(int Tpos, char Tchar) const;
		int PrevChar(int Tpos, char Tchar) const;

		int LineIndex(int Tpos, float Tx) const;

		Vec2 LinePos(int Tpos) const;

		Font* font;
		Vec2 pos;
		std::string string;
		Transform trans;

		Align align;
		Align valign;

		float warp;
		char warpchar;

		bool mnemonic;
	};

	bool operator==(const Text& Tltext, const Text& Trtext);
	bool operator!=(const Text& Tltext, const Text& Trtext);
}

#endif