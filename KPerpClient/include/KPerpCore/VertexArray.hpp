#ifndef _KPerpCore_VertexArray_hpp_
#define _KPerpCore_VertexArray_hpp_

#include <KPerpCore/OpenGLResource.hpp>

namespace kp {
	namespace OpenGL {
		class VertexArray : OpenGLObject {
		public:
			VertexArray();
			VertexArray(const float* Tvertices, int Tvasize, const unsigned int* Telement, int Telesize);

			~VertexArray();

			void Vertex(const float* Tvertices, int Tvasize);
			void Element(const unsigned int* Telement, int Telesize);

			void Bind();

			void Draw(unsigned int Tglmode, int Tcount);

			void Section(int Tindex, int Tsize, int Tvsize, int Tptr);

			void Create(const float* Tvertices, int Tvasize, const unsigned int* Telement, int Telesize);
			void Delete();

			VertexArray& operator=(const VertexArray& Tva);

		private:
			unsigned int vertexarray;
			unsigned int vertexbuffer;
			unsigned int elementbuffer;
		};
	}
}

#endif