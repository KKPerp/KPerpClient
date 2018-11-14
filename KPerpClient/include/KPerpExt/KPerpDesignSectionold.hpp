#ifndef _KPerpCore_KPerpDesignSection_hpp_
#define _KPerpCore_KPerpDesignSection_hpp_

#include "KPerpDesignObject.hpp"

namespace kp {
	class DesignSectionData;

	class DesignSection {
	public:
		DesignSection();
		~DesignSection();

		DSPort Create(DesignSectionObjectStruct Tdsobjstruct);
		std::string GetInfo();
		
	private:
		void init();
		void destroy();

		DesignSectionData* data;
	};
}

#endif