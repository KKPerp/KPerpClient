#include "CritSection.hpp"

#include <windows.h>

namespace kp {
	class CritSection {
	public:
		CRITICAL_SECTION critsect;
	};

	Mutex::Mutex() {
		critsect = new CritSection;
		InitializeCriticalSection(&(critsect->critsect));

		state = 0;
	}
	Mutex::~Mutex() {
		if (state == 1) {
			LeaveCriticalSection(&(critsect->critsect));
			state = 0;
		}
		DeleteCriticalSection(&(critsect->critsect));
		delete critsect;
	}

	bool Mutex::enter() {
		EnterCriticalSection(&(critsect->critsect));
		state = 1;
		return state;
	}
	bool Mutex::leave() {
		LeaveCriticalSection(&(critsect->critsect));
		state = 0;
		return state;
	}
}