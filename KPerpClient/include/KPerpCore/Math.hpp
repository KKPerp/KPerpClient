#ifndef _KPerpCore_Math_hpp_
#define _KPerpCore_Math_hpp_

#include <math.h>

namespace kp {
	// Point : A 2-dimension coordinate
	template <typename _Type> class Point {
	public:
		_Type x;
		_Type y;
	};
	// Point3D : A 3-dimension coordinate
	template <typename _Type> class Point3D {
	public:
		_Type x;
		_Type y;
		_Type z;
	};
	// Point4D : A 4-dimension coordinate
	template <typename _Type> class Point4D {
	public:
		_Type x;
		_Type y;
		_Type z;
		_Type w;
	};

	template<typename _Type>
	_Type pi();
	template<typename _Type>
	_Type pi_const();
	template<typename _Type>
	_Type radians(_Type Tvalue);
	template<typename _Type>
	_Type radians_const(_Type Tvalue);

}
#include <KPerpCore/Math.inl>

#endif