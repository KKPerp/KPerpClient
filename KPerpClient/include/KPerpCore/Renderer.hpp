#ifndef _KPerpCore_Renderer_hpp_
#define _KPerpCore_Renderer_hpp_


#include <KPerpCore/Win32Handles.hpp>
#include <KPerpCore/Shape.hpp>
#include <KPerpCore/Keyboard.hpp>
#include <KPerpCore/Drawing.hpp>
#include <KPerpCore/Graphic.hpp>
#include <KPerpCore/Matrix.hpp>
#include <KPerpCore/View.hpp>
#include <KPerpCore/Font.hpp>
#include <KPerpCore/ModernFont.hpp>

//#ifdef KPERPEXT_KGUI_INCLUDED
//#include <KPerpExt/KGUI/kgui.hpp>
//#endif

//#ifdef _WIN32
//    #define APIENTRY __stdcall
//#endif

#include <KPerpCore/OpenGLTools.hpp>

#include <KPerpCore/SoftwareRenderEngine.hpp>

#include "glad/glad.h"

#ifdef APIENTRY
#undef APIENTRY
#endif

namespace kp {
	enum class WindowStyle {
		None = 0UL,
		Overlapped = 0UL,
		Popup = 1L << 31,
		Minimized = 1L << 30,
		Maximized = 1L << 25,
		Visible = 1L << 28,
		Disabled = 1L << 27,
		Caption = 0x00C00000L,
		Border = 1L << 23,
		SysMenu = 1L << 19,
		ThickFrame = 1L << 18,
		MinimizeBox = 1L << 17,
		MaximizeBox = 1L << 16,

		FullScreen = 1L << 5,

		OverlappedWindow = Overlapped | Caption | SysMenu | ThickFrame | MinimizeBox | MaximizeBox,
		PopupWindow = Popup | Border | SysMenu
	};

	WindowStyle operator|(const WindowStyle& Tlstyle, const WindowStyle& Trstyle);

	struct Event {
		enum class Type {
			None,
			Close,
			GetFocus,
			LoseFocus,

			KeyPressed,
			KeyReleased,
			GlobalKeyPressed,
			GlobalKeyReleased,

			MouseLeftPressed,
			MouseLeftReleased,
			MouseLeftDoubleClick,
			MouseRightPressed,
			MouseRightReleased,
			MouseRightDoubleClick,
			MouseMiddlePressed,
			MouseMiddleReleased,
			MouseMiddleDoubleClick,

			MouseWheelMoved,

			MouseMove,
			MouseMoveInside,
			MouseEnterClient,
			MouseLeaveClient,
			MouseEnterClientFast,
			MouseLeaveClientFast,

			WindowMoved,
			WindowMoving,
			WindowSizeChanged,
			WindowChangingSize,
			WindowNonMinimizedChange,
			WindowChanged,
			WindowRestored,
			WindowMinimized,
			WindowMaximized,
			//WindowMovingBorder,
			//WindowSizing,

			Construct,
			Destruct
		};

		enum WindowChange {
			Restored,
			minimized,
			Maximized
		};

		Type type;

		Point<long> mousepos;

		WindowChange windowchange;

		Point<int> windowsize;

		Key key;
		Mouse mouse;

		struct MouseKey {
			bool leftbutton;
			bool rightbutton;
			bool shift;
			bool control;
			bool middlebutton;
			bool x1;
			bool x2;
		} mousekeys;

		struct KeyInfo {
			short repeats;
			bool previous;
		} keyinfo;

		struct WheelInfo {
			Mouse type;
			short delta;
		} wheelinfo;

		struct WheelScrollInfo {
			Mouse type;
			short delta;
		} wheelscrollinfo;
	};

	class Input {
	public:
		Input();
		~Input();

		unsigned char keys[256];

		Point<long> mousepos;
		bool mouseleftbutton;
		bool mouserightbutton;
		bool mousemiddlebutton;
		bool mousewheelup;
		bool mousewheeldown;
	};

	enum class BlendFactor {
		Zero,
		One,
		SourceColor,
		OneMinusSourceColor,
		DestColor,
		OneMinusDestColor,
		SourceAlpha,
		OneMinusSourceAlpha,
		DestAlpha,
		OneMinusDestAlpha,
	};

	class Graphic;
	class Sprite;
	class Texture;
	class View;
	class Text;
	class ModernText;

	class Window;

	namespace KGui {
		class Instance;
		class Textbox;
	}

	class DesignSectionObjectPort;

	//class Shader;

	typedef struct DesignSectionData *DesignSectionHandle;

	// Renderer : A main class for render with software and OpenGL

	class Renderer {
	public:
		Renderer();

		Renderer(int Tw, int Th);
		Renderer(int Topengl, int Tw, int Th);

		virtual void Destroy();

		virtual void Update();

		virtual void makeCurrent();

		virtual int getOpenGL();

		virtual Event getEvent();
		virtual Event waitEvent();
		virtual int waitPullEvent(Event& Tevent);
		virtual int pullEvent(Event& Tevent);
		virtual int getEventQueueSize();
		virtual Event putEvent(Event Tevent);
		virtual Event popEvent();

		virtual bool getResizing();

		typedef void(*WindowChangeCallback)(Rectangle<long>, Rectangle<long>, Event::WindowChange);
		void setWindowChangeCallBack(WindowChangeCallback Twinchangecallback);

		virtual int keyPress(Key Tkey);
		virtual int keyPress(unsigned char Tkey);

		virtual int keyHold(Key Tkey);
		virtual int keyHold(unsigned char Tkey);

		virtual int keyPressed(Key Tkey);
		virtual int keyPressed(unsigned char Tkey);
		virtual int keyReleased(Key Tkey);
		virtual int keyReleased(unsigned char Tkey);

		virtual	int mousePress(Mouse Tmousebutton);
		virtual	int mousePressed(Mouse Tmousebutton);
		virtual	int mouseReleased(Mouse Tmousebutton);
		virtual	int mouseHold(Mouse Tmousebutton);

		virtual short MouseWheel();

		virtual Point<long> MousePos();
		virtual Point<long> ViewMousePos();

		virtual Point<long> WindowSize();
		virtual Point<long> ClientSize();

		virtual Rectangle<long> WindowRect();
		virtual Rectangle<long> ClientRect();

		virtual void EnableBlending(BlendFactor TSourceFac, BlendFactor TDestFac);
		virtual void DisableBlending();

		virtual void setTarget(Texture& Ttex);
		virtual void setTarget(const View& Tview);
		virtual void resetTarget();

		virtual void restoreView();
		virtual void updateView();
		virtual void updateViewPosition();
		virtual void useView(bool Tuse);

		bool isDestructing();

		virtual Matrix<float, 4, 4> GetMatrix();
		virtual Matrix<float, 4, 4> GetViewMatrix();
		virtual Matrix<float, 4, 4> GetTransformMatrix();
		virtual void UseShader(OpenGL::Shader& Tshader, unsigned int Tmatrixloc, unsigned int Tviewmatrixloc, unsigned int Ttransmatrixloc);
		virtual void UseDefaultShader();
		virtual OpenGL::Shader* getShader();
		virtual bool isShaderDefault();
		virtual void getShaderMatrixLocation(unsigned int* Tmatrixloc, unsigned int* Tviewmatrixloc, unsigned int* Ttransmatrixloc);
		virtual void getShaderMatrixLocation(unsigned int* Tloc);

		virtual Matrix<float, 4, 4> getViewMatrix();
		virtual void setViewMatrix(Matrix<float, 4, 4> Tmatrix);
		virtual void restoreViewMatrix();

		// Drawing

		virtual void Clear(Color Tcolor);

		virtual Renderer& operator<< (Drawing::Line Tline);
		virtual Renderer& operator<< (Drawing::Triangle Ttriangle);
		virtual Renderer& __stdcall operator<< (Drawing::Rectangle Trectangle);

		virtual Renderer& operator<< (Drawing::VertexArray& Tva);

		virtual void LoadIdentity();

		virtual void Combine(const Matrix<float, 4, 4>& Tmatrix);

		virtual void __stdcall UseSolidTexture();

		// Render Stream

		virtual Renderer& operator<< (Color Tcolor);
		virtual Renderer& operator<< (int Tint);

		virtual Renderer& operator<< (Drawing::VertexArray::Type Tptype);

		virtual void processInput();
		virtual void processMouseInput();
		virtual void processKeyInput();

		class _End {

		};

		virtual Renderer& operator<< (const Drawing::Vertex& Tvertex);
		virtual Renderer& operator<< (_End);

		virtual Renderer& operator<< (Graphic& Tgraphic);

		virtual Renderer& operator<< (const Sprite& Tsprite);

		virtual Renderer& operator<< (const Text& Ttext);

		virtual Renderer& operator<< (const ModernText& Ttext);

		// Kgui

		virtual Renderer& operator<< (KGui::Instance& Tinst);
		virtual Renderer& operator<< (KGui::Instance* Tinst);

		virtual Renderer& operator<< (DesignSectionHandle Tdsobjport);

//#ifdef KPERPEXT_KGUI_INCLUDED
//		virtual Renderer& operator<< (const ext::Subwindow& gui);
//#endif //KPERPEXT_KGUI_INCLUDED

		//Renderer& operator<< (Renderer& renderer, const ext::Subwindow& gui);

		~Renderer();
	protected:
		int opengl;

		HandleDeviceContext hdc;
		HandleDeviceContext chdc;

		HandleGLRenderContext hglrc;

		HandleWindow hwnd;

		unsigned int linevao;
		unsigned int linevbo;
		unsigned int lineebo;

		unsigned int trianglevao;
		unsigned int trianglevbo;
		unsigned int triangleebo;

		unsigned int rectvao;
		unsigned int rectvbo;
		unsigned int rectebo;

		unsigned int vao;
		unsigned int vbo;

		Rectangle<long> rect;
		Rectangle<long> clientrect;

		Rectangle<long> crect;

		long width;
		long height;

		Point<long> defsize;

		bool running;
		bool destructing;

		char bmpinfo[44];
		HandleBitmap hbmp;
		unsigned int* buffer;

		Input input;

		WindowStyle style;

		short mousewheeldelta;
		bool mouseinside;
		bool mouseinsidetemp;

		int minimized; // 2 = maximized
		int cminimized;
		bool resizing;

		bool fullscreened;

		Point<long> mousepos;
		Point<long> _mousepos;

		char pressed[256];

		void* prop[32];

		unsigned int tframebuffer;
		Texture* targettexture;

		int renderwidth;
		int renderheight;

		bool beginvertex;

		View* view;
		View* defview;

		bool useview;

		OpenGL::Shader* shader;
		OpenGL::Shader moderntext_shader;
		Matrix<float, 4, 4> matrix;
		Matrix<float, 4, 4> viewmatrix;
		Matrix<float, 4, 4> transmatrix;

		unsigned int matrixlocation;
		unsigned int viewmatrixlocation;
		unsigned int transmatrixlocation;

		unsigned int shadermatrixlocation;
		unsigned int shaderviewmatrixlocation;
		unsigned int shadertransmatrixlocation;

		unsigned int modernmatrixlocation;
		unsigned int modernviewmatrixlocation;
		unsigned int moderntransmatrixlocation;


		WindowChangeCallback winchangecallback;

		public:
		SoftwareRenderEngine renderer;
		protected:

		OpenGL::Shader* cshader;

		unsigned int white;
		unsigned int black;

		bool sizechanged;

		void* designsectionclass;
		void* designsection;

		void vao_init();

		void shader_init();

		void color_tex_init();

		void framebuffer_init();

		void view_init();

		bool create_software(int Tw, int Th);
		bool create_software_window(int Tx, int Ty, int Tw, int Th, const wchar_t* Ttext, WindowStyle Twinstyle);
		bool create_opengl(int Tx, int Ty, int Topengl, int Tw, int Th, const wchar_t* Ttext, WindowStyle Twinstyle);

		void toggletextboxmarkerblink();
		void drawcurrentfocus();
		void requestredrawcurrentfocus();
		void resetalltextboxfocus();
		void textboxtyping(char Tchar);
		void requestredrawcurrentfocusall();
		void scrolltextbox(int Tdelta);

		bool enterfullscreen(int Tw, int Th);
		bool leavefullscreen(WindowStyle Tstyle);

		void* getdesignsectionclass();
		void* getdesignsection();

		void* createdesignsectionclass(void* Tdsclass);
		void* createdesignsection(void* Tdshclass, std::string Tname, Rectangle<int> Trect);
		void* createdesignsection(std::string Tclass, std::string Tname, Rectangle<int> Trect);

		unsigned int processeventdesignsection(void* Tdshandle);
		
		void* beginpaint(DesignSectionHandle Tdshandle);
		bool endpaint(DesignSectionHandle Tdshandle);

		bool setunsignedint(DesignSectionHandle Tdshandle, unsigned int Tuint);
		unsigned int getunsignedint(DesignSectionHandle Tdshandle);

		bool setpos(DesignSectionHandle Tdshandle, Point<int> Tpoint);
		bool resize(DesignSectionHandle Tdshandle, Point<int> Tpoint);
		bool move(DesignSectionHandle Tdshandle, Point<int> Tpoint);
		bool addsize(DesignSectionHandle Tdshandle, Point<int> Tpoint);
		bool setrect(DesignSectionHandle Tdshandle, Rectangle<int> Trect);

		Rectangle<int> getrect(DesignSectionHandle Tdshandle);
		bool setsprite(DesignSectionHandle Tdshandle, Sprite Tsprite);
		Sprite getsprite(DesignSectionHandle Tdshandle);

		friend class Texture;
		friend long _stdcall WinProc(HandleWindow Thwnd, unsigned Tmsg, unsigned int Twparam, long Tlparam);
		friend int PushMessage(Window& Twindow, int Tmessage);

		friend class DesignSectionClass;
		friend class DesignSection;

		//friend class 

		friend class KGui::Textbox;
	};

	class _ShaderDeclare {

	};
	class _ShaderMultiply {

	};

	static const Renderer::_End End;
	static const _ShaderDeclare ShaderDeclare;
	static const _ShaderMultiply ShaderMultiply;

	Renderer* getCurrentRenderer();
}

#endif