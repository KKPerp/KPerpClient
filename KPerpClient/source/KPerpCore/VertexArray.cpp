

#include <KPerpCore/VertexArray.hpp>
#include <KPerpCore/Renderer.hpp>

#include <windows.h>

namespace kp {
	namespace OpenGL {
		VertexArray::VertexArray() {
			hdc = wglGetCurrentDC();
			hglrc = wglGetCurrentContext();
		}
		VertexArray::VertexArray(const float* Tvertices, int Tvasize, const unsigned int* Telement, int Telesize) {
			hdc = wglGetCurrentDC();
			hglrc = wglGetCurrentContext();

			glGenVertexArrays(1, &vertexarray);
			glGenBuffers(1, &vertexbuffer);
			glGenBuffers(1, &elementbuffer);

			glBindVertexArray(vertexarray);
			glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

			glBufferData(GL_ARRAY_BUFFER, Tvasize, Tvertices, GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

			if (Telement == NULL) {
				unsigned int* _element = new unsigned int[Telesize];
				for (int i = 0;i < Telesize;i++) {
					_element[i] = i;
				}

				glBufferData(GL_ELEMENT_ARRAY_BUFFER, Telesize * sizeof(unsigned int), _element, GL_STATIC_DRAW);

				delete[] _element;
			}
			else {
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, Telesize, Telement, GL_STATIC_DRAW);
			}

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);

			//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(3 * sizeof(float)));
			//glEnableVertexAttribArray(1);
		}

		VertexArray::~VertexArray() {
			if (!isThisResourceisForThisContext()) {
				HDC _hdc;
				HGLRC _hglrc;
				_hdc = wglGetCurrentDC();
				_hglrc = wglGetCurrentContext();
				wglMakeCurrent(hdc, hglrc);
				glDeleteVertexArrays(1, &vertexarray);
				glDeleteBuffers(1, &vertexbuffer);
				glDeleteBuffers(1, &elementbuffer);
				wglMakeCurrent(_hdc, _hglrc);
			}
			else {
				glDeleteVertexArrays(1, &vertexarray);
				glDeleteBuffers(1, &vertexbuffer);
				glDeleteBuffers(1, &elementbuffer);
			}
		}

		void VertexArray::Vertex(const float* Tvertices, int Tvasize) {
			if (!isThisResourceisForThisContext()) {
				HDC _hdc;
				HGLRC _hglrc;
				_hdc = wglGetCurrentDC();
				_hglrc = wglGetCurrentContext();
				wglMakeCurrent(hdc, hglrc);
				glBindVertexArray(vertexarray);
				glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

				glBufferSubData(GL_ARRAY_BUFFER, 0, Tvasize, Tvertices);
				wglMakeCurrent(_hdc, _hglrc);
			}
			else {
				glBindVertexArray(vertexarray);
				glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

				glBufferSubData(GL_ARRAY_BUFFER, 0, Tvasize, Tvertices);
			}
		}
		void VertexArray::Element(const unsigned int* Telement, int Telesize) {
			if (!isThisResourceisForThisContext()) {
				HDC _hdc;
				HGLRC _hglrc;
				_hdc = wglGetCurrentDC();
				_hglrc = wglGetCurrentContext();
				wglMakeCurrent(hdc, hglrc);
				glBindVertexArray(vertexarray);
				glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexbuffer);

				if (Telement == NULL) {
					unsigned int* _element = new unsigned int[Telesize];
					for (int i = 0;i < Telesize;i++) {
						_element[i] = i;
					}

					glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, Telesize * sizeof(unsigned int), _element);

					delete[] _element;
				}
				else {
					glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, Telesize, Telement);
				}
				wglMakeCurrent(_hdc, _hglrc);
			}
			else {
				glBindVertexArray(vertexarray);
				glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexbuffer);

				if (Telement == NULL) {
					unsigned int* _element = new unsigned int[Telesize];
					for (int i = 0;i < Telesize;i++) {
						_element[i] = i;
					}

					glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, Telesize * sizeof(unsigned int), _element);

					delete[] _element;
				}
				else {
					glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, Telesize, Telement);
				}
			}
		}

		void VertexArray::Bind() {
			if (isThisResourceisForThisContext()) {
				glBindVertexArray(vertexarray);
				glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
			}
		}

		void VertexArray::Draw(unsigned int Tglmode, int Tcount) {
			if (isThisResourceisForThisContext()) {
				glDrawElements(Tglmode, Tcount, GL_UNSIGNED_INT, 0);
			}
		}

		void VertexArray::Section(int Tindex, int Tsize, int Tvsize, int Tptr) {
			if (!isThisResourceisForThisContext()) {
				HDC _hdc;
				HGLRC _hglrc;
				_hdc = wglGetCurrentDC();
				_hglrc = wglGetCurrentContext();
				wglMakeCurrent(hdc, hglrc);
				glBindVertexArray(vertexarray);
				glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

				glVertexAttribPointer(Tindex, Tsize, GL_FLOAT, GL_FALSE, sizeof(float) * Tvsize, (void*)(Tptr * sizeof(float)));
				glEnableVertexAttribArray(Tindex);
				wglMakeCurrent(_hdc, _hglrc);
			}
			else {
				glBindVertexArray(vertexarray);
				glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

				glVertexAttribPointer(Tindex, Tsize, GL_FLOAT, GL_FALSE, sizeof(float) * Tvsize, (void*)(Tptr * sizeof(float)));
				glEnableVertexAttribArray(Tindex);
			}
		}

		void VertexArray::Create(const float* Tvertices, int Tvasize, const unsigned int* Telement, int Telesize) {
			hdc = wglGetCurrentDC();
			hglrc = wglGetCurrentContext();

			glGenVertexArrays(1, &vertexarray);
			glGenBuffers(1, &vertexbuffer);
			glGenBuffers(1, &elementbuffer);

			glBindVertexArray(vertexarray);
			glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

			glBufferData(GL_ARRAY_BUFFER, Tvasize, Tvertices, GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

			if (Telement == NULL) {
				unsigned int* _element = new unsigned int[Telesize];
				for (int i = 0;i < Telesize;i++) {
					_element[i] = i;
				}

				glBufferData(GL_ELEMENT_ARRAY_BUFFER, Telesize * sizeof(unsigned int), _element, GL_STATIC_DRAW);

				delete[] _element;
			}
			else {
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, Telesize, Telement, GL_STATIC_DRAW);
			}

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}

		void VertexArray::Delete() {
			if (!isThisResourceisForThisContext()) {
				HDC _hdc;
				HGLRC _hglrc;
				_hdc = wglGetCurrentDC();
				_hglrc = wglGetCurrentContext();
				wglMakeCurrent(hdc, hglrc);
				glDeleteVertexArrays(1, &vertexarray);
				glDeleteBuffers(1, &vertexbuffer);
				glDeleteBuffers(1, &elementbuffer);
				wglMakeCurrent(_hdc, _hglrc);
			}
			else {
				glDeleteVertexArrays(1, &vertexarray);
				glDeleteBuffers(1, &vertexbuffer);
				glDeleteBuffers(1, &elementbuffer);
			}
		}

		VertexArray& VertexArray::operator=(const VertexArray& Tva) {
			memcpy(this, &Tva, sizeof(*this));
			return *this;
		}
	}
}