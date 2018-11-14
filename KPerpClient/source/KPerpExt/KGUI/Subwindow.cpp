#include <KPerpExt/KGUI/Subwindow.hpp>
#include <KPerpCore/ModernFont.hpp>
#include <string>


namespace kp {
	namespace ext {
		Subwindow::Subwindow()
		{

		}
		Subwindow::Subwindow(Vec4 Bound, std::wstring cap) : Widget(Bound)
		{
			wg_bound = Bound;
			caption = cap;
			exist = true;
		}
		Subwindow::Subwindow(Vec4 Bound, const wchar_t * cap) : Widget(Bound)
		{
			wg_bound = Bound;
			caption = cap;
			exist = true;
		}
		Subwindow::~Subwindow()
		{

		}
		void Subwindow::setCaption(std::wstring text)
		{
			caption = text;
		}
		void Subwindow::setCaption(const wchar_t * text)
		{
			caption = text;
		}
		void Subwindow::setResizable(bool resizable)
		{
			is_resizable = resizable;
		}
		void Subwindow::setCanMinimize(bool minimize)
		{
			include_minimize = minimize;
		}
		void Subwindow::setCanMaximize(bool maximize)
		{
			include_minimize = maximize;
		}
		void Subwindow::setCanClose(bool closable)
		{
			include_close = closable;
		}
		std::wstring Subwindow::getCaption() const
		{
			return caption;
		}

	}
}
