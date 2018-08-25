#include "Renderer.hpp"
#include "Window.hpp"
#include "Drawing.hpp"

#include <string.h>

namespace kp {
	unsigned int _glmodes[] = {
		GL_POINTS,GL_LINES,GL_LINE_STRIP,
		GL_TRIANGLES,GL_TRIANGLE_STRIP,GL_TRIANGLE_FAN,GL_QUADS
	};

	void Renderer::Clear(Color Tcolor) {
		if (beginvertex == 1) {
			glEnd();
		}
		glClearColor(Tcolor.r() / 255.0f, Tcolor.b() / 255.0f, Tcolor.g() / 255.0f, Tcolor.a() / 255.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	
	Renderer& Renderer::operator<< (Drawing::Line Tline) {
		if (beginvertex == 1) {
			glEnd();
		}

		float _buffer[] = {
			((Tline.a.x)),(((Tline.a.y))),0.0f,Tline.c1.x,Tline.c1.y,Tline.c1.z,Tline.c1.w,Tline.t1.x,1.0f - Tline.t1.y,
			((Tline.b.x)),(((Tline.b.y))),0.0f,Tline.c2.x,Tline.c2.y,Tline.c2.z,Tline.c2.w,Tline.t2.x,1.0f - Tline.t2.y,
		};

		glBindVertexArray(linevao);
		glBindBuffer(GL_ARRAY_BUFFER, linevbo);

		memcpy(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY), _buffer, sizeof(_buffer));
		glUnmapBuffer(GL_ARRAY_BUFFER);

		glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, 0);

		return *this;
	}
	Renderer& Renderer::operator<<(Drawing::Triangle Ttriangle) {
		if (beginvertex == 1) {
			glEnd();
		}

		glBindTexture(GL_TEXTURE_2D, white);

		float _buffer[] = {
			((Ttriangle.a.x)),(((Ttriangle.a.y))),0.0f,Ttriangle.c1.x,Ttriangle.c1.y,Ttriangle.c1.z,Ttriangle.c1.w,Ttriangle.t1.x,1.0f - Ttriangle.t1.y,
			((Ttriangle.b.x)),(((Ttriangle.b.y))),0.0f,Ttriangle.c2.x,Ttriangle.c2.y,Ttriangle.c2.z,Ttriangle.c2.w,Ttriangle.t2.x,1.0f - Ttriangle.t2.y,
			((Ttriangle.c.x)),(((Ttriangle.c.y))),0.0f,Ttriangle.c3.x,Ttriangle.c3.y,Ttriangle.c3.z,Ttriangle.c3.w,Ttriangle.t3.x,1.0f - Ttriangle.t3.y
		};

		glBindVertexArray(trianglevao);
		glBindBuffer(GL_ARRAY_BUFFER, trianglevbo);

		memcpy(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY), _buffer, sizeof(_buffer));
		glUnmapBuffer(GL_ARRAY_BUFFER);

		if (Ttriangle.fill == 0) {
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		}
		else {
			glDrawElements(GL_LINE_LOOP, 3, GL_UNSIGNED_INT, 0);
			glDrawElements(GL_POINTS, 3, GL_UNSIGNED_INT, 0);
		}

		return *this;
	}
	Renderer& Renderer::operator<<(Drawing::Rectangle Trectangle) {
		if (beginvertex == 1) {
			glEnd();
		}

		if (Trectangle.fill == 1) {
			float _buffer[] = {
				((Trectangle.a.x)),(((Trectangle.a.y))),0.0f,Trectangle.c1.x,Trectangle.c1.y,Trectangle.c1.z,Trectangle.c1.w,Trectangle.t1.x,1.0f - Trectangle.t1.y,
				((Trectangle.c.x)),(((Trectangle.a.y))),0.0f,Trectangle.c2.x,Trectangle.c2.y,Trectangle.c2.z,Trectangle.c2.w,Trectangle.t2.x,1.0f - Trectangle.t2.y,
				((Trectangle.a.x)),(((Trectangle.c.y))),0.0f,Trectangle.c3.x,Trectangle.c3.y,Trectangle.c3.z,Trectangle.c3.w,Trectangle.t3.x,1.0f - Trectangle.t3.y,
				((Trectangle.c.x)),(((Trectangle.c.y))),0.0f,Trectangle.c4.x,Trectangle.c4.y,Trectangle.c4.z,Trectangle.c4.w,Trectangle.t4.x,1.0f - Trectangle.t4.y
			};

			glBindVertexArray(rectvao);
			glBindBuffer(GL_ARRAY_BUFFER, rectvbo);

			memcpy(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY), _buffer, sizeof(_buffer));

			glUnmapBuffer(GL_ARRAY_BUFFER);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
		else {
			float _buffer[] = {
				((Trectangle.a.x)),(((Trectangle.a.y))),0.0f,Trectangle.c1.x,Trectangle.c1.y,Trectangle.c1.z,Trectangle.c1.w,Trectangle.t1.x,1.0f - Trectangle.t1.y,
				((Trectangle.c.x)),(((Trectangle.a.y))),0.0f,Trectangle.c2.x,Trectangle.c2.y,Trectangle.c2.z,Trectangle.c2.w,Trectangle.t2.x,1.0f - Trectangle.t2.y,
				((Trectangle.a.x)),(((Trectangle.c.y))),0.0f,Trectangle.c3.x,Trectangle.c3.y,Trectangle.c3.z,Trectangle.c3.w,Trectangle.t3.x,1.0f - Trectangle.t3.y,
				((Trectangle.c.x)),(((Trectangle.c.y))),0.0f,Trectangle.c4.x,Trectangle.c4.y,Trectangle.c4.z,Trectangle.c4.w,Trectangle.t4.x,1.0f - Trectangle.t4.y
			};

			glBindVertexArray(rectvao);
			glBindBuffer(GL_ARRAY_BUFFER, rectvbo);

			memcpy(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY), _buffer, sizeof(_buffer));

			glUnmapBuffer(GL_ARRAY_BUFFER);
			glDrawArrays(GL_LINE_LOOP, 0, 4);
			glDrawArrays(GL_POINTS, 0, 4);
		}

		return *this;
	}
	Renderer& Renderer::operator<<(Drawing::VertexArray& Tva) {
		if (beginvertex == 1) {
			glEnd();
		}
		/*
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		*/
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		/*
		Vec3 l = Tva[0].pos;
		glVertexPointer(3, GL_FLOAT, sizeof(Drawing::Vertex), &(Tva[0].pos));
		glColorPointer(4, GL_FLOAT, sizeof(Drawing::Vertex), &(Tva[0].col));
		glTexCoordPointer(2, GL_FLOAT, sizeof(Drawing::Vertex), &(Tva[0].tex));
		*/
		glBufferData(GL_ARRAY_BUFFER, sizeof(Drawing::Vertex) * Tva.getSize(), &(Tva[0]), GL_DYNAMIC_DRAW);
		//unsigned int _program;
		//glGetIntegerv(GL_CURRENT_PROGRAM, (int*)&_program);
		//glShadeModel(GL_SMOOTH);
		glDrawArrays(_glmodes[Tva.getType()], 0, Tva.getSize());
		//glUseProgram(_program);

		//glDisableClientState(GL_VERTEX_ARRAY);
		//glDisableClientState(GL_COLOR_ARRAY);
		//glDisableClientState(GL_TEXTURE_COORD_ARRAY);

		return *this;
	}

	void Renderer::LoadIdentity() {
		matrix = Matrix<float,4,4>();
		if (hglrc != NULL) {
			shader.setUniform(matrixlocation, matrix);
			if (cshader != NULL) {
				cshader->setUniform(shadermatrixlocation, matrix);
			}
		}
	}

	void Renderer::Combine(const Matrix<float, 4, 4>& Tmatrix) {
		matrix *= Tmatrix;
		if (hglrc != NULL) {
			shader.setUniform(matrixlocation, matrix);
			if (cshader != NULL) {
				cshader->setUniform(shadermatrixlocation, matrix);
			}
		}
	}

	void Renderer::UseSolidTexture() {
		glBindTexture(GL_TEXTURE_2D, white);
	}

	Renderer& Renderer::operator<< (Color Tcolor) {
		glClearColor(Tcolor.r() / 255.0f, Tcolor.b() / 255.0f, Tcolor.g() / 255.0f, Tcolor.a() / 255.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		return *this;
	}

	Renderer& Renderer::operator<< (Drawing::VertexArray::Type Tptype) {
		unsigned int _ptype;
		switch (Tptype) {
		case Drawing::VertexArray::Points: {
			_ptype = GL_POINTS;
			break;
		}
		case Drawing::VertexArray::Line: {
			_ptype = GL_LINES;
			break;
		}
		case Drawing::VertexArray::LineStrip: {
			_ptype = GL_LINE_STRIP;
			break;
		}
		case Drawing::VertexArray::Triangles: {
			_ptype = GL_TRIANGLES;
			break;
		}
		case Drawing::VertexArray::TriangleStrip: {
			_ptype = GL_TRIANGLE_STRIP;
			break;
		}
		case Drawing::VertexArray::TriangleFan: {
			_ptype = GL_TRIANGLE_FAN;
			break;
		}
		case Drawing::VertexArray::Quads: {
			_ptype = GL_QUADS;
			break;
		}
		}

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBegin(_ptype);
		beginvertex = 1;

		return *this;
	}

	Renderer& Renderer::operator<< (const Drawing::Vertex& Tvertex) {
		glVertex3fv((float*)&(Tvertex.pos));
		glColor4fv((float*)&(Tvertex.col));
		glTexCoord2fv((float*)&(Tvertex.tex));

		//float gg[9];
		//glGetFloatv(GL_CURRENT_, gg);

		return *this;
	}

	Renderer& Renderer::operator<< (_End) {
		if (beginvertex == 1) {
			glEnd();
		}

		return *this;
	}

	Renderer& Renderer::operator<< (Graphic& Tgraphic) {
		if (beginvertex == 1) {
			glEnd();
		}

		Tgraphic.getTexture().Bind();

		int _size = Tgraphic.getVertexArray().getSize();

		float* _buffer = new float[sizeof(Drawing::Vertex) * _size];
		memcpy(_buffer, &(Tgraphic.getVertexArray()[0]), sizeof(Drawing::Vertex) * _size);

		for (int i = 0;i < _size;i++) {
			//Vec3 l = Tgraphic.getVertexArray()[i].pos;
			(((((Drawing::Vertex*)_buffer)[i].pos.x /= renderwidth) -= 0.5f) *= 2.0f);
			(((((Drawing::Vertex*)_buffer)[i].pos.y /= renderheight) -= 0.5f) *= 2.0f) *= -1.0f;
		}

		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		glBufferData(GL_ARRAY_BUFFER, sizeof(Drawing::Vertex) * _size, _buffer, GL_DYNAMIC_DRAW);

		delete[] _buffer;

		glDrawArrays(_glmodes[Tgraphic.getVertexArray().getType()], 0, _size);

		return *this;
	}
	Renderer& Renderer::operator<< (const Sprite& Tsprite) {
		if (beginvertex == 1) {
			glEnd();
		}

		Tsprite.texture->Bind();

		if (Tsprite.trans.angle != 0.1) {
			float _width = (Tsprite.rect.c.x - Tsprite.rect.a.x)*Tsprite.trans.scale.x;
			float _height = (Tsprite.rect.c.y - Tsprite.rect.a.y)*Tsprite.trans.scale.y;

			float _cos = cos(radians_const(Tsprite.trans.angle - 90));
			float _sin = sin(radians_const(Tsprite.trans.angle - 180));
			//float _cos2 = cos(radians_const(Tsprite.trans.angle + 90));
			float _sin2 = sin(radians_const(Tsprite.trans.angle + 90));
			float _cos3 = cos(radians_const(Tsprite.trans.angle));
			//float _sin3 = sin(radians_const(Tsprite.trans.angle));

			Vec2 _rot_a_ = Vec2(_sin - _sin2, _cos - _cos3) * Tsprite.trans.origin;

			Vec2 _rot_b_ = Vec2(_sin2, -_cos) * _width;

			Vec2 _rot_c_ = Vec2(-_sin, _cos3) * _height;

			//float _ox = _width - Tsprite.trans.origin.x;
			//float _oy = _height - Tsprite.trans.origin.y;

			float _ax = ((((Tsprite.rect.a.x +				_rot_a_.x))));
			float _ay = ((((Tsprite.rect.a.y +		_rot_a_.y))));
			float _bx = ((((Tsprite.rect.a.x +			  ((_rot_a_.x + _rot_b_.x))))));
			float _by = ((((Tsprite.rect.a.y +	  ((_rot_a_.y + _rot_b_.y))))));
			float _cx = ((((Tsprite.rect.a.x +			  ((_rot_a_.x + _rot_c_.x))))));
			float _cy = ((((Tsprite.rect.a.y +	  ((_rot_a_.y + _rot_c_.y))))));
			float _dx = ((((Tsprite.rect.a.x +		 	  ((_rot_a_.x + _rot_b_.x + _rot_c_.x))))));
			float _dy = ((((Tsprite.rect.a.y  +	  ((_rot_a_.y + _rot_b_.y + _rot_c_.y))))));

			float _buffer[] = {
				_ax,_ay,0.0f,Tsprite.rect.c1.x,Tsprite.rect.c1.y,Tsprite.rect.c1.z,Tsprite.rect.c1.w,Tsprite.rect.t1.x,1.0f - Tsprite.rect.t1.y,
				_bx,_by,0.0f,Tsprite.rect.c2.x,Tsprite.rect.c2.y,Tsprite.rect.c2.z,Tsprite.rect.c2.w,Tsprite.rect.t2.x,1.0f - Tsprite.rect.t2.y,
				_cx,_cy,0.0f,Tsprite.rect.c3.x,Tsprite.rect.c3.y,Tsprite.rect.c3.z,Tsprite.rect.c3.w,Tsprite.rect.t3.x,1.0f - Tsprite.rect.t3.y,
				_dx,_dy,0.0f,Tsprite.rect.c4.x,Tsprite.rect.c4.y,Tsprite.rect.c4.z,Tsprite.rect.c4.w,Tsprite.rect.t4.x,1.0f - Tsprite.rect.t4.y
			};


			glBindVertexArray(rectvao);
			glBindBuffer(GL_ARRAY_BUFFER, rectvbo);

			memcpy(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY), _buffer, sizeof(_buffer));
			glUnmapBuffer(GL_ARRAY_BUFFER);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
		else {
			if (Tsprite.trans.scale.x == 1 && Tsprite.trans.scale.y == 1) {
				float _buffer[] = {
					(((Tsprite.rect.a.x - Tsprite.trans.origin.x))),((((Tsprite.rect.a.y - Tsprite.trans.origin.y)))),0.0f,Tsprite.rect.c1.x,Tsprite.rect.c1.y,Tsprite.rect.c1.z,Tsprite.rect.c1.w,Tsprite.rect.t1.x,1.0f - Tsprite.rect.t1.y,
					(((Tsprite.rect.c.x - Tsprite.trans.origin.x))),((((Tsprite.rect.a.y - Tsprite.trans.origin.y)))),0.0f,Tsprite.rect.c2.x,Tsprite.rect.c2.y,Tsprite.rect.c2.z,Tsprite.rect.c2.w,Tsprite.rect.t2.x,1.0f - Tsprite.rect.t2.y,
					(((Tsprite.rect.a.x - Tsprite.trans.origin.x))),((((Tsprite.rect.c.y - Tsprite.trans.origin.y)))),0.0f,Tsprite.rect.c3.x,Tsprite.rect.c3.y,Tsprite.rect.c3.z,Tsprite.rect.c3.w,Tsprite.rect.t3.x,1.0f - Tsprite.rect.t3.y,
					(((Tsprite.rect.c.x - Tsprite.trans.origin.x))),((((Tsprite.rect.c.y - Tsprite.trans.origin.y)))),0.0f,Tsprite.rect.c4.x,Tsprite.rect.c4.y,Tsprite.rect.c4.z,Tsprite.rect.c4.w,Tsprite.rect.t4.x,1.0f - Tsprite.rect.t4.y,
				};


				glBindVertexArray(rectvao);
				glBindBuffer(GL_ARRAY_BUFFER, rectvbo);

				memcpy(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY), _buffer, sizeof(_buffer));
				glUnmapBuffer(GL_ARRAY_BUFFER);

				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			}
			else {
				float _widtho = ((Tsprite.rect.c.x - Tsprite.rect.a.x) - Tsprite.trans.origin.x)*Tsprite.trans.scale.x;
				float _heighto = ((Tsprite.rect.c.y - Tsprite.rect.a.y) - Tsprite.trans.origin.y)*Tsprite.trans.scale.y;

				float _buffer[] = {
					(((Tsprite.rect.a.x - Tsprite.trans.origin.x*Tsprite.trans.scale.x))),((((Tsprite.rect.a.y - Tsprite.trans.origin.y*Tsprite.trans.scale.y)))),0.0f,Tsprite.rect.c1.x,Tsprite.rect.c1.y,Tsprite.rect.c1.z,Tsprite.rect.c1.w,Tsprite.rect.t1.x,1.0f - Tsprite.rect.t1.y,
					(((Tsprite.rect.a.x + _widtho))),((((Tsprite.rect.a.y - Tsprite.trans.origin.y*Tsprite.trans.scale.y)))),0.0f,Tsprite.rect.c2.x,Tsprite.rect.c2.y,Tsprite.rect.c2.z,Tsprite.rect.c2.w,Tsprite.rect.t2.x,1.0f - Tsprite.rect.t2.y,
					(((Tsprite.rect.a.x - Tsprite.trans.origin.x*Tsprite.trans.scale.x))),((((Tsprite.rect.a.y + _heighto)))),0.0f,Tsprite.rect.c3.x,Tsprite.rect.c3.y,Tsprite.rect.c3.z,Tsprite.rect.c3.w,Tsprite.rect.t3.x,1.0f - Tsprite.rect.t3.y,
					(((Tsprite.rect.a.x + _widtho))),((((Tsprite.rect.a.y + _heighto)))),0.0f,Tsprite.rect.c4.x,Tsprite.rect.c4.y,Tsprite.rect.c4.z,Tsprite.rect.c4.w,Tsprite.rect.t4.x,1.0f - Tsprite.rect.t4.y,
				};


				glBindVertexArray(rectvao);
				glBindBuffer(GL_ARRAY_BUFFER, rectvbo);

				memcpy(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY), _buffer, sizeof(_buffer));
				glUnmapBuffer(GL_ARRAY_BUFFER);

				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			}
		}

		return *this;
	}

	unsigned char hexchar(char Tchar) {
		return ((Tchar == '0') ? 0 :
			(Tchar == '1') ? 1 :
			(Tchar == '2') ? 2 :
			(Tchar == '3') ? 3 :
			(Tchar == '4') ? 4 :
			(Tchar == '5') ? 5 :
			(Tchar == '6') ? 6 :
			(Tchar == '7') ? 7 :
			(Tchar == '8') ? 8 :
			(Tchar == '9') ? 9 :
			(Tchar == 'A') ? 10 :
			(Tchar == 'B') ? 11 :
			(Tchar == 'C') ? 12 :
			(Tchar == 'D') ? 13 :
			(Tchar == 'E') ? 14 :
			(Tchar == 'F') ? 15 :
			(Tchar == 'a') ? 10 :
			(Tchar == 'b') ? 11 :
			(Tchar == 'c') ? 12 :
			(Tchar == 'd') ? 13 :
			(Tchar == 'e') ? 14 :
			(Tchar == 'f') ? 15 : 16);
	}

	enum TextFunc {
		None,
		Func,
		ColorTag,
		ColorHex
	};

	Renderer& Renderer::operator<< (const Text& Ttext) {
		int _length = Ttext.string.length();
		TextFunc _Tfunc = TextFunc::None;
		int _Tpos = 0;
		int _Tline = 0;
		int _Tex = 0;

		std::string _collecttext;
		int _hexl = 0;

		Color _Tcolor(255, 255, 255, 255);
		Vec4 _color = _Tcolor;

		int _Txpos = 0;

		bool _Tdraw = 0;

		bool _allowbackslash = 0;

		Ttext.font->getTex()->Bind();

		for (int i = 0;i < _length;i++) {
			if (Ttext.string[i] == '\n') {
				_Tline++;
				//_Tex++;
				_Tpos = 0;
				_Txpos = 0;
			}
			if (Ttext.string[i] == '~') {
				if (_Tfunc == TextFunc::Func) {
					_Tfunc = TextFunc::None;
				}
				else {
					_Tfunc = TextFunc::Func;
				}
			}
			_Tdraw = _Tfunc == (TextFunc::None);
			if ((Ttext.string[i] != ' ') && (Ttext.string[i] != '\n') && (_Tdraw)) {
				float Rx = Ttext.pos.x + _Txpos;
				float Ry = Ttext.pos.y + (_Tline*(Ttext.font->getFullHeight() + Ttext.font->getSepWidth()));
				//Shader MShader("Texture.vs", "Texture.fs");
				//std::cout << (TSH) << "," << (DrawTargetHeight) << "," << DrawTarget << "," << (float(DrawTargetHeight) / (ScreenH)) << "\n";
				float Rw = float(((Ttext.font->getWidth(Ttext.string[i]))));
				float Rh = float(((Ttext.font->getFullHeight())));
				float RTx = float(((Ttext.string[i] - Ttext.font->getStartChar()) % 16) * Ttext.font->getFullWidth()) / Ttext.font->getTex()->getSize().x;
				float RTy = float(int((Ttext.string[i] - Ttext.font->getStartChar()) / 16) * Ttext.font->getFullHeight()) / Ttext.font->getTex()->getSize().y;
				float RTw = float(Ttext.font->getWidth(Ttext.string[i])) / Ttext.font->getTex()->getSize().x;
				float RTh = (float(Ttext.font->getFullHeight()) / Ttext.font->getTex()->getSize().y);

				float _buffer[] = {
					// positions				// colors					// texture coords
					(Rx),  Ry,				0, _color.x, _color.y, _color.z, _color.w,	RTx		 ,1.0f - (RTy),					// top left
					((Rx + Rw)), Ry,		0, _color.x, _color.y, _color.z, _color.w,	RTx + RTw,1.0f - (RTy),				// top right
					(Rx),  Ry + Rh,			0, _color.x, _color.y, _color.z, _color.w,	RTx		 ,1.0f - (RTy + RTh),		// bottom left
					((Rx + Rw)), Ry + Rh,	0, _color.x, _color.y, _color.z, _color.w,	RTx + RTw,1.0f - (RTy + RTh)	// bottom right
					 
				};
				//*this << Sprite(*Ttext.font->getTex(), ((Ttext.string[i] - Ttext.font->getStartChar()) % 16) * Ttext.font->getFullWidth(), int((Ttext.string[i] - Ttext.font->getStartChar()) / 16) * Ttext.font->getFullHeight(), Ttext.font->getWidth(Ttext.string[i]), Ttext.font->getFullHeight(), Rx, Ry, Rw, Rh);
				glBindVertexArray(rectvao);
				glBindBuffer(GL_ARRAY_BUFFER, rectvbo);

				memcpy(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY), _buffer, sizeof(_buffer));
				glUnmapBuffer(GL_ARRAY_BUFFER);

				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

				_Txpos = _Txpos + (Ttext.font->getWidth(Ttext.string[i]) + Ttext.font->getSepWidth());
				_Tpos++;

				_collecttext += Ttext.string[i];
			}
			else {
				if (Ttext.string[i] == ' ') {
					_Txpos = _Txpos + Ttext.font->getSpaceWidth();
					_Tpos++;
					_collecttext += Ttext.string[i];
					//_Tfunc = _Tfunc + text[i];
					//_Tex++;
				}
				if (_Tfunc == TextFunc::Func) {
					switch (Ttext.string[i]) {
					default: {
						_Tfunc = TextFunc::None;
						break;
					}
					case '~': {
						break;
					}
					case '&': {
						_Tfunc = TextFunc::ColorTag;
						break;
					}
							  //hex input
					case '#': {
						_Tfunc = TextFunc::ColorHex;
						break;
					}
					}
					continue;
				}
				if (_Tfunc == TextFunc::ColorTag) {
					switch (Ttext.string[i]) {
					default: {
						_Tcolor = Color(255, 255, 255, 255);
						_Tfunc = TextFunc::None;
						break;
					}
					case '0': {
						_Tcolor = Color(0, 0, 0, 255);
						_Tfunc = TextFunc::None;
						break;
					}
					case '~': {
						break;
					}
					case '1': {
						_Tcolor = Color(255, 255, 0, 255);
						_Tfunc = TextFunc::None;
						break;
					}
					case '2': {
						_Tcolor = Color(0, 255, 0, 255);
						_Tfunc = TextFunc::None;
						break;
					}
					case '3': {
						_Tcolor = Color(0, 255, 255, 255);
						_Tfunc = TextFunc::None;
						break;
					}
					case '4': {
						_Tcolor = Color(0, 0, 255, 255);
						_Tfunc = TextFunc::None;
						break;
					}
					case '5': {
						_Tcolor = Color(255, 0, 255, 255);
						_Tfunc = TextFunc::None;
						break;
					}
					case '6': {
						_Tcolor = Color(255, 0, 0, 255);
						_Tfunc = TextFunc::None;
						break;
					}
					case '7': {
						_Tcolor = Color(63, 63, 63, 255);
						_Tfunc = TextFunc::None;
						break;
					}
					case '8': {
						_Tcolor = Color(127, 127, 127, 255);
						_Tfunc = TextFunc::None;
						break;
					}
					case '9': {
						_Tcolor = Color(191, 191, 191, 255);
						_Tfunc = TextFunc::None;
						break;
					}
					case 'G': {
						_Tcolor = Color(0, 255, 0, 255);
						_Tfunc = TextFunc::None;
						break;
					}
					}
					_color = _Tcolor;
					continue;
				}
				if (_Tfunc == TextFunc::ColorHex) {
					if (_hexl == 0) {
						_Tcolor = Color(0, 0, 0, 255);
					}
					_hexl++;
					if (_hexl == 1) {
						_Tcolor.r() += hexchar(Ttext.string[i]) * 16;
					}
					if (_hexl == 2) {
						_Tcolor.r() += hexchar(Ttext.string[i]) * 1;
					}
					if (_hexl == 3) {
						_Tcolor.g() += hexchar(Ttext.string[i]) * 16;
					}
					if (_hexl == 4) {
						_Tcolor.g() += hexchar(Ttext.string[i]) * 1;
					}
					if (_hexl == 5) {
						_Tcolor.b() += hexchar(Ttext.string[i]) * 16;
					}
					if (_hexl == 6) {
						_Tcolor.b() += hexchar(Ttext.string[i]) * 1;
						_Tfunc = TextFunc::None;
						_hexl = 0;
						_color = _Tcolor;
					}
				}
			}
		}
		return *this;
	}

	Renderer& Renderer::operator<< (const ModernText& Ttext) {
		// Activate corresponding render state
		moderntext_shader.Use();
		const int scale = 1;
		int posx = Ttext.pos.x;
		int posy = Ttext.pos.y;
		//moderntext_shader.setUniform("textColor", Ttext.color);
		Vec4 Tcolor = Ttext.color;


		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, Ttext.font->getTexture());
		glBindVertexArray(rectvao);
		//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		// Iterate through all characters
		std::string::const_iterator c;
		for (c = Ttext.string.begin(); c != Ttext.string.end(); c++)
		{
			ModernGlyph ch = getModernGlyphList()[*c];

			float xpos = posx + ch.Bearing.x * scale;
			float ypos = posy - (ch.Size.y) * scale;

			float w = ch.Size.x * scale;
			float h = ch.Size.y * scale;
			// Update VBO for each character
			float vertices[] = {
				xpos,     ypos,			0,Tcolor.x, Tcolor.y, Tcolor.z, Tcolor.w,0.0, 0.0 ,
				xpos,     ypos + h,		0,Tcolor.x, Tcolor.y, Tcolor.z, Tcolor.w, 0.0, 1.0 ,
				xpos + w, ypos,			0,Tcolor.x, Tcolor.y, Tcolor.z, Tcolor.w, 1.0, 0.0 ,
				xpos + w, ypos + h,		0,Tcolor.x, Tcolor.y, Tcolor.z, Tcolor.w, 1.0, 1.0
			};

			/*float vertices[] = {
				xpos	, ypos		,	0.0, 0.0,
				xpos	, ypos + h	,	0.0, 1.0,
				xpos + w, ypos		,	1.0, 0.0,
				xpos + w, ypos + h	,	1.0, 1.0
			};*/

			/*
			float _buffer[] = {
			// positions				// colors					// texture coords
			(Rx),  Ry,				0, _color.x, _color.y, _color.z, _color.w,	RTx		 ,1.0f - (RTy),					// top left
			((Rx + Rw)), Ry,		0, _color.x, _color.y, _color.z, _color.w,	RTx + RTw,1.0f - (RTy),				// top right
			(Rx),  Ry + Rh,			0, _color.x, _color.y, _color.z, _color.w,	RTx		 ,1.0f - (RTy + RTh),		// bottom left
			((Rx + Rw)), Ry + Rh,	0, _color.x, _color.y, _color.z, _color.w,	RTx + RTw,1.0f - (RTy + RTh)	// bottom right

			};
			*/
	
			char log[1000];
			moderntext_shader.getLog(OpenGL::Shader::ShaderType::Fragment, log, 1000);
			char loga[1000];
			moderntext_shader.getLog(OpenGL::Shader::ShaderType::Vertex, loga, 1000);

			// Render glyph texture over quad
			glBindTexture(GL_TEXTURE_2D, ch.TextureID);
			// Update content of VBO memory
			glBindBuffer(GL_ARRAY_BUFFER, rectvbo);
			//glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData
			memcpy(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY), vertices, sizeof(vertices));
			glUnmapBuffer(GL_ARRAY_BUFFER);
			//glBindBuffer(GL_ARRAY_BUFFER, 0);
			// Render quad
			//glDrawArrays(GL_TRIANGLES, 0, 6);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
			posx += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
		}
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
		shader.Use();
		return *this;
	}
}