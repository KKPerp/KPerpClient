#ifndef _KPerpCore_Window_hpp_
#define _KPerpCore_Window_hpp_

#include "Win32Handles.hpp"
#include "Renderer.hpp"

namespace kp {
	namespace KGui {
		class Element;
	}

	class Window : public Renderer {
	public:
		Window();

		Window(int Tx, int Ty, int Tw, int Th, const char* Ttext, WindowStyle Tstyle);
		Window(int Topengl, int Tx, int Ty, int Tw, int Th, const char* Ttext, WindowStyle Tstyle);
		Window(int Tw, int Th, const char* Ttext, WindowStyle Tstyle);
		Window(int Topengl, int Tw, int Th, const char* Ttext, WindowStyle Tstyle);
		Window(int Tx, int Ty, int Tw, int Th, const wchar_t* Ttext, WindowStyle Tstyle);
		Window(int Topengl, int Tx, int Ty, int Tw, int Th, const wchar_t* Ttext, WindowStyle Tstyle);
		Window(int Tw, int Th, const wchar_t* Ttext, WindowStyle Tstyle);
		Window(int Topengl, int Tw, int Th, const wchar_t* Ttext, WindowStyle Tstyle);

		void Destroy();
		bool isActive();

		void makeCurrent();

		Event getEvent();
		Event waitEvent();
		int waitPullEvent(Event& Tevent);
		int pullEvent(Event& Tevent);
		int getEventQueueSize();
		Event putEvent(Event Tevent);
		Event popEvent();

		virtual int keyPress(Key Tkey);
		virtual int keyPress(unsigned char Tkey);

		virtual int keyPressLocal(Key Tkey);
		virtual int keyPressLocal(unsigned char Tkey);

		virtual int keyHold(Key Tkey);
		virtual int keyHold(unsigned char Tkey);

		virtual int keyPressed(Key Tkey);
		virtual int keyPressed(unsigned char Tkey);
		virtual int keyReleased(Key Tkey);
		virtual int keyReleased(unsigned char Tkey);

		virtual	int mousePress(Mouse Tmousebutton);
		virtual	int mousePressLocal(Mouse Tmousebutton);
		virtual	int mousePressed(Mouse Tmousebutton);
		virtual	int mouseReleased(Mouse Tmousebutton);
		virtual	int mouseHold(Mouse Tmousebutton);
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

		WindowStyle getStyle(WindowStyle Tstyle);
		bool isStyle(WindowStyle Tstyle);

		bool getMinimized();
		bool getMaximized();

		void processInput();
		void processMouseInput();
		void processKeyInput();
		void processInputGlobal();
		void processMouseInputGlobal();
		void processKeyInputGlobal();

		void Update();

		friend Window& operator<=(Window& Twindow, KGui::Element* Telement);

		void ProcessWidget();
		void DrawAllWidgets();
		void DrawAllWidgetSurfaces();

		~Window();
	private:

		char msg[28];

		void* events;

		// KGui
		void* elementmanager;
	};
}

#endif