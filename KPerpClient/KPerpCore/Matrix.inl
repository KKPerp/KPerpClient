namespace kp {
	template <typename _Type, int _Dimension_x, int _Dimension_y>
	Matrix<_Type, _Dimension_x, _Dimension_y>::Matrix() {
		memset(&vectors, 0, sizeof(*this));

		// Identity
		for (int i = 0;i < _Dimension_x;i++) {
			vectors[i][i] = 1;
		}
	}

	template <typename _Type, int _Dimension_x, int _Dimension_y>
	Matrix<_Type, _Dimension_x, _Dimension_y>::Matrix(_Type Tstarter, ...) {
		for (int i = 0;i < _Dimension_x;i++) {
			for (int j = 0;j < _Dimension_y;j++) {
				vectors[i][j] = (&Tstarter)[(j*_Dimension_x) + i];
			}
		}
	}
	template <typename _Type, int _Dimension_x, int _Dimension_y>
	Matrix<_Type, _Dimension_x, _Dimension_y>::Matrix(Vector<_Type, _Dimension_y> Tstarter, ...) {
		for (int i = 0;i < _Dimension_x;i++) {
			for (int j = 0;j < _Dimension_y;j++) {
				vectors[i][j] = ((_Type*)&Tstarter)[(j*_Dimension_x) + i];
			}
		}
	}

	template <typename _Type, int _Dimension_x, int _Dimension_y>
	Matrix<_Type, _Dimension_x, _Dimension_y>::Matrix(_Type* Tarray) {
		for (int i = 0;i < _Dimension_x;i++) {
			for (int j = 0;j < _Dimension_y;j++) {
				vectors[i][j] = Tarray[(j*_Dimension_x) + i];
			}
		}
	}
	template <typename _Type, int _Dimension_x, int _Dimension_y>
	Matrix<_Type, _Dimension_x, _Dimension_y>::Matrix(Vector<_Type, _Dimension_y>* Tarray) {
		for (int i = 0;i < _Dimension_x;i++) {
			for (int j = 0;j < _Dimension_y;j++) {
				vectors[i][j] = ((_Type*)&Tarray)[(j*_Dimension_x) + i];
			}
		}
	}

	template <typename _Type, int _Dimension_x, int _Dimension_y>
	Matrix<_Type, _Dimension_x, _Dimension_y> Matrix<_Type, _Dimension_x, _Dimension_y>::operator+(const Matrix& Tmatrix) {
		Matrix<_Type, _Dimension_x, _Dimension_y> _matrix = *this;
		for (int i = 0;i < _Dimension_x;i++) {
			_matrix.vectors[i] += Tmatrix.vectors[i];
		}
		return _matrix;
	}
	template <typename _Type, int _Dimension_x, int _Dimension_y>
	Vector<_Type, _Dimension_y> Matrix<_Type, _Dimension_x, _Dimension_y>:: operator+(const Vector<_Type, _Dimension_y>& Tvector) {
		Matrix<_Type, _Dimension_x, _Dimension_y> _matrix = *this;
		for (int i = 0;i < _Dimension_x;i++) {
			_matrix.vectors[i] += Tvector;
		}
		return _matrix;
	}
	template <typename _Type, int _Dimension_x, int _Dimension_y>
	Matrix<_Type, _Dimension_x, _Dimension_y> Matrix<_Type, _Dimension_x, _Dimension_y>:: operator+(const _Type& Tvalue) {
		Matrix<_Type, _Dimension_x, _Dimension_y> _matrix = *this;
		for (int i = 0;i < _Dimension_x;i++) {
			for (int j = 0;j < _Dimension_y;j++) {
				_matrix.vectors[i][j] += Tvalue;
			}
		}
		return _matrix;
	}

	template <typename _Type, int _Dimension_x, int _Dimension_y>
	Matrix<_Type, _Dimension_x, _Dimension_y> Matrix<_Type, _Dimension_x, _Dimension_y>::operator-(const Matrix& Tmatrix) {
		Matrix<_Type, _Dimension_x, _Dimension_y> _matrix = *this;
		for (int i = 0;i < _Dimension_x;i++) {
			_matrix.vectors[i] -= Tmatrix.vectors[i];
		}
		return _matrix;
	}
	template <typename _Type, int _Dimension_x, int _Dimension_y>
	Vector<_Type, _Dimension_y> Matrix<_Type, _Dimension_x, _Dimension_y>:: operator-(const Vector<_Type, _Dimension_y>& Tvector) {
		Matrix<_Type, _Dimension_x, _Dimension_y> _matrix = *this;
		for (int i = 0;i < _Dimension_x;i++) {
			_matrix.vectors[i] -= Tvector;
		}
		return _matrix;
	}
	template <typename _Type, int _Dimension_x, int _Dimension_y>
	Matrix<_Type, _Dimension_x, _Dimension_y> Matrix<_Type, _Dimension_x, _Dimension_y>:: operator-(const _Type& Tvalue) {
		Matrix<_Type, _Dimension_x, _Dimension_y> _matrix = *this;
		for (int i = 0;i < _Dimension_x;i++) {
			for (int j = 0;j < _Dimension_y;j++) {
				_matrix.vectors[i][j] -= Tvalue;
			}
		}
		return _matrix;
	}

	template <typename _Type, int _Dimension_x, int _Dimension_y>
	Matrix<_Type, _Dimension_x, _Dimension_y> Matrix<_Type, _Dimension_x, _Dimension_y>::operator*(const Matrix& Tmatrix) {
		Matrix<_Type, _Dimension_x, _Dimension_y> _matrix = *this;
		for (int j = 0;j < _Dimension_y;j++) {
			for (int i = 0;i < _Dimension_x;i++) {
				float _dot = 0;
				for (int k = 0;k < _Dimension_y;k++) {
					_dot += (vectors[k][j] * Tmatrix[i][k]);
				}
				_matrix[i][j] = _dot;
			}
		}
		return _matrix;
	}
	template <typename _Type, int _Dimension_x, int _Dimension_y>
	Vector<_Type, _Dimension_y> Matrix<_Type, _Dimension_x, _Dimension_y>:: operator*(const Vector<_Type, _Dimension_y>& Tvector) {
		Vector<_Type, _Dimension_y> _vector;
		for (int i = 0;i < _Dimension_y;i++) {
			float _dot = 0;
			for (int j = 0;j < _Dimension_x;j++) {
				_dot += (vectors[j][i] * Tvector[j]);
			}
			_vector[i] = _dot;
		}
		return _vector;
	}

	template <typename _Type, int _Dimension_x, int _Dimension_y>
	Matrix<_Type, _Dimension_x, _Dimension_y> Matrix<_Type, _Dimension_x, _Dimension_y>:: operator/(const Matrix& Tmatrix) {
		Matrix<_Type, _Dimension_x, _Dimension_y> _matrix = *this;
		for (int j = 0;j < _Dimension_y;j++) {
			for (int i = 0;i < _Dimension_x;i++) {
				float _dot = 0;
				for (int k = 0;k < _Dimension_y;k++) {
					_dot += (vectors[k][j] / Tmatrix[i][k]);
				}
				_matrix[i][j] = _dot;
			}
		}
		return _matrix;
	}
	template <typename _Type, int _Dimension_x, int _Dimension_y>
	Vector<_Type, _Dimension_y> Matrix<_Type, _Dimension_x, _Dimension_y>:: operator/(const Vector<_Type, _Dimension_y>& Tvector) {
		Vector<_Type, _Dimension_y> _vector;
		for (int i = 0;i < _Dimension_y;i++) {
			float _dot = 0;
			for (int j = 0;j < _Dimension_x;j++) {
				_dot += (vectors[j][i] * Tvector[j]);
			}
			_vector[i] = _dot;
		}
		return _vector;
	}

	//Vector& operator=(const Vector& Tvector) {
	//	memcpy(value, &Tvector, sizeof(this));
	//	return *this;
	//}

	template <typename _Type, int _Dimension_x, int _Dimension_y>
	Matrix<_Type, _Dimension_x, _Dimension_y>& Matrix<_Type, _Dimension_x, _Dimension_y>::operator++() {
		Matrix<_Type, _Dimension_x, _Dimension_y> _matrix = *this;
		for (int i = 0;i < _Dimension_x;i++) {
			_matrix.vectors[i]++;
		}
		return _matrix;
	}

	template <typename _Type, int _Dimension_x, int _Dimension_y>
	Matrix<_Type, _Dimension_x, _Dimension_y>& Matrix<_Type, _Dimension_x, _Dimension_y>::operator--() {
		Matrix<_Type, _Dimension_x, _Dimension_y> _matrix = *this;
		for (int i = 0;i < _Dimension_x;i++) {
			_matrix.vectors[i]--;
		}
		return _matrix;
	}

	template <typename _Type, int _Dimension_x, int _Dimension_y>
	Matrix<_Type, _Dimension_x, _Dimension_y>& Matrix<_Type, _Dimension_x, _Dimension_y>::operator+=(const Matrix& Tmatrix) {
		for (int i = 0;i < _Dimension_x;i++) {
			vectors[i] += Tmatrix.vectors[i];
		}
		return *this;
	}
	template <typename _Type, int _Dimension_x, int _Dimension_y>
	Matrix<_Type, _Dimension_x, _Dimension_y>& Matrix<_Type, _Dimension_x, _Dimension_y>::operator+=(const _Type& Tvalue) {
		for (int i = 0;i < _Dimension_x;i++) {
			vectors[i] += Tvalue;
		}
		return *this;
	}

	template <typename _Type, int _Dimension_x, int _Dimension_y>
	Matrix<_Type, _Dimension_x, _Dimension_y>& Matrix<_Type, _Dimension_x, _Dimension_y>::operator-=(const Matrix& Tmatrix) {
		for (int i = 0;i < _Dimension_x;i++) {
			vectors[i] -= Tmatrix.vectors[i];
		}
		return *this;
	}
	template <typename _Type, int _Dimension_x, int _Dimension_y>
	Matrix<_Type, _Dimension_x, _Dimension_y>& Matrix<_Type, _Dimension_x, _Dimension_y>::operator-=(const _Type& Tvalue) {
		for (int i = 0;i < _Dimension_x;i++) {
			vectors[i] -= Tvalue;
		}
		return *this;
	}

	template <typename _Type, int _Dimension_x, int _Dimension_y>
	Matrix<_Type, _Dimension_x, _Dimension_y>& Matrix<_Type, _Dimension_x, _Dimension_y>::operator*=(const Matrix& Tmatrix) {
		Matrix<_Type, _Dimension_x, _Dimension_y> _matrix = *this;
		for (int i = 0;i < _Dimension_x;i++) {
			for (int j = 0;j < _Dimension_y;j++) {
				float _dot = 0;
				for (int k = 0;k < _Dimension_x;k++) {
					_dot += (_matrix[k][j] * Tmatrix[i][k]);
				}
				vectors[i][j] = _dot;
			}
		}
		return *this;
	}

	template <typename _Type, int _Dimension_x, int _Dimension_y>
	Matrix<_Type, _Dimension_x, _Dimension_y>& Matrix<_Type, _Dimension_x, _Dimension_y>::operator/=(const Matrix& Tmatrix) {
		Matrix<_Type, _Dimension_x, _Dimension_y> _matrix = *this;
		for (int i = 0;i < _Dimension_x;i++) {
			for (int j = 0;j < _Dimension_y;j++) {
				float _dot = 0;
				for (int k = 0;k < _Dimension_x;k++) {
					_dot += (_matrix[k][j] / Tmatrix[i][k]);
				}
				vectors[i][j] = _dot;
			}
		}
		return *this;
	}

	template <typename _Type, int _Dimension_x, int _Dimension_y>
	bool Matrix<_Type, _Dimension_x, _Dimension_y>::operator==(const Matrix& Tmatrix) {
		for (int i = 0;i < _Dimension_x;i++) {
			if (this->vectors[i] != Tmatrix[i]) {
				return 0;
			}
		}
		return 1;
	}
	template <typename _Type, int _Dimension_x, int _Dimension_y>
	bool Matrix<_Type, _Dimension_x, _Dimension_y>::operator!=(const Matrix& Tmatrix) {
		for (int i = 0;i < _Dimension_x;i++) {
			if (this->vectors[i] != Tmatrix[i]) {
				return 1;
			}
		}
		return 0;
	}

	template <typename _Type, int _Dimension_x, int _Dimension_y>
	Matrix<_Type, _Dimension_x, _Dimension_y> Matrix<_Type, _Dimension_x, _Dimension_y>:: operator&&(const Matrix& Tmatrix) {
		Matrix<_Type, _Dimension_x, _Dimension_y> _matrix = *this;
		for (int i = 0;i < _Dimension_x;i++) {
			_matrix.vectors[i] &= Tmatrix.vectors[i];
		}
		return _matrix;
	}
	template <typename _Type, int _Dimension_x, int _Dimension_y>
	Matrix<_Type, _Dimension_x, _Dimension_y> Matrix<_Type, _Dimension_x, _Dimension_y>:: operator||(const Matrix& Tmatrix) {
		Matrix<_Type, _Dimension_x, _Dimension_y> _matrix = *this;
		for (int i = 0;i < _Dimension_x;i++) {
			_matrix.vectors[i] |= Tmatrix.vectors[i];
		}
		return _matrix;
	}

	template <typename _Type, int _Dimension_x, int _Dimension_y>
	Matrix<_Type, _Dimension_x, _Dimension_y> Matrix<_Type, _Dimension_x, _Dimension_y>:: operator()(const Matrix& Tmatrix, const Pred Tpred) {
		Matrix<_Type, _Dimension_x, _Dimension_y> _matrix = *this;
		for (int i = 0;i < _Dimension_x;i++) {
			Tpred(sizeof(_Type), &(this->vectors[i]), &(Tmatrix[i]));
		}
		return _matrix;
	}
	template <typename _Type, int _Dimension_x, int _Dimension_y>
	Vector<_Type, _Dimension_y>& Matrix<_Type, _Dimension_x, _Dimension_y>::operator[](int Tindex) {
		return vectors[Tindex];
	}
	template <typename _Type, int _Dimension_x, int _Dimension_y>
	Vector<_Type, _Dimension_y> Matrix<_Type, _Dimension_x, _Dimension_y>::operator[](int Tindex) const {
		return vectors[Tindex];
	}

	template <typename _Type, int _Dimension_x, int _Dimension_y>
	Matrix<_Type, _Dimension_x, _Dimension_y> operator*(const _Type& Tvalue, const Matrix<_Type, _Dimension_x, _Dimension_y>& Tmatrix) {
		Matrix<_Type, _Dimension_x, _Dimension_y> _matrix;
		for (int i = 0;i < _Dimension_x;i++) {
			_matrix.vectors[i] *= Tmatrix.vectors[i];
		}
		return _matrix;
	}
	template <typename _Type, int _Dimension_x, int _Dimension_y>
	Matrix<_Type, _Dimension_x, _Dimension_y> operator/(const _Type& Tvalue, const Matrix<_Type, _Dimension_x, _Dimension_y>& Tmatrix) {
		Matrix<_Type, _Dimension_x, _Dimension_y> _matrix;
		for (int i = 0;i < _Dimension_x;i++) {
			_matrix.vectors[i] /= Tmatrix.vectors[i];
		}
		return _matrix;
	}

	static float dot(const Vec2& Tlvec2, const Vec2& Trvec2) {
		return (Tlvec2.x*Trvec2.x) + (Tlvec2.y*Trvec2.y);
	}
	static float dot(const Vec3& Tlvec3, const Vec3& Trvec3) {
		return (Tlvec3.x*Trvec3.x) + (Tlvec3.y*Trvec3.y);
	}
	static float dot(const Vec4& Tlvec3, const Vec4& Trvec4) {
		return (Tlvec3.x*Trvec4.x) + (Tlvec3.y*Trvec4.y);
	}

	static Vec2 normalize(const Vec2& Tvec2) {
		float _length = sqrt((Tvec2.x*Tvec2.y) + (Tvec2.y*Tvec2.y));
		_length = (_length == 0 ? 1 : _length);
		return Vec2(Tvec2) / _length;
	}
	static Vec3 normalize(const Vec3& Tvec3) {
		float _length = sqrt((Tvec3.x*Tvec3.y) + (Tvec3.y*Tvec3.y) + (Tvec3.z*Tvec3.z));
		_length = (_length == 0 ? 1 : _length);
		return Vec3(Tvec3) / _length;
	}
	static Vec4 normalize(const Vec4& Tvec4) {
		float _length = sqrt((Tvec4.x*Tvec4.y) + (Tvec4.y*Tvec4.y) + (Tvec4.z*Tvec4.z) + (Tvec4.w*Tvec4.w));
		_length = (_length == 0 ? 1 : _length);
		return Vec4(Tvec4) / _length;
	}

	template <typename _Type>
	Matrix<_Type, 4, 4> Translate(const Matrix<_Type, 4, 4>& Tmatrix, const Vector<_Type, 3>& Tvec3) {
		/*
			1  0  0  x
			0  1  0  y
			0  0  1  z
			0  0  0  1
		*/
		Matrix<_Type, 4, 4> _matrix;
		_matrix[3][0] = Tvec3[0];
		_matrix[3][1] = Tvec3[1];
		_matrix[3][2] = Tvec3[2];
		return Matrix<float, 4, 4>(Tmatrix) * _matrix;
	}
	template <typename _Type>
	Matrix<_Type, 4, 4> Translate(const Matrix<_Type, 4, 4>& Tmatrix, const Vector<_Type, 4>& Tvec4) {
		/*
			1  0  0  x
			0  1  0  y
			0  0  1  z
			0  0  0  w
		*/
		Matrix<_Type, 4, 4> _matrix;
		_matrix[3][0] = Tvec4[0];
		_matrix[3][1] = Tvec4[1];
		_matrix[3][2] = Tvec4[2];
		_matrix[3][3] = Tvec4[3];
		return Matrix<float, 4, 4>(Tmatrix) * _matrix;
	}

	template <typename _Type>
	Matrix<_Type, 4, 4> Scale(const Matrix<_Type, 4, 4>& Tmatrix, const Vector<_Type, 3>& Tvec3) {
		/*
			x  0  0  0
			0  y  0  0
			0  0  z  0
			0  0  0  1
		*/
		Matrix<_Type, 4, 4> _matrix;
		_matrix[0][0] = Tvec3[0];
		_matrix[1][1] = Tvec3[1];
		_matrix[2][2] = Tvec3[2];
		return Matrix<float, 4, 4>(Tmatrix) * _matrix;
	}
	template <typename _Type>
	Matrix<_Type, 4, 4> Scale(const Matrix<_Type, 4, 4>& Tmatrix, const Vector<_Type, 4>& Tvec4) {
		/*
			x  0  0  0
			0  y  0  0
			0  0  z  0
			0  0  0  w
		*/
		Matrix<_Type, 4, 4> _matrix;
		_matrix[0][0] = Tvec4[0];
		_matrix[1][1] = Tvec4[1];
		_matrix[2][2] = Tvec4[2];
		_matrix[3][3] = Tvec4[3];
		return Matrix<float, 4, 4>(Tmatrix) * _matrix;
	}

	template <typename _Type>
	Matrix<_Type, 4, 4> Rotate(const Matrix<_Type, 4, 4>& Tmatrix, _Type Tangle, const Vector<_Type, 3>& Tvec3) {
		/*
			cos+((x^2)(1-cos))   (xy(1-cos))-(z-sin)  (xz(1-cos))+(y-sin)  0
			(xy(1-cos))+(z-sin)  cos+((y^2)(1-cos))   (yz(1-cos))-(x-sin)  0
			(xz(1-cos))-(y-sin)  (yz(1-cos))+(x-sin)  cos+((z^2)(1-cos))   0
			0                    0                    0                    1
		*/
		Matrix<_Type, 4, 4> _matrix;

		const _Type	_cos = (_Type)cos(Tangle);
		const _Type _sin = (_Type)sin(Tangle);

		Vec3 axis = normalize(Tvec3);

		// 1 - cos(...)
		const _Type _1cos = (((_Type)1) - _cos);

		_matrix[0][0] = _cos + (axis.x * axis.x * _1cos);
		_matrix[1][0] = ((_Type)(axis.x * axis.y) * _1cos) - ((_Type)axis.z * _sin);
		_matrix[2][0] = ((_Type)(axis.x * axis.z) * _1cos) + ((_Type)axis.y * _sin);

		_matrix[0][1] = ((_Type)(axis.x * axis.y) * _1cos) + ((_Type)axis.z * _sin);
		_matrix[1][1] = _cos + (axis.y * axis.y * _1cos);
		_matrix[2][1] = ((_Type)(axis.y * axis.z) * _1cos) - ((_Type)axis.x * _sin);

		_matrix[0][2] = ((_Type)(axis.x * axis.z) * _1cos) - ((_Type)axis.y * _sin);
		_matrix[1][2] = ((_Type)(axis.y * axis.z) * _1cos) + ((_Type)axis.x * _sin);
		_matrix[2][2] = _cos + (axis.z * axis.z * _1cos);

		return Matrix<_Type, 4, 4>(Tmatrix) * _matrix;
	}

	template <typename _Type>
	Matrix<_Type, 4, 4> Ortho(Rectangle<_Type> Trect) {
		/*
			Transform to OpenGL coordinate

			2/(R-L)  0        0        -(R+L)/(R-L)
			0        2/(T-B)  0        -(T+B)/(T-B)
			0        0        -1       0
			0        0        0        0    
		*/

		Matrix<_Type, 4, 4> _matrix;
		_matrix[0][0] = ((_Type)2) / (Trect.c.x - Trect.a.x);
		_matrix[1][1] = ((_Type)2) / (Trect.a.y - Trect.c.y);
		_matrix[2][2] = ((_Type)-1);
		_matrix[3][0] = -(Trect.c.x + Trect.a.x) / (Trect.c.x - Trect.a.x);
		_matrix[3][1] = -(Trect.a.y + Trect.c.y) / (Trect.a.y - Trect.c.y);

		return _matrix;
	}

	template <typename _Type>
	Matrix<_Type, 4, 4> Translate(const Matrix<float, 4, 4>& Tmatrix, const Vector3<_Type>& Tvec3) {
		/*
			1  0  0  x
			0  1  0  y
			0  0  1  z
			0  0  0  1
		*/
		Matrix<float, 4, 4> _matrix;
		_matrix[3] = Tvec3;
		_matrix[3][3] = 1;
		return Matrix<float, 4, 4>(Tmatrix) * _matrix;
	}
	template <typename _Type>
	Matrix<_Type, 4, 4> Translate(const Matrix<float, 4, 4>& Tmatrix, const Vector4<_Type>& Tvec4) {
		/*
			1  0  0  x
			0  1  0  y
			0  0  1  z
			0  0  0  w
		*/
		Matrix<float, 4, 4> _matrix;
		_matrix[3] = Tvec4;
		return Matrix<float, 4, 4>(Tmatrix) * _matrix;
	}

	template <typename _Type>
	Matrix<_Type, 4, 4> Scale(const Matrix<float, 4, 4>& Tmatrix, const Vector3<_Type>& Tvec3) {
		/*
			x  0  0  0
			0  y  0  0
			0  0  z  0
			0  0  0  1
		*/
		Matrix<float, 4, 4> _matrix;
		_matrix[0][0] = Tvec3.x;
		_matrix[1][1] = Tvec3.y;
		_matrix[2][2] = Tvec3.z;
		return Matrix<float, 4, 4>(Tmatrix) * _matrix;
	}
	template <typename _Type>
	Matrix<_Type, 4, 4> Scale(const Matrix<float, 4, 4>& Tmatrix, const Vector4<_Type>& Tvec4) {
		/*
			x  0  0  0
			0  y  0  0
			0  0  z  0
			0  0  0  w
		*/
		Matrix<float, 4, 4> _matrix;
		_matrix[0][0] = Tvec4.x;
		_matrix[1][1] = Tvec4.y;
		_matrix[2][2] = Tvec4.z;
		_matrix[3][3] = Tvec4.w;
		return Matrix<float, 4, 4>(Tmatrix) * _matrix;
	}

	template <typename _Type>
	Matrix<_Type, 4, 4> Rotate(const Matrix<float, 4, 4>& Tmatrix, float Tangle, const Vector3<_Type>& Tvec3) {
		/*
			cos+((x^2)(1-cos))   (xy(1-cos))-(z-sin)  (xz(1-cos))+(y-sin)  0
			(xy(1-cos))+(z-sin)  cos+((y^2)(1-cos))   (yz(1-cos))-(x-sin)  0
			(xz(1-cos))-(y-sin)  (yz(1-cos))+(x-sin)  cos+((z^2)(1-cos))   0
			0                    0                    0                    1
		*/
		Matrix<float, 4, 4> _matrix;

		const float	_cos = (float)cos(Tangle);
		const float _sin = (float)sin(Tangle);

		Vec3 axis = normalize(Tvec3);

		// 1 - cos(...)
		const float _1cos = ((1.0f) - _cos);

		_matrix[0][0] = _cos + (axis.x * axis.x * _1cos);
		_matrix[1][0] = ((float)(axis.x * axis.y) * _1cos) - ((float)axis.z * _sin);
		_matrix[2][0] = ((float)(axis.x * axis.z) * _1cos) + ((float)axis.y * _sin);

		_matrix[0][1] = ((float)(axis.x * axis.y) * _1cos) + ((float)axis.z * _sin);
		_matrix[1][1] = _cos + (axis.y * axis.y * _1cos);
		_matrix[2][1] = ((float)(axis.y * axis.z) * _1cos) - ((float)axis.x * _sin);

		_matrix[0][2] = ((float)(axis.x * axis.z) * _1cos) - ((float)axis.y * _sin);
		_matrix[1][2] = ((float)(axis.y * axis.z) * _1cos) + ((float)axis.x * _sin);
		_matrix[2][2] = _cos + (axis.z * axis.z * _1cos);

		return Matrix<float, 4, 4>(Tmatrix) * _matrix;
	}

	template <typename _Type>
	Matrix<_Type, 4, 4> Ortho(Rectangle<float> Trect) {
		/*
		Transform to OpenGL coordinate

		2/(R-L)  0        0        -(R+L)/(R-L)
		0        2/(T-B)  0        -(T+B)/(T-B)
		0        0        -1       0
		0        0        0        0
		*/

		Matrix<float, 4, 4> _matrix;
		_matrix[0][0] = ((float)2) / (Trect.c.x - Trect.a.x);
		_matrix[1][1] = ((float)2) / (Trect.c.y - Trect.a.y);
		_matrix[2][2] = ((float)-1);
		_matrix[3][0] = -(Trect.c.x + Trect.a.x) / (Trect.c.x - Trect.a.x);
		_matrix[3][1] = -(Trect.c.y + Trect.a.y) / (Trect.c.y - Trect.a.y);

		return _matrix;
	}
}