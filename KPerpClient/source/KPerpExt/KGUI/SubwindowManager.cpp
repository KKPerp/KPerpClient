//อินครูต ลิส ก่อน
#include <KPerpCore/Area.inl>

#include <KPerpExt/KGUI/SubwindowManager.hpp>

#include <KPerpExt/KGUI/kgui.hpp>

#define _wndlw_ wng.getSubWindowList()[w]
#define _wndl_ wng.getSubWindowList()


#define DRAW_OUTLINE_ALL false

namespace kp {
	namespace ext {

		unsigned int SubWindowManager::AddSubWindow(Subwindow subwin)
		{
			windowList.insert(windowList.begin(),subwin);
			return windowList.size() - 1 ;
		}

		std::vector<Subwindow>& SubWindowManager::getSubWindowList()
		{
			return windowList;
		}


		Renderer & operator<<(Window & renderer, SubWindowManager& wng)
		{
			for (unsigned int w = 0;w < wng.getSubWindowList().size();w++)
			{ 
				/*if (wng->getSubWindowList()[w].exist) {
					return renderer;
				}*/
				const float headerMargin = 5;
				const float headerHeight = 30;

				renderer.UseSolidTexture();
				Color col(50, 50, 50, 255);
				Color col_prim(255, 100, 10, 255);
				Color col_header_l(0, 0, 0, 255);
				float posx = _wndlw_.getWidgetBound().x;
				float posy = _wndlw_.getWidgetBound().y;
				float posw = _wndlw_.getWidgetBound().z;
				float posh = _wndlw_.getWidgetBound().w;

				const Vec4 closeButtonArea(posx + posw - headerHeight + headerMargin, posy + headerMargin, posx + posw - headerMargin, posy + headerHeight - headerMargin);

				renderer << Drawing::Rectangle(Vec3(posx, posy, 0), Vec3(posx + posw, posy + posh, 0), col, col, col, col, Vec2(0, 0), Vec2(0, 1), Vec2(1, 0), Vec2(1, 1), true);

				renderer << Drawing::Rectangle(Vec3(posx, posy, 0), Vec3(posx + posw, posy + posh, 0), col_prim, col_prim, col_prim, col_prim, Vec2(0, 0), Vec2(0, 1), Vec2(1, 0), Vec2(1, 1), false);

				renderer << Drawing::Rectangle(Vec3(posx + headerMargin, posy + headerMargin, 0), Vec3(posx + posw - headerMargin, posy + headerHeight - headerMargin, 0), col_header_l, col_prim, col_header_l, col_prim, Vec2(0, 0), Vec2(0, 1), Vec2(1, 0), Vec2(1, 1), true);

				if (DRAW_OUTLINE_ALL)
				{
					//Window Header
					renderer << Drawing::Rectangle(Vec3(posx + headerMargin, posy + headerMargin, 0), Vec3(posx + posw - headerMargin, posy + headerHeight - headerMargin, 0), Color::Blue, Color::Green, Color::Red, Color::Yellow, Vec2(0, 0), Vec2(0, 1), Vec2(1, 0), Vec2(1, 1), false);

					//Close Button Area
					renderer << Drawing::Rectangle(Vec3(closeButtonArea.x, closeButtonArea.y, 0), Vec3(closeButtonArea.z, closeButtonArea.w, 0), Color::Blue, Color::Green, Color::Red, Color::Yellow, Vec2(0, 0), Vec2(0, 1), Vec2(1, 0), Vec2(1, 1), false);

				}
				
				ModernText capp(wng.cfnt, Vec2(posw-(headerMargin + 30), headerHeight-(headerMargin + 5)), Vec2(posx + headerMargin + 5, posy + headerMargin + 5), _wndlw_.getCaption(), Color(255, 255, 255, 255), 1.0f);
				capp.oneLine = true;
				renderer << capp;

				ModernText CloseText(wng.cfnt, Vec2(30, headerHeight-(headerMargin + 5)), Vec2(posx + posw - headerMargin - 15, posy + headerMargin + 5), L"x", Color(0, 0, 0, 255), 1.0f);
				CloseText.oneLine = true;
				renderer << CloseText;

				if (_____CLASS_____MOUSE_____PROCESS_____gg____________________________SUCC____________________________GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG::MOUZ_PRESD == 1) {
					std::cout << "PRESSED M8\n";
				}
				

				if (_wndlw_.dragging)
				{
					_wndlw_.setWidgetBound(renderer.ViewMousePos().x, renderer.ViewMousePos().y, _wndlw_.getWidgetBound().z, _wndlw_.getWidgetBound().w);
					_wndlw_.setWidgetBound(renderer.ViewMousePos().x - wng.pos_old.x, renderer.ViewMousePos().y - wng.pos_old.y, _wndlw_.getWidgetBound().z, _wndlw_.getWidgetBound().w);
				}

				if (mouse_area(renderer, Vec2(posx + headerMargin, posy + headerMargin), Vec2(posx + posw - headerMargin, posy + headerHeight - headerMargin)) and renderer.mousePressed(Mouse::LeftButton))
				{
					if (_____CLASS_____MOUSE_____PROCESS_____gg____________________________SUCC____________________________GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG::MOUZ_PRESD == 1)
					{
						wng.pos_old.x = renderer.ViewMousePos().x - _wndlw_.getWidgetBound().x;
						wng.pos_old.y = renderer.ViewMousePos().y - _wndlw_.getWidgetBound().y;
						_wndlw_.dragging = true;
					}
					
				}

				if (_____CLASS_____MOUSE_____PROCESS_____gg____________________________SUCC____________________________GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG::MOUZ_PRESD == 3)
				{
					std::cout << " RELEASED\n";
					_wndlw_.dragging = false;
				}

				if (mouse_area(renderer, closeButtonArea) and _____CLASS_____MOUSE_____PROCESS_____gg____________________________SUCC____________________________GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG::MOUZ_PRESD == 1)
				{
					////Actioning
					//gui->exist = false;

					//delete gui;

					/*gui = NULL;*/
					wng.getSubWindowList().erase(wng.getSubWindowList().begin() + w);
					//_wndlw_.setWidgetBound(0, 0, 0, 0);
					//_wndlw_.setCaption("");
				}
			}
			return renderer;
		}

	}
}