#include "SoftwareRenderEngine.hpp"
#include <cmath>

#include "Resource.hpp"

#define colorinta(_cl_r,_cl_g,_cl_b,_cl_a) (_cl_r) + ((_cl_g) * 256U) + ((_cl_b) * 65536U) + ((_cl_a) * 16777216U)

namespace kp {
	SoftwareRenderEngine::SoftwareRenderEngine() {

	}

	bool SoftwareRenderEngine::settarget(int Tw, int Th, unsigned int* Tbuffer) {
		width = Tw;
		height = Th;
		buffer = Tbuffer;

		size = width * height;

		return 1;
	}

	void SoftwareRenderEngine::reset() {
		memset(buffer, 0, width * height * sizeof(unsigned int));
	}

	void SoftwareRenderEngine::clear(unsigned int Tcolor) {
		unsigned int* _buffer = buffer;
		int _size = size;

		_asm {
			mov edi, _buffer
			jz end

			mov eax, Tcolor	
			mov ebx, _size

		cleaning:
			mov [edi], eax	
			add edi, 4

			dec ebx

			jnz cleaning
		end:
		}
	}
	void SoftwareRenderEngine::point(int Tx, int Ty, unsigned int Tcolor) {
		if (!buffer) {
			return;
		}
		buffer[(Ty*width) + Tx] = Tcolor;
	}
	void SoftwareRenderEngine::rectangle(int Tx1, int Ty1, int Tx2, int Ty2, unsigned int Tcolor) {
		if (!buffer) {
			return;
		}
		if (Tx1 < 0) {
			Tx1 = 0;
		}
		if (Ty1 < 0) {
			Ty1 = 0;
		}
		if (Tx2 >= width) {
			Tx2 = width-1;
		}
		if (Ty2 >= height) {
			Ty2 = height-1;
		}

		int _dx = abs(Tx2 - Tx1) + 1;
		int _dy = abs(Ty2 - Ty1) + 1;
		int _x1 = (Tx1 < Tx2) ? Tx1 : Tx2;
		int _y1 = (Ty1 < Ty2) ? Ty1 : Ty2;
		char _xd = (Tx2 > Tx1) ? 1 : (Tx2 == Tx1) ? 0 : -1;
		char _yd = (Ty2 > Ty1) ? 1 : (Ty2 == Ty1) ? 0 : -1;

		int _i = 0;
		int _j = 0;

		if (*((unsigned char*)(&Tcolor) + 3)) {
			for (int i = 0;i < (_dy);i++) {
				unsigned int _xf = (((_i + Ty1))*width) + Tx1;

				_j = _xf;
				for (unsigned int j = _xf;j < _xf + (_dx);j++) {
					if (_j > (unsigned int)buffer) {
						break;
					}
					/*
					if ((char*)&(buffer[_j]) < (char*)buffer) {
						int wtf = 0;
					}
					if (((char*)&(buffer[_j])) >= ((char*)buffer) + (width*height*4)) {
						int wtf = 0;
					}
					*/
					//if (_j < (unsigned int)buffer) {
					//	int wtf = 0;
					//}

					buffer[_j] = Tcolor;
					_j += _xd;
				}

				_i += _yd;
			}
		}
	}
	void SoftwareRenderEngine::rectangle(Rectangle<int> Trect, unsigned int Tcolor) {
		if (!buffer) {
			return;
		}
		if (Trect.a.x < 0) {
			Trect.a.x = 0;
		}
		if (Trect.a.y < 0) {
			Trect.a.y = 0;
		}
		if (Trect.c.x >= width) {
			Trect.c.x = width - 1;
		}
		if (Trect.c.y >= height) {
			Trect.c.y = height - 1;
		}
		int _dx = abs(Trect.c.x - Trect.a.x) + 1;
		int _dy = abs(Trect.c.y - Trect.a.y) + 1;
		int _x1 = (Trect.a.x < Trect.c.x) ? Trect.a.x : Trect.c.x;
		int _y1 = (Trect.a.y < Trect.c.y) ? Trect.a.y : Trect.c.y;
		char _xd = (Trect.c.x > Trect.a.x) ? 1 : (Trect.c.x == Trect.a.x) ? 0 : -1;
		char _yd = (Trect.c.y > Trect.a.y) ? 1 : (Trect.c.y == Trect.a.y) ? 0 : -1;

		int _i = 0;
		int _j = 0;

		for (int i = 0;i < (_dy);i++) {
			unsigned int _xf = (((_i + Trect.a.y))*width) + Trect.a.x;

			_j = _xf;
			for (unsigned int j = _xf;j < _xf + (_dx);j++) {
				if (_j >(unsigned int)buffer) {
					break;
				}

				if (*((unsigned char*)(&buffer[_j]) + 3)) {
					buffer[_j] = Tcolor;
				}
				_j += _xd;
			}

			_i += _yd;
		}
	}

	void SoftwareRenderEngine::rectangle(int Tx1, int Ty1, int Tx2, int Ty2, unsigned int Tcolor1, unsigned int Tcolor2, unsigned int Tcolor3, unsigned int Tcolor4) {
		if (!buffer) {
			return;
		}
		int _dx = abs(Tx2 - Tx1) + 1;
		int _dy = abs(Ty2 - Ty1) + 1;
		int _x1 = (Tx1 < Tx2) ? Tx1 : Tx2;
		int _y1 = (Ty1 < Ty2) ? Ty1 : Ty2;
		char _xd = (Tx2 > Tx1) ? 1 : (Tx2 == Tx1) ? 0 : -1;
		char _yd = (Ty2 > Ty1) ? 1 : (Ty2 == Ty1) ? 0 : -1;

		int _i = 0;
		int _j = 0;

		int _tj;

		float _cx;
		float _cy;

		unsigned int _color;

		for (int i = 0;i < (_dy);i++) {
			unsigned int _xf = (((_i + Ty1))*width) + Tx1;

			_j = _xf;
			_cy = i / (float)_dy;
			unsigned char _c1r = (((unsigned char*)&Tcolor1)[0]) + (((((unsigned char*)&Tcolor4)[0]) - (((unsigned char*)&Tcolor1)[0])) * (_cy));
			unsigned char _c2r = ((unsigned char*)&Tcolor2)[0] + ((((unsigned char*)&Tcolor3)[0] - ((unsigned char*)&Tcolor2)[0]) * (_cy));
			unsigned char _c1g = (((unsigned char*)&Tcolor1)[1]) + (((((unsigned char*)&Tcolor4)[1]) - (((unsigned char*)&Tcolor1)[1])) * (_cy));
			unsigned char _c2g = ((unsigned char*)&Tcolor2)[1] + ((((unsigned char*)&Tcolor3)[1] - ((unsigned char*)&Tcolor2)[1]) * (_cy));
			unsigned char _c1b = (((unsigned char*)&Tcolor1)[2]) + (((((unsigned char*)&Tcolor4)[2]) - (((unsigned char*)&Tcolor1)[2])) * (_cy));
			unsigned char _c2b = ((unsigned char*)&Tcolor2)[2] + ((((unsigned char*)&Tcolor3)[2] - ((unsigned char*)&Tcolor2)[2]) * (_cy));

			_tj = 0;

			for (unsigned int j = _xf;j < _xf + (_dx);j++) {
				if (_j > (unsigned int)buffer) {
					break;
				}

				_cx = _tj / (float)_dx;

				((unsigned char*)&_color)[0] = (_c1r + ((_c2r - _c1r) * (_cx)));
				((unsigned char*)&_color)[1] = (_c1g + ((_c2g - _c1g) * (_cx)));
				((unsigned char*)&_color)[2] = (_c1b + ((_c2b - _c1b) * (_cx)));

				buffer[_j] = _color;
				_j += _xd;
				_tj++;
			}

			_i += _yd;
		}
	}

	void SoftwareRenderEngine::rectangle(const Texture& Ttexture, int Tx1, int Ty1, int Tx2, int Ty2) {
		if (!buffer) {
			return;
		}
		int _dx = abs(Tx2 - Tx1) + 1;
		int _dy = abs(Ty2 - Ty1) + 1;
		int _x1 = (Tx1 < Tx2) ? Tx1 : Tx2;
		int _y1 = (Ty1 < Ty2) ? Ty1 : Ty2;
		char _xd = (Tx2 > Tx1) ? 1 : (Tx2 == Tx1) ? 0 : -1;
		char _yd = (Ty2 > Ty1) ? 1 : (Ty2 == Ty1) ? 0 : -1;

		int _i = 0;
		int _j = 0;

		int _tj;

		float _cx;
		float _cy;

		unsigned int _color;

		int _x;
		int _y;

		for (int i = 0;i < (_dy);i++) {
			unsigned int _xf = (((_i + Ty1))*width) + Tx1;

			_j = _xf;
			_cy = i / (float)_dy;
			
			_y = (int)(Ttexture.height*_cy);

			_tj = 0;

			for (unsigned int j = _xf;j < _xf + (_dx);j++) {
				if (_j >(unsigned int)buffer) {
					break;
				}

				_cx = _tj / (float)_dx;

				_x = (int)(Ttexture.width * _cx);

				_color = ((unsigned int*)Ttexture.buffer)[(Ttexture.width*_y) + ((_x))];

				buffer[_j] = _color;

				_j += _xd;
				_tj++;
			}

			_i += _yd;
		}
	}

	void SoftwareRenderEngine::rectangle(const Texture& Ttexture, int Tx1, int Ty1, int Tx2, int Ty2, int Ttx1, int Tty1, int Ttx2, int Tty2) {
		if (!buffer) {
			return;
		}
		int _dx = abs(Tx2 - Tx1) + 1;
		int _dy = abs(Ty2 - Ty1) + 1;
		int _x1 = (Tx1 < Tx2) ? Tx1 : Tx2;
		int _y1 = (Ty1 < Ty2) ? Ty1 : Ty2;
		char _xd = (Tx2 > Tx1) ? 1 : (Tx2 == Tx1) ? 0 : -1;
		char _yd = (Ty2 > Ty1) ? 1 : (Ty2 == Ty1) ? 0 : -1;

		int _i = 0;
		int _j = 0;

		int _tj;

		float _cx;
		float _cy;

		unsigned int _color;

		int _x;
		int _y;

		int _w = (Ttx2 - Ttx1);
		int _h = (Tty2 - Tty1);

		if (!(_w && _h)) {
			return;
		}

		if (_w < 0) {
			Ttx1--;
		}
		if (_h < 0) {
			Tty1--;
		}

		for (int i = 0;i < (_dy);i++) {
			unsigned int _xf = (((_i + Ty1))*width) + Tx1;

			_j = _xf;
			_cy = i / (float)_dy;

			_y = Tty1 + (int)(_h *_cy);

			_tj = 0;

			for (unsigned int j = _xf;j < _xf + (_dx);j++) {
				if (_j >(unsigned int)buffer) {
					break;
				}

				_cx = _tj / (float)_dx;

				_x = Ttx1 + (int)(_w * _cx);

				_color = ((unsigned int*)Ttexture.buffer)[(Ttexture.width*_y) + ((_x))];

				buffer[_j] = _color;

				_j += _xd;
				_tj++;
			}

			_i += _yd;
		}
	}

	void SoftwareRenderEngine::rectangle(const Texture& Ttexture, int Tx1, int Ty1, int Tx2, int Ty2, unsigned int Tcolor) {
		if (!buffer) {
			return;
		}
		int _dx = abs(Tx2 - Tx1) + 1;
		int _dy = abs(Ty2 - Ty1) + 1;
		int _x1 = (Tx1 < Tx2) ? Tx1 : Tx2;
		int _y1 = (Ty1 < Ty2) ? Ty1 : Ty2;
		char _xd = (Tx2 > Tx1) ? 1 : (Tx2 == Tx1) ? 0 : -1;
		char _yd = (Ty2 > Ty1) ? 1 : (Ty2 == Ty1) ? 0 : -1;

		int _i = 0;
		int _j = 0;

		int _tj;

		float _cx;
		float _cy;

		unsigned int _color;
		unsigned int _texcolor;

		int _x;
		int _y;

		for (int i = 0;i < (_dy);i++) {
			unsigned int _xf = (((_i + Ty1))*width) + Tx1;

			_j = _xf;
			_cy = i / (float)_dy;

			_y = (int)(Ttexture.height*_cy);

			_tj = 0;

			for (unsigned int j = _xf;j < _xf + (_dx);j++) {
				if (_j >(unsigned int)buffer) {
					break;
				}

				_cx = _tj / (float)_dx;

				_x = (int)(Ttexture.width * _cx);

				_texcolor = ((unsigned int*)Ttexture.buffer)[(Ttexture.width*_y) + ((_x))];

				((unsigned char*)&_color)[0] = (((((unsigned char*)&Tcolor)[0]) / 255.0f)*(((unsigned char*)&_texcolor)[0] / 255.0f)) * 255;
				((unsigned char*)&_color)[1] = (((((unsigned char*)&Tcolor)[1]) / 255.0f)*(((unsigned char*)&_texcolor)[1] / 255.0f)) * 255;
				((unsigned char*)&_color)[2] = (((((unsigned char*)&Tcolor)[2]) / 255.0f)*(((unsigned char*)&_texcolor)[2] / 255.0f)) * 255;

				buffer[_j] = _color;

				_j += _xd;
				_tj++;
			}

			_i += _yd;
		}
	}
	void SoftwareRenderEngine::rectangle(const Texture& Ttexture, int Tx1, int Ty1, int Tx2, int Ty2, int Ttx1, int Tty1, int Ttx2, int Tty2, unsigned int Tcolor) {
		if (!buffer) {
			return;
		}
		int _dx = abs(Tx2 - Tx1) + 1;
		int _dy = abs(Ty2 - Ty1) + 1;
		int _x1 = (Tx1 < Tx2) ? Tx1 : Tx2;
		int _y1 = (Ty1 < Ty2) ? Ty1 : Ty2;
		char _xd = (Tx2 > Tx1) ? 1 : (Tx2 == Tx1) ? 0 : -1;
		char _yd = (Ty2 > Ty1) ? 1 : (Ty2 == Ty1) ? 0 : -1;

		int _i = 0;
		int _j = 0;

		int _tj;

		float _cx;
		float _cy;

		unsigned int _color;
		unsigned int _texcolor;

		int _x;
		int _y;

		int _w = (Ttx2 - Ttx1);
		int _h = (Tty2 - Tty1);

		if (!(_w && _h)) {
			return;
		}

		if (_w < 0) {
			Ttx1--;
		}
		if (_h < 0) {
			Tty1--;
		}

		float _ccol;

		for (int i = 0;i < (_dy);i++) {
			unsigned int _xf = (((_i + Ty1))*width) + Tx1;

			_j = _xf;
			_cy = i / (float)_dy;

			_y = Tty1 + (int)(_h *_cy);

			_tj = 0;

			for (unsigned int j = _xf;j < _xf + (_dx);j++) {
				if (_j >(unsigned int)buffer) {
					break;
				}

				_cx = _tj / (float)_dx;

				_x = Ttx1 + (int)(_w * _cx);

				_texcolor = ((unsigned int*)Ttexture.buffer)[(Ttexture.width*_y) + ((_x))];

				((unsigned char*)&_color)[0] = (((((unsigned char*)&Tcolor)[0]) / 255.0f)*(((unsigned char*)&_texcolor)[0] / 255.0f)) * 255;
				((unsigned char*)&_color)[1] = (((((unsigned char*)&Tcolor)[1]) / 255.0f)*(((unsigned char*)&_texcolor)[1] / 255.0f)) * 255;
				((unsigned char*)&_color)[2] = (((((unsigned char*)&Tcolor)[2]) / 255.0f)*(((unsigned char*)&_texcolor)[2] / 255.0f)) * 255;

				buffer[_j] = _color;

				_j += _xd;
				_tj++;
			}

			_i += _yd;
		}


	}

	void SoftwareRenderEngine::rectangle(const Texture& Ttexture, int Tx1, int Ty1, int Tx2, int Ty2, unsigned int Tcolor1, unsigned int Tcolor2, unsigned int Tcolor3, unsigned int Tcolor4) {
		if (!buffer) {
			return;
		}
		int _dx = abs(Tx2 - Tx1) + 1;
		int _dy = abs(Ty2 - Ty1) + 1;
		int _x1 = (Tx1 < Tx2) ? Tx1 : Tx2;
		int _y1 = (Ty1 < Ty2) ? Ty1 : Ty2;
		char _xd = (Tx2 > Tx1) ? 1 : (Tx2 == Tx1) ? 0 : -1;
		char _yd = (Ty2 > Ty1) ? 1 : (Ty2 == Ty1) ? 0 : -1;

		int _i = 0;
		int _j = 0;

		int _tj;

		float _cx;
		float _cy;

		unsigned int _color;
		unsigned int _texcolor;

		int _x;
		int _y;

		for (int i = 0;i < (_dy);i++) {
			unsigned int _xf = (((_i + Ty1))*width) + Tx1;

			_j = _xf;
			_cy = i / (float)_dy;

			unsigned char _c1r = (((unsigned char*)&Tcolor1)[0]) + (((((unsigned char*)&Tcolor4)[0]) - (((unsigned char*)&Tcolor1)[0])) * (_cy));
			unsigned char _c2r = ((unsigned char*)&Tcolor2)[0] + ((((unsigned char*)&Tcolor3)[0] - ((unsigned char*)&Tcolor2)[0]) * (_cy));
			unsigned char _c1g = (((unsigned char*)&Tcolor1)[1]) + (((((unsigned char*)&Tcolor4)[1]) - (((unsigned char*)&Tcolor1)[1])) * (_cy));
			unsigned char _c2g = ((unsigned char*)&Tcolor2)[1] + ((((unsigned char*)&Tcolor3)[1] - ((unsigned char*)&Tcolor2)[1]) * (_cy));
			unsigned char _c1b = (((unsigned char*)&Tcolor1)[2]) + (((((unsigned char*)&Tcolor4)[2]) - (((unsigned char*)&Tcolor1)[2])) * (_cy));
			unsigned char _c2b = ((unsigned char*)&Tcolor2)[2] + ((((unsigned char*)&Tcolor3)[2] - ((unsigned char*)&Tcolor2)[2]) * (_cy));

			_y = (int)(Ttexture.height*_cy);

			_tj = 0;

			for (unsigned int j = _xf;j < _xf + (_dx);j++) {
				if (_j >(unsigned int)buffer) {
					break;
				}

				_cx = _tj / (float)_dx;

				_x = (int)(Ttexture.width * _cx);

				_texcolor = ((unsigned int*)Ttexture.buffer)[(Ttexture.width*_y) + ((_x))];

				((unsigned char*)&_color)[0] = (((_c1r + ((_c2r - _c1r) * (_cx))) / 255.0f)*(((unsigned char*)&_texcolor)[0] / 255.0f)) * 255;
				((unsigned char*)&_color)[1] = (((_c1g + ((_c2g - _c1g) * (_cx))) / 255.0f)*(((unsigned char*)&_texcolor)[1] / 255.0f)) * 255;
				((unsigned char*)&_color)[2] = (((_c1b + ((_c2b - _c1b) * (_cx))) / 255.0f)*(((unsigned char*)&_texcolor)[2] / 255.0f)) * 255;

				buffer[_j] = _color;

				_j += _xd;
				_tj++;
			}

			_i += _yd;
		}
	}
	void SoftwareRenderEngine::rectangle(const Texture& Ttexture, int Tx1, int Ty1, int Tx2, int Ty2, int Ttx1, int Tty1, int Ttx2, int Tty2, unsigned int Tcolor1, unsigned int Tcolor2, unsigned int Tcolor3, unsigned int Tcolor4) {
		if (!buffer) {
			return;
		}
		int _dx = abs(Tx2 - Tx1) + 1;
		int _dy = abs(Ty2 - Ty1) + 1;
		int _x1 = (Tx1 < Tx2) ? Tx1 : Tx2;
		int _y1 = (Ty1 < Ty2) ? Ty1 : Ty2;
		char _xd = (Tx2 > Tx1) ? 1 : (Tx2 == Tx1) ? 0 : -1;
		char _yd = (Ty2 > Ty1) ? 1 : (Ty2 == Ty1) ? 0 : -1;

		int _i = 0;
		int _j = 0;

		int _tj;

		float _cx;
		float _cy;

		unsigned int _color;
		unsigned int _texcolor;

		int _x;
		int _y;

		int _w = (Ttx2 - Ttx1);
		int _h = (Tty2 - Tty1);

		if (!(_w && _h)) {
			return;
		}

		if (_w < 0) {
			Ttx1--;
		}
		if (_h < 0) {
			Tty1--;
		}

		float _ccol;

		for (int i = 0;i < (_dy);i++) {
			unsigned int _xf = (((_i + Ty1))*width) + Tx1;

			_j = _xf;
			_cy = i / (float)_dy;

			unsigned char _c1r = (((unsigned char*)&Tcolor1)[0]) + (((((unsigned char*)&Tcolor4)[0]) - (((unsigned char*)&Tcolor1)[0])) * (_cy));
			unsigned char _c2r = ((unsigned char*)&Tcolor2)[0] + ((((unsigned char*)&Tcolor3)[0] - ((unsigned char*)&Tcolor2)[0]) * (_cy));
			unsigned char _c1g = (((unsigned char*)&Tcolor1)[1]) + (((((unsigned char*)&Tcolor4)[1]) - (((unsigned char*)&Tcolor1)[1])) * (_cy));
			unsigned char _c2g = ((unsigned char*)&Tcolor2)[1] + ((((unsigned char*)&Tcolor3)[1] - ((unsigned char*)&Tcolor2)[1]) * (_cy));
			unsigned char _c1b = (((unsigned char*)&Tcolor1)[2]) + (((((unsigned char*)&Tcolor4)[2]) - (((unsigned char*)&Tcolor1)[2])) * (_cy));
			unsigned char _c2b = ((unsigned char*)&Tcolor2)[2] + ((((unsigned char*)&Tcolor3)[2] - ((unsigned char*)&Tcolor2)[2]) * (_cy));

			_y = Tty1 + (int)(_h *_cy);

			_tj = 0;

			for (unsigned int j = _xf;j < _xf + (_dx);j++) {
				if (_j > (unsigned int)buffer) {
					break;
				}

				_cx = _tj / (float)_dx;

				_x = Ttx1 + (int)(_w * _cx);

				_texcolor = ((unsigned int*)Ttexture.buffer)[(Ttexture.width*_y) + ((_x))];

				((unsigned char*)&_color)[0] = (((_c1r + ((_c2r - _c1r) * (_cx))) / 255.0f)*(((unsigned char*)&_texcolor)[0] / 255.0f)) * 255;
				((unsigned char*)&_color)[1] = (((_c1g + ((_c2g - _c1g) * (_cx))) / 255.0f)*(((unsigned char*)&_texcolor)[1] / 255.0f)) * 255;
				((unsigned char*)&_color)[2] = (((_c1b + ((_c2b - _c1b) * (_cx))) / 255.0f)*(((unsigned char*)&_texcolor)[2] / 255.0f)) * 255;

				buffer[_j] = _color;

				_j += _xd;
				_tj++;
			}

			_i += _yd;
		}

		
	}

	void SoftwareRenderEngine::line(int Tx1, int Ty1, int Tx2, int Ty2, unsigned int Tcolor) {
		if (!buffer) {
			return;
		}
		float _dx = (Tx2 - Tx1);
		float _dy = (Ty2 - Ty1);

		float _de;// = (_dy / _dx);

		float _err = 0;
		float __x = Tx1;
		int _sx = ((_dx > 0) - (_dx < 0));
		int _sy = ((_dy > 0) - (_dy < 0));
		float __y = Ty1;

		if ((_dx < 0 ? -_dx : _dx) > (_dy < 0 ? -_dy : _dy)) {
			_de = (_dy / (_dx < 0 ? -_dx : _dx));//(((_dy / _dx) < 0 ? -(_dy / _dx) : (_dy / _dx)));
												 //float __de = _dy /

			if (Ty2 == -9) {
				int fuck = 0;
			}

			float _b = (Ty1 - (_de*Tx1));
			for (unsigned int i = 0;i <= (_dx < 0 ? -_dx : _dx);i++) {
				if ((__x) >= 0 && (__x) < width && (__y) >= 0 && (__y) < height) {
					buffer[(((int)round(__y))*width) + ((int)round(__x))] = Tcolor;
				}

				__x += _sx;
				__y += _de;
			}
		}
		else {
			_de = (_dx / (_dy < 0 ? -_dy : _dy));
			if (_de < 0) {
				int lol = 0;
			}
			for (unsigned int i = 0;i <= (_dy < 0 ? -_dy : _dy);i++) {
				if ((__x) >= 0 && (__x) < width && (__y) >= 0 && (__y) < height) {
					buffer[(((int)round(__y))*width) + ((int)round(__x))] = Tcolor;
				}
				__x += _de;
				__y += _sy;
			}
		}
	}
	void SoftwareRenderEngine::line(int Tx1, int Ty1, int Tx2, int Ty2, unsigned int Tcolor1, unsigned int Tcolor2) {
		if (!buffer) {
			return;
		}
		float _dx = (Tx2 - Tx1);
		float _dy = (Ty2 - Ty1);

		float _de;// = (_dy / _dx);

		float _err = 0;
		float __x = Tx1;
		int _sx = ((_dx > 0) - (_dx < 0));
		int _sy = ((_dy > 0) - (_dy < 0));
		float __y = Ty1;

		unsigned int _color;

		if ((_dx < 0 ? -_dx : _dx) >(_dy < 0 ? -_dy : _dy)) {
			_de = (_dy / (_dx < 0 ? -_dx : _dx));//(((_dy / _dx) < 0 ? -(_dy / _dx) : (_dy / _dx)));
												 //float __de = _dy /

			int _w = (_dx < 0 ? -_dx : _dx);
			float _l;
			for (unsigned int i = 0;i <= _w;i++) {
				if ((__x) >= 0 && (__x) < width && (__y) >= 0 && (__y) < height) {
					_l = (i / (float)_w);
					((unsigned char*)&_color)[0] = ((unsigned char*)&Tcolor1)[0] + ((((unsigned char*)&Tcolor2)[0] - ((unsigned char*)&Tcolor1)[0]) * (_l));
					((unsigned char*)&_color)[1] = ((unsigned char*)&Tcolor1)[1] + ((((unsigned char*)&Tcolor2)[1] - ((unsigned char*)&Tcolor1)[1]) * (_l));
					((unsigned char*)&_color)[2] = ((unsigned char*)&Tcolor1)[2] + ((((unsigned char*)&Tcolor2)[2] - ((unsigned char*)&Tcolor1)[2]) * (_l));
					buffer[(((int)round(__y))*width) + ((int)round(__x))] = _color;
				}

				__x += _sx;
				__y += _de;
			}
		}
		else {
			_de = (_dx / (_dy < 0 ? -_dy : _dy));

			int _h = (_dy < 0 ? -_dy : _dy);
			float _l;
			for (unsigned int i = 0;i <= _h;i++) {
				if ((__x) >= 0 && (__x) < width && (__y) >= 0 && (__y) < height) {
					_l = (i / (float)_h);
					((unsigned char*)&_color)[0] = ((unsigned char*)&Tcolor1)[0] + ((((unsigned char*)&Tcolor2)[0] - ((unsigned char*)&Tcolor1)[0]) * (_l));
					((unsigned char*)&_color)[1] = ((unsigned char*)&Tcolor1)[1] + ((((unsigned char*)&Tcolor2)[1] - ((unsigned char*)&Tcolor1)[1]) * (_l));
					((unsigned char*)&_color)[2] = ((unsigned char*)&Tcolor1)[2] + ((((unsigned char*)&Tcolor2)[2] - ((unsigned char*)&Tcolor1)[2]) * (_l));
					buffer[(((int)round(__y))*width) + ((int)round(__x))] = _color;
				}
				__x += _de;
				__y += _sy;
			}
		}
	}

	void SoftwareRenderEngine::triangle(int Tx1, int Ty1, int Tx2, int Ty2, int Tx3, int Ty3, unsigned int Tcolor) {
		if (!buffer) {
			return;
		}
		Point<int> _p1 = { Tx1,Ty1 };
		Point<int> _p2 = { Tx2,Ty2 };
		Point<int> _p3 = { Tx3,Ty3 };

		Point<int> _Pcalc = (_p1.y < _p2.y) ? _p1 : _p2;
		Point<int> _tp1 = ((_Pcalc.y < _p3.y) ? _Pcalc : _p3);
		_Pcalc = (_p1.y > _p2.y) ? _p1 : _p2;
		Point<int> _bp1 = ((_Pcalc.y > _p3.y) ? _Pcalc : _p3);
		_Pcalc = (_p1.x < _p2.x) ? _p1 : _p2;
		Point<int> _lp1 = ((_Pcalc.x < _p3.x) ? _Pcalc : _p3);
		_Pcalc = (_p1.x > _p2.x) ? _p1 : _p2;
		Point<int> _rp1 = ((_Pcalc.x > _p3.x) ? _Pcalc : _p3);

		Point<int> _mp1 = _tp1;

		if ((_tp1.x != _p1.x ||
			_tp1.y != _p1.y) &&
			(_bp1.x != _p1.x ||
				_bp1.y != _p1.y)) {
			_mp1 = _p1;
		}
		if ((_tp1.x != _p2.x ||
			_tp1.y != _p2.y) &&
			(_bp1.x != _p2.x ||
				_bp1.y != _p2.y)) {
			_mp1 = _p2;
		}
		if ((_tp1.x != _p3.x ||
			_tp1.y != _p3.y) &&
			(_bp1.x != _p3.x ||
				_bp1.y != _p3.y)) {
			_mp1 = _p3;
		}

		if ((_tp1.x == _mp1.x) && (_tp1.y == _mp1.y)) {
			line(_tp1.x, _tp1.y, _bp1.x, _bp1.y, Tcolor);
			return;
		}

		//int _rx1 = ((((_p1.x > _p2.x) ? _p1.x : _p2.x) > _p3.x) ? ((_p1.x > _p2.x) ? _p1.x : _p2.x) : _p3.x);

		float mslope = (_tp1.x - _bp1.x) / abs(float(_tp1.y - _bp1.y));
		float slope1 = (_mp1.x - _tp1.x) / abs(float(_mp1.y - _tp1.y));
		float slope2 = (_mp1.x - _bp1.x) / abs(float(_bp1.y - _mp1.y));

		float _lx = _tp1.x;
		float _rx = _tp1.x;

		float _lslope = (_tp1.x < _mp1.x ? mslope : mslope);
		float _rslope = (_tp1.x > _mp1.x ? slope1 : slope1);

		//float _ms = ()
		if (_tp1.y != _mp1.y) {
			for (int i = _tp1.y;i < _mp1.y; i++) {
				if ((i) >= 0 && (i) < (int)height) {
					for (int j = round(_lx < _rx ? _lx : _rx);j <= round(_lx > _rx ? _lx : _rx);j++) {
						if ((j) >= 0 && (j) < (int)width) {
							buffer[((i)*width) + (j)] = Tcolor;
						}
					}
				}

				_lx -= _lslope;
				_rx += _rslope;
			}

			_lslope = (_mp1.x > _bp1.x ? mslope : mslope);
			_rslope = (_mp1.x < _bp1.x ? slope2 : slope2);
		}
		else {
			_lx = (_tp1.x < _mp1.x ? _tp1.x : _mp1.x);
			_rx = (_tp1.x > _mp1.x ? _tp1.x : _mp1.x);

			_lslope = (_tp1.x > _mp1.x ? slope2 : mslope);
			_rslope = (_tp1.x < _mp1.x ? slope2 : mslope);
		}

		

		for (int i = _mp1.y;i <= _bp1.y; i++) {
			if ((i) >= 0 && (i) < (int)height) {
				for (int j = round(_lx < _rx ? _lx : _rx);j <= round(_lx > _rx ? _lx : _rx);j++) {
					if ((j) >= 0 && (j) < (int)width) {
						buffer[((i)*width) + (j)] = Tcolor;
					}
				}
			}

			_lx -= _lslope;
			_rx -= _rslope;
		}
	}

	void SoftwareRenderEngine::triangle(int Tx1, int Ty1, int Tx2, int Ty2, int Tx3, int Ty3, unsigned int Tcolor1, unsigned int Tcolor2, unsigned int Tcolor3) {
		if (!buffer) {
			return;
		}
		struct PointColor {
			int x;
			int y;
			unsigned int color;
		};

		PointColor _p1 = { Tx1,Ty1, Tcolor1 };
		PointColor _p2 = { Tx2,Ty2, Tcolor2 };
		PointColor _p3 = { Tx3,Ty3, Tcolor3 };

		PointColor _Pcalc = (_p1.y < _p2.y) ? _p1 : _p2;
		PointColor _tp1 = ((_Pcalc.y < _p3.y) ? _Pcalc : _p3);
		_Pcalc = (_p1.y > _p2.y) ? _p1 : _p2;
		PointColor _bp1 = ((_Pcalc.y > _p3.y) ? _Pcalc : _p3);
		_Pcalc = (_p1.x < _p2.x) ? _p1 : _p2;
		PointColor _lp1 = ((_Pcalc.x < _p3.x) ? _Pcalc : _p3);
		_Pcalc = (_p1.x > _p2.x) ? _p1 : _p2;
		PointColor _rp1 = ((_Pcalc.x > _p3.x) ? _Pcalc : _p3);

		PointColor _mp1 = _tp1;

		if ((_tp1.x != _p1.x ||
			_tp1.y != _p1.y) &&
			(_bp1.x != _p1.x ||
				_bp1.y != _p1.y)) {
			_mp1 = _p1;
		}
		if ((_tp1.x != _p2.x ||
			_tp1.y != _p2.y) &&
			(_bp1.x != _p2.x ||
				_bp1.y != _p2.y)) {
			_mp1 = _p2;
		}
		if ((_tp1.x != _p3.x ||
			_tp1.y != _p3.y) &&
			(_bp1.x != _p3.x ||
				_bp1.y != _p3.y)) {
			_mp1 = _p3;
		}

		if ((_tp1.x == _mp1.x) && (_tp1.y == _mp1.y)) {
			line(_tp1.x, _tp1.y, _bp1.x, _bp1.y, _tp1.color, _bp1.color);
			//line(_tp1.x, _tp1.y, _bp1.x, _bp1.y, Tcolor);
			return;
		}
		//int _rx1 = ((((_p1.x > _p2.x) ? _p1.x : _p2.x) > _p3.x) ? ((_p1.x > _p2.x) ? _p1.x : _p2.x) : _p3.x);
			  
		float mslope = (_tp1.x - _bp1.x) / abs(float(_tp1.y - _bp1.y));
		float slope1 = (_mp1.x - _tp1.x) / abs(float(_mp1.y - _tp1.y));
		float slope2 = (_mp1.x - _bp1.x) / abs(float(_bp1.y - _mp1.y));

		float _lx = _tp1.x;
		float _rx = _tp1.x;

		float _lslope = (_tp1.x < _mp1.x ? mslope : mslope);
		float _rslope = (_tp1.x > _mp1.x ? slope1 : slope1);

		unsigned int _color;
		float _clx;
		float _cly;
		float _w1;
		float _w2;
		float _w3;
		float _h = _bp1.y - _tp1.y;
		float _h2 = _mp1.y - _tp1.y;

		float _cly2;

		int _i = 0;
		int _i2 = 0;
		int _j = 0; 

		//float _ms = ()
		if (-_lslope <= _rslope) {
			if (_tp1.y != _mp1.y) {
				for (int i = _tp1.y;i < _mp1.y; i++) {
					if ((i) >= 0 && (i) < (int)height) {
						_w1 = round(_lx < _rx ? _lx : _rx);
						_w2 = round(_lx > _rx ? _lx : _rx);
						_w3 = (_w2 - _w1) + 1;
						_cly = (_i / _h);
						_cly2 = (_i2 / _h2);
						_j = 0;
						unsigned char _c1r = (((unsigned char*)&_tp1.color)[0]) + (((((unsigned char*)&_bp1.color)[0]) - (((unsigned char*)&_tp1.color)[0])) * (_cly));
						unsigned char _c2r = ((unsigned char*)&_tp1.color)[0] + ((((unsigned char*)&_mp1.color)[0] - ((unsigned char*)&_tp1.color)[0]) * (_cly2));
						unsigned char _c1g = (((unsigned char*)&_tp1.color)[1]) + (((((unsigned char*)&_bp1.color)[1]) - (((unsigned char*)&_tp1.color)[1])) * (_cly));
						unsigned char _c2g = ((unsigned char*)&_tp1.color)[1] + ((((unsigned char*)&_mp1.color)[1] - ((unsigned char*)&_tp1.color)[1]) * (_cly2));
						unsigned char _c1b = (((unsigned char*)&_tp1.color)[2]) + (((((unsigned char*)&_bp1.color)[2]) - (((unsigned char*)&_tp1.color)[2])) * (_cly));
						unsigned char _c2b = ((unsigned char*)&_tp1.color)[2] + ((((unsigned char*)&_mp1.color)[2] - ((unsigned char*)&_tp1.color)[2]) * (_cly2));
						for (int j = _w1;j <= _w2;j++) {
							if ((j) >= 0 && (j) < (int)width) {
								_clx = (_j / _w3);
								((unsigned char*)&_color)[0] = (_c1r + ((_c2r - _c1r) * (_clx)));
								((unsigned char*)&_color)[1] = (_c1g + ((_c2g - _c1g) * (_clx)));
								((unsigned char*)&_color)[2] = (_c1b + ((_c2b - _c1b) * (_clx)));
								buffer[((i)*width) + (j)] = _color;
							}
							_j++;
						}
					}

					_lx -= _lslope;
					_rx += _rslope;
					_i++;
					_i2++;
				}

				_lslope = (_mp1.x > _bp1.x ? mslope : mslope);
				_rslope = (_mp1.x < _bp1.x ? slope2 : slope2);
			}
			else {
				_lx = (_tp1.x < _mp1.x ? _tp1.x : _mp1.x);
				_rx = (_tp1.x > _mp1.x ? _tp1.x : _mp1.x);

				_lslope = (_tp1.x > _mp1.x ? slope2 : mslope);
				_rslope = (_tp1.x < _mp1.x ? slope2 : mslope);
			}
		}
		else {
			if (_tp1.y != _mp1.y) {
				for (int i = _tp1.y;i < _mp1.y; i++) {
					if ((i) >= 0 && (i) < (int)height) {
						_w1 = round(_lx < _rx ? _lx : _rx);
						_w2 = round(_lx > _rx ? _lx : _rx);
						_w3 = (_w2 - _w1) + 1;
						_cly = (_i / _h);
						_cly2 = (_i2 / _h2);
						_j = 0;
						unsigned char _c1r = (((unsigned char*)&_tp1.color)[0]) + (((((unsigned char*)&_bp1.color)[0]) - (((unsigned char*)&_tp1.color)[0])) * (_cly));
						unsigned char _c2r = ((unsigned char*)&_tp1.color)[0] + ((((unsigned char*)&_mp1.color)[0] - ((unsigned char*)&_tp1.color)[0]) * (_cly2));
						unsigned char _c1g = (((unsigned char*)&_tp1.color)[1]) + (((((unsigned char*)&_bp1.color)[1]) - (((unsigned char*)&_tp1.color)[1])) * (_cly));
						unsigned char _c2g = ((unsigned char*)&_tp1.color)[1] + ((((unsigned char*)&_mp1.color)[1] - ((unsigned char*)&_tp1.color)[1]) * (_cly2));
						unsigned char _c1b = (((unsigned char*)&_tp1.color)[2]) + (((((unsigned char*)&_bp1.color)[2]) - (((unsigned char*)&_tp1.color)[2])) * (_cly));
						unsigned char _c2b = ((unsigned char*)&_tp1.color)[2] + ((((unsigned char*)&_mp1.color)[2] - ((unsigned char*)&_tp1.color)[2]) * (_cly2));
						for (int j = _w1;j <= _w2;j++) {
							if ((j) >= 0 && (j) < (int)width) {
								_clx = (_j / _w3);
								((unsigned char*)&_color)[0] = (_c2r + ((_c1r - _c2r) * (_clx)));
								((unsigned char*)&_color)[1] = (_c2g + ((_c1g - _c2g) * (_clx)));
								((unsigned char*)&_color)[2] = (_c2b + ((_c1b - _c2b) * (_clx)));
								buffer[((i)*width) + (j)] = _color;
							}
							_j++;
						}
					}

					_lx -= _lslope;
					_rx += _rslope;
					_i++;
					_i2++;
				}

				_lslope = (_mp1.x > _bp1.x ? mslope : mslope);
				_rslope = (_mp1.x < _bp1.x ? slope2 : slope2);
			}
			else {
				_lx = (_tp1.x < _mp1.x ? _tp1.x : _mp1.x);
				_rx = (_tp1.x > _mp1.x ? _tp1.x : _mp1.x);

				_lslope = (_tp1.x > _mp1.x ? slope2 : mslope);
				_rslope = (_tp1.x < _mp1.x ? slope2 : mslope);
			}
		}
		
		_i2 = 0;
		_h2 = (_bp1.y - _mp1.y);
		if (_bp1.y == _mp1.y) {
			return;
		}
		if (_lslope <= _rslope && (_tp1.y != _mp1.y)) {
			for (int i = _mp1.y;i <= _bp1.y; i++) {
				if ((i) >= 0 && (i) < (int)height) {
					_w1 = round(_lx < _rx ? _lx : _rx);
					_w2 = round(_lx > _rx ? _lx : _rx);
					_w3 = (_w2 - _w1) + 1;
					_cly = (_i / _h);
					_cly2 = (_i2 / _h2);
					_j = 0;
					unsigned char _c1r = (((unsigned char*)&_tp1.color)[0]) + (((((unsigned char*)&_bp1.color)[0]) - (((unsigned char*)&_tp1.color)[0])) * (_cly));
					unsigned char _c2r = ((unsigned char*)&_mp1.color)[0] + ((((unsigned char*)&_bp1.color)[0] - ((unsigned char*)&_mp1.color)[0]) * (_cly2));
					unsigned char _c1g = (((unsigned char*)&_tp1.color)[1]) + (((((unsigned char*)&_bp1.color)[1]) - (((unsigned char*)&_tp1.color)[1])) * (_cly));
					unsigned char _c2g = ((unsigned char*)&_mp1.color)[1] + ((((unsigned char*)&_bp1.color)[1] - ((unsigned char*)&_mp1.color)[1]) * (_cly2));
					unsigned char _c1b = (((unsigned char*)&_tp1.color)[2]) + (((((unsigned char*)&_bp1.color)[2]) - (((unsigned char*)&_tp1.color)[2])) * (_cly));
					unsigned char _c2b = ((unsigned char*)&_mp1.color)[2] + ((((unsigned char*)&_bp1.color)[2] - ((unsigned char*)&_mp1.color)[2]) * (_cly2));
					for (int j = _w1;j <= _w2;j++) {
						if ((j) >= 0 && (j) < (int)width) {
							_clx = (_j / _w3);
							((unsigned char*)&_color)[0] = (_c1r + ((_c2r - _c1r) * (_clx)));
							((unsigned char*)&_color)[1] = (_c1g + ((_c2g - _c1g) * (_clx)));
							((unsigned char*)&_color)[2] = (_c1b + ((_c2b - _c1b) * (_clx)));
							buffer[((i)*width) + (j)] = _color;
						}
						_j++;
					}
				}

				_lx -= _lslope;
				_rx -= _rslope;
				_i++;
				_i2++;
			}
		}
		else {
			for (int i = _mp1.y;i <= _bp1.y; i++) {
				if ((i) >= 0 && (i) < (int)height) {
					_w1 = round(_lx < _rx ? _lx : _rx);
					_w2 = round(_lx > _rx ? _lx : _rx);
					_w3 = (_w2 - _w1) + 1;
					_cly = (_i / _h);
					_cly2 = (_i2 / _h2);
					_j = 0;
					unsigned char _c1r = (((unsigned char*)&_tp1.color)[0]) + (((((unsigned char*)&_bp1.color)[0]) - (((unsigned char*)&_tp1.color)[0])) * (_cly));
					unsigned char _c2r = ((unsigned char*)&_mp1.color)[0] + ((((unsigned char*)&_bp1.color)[0] - ((unsigned char*)&_mp1.color)[0]) * (_cly2));
					unsigned char _c1g = (((unsigned char*)&_tp1.color)[1]) + (((((unsigned char*)&_bp1.color)[1]) - (((unsigned char*)&_tp1.color)[1])) * (_cly));
					unsigned char _c2g = ((unsigned char*)&_mp1.color)[1] + ((((unsigned char*)&_bp1.color)[1] - ((unsigned char*)&_mp1.color)[1]) * (_cly2));
					unsigned char _c1b = (((unsigned char*)&_tp1.color)[2]) + (((((unsigned char*)&_bp1.color)[2]) - (((unsigned char*)&_tp1.color)[2])) * (_cly));
					unsigned char _c2b = ((unsigned char*)&_mp1.color)[2] + ((((unsigned char*)&_bp1.color)[2] - ((unsigned char*)&_mp1.color)[2]) * (_cly2));
					for (int j = _w1;j <= _w2;j++) {
						if ((j) >= 0 && (j) < (int)width) {
							_clx = (_j / _w3);
							((unsigned char*)&_color)[0] = (_c2r + ((_c1r - _c2r) * (_clx)));
							((unsigned char*)&_color)[1] = (_c2g + ((_c1g - _c2g) * (_clx)));
							((unsigned char*)&_color)[2] = (_c2b + ((_c1b - _c2b) * (_clx)));
							buffer[((i)*width) + (j)] = _color;
						}
						_j++;
					}
				}

				_lx -= _lslope;
				_rx -= _rslope;
				_i++;
				_i2++;
			}
		}
	}

	void SoftwareRenderEngine::triangle(const Texture& Ttexture, int Tx1, int Ty1, int Tx2, int Ty2, int Tx3, int Ty3, int Ttx1, int Tty1, int Ttx2, int Tty2, int Ttx3, int Tty3) {
		if (!buffer) {
			return;
		}
		struct PointTex {
			int x;
			int y;
			int tx;
			int ty;
		};

		PointTex _p1 = { Tx1,Ty1,Ttx1,Tty1 };
		PointTex _p2 = { Tx2,Ty2,Ttx1,Tty1 };
		PointTex _p3 = { Tx3,Ty3,Ttx1,Tty1 };

		PointTex _Pcalc = (_p1.y < _p2.y) ? _p1 : _p2;
		PointTex _tp1 = ((_Pcalc.y < _p3.y) ? _Pcalc : _p3);
		_Pcalc = (_p1.y > _p2.y) ? _p1 : _p2;
		PointTex _bp1 = ((_Pcalc.y > _p3.y) ? _Pcalc : _p3);
		_Pcalc = (_p1.x < _p2.x) ? _p1 : _p2;
		PointTex _lp1 = ((_Pcalc.x < _p3.x) ? _Pcalc : _p3);
		_Pcalc = (_p1.x > _p2.x) ? _p1 : _p2;
		PointTex _rp1 = ((_Pcalc.x > _p3.x) ? _Pcalc : _p3);

		PointTex _mp1 = _tp1;

		if ((_tp1.x != _p1.x ||
			_tp1.y != _p1.y) &&
			(_bp1.x != _p1.x ||
				_bp1.y != _p1.y)) {
			_mp1 = _p1;
		}
		if ((_tp1.x != _p2.x ||
			_tp1.y != _p2.y) &&
			(_bp1.x != _p2.x ||
				_bp1.y != _p2.y)) {
			_mp1 = _p2;
		}
		if ((_tp1.x != _p3.x ||
			_tp1.y != _p3.y) &&
			(_bp1.x != _p3.x ||
				_bp1.y != _p3.y)) {
			_mp1 = _p3;
		}

		PointTex _tp1_f = _p1;
		PointTex _mp1_f = _p3;
		PointTex _bp1_f = _p2;

		Point<int> _t_p1 = { Ttx1,Tty1 };
		Point<int> _t_p2 = { Ttx2,Tty2 };
		Point<int> _t_p3 = { Ttx3,Tty3 };
		//*
		Point<int> _tPcalc = (_t_p1.y < _t_p2.y) ? _t_p1 : _t_p2;
		Point<int> _t_tp1 = ((_tPcalc.y < _t_p3.y) ? _tPcalc : _t_p3);
		_tPcalc = (_t_p1.y > _t_p2.y) ? _t_p1 : _t_p2;
		Point<int> _t_bp1 = ((_tPcalc.y > _t_p3.y) ? _tPcalc : _t_p3);
		_tPcalc = (_t_p1.x < _t_p2.x) ? _t_p1 : _t_p2;
		Point<int> _t_lp1 = ((_tPcalc.x < _t_p3.x) ? _tPcalc : _t_p3);
		_tPcalc = (_t_p1.x > _t_p2.x) ? _t_p1 : _t_p2;
		Point<int> _t_rp1 = ((_tPcalc.x > _t_p3.x) ? _tPcalc : _t_p3);

		Point<int> _t_mp1 = _t_tp1;

		if ((_t_tp1.x != _t_p1.x ||
			_t_tp1.y != _t_p1.y) &&
			(_t_bp1.x != _t_p1.x ||
				_t_bp1.y != _t_p1.y)) {
			_t_mp1 = _t_p1;
		}
		if ((_t_tp1.x != _t_p2.x ||
			_t_tp1.y != _t_p2.y) &&
			(_t_bp1.x != _t_p2.x ||
				_t_bp1.y != _t_p2.y)) {
			_t_mp1 = _t_p2;
		}
		if ((_t_tp1.x != _t_p3.x ||
			_t_tp1.y != _t_p3.y) &&
			(_t_bp1.x != _t_p3.x ||
				_t_bp1.y != _t_p3.y)) {
			_t_mp1 = _t_p3;
		}

		if ((_t_tp1.x == _t_mp1.x) && (_t_tp1.y == _t_mp1.y)) {
			return;
		}
		//*/
		if ((_t_p1.x == _t_p2.x) && (_t_p1.y == _t_p2.y)) {
			return;
		}
		if ((_tp1.x == _mp1.x) && (_tp1.y == _mp1.y)) {
			line(_tp1.x, _tp1.y, _bp1.x, _bp1.y, 0);
			//line(_tp1.x, _tp1.y, _bp1.x, _bp1.y, Tcolor);
			return;
		}
		//int _rx1 = ((((_p1.x > _p2.x) ? _p1.x : _p2.x) > _p3.x) ? ((_p1.x > _p2.x) ? _p1.x : _p2.x) : _p3.x);

		float mslope = ((_tp1.x - _bp1.x) + 0) / abs(float(_tp1.y - _bp1.y) + 0);
		float slope1 = ((_mp1.x - _tp1.x) + 0) / abs(float(_mp1.y - _tp1.y) + 0);
		float slope2 = ((_mp1.x - _bp1.x) + 0) / abs(float(_bp1.y - _mp1.y) + 0);

		float mslope_y = ((_tp1.y - _bp1.y) + 0) / abs(float(_tp1.x - _bp1.x) + 0);
		float slope1_y = ((_mp1.y - _tp1.y) + 0) / abs(float(_mp1.x - _tp1.x) + 0);
		float slope2_y = ((_mp1.y - _bp1.y) + 0) / abs(float(_bp1.x - _mp1.x) + 0);

		float mslope_f = ((_tp1_f.x - _bp1_f.x) + 0) / abs(float(_tp1_f.y - _bp1_f.y) + 0);
		float slope1_f = ((_mp1_f.x - _tp1_f.x) + 0) / abs(float(_mp1_f.y - _tp1_f.y) + 0);
		float slope2_f = ((_mp1_f.x - _bp1_f.x) + 0) / abs(float(_bp1_f.y - _mp1_f.y) + 0);

		float mslope_y_f = ((_tp1_f.y - _bp1_f.y) + 0) / abs(float(_tp1_f.x - _bp1_f.x) + 0);
		float slope1_y_f = ((_mp1_f.y - _tp1_f.y) + 0) / abs(float(_mp1_f.x - _tp1_f.x) + 0);
		float slope2_y_f = ((_mp1_f.y - _bp1_f.y) + 0) / abs(float(_bp1_f.x - _mp1_f.x) + 0);

		float _mslope = (_tp1.y - _bp1.y) / abs(float(_tp1.x - _bp1.x));
		float _slope1 = (_mp1.y - _tp1.y) / abs(float(_mp1.x - _tp1.x));
		float _slope2 = (_mp1.y - _bp1.y) / abs(float(_bp1.x - _mp1.x));

		float _slopex = (_mp1.y - _tp1.y) / abs(float(_mp1.x - _tp1.x));
		float _slopey = (_mp1.x - _tp1.x) / abs(float(_mp1.y - _tp1.y));

		//float t_mslope = (_t_tp1.x - _t_bp1.x) / abs(float(_t_tp1.y - _t_bp1.y));
		//float t_slope1 = (_t_mp1.x - _t_tp1.x) / abs(float(_t_mp1.y - _t_tp1.y));
		//float t_slope2 = (_t_mp1.x - _t_bp1.x) / abs(float(_t_bp1.y - _t_mp1.y));
		float t_lx1 = 0;
		float t_ly1 = 0;
		if (_t_p1.y == _t_p2.y) {
			t_lx1 = (_t_p2.x - _t_p1.x);
			t_ly1 = 1;
		}
		else {
			if (t_lx1 != 1) {
				t_lx1 = (_t_p2.x - _t_p1.x) / (float(_t_p2.y - _t_p1.y));
			}
		}
		if (_t_p1.x == _t_p2.x) {
			t_lx1 = 1;
			t_ly1 = (_t_p2.y - _t_p1.y);
		}
		else {
			if (t_ly1 != 1) {
				t_ly1 = (_t_p2.y - _t_p1.y) / (float(_t_p2.x - _t_p1.x));
			}
		}

		float t_lx2 = 0;
		float t_ly2 = 0;
		if (_t_p1.y == _t_p3.y) {
			t_lx2 = (_t_p3.x - _t_p1.x);
			t_ly2 = 1;
		}
		else {
			if (t_lx2 != 1) {
				t_lx2 = (_t_p3.x - _t_p1.x) / (float(_t_p3.y - _t_p1.y));
			}
		}
		if (_t_p1.x == _t_p3.x) {
			t_lx2 = 1;
			t_ly2 = (_t_p3.y - _t_p1.y);
		}
		else {
			if (t_ly2 != 1) {
				t_ly2 = (_t_p3.y - _t_p1.y) / (float(_t_p3.x - _t_p1.x));
			}
		}

		float t_slopex1 = (1 / t_lx1);
		float t_slopey1 = (1 / t_ly1);

		float _lx = _tp1.x;
		float _rx = _tp1.x;

		float _lslope = (_tp1.x < _mp1.x ? mslope : mslope);
		float _rslope = (_tp1.x > _mp1.x ? slope1 : slope1);

		float _lslope_t = (_tp1.x < _mp1.x ? slope1 : slope1);
		float _rslope_t = (_tp1.x > _mp1.x ? mslope : mslope);

		float __lslope = (_tp1.x < _mp1.x ? _mslope : _mslope);
		float __rslope = (_tp1.x > _mp1.x ? _slope1 : _slope1);

		float _t_sx;
		float _t_sy;

		///

		float _t_wl = abs(_t_bp1.x - _t_tp1.x);
		float _t_hl = abs(_t_bp1.y - _t_tp1.y);

		unsigned int _color;
		float _clx;
		float _cly;
		float _w1;
		float _w2;
		float _w3;
		float _h = _bp1.y - _tp1.y;
		float _h2 = _mp1.y - _tp1.y;

		float _t_w1;
		float _t_w2;
		float _t_w3;

		float _cly2;

		int _i = 0;
		int _i2 = 0;
		int _j = 0;

		//float _w1 = (_mp1.tx - _tp1.tx);
		//float _h1 = (_mp1.ty - _tp1.ty);

		//float _ms = ()

		float _t__y = 0;

		float __x = 0;
		float __y = 0;

		float ___x = 0;
		float ___y = 0;

		float _t_lx = 0;

		//float _lslope_t;
		//float _rslope_t;

		if (-_lslope <= _rslope) {
			if (_tp1.y != _mp1.y) {
				
					//if (_bp1.x < _mp1.x) {
				std::cout << slope1_y << " " << ((_tp1.x + (_rslope * 50)) - _tp1.x) << " " << (0.5 * ((_tp1.x + (_rslope * 50)) - _tp1.x)) << " = " << (0.5 * ((_tp1.x + (_rslope * 50)) - _tp1.x))*slope1_y << "\n";
				for (int i = _tp1.y;i < _mp1.y; i++) {
					if ((i) >= 0 && (i) < (int)height) {
						_w1 = round(_lx < _rx ? _lx : _rx);
						_w2 = round(_lx > _rx ? _lx : _rx);
						_w3 = (_w2 - _w1) + 1;
						_cly = (_i / _h);
						_cly2 = (_i2 / _h2);
						_j = 0;
						for (int j = _w1;j <= _w2;j++) {
							if ((j) >= 0 && (j) < (int)width) {
								_clx = ((_j) / (_w3));
								_color = ((unsigned int*)Ttexture.buffer)[((int)((_cly*_t_hl) - (((((_j)*(1 / (mslope + slope1)))) / (abs(_tp1.y - _bp1.y)))*_t_hl))          *(int)Ttexture.width) +
									int(((((_j) * (1)) / (float)(								 //+((((_mp1.y - _tp1.y)*_lslope)) - _tp1.x)

									(((_mp1.y - _tp1.y)*_rslope)) +
										(((_mp1.y - _tp1.y)*_lslope))

										- 0))*_t_wl))];//*slope1
								//abs(_bp1.x - _mp1.x)
								//((unsigned char*)&_color)[0] = (_c1r + ((_c2r - _c1r) * (_clx)));
								//((unsigned char*)&_color)[1] = (_c1g + ((_c2g - _c1g) * (_clx)));
								//((unsigned char*)&_color)[2] = (_c1b + ((_c2b - _c1b) * (_clx)));
								//((unsigned char*)&_color)[0] = (_c1r + ((_c2r - _c1r) * (_clx)));
								//((unsigned char*)&_color)[1] = (_c1g + ((_c2g - _c1g) * (_clx)));
								//((unsigned char*)&_color)[2] = (_c1b + ((_c2b - _c1b) * (_clx)));
								buffer[((i)*width) + (j)] = _color;

								//if (abs(_w2 - _tp1.x) == ) {
									//buffer[((i)*width) + (j)] = colorinta(int(_clx*255), int((abs(_w2 - _tp1.x)/255) * 255), 0, 255);
								//}
							}
							_j++;
						}

					}

					_lx -= _lslope;
					_rx += _rslope;
					if ((int)_i == (_mp1.y - _tp1.y - 1)) {
						int lol = 0;
					}
					_t_lx -= mslope;
					_i++;
					_i2++;
				}

				_lslope = (_mp1.x > _bp1.x ? mslope : mslope);
				_rslope = (_mp1.x < _bp1.x ? slope2 : slope2);

				_lslope_t = _lslope;
				_rslope_t = _rslope;
				//}
			}
			else {
				_lx = (_tp1.x < _mp1.x ? _tp1.x : _mp1.x);
				_rx = (_tp1.x > _mp1.x ? _tp1.x : _mp1.x);

				_lslope = (_tp1.x > _mp1.x ? slope2 : mslope);
				_rslope = (_tp1.x < _mp1.x ? slope2 : mslope);

				_lslope_t = _lslope;
				_rslope_t = _rslope;
			}
			/*
			if (_clx == 0.5 && 0) {
				//buffer[((i)*width) + (j)] = colorinta(_clx * 255, 0, 255, 255);
				std::cout << "\n\n _clx = 0.5 : " <<
					"	_w2		: " << _w2 << "\n" <<
					"	_tp1.x		: " << _tp1.x << "\n" <<
					"	abs(_w2-_tp1.x)			: " << abs(_w2 - _tp1.x) << "\n" <<
					"	(_clx*(abs(_w2-_tp1.x)))	: " << (_clx*(abs(_w2 - _tp1.x))) << "\n";// <<
					//"abs(_w2-_tp1.x)			: " << abs(_w2 - _tp1.x) << "\n" <<
					//"abs(_w2-_tp1.x)			: " << abs(_w2 - _tp1.x) << "\n" <<
					//"abs(_w2-_tp1.x)			: " << abs(_w2 - _tp1.x) << "\n" <<
			}
			*/
		}



		else {
			if (_tp1.y != _mp1.y) {
				if ((_bp1.x < _tp1.x || 1)) {
					for (int i = _tp1.y;i < _mp1.y; i++) {
						if ((i) >= 0 && (i) < (int)height) {
							_w1 = round(_lx < _rx ? _lx : _rx);
							_w2 = round(_lx > _rx ? _lx : _rx);
							_w3 = (_w2 - _w1) + 1;
							_cly = (_i / _h);
							_cly2 = (_i2 / _h2);
							_j = 0;
							if (_i == 50) {
								int lol = 0;
							}
							for (int j = _w1;j <= _w2;j++) {
								if ((j) >= 0 && (j) < (int)width) {
									_clx = ((_j) / (_w3));													//+abs(_w2-_tp1.x)
									_color = ((unsigned int*)Ttexture.buffer)[((int)((_cly*_t_hl) - (((((_w3 - _j)*(1 / (-mslope - slope1)))) / abs(_tp1.y - _bp1.y))*_t_hl) - (0))          *(int)Ttexture.width) +
										int(((((_w3 - _j) * (1)) / (float)(								 //+((((_mp1.y - _tp1.y)*_lslope)) - _tp1.x)
																										 //((_w3 - _j)*(1 / (mslope + slope1)))
										(((_mp1.y - _tp1.y)*-_rslope)) +
											(((_mp1.y - _tp1.y)*-_lslope))

											- 0))*_t_wl))];//*slope1
														   //abs(_bp1.x - _mp1.x)
														   //((unsigned char*)&_color)[0] = (_c1r + ((_c2r - _c1r) * (_clx)));
														   //((unsigned char*)&_color)[1] = (_c1g + ((_c2g - _c1g) * (_clx)));
														   //((unsigned char*)&_color)[2] = (_c1b + ((_c2b - _c1b) * (_clx)));
									// lol32
									buffer[((i)*width) + (j)] = _color;
								}
								_j++;
							}
						}

						_lx -= _lslope;
						_rx += _rslope;
						if ((int)_i == (_mp1.y - _tp1.y - 1)) {
							int lol = 0;
						}
						_t_lx -= mslope;
						_i++;
						_i2++;
					}
				}
				else {
					// EDIT THIS M8- NAH FINISHED IT IS DOWNED-TOP-RIGHT
					for (int i = _tp1.y;i < _mp1.y; i++) {
						if ((i) >= 0 && (i) < (int)height) {
							_w1 = round(_lx < _rx ? _lx : _rx);
							_w2 = round(_lx > _rx ? _lx : _rx);
							_w3 = (_w2 - _w1) + 1;
							_cly = (_i / _h);
							_cly2 = (_i2 / _h2);
							float _cly3 = (_i / _h2);
							_j = 0;
							if (_i == 50) {
								int lol = 0;
							}
							for (int j = _w1;j <= _w2;j++) {
								if ((j) >= 0 && (j) < (int)width) {
									_clx = ((_j) / (_w3));													//+abs(_w2-_tp1.x)
									_color = ((unsigned int*)Ttexture.buffer)[((int)((_cly3*_t_hl) - (((((((_j)*(1/(-mslope + slope1)))*(1)))) / abs(_tp1.y - _mp1.y))*_t_hl) - (0))          *(int)Ttexture.width) +
										int(((((_j) * (1)) / (float)(								 //+((((_mp1.y - _tp1.y)*_lslope)) - _tp1.x)

										(((_bp1.y - _tp1.y)*_rslope)) +
											(((_bp1.y - _tp1.y)*-_lslope))

											- 0))*_t_wl))];//*slope1
														   //abs(_bp1.x - _mp1.x)
														   //((unsigned char*)&_color)[0] = (_c1r + ((_c2r - _c1r) * (_clx)));
														   //((unsigned char*)&_color)[1] = (_c1g + ((_c2g - _c1g) * (_clx)));
														   //((unsigned char*)&_color)[2] = (_c1b + ((_c2b - _c1b) * (_clx)));
									// lol32
									buffer[((i)*width) + (j)] = _color;
								}
								_j++;
							}
						}

						_lx -= _lslope;
						_rx += _rslope;
						if ((int)_i == (_mp1.y - _tp1.y - 1)) {
							int lol = 0;
						}
						_t_lx -= mslope;
						_i++;
						_i2++;
					}
				}

				_lslope = (_mp1.x > _bp1.x ? mslope : mslope);
				_rslope = (_mp1.x < _bp1.x ? slope2 : slope2);
			}
			else {
				_lx = (_tp1.x < _mp1.x ? _tp1.x : _mp1.x);
				_rx = (_tp1.x > _mp1.x ? _tp1.x : _mp1.x);

				_lslope = (_tp1.x > _mp1.x ? slope2 : mslope);
				_rslope = (_tp1.x < _mp1.x ? slope2 : mslope);
			}
		}

		line(_tp1.x, _tp1.y, _tp1.x + 255, _tp1.y, colorinta(0, 0, 0, 255));

		//*/
		_i2 = 0;
		_h2 = (_bp1.y - _mp1.y);
		if (_bp1.y == _mp1.y) {
			return;
		}
		// ENTER BOTTOM TRIANGLE

		if (_lslope <= _rslope && (_tp1.y != _mp1.y)) {
			for (int i = _mp1.y;i <= _bp1.y; i++) {
				if ((i) >= 0 && (i) < (int)height) {
					_w1 = round(_lx < _rx ? _lx : _rx);
					_w2 = round(_lx > _rx ? _lx : _rx);
					_w3 = (_w2 - _w1) + 1;
					_cly = (_i / _h);
					_cly2 = (_i2 / _h2);
					_j = 0;

					_t_sy = _t_p1.y + ((t_ly1)* _cly);

					for (int j = _w1;j <= _w2;j++) {
						if ((j) >= 0 && (j) < (int)width) {
							_clx = ((_j) / (_w3));
							_color = ((unsigned int*)Ttexture.buffer)[((int)((_cly*_t_hl) - (((((_j)*(1 / (mslope + slope1)))) / (abs(_tp1.y - _bp1.y)))*_t_hl))          *(int)Ttexture.width) +
								int(((((_j) * (1)) / (float)(								 //+((((_mp1.y - _tp1.y)*_lslope)) - _tp1.x)

								(((_bp1.y - _mp1.y)*_rslope)) +
									(((_bp1.y - _mp1.y)*-_lslope))

									- 0))*_t_wl))];//*slope1
												   //abs(_bp1.x - _mp1.x)
												   //((unsigned char*)&_color)[0] = (_c1r + ((_c2r - _c1r) * (_clx)));
												   //((unsigned char*)&_color)[1] = (_c1g + ((_c2g - _c1g) * (_clx)));
												   //((unsigned char*)&_color)[2] = (_c1b + ((_c2b - _c1b) * (_clx)));
							buffer[((i)*width) + (j)] = _color;
						}
						_j++;
					}
				}

				_lx -= _lslope;
				_rx -= _rslope;
				_i++;
				_i2++;
			}
		}

		else {
			for (int i = _mp1.y;i <= _bp1.y; i++) {
				if ((i) >= 0 && (i) < (int)height) {
					_w1 = round(_lx < _rx ? _lx : _rx);
					_w2 = round(_lx > _rx ? _lx : _rx);
					_w3 = (_w2 - _w1) + 1;
					_cly = (_i / _h);
					_cly2 = (_i2 / _h2);
					_j = 0;
					for (int j = _w1;j <= _w2;j++) {
						if ((j) >= 0 && (j) < (int)width) {
							_clx = ((_j) / (_w3));//continue;													//+abs(_w2-_tp1.x)
							_color = ((unsigned int*)Ttexture.buffer)[((int)((_cly*_t_hl) - (((((_w3 - _j)*(1 / (-mslope + -slope1)))) / abs(_tp1.y - _bp1.y))*_t_hl) - (0))          *(int)Ttexture.width) +
								int(((((_w3 - _j) * (1)) / (float)(								 //+((((_mp1.y - _tp1.y)*_lslope)) - _tp1.x)

								(((_bp1.y - _mp1.y)*-_rslope)) +
									(((_bp1.y - _mp1.y)*_lslope))

									- 0))*_t_wl))];//*slope1
												   //abs(_bp1.x - _mp1.x)
												   //((unsigned char*)&_color)[0] = (_c1r + ((_c2r - _c1r) * (_clx)));
												   //((unsigned char*)&_color)[1] = (_c1g + ((_c2g - _c1g) * (_clx)));
												   //((unsigned char*)&_color)[2] = (_c1b + ((_c2b - _c1b) * (_clx)));
							// lol32
							buffer[((i)*width) + (j)] = _color;
						}
						_j++;
					}
				}

				_lx -= _lslope;
				_rx -= _rslope;
				_i++;
				_i2++;
			}
		}
		
	}

	void SoftwareRenderEngine::blit(const Texture& Ttexture, int Tx, int Ty) {
		if (!buffer) {
			return;
		}
		int _ox = (Tx < 0 ? Tx : 0);
		int _oy = (Ty < 0 ? Ty : 0);

		int _dx = Ttexture.width;
		int _dy = Ttexture.height;
		//buffer[0] = wincolor(0, 255, 255, 255);
		int _inc = (width) * 4;

		int __lx = (unsigned)_dx * 4;
		int __rx = (width - Tx) * 4;
		int _sw = (__lx < __rx ? __lx : __rx);

		//int _ssw;// = std::min((unsigned)_dx * 4, (width - Tx) * 4);
		int _w = _dy * _inc;

		if (Tx < -(_dx)) {
			return;
		}
		if (Tx >(int)width) {
			return;
		}

		int _yo = 0;
		if (Ty + (Ttexture.height) > height) {
			_yo = ((Ty + (Ttexture.height)) - height) * _inc;
		}

		int _lx = (0 > -Tx ? 0 : -Tx) * 4;

		int _ssw = _sw;// *2;

		_sw -= _lx;
		//_ssw -= _lx;

		unsigned int _bufferstart = ((unsigned int)buffer) + ((Ty * width * 4) + (Tx * 4));
		unsigned int _Rbufferstart = ((unsigned int)Ttexture.buffer);

		unsigned int _offset = 0;

		if ((_bufferstart + (Tx * 4)) < (unsigned int)buffer) {
			_offset = (unsigned int)buffer - (_bufferstart + (Tx * 4));
		}

		//_bufferstart += _offset;
		//_Rbufferstart += _offset;

		int _ody = ((int)(_dy));
		_ody = (_ody > 0 ? _ody * ((width) * 4) : 0);

		int _ouy = (_oy * _inc);
		int _ouyt = (_oy * _dx * 4);

		int _ix = /*(_sw)+*/_lx - _ouyt;
		int _inct = (_dx * 4);

		_bufferstart += (-_ouy) + _lx;
		_Rbufferstart += _ix;
		//_bufferstart += ;
		//_Rbufferstart += _ouy;

		unsigned int _ic = _bufferstart + _ody + _ouy - _yo;
		//for (unsigned int i = 0;i < _w;i += _inc) {
		for (unsigned int i = _bufferstart;i < _ic;i += _inc) {
			//memset(buffer + ((i + Ty1)*width) + Tx1, Tcolor, _dx);
			//unsigned int _xf = ((height - (i))*width);
			//memset((void*)(_bufferstart - i), wincolor(255,0,0,255), _inc);
			memcpy((void*)(i), (void*)(_Rbufferstart), _sw);
			//*((unsigned int*)(_bufferstart + (_sw)+_lx)) = wincolor(0, 0, 255, 255);

			//_bufferstart -= _sw;
			_Rbufferstart += _inct;
			//for (unsigned int j = _xf;j < _xf + (_dx);j++) {
			//	buffer[j] = Tcolor;
			//}

			//_stepx++;
		}

		//draw_line(0, 0, _w / 4, 0, wincolor(0, 0, 255, 255));
		//draw_line(1, 0, std::max(_bufferstart - _w, (unsigned int)buffer), 1, wincolor(0, 255, 255, 255));
		//((buffer[10000])) = wincolor(0, 255, 255, 255);
		//*((unsigned int*)(_bufferstart)) = wincolor(0, 255, 255, 255);
	}

	void SoftwareRenderEngine::blittransparent(const Texture& Ttexture, int Tx, int Ty) {
		if (!buffer) {
			return;
		}
		int _ox = (Tx < 0 ? Tx : 0);
		int _oy = (Ty < 0 ? Ty : 0);

		int _dx = Ttexture.width;
		int _dy = Ttexture.height;
		//buffer[0] = wincolor(0, 255, 255, 255);
		int _inc = (width) * 4;

		int __lx = (unsigned)_dx * 4;
		int __rx = (width - Tx) * 4;
		int _sw = (__lx < __rx ? __lx : __rx);

		//int _ssw;// = std::min((unsigned)_dx * 4, (width - Tx) * 4);
		int _w = _dy * _inc;

		if (Tx < -(_dx)) {
			return;
		}
		if (Tx >(int)width) {
			return;
		}

		int _yo = 0;
		if (Ty + (Ttexture.height) > height) {
			_yo = ((Ty + (Ttexture.height)) - height) * _inc;
		}

		int _lx = (0 > -Tx ? 0 : -Tx) * 4;

		int _ssw = _sw;// *2;

		_sw -= _lx;
		//_ssw -= _lx;

		unsigned int _bufferstart = ((unsigned int)buffer) + ((Ty * width * 4) + (Tx * 4));
		unsigned int _Rbufferstart = ((unsigned int)Ttexture.buffer);

		unsigned int _offset = 0;

		if ((_bufferstart + (Tx * 4)) < (unsigned int)buffer) {
			_offset = (unsigned int)buffer - (_bufferstart + (Tx * 4));
		}

		//_bufferstart += _offset;
		//_Rbufferstart += _offset;

		int _ody = ((int)(_dy));
		_ody = (_ody > 0 ? _ody * ((width) * 4) : 0);

		int _ouy = (_oy * _inc);
		int _ouyt = (_oy * _dx * 4);

		int _ix = /*(_sw)+*/_lx - _ouyt;
		int _inct = (_dx * 4);

		_bufferstart += (-_ouy) + _lx;
		_Rbufferstart += _ix;
		//_bufferstart += ;
		//_Rbufferstart += _ouy;

		unsigned int _ic = _bufferstart + _ody + _ouy - _yo;
		//for (unsigned int i = 0;i < _w;i += _inc) {
		for (unsigned int i = _bufferstart;i < _ic;i += _inc) {
			//memset(buffer + ((i + Ty1)*width) + Tx1, Tcolor, _dx);
			//unsigned int _xf = ((height - (i))*width);
			//memset((void*)(_bufferstart - i), wincolor(255,0,0,255), _inc);
			int _jm = i + _sw;
			unsigned int _j = _Rbufferstart;
			//*((unsigned int*)i) = 0;
			for (int j = (i);j < _jm;j += 4) {
				if (*((unsigned char*)_j + 3)) {
					*((unsigned int*)j) = *((unsigned int*)_j);
					//((unsigned int*)j)[0] = ((j - i) / (float)(_jm - i))*255;
					//if (((j - i) / (float)(_jm - i)) == 0.5) {
					//	((unsigned int*)j)[0] = 255;
					//}
				}

				_j += 4;
			}

			//*((unsigned int*)(_bufferstart + (_sw)+_lx)) = wincolor(0, 0, 255, 255);

			//_bufferstart -= _sw;
			_Rbufferstart += _inct;
			//for (unsigned int j = _xf;j < _xf + (_dx);j++) {
			//	buffer[j] = Tcolor;
			//}

			//_stepx++;
		}

		//draw_line(0, 0, _w / 4, 0, wincolor(0, 0, 255, 255));
		//draw_line(1, 0, std::max(_bufferstart - _w, (unsigned int)buffer), 1, wincolor(0, 255, 255, 255));
		//((buffer[10000])) = wincolor(0, 255, 255, 255);
		//*((unsigned int*)(_bufferstart)) = wincolor(0, 255, 255, 255);
	}

	void SoftwareRenderEngine::blitrect(const Texture& Ttexture, int Tx, int Ty, int Txi, int Tyi, int Tw, int Th) {
		if (!buffer) {
			return;
		}
		int _ox = (Tx < 0 ? Tx : 0);
		int _oy = (Ty < 0 ? Ty : 0);

		int _dx = Ttexture.width;
		int _dy = Ttexture.height;
		//buffer[0] = wincolor(0, 255, 255, 255);
		int _inc = (width) * 4;

		int _sw_t = Tw;//(Tw - Txi);
		_sw_t = (_sw_t < 0 ? -_sw_t : _sw_t);
		int _sh_t = Th;//(Th - Tyi);
		_sh_t = (_sh_t < 0 ? -_sh_t : _sh_t);

		int _iw = (_sw_t < _dx ? _sw_t : _dx);
		int _ih = (_sh_t < _dy ? _sh_t : _dy);

		int _swt = _iw * 4;
		int _sht = _ih * 4;

		int __lx = (unsigned)_iw * 4;
		int __rx = (width - (Tx)) * 4;
		int _sw = (__lx < __rx ? __lx : __rx);

		
		//int _ssw;// = std::min((unsigned)_dx * 4, (width - Tx) * 4);
		int _w = _ih * _inc;

		if (Tx < -(_iw)) {
			return;
		}
		if (Ty < -(_ih)) {
			return;
		}
		if (Tx >(int)width) {
			return;
		}

		int _lx = _ox * 4;

		int _ssw = _sw;// *2;

		//_sw += _lx;
		//_iw += _lx;
		//_ssw -= _lx;

		unsigned int _bufferstart = ((unsigned int)buffer + ((Ty * width * 4) + (Tx * 4)));//((unsigned int)buffer + (width*height * 4)) - _inc - ((Ty * width * 4) - (Tx * 4));
		unsigned int _Rbufferstart = ((unsigned int)Ttexture.buffer + ((Tyi * _dx * 4) + (Txi * 4)));// -_sw - ((unsigned)_dx * 4) - ((Tyi * _dx * 4) - (Txi * 4));// - _sw - _lx;// - _sw;

																																				 //_bufferstart = ((unsigned int)buffer + (width*height * 4)) - _inc;
																																				 //_Rbufferstart = ((unsigned int)Tsurface.buffer + (_dx*_dy * 4)) - _sw;

																																				 //int __w = std::max(0, (int)height - (Ty + _dy)) * 4;
																																				 //_w -= __w;

																																				 //int _stepx = 0;

		int _ody = (height - (int)(Ty + _ih));
		_ody = (_ody < 0 ? _ody * ((width) * 4) : 0);

		int _ouy = (_oy * _inc);
		int _ouyt = (_oy * _dx * 4);

		int _ix = 0 - _ouyt;
		int _inct = (_dx * 4);
		//std::cout << _sw / 4 << "\n";
		//_bufferstart += _ouy + _lx;

		_bufferstart += (-_ouy) - _lx;// +_lx;
		_Rbufferstart += _ix -_lx;
		//_bufferstart += ;
		//_Rbufferstart += _ouyt;

		int _ic = _bufferstart + _w + _ody + _ouy;
		int _swl = _sw + _lx;

		//int _swt = (Txi - Tx);

		//for (unsigned int i = 0;i < _w;i += _inc) {
		for (unsigned int i = _bufferstart;i < _ic;i += _inc) {
			//memset(buffer + ((i + Ty1)*width) + Tx1, Tcolor, _dx);
			//unsigned int _xf = ((height - (i))*width);
			//memset((void*)(_bufferstart - i), wincolor(255,0,0,255), _inc);
			int _jm = i + _swl;
			unsigned int _j = _Rbufferstart;
			//*((unsigned int*)i) = 0;
			for (int j = (i);j < _jm;j += 4) {
				if (*((unsigned char*)_j + 3) != 0) {
					*((unsigned int*)j) = *((unsigned int*)_j);
					//((unsigned int*)j)[0] = ((j - i) / (float)(_jm - i))*255;
					//if (((j - i) / (float)(_jm - i)) == 0.5) {
					//	((unsigned int*)j)[0] = 255;
					//}
				}

				_j += 4;
			}

			//memcpy((void*)(i), (void*)(_Rbufferstart), _sw);

			//*((unsigned int*)(_bufferstart + (_sw)+_lx)) = wincolor(0, 0, 255, 255);

			//_bufferstart -= _sw;
			_Rbufferstart += _inct;
			//for (unsigned int j = _xf;j < _xf + (_dx);j++) {
			//	buffer[j] = Tcolor;
			//}

			//_stepx++;
		}

		//draw_line(0, 0, _w / 4, 0, wincolor(0, 0, 255, 255));
		//draw_line(1, 0, std::max(_bufferstart - _w, (unsigned int)buffer), 1, wincolor(0, 255, 255, 255));
		//((buffer[10000])) = wincolor(0, 255, 255, 255);
		//*((unsigned int*)(_bufferstart)) = wincolor(0, 255, 255, 255);
	}

	void SoftwareRenderEngine::blitrectcolor(const Texture& Ttexture, int Tx, int Ty, int Txi, int Tyi, int Tw, int Th, unsigned int Tcolor) {
		if (!buffer) {
			return;
		}
		int _ox = (Tx < 0 ? Tx : 0);
		int _oy = (Ty < 0 ? Ty : 0);

		int _dx = Ttexture.width;
		int _dy = Ttexture.height;
		//buffer[0] = wincolor(0, 255, 255, 255);
		int _inc = (width) * 4;

		int _sw_t = Tw;//(Tw - Txi);
		_sw_t = (_sw_t < 0 ? -_sw_t : _sw_t);
		int _sh_t = Th;//(Th - Tyi);
		_sh_t = (_sh_t < 0 ? -_sh_t : _sh_t);

		int _iw = (_sw_t < _dx ? _sw_t : _dx);
		int _ih = (_sh_t < _dy ? _sh_t : _dy);

		int _swt = _iw * 4;
		int _sht = _ih * 4;

		int __lx = (unsigned)_iw * 4;
		int __rx = (width - (Tx)) * 4;
		int _sw = (__lx < __rx ? __lx : __rx);


		//int _ssw;// = std::min((unsigned)_dx * 4, (width - Tx) * 4);
		int _w = _ih * _inc;

		if (Tx < -(_iw)) {
			return;
		}
		if (Ty < -(_ih)) {
			return;
		}
		if (Tx >(int)width) {
			return;
		}

		int _lx = _ox * 4;

		int _ssw = _sw;// *2;

					   //_sw += _lx;
					   //_iw += _lx;
					   //_ssw -= _lx;

		unsigned int _bufferstart = ((unsigned int)buffer + ((Ty * width * 4) + (Tx * 4)));//((unsigned int)buffer + (width*height * 4)) - _inc - ((Ty * width * 4) - (Tx * 4));
		unsigned int _Rbufferstart = ((unsigned int)Ttexture.buffer + ((Tyi * _dx * 4) + (Txi * 4)));// -_sw - ((unsigned)_dx * 4) - ((Tyi * _dx * 4) - (Txi * 4));// - _sw - _lx;// - _sw;

																									 //_bufferstart = ((unsigned int)buffer + (width*height * 4)) - _inc;
																									 //_Rbufferstart = ((unsigned int)Tsurface.buffer + (_dx*_dy * 4)) - _sw;

																									 //int __w = std::max(0, (int)height - (Ty + _dy)) * 4;
																									 //_w -= __w;

																									 //int _stepx = 0;

		int _ody = (height - (int)(Ty + _ih));
		_ody = (_ody < 0 ? _ody * ((width) * 4) : 0);

		int _ouy = (_oy * _inc);
		int _ouyt = (_oy * _dx * 4);

		int _ix = 0 - _ouyt;
		int _inct = (_dx * 4);
		//std::cout << _sw / 4 << "\n";
		//_bufferstart += _ouy + _lx;

		_bufferstart += (-_ouy) - _lx;// +_lx;
		_Rbufferstart += _ix - _lx;
		//_bufferstart += ;
		//_Rbufferstart += _ouyt;

		int _ic = _bufferstart + _w + _ody + _ouy;
		int _swl = _sw + _lx;

		//int _swt = (Txi - Tx);

		//for (unsigned int i = 0;i < _w;i += _inc) {
		for (unsigned int i = _bufferstart;i < _ic;i += _inc) {
			//memset(buffer + ((i + Ty1)*width) + Tx1, Tcolor, _dx);
			//unsigned int _xf = ((height - (i))*width);
			//memset((void*)(_bufferstart - i), wincolor(255,0,0,255), _inc);
			int _jm = i + _swl;
			unsigned int _j = _Rbufferstart;
			//*((unsigned int*)i) = 0;
			for (int j = (i);j < _jm;j += 4) {
				if (*((unsigned char*)_j + 3) != 0) {
					*((unsigned int*)j) = Tcolor;
					//((unsigned int*)j)[0] = ((j - i) / (float)(_jm - i))*255;
					//if (((j - i) / (float)(_jm - i)) == 0.5) {
					//	((unsigned int*)j)[0] = 255;
					//}
				}

				_j += 4;
			}

			//memcpy((void*)(i), (void*)(_Rbufferstart), _sw);

			//*((unsigned int*)(_bufferstart + (_sw)+_lx)) = wincolor(0, 0, 255, 255);

			//_bufferstart -= _sw;
			_Rbufferstart += _inct;
			//for (unsigned int j = _xf;j < _xf + (_dx);j++) {
			//	buffer[j] = Tcolor;
			//}

			//_stepx++;
		}

		//draw_line(0, 0, _w / 4, 0, wincolor(0, 0, 255, 255));
		//draw_line(1, 0, std::max(_bufferstart - _w, (unsigned int)buffer), 1, wincolor(0, 255, 255, 255));
		//((buffer[10000])) = wincolor(0, 255, 255, 255);
		//*((unsigned int*)(_bufferstart)) = wincolor(0, 255, 255, 255);
	}
}