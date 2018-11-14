#ifndef _KPerpCore_SoftwareRenderEngine_hpp_
#define _KPerpCore_SoftwareRenderEngine_hpp_

#include "Math.hpp"
#include "Shape.hpp"

namespace kp {
	class Texture;

	class SoftwareRenderEngine {
	public:
		SoftwareRenderEngine();
		
		bool settarget(int Tw, int Th, unsigned int* Tbuffer);

		void reset();
		void clear(unsigned int Tcolor);

		void point(int Tx, int Ty, unsigned int Tcolor);

		void rectangle(int Tx1, int Ty1, int Tx2, int Ty2, unsigned int Tcolor);
		void rectangle(Rectangle<int> Trect, unsigned int Tcolor);

		void rectangle(int Tx1, int Ty1, int Tx2, int Ty2, unsigned int Tcolor1, unsigned int Tcolor2, unsigned int Tcolor3, unsigned int Tcolor4);
		void rectangle(const Texture& Ttexture, int Tx1, int Ty1, int Tx2, int Ty2);
		void rectangle(const Texture& Ttexture, int Tx1, int Ty1, int Tx2, int Ty2, int Ttx1, int Tty1, int Ttx2, int Tty2);
		void rectangle(const Texture& Ttexture, int Tx1, int Ty1, int Tx2, int Ty2, unsigned int Tcolor);
		void rectangle(const Texture& Ttexture, int Tx1, int Ty1, int Tx2, int Ty2, int Ttx1, int Tty1, int Ttx2, int Tty2, unsigned int Tcolor);
		void rectangle(const Texture& Ttexture, int Tx1, int Ty1, int Tx2, int Ty2, unsigned int Tcolor1, unsigned int Tcolor2, unsigned int Tcolor3, unsigned int Tcolor4);
		void rectangle(const Texture& Ttexture, int Tx1, int Ty1, int Tx2, int Ty2, int Ttx1, int Tty1, int Ttx2, int Tty2, unsigned int Tcolor1, unsigned int Tcolor2, unsigned int Tcolor3, unsigned int Tcolor4);

		void line(int Tx1, int Ty1, int Tx2, int Ty2, unsigned int Tcolor);
		void line(int Tx1, int Ty1, int Tx2, int Ty2, unsigned int Tcolor1, unsigned int Tcolor2);

		void triangle(int Tx1, int Ty1, int Tx2, int Ty2, int Tx3, int Ty3, unsigned int Tcolor);
		void triangle(int Tx1, int Ty1, int Tx2, int Ty2, int Tx3, int Ty3, unsigned int Tcolor1, unsigned int Tcolor2, unsigned int Tcolor3);

		void triangle(const Texture& Ttexture, int Tx1, int Ty1, int Tx2, int Ty2, int Tx3, int Ty3, int Ttx1, int Tty1, int Ttx2, int Tty2, int Ttx3, int Tty3);

		void blit(const Texture& Ttexture, int Tx, int Ty);
		void blittransparent(const Texture& Ttexture, int Tx, int Ty);
		void blitrect(const Texture& Ttexture, int Tx, int Ty, int Txi, int Tyi, int Tw, int Th);

		void blitrectcolor(const Texture& Ttexture, int Tx, int Ty, int Txi, int Tyi, int Tw, int Th, unsigned int Tcolor);

	private:

		int width;
		int height;
		int size;
		unsigned int* buffer;
	};
}

#endif