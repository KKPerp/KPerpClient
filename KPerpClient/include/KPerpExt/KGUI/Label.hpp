#ifndef _KPerpCore_KGui_Label_hpp_
#define _KPerpCore_KGui_Label_hpp_

#include "Element.hpp"

namespace kp {
	namespace KGui {
		class Label : public Instance {
		public:
			Label();
			Label(Element* Tparent, Rectangle<int> Trect, Text Ttext, Callback<Label> Tcallback = 0,
				Color Tbackcolor = Color(0, 0, 0, 0), Color Tbordercolor = Color(173, 173, 173), int Tborderthickness = 1, const Sprite& Tsprite = {},
				Rectangle<int> Tpadding = { 0,0,0,0 }, Dock Ttldock = {}, Dock Ttrdock = {}, Dock Tbldock = {}, Dock Tbrdock = {});

			~Label();

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

			Callback<Label> callback;

			bool mouseentered;

			friend class Instance;
			friend class Renderer;
			friend class Window;
		};
	}
}

#endif