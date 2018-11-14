namespace kp {
	template <typename _Type, int _Dimension>
	Vector<_Type, _Dimension>::Vector() {
		memset(value, 0, sizeof(*this));
	}

	template <typename _Type, int _Dimension>
	Vector<_Type, _Dimension>::Vector(_Type Tstarter, ...) {
		memcpy(value, &Tstarter, sizeof(*this));
	}
	template <typename _Type, int _Dimension>
	Vector<_Type, _Dimension>::Vector(_Type* Tarray) {
		memcpy(value, Tarray, sizeof(*this));
	}

	template <typename _Type, int _Dimension>
	Vector<_Type, _Dimension>::Vector(const Vector2<_Type>& Tvec2) {
		memcpy(value, &Tvec2, sizeof(*this));
	}
	template <typename _Type, int _Dimension>
	Vector<_Type, _Dimension>::Vector(const Vector3<_Type>& Tvec3) {
		memcpy(value, &Tvec3, sizeof(*this));
	}
	template <typename _Type, int _Dimension>
	Vector<_Type, _Dimension>::Vector(const Vector4<_Type>& Tvec4) {
		memcpy(value, &Tvec4, sizeof(*this));
	}

	template <typename _Type, int _Dimension>
	Vector<_Type, _Dimension> Vector<_Type, _Dimension>::operator+(const Vector& Tvector) {
		Vector<_Type, _Dimension> _vector = *this;
		for (int i = 0;i < _Dimension;i++) {
			_vector.value[i] += Tvector.value[i];
		}
		return _vector;
	}
	template <typename _Type, int _Dimension>
	Vector<_Type, _Dimension> Vector<_Type, _Dimension>::operator+(const _Type& Tvalue) {
		Vector<_Type, _Dimension> _vector = *this;
		for (int i = 0;i < _Dimension;i++) {
			_vector.value[i] += Tvalue;
		}
		return _vector;
	}

	template <typename _Type, int _Dimension>
	Vector<_Type, _Dimension> Vector<_Type, _Dimension>::operator-(const Vector& Tvector) {
		Vector<_Type, _Dimension> _vector = *this;
		for (int i = 0;i < _Dimension;i++) {
			_vector.value[i] -= Tvector.value[i];
		}
		return _vector;
	}
	template <typename _Type, int _Dimension>
	Vector<_Type, _Dimension> Vector<_Type, _Dimension>::operator-(const _Type& Tvalue) {
		Vector<_Type, _Dimension> _vector = *this;
		for (int i = 0;i < _Dimension;i++) {
			_vector.value[i] -= Tvalue;
		}
		return _vector;
	}

	template <typename _Type, int _Dimension>
	Vector<_Type, _Dimension> Vector<_Type, _Dimension>::operator*(const Vector& Tvector) {
		Vector<_Type, _Dimension> _vector = *this;
		for (int i = 0;i < _Dimension;i++) {
			_vector.value[i] *= Tvector.value[i];
		}
		return _vector;
	}
	template <typename _Type, int _Dimension>
	Vector<_Type, _Dimension> Vector<_Type, _Dimension>::operator*(const _Type& Tvalue) {
		Vector<_Type, _Dimension> _vector = *this;
		for (int i = 0;i < _Dimension;i++) {
			_vector.value[i] *= Tvalue;
		}
		return _vector;
	}

	template <typename _Type, int _Dimension>
	Vector<_Type, _Dimension> Vector<_Type, _Dimension>::operator/(const Vector& Tvector) {
		Vector<_Type, _Dimension> _vector = *this;
		for (int i = 0;i < _Dimension;i++) {
			_vector.value[i] /= Tvector.value[i];
		}
		return _vector;
	}
	template <typename _Type, int _Dimension>
	Vector<_Type, _Dimension> Vector<_Type, _Dimension>::operator/(const _Type& Tvalue) {
		Vector<_Type, _Dimension> _vector = *this;
		for (int i = 0;i < _Dimension;i++) {
			_vector.value[i] /= Tvalue;
		}
		return _vector;
	}

	template <typename _Type, int _Dimension>
	Vector<_Type, _Dimension> Vector<_Type, _Dimension>::operator%(const Vector& Tvector) {
		Vector<_Type, _Dimension> _vector = *this;
		for (int i = 0;i < _Dimension;i++) {
			_vector.value[i] %= Tvector.value[i];
		}
		return _vector;
	}
	template <typename _Type, int _Dimension>
	Vector<_Type, _Dimension> Vector<_Type, _Dimension>::operator%(const _Type& Tvalue) {
		Vector<_Type, _Dimension> _vector = *this;
		for (int i = 0;i < _Dimension;i++) {
			_vector.value[i] %= Tvalue;
		}
		return _vector;
	}

	//Vector& operator=(const Vector& Tvector) {
	//	memcpy(value, &Tvector, sizeof(this));
	//	return *this;
	//}

	template <typename _Type, int _Dimension>
	Vector<_Type, _Dimension>& Vector<_Type, _Dimension>::operator++() {
		for (int i = 0;i < _Dimension;i++) {
			this->value[i]++;
		}
		return *this;
	}

	template <typename _Type, int _Dimension>
	Vector<_Type, _Dimension>& Vector<_Type, _Dimension>::operator--() {
		for (int i = 0;i < _Dimension;i++) {
			this->value[i]--;
		}
		return *this;
	}

	template <typename _Type, int _Dimension>
	Vector<_Type, _Dimension>& Vector<_Type, _Dimension>::operator+=(const Vector<_Type, _Dimension>& Tvector) {
		for (int i = 0;i < _Dimension;i++) {
			this->value[i] += Tvector.value[i];
		}
		return *this;
	}
	template <typename _Type, int _Dimension>
	Vector<_Type, _Dimension>& Vector<_Type, _Dimension>::operator+=(const _Type& Tvalue) {
		for (int i = 0;i < _Dimension;i++) {
			this->value[i] += Tvalue;
		}
		return *this;
	}

	template <typename _Type, int _Dimension>
	Vector<_Type, _Dimension>& Vector<_Type, _Dimension>::operator-=(const Vector<_Type, _Dimension>& Tvector) {
		for (int i = 0;i < _Dimension;i++) {
			this->value[i] -= Tvector.value[i];
		}
		return *this;
	}
	template <typename _Type, int _Dimension>
	Vector<_Type, _Dimension>& Vector<_Type, _Dimension>::operator-=(const _Type& Tvalue) {
		for (int i = 0;i < _Dimension;i++) {
			this->value[i] -= Tvalue;
		}
		return *this;
	}

	template <typename _Type, int _Dimension>
	Vector<_Type, _Dimension>& Vector<_Type, _Dimension>::operator*=(const Vector<_Type, _Dimension>& Tvector) {
		for (int i = 0;i < _Dimension;i++) {
			this->value[i] *= Tvector.value[i];
		}
		return *this;
	}
	template <typename _Type, int _Dimension>
	Vector<_Type, _Dimension>& Vector<_Type, _Dimension>::operator*=(const _Type& Tvalue) {
		for (int i = 0;i < _Dimension;i++) {
			this->value[i] *= Tvalue;
		}
		return *this;
	}

	template <typename _Type, int _Dimension>
	Vector<_Type, _Dimension>& Vector<_Type, _Dimension>::operator/=(const Vector<_Type, _Dimension>& Tvector) {
		for (int i = 0;i < _Dimension;i++) {
			this->value[i] /= Tvector.value[i];
		}
		return *this;
	}
	template <typename _Type, int _Dimension>
	Vector<_Type, _Dimension>& Vector<_Type, _Dimension>::operator/=(const _Type& Tvalue) {
		for (int i = 0;i < _Dimension;i++) {
			this->value[i] /= Tvalue;
		}
		return *this;
	}

	template <typename _Type, int _Dimension>
	Vector<_Type, _Dimension>& Vector<_Type, _Dimension>::operator%=(const Vector<_Type, _Dimension>& Tvector) {
		for (int i = 0;i < _Dimension;i++) {
			this->value[i] %= Tvector.value[i];
		}
		return *this;
	}
	template <typename _Type, int _Dimension>
	Vector<_Type, _Dimension>& Vector<_Type, _Dimension>::operator%=(const _Type& Tvalue) {
		for (int i = 0;i < _Dimension;i++) {
			this->value[i] %= Tvalue;
		}
		return *this;
	}
	template <typename _Type, int _Dimension>
	bool Vector<_Type, _Dimension>::operator==(const Vector<_Type, _Dimension>& Tvector) {
		for (int i = 0;i < _Dimension;i++) {
			if (this->value[i] != Tvector.value[i]) {
				return 0;
			}
		}
		return 1;
	}
	template <typename _Type, int _Dimension>
	bool Vector<_Type, _Dimension>::operator!=(const _Type& Tvalue) {
		for (int i = 0;i < _Dimension;i++) {
			if (this->value[i] != Tvector.value[i]) {
				return 1;
			}
		}
		return 0;
	}

	template <typename _Type, int _Dimension>
	Vector<_Type, _Dimension> Vector<_Type, _Dimension>::operator&&(const Vector<_Type, _Dimension>& Tvector) {
		Vector<_Type, _Dimension> _vector = *this;
		for (int i = 0;i < _Dimension;i++) {
			_vector.value[i] &= Tvector.value[i];
		}
		return _vector;
	}
	template <typename _Type, int _Dimension>
	Vector<_Type, _Dimension> Vector<_Type, _Dimension>::operator||(const Vector<_Type, _Dimension>& Tvector) {
		Vector<_Type, _Dimension> _vector = *this;
		for (int i = 0;i < _Dimension;i++) {
			_vector.value[i] |= Tvector.value[i];
		}
		return _vector;
	}

	template <typename _Type, int _Dimension>
	Vector<_Type, _Dimension> Vector<_Type, _Dimension>::operator()(const Vector<_Type, _Dimension>& Tvector, const Pred Tpred) {
		Vector<_Type, _Dimension> _vector = Tvector;
		for (int i = 0;i < _Dimension;i++) {
			Tpred(sizeof(_Type), &(this->value[i]), &(_vector.value[i]));
		}
		return _vector;
	}

	template <typename _Type, int _Dimension>
	_Type& Vector<_Type, _Dimension>::operator[](int Tindex) {
		return value[Tindex];
	}

	template <typename _Type, int _Dimension>
	_Type Vector<_Type, _Dimension>::operator[](int Tindex) const {
		return value[Tindex];
	}

	//

	template <typename _Type>
	Vector2<_Type>::Vector2() {

	}

	template <typename _Type>
	Vector2<_Type>::Vector2(Point<_Type> Tpoint) {
		this->x = Tpoint.x;
		this->y = Tpoint.y;
	}

	template <typename _Type>
	Vector2<_Type>::Vector2(_Type Tx, _Type Ty) {
		this->x = Tx;
		this->y = Ty;
	}

	template <typename _Type>
	Vector2<_Type>::Vector2(Vector<_Type,2> Tvec2) {
		this->x = Tvec2[0];
		this->y = Tvec2[1];
	}

	template <typename _Type>
	Vector2<_Type> Vector2<_Type>::operator+(const Vector2<_Type>& Tvector) {
		Vector2<_Type> _vector = *this;
		_vector.x += Tvector.x;
		_vector.y += Tvector.y;

		return _vector;
	}
	template <typename _Type>
	Vector2<_Type> Vector2<_Type>::operator+(const _Type& Tvalue) {
		Vector2<_Type> _vector = *this;
		_vector.x += Tvalue;
		_vector.y += Tvalue;

		return _vector;
	}

	template <typename _Type>
	Vector2<_Type> Vector2<_Type>::operator-(const Vector2<_Type>& Tvector) {
		Vector2<_Type> _vector = *this;
		_vector.x -= Tvector.x;
		_vector.y -= Tvector.y;

		return _vector;
	}
	template <typename _Type>
	Vector2<_Type> Vector2<_Type>::operator-(const _Type& Tvalue) {
		Vector2<_Type> _vector = *this;
		_vector.x -= Tvalue;
		_vector.y -= Tvalue;

		return _vector;
	}

	template <typename _Type>
	Vector2<_Type> Vector2<_Type>::operator*(const Vector2<_Type>& Tvector) {
		Vector2<_Type> _vector = *this;
		_vector.x *= Tvector.x;
		_vector.y *= Tvector.y;

		return _vector;
	}
	template <typename _Type>
	Vector2<_Type> Vector2<_Type>::operator*(const _Type& Tvalue) {
		Vector2<_Type> _vector = *this;
		_vector.x *= Tvalue;
		_vector.y *= Tvalue;

		return _vector;
	}

	template <typename _Type>
	Vector2<_Type> Vector2<_Type>::operator/(const Vector2<_Type>& Tvector) {
		Vector2<_Type> _vector = *this;
		_vector.x /= Tvector.x;
		_vector.y /= Tvector.y;

		return _vector;
	}
	template <typename _Type>
	Vector2<_Type> Vector2<_Type>::operator/(const _Type& Tvalue) {
		Vector2<_Type> _vector = *this;
		_vector.x /= Tvalue;
		_vector.y /= Tvalue;

		return _vector;
	}

	//Vector2<_Type>& operator=(const Vector2<_Type>& Tvector) {
	//	memcpy(value, &Tvector, sizeof(this));
	//	return *this;
	//}

	template <typename _Type>
	Vector2<_Type>& Vector2<_Type>::operator++() {
		_vector.x++;
		_vector.y++;

		return *this;
	}

	template <typename _Type>
	Vector2<_Type>& Vector2<_Type>::operator--() {
		_vector.x--;
		_vector.y--;

		return *this;
	}

	template <typename _Type>
	Vector2<_Type>& Vector2<_Type>::operator+=(const Vector2<_Type>& Tvector) {
		this->x += Tvector.x;
		this->y += Tvector.y;

		return *this;
	}
	template <typename _Type>
	Vector2<_Type>& Vector2<_Type>::operator+=(const _Type& Tvalue) {
		this->x += Tvalue;
		this->y += Tvalue;

		return *this;
	}

	template <typename _Type>
	Vector2<_Type>& Vector2<_Type>::operator-=(const Vector2<_Type>& Tvector) {
		this->x -= Tvector.x;
		this->y -= Tvector.y;

		return *this;
	}
	template <typename _Type>
	Vector2<_Type>& Vector2<_Type>::operator-=(const _Type& Tvalue) {
		this->x -= Tvalue;
		this->y -= Tvalue;

		return *this;
	}

	template <typename _Type>
	Vector2<_Type>& Vector2<_Type>::operator*=(const Vector2<_Type>& Tvector) {
		this->x *= Tvector.x;
		this->y *= Tvector.y;

		return *this;
	}
	template <typename _Type>
	Vector2<_Type>& Vector2<_Type>::operator*=(const _Type& Tvalue) {
		this->x *= Tvalue;
		this->y *= Tvalue;

		return *this;
	}

	template <typename _Type>
	Vector2<_Type>& Vector2<_Type>::operator/=(const Vector2<_Type>& Tvector) {
		this->x /= Tvector.x;
		this->y /= Tvector.y;

		return *this;
	}
	template <typename _Type>
	Vector2<_Type>& Vector2<_Type>::operator/=(const _Type& Tvalue) {
		this->x /= Tvalue;
		this->y /= Tvalue;

		return *this;
	}

	template <typename _Type>
	bool Vector2<_Type>::operator==(const Vector2<_Type>& Tvector) const {
		return (this->x == Tvector.x && this->y == Tvector.y);
	}
	template <typename _Type>
	bool Vector2<_Type>::operator!=(const Vector2<_Type>& Tvector) const {
		return (this->x != Tvector.x || this->y != Tvector.y);
	}

	template <typename _Type>
	_Type Vector2<_Type>::mul() const {
		return this->x * this->y;
	}

	template <typename _Type>
	Vector2<_Type>::operator Point<_Type>() {
		Point<_Type> _point;
		_point.x = this->x;
		_point.y = this->y;
		return _point;
	}

	template <typename _Type>
	Vector2<_Type>::operator Vector<_Type,2>() {
		Vec2 _vec2;
		_vec2.x = this->x;
		_vec2.y = this->y;

		return _vec2
	}

	template <typename _Type>
	bool operator==(const Vector2<_Type>& Tlvector, const Vector2<_Type>& Trvector) {
		return (Tlvector->x == Trvector.x && Tlvector->y == Trvector.y);
	}

	template <typename _Type>
	bool operator!=(const Vector2<_Type>& Tlvector, const Vector2<_Type>& Trvector) {
		return (Tlvector->x != Trvector.x || Tlvector->y != Trvector.y);
	}

	//

	template <typename _Type>
	Vector3<_Type>::Vector3() {

	}

	template <typename _Type>
	Vector3<_Type>::Vector3(Point3D<_Type> Tpoint) {
		this->x = Tpoint.x;
		this->y = Tpoint.y;
		this->z = Tpoint.z;
	}

	template <typename _Type>
	Vector3<_Type>::Vector3(_Type Tx, _Type Ty, _Type Tz) {
		this->x = Tx;
		this->y = Ty;
		this->z = Tz;
	}

	template <typename _Type>
	Vector3<_Type>::Vector3(Vector<_Type, 3> Tvec3) {
		this->x = Tvec3[0];
		this->y = Tvec3[1];
		this->z = Tvec3[2];
	}

	template <typename _Type>
	Vector3<_Type> Vector3<_Type>::operator+(const Vector3<_Type>& Tvector) {
		Vector3<_Type> _vector = *this;
		_vector.x += Tvector.x;
		_vector.y += Tvector.y;
		_vector.z += Tvector.z;

		return _vector;
	}
	template <typename _Type>
	Vector3<_Type> Vector3<_Type>::operator+(const _Type& Tvalue) {
		Vector3<_Type> _vector = *this;
		_vector.x += Tvalue;
		_vector.y += Tvalue;
		_vector.z += Tvalue;

		return _vector;
	}

	template <typename _Type>
	Vector3<_Type> Vector3<_Type>::operator-(const Vector3<_Type>& Tvector) {
		Vector3<_Type> _vector = *this;
		_vector.x -= Tvector.x;
		_vector.y -= Tvector.y;
		_vector.z -= Tvector.z;

		return _vector;
	}
	template <typename _Type>
	Vector3<_Type> Vector3<_Type>::operator-(const _Type& Tvalue) {
		Vector3<_Type> _vector = *this;
		_vector.x -= Tvalue;
		_vector.y -= Tvalue;
		_vector.z -= Tvalue;

		return _vector;
	}

	template <typename _Type>
	Vector3<_Type> Vector3<_Type>::operator*(const Vector3<_Type>& Tvector) {
		Vector3<_Type> _vector = *this;
		_vector.x *= Tvector.x;
		_vector.y *= Tvector.y;
		_vector.z *= Tvector.z;

		return _vector;
	}
	template <typename _Type>
	Vector3<_Type> Vector3<_Type>::operator*(const _Type& Tvalue) {
		Vector3<_Type> _vector = *this;
		_vector.x *= Tvalue;
		_vector.y *= Tvalue;
		_vector.z *= Tvalue;

		return _vector;
	}

	template <typename _Type>
	Vector3<_Type> Vector3<_Type>::operator/(const Vector3<_Type>& Tvector) {
		Vector3<_Type> _vector = *this;
		_vector.x /= Tvector.x;
		_vector.y /= Tvector.y;
		_vector.z /= Tvector.z;

		return _vector;
	}
	template <typename _Type>
	Vector3<_Type> Vector3<_Type>::operator/(const _Type& Tvalue) {
		Vector3<_Type> _vector = *this;
		_vector.x /= Tvalue;
		_vector.y /= Tvalue;
		_vector.z /= Tvalue;

		return _vector;
	}

	//Vector3<_Type>& operator=(const Vector3<_Type>& Tvector) {
	//	memcpy(value, &Tvector, sizeof(this));
	//	return *this;
	//}

	template <typename _Type>
	Vector3<_Type>& Vector3<_Type>::operator++() {
		_vector.x++;
		_vector.y++;
		_vector.z++;

		return *this;
	}

	template <typename _Type>
	Vector3<_Type>& Vector3<_Type>::operator--() {
		_vector.x--;
		_vector.y--;
		_vector.z--;

		return *this;
	}

	template <typename _Type>
	Vector3<_Type>& Vector3<_Type>::operator+=(const Vector3<_Type>& Tvector) {
		this->x += Tvector.x;
		this->y += Tvector.y;
		this->z += Tvector.z;

		return *this;
	}
	template <typename _Type>
	Vector3<_Type>& Vector3<_Type>::operator+=(const _Type& Tvalue) {
		this->x += Tvalue;
		this->y += Tvalue;
		this->z += Tvalue;

		return *this;
	}

	template <typename _Type>
	Vector3<_Type>& Vector3<_Type>::operator-=(const Vector3<_Type>& Tvector) {
		this->x -= Tvector.x;
		this->y -= Tvector.y;
		this->z -= Tvector.z;

		return *this;
	}
	template <typename _Type>
	Vector3<_Type>& Vector3<_Type>::operator-=(const _Type& Tvalue) {
		this->x -= Tvalue;
		this->y -= Tvalue;
		this->z -= Tvalue;

		return *this;
	}

	template <typename _Type>
	Vector3<_Type>& Vector3<_Type>::operator*=(const Vector3<_Type>& Tvector) {
		this->x *= Tvector.x;
		this->y *= Tvector.y;
		this->z *= Tvector.z;

		return *this;
	}
	template <typename _Type>
	Vector3<_Type>& Vector3<_Type>::operator*=(const _Type& Tvalue) {
		this->x *= Tvalue;
		this->y *= Tvalue;
		this->z *= Tvalue;

		return *this;
	}

	template <typename _Type>
	Vector3<_Type>& Vector3<_Type>::operator/=(const Vector3<_Type>& Tvector) {
		this->x /= Tvector.x;
		this->y /= Tvector.y;
		this->z /= Tvector.z;

		return *this;
	}
	template <typename _Type>
	Vector3<_Type>& Vector3<_Type>::operator/=(const _Type& Tvalue) {
		this->x /= Tvalue;
		this->y /= Tvalue;
		this->z /= Tvalue;

		return *this;
	}

	template <typename _Type>
	bool Vector3<_Type>::operator==(const Vector3<_Type>& Tvector) const {
		return (this->x == Tvector.x && this->y == Tvector.y && this->z == Tvector.z);;
	}
	template <typename _Type>
	bool Vector3<_Type>::operator!=(const Vector3<_Type>& Tvector) const {
		return (this->x != Tvector.x || this->y != Tvector.y || this->z != Tvector.z);
	}

	template <typename _Type>
	_Type Vector3<_Type>::mul() const {
		return this->x * this->y * this->z;
	}

	template <typename _Type>
	Vector3<_Type>::operator Point3D<_Type>() {
		Point3D<_Type> _point;
		_point.x = this->x;
		_point.y = this->y;
		_point.z = this->z;
		return _point;
	}

	template <typename _Type>
	bool operator==(const Vector3<_Type>& Tlvector, const Vector3<_Type>& Trvector) {
		return (Tlvector->x == Trvector.x && Tlvector->y == Trvector.y && Tlvector->z == Trvector.z);
	}

	template <typename _Type>
	bool operator!=(const Vector3<_Type>& Tlvector, const Vector3<_Type>& Trvector) {
		return (Tlvector->x != Trvector.x || Tlvector->y != Trvector.y || Tlvector->z != Trvector.z);
	}

	//

	template <typename _Type>
	Vector4<_Type>::Vector4() {

	}

	template <typename _Type>
	Vector4<_Type>::Vector4(Point4D<_Type> Tpoint) {
		this->x = Tpoint.x;
		this->y = Tpoint.y;
		this->z = Tpoint.z;
		this->w = Tpoint.w;
	}

	template <typename _Type>
	Vector4<_Type>::Vector4(_Type Tx, _Type Ty, _Type Tz, _Type Tw) {
		this->x = Tx;
		this->y = Ty;
		this->z = Tz;
		this->w = Tw;
	}

	template <typename _Type>
	Vector4<_Type>::Vector4(Vector<_Type, 4> Tvec4) {
		this->x = Tvec4[0];
		this->y = Tvec4[1];
		this->z = Tvec4[2];
		this->w = Tvec4[3];
	}

	template <typename _Type>
	Vector4<_Type> Vector4<_Type>::operator+(const Vector4<_Type>& Tvector) {
		Vector4<_Type> _vector = *this;
		_vector.x += Tvector.x;
		_vector.y += Tvector.y;
		_vector.z += Tvector.z;
		_vector.w += Tvector.w;

		return _vector;
	}
	template <typename _Type>
	Vector4<_Type> Vector4<_Type>::operator+(const _Type& Tvalue) {
		Vector4<_Type> _vector = *this;
		_vector.x += Tvalue;
		_vector.y += Tvalue;
		_vector.z += Tvalue;
		_vector.w += Tvalue;

		return _vector;
	}

	template <typename _Type>
	Vector4<_Type> Vector4<_Type>::operator-(const Vector4<_Type>& Tvector) {
		Vector4<_Type> _vector = *this;
		_vector.x -= Tvector.x;
		_vector.y -= Tvector.y;
		_vector.z -= Tvector.z;
		_vector.w -= Tvector.z;

		return _vector;
	}
	template <typename _Type>
	Vector4<_Type> Vector4<_Type>::operator-(const _Type& Tvalue) {
		Vector4<_Type> _vector = *this;
		_vector.x -= Tvalue;
		_vector.y -= Tvalue;
		_vector.z -= Tvalue;
		_vector.w -= Tvalue;

		return _vector;
	}

	template <typename _Type>
	Vector4<_Type> Vector4<_Type>::operator*(const Vector4<_Type>& Tvector) {
		Vector4<_Type> _vector = *this;
		_vector.x *= Tvector.x;
		_vector.y *= Tvector.y;
		_vector.z *= Tvector.z;
		_vector.w *= Tvector.w;

		return _vector;
	}
	template <typename _Type>
	Vector4<_Type> Vector4<_Type>::operator*(const _Type& Tvalue) {
		Vector4<_Type> _vector = *this;
		_vector.x *= Tvalue;
		_vector.y *= Tvalue;
		_vector.z *= Tvalue;
		_vector.w *= Tvalue;

		return _vector;
	}

	template <typename _Type>
	Vector4<_Type> Vector4<_Type>::operator/(const Vector4<_Type>& Tvector) {
		Vector4<_Type> _vector = *this;
		_vector.x /= Tvector.x;
		_vector.y /= Tvector.y;
		_vector.z /= Tvector.z;
		_vector.w /= Tvector.w;

		return _vector;
	}
	template <typename _Type>
	Vector4<_Type> Vector4<_Type>::operator/(const _Type& Tvalue) {
		Vector4<_Type> _vector = *this;
		_vector.x /= Tvalue;
		_vector.y /= Tvalue;
		_vector.z /= Tvalue;
		_vector.w /= Tvalue;

		return _vector;
	}

	//Vector4<_Type>& operator=(const Vector4<_Type>& Tvector) {
	//	memcpy(value, &Tvector, sizeof(this));
	//	return *this;
	//}

	template <typename _Type>
	Vector4<_Type>& Vector4<_Type>::operator++() {
		_vector.x++;
		_vector.y++;
		_vector.z++;
		_vector.w++;

		return *this;
	}

	template <typename _Type>
	Vector4<_Type>& Vector4<_Type>::operator--() {
		_vector.x--;
		_vector.y--;
		_vector.z--;
		_vector.w--;

		return *this;
	}

	template <typename _Type>
	Vector4<_Type>& Vector4<_Type>::operator+=(const Vector4<_Type>& Tvector) {
		this->x += Tvector.x;
		this->y += Tvector.y;
		this->z += Tvector.z;
		this->w += Tvector.w;

		return *this;
	}
	template <typename _Type>
	Vector4<_Type>& Vector4<_Type>::operator+=(const _Type& Tvalue) {
		this->x += Tvalue;
		this->y += Tvalue;
		this->z += Tvalue;
		this->w += Tvalue;

		return *this;
	}

	template <typename _Type>
	Vector4<_Type>& Vector4<_Type>::operator-=(const Vector4<_Type>& Tvector) {
		this->x -= Tvector.x;
		this->y -= Tvector.y;
		this->z -= Tvector.z;
		this->w -= Tvector.w;

		return *this;
	}
	template <typename _Type>
	Vector4<_Type>& Vector4<_Type>::operator-=(const _Type& Tvalue) {
		this->x -= Tvalue;
		this->y -= Tvalue;
		this->z -= Tvalue;
		this->w -= Tvalue;

		return *this;
	}

	template <typename _Type>
	Vector4<_Type>& Vector4<_Type>::operator*=(const Vector4<_Type>& Tvector) {
		this->x *= Tvector.x;
		this->y *= Tvector.y;
		this->z *= Tvector.z;
		this->w *= Tvector.w;

		return *this;
	}
	template <typename _Type>
	Vector4<_Type>& Vector4<_Type>::operator*=(const _Type& Tvalue) {
		this->x *= Tvalue;
		this->y *= Tvalue;
		this->z *= Tvalue;
		this->w *= Tvalue;

		return *this;
	}

	template <typename _Type>
	Vector4<_Type>& Vector4<_Type>::operator/=(const Vector4<_Type>& Tvector) {
		this->x /= Tvector.x;
		this->y /= Tvector.y;
		this->z /= Tvector.z;
		this->w /= Tvector.w;

		return *this;
	}
	template <typename _Type>
	Vector4<_Type>& Vector4<_Type>::operator/=(const _Type& Tvalue) {
		this->x /= Tvalue;
		this->y /= Tvalue;
		this->z /= Tvalue;
		this->w /= Tvalue;

		return *this;
	}

	template <typename _Type>
	bool Vector4<_Type>::operator==(const Vector4<_Type>& Tvector) const {
		return (this->x == Tvector.x && this->y == Tvector.y && this->z == Tvector.z && this->w == Tvector.w);
	}
	template <typename _Type>
	bool Vector4<_Type>::operator!=(const Vector4<_Type>& Tvector) const {
		return (this->x != Tvector.x || this->y != Tvector.y || this->z != Tvector.z || this->w != Tvector.w);
	}

	template <typename _Type>
	_Type Vector4<_Type>::mul() const {
		return this->x * this->y * this->z * this->w;
	}

	template <typename _Type>
	bool operator==(const Vector4<_Type>& Tlvector, const Vector4<_Type>& Trvector) {
		return (Tlvector->x == Trvector.x && Tlvector->y == Trvector.y && Tlvector->z == Trvector.w && Tlvector->z == Trvector.w);
	}

	template <typename _Type>
	bool operator!=(const Vector4<_Type>& Tlvector, const Vector4<_Type>& Trvector) {
		return (Tlvector->x != Trvector.x || Tlvector->y != Trvector.y || Tlvector->z != Trvector.w && Tlvector->z == Trvector.w);
	}

	template <typename _Type>
	Vector4<_Type>::operator Point4D<_Type>() {
		Point4D<_Type> _point;
		_point.x = this->x;
		_point.y = this->y;
		_point.z = this->z;
		_point.w = this->w;
		return _point;
	}
}