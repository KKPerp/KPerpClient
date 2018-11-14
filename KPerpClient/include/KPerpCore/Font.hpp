#ifndef __KPerpCore_Font_hpp_
#define __KPerpCore_Font_hpp_

#include <KPerpCore/Resource.hpp>

namespace kp {
	class Texture;

	class Font {
	public:
		Font();
		Font(Texture &Ttex, int Tw, int Th, int Tfh);
		Font(Texture &Ttex, int Tw, int Th, int Tfh, unsigned char Tstart);
		Font(Texture &Ttex, int Tw, int Th, int Tfh, unsigned char Tstart, unsigned char Tend);
		Font(Texture &Ttex, int Tw, int Th, int Tfh, unsigned char Tstart, unsigned char Tend, bool Tm);
		Font(Texture &Ttex, int Tw, int Th, int Tfh, unsigned char Tstart, unsigned char Tend, bool Tm, int Tsep);
		Font(Texture &Ttex, int Tw, int Th, int Tfh, unsigned char Tstart, unsigned char Tend, bool Tm, int Tsep, int Tspace);
		//~Font();

		char getStartChar() const;
		char getEndChar() const;
		bool getMonospace() const;
		int getSepWidth() const;
		int* getWidth();
		int getWidth(int Tpos) const;
		int getHeight() const;
		int getFullWidth() const;
		int getFullHeight() const;
		Texture* getTex() const;
		int getSpaceWidth() const;

		void setStartChar(char Tvalue);
		void setEndChar(char Tvalue);
		void setMonospace(bool Tvalue);
		void setSepWidth(int Tvalue);
		void setWidth(int* Tpos);
		void setWidth(int Tpos, int Tvalue);
		void setHeight(int Tvalue);
		void setFullWidth(int Tvalue);
		void setFullHeight(int Tvalue);
		void setSpaceWidth(int Tvalue);

	private:
		int start = 0;
		int end = 255;

		bool monospace = 0;
		int sepration = 0;

		int width[255] = { 0 };
		int height = 0;
		int fullheight = 0;

		int fullwidth = 0;

		int spacewidth = 0;

		Texture* tex;
	};
}

#endif