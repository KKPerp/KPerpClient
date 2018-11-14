#ifndef _KPerpCore_KPerpSound_Base_WaveOut_
#define _KPerpCore_KPerpSound_Base_WaveOut_

namespace kp {
	namespace Base {
		struct WaveBuffer {
			void* wave;
			unsigned int size;
		};

		struct WaveConfig {
			int samplerate;
			int bitspersample;
			int channels;
		};

		class WaveOut {
		public:
			WaveOut();
			WaveOut(WaveConfig Twavcfg);

			WaveOut(WaveBuffer Twavbuffer);

			WaveOut(WaveConfig Twavcfg, WaveBuffer Twavbuffer);

			void SetConfig(WaveConfig Twavcfg);

			void SetWave(WaveBuffer Twavbuffer);

			WaveOut(const WaveOut& Timl) = delete;
			WaveOut& operator=(const WaveOut& Timl) = delete;

			bool Open(unsigned int Tdevice = ((unsigned int)-1));

			bool Prepare();

			void Write();

			void Pause();

			void Resume();

			void Stop();

			int getPosition();

			void Close();

			bool Unprepare();

			~WaveOut();

		private:
			WaveBuffer wavbuffer;
			WaveConfig wavcfg;

			void* hwaveout;

			char waveformatex[18];
			char waveheader[32];

			bool prepared;
		};
	}
}

#endif