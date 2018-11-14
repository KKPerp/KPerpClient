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
		
		// Load character glyph 
		if (FT_Load_Glyph(*face, glyphIndex, FT_LOAD_DEFAULT))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
		}
		else
		{
			int error;
			//error = FT_Library_SetLcdFilter(ft, FT_LCD_FILTER_DEFAULT);
			FT_Stroker stroker;
			FT_Stroker_New(ft, &stroker);

			

			std::map<unsigned int, ModernGlyph>::iterator it;
			it = GlyphList.find(glyphIndex);
			if (it == GlyphList.end())
			{
				FT_Glyph glyphDescStroke;
				error = FT_Get_Glyph((*face)->glyph, &glyphDescStroke);

				static double outlineThickness = 1;
				FT_Stroker_Set(stroker, static_cast<FT_Fixed>(outlineThickness * static_cast<float>(1 << 6)), FT_STROKER_LINECAP_ROUND, FT_STROKER_LINEJOIN_ROUND, 0);
				if (error == 0)
					error = FT_Glyph_Stroke(&glyphDescStroke, stroker, true);

				if (error == 0)
					error = FT_Glyph_To_Bitmap(&glyphDescStroke, FT_RENDER_MODE_NORMAL, 0, 1);

				FT_BitmapGlyph glyph_bitmap;
				FT_Bitmap *bitmap_stroke = nullptr;
				if (error == 0)
				{
					glyph_bitmap = (FT_BitmapGlyph)glyphDescStroke;
					bitmap_stroke = &glyph_bitmap->bitmap;
				}

				unsigned int cx = 0, cy = 0, ox = 0, oy = 0;
				std::vector<unsigned char> buffer;
				if (error == 0)
				{
					cx = bitmap_stroke->width;
					cy = bitmap_stroke->rows;
					ox = ((FT_BitmapGlyph)glyphDescStroke)->left;
					oy = ((FT_BitmapGlyph)glyphDescStroke)->top;

					buffer = std::vector<unsigned char>(cx * cy * 2, 0); // * 2 -> 2 color channels (red and green)
					for (unsigned int i = 0; i < cx * cy; ++i)
						buffer[i * 2 + 1] = bitmap_stroke->buffer[i];      // + 1 -> 2nd color channel
				}
				FT_Done_Glyph(glyphDescStroke);
				FT_Glyph glyphDescFill;
				FT_Get_Glyph((*face)->glyph, &glyphDescFill);
				FT_Glyph_To_Bitmap(&glyphDescFill, FT_RENDER_MODE_NORMAL, 0, 1);

				FT_Bitmap *bitmap_fill = nullptr;
				glyph_bitmap = (FT_BitmapGlyph)glyphDescFill;

				bitmap_fill = &glyph_bitmap->bitmap;

				if (bitmap_fill)
				{
					unsigned int cx_fill = bitmap_fill->width;
					unsigned int cy_fill = bitmap_fill->rows;
					unsigned int offset_x = (cx - cx_fill) / 2; // offset because the bitmap my be smaller, 
					unsigned int offset_y = (cy - cy_fill) / 2; // then the former

					for (unsigned int y = 0; y < cy_fill; ++y)
					{
						for (unsigned int x = 0; x < cx_fill; ++x)
						{
							unsigned int i_source = y * cx_fill + x;
							unsigned int i_target = (y + offset_y) * cx + x + offset_x;
							buffer[i_target * 2 + 0] = bitmap_fill->buffer[i_source]; // + 0 -> 1st color channel
						}
					}
				}

				FT_Done_Glyph(glyphDescFill);

				// Generate texture
				glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
				glGenTextures(1, &texture);
				glBindTexture(GL_TEXTURE_2D, texture);
				glTexImage2D(
					GL_TEXTURE_2D,
					0,
					GL_RG8,
					cx,
					cy,
					0,
					GL_RG,
					GL_UNSIGNED_BYTE,
					buffer.data()
				);
				glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
				// Set texture options
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				// Now store character for later use
				ModernGlyph glyph{
					texture,
					Vector2<int>(cx, cy),
					Vector2<int>(ox, oy),
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
			FT_Stroker_Done(stroker);
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

	ModernText::ModernText() {

	}
	ModernText::ModernText(ModernFont& Tfont, Vec2 Tsize, Vec2 Tpos, const std::wstring& Tstring, Color Tcolor, float Tscale) {
		font = &Tfont;
		pos = Tpos;
		string = Tstring;
		DiffuseColor = Tcolor;
		OutlineColor = Color(0, 0, 0, 0);
		size = Tsize;
		scale = Tscale;
		harfbuzzInit();
	}

	ModernText::ModernText(ModernFont& Tfont, Vec2 Tsize, Vec2 Tpos, const std::wstring& Tstring, Color Tcolor, Color TcolorOutline, float Tscale)
	{
		font = &Tfont;
		pos = Tpos;
		string = Tstring;
		DiffuseColor = Tcolor;
		OutlineColor = TcolorOutline;
		size = Tsize;
		scale = Tscale;
		harfbuzzInit();
	}

	ModernText::ModernText(ModernFont& Tfont, Vec2 Tsize, Vec2 Tpos, const std::wstring& Tstring, ModernTextStyle style, float Tscale)
	{
		font = &Tfont;
		pos = Tpos;
		string = Tstring;
		DiffuseColor = style.diffuseColor;
		OutlineColor = style.outlineColor;
		shadowShift = style.shadowShift;
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