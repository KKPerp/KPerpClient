#ifndef _KPerpCore_Matrix_hpp_
#define _KPerpCore_Matrix_hpp_

#include <KPerpCore/Vector.hpp>

#include <math.h>
#include <iostream>

#include <string.h>

#include <KPerpCore/Shape.hpp>

namespace kp {
	template <typename _Type, int _Dimension_x, int _Dimension_y>
	class Matrix {
	public:
		Matrix();

		Matrix(_Type Tstarter, ...);
		Matrix(Vector<_Type, _Dimension_y> Tstarter, ...);

		Matrix(_Type* Tarray);
		Matrix(Vector<_Type, _Dimension_y>* Tarray);

		Matrix operator+(const Matrix& Tmatrix);
		Vector<_Type, _Dimension_y> operator+(const Vector<_Type, _Dimension_y>& Tvector);
		Matrix operator+(const _Type& Tvalue);

		Matrix operator-(const Matrix& Tmatrix);
		Vector<_Type, _Dimension_y> operator-(const Vector<_Type, _Dimension_y>& Tvector);
		Matrix operator-(const _Type& Tvalue);

		Matrix operator*(const Matrix& Tmatrix);
		Vector<_Type, _Dimension_y> operator*(const Vector<_Type, _Dimension_y>& Tvector);

		Matrix operator/(const Matrix& Tmatrix);
		Vector<_Type, _Dimension_y> operator/(const Vector<_Type, _Dimension_y>& Tvector);

		//Vector& operator=(const Vector& Tvector) {
		//	memcpy(value, &Tvector, sizeof(this));
		//	return *this;
		//}

		Matrix& operator++();

		Matrix& operator--();

		Matrix& operator+=(const Matrix& Tmatrix);
		Matrix& operator+=(const _Type& Tvalue);

		Matrix& operator-=(const Matrix& Tmatrix);
		Matrix& operator-=(const _Type& Tvalue);

		Matrix& operator*=(const Matrix& Tmatrix);

		Matrix& operator/=(const Matrix& Tmatrix);

		bool operator==(const Matrix& Tmatrix);
		bool operator!=(const Matrix& Tmatrix);

		Matrix operator&&(const Matrix& Tmatrix);
		Matrix operator||(const Matrix& Tmatrix);

		Matrix operator()(const Matrix& Tmatrix, const Pred Tpred);

		Vector<_Type, _Dimension_y>& operator[](int Tindex);

		Vector<_Type, _Dimension_y> operator[](int Tindex) const;
	private:
		// Columns
		Vector<_Type, _Dimension_y> vectors[_Dimension_x];
	};

	typedef Matrix<float, 4, 4> mat4x4;

	float dot(const Vec2& Tlvec2, const Vec2& Trvec2);
	float dot(const Vec3& Tlvec3, const Vec3& Trvec3);
	float dot(const Vec4& Tlvec3, const Vec4& Trvec4);

	Vec2 normalize(const Vec2& Tvec2);
	Vec3 normalize(const Vec3& Tvec3);
	Vec4 normalize(const Vec4& Tvec4);

	template <typename _Type>
	Matrix<_Type, 4, 4> Translate(const Matrix<_Type, 4, 4>& Tmatrix, const Vector<_Type, 3>& Tvec3);
	template <typename _Type>
	Matrix<_Type, 4, 4> Translate(const Matrix<_Type, 4, 4>& Tmatrix, const Vector<_Type, 4>& Tvec4);

	template <typename _Type>
	Matrix<_Type, 4, 4> Scale(const Matrix<_Type, 4, 4>& Tmatrix, const Vector<_Type, 3>& Tvec3);
	template <typename _Type>
	Matrix<_Type, 4, 4> Scale(const Matrix<_Type, 4, 4>& Tmatrix, const Vector<_Type, 4>& Tvec4);

	template <typename _Type>
	Matrix<_Type, 4, 4> Rotate(const Matrix<_Type, 4, 4>& Tmatrix, _Type Tangle, const Vector<_Type, 3>& Tvec3);

	template <typename _Type>
	Matrix<_Type, 4, 4> Ortho(Rectangle<_Type> Trect);

	template <typename _Type>
	Matrix<_Type, 4, 4> Translate(const Matrix<float, 4, 4>& Tmatrix, const Vector3<_Type>& Tvec3);
	template <typename _Type>
	Matrix<_Type, 4, 4> Translate(const Matrix<float, 4, 4>& Tmatrix, const Vector4<_Type>& Tvec4);

	template <typename _Type>
	Matrix<_Type, 4, 4> Scale(const Matrix<float, 4, 4>& Tmatrix, const Vector3<_Type>& Tvec3);
	template <typename _Type>
	Matrix<_Type, 4, 4> Scale(const Matrix<float, 4, 4>& Tmatrix, const Vector4<_Type>& Tvec4);

	template <typename _Type>
	Matrix<_Type, 4, 4> Rotate(const Matrix<float, 4, 4>& Tmatrix, float Tangle, const Vector3<_Type>& Tvec3);

	template <typename _Type>
	Matrix<_Type, 4, 4> Ortho(Rectangle<float> Trect);

	template <typename _Type, int _Dimension_x, int _Dimension_y>
	Matrix<_Type, _Dimension_x, _Dimension_y> operator*(const _Type& Tvalue, const Matrix<_Type, _Dimension_x, _Dimension_y>& Tmatrix);
	template <typename _Type, int _Dimension_x, int _Dimension_y>
	Matrix<_Type, _Dimension_x, _Dimension_y> operator/(const _Type& Tvalue, const Matrix<_Type, _Dimension_x, _Dimension_y>& Tmatrix);
}

#include "Matrix.inl"

#endif