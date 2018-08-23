#include "ImageFile.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

namespace kp {
	ImageFile::ImageFile() {

	}
	ImageFile::ImageFile(const char* Tfilename, bool Tfilp) {
		stbi_set_flip_vertically_on_load(Tfilp);
		buffer = stbi_load(Tfilename, &width, &height, &channels, 0);
	}
	ImageFile::ImageFile(Type Ttype, const char* Tfilename, int Tw, int Th, unsigned char* Tbuffer, int quality) {
		switch (Ttype) {
		case PNG: {
			stbi_write_png(Tfilename, Tw, Th, 4, buffer, 0);
			break;
		}
		case BMP: {
			stbi_write_bmp(Tfilename, Tw, Th, 4, buffer);
			break;
		}
		case JPG: {
			stbi_write_jpg(Tfilename, Tw, Th, 4, buffer, quality);
			break;
		}
		}
	}

	void ImageFile::Free() {
		if (buffer != NULL) {
			delete[] buffer;
		}
	}
}

