#ifndef _KPerpCore_Resource_hpp_
#define _KPerpCore_Resource_hpp_

#include "Shape.hpp"
#include "Renderer.hpp"
#include "OpenGLTools.hpp"
#include "ImageFile.hpp"

namespace kp {
	class Renderer;

	class Texture : public OpenGL::Texture {
	public:
		Texture();
		Texture(Renderer& Trenderer, unsigned int Tid);
		Texture(int Tw, int Th);
		Texture(int Tw, int Th, unsigned char* Tbuffer);
		Texture(ImageFile& Timg);
		Texture(Renderer& Trenderer, int Tw, int Th);
		Texture(Renderer& Trenderer, int Tw, int Th, unsigned char* Tbuffer);
		Texture(Renderer& Trenderer, ImageFile& Timg);

		void create(int Tw, int Th, unsigned char* Tbuffer);
		void create(unsigned char* Tbuffer);

		void bufferdata(unsigned char* Tbuffer);

		Point<int> getSize();

		bool _testcurrent();

		void _makeframebuffer();

		~Texture();
	private:
		void create_software(int Tw = 0, int Th = 0, unsigned char* Tbuffer = NULL);
		void create_opengl(Renderer& Trenderer, unsigned int Tid = 0, int Tw = 0, int Th = 0, unsigned char* Tbuffer = NULL);

		int width;
		int height;
		unsigned char* buffer;
	};
}

#endif