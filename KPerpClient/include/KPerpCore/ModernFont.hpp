#ifndef __KPerpCore_ModernFont_hpp_
#define __KPerpCore_ModernFont_hpp_

#include <map>
#include <KPerpCore/Matrix.hpp>
#include <KPerpCore/Drawing.hpp>
#define KPERPCORE_MODERNFONT_DEF_PXLSIZE 12

namespace kp {
	struct ModernGlyph {
		unsigned int TextureID;   // ID handle of the glyph texture
		Vector2<int> Size;    // Size of glyph
		Vector2<int> Bearing;  // Offset from baseline to left/top of glyph
		unsigned int Advance;    // Horizontal offset to advance to next glyph
	};

	//std::map<char, ModernGlyph> &getModernGlyphList();
	class ModernFont
	{
	public:
		ModernFont();
		ModernFont(const char * font);
		ModernFont(const char * font, int pix);

		unsigned int getTexture() const;
		int getPixelSize() const;

		std::map<char, ModernGlyph> GlyphList;

	private:
		unsigned int texture;
		void freetypeInit(const char * font, int pxl);
		const char * fontFile;
		int pixelSize;
	};

}
#endif