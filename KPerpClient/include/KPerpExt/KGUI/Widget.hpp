#ifndef __KPerpExt_KGUI_widget_hpp_
#define __KPerpExt_KGUI_widget_hpp_

#include <KPerpCore/Matrix.hpp>
#include <KPerpExt/KGUI/Layout.hpp>

namespace kp {
	namespace ext {


		class Widget
		{
		public:
			Widget();
			Widget(Widget * parent);
			Widget(Vec4 bound);
			~Widget();


			virtual Vec4 getWidgetBound() const; 
			virtual void setWidgetBound(Vec4 Bound);
			virtual void setWidgetBound(Vec2 posx, Vec2 posy);
			virtual void setWidgetBound(float x1, float y1, float x2, float y2);
			//virtual void addWidget(Widget * widget);
		protected:
			Widget * parent;
			Vec4 wg_bound;
			Layout* wg_layout;
		};
	}
}

#endif
