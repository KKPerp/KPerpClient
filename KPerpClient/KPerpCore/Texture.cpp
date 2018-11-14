#include "Texture.hpp"
#include "Renderer.hpp"

#include <windows.h>

namespace kp {
	namespace OpenGL {
		Texture::Texture() {
			hdc = wglGetCurrentDC();
			hglrc = wglGetCurrentContext();
		}
		Texture::Texture(int Tw, int Th, unsigned int Tformat, const char* buffer, bool Tmipmap) {
			hdc = wglGetCurrentDC();
			hglrc = wglGetCurrentContext();

			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);

			glTexImage2D(GL_TEXTURE_2D, 0, Tformat, Tw, Th, 0, Tformat, GL_UNSIGNED_BYTE, buffer);

			if (Tmipmap == 1) {
				glGenerateMipmap(GL_TEXTURE_2D);
			}

			glBindTexture(GL_TEXTURE_2D, 0);
		}
		Texture::~Texture() {
			hdc = wglGetCurrentDC();
			hglrc = wglGetCurrentContext();
			if (this->hglrc == NULL) {
				return;
			}
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

		void Texture::Buffer(int Tw, int Th, const char* buffer, unsigned int Tformat) {
			hdc = wglGetCurrentDC();
			hglrc = wglGetCurrentContext();
			if (!isThisResourceisForThisContext()) {
				HDC _hdc;
				HGLRC _hglrc;
				_hdc = wglGetCurrentDC();
				_hglrc = wglGetCurrentContext();
				wglMakeCurrent(hdc, hglrc);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, Tw, Th, Tformat, GL_UNSIGNED_BYTE, buffer);
			glBindTexture(GL_TEXTURE_2D, 0);
			wglMakeCurrent(_hdc, _hglrc);
			}
			else {
				glBindTexture(GL_TEXTURE_2D, texture);
				glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, Tw, Th, Tformat, GL_UNSIGNED_BYTE, buffer);
				glBindTexture(GL_TEXTURE_2D, 0);
			}
		}

		void Texture::Attribute(unsigned int Twarps, unsigned int Twarpt, unsigned int Tminf, unsigned int Tmaxf) {
			hdc = wglGetCurrentDC();
			hglrc = wglGetCurrentContext();
			if (!isThisResourceisForThisContext()) {
				HDC _hdc;
				HGLRC _hglrc;
				_hdc = wglGetCurrentDC();
				_hglrc = wglGetCurrentContext();
				wglMakeCurrent(hdc, hglrc);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, Twarps);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, Twarpt);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, Tminf);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, Tmaxf);
			glBindTexture(GL_TEXTURE_2D, 0);
			wglMakeCurrent(_hdc, _hglrc);
			}
			else {
				glBindTexture(GL_TEXTURE_2D, texture);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, Twarps);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, Twarpt);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, Tminf);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, Tmaxf);
				glBindTexture(GL_TEXTURE_2D, 0);
			}
		}

		void Texture::Bind() {
			if (isThisResourceisForThisContext()) {
				glBindTexture(GL_TEXTURE_2D, texture);
			}
		}

		Texture& Texture::operator=(const Texture& Ttexture) {
			memcpy(this, &Ttexture, sizeof(*this));
			return *this;
		}

		int Texture::GetParameterInt(unsigned int Tattrib) {
			int _value;
			hdc = wglGetCurrentDC();
			hglrc = wglGetCurrentContext();
			if (!isThisResourceisForThisContext()) {
				HDC _hdc;
				HGLRC _hglrc;
				_hdc = wglGetCurrentDC();
				_hglrc = wglGetCurrentContext();
				wglMakeCurrent(hdc, hglrc);
			glGetTexParameteriv(GL_TEXTURE_2D, Tattrib, &_value);

			return _value;
			wglMakeCurrent(_hdc, _hglrc);
			}
			else {
				glGetTexParameteriv(GL_TEXTURE_2D, Tattrib, &_value);
				return _value;
			}
		}
		float Texture::GetParameterFloat(unsigned int Tattrib) {
			float _value;
			hdc = wglGetCurrentDC();
			hglrc = wglGetCurrentContext();
			if (!isThisResourceisForThisContext()) {
				HDC _hdc;
				HGLRC _hglrc;
				_hdc = wglGetCurrentDC();
				_hglrc = wglGetCurrentContext();
				wglMakeCurrent(hdc, hglrc);
			glGetTexParameterfv(GL_TEXTURE_2D, Tattrib, &_value);

			return _value;
			wglMakeCurrent(_hdc, _hglrc);
			}
			else {
				glGetTexParameterfv(GL_TEXTURE_2D, Tattrib, &_value);
				return _value;
			}
		}

		void Texture::SetParameterInt(unsigned int Tattrib, int Tvalue) {
			hdc = wglGetCurrentDC();
			hglrc = wglGetCurrentContext();
			if (!isThisResourceisForThisContext()) {
				HDC _hdc;
				HGLRC _hglrc;
				_hdc = wglGetCurrentDC();
				_hglrc = wglGetCurrentContext();
				wglMakeCurrent(hdc, hglrc);
			glTexParameteri(GL_TEXTURE_2D, Tattrib, Tvalue);
			wglMakeCurrent(_hdc, _hglrc);
			}
			else {
				glTexParameteri(GL_TEXTURE_2D, Tattrib, Tvalue);
			}
		}
		void Texture::SetParameterFloat(unsigned int Tattrib, float Tvalue) {
			hdc = wglGetCurrentDC();
			hglrc = wglGetCurrentContext();
			if (!isThisResourceisForThisContext()) {
				HDC _hdc;
				HGLRC _hglrc;
				_hdc = wglGetCurrentDC();
				_hglrc = wglGetCurrentContext();
				wglMakeCurrent(hdc, hglrc);
			glTexParameterf(GL_TEXTURE_2D, Tattrib, Tvalue);
			wglMakeCurrent(_hdc, _hglrc);
			}
			else {
				glTexParameterf(GL_TEXTURE_2D, Tattrib, Tvalue);
			}
		}

		void Texture::Unbind() {
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}