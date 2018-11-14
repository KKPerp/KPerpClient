#ifndef __KPerpExt_KGUI_subwindow_hpp_
#define __KPerpExt_KGUI_subwindow_hpp_

#include <KPerpExt/KGUI/Widget.hpp>
#include <string>

#include <KPerpCore/Window.hpp>
namespace kp {
	namespace ext {
		enum subwin_drag_mode {
			DRAG_NONE,
			DRAG_LEFT,
			DRAG_RIGHT,
			DRAG_TOP,
			DRAG_BOTTOM,
			DRAG_LT,
			DRAG_RT,
			DRAG_LB,
			DRAG_RB,
			DRAG_CAP
		};
		class Subwindow : public Widget
		{
		public:
			Subwindow();
			Subwindow(Vec4 Bound, std::wstring cap);
			Subwindow(Vec4 Bound, const wchar_t * cap);
			~Subwindow();
			virtual void setCaption(std::wstring text);
			virtual void setCaption(const wchar_t * text);

			virtual void setResizable(bool resizable);

			virtual void setCanMinimize(bool minimize);
			virtual void setCanMaximize(bool maximize);
			virtual void setCanClose(bool closable);

			std::wstring getCaption() const;
			subwin_drag_mode dragging = DRAG_NONE;
		private:
			std::wstring caption;
			bool exist;
			bool include_minimize = false;
			bool include_maximize = false;
			bool include_close = false;

			bool is_resizable = true;
			
			//friend Renderer & operator<<(Window & renderer, Subwindow* & gui);
		};

		
	}
}

#endif