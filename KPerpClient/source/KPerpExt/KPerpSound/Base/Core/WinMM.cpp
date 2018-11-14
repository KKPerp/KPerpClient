#include <KPerpExt/KPerpSound/Base/Core/WinMM.hpp>
#include <windows.h>

HandleInst WinMM::winmminst = NULL;

WinMM::_sndPlaySoundW WinMM::sndPlaySoundW = NULL;
WinMM::_PlaySoundW WinMM::PlaySoundW = NULL;

WinMM::_waveOutGetNumDevs WinMM::waveOutGetNumDevs = NULL;
WinMM::_waveOutGetDevCapsW WinMM::waveOutGetDevCapsW = NULL;
WinMM::_waveOutGetVolume WinMM::waveOutGetVolume = NULL;
WinMM::_waveOutSetVolume WinMM::waveOutSetVolume = NULL;

WinMM::_waveOutGetErrorTextW WinMM::waveOutGetErrorTextW = NULL;

WinMM::_waveOutOpen WinMM::waveOutOpen = NULL;
WinMM::_waveOutClose WinMM::waveOutClose = NULL;

WinMM::_waveOutPrepareHeader WinMM::waveOutPrepareHeader = NULL;
WinMM::_waveOutUnprepareHeader WinMM::waveOutUnprepareHeader = NULL;

WinMM::_waveOutWrite WinMM::waveOutWrite = NULL;
WinMM::_waveOutPause WinMM::waveOutPause = NULL;

WinMM::_waveOutRestart WinMM::waveOutRestart = NULL;
WinMM::_waveOutReset WinMM::waveOutReset = NULL;

// waveOutGetPosition

WinMM::_waveOutGetPitch WinMM::waveOutGetPitch = NULL;
WinMM::_waveOutSetPitch WinMM::waveOutSetPitch = NULL;
WinMM::_waveOutGetPlaybackRate WinMM::waveOutGetPlaybackRate = NULL;
WinMM::_waveOutSetPlaybackRate WinMM::waveOutSetPlaybackRate = NULL;

WinMM::_waveOutGetID WinMM::waveOutGetID = NULL;

WinMM::_waveOutMessage WinMM::waveOutMessage = NULL;

WinMM::_waveInGetNumDevs WinMM::waveInGetNumDevs = NULL;
WinMM::_waveInGetDevCapsW WinMM::waveInGetDevCapsW = NULL;

//typedef unsigned int(__stdcall* _waveInGetVolume)(HandleWaveIn Thwavein, unsigned long* Tvolume);
//typedef unsigned int(__stdcall* _waveInSetVolume)(HandleWaveIn Thwavein, unsigned long Tvolume);

WinMM::_waveInGetErrorTextW WinMM::waveInGetErrorTextW = NULL;

WinMM::_waveInOpen WinMM::waveInOpen = NULL;
WinMM::_waveInClose WinMM::waveInClose = NULL;

WinMM::_waveInPrepareHeader WinMM::waveInPrepareHeader = NULL;
WinMM::_waveInUnprepareHeader WinMM::waveInUnprepareHeader = NULL;

WinMM::_waveInAddBuffer WinMM::waveInAddBuffer = NULL;
WinMM::_waveInStart WinMM::waveInStart = NULL;
WinMM::_waveInStop WinMM::waveInStop = NULL;

WinMM::_waveInReset WinMM::waveInReset = NULL;

// waveInGetPosition

WinMM::_waveInGetID WinMM::waveInGetID = NULL;

WinMM::_mciSendCommandW WinMM::mciSendCommandW = NULL;

WinMM::_mciSendStringA WinMM::mciSendStringA = NULL;
WinMM::_mciSendStringW WinMM::mciSendStringW = NULL;

WinMM::_mciGetDeviceIDA WinMM::mciGetDeviceIDA = NULL;
WinMM::_mciGetDeviceIDW WinMM::mciGetDeviceIDW = NULL;

WinMM::_mciGetdeviceIDFromElementIDA WinMM::mciGetdeviceIDFromElementIDA = NULL;
WinMM::_mciGetdeviceIDFromElementIDW WinMM::mciGetdeviceIDFromElementIDW = NULL;

WinMM::_mciGetErrorStringA WinMM::mciGetErrorStringA = NULL;
WinMM::_mciGetErrorStringW WinMM::mciGetErrorStringW = NULL;

bool WinMM::Load() {
	winmminst = LoadLibraryW(L"winmm.dll");
	if (!winmminst) {
		return 0;
	}

	sndPlaySoundW = (_sndPlaySoundW)GetProcAddress(winmminst, "sndPlaySoundW");
	PlaySoundW = (_PlaySoundW)GetProcAddress(winmminst, "PlaySoundW");

	waveOutGetNumDevs = (_waveOutGetNumDevs)GetProcAddress(winmminst, "waveOutGetNumDevs");
	waveOutGetDevCapsW = (_waveOutGetDevCapsW)GetProcAddress(winmminst, "waveOutGetDevCapsW");
	waveOutGetVolume = (_waveOutGetVolume)GetProcAddress(winmminst, "waveOutGetVolume");
	waveOutSetVolume = (_waveOutSetVolume)GetProcAddress(winmminst, "waveOutSetVolume");

	waveOutGetErrorTextW = (_waveOutGetErrorTextW)GetProcAddress(winmminst, "waveOutGetErrorTextW");

	waveOutOpen = (_waveOutOpen)GetProcAddress(winmminst, "waveOutOpen");
	waveOutClose = (_waveOutClose)GetProcAddress(winmminst, "waveOutClose");

	waveOutPrepareHeader = (_waveOutPrepareHeader)GetProcAddress(winmminst, "waveOutPrepareHeader");
	waveOutUnprepareHeader = (_waveOutUnprepareHeader)GetProcAddress(winmminst, "waveOutUnprepareHeader");

	waveOutWrite = (_waveOutWrite)GetProcAddress(winmminst, "waveOutWrite");
	waveOutPause = (_waveOutPause)GetProcAddress(winmminst, "waveOutPause");

	waveOutRestart = (_waveOutRestart)GetProcAddress(winmminst, "waveOutRestart");
	waveOutReset = (_waveOutReset)GetProcAddress(winmminst, "waveOutReset");

	// waveOutGetPosition

	waveOutGetPitch = (_waveOutGetPitch)GetProcAddress(winmminst, "waveOutGetPitch");
	waveOutSetPitch = (_waveOutSetPitch)GetProcAddress(winmminst, "waveOutSetPitch");
	waveOutGetPlaybackRate = (_waveOutGetPlaybackRate)GetProcAddress(winmminst, "waveOutGetPlaybackRate");
	waveOutSetPlaybackRate = (_waveOutSetPlaybackRate)GetProcAddress(winmminst, "waveOutSetPlaybackRate");

	waveOutGetID = (_waveOutGetID)GetProcAddress(winmminst, "waveOutGetID");

	waveOutMessage = (_waveOutMessage)GetProcAddress(winmminst, "waveOutMessage");

	waveInGetNumDevs = (_waveInGetNumDevs)GetProcAddress(winmminst, "waveInGetNumDevs");
	waveInGetDevCapsW = (_waveInGetDevCapsW)GetProcAddress(winmminst, "waveInGetDevCapsW");

	//typedef unsigned int(__stdcall* _waveInGetVolume)(HandleWaveIn Thwavein, unsigned long* Tvolume);
	//typedef unsigned int(__stdcall* _waveInSetVolume)(HandleWaveIn Thwavein, unsigned long Tvolume);

	waveInGetErrorTextW = (_waveInGetErrorTextW)GetProcAddress(winmminst, "waveInGetErrorTextW");

	waveInOpen = (_waveInOpen)GetProcAddress(winmminst, "waveInOpen");
	waveInClose = (_waveInClose)GetProcAddress(winmminst, "waveInClose");

	waveInPrepareHeader = (_waveInPrepareHeader)GetProcAddress(winmminst, "waveInPrepareHeader");
	waveInUnprepareHeader = (_waveInUnprepareHeader)GetProcAddress(winmminst, "waveInUnprepareHeader");

	waveInAddBuffer = (_waveInAddBuffer)GetProcAddress(winmminst, "waveInAddBuffer");
	waveInStart = (_waveInStart)GetProcAddress(winmminst, "waveInStart");
	waveInStop = (_waveInStop)GetProcAddress(winmminst, "waveInStop");

	waveInReset = (_waveInReset)GetProcAddress(winmminst, "waveInReset");

	// waveInGetPosition

	waveInGetID = (_waveInGetID)GetProcAddress(winmminst, "waveInGetID");

	mciSendCommandW = (_mciSendCommandW)GetProcAddress(winmminst, "mciSendCommandW");

	mciSendStringA = (_mciSendStringA)GetProcAddress(winmminst, "mciSendStringA");
	mciSendStringW = (_mciSendStringW)GetProcAddress(winmminst, "mciSendStringW");

	mciGetDeviceIDA = (_mciGetDeviceIDA)GetProcAddress(winmminst, "mciGetDeviceIDA");
	mciGetDeviceIDW = (_mciGetDeviceIDW)GetProcAddress(winmminst, "mciGetDeviceIDW");

	mciGetdeviceIDFromElementIDA = (_mciGetdeviceIDFromElementIDA)GetProcAddress(winmminst, "mciGetdeviceIDFromElementIDA");
	mciGetdeviceIDFromElementIDW = (_mciGetdeviceIDFromElementIDW)GetProcAddress(winmminst, "mciGetdeviceIDFromElementIDW");

	mciGetErrorStringA = (_mciGetErrorStringA)GetProcAddress(winmminst, "mciGetErrorStringA");
	mciGetErrorStringW = (_mciGetErrorStringW)GetProcAddress(winmminst, "mciGetErrorStringW");

	return (winmminst != NULL);
}

bool WinMM::Free() {
	bool _result = FreeLibrary(winmminst);
	winmminst = NULL;
	return _result;
}

bool WinMM::Loaded() {
	return winmminst != NULL;
}