#ifndef _KPerpCore_Renderer_hpp_
#define _KPerpCore_Renderer_hpp_

#include "Win32Handles.hpp"
#include "Shape.hpp"

#include "Keyboard.hpp"

#include "Drawing.hpp"

#include "Graphic.hpp"

#include "Matrix.hpp"

#include "View.hpp"

#include "Font.hpp"

#include "ModernFont.hpp"

//#ifdef _WIN32
//    #define APIENTRY __stdcall
//#endif

#include "OpenGLTools.hpp"

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

	enum class Event {
		None,
		Close,
		GetFocus,

		KeyDown,
		KeyUp,
		GlobalKeyDown,
		GlobalKeyUp,

		MouseWheelMoved,

		MouseMove,
		MouseEnterClient,
		MouseLeaveClient,

		WindowMoved,
		WindowMoving,
		WindowSizeChanged,
		WindowChangingSize,
		WindowNonMinimizedChange,
		WindowChanged,
		WindowRestored,
		WindowMinimized,
		WindowMaximized
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
	//class Shader;

	// Renderer : A main class for render with software and OpenGL

	class Renderer {
	public:
		Renderer();

		Renderer(int Tw, int Th);
		Renderer(int Topengl, int Tw, int Th);

		virtual void Destroy();

		virtual void Update();

		virtual void makeCurrent();

		virtual Event getEvent();
		virtual Event waitEvent();
		virtual Event putEvent(Event Tevent);
		virtual Event popEvent();

		virtual int keyPressed(Key Tkey);
		virtual int keyPressed(unsigned char Tkey);

		virtual	int mousePressed(Mouse Tmousebutton);
		virtual short MouseWheel();

		virtual Point<long> MousePos();

		virtual Point<long> WindowSize();
		virtual Point<long> ClientSize();

		virtual void EnableBlending(BlendFactor TSourceFac, BlendFactor TDestFac);
		virtual void DisableBlending();

		virtual void setTarget(Texture& Ttex);
		virtual void setTarget(const View& Tview);
		virtual void resetTarget();

		virtual void restoreView();
		virtual void updateView();
		virtual void updateViewPosition();
		virtual void useView(bool Tuse);

		virtual Matrix<float, 4, 4> GetMatrix();
		virtual Matrix<float, 4, 4> GetViewMatrix();
		virtual Matrix<float, 4, 4> GetTransformMatrix();
		virtual void UseShader(OpenGL::Shader& Tshader, unsigned int Tmatrixloc, unsigned int Tviewmatrixloc, unsigned int Ttransmatrixloc);

		// Drawing

		virtual void Clear(Color Tcolor);

		virtual Renderer& operator<< (Drawing::Line Tline);
		virtual Renderer& operator<< (Drawing::Triangle Ttriangle);
		virtual Renderer& operator<< (Drawing::Rectangle Trectangle);

		virtual Renderer& operator<< (Drawing::VertexArray& Tva);

		virtual void LoadIdentity();

		virtual void Combine(const Matrix<float,4,4>& Tmatrix);

		virtual void UseSolidTexture();

		// Render Stream

		virtual Renderer& operator<< (Color Tcolor);

		virtual Renderer& operator<< (Drawing::VertexArray::Type Tptype);

		class _End {

		};

		virtual Renderer& operator<< (const Drawing::Vertex& Tvertex);
		virtual Renderer& operator<< (_End);

		virtual Renderer& operator<< (Graphic& Tgraphic);

		virtual Renderer& operator<< (const Sprite& Tsprite);

		virtual Renderer& operator<< (const Text& Ttext);

		virtual Renderer& operator<< (const ModernText& Ttext);

		~Renderer();
	protected:
		int opengl;

		HandleDeviceContext hdc;
		HandleDeviceContext chdc;

		HandleGLRenderContext hglrc;

		HandleWindow hwnd;

		Rectangle<long> rect;
		Rectangle<long> clientrect;

		long width;
		long height;

		Point<long> defsize;

		bool running;

		char bmpinfo[44];
		HandleBitmap hbmp;
		unsigned int* buffer;

		Input input;

		WindowStyle style;

		short mousewheeldelta;
		bool mouseinside;
		bool mouseinsidetemp;

		int minimized; // 2 = maximized
		bool resizing;

		Point<long> mousepos;
		Point<long> _mousepos;

		void* prop[32];

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

		unsigned int tframebuffer;
		Texture* targettexture;

		int renderwidth;
		int renderheight;

		bool beginvertex;

		View* view;
		View* defview;

		bool useview;

		OpenGL::Shader shader;
		OpenGL::Shader moderntext_shader;
		Matrix<float, 4, 4> matrix;
		Matrix<float, 4, 4> viewmatrix;
		Matrix<float, 4, 4> transmatrix;

		unsigned int matrixlocation;
		unsigned int viewmatrixlocation;
		unsigned int transmatrixlocation;

		unsigned int modernmatrixlocation;
		unsigned int modernviewmatrixlocation;
		unsigned int moderntransmatrixlocation;

		unsigned int shadermatrixlocation;
		unsigned int shaderviewmatrixlocation;
		unsigned int shadertransmatrixlocation;

		OpenGL::Shader* cshader;

		unsigned int white;
		unsigned int black;

		void vao_init();

		void shader_init();

		void color_tex_init();

		void framebuffer_init();

		void view_init();

		bool create_software(int Tw, int Th);
		bool create_software_window(int Tx, int Ty, int Tw, int Th, const char* Ttext, WindowStyle Twinstyle);
		bool create_opengl(int Tx, int Ty, int Topengl, int Tw, int Th, const char* Ttext, WindowStyle Twinstyle);

		bool enterfullscreen(int Tw, int Th);
		bool leavefullscreen(WindowStyle Tstyle);
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