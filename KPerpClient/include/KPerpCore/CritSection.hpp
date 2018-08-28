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

		bool state;
		CritSection* critsect;
	};
}

#endif