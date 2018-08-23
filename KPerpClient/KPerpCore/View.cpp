#include "View.hpp"

namespace kp {
	View::View() {
		view = { 0,0,0,0 };
		port = { 0,0,0,0 };

		zoom = Vec2(0, 0);
		angle = 0;
	}
	View::View(Rectangle<float> Trect, Rectangle<float> Tport) {
		view = Trect;
		port = Tport;

		zoom = Vec2(1, 1);
		angle = 0;
	}
	View::View(Rectangle<float> Trect, Rectangle<float> Tport, Vec2 Tzoom, float Tangle) {
		view = Trect;
		port = Tport;

		zoom = Tzoom;
		angle = Tangle;
	}
}