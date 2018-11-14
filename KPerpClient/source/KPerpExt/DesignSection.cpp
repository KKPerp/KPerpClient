#include <KPerpExt/DesignSection.hpp>

namespace kp {
	DesignSectionPaint::DesignSectionPaint() {
		renderer = NULL;
	}
	DesignSectionPaint& DesignSectionPaint::operator<< (Drawing::Line Tline) {
		*renderer << Tline;
		return *this;
	}
	DesignSectionPaint& DesignSectionPaint::operator<< (Drawing::Triangle Ttriangle) {
		*renderer << Ttriangle;
		return *this;
	}
	DesignSectionPaint& DesignSectionPaint::operator<< (Drawing::Rectangle Trectangle) {
		*renderer << Trectangle;
		return *this;
	}

	DesignSectionPaint& DesignSectionPaint::operator<< (Drawing::VertexArray& Tva) {
		*renderer << Tva;
		return *this;
	}

	DesignSectionPaint& DesignSectionPaint::operator<< (Color Tcolor) {
		*renderer << Tcolor;
		return *this;
	}
	DesignSectionPaint& DesignSectionPaint::operator<< (int Tint) {
		*renderer << Tint;
		return *this;
	}

	DesignSectionPaint& DesignSectionPaint::operator<< (const Sprite& Tsprite) {
		*renderer << Tsprite;
		return *this;
	}

	DesignSectionPaint& DesignSectionPaint::operator<< (const Text& Ttext) {
		*renderer << Ttext;
		return *this;
	}

	bool DesignSectionPaint::available() {
		return renderer;
	}

	DesignSectionClass::DesignSectionClass() {
		renderer = NULL;
		name = "";

		exsize = 0;
		dsproc = NULL;

		bgdrawfunc = NULL;
		fgdrawfunc = NULL;
	}

	DesignSectionHandleClass DesignSectionClass::Create(DesignSectionClass Tdsclass) {
		if (Tdsclass.renderer) {
			return (DesignSectionHandleClass)Tdsclass.renderer->createdesignsectionclass(&Tdsclass);
		}
		else {
			return NULL;
		}
	}

	DesignSectionHandle DesignSectionClass::CreateDesignSection(DesignSectionHandleClass Tdshclass, std::string Tname, Rectangle<int> Trect) {
		if (Tdshclass) {
			return (DesignSectionHandle)(*((Renderer**)((void*)(((char*)Tdshclass) + 4))))->createdesignsection(Tdshclass, Tname, Trect);
		}
		else {
			return NULL;
		}
	}
	DesignSectionHandle DesignSectionClass::CreateDesignSection(Renderer& Trenderer, std::string Tclass, std::string Tname, Rectangle<int> Trect) {
		return (DesignSectionHandle)Trenderer.createdesignsection(Tclass, Tname, Trect);
	}

	DesignSectionHandle CreateDesignSection(DesignSectionHandleClass Tdshclass, std::string Tname, Rectangle<int> Trect) {
		return DesignSectionClass::CreateDesignSection(Tdshclass, Tname, Trect);
	}
	DesignSectionHandle CreateDesignSection(Renderer& Trenderer, std::string Tclass, std::string Tname, Rectangle<int> Trect) {
		return DesignSectionClass::CreateDesignSection(Trenderer, Tclass, Tname, Trect);
	}

	DesignSectionHandle DesignSection::Create(DesignSectionHandleClass Tdshclass, std::string Tname, Rectangle<int> Trect) {
		return DesignSectionClass::CreateDesignSection(Tdshclass, Tname, Trect);
	}

	unsigned int DesignSection::ProcessEvent(DesignSectionHandle Tdshandle, Event& Tevent) {
		if (Tdshandle) {
			return (*((Renderer**)((void*)(((char*)*((DesignSectionHandleClass*)Tdshandle) + 4)))))->processeventdesignsection(Tdshandle);
		}
		else {
			return NULL;
		}
	}

	DesignSectionPaint DesignSection::BeginPaint(DesignSectionHandle Tdshandle) {
		if (Tdshandle) {
			return *((DesignSectionPaint*)(*((Renderer**)((void*)(((char*)*((DesignSectionHandleClass*)Tdshandle) + 4)))))->beginpaint(Tdshandle));
		}
		else {
			return {};
		}
	}
	bool DesignSection::EndPaint(DesignSectionHandle Tdshandle) {
		if (Tdshandle) {
			return (*((Renderer**)((void*)(((char*)*((DesignSectionHandleClass*)Tdshandle) + 4)))))->endpaint(Tdshandle);
		}
		else {
			return NULL;
		}
	}

	bool DesignSection::SetUnsignedInt(DesignSectionHandle Tdshandle, unsigned int Tuint) {
		if (Tdshandle) {
			return (*((Renderer**)((void*)(((char*)*((DesignSectionHandleClass*)Tdshandle) + 4)))))->setunsignedint(Tdshandle, Tuint);
		}
		else {
			return NULL;
		}
	}
	unsigned int DesignSection::GetUnsignedInt(DesignSectionHandle Tdshandle) {
		if (Tdshandle) {
			return (*((Renderer**)((void*)(((char*)*((DesignSectionHandleClass*)Tdshandle) + 4)))))->getunsignedint(Tdshandle);
		}
		else {
			return NULL;
		}
	}

	bool DesignSection::SetPos(DesignSectionHandle Tdshandle, Point<int> Tpoint) {
		if (Tdshandle) {
			return (*((Renderer**)((void*)(((char*)*((DesignSectionHandleClass*)Tdshandle) + 4)))))->setpos(Tdshandle, Tpoint);
		}
		else {
			return NULL;
		}
	}
	bool DesignSection::Resize(DesignSectionHandle Tdshandle, Point<int> Tpoint) {
		if (Tdshandle) {
			return (*((Renderer**)((void*)(((char*)*((DesignSectionHandleClass*)Tdshandle) + 4)))))->resize(Tdshandle, Tpoint);
		}
		else {
			return NULL;
		}
	}
	bool DesignSection::Move(DesignSectionHandle Tdshandle, Point<int> Tpoint) {
		if (Tdshandle) {
			return (*((Renderer**)((void*)(((char*)*((DesignSectionHandleClass*)Tdshandle) + 4)))))->move(Tdshandle, Tpoint);
		}
		else {
			return NULL;
		}
	}
	bool DesignSection::AddSize(DesignSectionHandle Tdshandle, Point<int> Tpoint) {
		if (Tdshandle) {
			return (*((Renderer**)((void*)(((char*)*((DesignSectionHandleClass*)Tdshandle) + 4)))))->addsize(Tdshandle, Tpoint);
		}
		else {
			return NULL;
		}
	}
	bool DesignSection::SetRect(DesignSectionHandle Tdshandle, Rectangle<int> Trect) {
		if (Tdshandle) {
			return (*((Renderer**)((void*)(((char*)*((DesignSectionHandleClass*)Tdshandle) + 4)))))->setrect(Tdshandle, Trect);
		}
		else {
			return NULL;
		}
	}

	Rectangle<int> DesignSection::GetRect(DesignSectionHandle Tdshandle) {
		if (Tdshandle) {
			return (*((Renderer**)((void*)(((char*)*((DesignSectionHandleClass*)Tdshandle) + 4)))))->getrect(Tdshandle);
		}
		else {
			return { 0,0,0,0 };
		}
	}
	bool DesignSection::SetSprite(DesignSectionHandle Tdshandle, Sprite Tsprite) {
		if (Tdshandle) {
			return (*((Renderer**)((void*)(((char*)*((DesignSectionHandleClass*)Tdshandle) + 4)))))->setsprite(Tdshandle, Tsprite);
		}
		else {
			return NULL;
		}
	}
	Sprite DesignSection::GetSprite(DesignSectionHandle Tdshandle) {
		if (Tdshandle) {
			return (*((Renderer**)((void*)(((char*)*((DesignSectionHandleClass*)Tdshandle) + 4)))))->getsprite(Tdshandle);
		}
		else {
			return {};
		}
	}

	DesignSectionHandleClass DesignSection::GetClass(DesignSectionHandle Tdshandle) {
		if (Tdshandle) {
			return *((DesignSectionHandleClass*)Tdshandle);
		}
		else {
			return NULL;
		}
	}

	Renderer* DesignSection::GetRenderer(DesignSectionHandle Tdshandle) {
		if (Tdshandle) {
			return *((Renderer**)((void*)(((char*)*((DesignSectionHandleClass*)Tdshandle) + 4))));
		}
		else {
			return NULL;
		}
	}
}