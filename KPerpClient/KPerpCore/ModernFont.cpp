#include "ModernFont.hpp"
#include "glad/glad.h"


#include <ft2build.h>
#include FT_FREETYPE_H  
namespace kp {
	std::map<char, ModernGlyph> ModernGlyphList;
	ModernFont::ModernFont(const char * font)
	{
		freetypeInit(font, KPERPCORE_MODERNFONT_DEF_PXLSIZE);
		pixelSize = KPERPCORE_MODERNFONT_DEF_PXLSIZE;
		fontFile = font;
	}

	ModernFont::ModernFont(const char * font, int pix)
	{
		freetypeInit(font, pix);
		pixelSize = pix;
		fontFile = font;
	}

	unsigned int ModernFont::getTexture() const
	{
		return texture;
	}

	int ModernFont::getPixelSize() const
	{
		return pixelSize;
	}

	void ModernFont::freetypeInit(const char * font, int pxl)
	{

		// FreeType
		FT_Library ft;

		// All functions return a value different than 0 whenever an error occurred
		if (FT_Init_FreeType(&ft))
			std::cout << "CORE-ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

		// Load font as face
		FT_Face face;
		if (FT_New_Face(ft, font, 0, &face))
			std::cout << "SEMI-ERROR::FREETYPE: Failed to load font / font not found" << std::endl;

		// Set size to load glyphs as
		FT_Set_Pixel_Sizes(face, 0, pxl);
		// Disable byte-alignment restriction
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		// Load first 128 characters of ASCII set
		for (unsigned char c = 0; c < 128; c++)
		{
			// Load character glyph 
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
				continue;
			}
			// Generate texture
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				face->glyph->bitmap.buffer
			);
			// Set texture options
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			// Now store character for later use
			ModernGlyph glyph = {
				texture,
				Vector2<int>(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				Vector2<int>(face->glyph->bitmap_left, face->glyph->bitmap_top),
				face->glyph->advance.x
			};
			ModernGlyphList.insert(std::pair<char, ModernGlyph>(c, glyph));
		}
		glBindTexture(GL_TEXTURE_2D, 0);
		/*
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);*/
		// Destroy FreeType once we're finished
		FT_Done_Face(face);
		FT_Done_FreeType(ft);
	}
	std::map<char, ModernGlyph> &getModernGlyphList()
	{
		return ModernGlyphList;
	}
}