#ifndef _KPerpCore_Shape_hpp_
#define _KPerpCore_Shape_hpp_

#include "Math.hpp"

namespace kp {
	// Line : Just a pair of points 
	template <typename _Type> struct Line {
		Point<_Type> a;
		Point<_Type> b;
	};

	// Triangle : A group of three points 
	template <typename _Type> struct Triangle {
		Point<_Type> a;
		Point<_Type> b;
		Point<_Type> c;
	};

	// Rectangle : Two points as top-left and bottom-right corner 
	template <typename _Type> struct Rectangle {
		Point<_Type> a;
		Point<_Type> c;
	};

	// Line3D : Just a pair of point3Ds 
	template <typename _Type> struct Line3D {
		Point3D<_Type> a;
		Point3D<_Type> b;
	};

	// Triangle3D : A group of three point3Ds 
	template <typename _Type> struct Triangle3D {
		Point3D<_Type> a;
		Point3D<_Type> b;
		Point3D<_Type> c;
	};

	// Rectangle3D : Two point3Ds as top-left and bottom-right corner 
	template <typename _Type> struct Rectangle3D {
		Point3D<_Type> a;
		Point3D<_Type> c;
	};
}

#endif