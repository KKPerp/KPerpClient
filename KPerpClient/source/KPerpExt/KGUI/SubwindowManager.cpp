//อินครูต ลิส ก่อน
#include <KPerpCore/Area.inl>

#include <KPerpExt/KGUI/SubwindowManager.hpp>

#include <KPerpExt/KGUI/kgui.hpp>

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
#define _wndlw_ wng.getSubWindowList()[w]
#define _wndl_ wng.getSubWindowList()
#define __SW_X _wndlw_.getWidgetBound().x
#define __SW_Y _wndlw_.getWidgetBound().y
#define __SW_W _wndlw_.getWidgetBound().z
#define __SW_H _wndlw_.getWidgetBound().w
			for (unsigned int w = 0 ;w < wng.getSubWindowList().size();w++)
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



				const Vec4 closeButtonArea(__SW_X + __SW_W - headerHeight + headerMargin, __SW_Y + headerMargin, __SW_X + __SW_W - headerMargin, __SW_Y + headerHeight - headerMargin);

				renderer << Drawing::Rectangle(Vec3(__SW_X, __SW_Y, 0), Vec3(__SW_X + __SW_W, __SW_Y + __SW_H, 0), col, col, col, col, Vec2(0, 0), Vec2(0, 1), Vec2(1, 0), Vec2(1, 1), true);

				renderer << Drawing::Rectangle(Vec3(__SW_X, __SW_Y, 0), Vec3(__SW_X + __SW_W, __SW_Y + __SW_H, 0), col_prim, col_prim, col_prim, col_prim, Vec2(0, 0), Vec2(0, 1), Vec2(1, 0), Vec2(1, 1), false);

				renderer << Drawing::Rectangle(Vec3(__SW_X + headerMargin, __SW_Y + headerMargin, 0), Vec3(__SW_X + __SW_W - headerMargin, __SW_Y + headerHeight - headerMargin, 0), col_header_l, col_prim, col_header_l, col_prim, Vec2(0, 0), Vec2(0, 1), Vec2(1, 0), Vec2(1, 1), true);

				if (DRAW_OUTLINE_ALL)
				{
					//Window Header
					renderer << Drawing::Rectangle(Vec3(__SW_X + headerMargin, __SW_Y + headerMargin, 0), Vec3(__SW_X + __SW_W - headerMargin, __SW_Y + headerHeight - headerMargin, 0), Color::Blue, Color::Green, Color::Red, Color::Yellow, Vec2(0, 0), Vec2(0, 1), Vec2(1, 0), Vec2(1, 1), false);

					//Close Button Area
					renderer << Drawing::Rectangle(Vec3(closeButtonArea.x, closeButtonArea.y, 0), Vec3(closeButtonArea.z, closeButtonArea.w, 0), Color::Blue, Color::Green, Color::Red, Color::Yellow, Vec2(0, 0), Vec2(0, 1), Vec2(1, 0), Vec2(1, 1), false);

				}
				
				ModernText capp(wng.cfnt, Vec2(__SW_W-(headerMargin + 30), headerHeight-(headerMargin + 5)), Vec2(__SW_X + headerMargin + 5, __SW_Y + headerMargin), _wndlw_.getCaption(), Color(255, 255, 255, 255), 1.0f);
				capp.oneLine = true;
				renderer << capp;

				ModernText CloseText(wng.cfnt, Vec2(30, headerHeight-(headerMargin + 5)), Vec2(__SW_X + __SW_W - headerMargin - 15, __SW_Y + headerMargin), L"x", Color(0, 0, 0, 255), 1.0f);
				CloseText.oneLine = true;
				renderer << CloseText;
		
				

				if (_wndlw_.dragging == DRAG_CAP)
				{
					//_wndlw_.setWidgetBound(renderer.ViewMousePos().x, renderer.ViewMousePos().y, _wndlw_.getWidgetBound().z, _wndlw_.getWidgetBound().w);
					_wndlw_.setWidgetBound(renderer.ViewMousePos().x - wng.pos_old.x, renderer.ViewMousePos().y - wng.pos_old.y, _wndlw_.getWidgetBound().z, _wndlw_.getWidgetBound().w);
				}
				if (_wndlw_.dragging == DRAG_RIGHT)
				{
					_wndlw_.setWidgetBound(_wndlw_.getWidgetBound().x, _wndlw_.getWidgetBound().y, renderer.ViewMousePos().x - _wndlw_.getWidgetBound().x, _wndlw_.getWidgetBound().w);
				}

				if (mouse_area(renderer, Vec2(__SW_X + headerMargin, __SW_Y + headerMargin), Vec2(__SW_X + __SW_W - headerMargin, __SW_Y + headerHeight - headerMargin)) and renderer.mousePressed(Mouse::LeftButton))
				{
					if (renderer.mousePressed(Mouse::LeftButton))
					{
						wng.pos_old.x = renderer.ViewMousePos().x - _wndlw_.getWidgetBound().x;
						wng.pos_old.y = renderer.ViewMousePos().y - _wndlw_.getWidgetBound().y;
						_wndlw_.dragging = DRAG_CAP;
					}
					
				}

				if (renderer.mouseReleased(Mouse::LeftButton))
				{
					_wndlw_.dragging = false;
				}

				if (mouse_area(renderer, closeButtonArea) and renderer.mouseReleased(Mouse::LeftButton))
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
#undef __SW_X
#undef __SW_Y
#undef __SW_W
#undef __SW_H
			return renderer;
		}

	}
}