#include <KPerpCore/Renderer.hpp>
#include <KPerpExt/DesignSection.hpp>

namespace kp {
	struct DesignSectionClassData {
		unsigned int exsize;
		Renderer* renderer;

		DesignSectionProcedure dsproc;
		bool enablestep;

		DesignSectionDrawFunc backdrawfunc;
		DesignSectionDrawFunc foredrawfunc;
	};

	struct DesignSectionData {
		DesignSectionData() {
			texture = NULL;
		}
		~DesignSectionData() {
			if (texture) {
				delete texture;
			}
		}

		DesignSectionClassData* dsclass;

		Rectangle<int> rect;

		bool mouseentered;
		bool pressed[3];

		Texture* texture;
		Sprite sprite;

		bool painting;

		unsigned int uint;

		bool mouseover;
	};

	Renderer& Renderer::operator<< (DesignSectionHandle Tdsobjport) {
		UseSolidTexture();

		if (Tdsobjport->dsclass->backdrawfunc) {
			Tdsobjport->dsclass->backdrawfunc(*this, Tdsobjport, Tdsobjport->rect, Tdsobjport->texture, Tdsobjport->uint);
		}

		//*this << Drawing::Rectangle(Vec3(Tdsobjport->rect.a.x, Tdsobjport->rect.a.y, 0), Vec3(Tdsobjport->rect.c.x, Tdsobjport->rect.c.y, 0), Color::White, Color::White, Color::White, Color::White, Vec2(0, 0), Vec2(1, 0), Vec2(0, 1), Vec2(1, 1), 0);
		Tdsobjport->sprite.rect.a = Vec3(Tdsobjport->rect.a.x, Tdsobjport->rect.a.y, 0);
		Tdsobjport->sprite.rect.c = Vec3(Tdsobjport->rect.c.x, Tdsobjport->rect.c.y, 0);
		*this << Tdsobjport->sprite;

		if (Tdsobjport->dsclass->foredrawfunc) {
			Tdsobjport->dsclass->foredrawfunc(*this, Tdsobjport, Tdsobjport->rect, Tdsobjport->texture, Tdsobjport->uint);
		}

		return *this;
	}
}