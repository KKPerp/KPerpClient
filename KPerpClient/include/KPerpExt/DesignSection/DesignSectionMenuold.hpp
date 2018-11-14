#ifndef _KPerpCore_KPerpDesignSectionMenu_hpp_
#define _KPerpCore_KPerpDesignSectionMenu_hpp_

#include "../KPerpDesignSection.hpp"
#include "../../Graphic.hpp"

namespace kp {
	struct DesignSectionMenu {
		Text text;

		int sep;
	};

	typedef DesignSectionMenu DSMenu;
}

#endif