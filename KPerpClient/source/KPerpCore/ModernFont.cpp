

#include <KPerpCore/ModernFont.hpp>
#include <glad/glad.h>

namespace kp {
	//std::map<char, ModernGlyph> ModernGlyphList;
	
	ModernFont::ModernFont()
	{
	}
	ModernFont::ModernFont(const char * font)
	{
		freetypeInit(font, KPERPCORE_MODERNFONT_DEF_PXLSIZE);
		pixelSize = KPERPCORE_MODERNFONT_DEF_PXLSIZE;
		fontFile = font;
		rangeOfChar = KPERPCORE_MODERNFONT_DEF_RANGE;
	}

	ModernFont::ModernFont(const char * font, int pix)
	{
		freetypeInit(font, pix);
		pixelSize = pix;
		fontFile = font;
		rangeOfChar = KPERPCORE_MODERNFONT_DEF_RANGE;
	}

	ModernFont::~ModernFont()
	{
		freeFace();
	}

	unsigned int ModernFont::getTexture() const
	{
		return texture;
	}

	int ModernFont::getPixelSize() const
	{
		return pixelSize;
	}

	ModernGlyph ModernFont::rasterizeGlyph(unsigned int glyphIndex)
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		// Load character glyph 
		if (FT_Load_Glyph(*face, glyphIndex, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
		}
		else
		{
			std::map<unsigned int, ModernGlyph>::iterator it;
			it = GlyphList.find(glyphIndex);
			if (it == GlyphList.end())
			{
				// Generate texture
				glGenTextures(1, &texture);
				glBindTexture(GL_TEXTURE_2D, texture);
				glTexImage2D(
					GL_TEXTURE_2D,
					0,
					GL_RED,
					(*face)->glyph->bitmap.width,
					(*face)->glyph->bitmap.rows,
					0,
					GL_RED,
					GL_UNSIGNED_BYTE,
					(*face)->glyph->bitmap.buffer
				);
				// Set texture options
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				// Now store character for later use
				ModernGlyph glyph{
					texture,
					Vector2<int>((*face)->glyph->bitmap.width, (*face)->glyph->bitmap.rows),
					Vector2<int>((*face)->glyph->bitmap_left, (*face)->glyph->bitmap_top),
					(*face)->glyph->advance.x
				};
				GlyphList.insert(std::pair<unsigned int, ModernGlyph>(glyphIndex, glyph));
				glBindTexture(GL_TEXTURE_2D, 0);
				return glyph;
			}
			else
			{
				return it->second;
			}
			
		}
		
	}

	void ModernFont::freeFace()
	{
		FT_Done_Face(*face);
		FT_Done_FreeType(ft);

		for (auto const& x : GlyphList)
		{
			glDeleteTextures(1, &(x.second.TextureID));
		}
	}

	//std::map<char, ModernGlyph>& ModernFont::GlyphList;

	void ModernFont::freetypeInit(const char * font, int pxl)
	{
		// All functions return a value different than 0 whenever an error occurred
		if (FT_Init_FreeType(&ft))
		{
			std::cout << "CORE-ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
		}
		else
		{


			// Load font as face
			if (FT_New_Face(ft, font, 0, face))
			{
				std::cout << "SEMI-ERROR::FREETYPE: Failed to load font / font not found" << std::endl;
			}
			else
			{
				FT_Set_Pixel_Sizes(*face, 0, pxl);
				rasterizeGlyph(392); // ?
#ifdef KONGPHA_WOT
				rasterizeGlyph(3585); // ¡
				rasterizeGlyph(3657); // é
				rasterizeGlyph(3629); // Í
				rasterizeGlyph(3591); // §
#endif
			}
		}
	}
	//std::map<char, ModernGlyph> & getModernGlyphList()
	//{
	//	return ModernGlyphList;
	//}
}