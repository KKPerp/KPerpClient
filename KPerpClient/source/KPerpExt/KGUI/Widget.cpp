#include <KPerpExt/KGUI/Widget.hpp>

namespace kp {
	namespace ext {
		Widget::Widget(Widget * parent)
		{
			this->parent = parent;
		}
		Widget::Widget(Vec4 bound)
		{
			wg_bound = bound;
		}

		Widget::Widget()
		{

		}

		Widget::~Widget()
		{

		}

		kp::Vec4 Widget::getWidgetBound() const
		{
			return wg_bound;
		}

		void Widget::setWidgetBound(Vec4 Bound)
		{
			wg_bound = Bound;
		}

		void Widget::setWidgetBound(Vec2 posx, Vec2 posy)
		{
			wg_bound = Vec4(posx.x, posx.y, posy.x, posy.y);
		}

		void Widget::setWidgetBound(float x1, float y1, float x2, float y2)
		{
			wg_bound = Vec4(x1,y1,x2,y2);
		}

	}
}