#ifndef _KPerpCore_Win32Handles_hpp_
#define _KPerpCore_Win32Handles_hpp_

// We trying to avoid including <window.h> on any KPerp Headers

// Window handles are end with "__"
struct HWND__;
struct HHOOK__;
struct HEVENT__;
struct HGDIOBJ__;
struct HACCEL__;
struct HBITMAP__;
struct HBRUSH__;
struct HCOLORSPACE__;
struct HDC__;
struct HGLRC__;
struct HDESK__;
struct HENHMETANEWFILE__;
struct HFONT__;
struct HICON__;
struct HMENU__;
struct HPALETTE__;
struct HPEN__;
struct HWINEVENTHOOK__;
struct HMONITOR__;
struct HUMPD__;
typedef HICON__* HCURSOR; //not mac

namespace kp {
	typedef HWND__* HandleWindow;
	typedef HBITMAP__* HandleBitmap;
	typedef HDC__* HandleDeviceContext;
	typedef HGLRC__* HandleGLRenderContext;
	typedef HICON__* HandleIcon;
}

#endif