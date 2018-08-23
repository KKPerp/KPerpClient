#ifndef _KPerpCore_Texture_hpp_
#define _KPerpCore_Texture_hpp_

#include "OpenGLResource.hpp"

#ifndef NULL
#define NULL 0
#endif

namespace kp {
	namespace OpenGL {
		class Texture : public OpenGLObject {
		public:
			Texture();
			Texture(int Tw, int Th, unsigned int Tformat, const char* buffer, bool Tmipmap);
			~Texture();

			void Buffer(int Tw, int Th, const char* buffer, unsigned int Tformat);

			void Attribute(unsigned int Twarps, unsigned int Twarpt, unsigned int Tminf, unsigned int Tmaxf);

			void Bind();

			Texture& operator=(const Texture& Ttexture);

			int GetParameterInt(unsigned int Tattrib);
			float GetParameterFloat(unsigned int Tattrib);

			void SetParameterInt(unsigned int Tattrib, int Tvalue);
			void SetParameterFloat(unsigned int Tattrib, float Tvalue);

		protected:
			unsigned int texture;
		};
	}
}

#endif
