#ifndef _KPerpCore_KPerpDesignSection_hpp_
#define _KPerpCore_KPerpDesignSection_hpp_

//#include "KPerpDesignObject.hpp"
#include <KPerpCore/Renderer.hpp>
#include <KPerpCore/Shape.hpp>

namespace kp {
	struct DesignSectionData;

	typedef struct DesignSectionClassData *DesignSectionHandleClass, *DSHClass;
	typedef struct DesignSectionData *DesignSectionHandle, *DSHandle;

	class DesignSectionPaint {
	public:
		DesignSectionPaint();

		DesignSectionPaint& operator<< (Drawing::Line Tline);
		DesignSectionPaint& operator<< (Drawing::Triangle Ttriangle);
		DesignSectionPaint& operator<< (Drawing::Rectangle Trectangle);

		DesignSectionPaint& operator<< (Drawing::VertexArray& Tva);

		DesignSectionPaint& operator<< (Color Tcolor);
		DesignSectionPaint& operator<< (int Tint);

		DesignSectionPaint& operator<< (const Sprite& Tsprite);

		DesignSectionPaint& operator<< (const Text& Ttext);

		bool available();
	private:
		Renderer* renderer;
		DesignSectionHandle dshandle;

		friend class Renderer;
	};

	struct DesignSection {
		enum Event {
			OnClick,
			OnPressed,
			OnReleased,
			MouseEnter,
			MouseLeave,
			MouseOn,
			OnClicked,

			Step
		};

		static DesignSectionHandle Create(DesignSectionHandleClass Tdshclass, std::string Tname, Rectangle<int> Trect);
		static unsigned int ProcessEvent(DesignSectionHandle Tdshandle, Event& Tevent);

		static DesignSectionPaint BeginPaint(DesignSectionHandle Tdshandle);
		static bool EndPaint(DesignSectionHandle Tdshandle);

		static bool SetUnsignedInt(DesignSectionHandle Tdshandle, unsigned int Tuint);
		static unsigned int GetUnsignedInt(DesignSectionHandle Tdshandle);

		static bool SetPos(DesignSectionHandle Tdshandle, Point<int> Tuint);
		static bool Resize(DesignSectionHandle Tdshandle, Point<int> Tuint);
		static bool Move(DesignSectionHandle Tdshandle, Point<int> Tuint);
		static bool AddSize(DesignSectionHandle Tdshandle, Point<int> Tuint);
		static bool SetRect(DesignSectionHandle Tdshandle, Rectangle<int> Trect);

		static Rectangle<int> GetRect(DesignSectionHandle Tdshandle);
		static bool SetSprite(DesignSectionHandle Tdshandle, Sprite Tsprite);
		static Sprite GetSprite(DesignSectionHandle Tdshandle);

		static DesignSectionHandleClass GetClass(DesignSectionHandle Tdshandle);

		static Renderer* GetRenderer(DesignSectionHandle Tdshandle);
	};

	struct DesignSectionEventInfo {
		bool mouseover;
	};

	typedef void(*DesignSectionProcedure)(DesignSectionHandle Tdshandle, DesignSection::Event Tevent, unsigned int Tparam1, unsigned int Tparam2);
	typedef DesignSectionProcedure DSProc;
	typedef void(*DesignSectionDrawFunc)(Renderer& Trenderer, DesignSectionHandle Tdshandle, Rectangle<int> Trect, Texture* Ttexture, unsigned int Tuint);
	typedef DesignSectionDrawFunc DSDrawFunc;

	struct DesignSectionClass {
		DesignSectionClass();
		
		Renderer* renderer;
		std::string name;

		unsigned int exsize;

		DesignSectionProcedure dsproc;

		bool enablestep;

		DesignSectionDrawFunc bgdrawfunc;
		DesignSectionDrawFunc fgdrawfunc;

		static DesignSectionHandleClass Create(DesignSectionClass Tdsclass);

	private:
		static DesignSectionHandle CreateDesignSection(DesignSectionHandleClass Tdshclass, std::string Tname, Rectangle<int> Trect);
		static DesignSectionHandle CreateDesignSection(Renderer& Trenderer, std::string Tclass, std::string Tname, Rectangle<int> Trect);

		friend DesignSectionHandle CreateDesignSection(DesignSectionHandleClass Tdshclass, std::string Tname, Rectangle<int> Trect);
		friend DesignSectionHandle CreateDesignSection(Renderer& Trenderer, std::string Tclass, std::string Tname, Rectangle<int> Trect);

		friend class DesignSection;
	};

	typedef DesignSectionClass DSClass;

	DesignSectionHandle CreateDesignSection(DesignSectionHandleClass Tdshclass, std::string Tname, Rectangle<int> Trect);
	DesignSectionHandle CreateDesignSection(Renderer& Trenderer, std::string Tclass, std::string Tname, Rectangle<int> Trect);
}

#endif