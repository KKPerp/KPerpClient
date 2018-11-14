#include <KPerpExt/KGUI/Button.hpp>

namespace kp {
	namespace ext {
		Button::Button(Widget * parent, std::string buttonLabel) : Widget(parent)
		{

		}
		Button::Button(Vec4 Bound, std::string buttonLabel) : Widget(Bound)
		{
			bound = Bound;
			label = buttonLabel;
		}

		Button::Button(Vec4 Bound, std::string buttonLabel, bool enabled) : Widget(Bound)
		{
			bound = Bound;
			label = buttonLabel;
			enable = enabled;
		}

		Button::Button(Vec4 Bound, std::string buttonLabel, bool enabled, std::string buttonTip) : Widget(Bound)
		{
			bound = Bound;
			label = buttonLabel;
			tip = buttonTip;
		}

		Button::Button(Vec4 Bound, std::string buttonLabel, bool enabled, const char * buttonTip) : Widget(Bound)
		{
			bound = Bound;
			label = buttonLabel;
			tip = buttonTip;
		}

		Button::Button()
		{

		}

	}
}