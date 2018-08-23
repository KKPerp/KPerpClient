#ifndef _KPerpCore_View_hpp_
#define _KPerpCore_View_hpp_

#include "Renderer.hpp"
#include "Math.hpp"
#include "Graphic.hpp"
#include "Vector.hpp"

namespace kp {
	typedef Rectangle<float> RectView;

	// View : Viewport class
	class View {
	public:
		View();
		View(Rectangle<float> Trect, Rectangle<float> Tport);
		View(Rectangle<float> Trect, Rectangle<float> Tport, Vec2 Tzoom, float Tangle);

		Rectangle<float> view;
		Rectangle<float> port;

		Vec2 zoom;
		float angle;
	};
}

#endif
