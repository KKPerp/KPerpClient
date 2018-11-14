#ifndef _KPerpCore_KPerpSound_InstantMediaLine_
#define _KPerpCore_KPerpSound_InstantMediaLine_

#include "Base\Core\WinMM.hpp"

#include "Base\MediaInterface.hpp"

namespace kp {
	class InstantMediaLine : public MediaInterface {
	public:
		InstantMediaLine() {

		}
		InstantMediaLine(const std::string& Tstring) {
			Load(Tstring);
		}

		InstantMediaLine(const InstantMediaLine& Timl) = delete;
		InstantMediaLine& operator=(const InstantMediaLine& Timl) = delete;

		~InstantMediaLine() {
			Close();
		}

		bool Load(const std::string& Tstring) {
			if (Tstring.size() > 127) {
				return 0;
			}

			filename = Tstring;

			alias = std::to_string((unsigned int)this);

			loaded = WinMM::mciSendStringA(("open \"" + Tstring + "\" alias kpIML" + alias).c_str(), returnstring, 101, NULL) == 0;

			return loaded;
		}

		bool Close() {
			if (loaded) {
				if (WinMM::mciSendStringA(("close kpIML" + alias).c_str(), returnstring, 101, NULL) == 0) {
					loaded = 0;
					filename = "";
					return 1;
				}
			}

			return 0;
		}

		void Play() {
			if (loaded) {
				WinMM::mciSendStringA(("play kpIML" + alias).c_str(), returnstring, 101, NULL);

				state = State::Playing;
			}
		}
		void Play(int Tsec) {
			if (loaded) {
				char _scharf[50];
				sprintf_s(_scharf, "%d", Tsec);

				WinMM::mciSendStringA(("play kpIML" + alias + " from " + std::string(_scharf)).c_str(), returnstring, 101, NULL);

				state = State::Playing;
			}
		}

		void Pause() {
			if (loaded) {
				WinMM::mciSendStringA(("pause kpIML" + alias).c_str(), returnstring, 101, NULL);

				state = State::Pause;
			}
		}

		void Resume() {
			if (loaded) {
				if (state == State::Pause) {
					WinMM::mciSendStringA(("resume kpIML" + alias).c_str(), returnstring, 101, NULL);

					state = State::Playing;
				}
			}
		}

		void Stop() {
			if (loaded) {
				WinMM::mciSendStringA(("stop kpIML" + alias).c_str(), returnstring, 101, NULL);

				state = State::Idle;
			}
		}

		void Seek(int Tmsecond) {
			if (loaded) {
				char _schar[50];
				sprintf_s(_schar, "%d", Tmsecond);

				WinMM::mciSendStringA(("seek kpIML" + alias + " to " + std::string(_schar)).c_str(), returnstring, 101, NULL);

				if (state == State::Playing) {
					Play();
				}
			}
		}

		int Pos() {
			if (loaded) {
				WinMM::mciSendStringA(("status kpIML" + alias + " position").c_str(), returnstring, 101, NULL);

				return atoi(returnstring);
			}

			return 0;
		}
		int Length() {
			if (loaded) {
				WinMM::mciSendStringA(("status kpIML" + alias + " length").c_str(), returnstring, 101, NULL);

				return atoi(returnstring);
			}

			return 0;
		}

		State getState() {
			return state;
		}

		void Play(int Tfrom, int Tto) {
			if (loaded) {
				char _scharf[50];
				sprintf_s(_scharf, "%d", Tfrom);
				char _schart[50];
				sprintf_s(_schart, "%d", Tto);

				WinMM::mciSendStringA(("play kpIML" + alias + " from " + std::string(_scharf) + " to " + std::string(_schart)).c_str(), returnstring, 101, NULL);

				state = State::Playing;
			}
		}

	private:
		std::string filename;
		State state;

		std::string alias;

		bool loaded;

		char returnstring[101];
	};

	class InstantMediaLineMPEG : public MediaInterface {
	public:
		InstantMediaLineMPEG() {

		}
		InstantMediaLineMPEG(const std::string& Tstring) {
			Load(Tstring);
		}

		InstantMediaLineMPEG(const InstantMediaLineMPEG& Timl) = delete;
		InstantMediaLineMPEG& operator=(const InstantMediaLineMPEG& Timl) = delete;

		~InstantMediaLineMPEG() {
			Close();
		}

		bool Load(const std::string& Tstring) {
			if (Tstring.size() > 127) {
				return 0;
			}

			filename = Tstring;

			alias = std::to_string((unsigned int)this);

			loaded = WinMM::mciSendStringA(("open \"" + Tstring + "\" type mpegvideo alias kpIML" + alias).c_str(), returnstring, 101, NULL) == 0;

			return loaded;
		}

		bool Close() {
			if (loaded) {
				if (WinMM::mciSendStringA(("close kpIML" + alias).c_str(), returnstring, 101, NULL) == 0) {
					loaded = 0;
					filename = "";
					return 1;
				}
			}

			return 0;
		}

		void Play() {
			if (loaded) {
				WinMM::mciSendStringA(("play kpIML" + alias + " from 0").c_str(), returnstring, 101, NULL);

				state = State::Playing;
			}
		}
		void Play(int Tsec) {
			if (loaded) {
				char _scharf[50];
				sprintf_s(_scharf, "%d", Tsec);

				//int lol = WinMM::mciSendStringA(("set kpIML" + alias + " speed 2").c_str(), returnstring, 101, NULL);
				WinMM::mciSendStringA(("play kpIML" + alias + " from " + std::string(_scharf)).c_str(), returnstring, 101, NULL);

				state = State::Playing;
			}
		}

		void Pause() {
			if (loaded) {
				WinMM::mciSendStringA(("pause kpIML" + alias).c_str(), returnstring, 101, NULL);

				state = State::Pause;
			}
		}

		void Resume() {
			if (loaded) {
				if (state == State::Pause) {
					WinMM::mciSendStringA(("resume kpIML" + alias).c_str(), returnstring, 101, NULL);

					state = State::Playing;
				}
			}
		}

		void Stop() {
			if (loaded) {
				WinMM::mciSendStringA(("stop kpIML" + alias).c_str(), returnstring, 101, NULL);

				state = State::Idle;
			}
		}

		void Seek(int Tmsecond) {
			if (loaded) {
				char _schar[50];
				sprintf_s(_schar, "%d", Tmsecond);

				WinMM::mciSendStringA(("seek kpIML" + alias + " to " + std::string(_schar)).c_str(), returnstring, 101, NULL);

				if (state == State::Playing) {
					Play();
				}
			}
		}

		int Pos() {
			if (loaded) {
				WinMM::mciSendStringA(("status kpIML" + alias + " position").c_str(), returnstring, 101, NULL);

				return atoi(returnstring);
			}

			return 0;
		}
		int Length() {
			if (loaded) {
				WinMM::mciSendStringA(("status kpIML" + alias + " length").c_str(), returnstring, 101, NULL);

				return atoi(returnstring);
			}

			return 0;
		}

		State getState() {
			return state;
		}

		void Play(int Tfrom, int Tto) {
			if (loaded) {
				char _scharf[50];
				sprintf_s(_scharf, "%d", Tfrom);
				char _schart[50];
				sprintf_s(_schart, "%d", Tto);

				WinMM::mciSendStringA(("play kpIML" + alias + " from " + std::string(_scharf) + " to " + std::string(_schart)).c_str(), returnstring, 101, NULL);

				state = State::Playing;
			}
		}

		void SetVolume(int Tvolume) {
			if (loaded) {
				char _scharv[50];
				sprintf_s(_scharv, "%d", Tvolume);

				if (Tvolume >= 0 && Tvolume <= 1000) {
					//std::string lol32 = ("setaudio kpIML" + alias + " volume to " + _scharv);
					WinMM::mciSendStringA(("setaudio kpIML" + alias + " volume to " + _scharv).c_str(), returnstring, 101, NULL);
					//int what = 0;
				}
			}
		}

	private:
		std::string filename;
		State state;

		std::string alias;

		bool loaded;

		char returnstring[101];
	};
}

#endif