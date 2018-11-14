#include <KPerpExt/KPerpSound/Base/WaveOut.hpp>

#include <windows.h>
#include <KPerpExt/KPerpSound/Base/Core/WinMM.hpp>

namespace kp {
	namespace Base {
		WaveOut::WaveOut() {
			((WAVEFORMATEX*)&waveformatex)->nSamplesPerSec = 44100;
			((WAVEFORMATEX*)&waveformatex)->wBitsPerSample = 16;
			((WAVEFORMATEX*)&waveformatex)->nChannels = 2;

			((WAVEFORMATEX*)&waveformatex)->cbSize = 0;
			((WAVEFORMATEX*)&waveformatex)->wFormatTag = WAVE_FORMAT_PCM;
			((WAVEFORMATEX*)&waveformatex)->nBlockAlign = (((WAVEFORMATEX*)&waveformatex)->wBitsPerSample >> 3) * ((WAVEFORMATEX*)&waveformatex)->nChannels;
			((WAVEFORMATEX*)&waveformatex)->nAvgBytesPerSec = ((WAVEFORMATEX*)&waveformatex)->nBlockAlign * ((WAVEFORMATEX*)&waveformatex)->nSamplesPerSec;

			wavbuffer = { NULL,0 };

			prepared = 0;
			hwaveout = NULL;
		}
		WaveOut::WaveOut(WaveConfig Twavcfg) {
			wavbuffer = { NULL,0 };
			SetConfig(Twavcfg);

			prepared = 0;
			hwaveout = NULL;
		}

		WaveOut::WaveOut(WaveBuffer Twavbuffer) {
			((WAVEFORMATEX*)&waveformatex)->nSamplesPerSec = 44100;
			((WAVEFORMATEX*)&waveformatex)->wBitsPerSample = 16;
			((WAVEFORMATEX*)&waveformatex)->nChannels = 2;

			((WAVEFORMATEX*)&waveformatex)->cbSize = 0;
			((WAVEFORMATEX*)&waveformatex)->wFormatTag = WAVE_FORMAT_PCM;
			((WAVEFORMATEX*)&waveformatex)->nBlockAlign = (((WAVEFORMATEX*)&waveformatex)->wBitsPerSample >> 3) * ((WAVEFORMATEX*)&waveformatex)->nChannels;
			((WAVEFORMATEX*)&waveformatex)->nAvgBytesPerSec = ((WAVEFORMATEX*)&waveformatex)->nBlockAlign * ((WAVEFORMATEX*)&waveformatex)->nSamplesPerSec;

			SetWave(Twavbuffer);

			prepared = 0;
			hwaveout = NULL;
		}

		WaveOut::WaveOut(WaveConfig Twavcfg, WaveBuffer Twavbuffer) {
			SetConfig(Twavcfg);
			SetWave(Twavbuffer);

			prepared = 0;
			hwaveout = NULL;
		}

		void WaveOut::SetConfig(WaveConfig Twavcfg) {
			((WAVEFORMATEX*)&waveformatex)->nSamplesPerSec = Twavcfg.samplerate;
			((WAVEFORMATEX*)&waveformatex)->wBitsPerSample = Twavcfg.bitspersample;
			((WAVEFORMATEX*)&waveformatex)->nChannels = Twavcfg.channels;

			((WAVEFORMATEX*)&waveformatex)->cbSize = 0;
			((WAVEFORMATEX*)&waveformatex)->wFormatTag = WAVE_FORMAT_PCM;
			((WAVEFORMATEX*)&waveformatex)->nBlockAlign = (((WAVEFORMATEX*)&waveformatex)->wBitsPerSample >> 3) * ((WAVEFORMATEX*)&waveformatex)->nChannels;
			((WAVEFORMATEX*)&waveformatex)->nAvgBytesPerSec = ((WAVEFORMATEX*)&waveformatex)->nBlockAlign * ((WAVEFORMATEX*)&waveformatex)->nSamplesPerSec;
		}

		void WaveOut::SetWave(WaveBuffer Twavbuffer) {
			wavbuffer = Twavbuffer;
		}

		bool WaveOut::Open(unsigned int Tdevice) {
			if (!hwaveout) {
				if (WinMM::waveOutOpen((HWAVEOUT*)&hwaveout, Tdevice, (WAVEFORMATEX*)&waveformatex, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR) {
					return 0;
				}
			}
		}

		bool WaveOut::Prepare() {
			if (!prepared) {
				ZeroMemory(&waveheader, sizeof(WAVEHDR));
				((WAVEHDR*)&waveheader)->dwBufferLength = wavbuffer.size;
				((WAVEHDR*)&waveheader)->lpData = (char*)wavbuffer.wave;

				//unsigned int lol = WinMM::waveOutSetPitch(Thwaveout, 0x00020000);

				prepared = (WinMM::waveOutPrepareHeader((HWAVEOUT)hwaveout, (WAVEHDR*)&waveheader, sizeof(WAVEHDR)) == MMSYSERR_NOERROR);
				return prepared;

			}
		}

		void WaveOut::Write() {
			if (prepared && hwaveout) {
				WinMM::waveOutWrite((HWAVEOUT)hwaveout, (WAVEHDR*)&waveheader, sizeof(WAVEHDR));
			}
		}

		void WaveOut::Pause() {
			if (prepared && hwaveout) {
				WinMM::waveOutPause((HWAVEOUT)hwaveout);
			}
		}

		void WaveOut::Resume() {
			if (prepared && hwaveout) {
				WinMM::waveOutRestart((HWAVEOUT)hwaveout);
			}
		}

		void WaveOut::Stop() {
			if (prepared && hwaveout) {
				WinMM::waveOutReset((HWAVEOUT)hwaveout);
			}
		}

		int WaveOut::getPosition() {
			if (prepared && hwaveout) {
				//WinMM::waveOutGetPosition((HWAVEOUT)hwaveout);
				return 0;
			}
		}

		void WaveOut::Close() {
			if (hwaveout) {
				WinMM::waveOutClose((HWAVEOUT)hwaveout);
				hwaveout = NULL;
			}
		}

		bool WaveOut::Unprepare() {
			if (prepared && hwaveout) {
				int _error = (WinMM::waveOutUnprepareHeader((HWAVEOUT)hwaveout, (WAVEHDR*)&waveheader, sizeof(WAVEHDR)));
				if (_error == MMSYSERR_NOERROR) {
					prepared = 0;
					return 1;
				}
				else {
					return 0;
				}
			}
		}

		WaveOut::~WaveOut() {
			Unprepare();
		}
	}
}