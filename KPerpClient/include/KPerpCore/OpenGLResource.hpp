#ifndef _KPerpCore_OpenGLResource_hpp_
#define _KPerpCore_OpenGLResource_hpp_

#include <KPerpCore/Win32Handles.hpp>

namespace kp {
	namespace OpenGL {
		class OpenGLObject {
		protected:
			bool isThisResourceisForThisContext() const;

			HandleDeviceContext hdc;
			HandleGLRenderContext hglrc;
		};
	}
}

#endif