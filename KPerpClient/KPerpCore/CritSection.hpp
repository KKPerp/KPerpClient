#ifndef __KPerpCore_CritSection_hpp_
#define __KPerpCore_CritSection_hpp_

namespace kp {
	// CritSection and Mutex :
	//  Block other thread use enter()
	//  Lets other thread use leave()
	//
	// Structure :
	//  Mutex mutex;
	//  mutex.enter();
	//  
	//  ...
	//  
	//  mutex.leave();

	class CritSection;

	class Mutex {
	public:
		Mutex();
		~Mutex();

		bool enter();
		bool leave();

	private:
		bool state;
		CritSection* critsect;
	};

	class Lock {
	public:
		Lock(Mutex& Tmutex);
		~Lock();

	private:
		Mutex * mutex;
	};

	class ControlableLock {
	public:
		ControlableLock(Mutex& Tmutex);
		ControlableLock(Mutex& Tmutex, bool Tlock);
		~ControlableLock();

		void lock();
		void unlock();

	private:
		Mutex * mutex;
		bool state;
	};

	class LocalLocker {
	public:
		LocalLocker(ControlableLock& Tclock);
		~LocalLocker();

	private:
		ControlableLock * lock;
	};

	void waitThisMutex(Mutex& Tmutex);
}

#endif