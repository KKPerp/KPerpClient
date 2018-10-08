#ifndef _KPerpCore_Window_hpp_
#define _KPerpCore_Window_hpp_

#include <KPerpCore/Win32Handles.hpp>
#include <KPerpCore/Renderer.hpp>

namespace kp {

	class Window : public Renderer {
	public:
		Window();

		Window(int Tx, int Ty, int Tw, int Th, const char* Ttext, WindowStyle Tstyle);
		Window(int Topengl, int Tx, int Ty, int Tw, int Th, const char* Ttext, WindowStyle Tstyle);
		Window(int Tw, int Th, const char* Ttext, WindowStyle Tstyle);
		Window(int Topengl, int Tw, int Th, const char* Ttext, WindowStyle Tstyle);

		void Destroy();
		bool isActive();

		void makeCurrent();

		Event getEvent();
		Event waitEvent();
		Event putEvent(Event Tevent);
		Event popEvent();

		int keyPressed(Key Tkey);
		int keyPressed(unsigned char Tkey);

		int mousePressed(Mouse Tmousebutton);
		short MouseWheel();

		Point<long> MousePos();
		Point<long> ViewMousePos();
		Point<float> MousePosFloat();
		Point<float> ViewMousePosFloat();

		Point<long> WindowSize();
		Point<long> ClientSize();

		void EnableBlending(BlendFactor TSourceFac, BlendFactor TDestFac);
		void DisableBlending();

		bool EnterFullscreen(bool Tscreen);
		bool ExitFullScreen(WindowStyle Tstyle);

		void Update();
	private:
		char msg[28];
		char mousePress = 0;
		void* events;
	};
}

#endif