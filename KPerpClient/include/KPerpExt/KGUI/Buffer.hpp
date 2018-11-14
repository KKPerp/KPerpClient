#ifndef _KPerpCore_KGui_Buffer_hpp_
#define _KPerpCore_KGui_Buffer_hpp_

#include <string.h>

namespace kp {
	namespace KGui {
		class Buffer {
		public:
			Buffer() {
				size = 0;
				buffer = NULL;
			}
			Buffer(unsigned int Tsize) {
				size = Tsize;

				buffer = new char[size];
				memset(buffer, 0, size);
			}
			Buffer(unsigned int Tsize, const void* Tbuffer) {
				size = Tsize;

				buffer = new char[size];
				memcpy(buffer, Tbuffer, size);
			}
			Buffer(const char* Tstring) {
				size = strlen(Tstring);

				buffer = new char[size];
				memcpy(buffer, Tstring, size);
			};
			Buffer(const Buffer& Tbuffer) {
				if (buffer != NULL) {
					delete[] buffer;
					buffer = NULL;

					size = 0;
				}
				size = Tbuffer.size;

				buffer = new char[size];
				memcpy(buffer, Tbuffer.buffer, size);
			}

			void Data(const void* Tbuffer) {
				if (buffer != NULL) {
					memcpy(buffer, Tbuffer, size);
				}
			}
			void Data(unsigned int Tsize, const void* Tbuffer) {
				if (buffer != NULL) {
					delete[] buffer;
					buffer = NULL;

					size = 0;
				}
				size = Tsize;

				buffer = new char[size];
				memcpy(buffer, Tbuffer, size);
			}
			void Resize(unsigned int Tsize) {
				if (buffer == NULL) {
					size = Tsize;

					buffer = new char[size];
					memset(buffer, 0, size);
				}
				else {
					char* temp = new char[Tsize];
					memset(temp, 0, Tsize);

					memcpy(temp, buffer, size < Tsize ? size : Tsize);

					size = Tsize;

					delete[] buffer;
					buffer = temp;
				}
			}

			void Delete() {
				if (buffer != NULL) {
					delete[] buffer;
					buffer = NULL;

					size = 0;
				}
			}

			char& operator[](unsigned int Tind) {
				return buffer[Tind];
			}
			char operator[](unsigned int Tind) const {
				return buffer[Tind];
			}

			Buffer& operator++() {
				this->Resize(this->size + 1);
				return *this;
			}
			Buffer& operator--() {
				this->Resize(this->size + 1);
				return *this;
			}

			Buffer operator+(const Buffer& Tbuffer) {
				Buffer product(this->size + Tbuffer.size, this->buffer);
				memcpy((char*)((product.buffer) + (this->size)), Tbuffer.buffer, Tbuffer.size);

				return product;
			}
			Buffer operator+=(const Buffer& Tbuffer) {
				this->Resize(this->size + Tbuffer.size);
				memcpy((char*)((this->buffer) + (this->size)), Tbuffer.buffer, Tbuffer.size);
			}

			~Buffer() {
				if (buffer != NULL) {
					delete[] buffer;
					buffer = NULL;

					size = 0;
				}
			}

		private:
			unsigned int size;
			char* buffer;
		};
	}
}

#endif
