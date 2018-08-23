#include "Resource.hpp"

#ifdef APIENTRY
#undef APIENTRY
#endif

#include <windows.h>

namespace kp {
	Texture::Texture() {
		width = 0;
		height = 0;
		texture = 0;
		buffer = NULL;
	}
	Texture::Texture(Renderer& Trenderer, unsigned int Tid) {
		create_opengl(Trenderer, Tid);
	}
	Texture::Texture(int Tw, int Th) {
		create_software(Tw, Th);
	}
	Texture::Texture(int Tw, int Th, unsigned char* Tbuffer) {
		create_software(Tw, Th, Tbuffer);
	}
	Texture::Texture(ImageFile& Timg) {
		create_software(Timg.width, Timg.height, Timg.buffer);
	}
	Texture::Texture(Renderer& Trenderer, int Tw, int Th) {
		create_opengl(Trenderer, 0, Tw, Th);
	}
	Texture::Texture(Renderer& Trenderer, int Tw, int Th, unsigned char* Tbuffer) {
		create_opengl(Trenderer, 0, Tw, Th, Tbuffer);
	}
	Texture::Texture(Renderer& Trenderer, ImageFile& Timg) {
		create_opengl(Trenderer, 0, Timg.width, Timg.height, Timg.buffer);
	}

	void Texture::create(int Tw, int Th, unsigned char* Tbuffer) {
		if (buffer == NULL && Tbuffer != NULL) {
			create_software(Tw, Th, Tbuffer);
		}
	}
	void Texture::create(unsigned char* Tbuffer) {
		if (Tbuffer != NULL && (width*height != 0)) {
			if (buffer == NULL) {
				memcpy(buffer, Tbuffer, width * height * 4);
			}
		}
	}

	void Texture::bufferdata(unsigned char* Tbuffer) {
		if (width * height != 0) {
			if (texture == 0) {
				if (buffer != NULL && Tbuffer != NULL) {
					memcpy(buffer, Tbuffer, width * height * 4);
				}
			}
			else {
				hdc = wglGetCurrentDC();
				hglrc = wglGetCurrentContext();
				if (!(wglGetCurrentDC() == hdc) && (wglGetCurrentContext() == hglrc)) {
					HDC _hdc;
					HGLRC _hglrc;
					_hdc = wglGetCurrentDC();
					_hglrc = wglGetCurrentContext();
					wglMakeCurrent(hdc, hglrc);
					glBindTexture(GL_TEXTURE_2D, texture);
					glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, Tbuffer);
					wglMakeCurrent(_hdc, _hglrc);
				}
				else {
					glBindTexture(GL_TEXTURE_2D, texture);
					glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, Tbuffer);
				}
			}
		}
	}

	Point<int> Texture::getSize() {
		return { width,height };
	}

	bool Texture::_testcurrent() {
		return isThisResourceisForThisContext();
	}

	void Texture::_makeframebuffer() {
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
	}

	void Texture::create_software(int Tw, int Th, unsigned char* Tbuffer) {
		if (Tw*Th == 0) {
			return;
		}
		
		width = Tw;
		height = Th;

		buffer = new unsigned char[Tw*Th * 4];

		if (Tbuffer != NULL) {
			memcpy(buffer, Tbuffer, Tw * Th * 4);
		}

		texture = 0;
	}
	void Texture::create_opengl(Renderer& Trenderer, unsigned int Tid, int Tw, int Th, unsigned char* Tbuffer) {
		HGLRC _hglrc = wglGetCurrentContext();
		HDC _hdc = wglGetCurrentDC();

		Trenderer.makeCurrent();

		if (Tid == 0 && (Tw*Th != 0)) {

			width = Tw;
			height = Th;

			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Tw, Th, 0, GL_RGBA, GL_UNSIGNED_BYTE, Tbuffer);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glBindTexture(GL_TEXTURE_2D, 0);
		}
		else {
			if (!glIsTexture(Tid)) {
				texture = Tid;
			}
		}

		wglMakeCurrent(_hdc, _hglrc);
	}

	Texture::~Texture() {
		if (buffer != NULL) {
			delete[] buffer;
			buffer = NULL;
		}
		if (texture != 0) {
			hdc = wglGetCurrentDC();
			hglrc = wglGetCurrentContext();
			if (!isThisResourceisForThisContext()) {
				HDC _hdc;
				HGLRC _hglrc;
				_hdc = wglGetCurrentDC();
				_hglrc = wglGetCurrentContext();
				wglMakeCurrent(hdc, hglrc);
				glDeleteTextures(1, &texture);
				wglMakeCurrent(_hdc, _hglrc);
			}
			else {
				glDeleteTextures(1, &texture);
			}
		}
	}
}