#ifndef _KPerpCore_KPerpSound_WaveLine_
#define _KPerpCore_KPerpSound_WaveLine_

#include "Base/WaveOut.hpp"
#include "Base/MediaInterface.hpp"

namespace kp {
	class AudioFile {
	public:
		enum Type {
			WAV
		};

		AudioFile();
		AudioFile(const char* Tfilename);
		AudioFile(Type Ttype, const char* Tfilename) = delete; // not supported

		void Free();

		const char* filename;

		char* buffer;
		unsigned int size;
	};

	class WaveLine {
	public:
		WaveLine();
		WaveLine(AudioFile& Taudiofile);
		WaveLine(const void* Tbuffer, unsigned int Tsize);

		bool Load(AudioFile& Taudiofile);
		bool Load(const void* Tbuffer, unsigned int Tsize);

		bool Unload();

		void Play();

		void Pause();
		void Resume();

		void Stop();

		int Position();

		bool loaded();
		bool isPlaying();
		bool isPaused();

		~WaveLine();
	private:
		Base::WaveOut waveout;
		bool playing;
		bool pausing;

		Base::WaveBuffer wavebuffer;
	};
}

#endif