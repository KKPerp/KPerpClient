#ifndef _KPerpCore_KGui_Textbox_hpp_
#define _KPerpCore_KGui_Textbox_hpp_

#include "Element.hpp"

namespace kp {
	namespace KGui {
		class Textbox : public Instance {
		public:
			Textbox();
			Textbox(Element* Tparent, Rectangle<int> Trect, Text Ttext, Callback<Textbox> Tcallback = 0,
				Color Tbackcolor = Color(225, 225, 225), Color Tbordercolor = Color(173, 173, 173), int Tborderthickness = 1, const Sprite& Tsprite = {},
				Rectangle<int> Tpadding = { 0,0,0,0 }, Dock Ttldock = {}, Dock Ttrdock = {}, Dock Tbldock = {}, Dock Tbrdock = {},
				bool Tmultiline=0, std::string Tfilter="", int Tmaxlength=-1, char Tcoverchar=0, bool Treadonly=0, int Ttab=4, bool Twordwrap=0);

			~Textbox();

			Text getText();
			void setText(Text Ttext);
			void setTextString(std::string Tstring);

			Sprite getSprite();
			void setSprite(Sprite Tsprite);

			Color getBackgroundColor();
			void setBackgroundColor(Color Tcolor);

			int getBorderThickness();
			void setBorderThickness(int Tint);

			Color getBorderColor();
			void setBorderColor(Color Tcolor);

			bool getMultiline();
			void setMultiline(bool Tbool);
			std::string getFilter();
			void setFilter(std::string Tstring);
			int getMaxlength();
			void setMaxlength(int Tint);
			char getCoverchar();
			void setCoverchar(char Tchar);
			bool getReadonly();
			void setReadonly(bool Tbool);

			int getTabIndex();
			void setTabIndex(int Tint);
			bool getWordwrap();
			void setWordwrap(bool Tbool);

			bool getMouseEntered();

			void requestRedraw();

			void gainFocus();
			void killFocus();
			bool getFocus();

			int getPosition(Point<int> Tpoint);

			static void setFocusTo(Textbox* Ttextbox);
			static Textbox* getCurrentFocus();
			static void killCurrentFocus();

			static void requestRedrawAll();

		private:
			void create();
			void destroy();
			void step();
			void draw();

			void drawtext();

			Text text;
			Color bgcolor;
			int borderthickness;
			Color bordercolor;
			Sprite backgroundsprite;

			Rectangle<int> padding;

			bool pressed[3];

			Callback<Textbox> callback;

			bool mouseentered;

			bool requestredraw;

			bool focus;
			int position;

			static Textbox* currentfocus;

			static bool textboxmarker;
			static bool requestredrawall;

			static bool selecting;
			static int selectpos;

			bool multiline;
			std::string filter;
			int maxlength;
			char coverchar;
			bool readonly;
			
			int tab;
			bool wordwrap;

			int xseek;
			int yseek;

			friend class Instance;
			friend class Renderer;
			friend class Window;
		};
	}
}

#endif