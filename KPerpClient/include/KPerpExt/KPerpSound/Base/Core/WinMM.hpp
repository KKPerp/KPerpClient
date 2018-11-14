#ifndef _KPerpCore_KPerpSound_Base_Core_WinMM_
#define _KPerpCore_KPerpSound_Base_Core_WinMM_

// WinMM API Loader/Wrapper

struct HWND__;

struct HINSTANCE__;
struct HWAVE__;
struct HWAVEIN__;
struct HWAVEOUT__;

typedef HWND__* HandleWindow;

typedef HINSTANCE__* HandleInst;
typedef HWAVE__* HandleWave;
typedef HWAVEIN__* HandleWaveIn;
typedef HWAVEOUT__* HandleWaveOut;

typedef struct wavehdr_tag WaveHeader;

enum WaveHeaderFlag : unsigned int {
	Done = 1U,
	Prepared = 2U,
	BeginLoop = 4U,
	EndLoop = 8U,
	Inqueue = 10U
};

typedef struct tagWAVEOUTCAPSW WaveOutCaps;

enum WaveCapsFlag : unsigned int {
	Pitch = 1U,
	PlaybackRate = 2U,
	Volume = 4U,
	LeftRightVolume = 8U,
	Sync = 10U,
	SampleAccurate = 20U
};

typedef struct tagWAVEINCAPSW WaveInCaps;

enum WaveFormat : unsigned int {
	Invalid = 0U,
	Mono11025Hz8Bit = 1U,
	Stereo11025Hz8Bit = 2U,
	Mono11025Hz16Bit = 4U,
	Stereo11025Hz16Bit = 8U,
	Mono22050Hz8Bit = 10U,
	Stereo22050Hz8Bit = 20U,
	Mono22050Hz16Bit = 40U,
	Stereo22050Hz16Bit = 80U,
	Mono44100Hz8Bit = 100U,
	Stereo44100Hz8Bit = 200U,
	Mono44100Hz16Bit = 400U,
	Stereo44100Hz16Bit = 800U,
	Mono48000Hz8Bit = 1000U,
	Stereo48000Hz8Bit = 2000U,
	Mono48000Hz16Bit = 4000U,
	Stereo48000Hz16Bit = 8000U,
	Mono96000Hz8Bit = 10000U,
	Stereo96000Hz8Bit = 20000U,
	Mono96000Hz16Bit = 40000U,
	Stereo96000Hz16Bit = 80000U,

	PCM = 1U
};

typedef struct waveformat_tag WaveFormatStruct;
typedef struct tWAVEFORMATEX WaveFormatStructExtend;

class WinMM {
public:
	enum Flags : unsigned int {
		Sync = 0U,
		Async = 1U,
		NoDefault = 2U,
		Memory = 4U,
		Loop = 8U,
		NoStop = 10U,

		NoWait = 8192L,
		Alias = 65536L,
		AliasID = 1114112L,
		Filename = 131072L,
		Resource = 262148L,

		Purge = 64L,
		Application = 128L,

		Sentry = 524288L,
		Ring = 1048576L,
		System = 2097152L
	};

	static bool Load();
	static bool Free();

	typedef int(__stdcall* _sndPlaySoundW)(const wchar_t* Ttext, unsigned int Tflags);
	static _sndPlaySoundW sndPlaySoundW;

	typedef int(__stdcall* _PlaySoundW)(const wchar_t* Ttext, HandleInst Thinst, Flags Tflags);
	static _PlaySoundW PlaySoundW;

	typedef unsigned int(__stdcall* _waveOutGetNumDevs)();
	static _waveOutGetNumDevs waveOutGetNumDevs;
	typedef unsigned int(__stdcall* _waveOutGetDevCapsW)(unsigned int Tdeviceid, WaveOutCaps* Twaveoutcaps, unsigned int Tsize);
	static _waveOutGetDevCapsW waveOutGetDevCapsW;
	typedef unsigned int(__stdcall* _waveOutGetVolume)(HandleWaveOut Thwaveout, unsigned long* Tvolume);
	static _waveOutGetVolume waveOutGetVolume;
	typedef unsigned int(__stdcall* _waveOutSetVolume)(HandleWaveOut Thwaveout, unsigned long Tvolume);
	static _waveOutSetVolume waveOutSetVolume;

	typedef unsigned int(__stdcall* _waveOutGetErrorTextW)(unsigned int Terror, wchar_t* Ttext, unsigned int Tsize);
	static _waveOutGetErrorTextW waveOutGetErrorTextW;

	typedef unsigned int(_stdcall* _waveOutOpen)(HandleWaveOut* Thwaveout, unsigned int Tdeviceid, WaveFormatStructExtend* Twaveformatex, unsigned long Tcallback, unsigned long Tinstance, unsigned long Topen);
	static _waveOutOpen waveOutOpen;
	typedef unsigned int(_stdcall* _waveOutClose)(HandleWaveOut Thwaveout);
	static _waveOutClose waveOutClose;

	typedef unsigned int(_stdcall* _waveOutPrepareHeader)(HandleWaveOut Thwaveout, WaveHeader* Twaveheader, unsigned int Tsize);
	static _waveOutPrepareHeader waveOutPrepareHeader;
	typedef unsigned int(_stdcall* _waveOutUnprepareHeader)(HandleWaveOut Thwaveout, WaveHeader* Twaveheader, unsigned int Tsize);
	static _waveOutUnprepareHeader waveOutUnprepareHeader;

	typedef unsigned int(_stdcall* _waveOutWrite)(HandleWaveOut Thwaveout, WaveHeader* Twaveheader, unsigned int Tsize);
	static _waveOutWrite waveOutWrite;
	typedef unsigned int(_stdcall* _waveOutPause)(HandleWaveOut Thwaveout);
	static _waveOutPause waveOutPause;

	typedef unsigned int(_stdcall* _waveOutRestart)(HandleWaveOut Thwaveout);
	static _waveOutRestart waveOutRestart;
	typedef unsigned int(_stdcall* _waveOutReset)(HandleWaveOut Thwaveout);
	static _waveOutReset waveOutReset;
	typedef unsigned int(_stdcall* _waveOutBreakLoop)(HandleWaveOut Thwaveout);
	static _waveOutBreakLoop waveOutBreakLoop;

	// waveOutGetPosition

	typedef unsigned int(_stdcall* _waveOutGetPitch)(HandleWaveOut Thwaveout, unsigned long* Tpitch);
	static _waveOutGetPitch waveOutGetPitch;
	typedef unsigned int(_stdcall* _waveOutSetPitch)(HandleWaveOut Thwaveout, unsigned long Tpitch);
	static _waveOutSetPitch waveOutSetPitch;
	typedef unsigned int(_stdcall* _waveOutGetPlaybackRate)(HandleWaveOut Thwaveout, unsigned long* Trate);
	static _waveOutGetPlaybackRate waveOutGetPlaybackRate;
	typedef unsigned int(_stdcall* _waveOutSetPlaybackRate)(HandleWaveOut Thwaveout, unsigned long Trate);
	static _waveOutSetPlaybackRate waveOutSetPlaybackRate;

	typedef unsigned int(_stdcall* _waveOutGetID)(HandleWaveOut Thwaveout, unsigned int* Tdeviceid);
	static _waveOutGetID waveOutGetID;

	typedef unsigned int(_stdcall* _waveOutMessage)(HandleWaveOut Thwaveout, unsigned int Tmessage, unsigned long Tulong1, unsigned long Tulong2);
	static _waveOutMessage waveOutMessage;

	typedef unsigned int(__stdcall* _waveInGetNumDevs)();
	static _waveInGetNumDevs waveInGetNumDevs;
	typedef unsigned int(__stdcall* _waveInGetDevCapsW)(unsigned int Tdeviceid, WaveInCaps* Twaveincaps, unsigned int Tsize);
	static _waveInGetDevCapsW waveInGetDevCapsW;

	//typedef unsigned int(__stdcall* _waveInGetVolume)(HandleWaveIn Thwavein, unsigned long* Tvolume);
	//typedef unsigned int(__stdcall* _waveInSetVolume)(HandleWaveIn Thwavein, unsigned long Tvolume);

	typedef unsigned int(__stdcall* _waveInGetErrorTextW)(unsigned int Terror, wchar_t* Ttext, unsigned int Tsize);
	static _waveInGetErrorTextW waveInGetErrorTextW;

	typedef unsigned int(_stdcall* _waveInOpen)(HandleWaveIn* Thwavein, unsigned int Tdeviceid, WaveFormatStructExtend* Twaveformatex, unsigned long Tcallback, unsigned long Tinstance, unsigned long Topen);
	static _waveInOpen waveInOpen;
	typedef unsigned int(_stdcall* _waveInClose)(HandleWaveIn Thwavein);
	static _waveInClose waveInClose;

	typedef unsigned int(_stdcall* _waveInPrepareHeader)(HandleWaveIn Thwavein, WaveHeader* Twaveheader, unsigned int Tsize);
	static _waveInPrepareHeader waveInPrepareHeader;
	typedef unsigned int(_stdcall* _waveInUnprepareHeader)(HandleWaveIn Thwavein, WaveHeader* Twaveheader, unsigned int Tsize);
	static _waveInUnprepareHeader waveInUnprepareHeader;

	typedef unsigned int(_stdcall* _waveInAddBuffer)(HandleWaveIn Thwavein, WaveHeader* Twaveheader, unsigned int Tsize);
	static _waveInAddBuffer waveInAddBuffer;
	typedef unsigned int(_stdcall* _waveInStart)(HandleWaveIn Thwavein);
	static _waveInStart waveInStart;
	typedef unsigned int(_stdcall* _waveInStop)(HandleWaveIn Thwavein);
	static _waveInStop waveInStop;

	typedef unsigned int(_stdcall* _waveInReset)(HandleWaveIn Thwavein);
	static _waveInReset waveInReset;

	// waveInGetPosition

	typedef unsigned int(_stdcall* _waveInGetID)(HandleWaveIn Thwavein, unsigned int* Tdeviceid);
	static _waveInGetID waveInGetID;

	typedef unsigned long(_stdcall* _mciSendCommandW)(unsigned int Tmcid, unsigned int Tmessage, unsigned long Tulong1, unsigned long Tulong2);
	static _mciSendCommandW mciSendCommandW;

	typedef unsigned long(_stdcall* _mciSendStringA)(const char* Tstring, char* Treturnstring, unsigned int Treturnlength, HandleWindow Thwndcallback);
	static _mciSendStringA mciSendStringA;
	typedef unsigned long(_stdcall* _mciSendStringW)(const wchar_t* Tstring, wchar_t* Treturnstring, unsigned int Treturnlength, HandleWindow Thwndcallback);
	static _mciSendStringW mciSendStringW;

	typedef unsigned long(_stdcall* _mciGetDeviceIDA)(const char* Tdevice);
	static _mciGetDeviceIDA mciGetDeviceIDA;
	typedef unsigned long(_stdcall* _mciGetDeviceIDW)(const wchar_t* Tdevice);
	static _mciGetDeviceIDW mciGetDeviceIDW;

	typedef unsigned long(_stdcall* _mciGetdeviceIDFromElementIDA)(unsigned long Telementid, const char* Tdevice);
	static _mciGetdeviceIDFromElementIDA mciGetdeviceIDFromElementIDA;
	typedef unsigned long(_stdcall* _mciGetdeviceIDFromElementIDW)(unsigned long Telementid, const wchar_t* Tdevice);
	static _mciGetdeviceIDFromElementIDW mciGetdeviceIDFromElementIDW;

	typedef int(_stdcall* _mciGetErrorStringA)(unsigned long Terror, char* Ttext, unsigned int Tsize);
	static _mciGetErrorStringA mciGetErrorStringA;
	typedef int(_stdcall* _mciGetErrorStringW)(unsigned long Terror, wchar_t* Ttext, unsigned int Tsize);
	static _mciGetErrorStringW mciGetErrorStringW;

	// mciSetYieldProc
	// mciGetCreatorTask
	// mciGetYieldProc

	static bool Loaded();

private:
	static HandleInst winmminst;
	static void* winmmfunc[100];

	//bool PlaySoundW(const wchar_t* Tstring, HandleInst Tmodule, )
};



#endif