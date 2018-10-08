#ifndef _KPerpCore_Graphic_hpp_
#define _KPerpCore_Graphic_hpp_

#include <KPerpCore/Resource.hpp>
#include <KPerpCore/Drawing.hpp>
#include <KPerpCore/Win32Handles.hpp>
#include <KPerpCore/Font.hpp>
#include <KPerpCore/ModernFont.hpp>

#include <harfbuzz/src/hb.h>
#include <harfbuzz/src/hb-ft.h>
#include <vector>
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

	class Font;

	class Text {
	public:
		Text();
		Text(Font& Tfont, Vec2 Tpos, char Tchar);
		Text(Font& Tfont, Vec2 Tpos, const char* Tstring);
		Text(Font& Tfont, Vec2 Tpos, const std::string& Tstring);

		float getWidth();

		Font* font;
		Vec2 pos;
		std::string string;
		Transform trans;
	};

	class ModernText {
	public:
		ModernText();
		~ModernText();
		ModernText(ModernFont& Tfont, Vec2 Tsize, Vec2 Tpos, wchar_t Tchar, Color Tcolor, float Tscale);
		ModernText(ModernFont& Tfont, Vec2 Tsize, Vec2 Tpos, const wchar_t* Tstring, Color Tcolor, float Tscale);
		ModernText(ModernFont& Tfont, Vec2 Tsize, Vec2 Tpos, const std::wstring& Tstring, Color Tcolor, float Tscale);

		//float getWidth();

		ModernFont* font;
		Vec2 size;
		Vec2 pos;
		Color color;
		std::wstring string;
		Transform trans;
		float scale;
		/*hb_font_t * harfbuzzFace;
		hb_buffer_t * harfbuzzBuffer;*/
		void setText(std::wstring str);
		unsigned int glyphCount;
		hb_glyph_info_t * glyphInfo;
		hb_glyph_position_t * glyphPos;
		std::vector<ModernGlyph> Tglyph;
		std::vector<hb_feature_t> features;

		void free() const;
		void addFeature(hb_feature_t fea);

		bool oneLine = false;
	private:
		void harfbuzzInit();

	};
}

#endif