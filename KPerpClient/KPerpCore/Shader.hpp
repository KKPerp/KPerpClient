#ifndef _KPerpCore_Shader_hpp_
#define _KPerpCore_Shader_hpp_

#include "OpenGLResource.hpp"
#include "Matrix.hpp"

namespace kp {
	class _ShaderDeclare;
	class _ShaderMultiply;

	namespace OpenGL {
		class Shader : OpenGLObject {
		public:
			Shader();
			Shader(const char* Tvshader, const char* Tfshader);
			~Shader();

			enum class Type {
				Int,
				Float,
				Intptr,
				Floatptr,

				Vec2,
				Vec3,
				Vec4,

				Mat2x2, Mat3x2, Mat4x2,
				Mat2x3, Mat3x3, Mat4x3,
				Mat2x4, Mat3x4, Mat4x4
			};

			enum ShaderType {
				Vertex,
				Fragment,
				Program
			};

			void Create(const char* Tvshader, const char* Tfshader);
			void Source(const char* Tvshader, const char* Tfshader);

			void Use() const;
			void setUniformType(Type Ttype, const char* Tname, ...);

			unsigned int getLocation(const char* Tname);

			void setUniform(const char* Tname, int Tvalue);
			void setUniform(const char* Tname, float Tvalue);
			void setUniform(const char* Tname, int* Tvalue, unsigned int Tsize);
			void setUniform(const char* Tname, float* Tvalue, unsigned int Tsize);
			void setUniform(const char* Tname, Vec2 Tvalue);
			void setUniform(const char* Tname, Vec3 Tvalue);
			void setUniform(const char* Tname, Vec4 Tvalue);
			void setUniform(const char* Tname, Matrix<float, 2, 2> Tvalue);
			void setUniform(const char* Tname, Matrix<float, 3, 3> Tvalue);
			void setUniform(const char* Tname, Matrix<float, 4, 4> Tvalue);

			void setUniform(unsigned int Tlocation, int Tvalue);
			void setUniform(unsigned int Tlocation, float Tvalue);
			void setUniform(unsigned int Tlocation, int* Tvalue, unsigned int Tsize);
			void setUniform(unsigned int Tlocation, float* Tvalue, unsigned int Tsize);
			void setUniform(unsigned int Tlocation, Vec2 Tvalue);
			void setUniform(unsigned int Tlocation, Vec3 Tvalue);
			void setUniform(unsigned int Tlocation, Vec4 Tvalue);
			void setUniform(unsigned int Tlocation, Matrix<float, 2, 2> Tvalue);
			void setUniform(unsigned int Tlocation, Matrix<float, 3, 3> Tvalue);
			void setUniform(unsigned int Tlocation, Matrix<float, 4, 4> Tvalue);

			bool Compile();
			char* getLog(ShaderType Tstype);
			void getLog(ShaderType Tstype, char* Tstring, int Tsize);
			void freeLog(char* Tlog);

			void Begin(ShaderType Tstype, bool Tlive);
			void Submit();
			void End();

			Shader& operator=(const Shader& Tshader);

			void EditorAddText(const char* Ttext);
			Shader& operator<<(const char* Ttext);

			void EditorAddText(_ShaderDeclare Ttext);
			Shader& operator<<(_ShaderDeclare Ttext);

			void EditorAddText(_ShaderMultiply Ttext);
			Shader& operator<<(_ShaderMultiply Ttext);

			void EditorAddLine(const char* Ttext);
			void operator+=(const char* Ttext);

		private:
			unsigned int vertex;
			unsigned int fragment;
			unsigned int program;

			void* tempString;
			ShaderType dest;
			bool liveedit;

			struct {
				int headers;
				int entrypoint;
			} position;
		};
	}
}

#endif
