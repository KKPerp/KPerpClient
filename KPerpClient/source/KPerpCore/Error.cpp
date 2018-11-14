#include <KPerpCore/Error.hpp>

#include <Windows.h>

namespace kp {
	Error lasterror = Error::NoError;

	Error getLastError() {
		return lasterror;
	}
	Error setLastError(Error Terror) {
		Error _lasterror = lasterror;
		lasterror = Terror;
		return _lasterror;
	}

	int getWindowLastError() {
		return GetLastError();
	}
	int setWindowLastError(int Terror) {
		int _lasterror = GetLastError();
		SetLastError(Terror);
		return _lasterror;
	}
}