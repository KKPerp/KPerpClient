#ifndef _KPerpCore_KGui_Button_hpp_
#define _KPerpCore_KGui_Button_hpp_

#include "Element.hpp"

namespace kp {
	namespace KGui {
		class Button : public Instance {
		public:
			Button();
			Button(Element* Tparent, Rectangle<int> Trect, Text Ttext, Callback<Button> Tcallback = 0,
				Color Tbackcolor = Color(225, 225, 225), Color Tbordercolor = Color(173, 173, 173), int Tborderthickness = 1, const Sprite& Tsprite = {},
				Rectangle<int> Tpadding = {0,0,0,0}, Dock Ttldock = {}, Dock Ttrdock = {}, Dock Tbldock = {}, Dock Tbrdock = {});

			~Button();

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

			bool getMouseEntered();

		private:
			void create();
			void destroy();
			void step();
			void draw();

			Text text;
			Color bgcolor;
			int borderthickness;
			Color bordercolor;
			Sprite backgroundsprite;

			Rectangle<int> padding;

			bool pressed[3];

			Callback<Button> callback;

			bool mouseentered;

			friend class Instance;
			friend class Renderer;
			friend class Window;
		};
	}
}

#endif