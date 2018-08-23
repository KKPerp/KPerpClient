#include "Drawing.hpp"

#include <string.h>

#define colorint(_cl_r,_cl_g,_cl_b) (_cl_r) + ((_cl_g) * 256U) + ((_cl_b) * 65536U)
#define colorinta(_cl_r,_cl_g,_cl_b,_cl_a) (_cl_r) + ((_cl_g) * 256U) + ((_cl_b) * 65536U) + ((_cl_a) * 16777216U)

namespace kp {
	Color::Color() {

	}
	Color::Color(unsigned char Tr, unsigned char Tg, unsigned char Tb, unsigned char Ta) {
		color = colorinta(Tr, Tg, Tb, Ta);
	}
	Color::Color(unsigned int Tuint) {
		color = Tuint;
	}

	unsigned char Color::r() const {
		return ((unsigned char*)(&color))[0];
	}
	unsigned char Color::g() const {
		return ((unsigned char*)(&color))[1];
	}
	unsigned char Color::b() const {
		return ((unsigned char*)(&color))[2];
	}
	unsigned char Color::a() const {
		return ((unsigned char*)(&color))[3];
	}
	unsigned int Color::uint() const {
		return color;
	}
	unsigned char& Color::r() {
		return ((unsigned char*)(&color))[0];
	}
	unsigned char& Color::g() {
		return ((unsigned char*)(&color))[1];
	}
	unsigned char& Color::b() {
		return ((unsigned char*)(&color))[2];
	}
	unsigned char& Color::a() {
		return ((unsigned char*)(&color))[3];
	}
	unsigned int& Color::uint() {
		return color;
	}

	Color Color::operator* (const Color& Tcolor) {
		this->color = (unsigned int)colorinta((((unsigned char*)(&color))[0] / 255.0f) * (((unsigned char*)(&Tcolor))[0] / 255.0f),
			(((unsigned char*)(&color))[1] / 255.0f) * (((unsigned char*)(&Tcolor))[1] / 255.0f),
			(((unsigned char*)(&color))[2] / 255.0f) * (((unsigned char*)(&Tcolor))[2] / 255.0f),
			(((unsigned char*)(&color))[3] / 255.0f) * (((unsigned char*)(&Tcolor))[3] / 255.0f));

		return *this;
	}

	bool Color::operator== (const Color& Tcolor) {
		return (color == Tcolor.color);
	}

	bool Color::operator!= (const Color& Tcolor) {
		return (color != Tcolor.color);
	}

	Color::operator const Vec4() const {
		return Vec4(r() / 255.0f, g() / 255.0f, b() / 255.0f, a() / 255.0f);
	}

	const Color Color::Red(255, 0, 0, 255);
	const Color Color::Yellow(255, 255, 0, 255);
	const Color Color::Green(0, 255, 0, 255);
	const Color Color::Cyan(0, 255, 255, 255);
	const Color Color::Blue(0, 0, 255, 255);
	const Color Color::Magenta(255, 0, 255, 255);

	const Color Color::Black(0, 0, 0, 255);
	const Color Color::Gray(128, 128, 128, 255);
	const Color Color::White(255, 255, 255, 255);

	namespace Drawing {
		Line::Line() {

		}
		Line::Line(Vec3 Tv1, Vec3 Tv2, Vec4 Tc1, Vec4 Tc2, Vec2 Tt1, Vec2 Tt2) {
			a = Tv1;
			b = Tv2;

			c1 = Tc1;
			c2 = Tc2;

			t1 = Tt1;
			t2 = Tt2;
		}

		Triangle::Triangle() {

		}
		Triangle::Triangle(Vec3 Tv1, Vec3 Tv2, Vec3 Tv3, Vec4 Tc1, Vec4 Tc2, Vec4 Tc3, Vec2 Tt1, Vec2 Tt2, Vec2 Tt3, bool Tfill) {
			a = Tv1;
			b = Tv2;
			c = Tv3;

			c1 = Tc1;
			c2 = Tc2;
			c3 = Tc3;

			t1 = Tt1;
			t2 = Tt2;
			t3 = Tt3;

			fill = Tfill;
		}
		Rectangle::Rectangle() {

		}
		Rectangle::Rectangle(Vec3 Tv1, Vec3 Tv2, Vec4 Tc1, Vec4 Tc2, Vec4 Tc3, Vec4 Tc4, Vec2 Tt1, Vec2 Tt2, Vec2 Tt3, Vec2 Tt4, bool Tfill) {
			a = Tv1;
			c = Tv2;			   

			c1 = Tc1;
			c2 = Tc2;
			c3 = Tc3;
			c4 = Tc4;

			t1 = Tt1;
			t2 = Tt2;
			t3 = Tt3;
			t4 = Tt4;

			fill = Tfill;
		}

		Vertex::Vertex() {
			pos = Vec3(0.0f, 0.0f, 0.0f);
			col = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
			tex = Vec2(0.0f, 0.0f);
		}
		Vertex::Vertex(Vec3 Tpos) {
			pos = Tpos;
			col = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
			tex = Vec2(0.0f, 0.0f);
		}
		Vertex::Vertex(Vec3 Tpos, Vec4 Tcol) {
			pos = Tpos;
			col = Tcol;
			tex = Vec2(0.0f, 0.0f);
		}
		Vertex::Vertex(Vec3 Tpos, Vec4 Tcol, Vec2 Ttex) {
			pos = Tpos;
			col = Tcol;
			tex = Ttex;
		}

		VertexArray Vertex::operator<<(const Vertex& Tvertex) {
			VertexArray* _vertexarray = new VertexArray(VertexArray::Triangles, 2);
			(*_vertexarray)[0] = *this;
			(*_vertexarray)[1] = Tvertex;

			return *_vertexarray;
		}

		VertexArray::VertexArray() {
			vertices = NULL;
			count = 0;
			type = Points;
		}
		VertexArray::VertexArray(Type Ttype, int Tcount) {
			type = Ttype;
			if (Tcount > 0) {
				vertices = new Vertex[Tcount];
				count = Tcount;
			}
		}
		VertexArray::VertexArray(Type Ttype, int Tcount, const Vertex& Tvertex, ...) {
			type = Ttype;
			if (Tcount > 0) {
				vertices = new Vertex[Tcount];
				count = Tcount;

				memcpy(vertices, &Tvertex, sizeof(Vertex)*Tcount);
			}
		}

		void VertexArray::create(Type Ttype, int Tcount) {
			type = Ttype;
			if (Tcount > 0) {
				vertices = new Vertex[Tcount];
				count = Tcount;
			}
		}

		void VertexArray::create(Type Ttype, int Tcount, const Vertex& Tvertex, ...) {
			type = Ttype;
			if (Tcount > 0) {
				vertices = new Vertex[Tcount];
				count = Tcount;

				memcpy(vertices, &Tvertex, sizeof(Vertex)*Tcount);
			}
		}

		VertexArray::Type VertexArray::getType() const {
			return type;
		}
		void VertexArray::setType(Type Ttype) {
			type = Ttype;
		}

		int VertexArray::getSize() const {
			return count;
		}

		Vertex& VertexArray::operator[](int Tindex) {
			if (Tindex >= 0 && Tindex < count) {
				return vertices[Tindex];
			}
			return *vertices;
		}

		Vertex VertexArray::operator[](int Tindex) const {
			if (Tindex >= 0 && Tindex < count) {
				return vertices[Tindex];
			}
			return *vertices;
		}

		VertexArray& VertexArray::operator=(const VertexArray& Tvertexarray) {
			if (count == Tvertexarray.count) {
				memcpy(vertices, Tvertexarray.vertices, sizeof(Vertex)*count);
			}
			else {
				if (count == 0 && vertices == NULL) {
					vertices = new Vertex[Tvertexarray.count];
					memcpy(vertices, Tvertexarray.vertices, sizeof(Vertex)*count);
					count = Tvertexarray.count;
				}
				else {
					delete[] vertices;

					vertices = new Vertex[Tvertexarray.count];
					memcpy(vertices, Tvertexarray.vertices, sizeof(Vertex)*count);
					count = Tvertexarray.count;
				}
			}
			return *this;
		}
		bool VertexArray::operator==(const VertexArray& Tvertexarray) {
			if (count != Tvertexarray.count) {
				return 0;
			}
			else {
				return (memcmp(vertices, Tvertexarray.vertices, sizeof(Vertex)*count) == 0);
			}
		}
		bool VertexArray::operator!=(const VertexArray& Tvertexarray) {
			if (count != Tvertexarray.count) {
				return 1;
			}
			else {
				return (memcmp(vertices, Tvertexarray.vertices, sizeof(Vertex)*count) != 0);
			}
		}

		VertexArray& VertexArray::operator<<(const Vertex& Tvertex) {
			if (count == 0 && vertices == NULL) {
				vertices = new Vertex[1];
				vertices[0] = Tvertex;
				count = 1;
			}
			else {
				Vertex* _vertices = new Vertex[count];
				memcpy(_vertices, vertices, sizeof(Vertex)*count);

				delete[] vertices;

				vertices = new Vertex[count+1];
				memcpy(vertices, _vertices, sizeof(Vertex)*count);
				vertices[count] = Tvertex;

				count++;
			}

			return *this;
		}

		VertexArray::~VertexArray() {
			if (vertices != NULL) {
				delete[] vertices;
				vertices = NULL;

				count = 0;
			}
		}
	}
}