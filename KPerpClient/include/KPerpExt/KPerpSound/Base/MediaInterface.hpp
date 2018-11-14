#ifndef _KPerpCore_KPerpSound_Base_MediaInterface_
#define _KPerpCore_KPerpSound_Base_MediaInterface_

#include <string>

namespace kp {
	class MediaInterface {
	public:
		enum class State {
			Idle,
			Playing,
			Pause,
		};

		virtual bool Load(const std::string& Tstring) = 0;
		virtual bool Close() = 0;

		virtual void Play() = 0;
		virtual void Play(int Tsec) = 0;

		virtual void Pause() = 0;
		virtual void Resume() = 0;

		virtual void Stop() = 0;

		virtual int Pos() = 0;
		virtual int Length() = 0;

		virtual State getState() = 0;
	};
}

#endif