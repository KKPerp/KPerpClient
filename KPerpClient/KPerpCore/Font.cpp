#include "Font.hpp"

namespace kp {
	Font::Font() {

	}

	Font::Font(Texture &Ttex, int Tw, int Th, int Tfh) : height(Th), fullheight(Tfh) {
		fullwidth = 0;
		for (int i = 0;i < 255;i++) {
			width[i] = Tw;
			fullwidth = Tw;
		}
		spacewidth = Tw;
		tex = &Ttex;
	}

	Font::Font(Texture &Ttex, int Tw, int Th, int Tfh, unsigned char Tstart) : height(Th), fullheight(Tfh), start(Tstart) {
		fullwidth = 0;
		for (int i = 0;i < 255;i++) {
			width[i] = Tw;
			fullwidth = Tw;
		}
		spacewidth = Tw;
		tex = &Ttex;
	}

	Font::Font(Texture &Ttex, int Tw, int Th, int Tfh, unsigned char Tstart, unsigned char Tend) : height(Th), fullheight(Tfh), start(Tstart), end(Tend) {
		fullwidth = 0;
		for (int i = 0;i < 255;i++) {
			width[i] = Tw;
			fullwidth = Tw;
		}
		spacewidth = Tw;
		tex = &Ttex;
	}

	Font::Font(Texture &Ttex, int Tw, int Th, int Tfh, unsigned char Tstart, unsigned char Tend, bool Tm) : height(Th), fullheight(Tfh), start(Tstart), end(Tend), monospace(Tm) {
		fullwidth = 0;
		for (int i = 0;i < 255;i++) {
			width[i] = Tw;
			fullwidth = Tw;
		}
		spacewidth = Tw;
		tex = &Ttex;
	}

	Font::Font(Texture &Ttex, int Tw, int Th, int Tfh, unsigned char Tstart, unsigned char Tend, bool Tm, int Tsep) : height(Th), fullheight(Tfh), start(Tstart), end(Tend), monospace(Tm), sepration(Tsep) {
		fullwidth = 0;
		for (int i = 0;i < 255;i++) {
			width[i] = Tw;
			fullwidth = Tw;
		}
		spacewidth = Tw;
		tex = &Ttex;
	}

	Font::Font(Texture &Ttex, int Tw, int Th, int Tfh, unsigned char Tstart, unsigned char Tend, bool Tm, int Tsep, int Tspace) : height(Th), fullheight(Tfh), start(Tstart), end(Tend), monospace(Tm), sepration(Tsep) {
		fullwidth = 0;
		for (int i = 0;i < 255;i++) {
			width[i] = Tw;
			fullwidth = Tw;
		}
		tex = &Ttex;

		spacewidth = Tspace;
	}

	char Font::getStartChar() const {
		return start;
	}

	char Font::getEndChar() const {
		return end;
	}

	bool Font::getMonospace() const {
		return monospace;
	}

	int Font::getSepWidth() const {
		return sepration;
	}

	int* Font::getWidth() {
		return width;
	}

	int Font::getWidth(int Tpos) const {
		if ((Tpos < 0) || (Tpos > 255)) {
			return 0;;
		}
		return width[Tpos];
	}

	int Font::getHeight() const {
		return height;
	}

	int	Font::getFullWidth() const {
		return fullwidth;
	}

	int Font::getFullHeight() const {
		return fullheight;
	}

	Texture* Font::getTex() const {
		return tex;
	}

	int Font::getSpaceWidth() const {
		return spacewidth;
	}

	void Font::setStartChar(char Tvalue) {
		start = Tvalue;
	}

	void Font::setEndChar(char Tvalue) {
		end = Tvalue;
	}

	void Font::setMonospace(bool Tvalue) {
		monospace = Tvalue;
	}

	void Font::setSepWidth(int Tvalue) {
		sepration = Tvalue;
	}

	void Font::setWidth(int* Tvalue) {
		if (!monospace) {
			for (int i = 0;i < ((end - start)) + 1;i++) {
				width[start + i] = Tvalue[i];
			}
		}
	}

	void Font::setWidth(int Tpos, int Tvalue) {
		if ((Tpos < 0) || (Tpos > 255)) {
			return;
		}
		width[Tpos] = Tvalue;
	}

	void Font::setHeight(int Tvalue) {
		height = Tvalue;
	}

	void Font::setFullWidth(int Tvalue) {
		fullwidth = Tvalue;
	}

	void Font::setFullHeight(int Tvalue) {
		fullheight = Tvalue;
	}

	void Font::setSpaceWidth(int Tvalue) {
		spacewidth = Tvalue;
	}
}