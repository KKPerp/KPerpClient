#ifndef __KPerpExt_KGUI_button_hpp_
#define __KPerpExt_KGUI_button_hpp_

#include <KPerpExt/KGUI/Widget.hpp>
namespace kp {
	namespace ext {
		class Button : public Widget
		{
		public:
			Button();
			Button(Widget * parent, std::string buttonLabel);

			Button(Vec4 Bound, std::string buttonLabel);
			Button(Vec4 Bound, std::string buttonLabel, bool enabled);
			Button(Vec4 Bound, std::string buttonLabel, bool enabled, std::string buttonTip);
			Button(Vec4 Bound, std::string buttonLabel, bool enabled, const char * buttonTip);
		private:
			Vec4 bound;
			std::string label;
			std::string tip;
			bool enable = true;
		};
	}
}

#endif