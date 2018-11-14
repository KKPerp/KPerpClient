#include "Shader.hpp"
#include "Renderer.hpp"

#include <windows.h>

#include <string>
#include <sstream>

#define KP_SHADER_EDITOR_CHECK if (tempString == NULL) { return; }
#define KP_SHADER_EDITOR_STREAM_CHECK if (tempString == NULL) { return *this; }

namespace kp {
	namespace OpenGL {
		Shader::Shader() {
			hdc = wglGetCurrentDC();
			hglrc = wglGetCurrentContext();

			vertex = 0;
			fragment = 0;
			program = 0;

			tempString = NULL;
		}
		Shader::Shader(const char* Tvshader, const char* Tfshader) {
			hdc = wglGetCurrentDC();
			hglrc = wglGetCurrentContext();
			if (!isThisResourceisForThisContext()) {
				HDC _hdc;
				HGLRC _hglrc;
				_hdc = wglGetCurrentDC();
				_hglrc = wglGetCurrentContext();
				wglMakeCurrent(hdc, hglrc);
			vertex = glCreateShader(GL_VERTEX_SHADER);
			fragment = glCreateShader(GL_FRAGMENT_SHADER);
			if (Tvshader != NULL) {
				glShaderSource(vertex, 1, &Tvshader, NULL);
			}
			if (Tfshader != NULL) {
				glShaderSource(fragment, 1, &Tfshader, NULL);
			}
			wglMakeCurrent(_hdc, _hglrc);
			}
			else {
				vertex = glCreateShader(GL_VERTEX_SHADER);
				fragment = glCreateShader(GL_FRAGMENT_SHADER);
				if (Tvshader != NULL) {
					glShaderSource(vertex, 1, &Tvshader, NULL);
				}
				if (Tfshader != NULL) {
					glShaderSource(fragment, 1, &Tfshader, NULL);
				}
			}
		}
		Shader::~Shader() {

			if (!isThisResourceisForThisContext()) {
				HDC _hdc;
				HGLRC _hglrc;
				_hdc = wglGetCurrentDC();
				_hglrc = wglGetCurrentContext();
				wglMakeCurrent(hdc, hglrc);
				if (vertex) {
					glDeleteShader(vertex);
				}
				if (fragment) {
					glDeleteShader(fragment);
				}
				if (program) {
					glDeleteProgram(program);
				}
				wglMakeCurrent(_hdc, _hglrc);
			}
			else {
				if (vertex) {
					glDeleteShader(vertex);
				}
				if (fragment) {
					glDeleteShader(fragment);
				}
				if (program) {
					glDeleteProgram(program);
				}
			}
		}

		void Shader::Create(const char* Tvshader, const char* Tfshader) {
			hdc = wglGetCurrentDC();
			hglrc = wglGetCurrentContext();
			if (!isThisResourceisForThisContext()) {
				HDC _hdc;
				HGLRC _hglrc;
				_hdc = wglGetCurrentDC();
				_hglrc = wglGetCurrentContext();
				wglMakeCurrent(hdc, hglrc);
				if (vertex == NULL && fragment == NULL) {
					vertex = glCreateShader(GL_VERTEX_SHADER);
					fragment = glCreateShader(GL_FRAGMENT_SHADER);
					if (Tvshader != NULL) {
						glShaderSource(vertex, 1, &Tvshader, NULL);
					}
					if (Tfshader != NULL) {
						glShaderSource(fragment, 1, &Tfshader, NULL);
					}
				}
				wglMakeCurrent(_hdc, _hglrc);
			}
			else {
				if (vertex == NULL && fragment == NULL) {
					vertex = glCreateShader(GL_VERTEX_SHADER);
					fragment = glCreateShader(GL_FRAGMENT_SHADER);
					if (Tvshader != NULL) {
						glShaderSource(vertex, 1, &Tvshader, NULL);
					}
					if (Tfshader != NULL) {
						glShaderSource(fragment, 1, &Tfshader, NULL);
					}
				}
			}
		}

		void Shader::Source(const char* Tvshader, const char* Tfshader) {
			if (!isThisResourceisForThisContext()) {
				HDC _hdc;
				HGLRC _hglrc;
				_hdc = wglGetCurrentDC();
				_hglrc = wglGetCurrentContext();
				wglMakeCurrent(hdc, hglrc);
			glShaderSource(vertex, 1, &Tvshader, NULL);
			glShaderSource(fragment, 1, &Tfshader, NULL);
			wglMakeCurrent(_hdc, _hglrc);
			}
			else {
				glShaderSource(vertex, 1, &Tvshader, NULL);
				glShaderSource(fragment, 1, &Tfshader, NULL);
			}
		}

		void Shader::Use() const {
			if (isThisResourceisForThisContext()) {
				glUseProgram(program);
			}
		}
		void Shader::setUniformType(Type Ttype, const char* Tname, ...) {
			if (!isThisResourceisForThisContext()) {
				HDC _hdc;
				HGLRC _hglrc;
				_hdc = wglGetCurrentDC();
				_hglrc = wglGetCurrentContext();
				wglMakeCurrent(hdc, hglrc);
			glUseProgram(program);
			switch (Ttype) {
			case Type::Int: {
				glUniform1i(glGetUniformLocation(program, Tname), *(int*)(&Tname + 4));
				break;
			}
			case Type::Float: {
				glUniform1f(glGetUniformLocation(program, Tname), *(float*)(&Tname + 4));
				break;
			}
			case Type::Intptr: {
				glUniform1iv(glGetUniformLocation(program, Tname), 1, (int*)(&Tname + 4));
				break;
			}
			case Type::Floatptr: {
				glUniform1fv(glGetUniformLocation(program, Tname), 1, (float*)(&Tname + 4));
				break;
			}
			case Type::Vec2: {
				glUniform2fv(glGetUniformLocation(program, Tname), 1, (float*)(&Tname + 4));
				break;
			}
			case Type::Vec3: {
				glUniform3fv(glGetUniformLocation(program, Tname), 1, (float*)(&Tname + 4));
				break;
			}
			case Type::Vec4: {
				glUniform4fv(glGetUniformLocation(program, Tname), 1, (float*)(&Tname + 4));
				break;
			}
			case Type::Mat2x2: {
				glUniformMatrix2fv(glGetUniformLocation(program, Tname), 1, 0, (float*)(&Tname + 4));
				break;
			}
			case Type::Mat3x2: {
				glUniformMatrix3x2fv(glGetUniformLocation(program, Tname), 1, 0, (float*)(&Tname + 4));
				break;
			}
			case Type::Mat4x2: {
				glUniformMatrix4x2fv(glGetUniformLocation(program, Tname), 1, 0, (float*)(&Tname + 4));
				break;
			}
			case Type::Mat2x3: {
				glUniformMatrix2x3fv(glGetUniformLocation(program, Tname), 1, 0, (float*)(&Tname + 4));
				break;
			}
			case Type::Mat3x3: {
				glUniformMatrix3fv(glGetUniformLocation(program, Tname), 1, 0, (float*)(&Tname + 4));
				break;
			}
			case Type::Mat4x3: {
				glUniformMatrix4x3fv(glGetUniformLocation(program, Tname), 1, 0, (float*)(&Tname + 4));
				break;
			}
			case Type::Mat2x4: {
				glUniformMatrix2x4fv(glGetUniformLocation(program, Tname), 1, 0, (float*)(&Tname + 4));
				break;
			}
			case Type::Mat3x4: {
				glUniformMatrix3x4fv(glGetUniformLocation(program, Tname), 1, 0, (float*)(&Tname + 4));
				break;
			}
			case Type::Mat4x4: {
				glUniformMatrix4fv(glGetUniformLocation(program, Tname), 1, 0, (float*)(&Tname + 4));
				break;
			}
			default: {
				break;
			}
			}
			wglMakeCurrent(_hdc, _hglrc);
			}
			else {
				glUseProgram(program);
				switch (Ttype) {
				case Type::Int: {
					glUniform1i(glGetUniformLocation(program, Tname), *(int*)(&Tname + 4));
					break;
				}
				case Type::Float: {
					glUniform1f(glGetUniformLocation(program, Tname), *(float*)(&Tname + 4));
					break;
				}
				case Type::Intptr: {
					glUniform1iv(glGetUniformLocation(program, Tname), 1, (int*)(&Tname + 4));
					break;
				}
				case Type::Floatptr: {
					glUniform1fv(glGetUniformLocation(program, Tname), 1, (float*)(&Tname + 4));
					break;
				}
				case Type::Vec2: {
					glUniform2fv(glGetUniformLocation(program, Tname), 1, (float*)(&Tname + 4));
					break;
				}
				case Type::Vec3: {
					glUniform3fv(glGetUniformLocation(program, Tname), 1, (float*)(&Tname + 4));
					break;
				}
				case Type::Vec4: {
					glUniform4fv(glGetUniformLocation(program, Tname), 1, (float*)(&Tname + 4));
					break;
				}
				default: {
					break;
				}
				case Type::Mat2x2: {
					glUniformMatrix2fv(glGetUniformLocation(program, Tname), 1, 0, (float*)(&Tname + 4));
					break;
				}
				case Type::Mat3x2: {
					glUniformMatrix3x2fv(glGetUniformLocation(program, Tname), 1, 0, (float*)(&Tname + 4));
					break;
				}
				case Type::Mat4x2: {
					glUniformMatrix4x2fv(glGetUniformLocation(program, Tname), 1, 0, (float*)(&Tname + 4));
					break;
				}
				case Type::Mat2x3: {
					glUniformMatrix2x3fv(glGetUniformLocation(program, Tname), 1, 0, (float*)(&Tname + 4));
					break;
				}
				case Type::Mat3x3: {
					glUniformMatrix3fv(glGetUniformLocation(program, Tname), 1, 0, (float*)(&Tname + 4));
					break;
				}
				case Type::Mat4x3: {
					glUniformMatrix4x3fv(glGetUniformLocation(program, Tname), 1, 0, (float*)(&Tname + 4));
					break;
				}
				case Type::Mat2x4: {
					glUniformMatrix2x4fv(glGetUniformLocation(program, Tname), 1, 0, (float*)(&Tname + 4));
					break;
				}
				case Type::Mat3x4: {
					glUniformMatrix3x4fv(glGetUniformLocation(program, Tname), 1, 0, (float*)(&Tname + 4));
					break;
				}
				case Type::Mat4x4: {
					glUniformMatrix4fv(glGetUniformLocation(program, Tname), 1, 0, (float*)(&Tname + 4));
					break;
				}
				}
			}
		}
		unsigned int Shader::getLocation(const char* Tname) {
			if (!isThisResourceisForThisContext()) {
				HDC _hdc;
				HGLRC _hglrc;
				_hdc = wglGetCurrentDC();
				_hglrc = wglGetCurrentContext();
				wglMakeCurrent(hdc, hglrc);
				int _location = glGetUniformLocation(program, Tname);
				wglMakeCurrent(_hdc, _hglrc);
				return _location;
			}
			else {
				return glGetUniformLocation(program, Tname);
			}
		}

		void Shader::setUniform(const char* Tname, int Tvalue) {
			if (!isThisResourceisForThisContext()) {
				HDC _hdc;
				HGLRC _hglrc;
				_hdc = wglGetCurrentDC();
				_hglrc = wglGetCurrentContext();
				wglMakeCurrent(hdc, hglrc);
				glUniform1i(glGetUniformLocation(program, Tname), Tvalue);
				wglMakeCurrent(_hdc, _hglrc);
			}
			else {
				//unsigned int loc = glGetUniformLocation(program, Tname);
				glUniform1i(glGetUniformLocation(program, Tname), Tvalue);
			}
		}
		void Shader::setUniform(const char* Tname, float Tvalue) {
			if (!isThisResourceisForThisContext()) {
				HDC _hdc;
				HGLRC _hglrc;
				_hdc = wglGetCurrentDC();
				_hglrc = wglGetCurrentContext();
				wglMakeCurrent(hdc, hglrc);
				glUniform1f(glGetUniformLocation(program, Tname), Tvalue);
				wglMakeCurrent(_hdc, _hglrc);
			}
			else {
				glUniform1f(glGetUniformLocation(program, Tname), Tvalue);
			}
		}
		void Shader::setUniform(const char* Tname, int* Tvalue, unsigned int Tsize) {
			if (!isThisResourceisForThisContext()) {
				HDC _hdc;
				HGLRC _hglrc;
				_hdc = wglGetCurrentDC();
				_hglrc = wglGetCurrentContext();
				wglMakeCurrent(hdc, hglrc);
				glUniform1iv(glGetUniformLocation(program, Tname), Tsize, Tvalue);
				wglMakeCurrent(_hdc, _hglrc);
			}
			else {
				glUniform1iv(glGetUniformLocation(program, Tname), Tsize, Tvalue);
			}
		}
		void Shader::setUniform(const char* Tname, float* Tvalue, unsigned int Tsize) {
			if (!isThisResourceisForThisContext()) {
				HDC _hdc;
				HGLRC _hglrc;
				_hdc = wglGetCurrentDC();
				_hglrc = wglGetCurrentContext();
				wglMakeCurrent(hdc, hglrc);
				glUniform1fv(glGetUniformLocation(program, Tname), Tsize, Tvalue);
				wglMakeCurrent(_hdc, _hglrc);
			}
			else {
				glUniform1fv(glGetUniformLocation(program, Tname), Tsize, Tvalue);
			}
		}
		void Shader::setUniform(const char* Tname, Vec2 Tvalue) {
			if (!isThisResourceisForThisContext()) {
				HDC _hdc;
				HGLRC _hglrc;
				_hdc = wglGetCurrentDC();
				_hglrc = wglGetCurrentContext();
				wglMakeCurrent(hdc, hglrc);
				glUniform2fv(glGetUniformLocation(program, Tname), 1, (float*)&Tvalue);
				wglMakeCurrent(_hdc, _hglrc);
			}
			else {
				glUniform2fv(glGetUniformLocation(program, Tname), 1, (float*)&Tvalue);
			}
		}
		void Shader::setUniform(const char* Tname, Vec3 Tvalue) {
			if (!isThisResourceisForThisContext()) {
				HDC _hdc;
				HGLRC _hglrc;
				_hdc = wglGetCurrentDC();
				_hglrc = wglGetCurrentContext();
				wglMakeCurrent(hdc, hglrc);
				glUniform3fv(glGetUniformLocation(program, Tname), 1, (float*)&Tvalue);
				wglMakeCurrent(_hdc, _hglrc);
			}
			else {
				glUniform3fv(glGetUniformLocation(program, Tname), 1, (float*)&Tvalue);
			}
		}
		void Shader::setUniform(const char* Tname, Vec4 Tvalue) {
			if (!isThisResourceisForThisContext()) {
				HDC _hdc;
				HGLRC _hglrc;
				_hdc = wglGetCurrentDC();
				_hglrc = wglGetCurrentContext();
				wglMakeCurrent(hdc, hglrc);
				glUniform4fv(glGetUniformLocation(program, Tname), 1, (float*)&Tvalue);
				wglMakeCurrent(_hdc, _hglrc);
			}
			else {
				glUniform4fv(glGetUniformLocation(program, Tname), 1, (float*)&Tvalue);
			}
		}
		void Shader::setUniform(const char* Tname, Matrix<float, 2, 2> Tvalue) {
			if (!isThisResourceisForThisContext()) {
				HDC _hdc;
				HGLRC _hglrc;
				_hdc = wglGetCurrentDC();
				_hglrc = wglGetCurrentContext();
				wglMakeCurrent(hdc, hglrc);
				glUniformMatrix2fv(glGetUniformLocation(program, Tname), 1, 0, (float*)&Tvalue);
				wglMakeCurrent(_hdc, _hglrc);
			}
			else {
				glUniformMatrix2fv(glGetUniformLocation(program, Tname), 1, 0, (float*)&Tvalue);
			}
		}
		void Shader::setUniform(const char* Tname, Matrix<float, 3, 3> Tvalue) {
			if (!isThisResourceisForThisContext()) {
				HDC _hdc;
				HGLRC _hglrc;
				_hdc = wglGetCurrentDC();
				_hglrc = wglGetCurrentContext();
				wglMakeCurrent(hdc, hglrc);
				glUniformMatrix3fv(glGetUniformLocation(program, Tname), 1, 0, (float*)&Tvalue);
				wglMakeCurrent(_hdc, _hglrc);
			}
			else {
				glUniformMatrix3fv(glGetUniformLocation(program, Tname), 1, 0, (float*)&Tvalue);
			}
		}
		void Shader::setUniform(const char* Tname, Matrix<float, 4, 4> Tvalue) {
			if (!isThisResourceisForThisContext()) {
				HDC _hdc;
				HGLRC _hglrc;
				_hdc = wglGetCurrentDC();
				_hglrc = wglGetCurrentContext();
				wglMakeCurrent(hdc, hglrc);
				glUniformMatrix4fv(glGetUniformLocation(program, Tname), 1, 0, (float*)&Tvalue);
				wglMakeCurrent(_hdc, _hglrc);
			}
			else {
				glUniformMatrix4fv(glGetUniformLocation(program, Tname), 1, 0, (float*)&Tvalue);
			}
		}

		void Shader::setUniform(unsigned int Tlocation, int Tvalue) {
			if (!isThisResourceisForThisContext()) {
				HDC _hdc;
				HGLRC _hglrc;
				_hdc = wglGetCurrentDC();
				_hglrc = wglGetCurrentContext();
				wglMakeCurrent(hdc, hglrc);
				glUniform1i(Tlocation, Tvalue);
				wglMakeCurrent(_hdc, _hglrc);
			}
			else {
				glUniform1i(Tlocation, Tvalue);
			}
		}
		void Shader::setUniform(unsigned int Tlocation, float Tvalue) {
			if (!isThisResourceisForThisContext()) {
				HDC _hdc;
				HGLRC _hglrc;
				_hdc = wglGetCurrentDC();
				_hglrc = wglGetCurrentContext();
				wglMakeCurrent(hdc, hglrc);
				glUniform1f(Tlocation, Tvalue);
				wglMakeCurrent(_hdc, _hglrc);
			}
			else {
				glUniform1f(Tlocation, Tvalue);
			}
		}
		void Shader::setUniform(unsigned int Tlocation, int* Tvalue, unsigned int Tsize) {
			if (!isThisResourceisForThisContext()) {
				HDC _hdc;
				HGLRC _hglrc;
				_hdc = wglGetCurrentDC();
				_hglrc = wglGetCurrentContext();
				wglMakeCurrent(hdc, hglrc);
				glUniform1iv(Tlocation, Tsize, Tvalue);
				wglMakeCurrent(_hdc, _hglrc);
			}
			else {
				glUniform1iv(Tlocation, Tsize, Tvalue);
			}
		}
		void Shader::setUniform(unsigned int Tlocation, float* Tvalue, unsigned int Tsize) {
			if (!isThisResourceisForThisContext()) {
				HDC _hdc;
				HGLRC _hglrc;
				_hdc = wglGetCurrentDC();
				_hglrc = wglGetCurrentContext();
				wglMakeCurrent(hdc, hglrc);
				glUniform1fv(Tlocation, Tsize, Tvalue);
				wglMakeCurrent(_hdc, _hglrc);
			}
			else {
				glUniform1fv(Tlocation, Tsize, Tvalue);
			}
		}
		void Shader::setUniform(unsigned int Tlocation, Vec2 Tvalue) {
			if (!isThisResourceisForThisContext()) {
				HDC _hdc;
				HGLRC _hglrc;
				_hdc = wglGetCurrentDC();
				_hglrc = wglGetCurrentContext();
				wglMakeCurrent(hdc, hglrc);
				glUniform2fv(Tlocation, 1, (float*)&Tvalue);
				wglMakeCurrent(_hdc, _hglrc);
			}
			else {
				glUniform2fv(Tlocation, 1, (float*)&Tvalue);
			}
		}
		void Shader::setUniform(unsigned int Tlocation, Vec3 Tvalue) {
			if (!isThisResourceisForThisContext()) {
				HDC _hdc;
				HGLRC _hglrc;
				_hdc = wglGetCurrentDC();
				_hglrc = wglGetCurrentContext();
				wglMakeCurrent(hdc, hglrc);
				glUniform3fv(Tlocation, 1, (float*)&Tvalue);
				wglMakeCurrent(_hdc, _hglrc);
			}
			else {
				glUniform3fv(Tlocation, 1, (float*)&Tvalue);
			}
		}
		void Shader::setUniform(unsigned int Tlocation, Vec4 Tvalue) {
			if (!isThisResourceisForThisContext()) {
				HDC _hdc;
				HGLRC _hglrc;
				_hdc = wglGetCurrentDC();
				_hglrc = wglGetCurrentContext();
				wglMakeCurrent(hdc, hglrc);
				glUniform4fv(Tlocation, 1, (float*)&Tvalue);
				wglMakeCurrent(_hdc, _hglrc);
			}
			else {
				glUniform4fv(Tlocation, 1, (float*)&Tvalue);
			}
		}
		void Shader::setUniform(unsigned int Tlocation, Matrix<float, 2, 2> Tvalue) {
			if (!isThisResourceisForThisContext()) {
				HDC _hdc;
				HGLRC _hglrc;
				_hdc = wglGetCurrentDC();
				_hglrc = wglGetCurrentContext();
				wglMakeCurrent(hdc, hglrc);
				glUniformMatrix2fv(Tlocation, 1, 0, (float*)&Tvalue);
				wglMakeCurrent(_hdc, _hglrc);
			}
			else {
				glUniformMatrix2fv(Tlocation, 1, 0, (float*)&Tvalue);
			}
		}
		void Shader::setUniform(unsigned int Tlocation, Matrix<float, 3, 3> Tvalue) {
			if (!isThisResourceisForThisContext()) {
				HDC _hdc;
				HGLRC _hglrc;
				_hdc = wglGetCurrentDC();
				_hglrc = wglGetCurrentContext();
				wglMakeCurrent(hdc, hglrc);
				glUniformMatrix3fv(Tlocation, 1, 0, (float*)&Tvalue);
				wglMakeCurrent(_hdc, _hglrc);
			}
			else {
				glUniformMatrix3fv(Tlocation, 1, 0, (float*)&Tvalue);
			}
		}
		void Shader::setUniform(unsigned int Tlocation, Matrix<float, 4, 4> Tvalue) {
			if (!isThisResourceisForThisContext()) {
				HDC _hdc;
				HGLRC _hglrc;
				_hdc = wglGetCurrentDC();
				_hglrc = wglGetCurrentContext();
				wglMakeCurrent(hdc, hglrc);
				glUniformMatrix4fv(Tlocation, 1, 0, (float*)&Tvalue);
				wglMakeCurrent(_hdc, _hglrc);
			}
			else {
				glUniformMatrix4fv(Tlocation, 1, 0, (float*)&Tvalue);
			}
		}

		bool Shader::Compile() {
			if (vertex == 0 || fragment == 0) {
				return 0;
			}

			int _success;

			if (!isThisResourceisForThisContext()) {
				HDC _hdc;
				HGLRC _hglrc;
				_hdc = wglGetCurrentDC();
				_hglrc = wglGetCurrentContext();
				wglMakeCurrent(hdc, hglrc);
			glCompileShader(vertex);

			glGetShaderiv(vertex, GL_COMPILE_STATUS, &_success);
			if (!_success) {
				wglMakeCurrent(_hdc, _hglrc);
				return 0;
			}

			glCompileShader(fragment);
			glGetShaderiv(fragment, GL_COMPILE_STATUS, &_success);
			if (!_success) {
				wglMakeCurrent(_hdc, _hglrc);
				return 0;
			}

			program = glCreateProgram();
			glAttachShader(program, vertex);
			glAttachShader(program, fragment);
			glLinkProgram(program);

			glGetProgramiv(program, GL_LINK_STATUS, &_success);

			wglMakeCurrent(_hdc, _hglrc);
			}
			else {
				glCompileShader(vertex);

				glGetShaderiv(vertex, GL_COMPILE_STATUS, &_success);
				if (!_success) {
					return 0;
				}

				glCompileShader(fragment);
				glGetShaderiv(fragment, GL_COMPILE_STATUS, &_success);
				if (!_success) {
					return 0;
				}

				program = glCreateProgram();
				glAttachShader(program, vertex);
				glAttachShader(program, fragment);
				glLinkProgram(program);

				glGetProgramiv(program, GL_LINK_STATUS, &_success);
			}

			if (!_success) {
				return 0;
			}

			return 1;
		}

		char* Shader::getLog(ShaderType Tstype) {
			if (!isThisResourceisForThisContext()) {
				HDC _hdc;
				HGLRC _hglrc;
				_hdc = wglGetCurrentDC();
				_hglrc = wglGetCurrentContext();
				wglMakeCurrent(hdc, hglrc);
			char* infolog = new char[1024];

			if (Tstype == ShaderType::Vertex) {
				glGetShaderInfoLog(vertex, 1024, NULL, infolog);
			}
			if (Tstype == ShaderType::Fragment) {
				glGetShaderInfoLog(fragment, 1024, NULL, infolog);
			}
			if (Tstype == ShaderType::Program) {
				glGetShaderInfoLog(program, 1024, NULL, infolog);
			}

			wglMakeCurrent(_hdc, _hglrc);
			return infolog;
			}
			else {
				char* infolog = new char[1024];

				if (Tstype == ShaderType::Vertex) {
					glGetShaderInfoLog(vertex, 1024, NULL, infolog);
				}
				if (Tstype == ShaderType::Fragment) {
					glGetShaderInfoLog(fragment, 1024, NULL, infolog);
				}
				if (Tstype == ShaderType::Program) {
					glGetShaderInfoLog(program, 1024, NULL, infolog);
				}
				return infolog;
			}
		}
		void Shader::getLog(ShaderType Tstype, char* Tstring, int Tsize) {
			if (!isThisResourceisForThisContext()) {
				HDC _hdc;
				HGLRC _hglrc;
				_hdc = wglGetCurrentDC();
				_hglrc = wglGetCurrentContext();
				wglMakeCurrent(hdc, hglrc);
			if (Tstype == ShaderType::Vertex) {
				glGetShaderInfoLog(vertex, Tsize, NULL, Tstring);
			}
			if (Tstype == ShaderType::Fragment) {
				glGetShaderInfoLog(fragment, Tsize, NULL, Tstring);
			}
			if (Tstype == ShaderType::Program) {
				glGetShaderInfoLog(program, Tsize, NULL, Tstring);
			}

			wglMakeCurrent(_hdc, _hglrc);
			}
			else {
				if (Tstype == ShaderType::Vertex) {
					glGetShaderInfoLog(vertex, Tsize, NULL, Tstring);
				}
				if (Tstype == ShaderType::Fragment) {
					glGetShaderInfoLog(fragment, Tsize, NULL, Tstring);
				}
				if (Tstype == ShaderType::Program) {
					glGetShaderInfoLog(program, Tsize, NULL, Tstring);
				}
			}
		}
		void Shader::freeLog(char* Tlog) {
			if (Tlog != NULL) {
				free(Tlog);
			}
		}

		void Shader::Begin(ShaderType Tstype, bool Tlive) {
			tempString = (std::stringstream*) new std::stringstream;
			liveedit = Tlive;
			dest = Tstype;
		}
		void Shader::Submit() {
			if (!isThisResourceisForThisContext()) {
				HDC _hdc;
				HGLRC _hglrc;
				_hdc = wglGetCurrentDC();
				_hglrc = wglGetCurrentContext();
				wglMakeCurrent(hdc, hglrc);
			if (dest == ShaderType::Vertex) {
				if (vertex == NULL) {
					vertex = glCreateShader(GL_VERTEX_SHADER);
				}
				char* _code = new char[((std::stringstream*)tempString)->str().length() + 1];
				_code[((std::stringstream*)tempString)->str().length()] = 0;

				std::string _codestring = ((std::stringstream*)tempString)->str();

				//const char* fuck = _codestring.c_str();
				//int lol = ((std::stringstream*)tempString)->str().length();

				if (((std::stringstream*)tempString)->str().length() > 0) {

					memcpy(_code, _codestring.c_str(), ((std::stringstream*)tempString)->str().length());

					glShaderSource(vertex, 1, &(_code), NULL);

				}

				delete[] _code;
			}
			if (dest == ShaderType::Fragment) {
				if (fragment == NULL) {
					fragment = glCreateShader(GL_FRAGMENT_SHADER);
				}
				char* _code = new char[((std::stringstream*)tempString)->str().length() + 1];
				_code[((std::stringstream*)tempString)->str().length()] = 0;

				std::string _codestring = ((std::stringstream*)tempString)->str();

				if (((std::stringstream*)tempString)->str().length() > 0) {

					memcpy(_code, _codestring.c_str(), ((std::stringstream*)tempString)->str().length());

					glShaderSource(fragment, 1, &(_code), NULL);

				}

				delete[] _code;
			}
			wglMakeCurrent(_hdc, _hglrc);
			}
			else {
				if (dest == ShaderType::Vertex) {
					if (vertex == NULL) {
						vertex = glCreateShader(GL_VERTEX_SHADER);
					}
					char* _code = new char[((std::stringstream*)tempString)->str().length() + 1];
					_code[((std::stringstream*)tempString)->str().length()] = 0;

					std::string _codestring = ((std::stringstream*)tempString)->str();

					//const char* fuck = _codestring.c_str();
					//int lol = ((std::stringstream*)tempString)->str().length();

					if (((std::stringstream*)tempString)->str().length() > 0) {

						memcpy(_code, _codestring.c_str(), ((std::stringstream*)tempString)->str().length());

						glShaderSource(vertex, 1, &(_code), NULL);

					}

					delete[] _code;
				}
				if (dest == ShaderType::Fragment) {
					if (fragment == NULL) {
						fragment = glCreateShader(GL_FRAGMENT_SHADER);
					}
					char* _code = new char[((std::stringstream*)tempString)->str().length() + 1];
					_code[((std::stringstream*)tempString)->str().length()] = 0;

					std::string _codestring = ((std::stringstream*)tempString)->str();

					if (((std::stringstream*)tempString)->str().length() > 0) {

						memcpy(_code, _codestring.c_str(), ((std::stringstream*)tempString)->str().length());

						glShaderSource(fragment, 1, &(_code), NULL);

					}

					delete[] _code;
				}
			}
		}
		void Shader::End() {
			if (tempString != NULL) {
				delete tempString;
			}
		}

		Shader& Shader::operator=(const Shader& Tshader) {
			hdc = Tshader.hdc;
			hglrc = Tshader.hglrc;

			vertex = Tshader.vertex;
			fragment = Tshader.fragment;
			program = Tshader.program;
			//memcpy(this, &Tshader, sizeof(*this));
			return *this;
		}

		void Shader::EditorAddText(const char* Ttext) {
			KP_SHADER_EDITOR_CHECK;

			*((std::stringstream*)tempString) << Ttext;
		}
		void Shader::operator+=(const char* Ttext) {
			KP_SHADER_EDITOR_CHECK

			*((std::stringstream*)tempString) << Ttext << "\n";
		}

		void Shader::EditorAddText(_ShaderDeclare Ttext) {
			KP_SHADER_EDITOR_CHECK;

			*((std::stringstream*)tempString) << "uniform mat4 _kp_matrix;"
			<< "uniform mat4 _kp_view;"
			<< "uniform mat4 _kp_transview;";
		}
		Shader& Shader::operator<<(_ShaderDeclare Ttext) {
			KP_SHADER_EDITOR_STREAM_CHECK

			*((std::stringstream*)tempString) << "uniform mat4 _kp_matrix;"
			<< "uniform mat4 _kp_view;"
			<< "uniform mat4 _kp_transview;";

			return *this;
		}

		void Shader::EditorAddText(_ShaderMultiply Ttext) {
			KP_SHADER_EDITOR_CHECK;

			*((std::stringstream*)tempString) << "_kp_transview * _kp_view * _kp_matrix";
		}
		Shader& Shader::operator<<(_ShaderMultiply Ttext) {
			KP_SHADER_EDITOR_STREAM_CHECK

			*((std::stringstream*)tempString) << "_kp_transview * _kp_view * _kp_matrix";

			return *this;
		}

		void Shader::EditorAddLine(const char* Ttext) {
			KP_SHADER_EDITOR_CHECK

			*((std::stringstream*)tempString) << Ttext << "\n";
		}
		Shader& Shader::operator<<(const char* Ttext) {
			KP_SHADER_EDITOR_STREAM_CHECK

			*((std::stringstream*)tempString) << Ttext;

			return *this;
		}
	}
}