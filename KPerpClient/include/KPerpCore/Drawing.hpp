#ifndef _KPerpCore_Drawing_hpp_
#define _KPerpCore_Drawing_hpp_


#include <KPerpCore/Shape.hpp>
#include <KPerpCore/Vector.hpp>
#include <KPerpCore/Matrix.hpp>

//#include "Resource.hpp"
//#include "Texture.hpp"

namespace kp {
	class Color {
	public:
		Color();
		Color(unsigned char Tr, unsigned char Tg, unsigned char Tb, unsigned char Ta=255);
		Color(unsigned int Tuint);

		unsigned char r() const;
		unsigned char g() const;
		unsigned char b() const;
		unsigned char a() const;
		unsigned int uint() const;
		unsigned int ruint() const;
		unsigned char& r();
		unsigned char& g();
		unsigned char& b();
		unsigned char& a();
		unsigned int& uint();

		Color operator* (const Color& Tcolor);
		bool operator== (const Color& Tcolor);
		bool operator!= (const Color& Tcolor);

		operator const Vec4() const;

		static const Color Red;
		static const Color Yellow;
		static const Color Green;
		static const Color Cyan;
		static const Color Blue;
		static const Color Magenta;

		static const Color Black;
		static const Color Gray;
		static const Color White;
	private:
		unsigned int color;
	};
	namespace Drawing {
		class Drawable {

		};
		struct Line : public Drawable, public kp::Line3D<float> {
			Line();
			Line(Vec3 Tv1, Vec3 Tv2, Vec4 Tc1 = Vec4(1, 1, 1, 1), Vec4 Tc2 = Vec4(1, 1, 1, 1), Vec2 Tt1 = Vec2(0, 0), Vec2 Tt2 = Vec2(1, 1));

			Vec2 t1;
			Vec2 t2;
			Vec4 c1;
			Vec4 c2;
		};
		struct Triangle : public Drawable, public kp::Triangle3D<float> {
			Triangle();
			Triangle(Vec3 Tv1, Vec3 Tv2, Vec3 Tv3, Vec4 Tc1 = Vec4(1, 1, 1, 1), Vec4 Tc2 = Vec4(1, 1, 1, 1), Vec4 Tc3 = Vec4(1, 1, 1, 1), Vec2 Tt1 = Vec2(0, 0), Vec2 Tt2 = Vec2(1, 0), Vec2 Tt3 = Vec2(0, 1), bool Tfill = 1);

			Vec2 t1;
			Vec2 t2;
			Vec2 t3;
			Vec4 c1;
			Vec4 c2;
			Vec4 c3;

			bool fill;
		};
		/*
		(a)1 - - - 2
		   |       |
		   |       |
		   |       |
		   4 - - - 3(c)
		*/
		struct Rectangle : kp::Rectangle3D<float> {
			Rectangle();
			Rectangle(Vec3 Tv1, Vec3 Tv2, Vec4 Tc1 = Vec4(1, 1, 1, 1), Vec4 Tc2 = Vec4(1, 1, 1, 1), Vec4 Tc3 = Vec4(1, 1, 1, 1), Vec4 Tc4 = Vec4(1, 1, 1, 1), Vec2 Tt1 = Vec2(0, 0), Vec2 Tt2 = Vec2(1, 0), Vec2 Tt3 = Vec2(0, 1), Vec2 Tt4 = Vec2(1, 1), bool Tfill = 1);

			Vec2 t1;
			Vec2 t2;
			Vec2 t3;
			Vec2 t4;
			Vec4 c1;
			Vec4 c2;
			Vec4 c3;
			Vec4 c4;

			bool fill;
		};

		class VertexArray;

		struct Vertex {
			Vertex();
			Vertex(Vec3 Tpos);
			Vertex(Vec3 Tpos, Vec4 Tcol);
			Vertex(Vec3 Tpos, Vec4 Tcol, Vec2 Ttex);

			VertexArray operator<<(const Vertex& Tvertex);

			Vec3 pos;
			Vec4 col;
			Vec2 tex;
		};

		class VertexArray {
		public:
			enum Type {
				Points,
				Line,
				LineStrip,
				Triangles,
				TriangleStrip,
				TriangleFan,
				Quads
			};

			VertexArray();
			VertexArray(Type Ttype, int Tcount);
			VertexArray(Type Ttype, int Tcount, const Vertex& Tvertex, ...);

			void create(Type Ttype, int Tcount);
			void create(Type Ttype, int Tcount, const Vertex& Tvertex, ...);

			VertexArray(const VertexArray& Tvertexarray);
			VertexArray(VertexArray&& Tvertexarray);

			Type getType() const;
			void setType(Type Ttype);

			int getSize() const;

			Vertex& operator[](int Tindex);
			Vertex operator[](int Tindex) const;

			VertexArray& operator=(const VertexArray& Tvertexarray);
			bool operator==(const VertexArray& Tvertexarray);
			bool operator!=(const VertexArray& Tvertexarray);

			VertexArray& operator<<(const Vertex& Tvertex);

			~VertexArray();

		private:
			Type type;

			int count;
			Vertex* vertices;
		};
	}
}

#endif
