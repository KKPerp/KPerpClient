#include <KPerpExt/KPerpSound/WaveLine.hpp>

#include <algorithm>
#include <string>

namespace kp {
	AudioFile::AudioFile() {
		buffer = NULL;
	}
	AudioFile::AudioFile(const char* Tfilename) {
		buffer = NULL;

		std::string _filename = Tfilename;
		
		unsigned int _pos = _filename.find_last_of('.');
		std::string _type = _filename.substr(_pos + 1);

		std::transform(_type.begin(), _type.end(), _type.begin(), tolower);

		if (_type == "wav") {
			FILE* _file = NULL;

#if defined(_MSC_VER) && _MSC_VER >= 1400
			if (fopen_s(&_file, Tfilename, "rb") != 0) {
				return;
			}
#else
			_file = fopen(Tfilename, "rb");
			if (!_file) {
				return;
			}
#endif

			fseek(_file, 0, SEEK_END);
			unsigned int _sizef = ftell(_file);
			fseek(_file, 0, SEEK_SET);

			//*Tsize = _sizef;

			buffer = new char[_sizef];
			fread(buffer, 1, _sizef, _file);

			size = _sizef;

			fclose(_file);
		}
	}

	void AudioFile::Free() {
		if (buffer != NULL) {
			delete[] buffer;
		}
	}

	WaveLine::WaveLine() {
		playing = 0;
		pausing = 0;

		wavebuffer.size = 0;
		wavebuffer.wave = NULL;
	}
	WaveLine::WaveLine(AudioFile& Taudiofile) {
		playing = 0;
		pausing = 0;

		wavebuffer.size = 0;
		wavebuffer.wave = NULL;

		Load(Taudiofile);
	}
	WaveLine::WaveLine(const void* Tbuffer, unsigned int Tsize) {
		playing = 0;
		pausing = 0;

		wavebuffer.size = 0;
		wavebuffer.wave = NULL;

		Load(Tbuffer, Tsize);
	}

	bool WaveLine::Load(AudioFile& Taudiofile) {
		if (Taudiofile.buffer && Taudiofile.size) {
			wavebuffer.size = Taudiofile.size;
			wavebuffer.wave = new char[wavebuffer.size];
			memcpy(wavebuffer.wave, Taudiofile.buffer, wavebuffer.size);

			waveout.SetWave(wavebuffer);

			if (wavebuffer.wave) {
				waveout.SetWave(wavebuffer);
				waveout.Open();
				waveout.Prepare();
			}
		}

		return wavebuffer.wave;
	}
	bool WaveLine::Load(const void* Tbuffer, unsigned int Tsize) {
		if (Tbuffer && Tsize) {
			wavebuffer.size = Tsize;
			wavebuffer.wave = new char[Tsize];
			memcpy(wavebuffer.wave, Tbuffer, Tsize);

			if (wavebuffer.wave) {
				waveout.SetWave(wavebuffer);
				waveout.Open();
				waveout.Prepare();

				return 1;
			}
		}

		return 0;
	}

	bool WaveLine::Unload() {
		if (wavebuffer.wave) {
			waveout.Stop();
			waveout.Unprepare();
			waveout.Close();

			playing = 0;
			pausing = 0;

			delete[] wavebuffer.wave;
			wavebuffer.wave = NULL;
			wavebuffer.size = 0;

			return 1;
		}

		return 0;
	}

	void WaveLine::Play() {
		if (wavebuffer.wave) {
			waveout.Write();
			playing = 1;
			pausing = 0;
		}
	}

	void WaveLine::Pause() {
		if (wavebuffer.wave) {
			waveout.Pause();
			playing = 0;
			pausing = 1;
		}
	}
	void WaveLine::Resume() {
		if (wavebuffer.wave) {
			waveout.Resume();
			playing = 1;
			pausing = 0;
		}
	}

	void WaveLine::Stop() {
		if (wavebuffer.wave) {
			waveout.Stop();
			playing = 0;
			pausing = 0;
		}
	}

	int WaveLine::Position() {
		if (wavebuffer.wave) {
			return waveout.getPosition();
		}

		return 0;
	}

	bool WaveLine::loaded() {
		return (wavebuffer.wave != NULL);
	}
	bool WaveLine::isPlaying() {
		return playing;
	}
	bool WaveLine::isPaused() {
		return pausing;
	}

	WaveLine::~WaveLine() {
		Unload();
	}
}