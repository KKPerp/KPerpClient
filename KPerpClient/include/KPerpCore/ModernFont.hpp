#ifndef __KPerpCore_ModernFont_hpp_
#define __KPerpCore_ModernFont_hpp_

#include <KPerpCore/Matrix.hpp>
#include <KPerpCore/Drawing.hpp>

#include <map>

#include <ft2build.h>
#include FT_FREETYPE_H

#define KPERPCORE_MODERNFONT_DEF_PXLSIZE 12
#define KPERPCORE_MODERNFONT_DEF_RANGE 16384
namespace kp {

	
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
}
#endif