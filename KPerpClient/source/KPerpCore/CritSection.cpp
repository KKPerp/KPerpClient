#include <KPerpCore/CritSection.hpp>

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

	Lock::Lock(Mutex& Tmutex) {
		mutex = &Tmutex;
		mutex->enter();
	}
	Lock::~Lock() {
		mutex->leave();
	}

	ControlableLock::ControlableLock(Mutex& Tmutex) {
		mutex = &Tmutex;
		mutex->enter();

		state = 1;
	}
	ControlableLock::ControlableLock(Mutex& Tmutex, bool Tlock) {
		mutex = &Tmutex;
		if (Tlock) {
			mutex->enter();

			state = 1;
		}
		else {
			state = 0;
		}
	}
	ControlableLock::~ControlableLock() {
		if (state) {
			mutex->leave();

			state = 0;
		}
	}

	void ControlableLock::lock() {
		if (!state) {
			mutex->enter();

			state = 1;
		}
	}
	void ControlableLock::unlock() {
		if (state) {
			mutex->leave();

			state = 0;
		}
	}

	LocalLocker::LocalLocker(ControlableLock& Tclock) {
		lock = &Tclock;
		lock->lock();
	}
	LocalLocker::~LocalLocker() {
		lock->unlock();
	}

	void waitThisMutex(Mutex& Tmutex) {
		Lock _lock(Tmutex);
	}
}