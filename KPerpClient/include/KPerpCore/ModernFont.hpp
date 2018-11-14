#ifndef __KPerpCore_ModernFont_hpp_
#define __KPerpCore_ModernFont_hpp_

#include <KPerpCore/Matrix.hpp>
#include <KPerpCore/Drawing.hpp>
#include <vector>
#include <map>
#include <harfbuzz/src/hb.h>
#include <harfbuzz/src/hb-ft.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_STROKER_H
#include FT_LCD_FILTER_H

#define KPERPCORE_MODERNFONT_DEF_PXLSIZE 12
#define KPERPCORE_MODERNFONT_DEF_RANGE 16384
namespace kp {

	struct ModernTextStyle
	{
		Color diffuseColor;
		Color outlineColor;
		Color shadowColor;
		Vec2 shadowShift;
	};
	
	struct ModernGlyph {
		unsigned int TextureID;   // ID handle of the glyph texture
		Vector2<int> Size;    // Size of glyph
		Vector2<int> Bearing;  // Offset from baseline to left/top of glyph
		signed long Advance;    // Horizontal offset to advance to next glyph
	};

	//std::map<char, ModernGlyph> &getModernGlyphList();
	class ModernFont
	{
	public:
		ModernFont();
		~ModernFont();
		ModernFont(const char * font);
		ModernFont(const char * font, int pix);

		unsigned int getTexture() const;
		int getPixelSize() const;

		std::map<unsigned int, ModernGlyph> GlyphList;

		virtual ModernGlyph rasterizeGlyph(unsigned int glyphIndex);
		virtual void freeFace();

		
		FT_Face * face = new FT_Face;
		FT_Library ft;

	private:
		unsigned int texture;
		void freetypeInit(const char * font, int pxl);
		const char * fontFile;
		int pixelSize;
		int rangeOfChar;
	};

	class ModernText {
	public:
		ModernText();
		~ModernText();
		ModernText(ModernFont& Tfont, Vec2 Tsize, Vec2 Tpos, const std::wstring& Tstring, ModernTextStyle style, float Tscale);
		ModernText(ModernFont& Tfont, Vec2 Tsize, Vec2 Tpos, const std::wstring& Tstring, Color Tcolor, float Tscale);
		ModernText(ModernFont& Tfont, Vec2 Tsize, Vec2 Tpos, const std::wstring& Tstring, Color Tcolor, Color TcolorOutline, float Tscale);

		//float getWidth();

		ModernFont* font;
		Vec2 size;
		Vec2 pos;
		Vec2 shadowShift = Vec2(2.0f,2.0f);
		Color DiffuseColor;
		Color OutlineColor;
		std::wstring string;
		//Transform trans;
		float scale;
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