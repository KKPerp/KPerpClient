#include <KPerpCore/Window.hpp>
#include <KPerpCore/Matrix.hpp>

namespace kp {
	bool mouse_area(Window & win, float mouse_x1, float mouse_y1, float mouse_x2, float mouse_y2) {

		return ((win.ViewMousePos().x > mouse_x1) && (win.ViewMousePos().y > mouse_y1) && (win.ViewMousePos().x < mouse_x2) && (win.ViewMousePos().y < mouse_y2));
	}

	bool mouse_area(Window & win, Vec2 pos1, Vec2 pos2) {

		return ((win.ViewMousePos().x > pos1.x) && (win.ViewMousePos().y > pos1.y) && (win.ViewMousePos().x < pos2.x) && (win.ViewMousePos().y < pos2.y));
	}

	bool mouse_area(Window & win, Vec4 pos) {

		return ((win.ViewMousePos().x > pos.x) && (win.ViewMousePos().y > pos.y) && (win.ViewMousePos().x < pos.z) && (win.ViewMousePos().y < pos.w));
	}
}