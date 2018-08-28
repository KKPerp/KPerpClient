#ifndef __KPerpExt_KGUI_widget_hpp_
#define __KPerpExt_KGUI_widget_hpp_

#include "..\..\KPerpCore\Matrix.hpp"

namespace kp {
	namespace ext {


		class kgui_widget
		{
		public:
			kgui_widget(Vec2 position, Vec2 bound);
			~kgui_widget();
		private:
			Vec2 position;
			Vec2 size;
			bool visible;
		};
	}
}

#endif
