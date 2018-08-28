#ifndef __KPerpCore_ImageFile_hpp_
#define __KPerpCore_ImageFile_hpp_

namespace kp {
	class ImageFile {
	public:
		enum Type {
			PNG,
			BMP,
			JPG,
		};

		ImageFile();
		ImageFile(const char* Tfilename, bool Tfilp);
		ImageFile(Type Ttype, const char* Tfilename, int Tw, int Th, unsigned char* Tbuffer, int quality);

		void Free();

		const char* filename;

		int width;
		int height;
		int channels;

		unsigned char* buffer;
	};
}

#endif