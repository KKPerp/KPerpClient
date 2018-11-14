namespace kp {
	template<typename _Type>
	_Type pi() {
		return (_Type)acos(-1.0);
	}
	template<typename _Type>
	_Type pi_const() {
		return (_Type)3.14159265358979323846;
	}
	template<typename _Type>
	_Type radians(_Type Tvalue) {
		// pi / 180
		return (_Type)(Tvalue * (acos(-1.0) / 180.0));
	}
	template<typename _Type>
	_Type radians_const(_Type Tvalue) {
		// pi / 180
		return 	(_Type)(Tvalue * (_Type)0.0174532925199432957692);
	}
	template<typename _Type>
	constexpr _Type radians_constexpr(_Type Tvalue) {
		// pi / 180
		return 	(_Type)(Tvalue * (_Type)0.0174532925199432957692);
	}
}