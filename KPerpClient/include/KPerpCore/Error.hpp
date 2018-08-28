#ifndef __KPerpCore_Error_hpp_
#define __KPerpCore_Error_hpp_

namespace kp {
	enum class Error {
		NoError,
		KPerpEngineNotInitialized,
		InvalidWindowSize,
		InvalidSurfaceSize,
		WinClassRegisterFailed,
		WinClassRegisterFailedBecauseItsAlreadyExists,
		WindowCreationFailed,
		InvalidOpenGL,
		DIBSectionCreationFailed,
		EnterFullscreenFailed,
		EnterFullscreenFailedBecauseItsAlreadyFullScreen,
		LeaveFullscreenFailed
	};

	Error getLastError();
	Error setLastError(Error Terror);

	int getWindowLastError();
	int setWindowLastError(int Terror);
}

#endif