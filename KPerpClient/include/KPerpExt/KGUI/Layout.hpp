#ifndef __KPerpExt_KGUI_layout_hpp_
#define __KPerpExt_KGUI_layout_hpp_

#include "..\..\KPerpCore\Matrix.hpp"

namespace kp {
	namespace ext {


		class Layout
		{
		public:
			Layout(Vec4 bound);

			float getWidth() { return l_bound.x; };
			float getHeight() { return l_bound.y; };
		private:
			Vec4 l_bound;
		};
	}
}

#endif
