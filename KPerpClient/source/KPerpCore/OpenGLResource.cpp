
#include <KPerpCore/OpenGLResource.hpp>

#include <windows.h>

namespace kp {
	namespace OpenGL {
		bool OpenGLObject::isThisResourceisForThisContext() const {
			return ((wglGetCurrentDC() == hdc) && (wglGetCurrentContext() == hglrc));
		}
	}
}