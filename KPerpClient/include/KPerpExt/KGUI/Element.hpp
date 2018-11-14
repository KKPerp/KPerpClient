#ifndef _KPerpCore_KGui_Element_hpp_
#define _KPerpCore_KGui_Element_hpp_

#include "Buffer.hpp"

#include <KPerpCore/Math.hpp>
#include <KPerpCore/Shape.hpp>

#include <KPerpCore/Window.hpp>

#include <stdlib.h>

namespace kp {
	namespace KGui {
		enum class Type {
			Instance,
			Button,
			Label,
			Textbox
		};

		struct Dock {
			enum : unsigned int {
				Window = 0x0000001,
			};

			enum Corner {
				Auto = 0,
				TopLeft = 1,
				TopRight = 2,
				BottomLeft = 3,
				BottomRight = 4,
				Left = 5,
				Right = 6,
				Top = 7,
				Bottom = 8
			};

			Dock();
			Dock(Corner Tauto);
			Dock(Corner Tauto, unsigned int Telement);
			Dock(Corner Tauto, Corner Tcorner);
			Dock(Corner Tauto, Corner Tcorner, unsigned int Telement);
			Dock(Point<int> Tpos);
			Dock(unsigned int Telement, Point<int> Tpos);
			Dock(Corner Tcorner, unsigned int Telement, Point<int> Tpos);

			Corner point;
			unsigned int element;
			Point<int> pos;

			bool autopoint;
		};

		class ElementManager;
		
		class Element {
		public:
			Element();

			virtual void create();
			virtual void destroy();
			virtual void step();
			virtual void draw();

		protected:
			Element* parent;
			Buffer data;

			ElementManager* manager;

			bool drawable;

			friend class ElementManager;
			friend class Window;
		};

		class Instance : public Element {
		public:
			Instance();

			Rectangle<int> getRect();

			enum Event {
				OnClick,
				OnPressed,
				OnReleased,
				MouseEnter,
				MouseLeave,
				MouseOn,
				OnClicked,
			};

			typedef int Param;

			template <typename _Type>
			using Callback = void(*)(_Type&, Event, Point<long>, Param);

			~Instance();

		protected:
			virtual void create();
			virtual void destroy();
			virtual void step();
			virtual void draw();

			void initsurface();
			virtual void redraw();
			virtual void reset();

			Rectangle<int> rect;
			Dock tl, tr, bl, br;

			Texture* surface;

			Callback<Instance> callback;

			friend struct Dock;
			
			friend class ElementManager;
			friend class Renderer;
			friend class Window;

			friend Rectangle<int> getRect(Instance Tinst);

			Type type;
		};

		class ElementManager {
		public:
			ElementManager(Renderer& Trenderer) {
				container = new Element*[1];
				size = 1;

				renderer = &Trenderer;
			}
			~ElementManager() {
				delete[] container;
			}

			Element** add(int Tind, Element* Telement) {
				Tind++;

				container = (Element**)realloc(container, sizeof(Element*)*(size+1));

				for (int i = (size - 1);i > Tind - 1;i--) {
					container[i + 1] = container[i];
				}

				size++;

				Telement->manager = this;

				if (Telement->drawable) {
					((Instance*)Telement)->initsurface();
				}

				container[Tind] = Telement;

				return &container[Tind];
			}

			void remove(int Tind) {
				if (size < 2) {
					return;
				}

				Tind++;

				for (int i = Tind;i < size - 1;i++) {
					container[i] = container[i + 1];
				}

				container = (Element**)realloc(container, sizeof(Element*)*(size - 1));

				size--;
			}

			void draw(Renderer& Trenderer) {
				for (int i = 1;i <= size;i++) {
					//Trenderer << 
				}
			}

			Element*& operator[](int Tind) {
				return container[Tind + 1];
			}

			int getSize() {
				return size - 1;
			}

			Element*& getRight() {
				return container[size - 1];
			}

			Renderer* getrenderer() {
				return renderer;
			}

			int getIndex(Element* Telement) {
				for (int i = 1;i < size;i++) {
					if (container[i] == Telement) {
						return i;
					}
				}
			}

		private:
			Element ** container;
			int size;

			Renderer* renderer;
		};
	}
}

#endif