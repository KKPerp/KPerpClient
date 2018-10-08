#pragma once

#include <list>
#include <vector>
#include "Subwindow.hpp"
namespace kp {
	namespace ext {
		class SubWindowManager {
		private:
			std::vector<Subwindow> windowList;
			Vec2 pos_old;
			ModernFont cfnt = ModernFont("resources/fnt/plat.ttf", 20);
		public:
			unsigned int AddSubWindow(Subwindow subwin);
			std::vector<Subwindow>& getSubWindowList();

			friend Renderer & operator<<(Window & renderer, SubWindowManager & wng);
		};

		Renderer& operator<< (Window& renderer, SubWindowManager& wng);

	}
}
