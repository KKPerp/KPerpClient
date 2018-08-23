#ifndef _KPerpCore_Vector_hpp_
#define _KPerpCore_Vector_hpp_

#include "Math.hpp"

namespace kp {
	typedef void(*Pred)(int, void*, void*);

	template <typename _Type>
	class Vector2;
	template <typename _Type>
	class Vector3;
	template <typename _Type>
	class Vector4;

	template <typename _Type, int _Dimension> class Vector {
	public:
		Vector();

		Vector(_Type Tstarter, ...);
		Vector(_Type* Tarray);

		Vector(const Vector2<_Type>& Tvec2);
		Vector(const Vector3<_Type>& Tvec3);
		Vector(const Vector4<_Type>& Tvec4);

		Vector operator+(const Vector& Tvector);
		Vector operator+(const _Type& Tvalue);

		Vector operator-(const Vector& Tvector);
		Vector operator-(const _Type& Tvalue);

		Vector operator*(const Vector& Tvector);
		Vector operator*(const _Type& Tvalue);

		Vector operator/(const Vector& Tvector);
		Vector operator/(const _Type& Tvalue);

		Vector operator%(const Vector& Tvector);
		Vector operator%(const _Type& Tvalue);

		//Vector& operator=(const Vector& Tvector) {
		//	memcpy(value, &Tvector, sizeof(this));
		//	return *this;
		//}

		Vector& operator++();

		Vector& operator--();

		Vector& operator+=(const Vector& Tvector);
		Vector& operator+=(const _Type& Tvalue);

		Vector& operator-=(const Vector& Tvector);
		Vector& operator-=(const _Type& Tvalue);

		Vector& operator*=(const Vector& Tvector);
		Vector& operator*=(const _Type& Tvalue);

		Vector& operator/=(const Vector& Tvector);
		Vector& operator/=(const _Type& Tvalue);

		Vector& operator%=(const Vector& Tvector);
		Vector& operator%=(const _Type& Tvalue);
		bool operator==(const Vector& Tvector);
		bool operator!=(const _Type& Tvalue);

		Vector operator&&(const Vector& Tvector);
		Vector operator||(const Vector& Tvector);

		Vector operator()(const Vector& Tvector, const Pred Tpred);

		_Type& operator[](int Tindex);

		_Type operator[](int Tindex) const;

	private:
		_Type value[_Dimension];
	};

	template <typename _Type> class Vector2 : public Point<_Type> {
	public:

		Vector2();

		Vector2(Point<_Type> Tpoint);
		Vector2(_Type Tx, _Type Ty);

		Vector2(Vector<_Type,2> Tvec2);

		Vector2 operator+(const Vector2& Tvector);
		Vector2 operator+(const _Type& Tvalue);

		Vector2 operator-(const Vector2& Tvector);
		Vector2 operator-(const _Type& Tvalue);

		Vector2 operator*(const Vector2& Tvector);
		Vector2 operator*(const _Type& Tvalue);

		Vector2 operator/(const Vector2& Tvector);
		Vector2 operator/(const _Type& Tvalue);

		//Vector2& operator=(const Vector2& Tvector) {
		//	memcpy(value, &Tvector, sizeof(this));
		//	return *this;
		//}

		Vector2& operator++();

		Vector2& operator--();

		Vector2& operator+=(const Vector2& Tvector);
		Vector2& operator+=(const _Type& Tvalue);

		Vector2& operator-=(const Vector2& Tvector);
		Vector2& operator-=(const _Type& Tvalue);

		Vector2& operator*=(const Vector2& Tvector);
		Vector2& operator*=(const _Type& Tvalue);

		Vector2& operator/=(const Vector2& Tvector);
		Vector2& operator/=(const _Type& Tvalue);

		bool operator==(const Vector2& Tvector);
		bool operator!=(const Vector2& Tvector);

		_Type mul() const;

		operator Point<_Type>();

		operator Vector<_Type,2>();
	};

	typedef Vector2<float> Vec2;

	template <typename _Type> class Vector3 : public Point3D<_Type> {
	public:

		Vector3();

		Vector3(Point3D<_Type> Tpoint);
		Vector3(_Type Tx, _Type Ty, _Type Tz);

		Vector3(Vector<_Type, 3> Tvec3);

		Vector3 operator+(const Vector3& Tvector);
		Vector3 operator+(const _Type& Tvalue);

		Vector3 operator-(const Vector3& Tvector);
		Vector3 operator-(const _Type& Tvalue);

		Vector3 operator*(const Vector3& Tvector);
		Vector3 operator*(const _Type& Tvalue);

		Vector3 operator/(const Vector3& Tvector);
		Vector3 operator/(const _Type& Tvalue);

		//Vector3& operator=(const Vector3& Tvector) {
		//	memcpy(value, &Tvector, sizeof(this));
		//	return *this;
		//}

		Vector3& operator++();

		Vector3& operator--();

		Vector3& operator+=(const Vector3& Tvector);
		Vector3& operator+=(const _Type& Tvalue);

		Vector3& operator-=(const Vector3& Tvector);
		Vector3& operator-=(const _Type& Tvalue);

		Vector3& operator*=(const Vector3& Tvector);
		Vector3& operator*=(const _Type& Tvalue);

		Vector3& operator/=(const Vector3& Tvector);
		Vector3& operator/=(const _Type& Tvalue);

		bool operator==(const Vector3& Tvector);
		bool operator!=(const Vector3& Tvector);

		_Type mul() const;

		operator Point3D<_Type>();
	};

	typedef Vector3<float> Vec3;

	template <typename _Type> class Vector4 : public Point4D<_Type> {
	public:

		Vector4();

		Vector4(Point4D<_Type> Tpoint);
		Vector4(_Type Tx, _Type Ty, _Type Tz, _Type Tw);

		Vector4(Vector<_Type, 4> Tvec4);

		Vector4 operator+(const Vector4& Tvector);
		Vector4 operator+(const _Type& Tvalue);

		Vector4 operator-(const Vector4& Tvector);
		Vector4 operator-(const _Type& Tvalue);

		Vector4 operator*(const Vector4& Tvector);
		Vector4 operator*(const _Type& Tvalue);

		Vector4 operator/(const Vector4& Tvector);
		Vector4 operator/(const _Type& Tvalue);

		//Vector4& operator=(const Vector4& Tvector) {
		//	memcpy(value, &Tvector, sizeof(this));
		//	return *this;
		//}

		Vector4& operator++();

		Vector4& operator--();

		Vector4& operator+=(const Vector4& Tvector);
		Vector4& operator+=(const _Type& Tvalue);

		Vector4& operator-=(const Vector4& Tvector);
		Vector4& operator-=(const _Type& Tvalue);

		Vector4& operator*=(const Vector4& Tvector);
		Vector4& operator*=(const _Type& Tvalue);

		Vector4& operator/=(const Vector4& Tvector);
		Vector4& operator/=(const _Type& Tvalue);

		bool operator==(const Vector4& Tvector);
		bool operator!=(const Vector4& Tvector);

		_Type mul() const;

		operator Point4D<_Type>();
	};

	typedef Vector4<float> Vec4;

	template <int lol> void fucc() {
		Vector<int, 5> gg;
		gg = Vector<int, 5>(1, 2, 3, 4, 5);
		gg += Vector<int, 5>(1, 2, 3, 4, 5);

	}
}

#include "Vector.inl"

#endif