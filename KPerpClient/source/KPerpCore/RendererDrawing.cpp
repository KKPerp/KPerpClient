
#include <KPerpCore/Renderer.hpp>
#include <KPerpCore/Window.hpp>
#include <KPerpCore/Drawing.hpp>

//#include <KPerpExt/KGUI/kgui.hpp>

#include <string.h>
#define colorinta(_cl_r,_cl_g,_cl_b,_cl_a) (_cl_r) + ((_cl_g) * 256U) + ((_cl_b) * 65536U) + ((_cl_a) * 16777216U)

namespace kp {
	unsigned int _glmodes[] = {
		GL_POINTS,GL_LINES,GL_LINE_STRIP,
		GL_TRIANGLES,GL_TRIANGLE_STRIP,GL_TRIANGLE_FAN,GL_QUADS
	};

	void Renderer::Clear(Color Tcolor) {
		if (!hglrc) {
			if (!hwnd) {
				renderer.clear(Tcolor.uint());
			}
			else {
				renderer.clear(Tcolor.ruint());
			}
			return;
		}

		if (beginvertex == 1) {
			glEnd();
		}
		glClearColor(Tcolor.r() / 255.0f, Tcolor.g() / 255.0f, Tcolor.b() / 255.0f, Tcolor.a() / 255.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	Renderer& Renderer::operator<< (Drawing::Line Tline) {
		if (!hglrc) {
			if (!hwnd) {
				if (Tline.c1 == Tline.c2) {
					renderer.line(Tline.a.x, Tline.a.y, Tline.b.x, Tline.b.y, (unsigned int)(Tline.c1.x * 255) + (unsigned int)(Tline.c1.y * (65280U)) + (unsigned int)(Tline.c1.z * 16711680U) + (unsigned int)(Tline.c1.w * 4278190080U));
				}
				else {
					renderer.line(Tline.a.x, Tline.a.y, Tline.b.x, Tline.b.y,
						(unsigned int)(Tline.c1.x * 255) + (unsigned int)(Tline.c1.y * (65280U)) + (unsigned int)(Tline.c1.z * 16711680U) + (unsigned int)(Tline.c1.w * 4278190080U),
						(unsigned int)(Tline.c2.x * 255) + (unsigned int)(Tline.c2.y * (65280U)) + (unsigned int)(Tline.c2.z * 16711680U) + (unsigned int)(Tline.c2.w * 4278190080U));
				}
			}
			else {
				if (Tline.c1 == Tline.c2) {
					renderer.line(Tline.a.x, Tline.a.y, Tline.b.x, Tline.b.y, (unsigned int)(Tline.c1.z * 255) + (unsigned int)(Tline.c1.y * (65280U)) + (unsigned int)(Tline.c1.x * 16711680U) + (unsigned int)(Tline.c1.w * 4278190080U));
				}
				else {
					renderer.line(Tline.a.x, Tline.a.y, Tline.b.x, Tline.b.y,
						(unsigned int)(Tline.c1.z * 255) + (unsigned int)(Tline.c1.y * (65280U)) + (unsigned int)(Tline.c1.x * 16711680U) + (unsigned int)(Tline.c1.w * 4278190080U),
						(unsigned int)(Tline.c2.z * 255) + (unsigned int)(Tline.c2.y * (65280U)) + (unsigned int)(Tline.c2.x * 16711680U) + (unsigned int)(Tline.c2.w * 4278190080U));
				}
			}
			return *this;
		}
		if (beginvertex == 1) {
			glEnd();
		}

		float _buffer[] = {
			((Tline.a.x)),(((Tline.a.y))),((Tline.a.z)),Tline.c1.x,Tline.c1.y,Tline.c1.z,Tline.c1.w,Tline.t1.x,1.0f - Tline.t1.y,
			((Tline.b.x)),(((Tline.b.y))),((Tline.b.z)),Tline.c2.x,Tline.c2.y,Tline.c2.z,Tline.c2.w,Tline.t2.x,1.0f - Tline.t2.y,
		};

		glBindVertexArray(linevao);
		glBindBuffer(GL_ARRAY_BUFFER, linevbo);

		memcpy(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY), _buffer, sizeof(_buffer));
		glUnmapBuffer(GL_ARRAY_BUFFER);

		glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, 0);

		return *this;
	}
	Renderer& Renderer::operator<<(Drawing::Triangle Ttriangle) {
		if (!hglrc) {
			if (Ttriangle.fill) {
				if (!hwnd) {
					if ((Ttriangle.c1 == Ttriangle.c2) && (Ttriangle.c1 == Ttriangle.c3)) {
						renderer.triangle(Ttriangle.a.x, Ttriangle.a.y, Ttriangle.b.x, Ttriangle.b.y, Ttriangle.c.x, Ttriangle.c.y, (unsigned int)(Ttriangle.c1.x * 255) + (unsigned int)(Ttriangle.c1.y * (65280U)) + (unsigned int)(Ttriangle.c1.z * 16711680U) + (unsigned int)(Ttriangle.c1.w * 4278190080U));
					}
					else {
						renderer.triangle(Ttriangle.a.x, Ttriangle.a.y, Ttriangle.b.x, Ttriangle.b.y, Ttriangle.c.x, Ttriangle.c.y,
							(unsigned int)(Ttriangle.c1.x * 255) + (unsigned int)(Ttriangle.c1.y * (65280U)) + (unsigned int)(Ttriangle.c1.z * 16711680U) + (unsigned int)(Ttriangle.c1.w * 4278190080U),
							(unsigned int)(Ttriangle.c2.x * 255) + (unsigned int)(Ttriangle.c2.y * (65280U)) + (unsigned int)(Ttriangle.c2.z * 16711680U) + (unsigned int)(Ttriangle.c2.w * 4278190080U),
							(unsigned int)(Ttriangle.c3.x * 255) + (unsigned int)(Ttriangle.c3.y * (65280U)) + (unsigned int)(Ttriangle.c3.z * 16711680U) + (unsigned int)(Ttriangle.c3.w * 4278190080U));
					}
				}
				else {
					if ((Ttriangle.c1 == Ttriangle.c2) && (Ttriangle.c1 == Ttriangle.c3)) {
						renderer.triangle(Ttriangle.a.x, Ttriangle.a.y, Ttriangle.b.x, Ttriangle.b.y, Ttriangle.c.x, Ttriangle.c.y, (unsigned int)(Ttriangle.c1.z * 255) + (unsigned int)(Ttriangle.c1.y * (65280U)) + (unsigned int)(Ttriangle.c1.x * 16711680U) + (unsigned int)(Ttriangle.c1.w * 4278190080U));
					}
					else {
						renderer.triangle(Ttriangle.a.x, Ttriangle.a.y, Ttriangle.b.x, Ttriangle.b.y, Ttriangle.c.x, Ttriangle.c.y,
							(unsigned int)(Ttriangle.c1.z * 255) + (unsigned int)(Ttriangle.c1.y * (65280U)) + (unsigned int)(Ttriangle.c1.x * 16711680U) + (unsigned int)(Ttriangle.c1.w * 4278190080U),
							(unsigned int)(Ttriangle.c2.z * 255) + (unsigned int)(Ttriangle.c2.y * (65280U)) + (unsigned int)(Ttriangle.c2.x * 16711680U) + (unsigned int)(Ttriangle.c2.w * 4278190080U),
							(unsigned int)(Ttriangle.c3.z * 255) + (unsigned int)(Ttriangle.c3.y * (65280U)) + (unsigned int)(Ttriangle.c3.x * 16711680U) + (unsigned int)(Ttriangle.c3.w * 4278190080U));
					};
				}
			}
			else {
				if (!hwnd) {
					if ((Ttriangle.c1 == Ttriangle.c2) && (Ttriangle.c1 == Ttriangle.c3)) {
						renderer.line(Ttriangle.a.x, Ttriangle.a.y, Ttriangle.b.x, Ttriangle.b.y, (unsigned int)(Ttriangle.c1.x * 255) + (unsigned int)(Ttriangle.c1.y * (65280U)) + (unsigned int)(Ttriangle.c1.z * 16711680U) + (unsigned int)(Ttriangle.c1.w * 4278190080U));
						renderer.line(Ttriangle.b.x, Ttriangle.b.y, Ttriangle.c.x, Ttriangle.c.y, (unsigned int)(Ttriangle.c2.x * 255) + (unsigned int)(Ttriangle.c2.y * (65280U)) + (unsigned int)(Ttriangle.c2.z * 16711680U) + (unsigned int)(Ttriangle.c2.w * 4278190080U));
						renderer.line(Ttriangle.c.x, Ttriangle.c.y, Ttriangle.a.x, Ttriangle.a.y, (unsigned int)(Ttriangle.c3.x * 255) + (unsigned int)(Ttriangle.c3.y * (65280U)) + (unsigned int)(Ttriangle.c3.z * 16711680U) + (unsigned int)(Ttriangle.c3.w * 4278190080U));
					}
					else {
						renderer.line(Ttriangle.a.x, Ttriangle.a.y, Ttriangle.b.x, Ttriangle.b.y,
							(unsigned int)(Ttriangle.c1.x * 255) + (unsigned int)(Ttriangle.c1.y * (65280U)) + (unsigned int)(Ttriangle.c1.z * 16711680U) + (unsigned int)(Ttriangle.c1.w * 4278190080U),
							(unsigned int)(Ttriangle.c2.x * 255) + (unsigned int)(Ttriangle.c2.y * (65280U)) + (unsigned int)(Ttriangle.c2.z * 16711680U) + (unsigned int)(Ttriangle.c2.w * 4278190080U));
						renderer.line(Ttriangle.b.x, Ttriangle.b.y, Ttriangle.c.x, Ttriangle.c.y,
							(unsigned int)(Ttriangle.c2.x * 255) + (unsigned int)(Ttriangle.c2.y * (65280U)) + (unsigned int)(Ttriangle.c2.z * 16711680U) + (unsigned int)(Ttriangle.c2.w * 4278190080U),
							(unsigned int)(Ttriangle.c3.x * 255) + (unsigned int)(Ttriangle.c3.y * (65280U)) + (unsigned int)(Ttriangle.c3.z * 16711680U) + (unsigned int)(Ttriangle.c3.w * 4278190080U));
						renderer.line(Ttriangle.c.x, Ttriangle.c.y, Ttriangle.a.x, Ttriangle.a.y,
							(unsigned int)(Ttriangle.c3.x * 255) + (unsigned int)(Ttriangle.c3.y * (65280U)) + (unsigned int)(Ttriangle.c3.z * 16711680U) + (unsigned int)(Ttriangle.c3.w * 4278190080U),
							(unsigned int)(Ttriangle.c1.x * 255) + (unsigned int)(Ttriangle.c1.y * (65280U)) + (unsigned int)(Ttriangle.c1.z * 16711680U) + (unsigned int)(Ttriangle.c1.w * 4278190080U));
					}
				}
				else {
					if ((Ttriangle.c1 == Ttriangle.c2) && (Ttriangle.c1 == Ttriangle.c3)) {
						renderer.line(Ttriangle.a.x, Ttriangle.a.y, Ttriangle.b.x, Ttriangle.b.y, (unsigned int)(Ttriangle.c1.z * 255) + (unsigned int)(Ttriangle.c1.y * (65280U)) + (unsigned int)(Ttriangle.c1.x * 16711680U) + (unsigned int)(Ttriangle.c1.w * 4278190080U));
						renderer.line(Ttriangle.b.x, Ttriangle.b.y, Ttriangle.c.x, Ttriangle.c.y, (unsigned int)(Ttriangle.c2.z * 255) + (unsigned int)(Ttriangle.c2.y * (65280U)) + (unsigned int)(Ttriangle.c2.x * 16711680U) + (unsigned int)(Ttriangle.c2.w * 4278190080U));
						renderer.line(Ttriangle.c.x, Ttriangle.c.y, Ttriangle.a.x, Ttriangle.a.y, (unsigned int)(Ttriangle.c3.z * 255) + (unsigned int)(Ttriangle.c3.y * (65280U)) + (unsigned int)(Ttriangle.c3.x * 16711680U) + (unsigned int)(Ttriangle.c3.w * 4278190080U));
					}
					else {
						renderer.line(Ttriangle.a.x, Ttriangle.a.y, Ttriangle.b.x, Ttriangle.b.y,
							(unsigned int)(Ttriangle.c1.z * 255) + (unsigned int)(Ttriangle.c1.y * (65280U)) + (unsigned int)(Ttriangle.c1.x * 16711680U) + (unsigned int)(Ttriangle.c1.w * 4278190080U),
							(unsigned int)(Ttriangle.c2.z * 255) + (unsigned int)(Ttriangle.c2.y * (65280U)) + (unsigned int)(Ttriangle.c2.x * 16711680U) + (unsigned int)(Ttriangle.c2.w * 4278190080U));
						renderer.line(Ttriangle.b.x, Ttriangle.b.y, Ttriangle.c.x, Ttriangle.c.y,
							(unsigned int)(Ttriangle.c2.z * 255) + (unsigned int)(Ttriangle.c2.y * (65280U)) + (unsigned int)(Ttriangle.c2.x * 16711680U) + (unsigned int)(Ttriangle.c2.w * 4278190080U),
							(unsigned int)(Ttriangle.c3.z * 255) + (unsigned int)(Ttriangle.c3.y * (65280U)) + (unsigned int)(Ttriangle.c3.x * 16711680U) + (unsigned int)(Ttriangle.c3.w * 4278190080U));
						renderer.line(Ttriangle.c.x, Ttriangle.c.y, Ttriangle.a.x, Ttriangle.a.y,
							(unsigned int)(Ttriangle.c3.z * 255) + (unsigned int)(Ttriangle.c3.y * (65280U)) + (unsigned int)(Ttriangle.c3.x * 16711680U) + (unsigned int)(Ttriangle.c3.w * 4278190080U),
							(unsigned int)(Ttriangle.c1.z * 255) + (unsigned int)(Ttriangle.c1.y * (65280U)) + (unsigned int)(Ttriangle.c1.x * 16711680U) + (unsigned int)(Ttriangle.c1.w * 4278190080U));
					};
				}
			}
			return *this;
		}
		if (beginvertex == 1) {
			glEnd();
		}

		//glBindTexture(GL_TEXTURE_2D, white);

		float _buffer[] = {
			((Ttriangle.a.x)),(((Ttriangle.a.y))),((Ttriangle.a.z)),Ttriangle.c1.x,Ttriangle.c1.y,Ttriangle.c1.z,Ttriangle.c1.w,Ttriangle.t1.x,1.0f - Ttriangle.t1.y,
			((Ttriangle.b.x)),(((Ttriangle.b.y))),((Ttriangle.b.z)),Ttriangle.c2.x,Ttriangle.c2.y,Ttriangle.c2.z,Ttriangle.c2.w,Ttriangle.t2.x,1.0f - Ttriangle.t2.y,
			((Ttriangle.c.x)),(((Ttriangle.c.y))),((Ttriangle.c.z)),Ttriangle.c3.x,Ttriangle.c3.y,Ttriangle.c3.z,Ttriangle.c3.w,Ttriangle.t3.x,1.0f - Ttriangle.t3.y
		};

		glBindVertexArray(trianglevao);
		glBindBuffer(GL_ARRAY_BUFFER, trianglevbo);

		memcpy(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY), _buffer, sizeof(_buffer));
		glUnmapBuffer(GL_ARRAY_BUFFER);

		if (Ttriangle.fill) {
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		}
		else {
			glDrawElements(GL_LINE_LOOP, 3, GL_UNSIGNED_INT, 0);
			glDrawElements(GL_POINTS, 3, GL_UNSIGNED_INT, 0);
		}

		return *this;
	}
	Renderer& Renderer::operator<<(Drawing::Rectangle Trectangle) {
		if (!hglrc) {
			if (Trectangle.fill) {
				if (!hwnd) {
					if ((Trectangle.c1 == Trectangle.c2) && (Trectangle.c1 == Trectangle.c3)) {
						renderer.rectangle(Trectangle.a.x, Trectangle.a.y, Trectangle.c.x, Trectangle.c.y, (unsigned int)(Trectangle.c1.x * 255) + (unsigned int)(Trectangle.c1.y * (65280U)) + (unsigned int)(Trectangle.c1.z * 16711680U) + (unsigned int)(Trectangle.c1.w * 4278190080U));
					}
					else {
						renderer.rectangle(Trectangle.a.x, Trectangle.a.y, Trectangle.c.x, Trectangle.c.y,
							(unsigned int)(Trectangle.c1.x * 255) + (unsigned int)(Trectangle.c1.y * (65280U)) + (unsigned int)(Trectangle.c1.z * 16711680U) + (unsigned int)(Trectangle.c1.w * 4278190080U),
							(unsigned int)(Trectangle.c2.x * 255) + (unsigned int)(Trectangle.c2.y * (65280U)) + (unsigned int)(Trectangle.c2.z * 16711680U) + (unsigned int)(Trectangle.c2.w * 4278190080U),
							(unsigned int)(Trectangle.c3.x * 255) + (unsigned int)(Trectangle.c3.y * (65280U)) + (unsigned int)(Trectangle.c3.z * 16711680U) + (unsigned int)(Trectangle.c3.w * 4278190080U),
							(unsigned int)(Trectangle.c4.x * 255) + (unsigned int)(Trectangle.c4.y * (65280U)) + (unsigned int)(Trectangle.c4.z * 16711680U) + (unsigned int)(Trectangle.c4.w * 4278190080U));
					}
				}
				else {
					if ((Trectangle.c1 == Trectangle.c2) && (Trectangle.c1 == Trectangle.c3)) {
						renderer.rectangle(Trectangle.a.x, Trectangle.a.y, Trectangle.c.x, Trectangle.c.y, (unsigned int)(Trectangle.c1.z * 255) + (unsigned int)(Trectangle.c1.y * (65280U)) + (unsigned int)(Trectangle.c1.x * 16711680U) + (unsigned int)(Trectangle.c1.w * 4278190080U));
					}
					else {
						renderer.rectangle(Trectangle.a.x, Trectangle.a.y, Trectangle.c.x, Trectangle.c.y,
							(unsigned int)(Trectangle.c1.z * 255) + (unsigned int)(Trectangle.c1.y * (65280U)) + (unsigned int)(Trectangle.c1.x * 16711680U) + (unsigned int)(Trectangle.c1.w * 4278190080U),
							(unsigned int)(Trectangle.c2.z * 255) + (unsigned int)(Trectangle.c2.y * (65280U)) + (unsigned int)(Trectangle.c2.x * 16711680U) + (unsigned int)(Trectangle.c2.w * 4278190080U),
							(unsigned int)(Trectangle.c3.z * 255) + (unsigned int)(Trectangle.c3.y * (65280U)) + (unsigned int)(Trectangle.c3.x * 16711680U) + (unsigned int)(Trectangle.c3.w * 4278190080U),
							(unsigned int)(Trectangle.c4.z * 255) + (unsigned int)(Trectangle.c4.y * (65280U)) + (unsigned int)(Trectangle.c4.x * 16711680U) + (unsigned int)(Trectangle.c4.w * 4278190080U));
					};
				}
			}
			else {
				if (!hwnd) {
					if ((Trectangle.c1 == Trectangle.c2) && (Trectangle.c1 == Trectangle.c3)) {
						renderer.line(Trectangle.a.x, Trectangle.a.y, Trectangle.c.x, Trectangle.a.y, (unsigned int)(Trectangle.c1.x * 255) + (unsigned int)(Trectangle.c1.y * (65280U)) + (unsigned int)(Trectangle.c1.z * 16711680U) + (unsigned int)(Trectangle.c1.w * 4278190080U));
						renderer.line(Trectangle.c.x, Trectangle.a.y, Trectangle.c.x, Trectangle.c.y, (unsigned int)(Trectangle.c2.x * 255) + (unsigned int)(Trectangle.c2.y * (65280U)) + (unsigned int)(Trectangle.c2.z * 16711680U) + (unsigned int)(Trectangle.c2.w * 4278190080U));
						renderer.line(Trectangle.c.x, Trectangle.c.y, Trectangle.a.x, Trectangle.c.y, (unsigned int)(Trectangle.c3.x * 255) + (unsigned int)(Trectangle.c3.y * (65280U)) + (unsigned int)(Trectangle.c3.z * 16711680U) + (unsigned int)(Trectangle.c3.w * 4278190080U));
						renderer.line(Trectangle.a.x, Trectangle.c.y, Trectangle.a.x, Trectangle.a.y, (unsigned int)(Trectangle.c4.x * 255) + (unsigned int)(Trectangle.c4.y * (65280U)) + (unsigned int)(Trectangle.c4.z * 16711680U) + (unsigned int)(Trectangle.c4.w * 4278190080U));
					}
					else {
						renderer.line(Trectangle.a.x, Trectangle.a.y, Trectangle.c.x, Trectangle.a.y,
							(unsigned int)(Trectangle.c1.x * 255) + (unsigned int)(Trectangle.c1.y * (65280U)) + (unsigned int)(Trectangle.c1.z * 16711680U) + (unsigned int)(Trectangle.c1.w * 4278190080U),
							(unsigned int)(Trectangle.c2.x * 255) + (unsigned int)(Trectangle.c2.y * (65280U)) + (unsigned int)(Trectangle.c2.z * 16711680U) + (unsigned int)(Trectangle.c2.w * 4278190080U));
						renderer.line(Trectangle.c.x, Trectangle.a.y, Trectangle.c.x, Trectangle.c.y,
							(unsigned int)(Trectangle.c2.x * 255) + (unsigned int)(Trectangle.c2.y * (65280U)) + (unsigned int)(Trectangle.c2.z * 16711680U) + (unsigned int)(Trectangle.c2.w * 4278190080U),
							(unsigned int)(Trectangle.c4.x * 255) + (unsigned int)(Trectangle.c4.y * (65280U)) + (unsigned int)(Trectangle.c4.z * 16711680U) + (unsigned int)(Trectangle.c4.w * 4278190080U));
						renderer.line(Trectangle.c.x, Trectangle.c.y, Trectangle.a.x, Trectangle.c.y,
							(unsigned int)(Trectangle.c4.x * 255) + (unsigned int)(Trectangle.c4.y * (65280U)) + (unsigned int)(Trectangle.c4.z * 16711680U) + (unsigned int)(Trectangle.c4.w * 4278190080U),
							(unsigned int)(Trectangle.c3.x * 255) + (unsigned int)(Trectangle.c3.y * (65280U)) + (unsigned int)(Trectangle.c3.z * 16711680U) + (unsigned int)(Trectangle.c3.w * 4278190080U));
						renderer.line(Trectangle.a.x, Trectangle.c.y, Trectangle.a.x, Trectangle.a.y,
							(unsigned int)(Trectangle.c3.x * 255) + (unsigned int)(Trectangle.c3.y * (65280U)) + (unsigned int)(Trectangle.c3.z * 16711680U) + (unsigned int)(Trectangle.c3.w * 4278190080U),
							(unsigned int)(Trectangle.c1.x * 255) + (unsigned int)(Trectangle.c1.y * (65280U)) + (unsigned int)(Trectangle.c1.z * 16711680U) + (unsigned int)(Trectangle.c1.w * 4278190080U));
					}
				}
				else {
					if ((Trectangle.c1 == Trectangle.c2) && (Trectangle.c1 == Trectangle.c3)) {
						renderer.line(Trectangle.a.x, Trectangle.a.y, Trectangle.c.x, Trectangle.a.y, (unsigned int)(Trectangle.c1.z * 255) + (unsigned int)(Trectangle.c1.y * (65280U)) + (unsigned int)(Trectangle.c1.x * 16711680U) + (unsigned int)(Trectangle.c1.w * 4278190080U));
						renderer.line(Trectangle.c.x, Trectangle.a.y, Trectangle.c.x, Trectangle.c.y, (unsigned int)(Trectangle.c2.z * 255) + (unsigned int)(Trectangle.c2.y * (65280U)) + (unsigned int)(Trectangle.c2.x * 16711680U) + (unsigned int)(Trectangle.c2.w * 4278190080U));
						renderer.line(Trectangle.c.x, Trectangle.c.y, Trectangle.a.x, Trectangle.c.y, (unsigned int)(Trectangle.c3.z * 255) + (unsigned int)(Trectangle.c3.y * (65280U)) + (unsigned int)(Trectangle.c3.x * 16711680U) + (unsigned int)(Trectangle.c3.w * 4278190080U));
						renderer.line(Trectangle.a.x, Trectangle.c.y, Trectangle.a.x, Trectangle.a.y, (unsigned int)(Trectangle.c4.z * 255) + (unsigned int)(Trectangle.c4.y * (65280U)) + (unsigned int)(Trectangle.c4.x * 16711680U) + (unsigned int)(Trectangle.c4.w * 4278190080U));
					}
					else {
						renderer.line(Trectangle.a.x, Trectangle.a.y, Trectangle.c.x, Trectangle.a.y,
							(unsigned int)(Trectangle.c1.z * 255) + (unsigned int)(Trectangle.c1.y * (65280U)) + (unsigned int)(Trectangle.c1.x * 16711680U) + (unsigned int)(Trectangle.c1.w * 4278190080U),
							(unsigned int)(Trectangle.c2.z * 255) + (unsigned int)(Trectangle.c2.y * (65280U)) + (unsigned int)(Trectangle.c2.x * 16711680U) + (unsigned int)(Trectangle.c2.w * 4278190080U));
						renderer.line(Trectangle.c.x, Trectangle.a.y, Trectangle.c.x, Trectangle.c.y,
							(unsigned int)(Trectangle.c2.z * 255) + (unsigned int)(Trectangle.c2.y * (65280U)) + (unsigned int)(Trectangle.c2.x * 16711680U) + (unsigned int)(Trectangle.c2.w * 4278190080U),
							(unsigned int)(Trectangle.c4.z * 255) + (unsigned int)(Trectangle.c4.y * (65280U)) + (unsigned int)(Trectangle.c4.x * 16711680U) + (unsigned int)(Trectangle.c4.w * 4278190080U));
						renderer.line(Trectangle.c.x, Trectangle.c.y, Trectangle.a.x, Trectangle.c.y,
							(unsigned int)(Trectangle.c4.z * 255) + (unsigned int)(Trectangle.c4.y * (65280U)) + (unsigned int)(Trectangle.c4.x * 16711680U) + (unsigned int)(Trectangle.c4.w * 4278190080U),
							(unsigned int)(Trectangle.c3.z * 255) + (unsigned int)(Trectangle.c3.y * (65280U)) + (unsigned int)(Trectangle.c3.x * 16711680U) + (unsigned int)(Trectangle.c3.w * 4278190080U));
						renderer.line(Trectangle.a.x, Trectangle.c.y, Trectangle.a.x, Trectangle.a.y,
							(unsigned int)(Trectangle.c3.z * 255) + (unsigned int)(Trectangle.c3.y * (65280U)) + (unsigned int)(Trectangle.c3.x * 16711680U) + (unsigned int)(Trectangle.c3.w * 4278190080U),
							(unsigned int)(Trectangle.c1.z * 255) + (unsigned int)(Trectangle.c1.y * (65280U)) + (unsigned int)(Trectangle.c1.x * 16711680U) + (unsigned int)(Trectangle.c1.w * 4278190080U));
					};
				}
			}
			return *this;
		}
		if (beginvertex == 1) {
			glEnd();
		}

		if (Trectangle.fill) {
			float _buffer[] = {
				((Trectangle.a.x)),(((Trectangle.a.y))),((Trectangle.a.z)),Trectangle.c1.x,Trectangle.c1.y,Trectangle.c1.z,Trectangle.c1.w,Trectangle.t1.x,1.0f - Trectangle.t1.y,
				((Trectangle.c.x)),(((Trectangle.a.y))),((Trectangle.a.z)),Trectangle.c2.x,Trectangle.c2.y,Trectangle.c2.z,Trectangle.c2.w,Trectangle.t2.x,1.0f - Trectangle.t2.y,
				((Trectangle.a.x)),(((Trectangle.c.y))),((Trectangle.c.z)),Trectangle.c3.x,Trectangle.c3.y,Trectangle.c3.z,Trectangle.c3.w,Trectangle.t3.x,1.0f - Trectangle.t3.y,
				((Trectangle.c.x)),(((Trectangle.c.y))),((Trectangle.c.z)),Trectangle.c4.x,Trectangle.c4.y,Trectangle.c4.z,Trectangle.c4.w,Trectangle.t4.x,1.0f - Trectangle.t4.y
			};

			glBindVertexArray(rectvao);
			glBindBuffer(GL_ARRAY_BUFFER, rectvbo);

			memcpy(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY), _buffer, sizeof(_buffer));

			glUnmapBuffer(GL_ARRAY_BUFFER);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
		else {
			float _buffer[] = {
				((Trectangle.a.x)),(((Trectangle.a.y + 1))),((Trectangle.a.z)),Trectangle.c1.x,Trectangle.c1.y,Trectangle.c1.z,Trectangle.c1.w,Trectangle.t1.x,1.0f - Trectangle.t1.y,
				((Trectangle.c.x - 1)),(((Trectangle.a.y + 1))),((Trectangle.a.z)),Trectangle.c2.x,Trectangle.c2.y,Trectangle.c2.z,Trectangle.c2.w,Trectangle.t2.x,1.0f - Trectangle.t2.y,
				((Trectangle.c.x - 1)),(((Trectangle.c.y))),((Trectangle.c.z)),Trectangle.c4.x,Trectangle.c4.y,Trectangle.c4.z,Trectangle.c4.w,Trectangle.t4.x,1.0f - Trectangle.t4.y,
				((Trectangle.a.x)),(((Trectangle.c.y))),((Trectangle.c.z)),Trectangle.c3.x,Trectangle.c3.y,Trectangle.c3.z,Trectangle.c3.w,Trectangle.t3.x,1.0f - Trectangle.t3.y,
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
		matrix = Matrix<float, 4, 4>();
		if (hglrc != NULL) {
			shader->setUniform(matrixlocation, matrix);
			if (cshader != NULL) {
				cshader->setUniform(shadermatrixlocation, matrix);
			}
		}
	}

	void Renderer::Combine(const Matrix<float, 4, 4>& Tmatrix) {
		matrix *= Tmatrix;
		if (hglrc != NULL) {
			shader->setUniform(matrixlocation, matrix);
			if (cshader != NULL) {
				cshader->setUniform(shadermatrixlocation, matrix);
			}
		}
	}

	void Renderer::UseSolidTexture() {
		if (hglrc != NULL) {
			glBindTexture(GL_TEXTURE_2D, white);
		}
	}

	Renderer& Renderer::operator<< (Color Tcolor) {
		if (!hglrc) {
			if (!hwnd) {
				renderer.clear(Tcolor.uint());
			}
			else {
				renderer.clear(Tcolor.ruint());
			}
			return *this;
		}

		glClearColor(Tcolor.r() / 255.0f, Tcolor.g() / 255.0f, Tcolor.b() / 255.0f, Tcolor.a() / 255.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		return *this;
	}

	Renderer& Renderer::operator<< (int Tint) {
		if (!Tint) {
			if (!hglrc) {
				renderer.reset();
				return *this;
			}

			glClearColor(0, 0, 0, 0);
			glClear(GL_COLOR_BUFFER_BIT);
			return *this;
		}
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

		if (hglrc == NULL) {
			if (Tsprite.trans.angle != 0) {

			}
			else {
				Sprite _sprite = Tsprite;

				if (!hwnd) {
					float _tempc = _sprite.rect.c1.x;
					_sprite.rect.c1.x = _sprite.rect.c1.z;
					_sprite.rect.c1.z = _tempc;
					_tempc = _sprite.rect.c2.x;
					_sprite.rect.c2.x = _sprite.rect.c2.z;
					_sprite.rect.c2.z = _tempc;
					_tempc = _sprite.rect.c3.x;
					_sprite.rect.c3.x = _sprite.rect.c3.z;
					_sprite.rect.c3.z = _tempc;
					_tempc = _sprite.rect.c4.x;
					_sprite.rect.c4.x = _sprite.rect.c4.z;
					_sprite.rect.c4.z = _tempc;
				}
				if ((_sprite.rect.c1 == _sprite.rect.c2) && (_sprite.rect.c3 == _sprite.rect.c4)) {
					if (_sprite.rect.c1 == Color::White) {
						if (_sprite.texture != NULL) {
							if (_sprite.trans.scale.x == 1 && _sprite.trans.scale.y == 1) {
								if (_sprite.rect.t1 == Vec2(0, 0), _sprite.rect.t4 == Vec2(1, 1)) {
									renderer.rectangle(
										*_sprite.texture,
										(((_sprite.rect.a.x - _sprite.trans.origin.x))), ((((_sprite.rect.a.y - _sprite.trans.origin.y)))),
										(((_sprite.rect.c.x - _sprite.trans.origin.x))), ((((_sprite.rect.c.y - _sprite.trans.origin.y))))
									);
								}
								else {
									renderer.rectangle(
										*_sprite.texture,
										(((_sprite.rect.a.x - _sprite.trans.origin.x))), ((((_sprite.rect.a.y - _sprite.trans.origin.y)))),
										(((_sprite.rect.c.x - _sprite.trans.origin.x))), ((((_sprite.rect.c.y - _sprite.trans.origin.y)))),
										(int)_sprite.rect.t1.x, _sprite.rect.t1.y, _sprite.rect.t4.x, _sprite.rect.t4.y
									);
								}
							}
							else {
								float _widtho = ((_sprite.rect.c.x - _sprite.rect.a.x) - _sprite.trans.origin.x)*_sprite.trans.scale.x;
								float _heighto = ((_sprite.rect.c.y - _sprite.rect.a.y) - _sprite.trans.origin.y)*_sprite.trans.scale.y;

								if (_sprite.rect.t1 == Vec2(0, 0), _sprite.rect.t4 == Vec2(1, 1)) {
									renderer.rectangle(
										*_sprite.texture,
										(((_sprite.rect.a.x - _sprite.trans.origin.x*_sprite.trans.scale.x))), ((((_sprite.rect.a.y - _sprite.trans.origin.y*_sprite.trans.scale.y)))),
										(((_sprite.rect.a.x + _widtho))), ((((_sprite.rect.a.y + _heighto))))
									);
								}
								else {
									renderer.rectangle(
										*_sprite.texture,
										(((_sprite.rect.a.x - _sprite.trans.origin.x*_sprite.trans.scale.x))), ((((_sprite.rect.a.y - _sprite.trans.origin.y*_sprite.trans.scale.y)))),
										(((_sprite.rect.a.x + _widtho))), ((((_sprite.rect.a.y + _heighto)))),
										(int)_sprite.rect.t1.x, _sprite.rect.t1.y, _sprite.rect.t4.x, _sprite.rect.t4.y
									);
								}
							}
						}
						else {
							if (_sprite.trans.scale.x == 1 && _sprite.trans.scale.y == 1) {
								if (_sprite.rect.t1 == Vec2(0, 0), _sprite.rect.t4 == Vec2(1, 1)) {
									renderer.rectangle(
										(((_sprite.rect.a.x - _sprite.trans.origin.x))), ((((_sprite.rect.a.y - _sprite.trans.origin.y)))),
										(((_sprite.rect.c.x - _sprite.trans.origin.x))), ((((_sprite.rect.c.y - _sprite.trans.origin.y)))),
										Color::White.uint()
									);
								}
								else {
									renderer.rectangle(
										(((_sprite.rect.a.x - _sprite.trans.origin.x))), ((((_sprite.rect.a.y - _sprite.trans.origin.y)))),
										(((_sprite.rect.c.x - _sprite.trans.origin.x))), ((((_sprite.rect.c.y - _sprite.trans.origin.y)))),
										Color::White.uint()
									);
								}
							}
							else {
								float _widtho = ((_sprite.rect.c.x - _sprite.rect.a.x) - _sprite.trans.origin.x)*_sprite.trans.scale.x;
								float _heighto = ((_sprite.rect.c.y - _sprite.rect.a.y) - _sprite.trans.origin.y)*_sprite.trans.scale.y;

								if (_sprite.rect.t1 == Vec2(0, 0), _sprite.rect.t4 == Vec2(1, 1)) {
									renderer.rectangle(

										(((_sprite.rect.a.x - _sprite.trans.origin.x*_sprite.trans.scale.x))), ((((_sprite.rect.a.y - _sprite.trans.origin.y*_sprite.trans.scale.y)))),
										(((_sprite.rect.a.x + _widtho))), ((((_sprite.rect.a.y + _heighto)))),
										Color::White.uint()
									);
								}
								else {
									renderer.rectangle(
										(((_sprite.rect.a.x - _sprite.trans.origin.x*_sprite.trans.scale.x))), ((((_sprite.rect.a.y - _sprite.trans.origin.y*_sprite.trans.scale.y)))),
										(((_sprite.rect.a.x + _widtho))), ((((_sprite.rect.a.y + _heighto)))),
										Color::White.uint()
									);
								}
							}
						}
					}
					else {
						if (_sprite.texture != NULL) {
							if (_sprite.trans.scale.x == 1 && _sprite.trans.scale.y == 1) {
								if (_sprite.rect.t1 == Vec2(0, 0), _sprite.rect.t4 == Vec2(1, 1)) {
									renderer.rectangle(
										*_sprite.texture,
										(((_sprite.rect.a.x - _sprite.trans.origin.x))), ((((_sprite.rect.a.y - _sprite.trans.origin.y)))),
										(((_sprite.rect.c.x - _sprite.trans.origin.x))), ((((_sprite.rect.c.y - _sprite.trans.origin.y)))),
										(unsigned int)(_sprite.rect.c1.x * 255) + (unsigned int)(_sprite.rect.c1.y * (65280U)) + (unsigned int)(_sprite.rect.c1.z * 16711680U) + (unsigned int)(_sprite.rect.c1.w * 4278190080U)
									);
								}
								else {
									renderer.rectangle(
										*_sprite.texture,
										(((_sprite.rect.a.x - _sprite.trans.origin.x))), ((((_sprite.rect.a.y - _sprite.trans.origin.y)))),
										(((_sprite.rect.c.x - _sprite.trans.origin.x))), ((((_sprite.rect.c.y - _sprite.trans.origin.y)))),
										_sprite.rect.t1.x, _sprite.rect.t1.y, _sprite.rect.t4.x, _sprite.rect.t4.y,
										(unsigned int)(_sprite.rect.c1.x * 255) + (unsigned int)(_sprite.rect.c1.y * (65280U)) + (unsigned int)(_sprite.rect.c1.z * 16711680U) + (unsigned int)(_sprite.rect.c1.w * 4278190080U)
									);
								}
							}
							else {
								float _widtho = ((_sprite.rect.c.x - _sprite.rect.a.x) - _sprite.trans.origin.x)*_sprite.trans.scale.x;
								float _heighto = ((_sprite.rect.c.y - _sprite.rect.a.y) - _sprite.trans.origin.y)*_sprite.trans.scale.y;

								if (_sprite.rect.t1 == Vec2(0, 0), _sprite.rect.t4 == Vec2(1, 1)) {
									renderer.rectangle(
										*_sprite.texture,
										(((_sprite.rect.a.x - _sprite.trans.origin.x*_sprite.trans.scale.x))), ((((_sprite.rect.a.y - _sprite.trans.origin.y*_sprite.trans.scale.y)))),
										(((_sprite.rect.a.x + _widtho))), ((((_sprite.rect.a.y + _heighto)))),
										(unsigned int)(_sprite.rect.c1.x * 255) + (unsigned int)(_sprite.rect.c1.y * (65280U)) + (unsigned int)(_sprite.rect.c1.z * 16711680U) + (unsigned int)(_sprite.rect.c1.w * 4278190080U)
									);
								}
								else {
									renderer.rectangle(
										*_sprite.texture,
										(((_sprite.rect.a.x - _sprite.trans.origin.x*_sprite.trans.scale.x))), ((((_sprite.rect.a.y - _sprite.trans.origin.y*_sprite.trans.scale.y)))),
										(((_sprite.rect.a.x + _widtho))), ((((_sprite.rect.a.y + _heighto)))),
										_sprite.rect.t1.x, _sprite.rect.t1.y, _sprite.rect.t4.x, _sprite.rect.t4.y,
										(unsigned int)(_sprite.rect.c1.x * 255) + (unsigned int)(_sprite.rect.c1.y * (65280U)) + (unsigned int)(_sprite.rect.c1.z * 16711680U) + (unsigned int)(_sprite.rect.c1.w * 4278190080U)
									);
								}
							}
						}
						else {
							if (_sprite.rect.c1.w) {
								if (_sprite.trans.scale.x == 1 && _sprite.trans.scale.y == 1) {
									if (_sprite.rect.t1 == Vec2(0, 0), _sprite.rect.t4 == Vec2(1, 1)) {
										renderer.rectangle(
											(((_sprite.rect.a.x - _sprite.trans.origin.x))), ((((_sprite.rect.a.y - _sprite.trans.origin.y)))),
											(((_sprite.rect.c.x - _sprite.trans.origin.x))), ((((_sprite.rect.c.y - _sprite.trans.origin.y)))),
											(unsigned int)(_sprite.rect.c1.x * 255) + (unsigned int)(_sprite.rect.c1.y * (65280U)) + (unsigned int)(_sprite.rect.c1.z * 16711680U) + (unsigned int)(_sprite.rect.c1.w * 4278190080U)
										);
									}
									else {
										renderer.rectangle(
											(((_sprite.rect.a.x - _sprite.trans.origin.x))), ((((_sprite.rect.a.y - _sprite.trans.origin.y)))),
											(((_sprite.rect.c.x - _sprite.trans.origin.x))), ((((_sprite.rect.c.y - _sprite.trans.origin.y)))),
											(unsigned int)(_sprite.rect.c1.x * 255) + (unsigned int)(_sprite.rect.c1.y * (65280U)) + (unsigned int)(_sprite.rect.c1.z * 16711680U) + (unsigned int)(_sprite.rect.c1.w * 4278190080U)
										);
									}
								}
								else {
									float _widtho = ((_sprite.rect.c.x - _sprite.rect.a.x) - _sprite.trans.origin.x)*_sprite.trans.scale.x;
									float _heighto = ((_sprite.rect.c.y - _sprite.rect.a.y) - _sprite.trans.origin.y)*_sprite.trans.scale.y;

									if (_sprite.rect.t1 == Vec2(0, 0), _sprite.rect.t4 == Vec2(1, 1)) {
										renderer.rectangle(
											(((_sprite.rect.a.x - _sprite.trans.origin.x*_sprite.trans.scale.x))), ((((_sprite.rect.a.y - _sprite.trans.origin.y*_sprite.trans.scale.y)))),
											(((_sprite.rect.a.x + _widtho))), ((((_sprite.rect.a.y + _heighto)))),
											(unsigned int)(_sprite.rect.c1.x * 255) + (unsigned int)(_sprite.rect.c1.y * (65280U)) + (unsigned int)(_sprite.rect.c1.z * 16711680U) + (unsigned int)(_sprite.rect.c1.w * 4278190080U)
										);
									}
									else {
										renderer.rectangle(
											(((_sprite.rect.a.x - _sprite.trans.origin.x*_sprite.trans.scale.x))), ((((_sprite.rect.a.y - _sprite.trans.origin.y*_sprite.trans.scale.y)))),
											(((_sprite.rect.a.x + _widtho))), ((((_sprite.rect.a.y + _heighto)))),
											(unsigned int)(_sprite.rect.c1.x * 255) + (unsigned int)(_sprite.rect.c1.y * (65280U)) + (unsigned int)(_sprite.rect.c1.z * 16711680U) + (unsigned int)(_sprite.rect.c1.w * 4278190080U)
										);
									}
								}
							}
						}
					}
				}
				else {
					if (_sprite.texture != NULL) {
						if (_sprite.trans.scale.x == 1 && _sprite.trans.scale.y == 1) {
							if (_sprite.rect.t1 == Vec2(0, 0), _sprite.rect.t4 == Vec2(1, 1)) {
								renderer.rectangle(
									*_sprite.texture,
									(((_sprite.rect.a.x - _sprite.trans.origin.x))), ((((_sprite.rect.a.y - _sprite.trans.origin.y)))),
									(((_sprite.rect.c.x - _sprite.trans.origin.x))), ((((_sprite.rect.c.y - _sprite.trans.origin.y)))),
									(unsigned int)(_sprite.rect.c1.x * 255) + (unsigned int)(_sprite.rect.c1.y * (65280U)) + (unsigned int)(_sprite.rect.c1.z * 16711680U) + (unsigned int)(_sprite.rect.c1.w * 4278190080U),
									(unsigned int)(_sprite.rect.c2.x * 255) + (unsigned int)(_sprite.rect.c2.y * (65280U)) + (unsigned int)(_sprite.rect.c2.z * 16711680U) + (unsigned int)(_sprite.rect.c2.w * 4278190080U),
									(unsigned int)(_sprite.rect.c3.x * 255) + (unsigned int)(_sprite.rect.c3.y * (65280U)) + (unsigned int)(_sprite.rect.c3.z * 16711680U) + (unsigned int)(_sprite.rect.c3.w * 4278190080U),
									(unsigned int)(_sprite.rect.c4.x * 255) + (unsigned int)(_sprite.rect.c4.y * (65280U)) + (unsigned int)(_sprite.rect.c4.z * 16711680U) + (unsigned int)(_sprite.rect.c4.w * 4278190080U)
								);
							}
							else {
								renderer.rectangle(
									*_sprite.texture,
									(((_sprite.rect.a.x - _sprite.trans.origin.x))), ((((_sprite.rect.a.y - _sprite.trans.origin.y)))),
									(((_sprite.rect.c.x - _sprite.trans.origin.x))), ((((_sprite.rect.c.y - _sprite.trans.origin.y)))),
									(int)_sprite.rect.t1.x, _sprite.rect.t1.y, _sprite.rect.t4.x, _sprite.rect.t4.y,
									(unsigned int)(_sprite.rect.c1.x * 255) + (unsigned int)(_sprite.rect.c1.y * (65280U)) + (unsigned int)(_sprite.rect.c1.z * 16711680U) + (unsigned int)(_sprite.rect.c1.w * 4278190080U),
									(unsigned int)(_sprite.rect.c2.x * 255) + (unsigned int)(_sprite.rect.c2.y * (65280U)) + (unsigned int)(_sprite.rect.c2.z * 16711680U) + (unsigned int)(_sprite.rect.c2.w * 4278190080U),
									(unsigned int)(_sprite.rect.c3.x * 255) + (unsigned int)(_sprite.rect.c3.y * (65280U)) + (unsigned int)(_sprite.rect.c3.z * 16711680U) + (unsigned int)(_sprite.rect.c3.w * 4278190080U),
									(unsigned int)(_sprite.rect.c4.x * 255) + (unsigned int)(_sprite.rect.c4.y * (65280U)) + (unsigned int)(_sprite.rect.c4.z * 16711680U) + (unsigned int)(_sprite.rect.c4.w * 4278190080U)
								);
							}
						}
						else {
							float _widtho = ((_sprite.rect.c.x - _sprite.rect.a.x) - _sprite.trans.origin.x)*_sprite.trans.scale.x;
							float _heighto = ((_sprite.rect.c.y - _sprite.rect.a.y) - _sprite.trans.origin.y)*_sprite.trans.scale.y;

							if (_sprite.rect.t1 == Vec2(0, 0), _sprite.rect.t4 == Vec2(1, 1)) {
								renderer.rectangle(
									*_sprite.texture,
									(((_sprite.rect.a.x - _sprite.trans.origin.x*_sprite.trans.scale.x))), ((((_sprite.rect.a.y - _sprite.trans.origin.y*_sprite.trans.scale.y)))),
									(((_sprite.rect.a.x + _widtho))), ((((_sprite.rect.a.y + _heighto)))),
									(unsigned int)(_sprite.rect.c1.x * 255) + (unsigned int)(_sprite.rect.c1.y * (65280U)) + (unsigned int)(_sprite.rect.c1.z * 16711680U) + (unsigned int)(_sprite.rect.c1.w * 4278190080U),
									(unsigned int)(_sprite.rect.c2.x * 255) + (unsigned int)(_sprite.rect.c2.y * (65280U)) + (unsigned int)(_sprite.rect.c2.z * 16711680U) + (unsigned int)(_sprite.rect.c2.w * 4278190080U),
									(unsigned int)(_sprite.rect.c3.x * 255) + (unsigned int)(_sprite.rect.c3.y * (65280U)) + (unsigned int)(_sprite.rect.c3.z * 16711680U) + (unsigned int)(_sprite.rect.c3.w * 4278190080U),
									(unsigned int)(_sprite.rect.c4.x * 255) + (unsigned int)(_sprite.rect.c4.y * (65280U)) + (unsigned int)(_sprite.rect.c4.z * 16711680U) + (unsigned int)(_sprite.rect.c4.w * 4278190080U)
								);
							}
							else {
								renderer.rectangle(
									*_sprite.texture,
									(((_sprite.rect.a.x - _sprite.trans.origin.x*_sprite.trans.scale.x))), ((((_sprite.rect.a.y - _sprite.trans.origin.y*_sprite.trans.scale.y)))),
									(((_sprite.rect.a.x + _widtho))), ((((_sprite.rect.a.y + _heighto)))),
									(int)_sprite.rect.t1.x, _sprite.rect.t1.y, _sprite.rect.t4.x, _sprite.rect.t4.y,
									(unsigned int)(_sprite.rect.c1.x * 255) + (unsigned int)(_sprite.rect.c1.y * (65280U)) + (unsigned int)(_sprite.rect.c1.z * 16711680U) + (unsigned int)(_sprite.rect.c1.w * 4278190080U),
									(unsigned int)(_sprite.rect.c2.x * 255) + (unsigned int)(_sprite.rect.c2.y * (65280U)) + (unsigned int)(_sprite.rect.c2.z * 16711680U) + (unsigned int)(_sprite.rect.c2.w * 4278190080U),
									(unsigned int)(_sprite.rect.c3.x * 255) + (unsigned int)(_sprite.rect.c3.y * (65280U)) + (unsigned int)(_sprite.rect.c3.z * 16711680U) + (unsigned int)(_sprite.rect.c3.w * 4278190080U),
									(unsigned int)(_sprite.rect.c4.x * 255) + (unsigned int)(_sprite.rect.c4.y * (65280U)) + (unsigned int)(_sprite.rect.c4.z * 16711680U) + (unsigned int)(_sprite.rect.c4.w * 4278190080U)
								);
							}
						}
					}
				}
			}
			return *this;
		}

		if (Tsprite.texture != NULL) {
			Tsprite.texture->Bind();
		}

		if (Tsprite.trans.angle != 0) {
			float _width = (Tsprite.rect.c.x - Tsprite.rect.a.x)*Tsprite.trans.scale.x;
			float _height = (Tsprite.rect.c.y - Tsprite.rect.a.y)*Tsprite.trans.scale.y;

			float _siny = sin(radians_const(Tsprite.trans.angle - 90));
			float _cosy = cos(radians_const(Tsprite.trans.angle - 90));
			float _sinx = sin(radians_const(Tsprite.trans.angle - 180));
			float _cosx = cos(radians_const(Tsprite.trans.angle - 180));
			//float _sin3 = sin(radians_const(Tsprite.trans.angle));

			Vec2 _rot_a_ = (Vec2(_sinx, _cosx) * Tsprite.trans.origin.y*Tsprite.trans.scale.y) + (Vec2(_siny, _cosy) * Tsprite.trans.origin.x*Tsprite.trans.scale.x);
			Vec2 _rot_b_ = Vec2(-_siny, -_cosy) * _width;

			Vec2 _rot_c_ = Vec2(-_sinx, -_cosx) * _height;

			//float _ox = _width - Tsprite.trans.origin.x;
			//float _oy = _height - Tsprite.trans.origin.y;

			float _ax = ((((Tsprite.rect.a.x + _rot_a_.x))));
			float _ay = ((((Tsprite.rect.a.y + _rot_a_.y))));
			float _bx = ((((Tsprite.rect.a.x + ((_rot_a_.x + _rot_b_.x))))));
			float _by = ((((Tsprite.rect.a.y + ((_rot_a_.y + _rot_b_.y))))));
			float _cx = ((((Tsprite.rect.a.x + ((_rot_a_.x + _rot_c_.x))))));
			float _cy = ((((Tsprite.rect.a.y + ((_rot_a_.y + _rot_c_.y))))));
			float _dx = ((((Tsprite.rect.a.x + ((_rot_a_.x + _rot_b_.x + _rot_c_.x))))));
			float _dy = ((((Tsprite.rect.a.y + ((_rot_a_.y + _rot_b_.y + _rot_c_.y))))));

			float _buffer[] = {
				_ax,_ay,Tsprite.rect.a.z,Tsprite.rect.c1.x,Tsprite.rect.c1.y,Tsprite.rect.c1.z,Tsprite.rect.c1.w,Tsprite.rect.t1.x,1.0f - Tsprite.rect.t1.y,
				_bx,_by,Tsprite.rect.a.z,Tsprite.rect.c2.x,Tsprite.rect.c2.y,Tsprite.rect.c2.z,Tsprite.rect.c2.w,Tsprite.rect.t2.x,1.0f - Tsprite.rect.t2.y,
				_cx,_cy,Tsprite.rect.c.z,Tsprite.rect.c3.x,Tsprite.rect.c3.y,Tsprite.rect.c3.z,Tsprite.rect.c3.w,Tsprite.rect.t3.x,1.0f - Tsprite.rect.t3.y,
				_dx,_dy,Tsprite.rect.c.z,Tsprite.rect.c4.x,Tsprite.rect.c4.y,Tsprite.rect.c4.z,Tsprite.rect.c4.w,Tsprite.rect.t4.x,1.0f - Tsprite.rect.t4.y
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
					(((Tsprite.rect.a.x - Tsprite.trans.origin.x))),((((Tsprite.rect.a.y - Tsprite.trans.origin.y)))),Tsprite.rect.a.z,Tsprite.rect.c1.x,Tsprite.rect.c1.y,Tsprite.rect.c1.z,Tsprite.rect.c1.w,Tsprite.rect.t1.x,1.0f - Tsprite.rect.t1.y,
					(((Tsprite.rect.c.x - Tsprite.trans.origin.x))),((((Tsprite.rect.a.y - Tsprite.trans.origin.y)))),Tsprite.rect.a.z,Tsprite.rect.c2.x,Tsprite.rect.c2.y,Tsprite.rect.c2.z,Tsprite.rect.c2.w,Tsprite.rect.t2.x,1.0f - Tsprite.rect.t2.y,
					(((Tsprite.rect.a.x - Tsprite.trans.origin.x))),((((Tsprite.rect.c.y - Tsprite.trans.origin.y)))),Tsprite.rect.c.z,Tsprite.rect.c3.x,Tsprite.rect.c3.y,Tsprite.rect.c3.z,Tsprite.rect.c3.w,Tsprite.rect.t3.x,1.0f - Tsprite.rect.t3.y,
					(((Tsprite.rect.c.x - Tsprite.trans.origin.x))),((((Tsprite.rect.c.y - Tsprite.trans.origin.y)))),Tsprite.rect.c.z,Tsprite.rect.c4.x,Tsprite.rect.c4.y,Tsprite.rect.c4.z,Tsprite.rect.c4.w,Tsprite.rect.t4.x,1.0f - Tsprite.rect.t4.y,
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
					(((Tsprite.rect.a.x - Tsprite.trans.origin.x*Tsprite.trans.scale.x))),((((Tsprite.rect.a.y - Tsprite.trans.origin.y*Tsprite.trans.scale.y)))),Tsprite.rect.a.z,Tsprite.rect.c1.x,Tsprite.rect.c1.y,Tsprite.rect.c1.z,Tsprite.rect.c1.w,Tsprite.rect.t1.x,1.0f - Tsprite.rect.t1.y,
					(((Tsprite.rect.a.x + _widtho))),((((Tsprite.rect.a.y - Tsprite.trans.origin.y*Tsprite.trans.scale.y)))),Tsprite.rect.a.z,Tsprite.rect.c2.x,Tsprite.rect.c2.y,Tsprite.rect.c2.z,Tsprite.rect.c2.w,Tsprite.rect.t2.x,1.0f - Tsprite.rect.t2.y,
					(((Tsprite.rect.a.x - Tsprite.trans.origin.x*Tsprite.trans.scale.x))),((((Tsprite.rect.a.y + _heighto)))),Tsprite.rect.c.z,Tsprite.rect.c3.x,Tsprite.rect.c3.y,Tsprite.rect.c3.z,Tsprite.rect.c3.w,Tsprite.rect.t3.x,1.0f - Tsprite.rect.t3.y,
					(((Tsprite.rect.a.x + _widtho))),((((Tsprite.rect.a.y + _heighto)))),Tsprite.rect.c.z,Tsprite.rect.c4.x,Tsprite.rect.c4.y,Tsprite.rect.c4.z,Tsprite.rect.c4.w,Tsprite.rect.t4.x,1.0f - Tsprite.rect.t4.y,
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

	static enum TextFunc {
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

		unsigned int _colort;

		std::string _collecttext;
		int _hexl = 0;

		Color _Tcolor(255, 255, 255, 255);
		Vec4 _color = _Tcolor;

		int _Txpos = 0;

		bool _Tdraw = 0;

		bool _allowbackslash = 0;

		if (hglrc != NULL) {
			Ttext.font->getTex()->Bind();
		}

		float _bottomheight = (Ttext.font->getFullHeight() - Ttext.font->getHeight());

		int _texty = 0;
		if (Ttext.valign == Text::Middle) {
			_texty = (Ttext.getSize().y - _bottomheight) / 2;
		}
		if (Ttext.valign == Text::Bottom) {
			_texty = (Ttext.getSize().y - _bottomheight);
		}

		if (Ttext.align == Text::Left) {
			for (int i = 0;i < _length;i++) {
				if (Ttext.string[i] == '\n') {
					_Tline++;
					//_Tex++;
					_Tpos = 0;
					_Txpos = 0;
				}
				if (Ttext.warp) {
					if (_Txpos > Ttext.warp) {
						if (Ttext.warpchar) {
							if (Ttext.string[i] == Ttext.warpchar) {
								_Tline++;
								//_Tex++;
								_Tpos = 0;
								_Txpos = 0;
							}
						}
						else {
							_Tline++;
							//_Tex++;
							_Tpos = 0;
							_Txpos = 0;
						}
					}
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
					if (hglrc != NULL) {
						float Rx = Ttext.pos.x + _Txpos;
						float Ry = Ttext.pos.y + (_Tline*(Ttext.font->getFullHeight() + Ttext.font->getSepWidth())) - _texty;
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

					}
					else {
						//if (i == 1) {
						if (hwnd == NULL) {
							_colort = (unsigned int)(_color.x * 255) + (unsigned int)(_color.y * (65280U)) + (unsigned int)(_color.z * 16711680U) + (unsigned int)(_color.w * 4278190080U);
						}
						else {
							_colort = (unsigned int)(_color.z * 255) + (unsigned int)(_color.y * (65280U)) + (unsigned int)(_color.x * 16711680U) + (unsigned int)(_color.w * 4278190080U);
						}
						renderer.blitrectcolor(*Ttext.font->getTex(), Ttext.pos.x + _Txpos, Ttext.pos.y + _Tline * (Ttext.font->getFullHeight() + Ttext.font->getSepWidth()) - _texty, ((Ttext.string[i] - Ttext.font->getStartChar()) % 16) * Ttext.font->getFullWidth(), int((Ttext.string[i] - Ttext.font->getStartChar()) / 16) * Ttext.font->getFullHeight(), Ttext.font->getWidth(Ttext.string[i]), Ttext.font->getFullHeight(), _colort);
						//}
					}

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
						case 'r': {
							_color = Color(255, 255, 255, 255);
							_Tfunc = TextFunc::None;
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
							_color = Color(255, 255, 255, 255);
							_Tfunc = TextFunc::None;
							break;
						}
						case '0': {
							_color = Color(0, 0, 0, 255);
							_Tfunc = TextFunc::None;
							break;
						}
						case '~': {
							break;
						}
						case '1': {
							_color = Color(255, 255, 0, 255);
							_Tfunc = TextFunc::None;
							break;
						}
						case '2': {
							_color = Color(0, 255, 0, 255);
							_Tfunc = TextFunc::None;
							break;
						}
						case '3': {
							_color = Color(0, 255, 255, 255);
							_Tfunc = TextFunc::None;
							break;
						}
						case '4': {
							_color = Color(0, 0, 255, 255);
							_Tfunc = TextFunc::None;
							break;
						}
						case '5': {
							_color = Color(255, 0, 255, 255);
							_Tfunc = TextFunc::None;
							break;
						}
						case '6': {
							_color = Color(255, 0, 0, 255);
							_Tfunc = TextFunc::None;
							break;
						}
						case '7': {
							_color = Color(63, 63, 63, 255);
							_Tfunc = TextFunc::None;
							break;
						}
						case '8': {
							_color = Color(127, 127, 127, 255);
							_Tfunc = TextFunc::None;
							break;
						}
						case '9': {
							_color = Color(191, 191, 191, 255);
							_Tfunc = TextFunc::None;
							break;
						}
						case 'r': {
							_color = Color(255, 255, 255, 255);
							_Tfunc = TextFunc::None;
							break;
						}
						case 'G': {
							_color = Color(0, 255, 0, 255);
							_Tfunc = TextFunc::None;
							break;
						}
						}
						//_color = _Tcolor;
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
		if (Ttext.align == Text::Right) {
			int _textx = 0;

			for (int i = 0;i < _length;i++) {
				if (Ttext.warp) {
					if (_Txpos > Ttext.warp) {
						if (Ttext.warpchar) {
							if (Ttext.string[i] == Ttext.warpchar) {
								_Tline++;
								//_Tex++;
								_Tpos = 0;
								_Txpos = 0;
							}
						}
						else {
							_Tline++;
							//_Tex++;
							_Tpos = 0;
							_Txpos = 0;
						}
					}
				}
				if (!_Txpos) {
					float _linewidth = Ttext.LineWidth(i);
					if (_linewidth > Ttext.warp) {
						_textx = Ttext.pos.x - (Ttext.warp);
					}
					else {
						_textx = Ttext.pos.x - (_linewidth);
					}

				}
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

					if (hglrc != NULL) {
						float Rx = _textx + _Txpos;
						float Ry = Ttext.pos.y + _Tline * (Ttext.font->getFullHeight() + Ttext.font->getSepWidth()) - _texty;
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

					}
					else {
						//if (i == 1) {
						//_textx +
						/*
						renderer.blitrect(*Ttext.font->getTex(),
						(_Txpos) + (Ttext.font->getWidth(Ttext.string[i])),
						(Ttext.pos.y + (_size.y - ((_Tline) * (Ttext.font->getFullHeight() + Ttext.font->getSepWidth())))),
						(((Ttext.string[i] - Ttext.font->getStartChar()) % 16) * Ttext.font->getFullWidth()),
						(int((Ttext.string[i] - Ttext.font->getStartChar()) / 16) * Ttext.font->getFullHeight()),
						(Ttext.font->getWidth(Ttext.string[i])),
						(Ttext.font->getFullHeight()));
						*/
						if (hwnd == NULL) {
							_colort = (unsigned int)(_color.x * 255) + (unsigned int)(_color.y * (65280U)) + (unsigned int)(_color.z * 16711680U) + (unsigned int)(_color.w * 4278190080U);
						}
						else {
							_colort = (unsigned int)(_color.z * 255) + (unsigned int)(_color.y * (65280U)) + (unsigned int)(_color.x * 16711680U) + (unsigned int)(_color.w * 4278190080U);
						}
						renderer.blitrectcolor(*Ttext.font->getTex(), _textx + _Txpos, Ttext.pos.y + _Tline * (Ttext.font->getFullHeight() + Ttext.font->getSepWidth()) - _texty, ((Ttext.string[i] - Ttext.font->getStartChar()) % 16) * Ttext.font->getFullWidth(), int((Ttext.string[i] - Ttext.font->getStartChar()) / 16) * Ttext.font->getFullHeight(), Ttext.font->getWidth(Ttext.string[i]), Ttext.font->getFullHeight(), _colort);
						//}
					}

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
						case 'r': {
							_color = Color(255, 255, 255, 255);
							_Tfunc = TextFunc::None;
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
							_color = Color(255, 255, 255, 255);
							_Tfunc = TextFunc::None;
							break;
						}
						case '0': {
							_color = Color(0, 0, 0, 255);
							_Tfunc = TextFunc::None;
							break;
						}
						case '~': {
							break;
						}
						case '1': {
							_color = Color(255, 255, 0, 255);
							_Tfunc = TextFunc::None;
							break;
						}
						case '2': {
							_color = Color(0, 255, 0, 255);
							_Tfunc = TextFunc::None;
							break;
						}
						case '3': {
							_color = Color(0, 255, 255, 255);
							_Tfunc = TextFunc::None;
							break;
						}
						case '4': {
							_color = Color(0, 0, 255, 255);
							_Tfunc = TextFunc::None;
							break;
						}
						case '5': {
							_color = Color(255, 0, 255, 255);
							_Tfunc = TextFunc::None;
							break;
						}
						case '6': {
							_color = Color(255, 0, 0, 255);
							_Tfunc = TextFunc::None;
							break;
						}
						case '7': {
							_color = Color(63, 63, 63, 255);
							_Tfunc = TextFunc::None;
							break;
						}
						case '8': {
							_color = Color(127, 127, 127, 255);
							_Tfunc = TextFunc::None;
							break;
						}
						case '9': {
							_color = Color(191, 191, 191, 255);
							_Tfunc = TextFunc::None;
							break;
						}
						case 'r': {
							_color = Color(255, 255, 255, 255);
							_Tfunc = TextFunc::None;
							break;
						}
						case 'G': {
							_color = Color(0, 255, 0, 255);
							_Tfunc = TextFunc::None;
							break;
						}
						}
						//_color = _Tcolor;
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
		if (Ttext.align == Text::Center) {
			int _textx = 0;

			for (int i = 0;i < _length;i++) {
				if (Ttext.warp) {
					if (_Txpos > Ttext.warp) {
						if (Ttext.warpchar) {
							if (Ttext.string[i] == Ttext.warpchar) {
								_Tline++;
								//_Tex++;
								_Tpos = 0;
								_Txpos = 0;
							}
						}
						else {
							_Tline++;
							//_Tex++;
							_Tpos = 0;
							_Txpos = 0;
						}
					}
				}
				if (!_Txpos) {
					float _linewidth = Ttext.LineWidth(i);
					if (_linewidth > Ttext.warp) {
						_textx = Ttext.pos.x - (Ttext.warp / 2);
					}
					else {
						_textx = Ttext.pos.x - (_linewidth / 2);
					}

				}
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

					if (hglrc != NULL) {
						float Rx = _textx + _Txpos;
						float Ry = Ttext.pos.y + _Tline * (Ttext.font->getFullHeight() + Ttext.font->getSepWidth()) - _texty;
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

					}
					else {
						//if (i == 1) {
						//_textx +
						/*
						renderer.blitrect(*Ttext.font->getTex(),
						(_Txpos) + (Ttext.font->getWidth(Ttext.string[i])),
						(Ttext.pos.y + (_size.y - ((_Tline) * (Ttext.font->getFullHeight() + Ttext.font->getSepWidth())))),
						(((Ttext.string[i] - Ttext.font->getStartChar()) % 16) * Ttext.font->getFullWidth()),
						(int((Ttext.string[i] - Ttext.font->getStartChar()) / 16) * Ttext.font->getFullHeight()),
						(Ttext.font->getWidth(Ttext.string[i])),
						(Ttext.font->getFullHeight()));
						*/
						if (hwnd == NULL) {
							_colort = (unsigned int)(_color.x * 255) + (unsigned int)(_color.y * (65280U)) + (unsigned int)(_color.z * 16711680U) + (unsigned int)(_color.w * 4278190080U);
						}
						else {
							_colort = (unsigned int)(_color.z * 255) + (unsigned int)(_color.y * (65280U)) + (unsigned int)(_color.x * 16711680U) + (unsigned int)(_color.w * 4278190080U);
						}
						renderer.blitrectcolor(*Ttext.font->getTex(), _textx + _Txpos, Ttext.pos.y + _Tline * (Ttext.font->getFullHeight() + Ttext.font->getSepWidth()) - _texty, ((Ttext.string[i] - Ttext.font->getStartChar()) % 16) * Ttext.font->getFullWidth(), int((Ttext.string[i] - Ttext.font->getStartChar()) / 16) * Ttext.font->getFullHeight(), Ttext.font->getWidth(Ttext.string[i]), Ttext.font->getFullHeight(), _colort);
						//}
					}

					_Txpos = _Txpos + ((Ttext.font->getWidth(Ttext.string[i]) + Ttext.font->getSepWidth()));
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
						case 'r': {
							_color = Color(255, 255, 255, 255);
							_Tfunc = TextFunc::None;
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
							_color = Color(255, 255, 255, 255);
							_Tfunc = TextFunc::None;
							break;
						}
						case '0': {
							_color = Color(0, 0, 0, 255);
							_Tfunc = TextFunc::None;
							break;
						}
						case '~': {
							break;
						}
						case '1': {
							_color = Color(255, 255, 0, 255);
							_Tfunc = TextFunc::None;
							break;
						}
						case '2': {
							_color = Color(0, 255, 0, 255);
							_Tfunc = TextFunc::None;
							break;
						}
						case '3': {
							_color = Color(0, 255, 255, 255);
							_Tfunc = TextFunc::None;
							break;
						}
						case '4': {
							_color = Color(0, 0, 255, 255);
							_Tfunc = TextFunc::None;
							break;
						}
						case '5': {
							_color = Color(255, 0, 255, 255);
							_Tfunc = TextFunc::None;
							break;
						}
						case '6': {
							_color = Color(255, 0, 0, 255);
							_Tfunc = TextFunc::None;
							break;
						}
						case '7': {
							_color = Color(63, 63, 63, 255);
							_Tfunc = TextFunc::None;
							break;
						}
						case '8': {
							_color = Color(127, 127, 127, 255);
							_Tfunc = TextFunc::None;
							break;
						}
						case '9': {
							_color = Color(191, 191, 191, 255);
							_Tfunc = TextFunc::None;
							break;
						}
						case 'r': {
							_color = Color(255, 255, 255, 255);
							_Tfunc = TextFunc::None;
							break;
						}
						case 'G': {
							_color = Color(0, 255, 0, 255);
							_Tfunc = TextFunc::None;
							break;
						}
						}
						//_color = _Tcolor;
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
	}

	Renderer& Renderer::operator<< (const ModernText& Ttext) {
		UseShader(moderntext_shader,
			modernmatrixlocation,
			modernviewmatrixlocation,
			moderntransmatrixlocation
		);
		int posx = Ttext.pos.x;
		int posy = Ttext.pos.y;
		const float CharHeightMax = (Ttext.font->getPixelSize() / 2);
		int cWidth;
		moderntext_shader.setUniform("textColor", Ttext.color);
		Vec4 Tcolor = Ttext.color;
		bool deadend = false;


		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, Ttext.font->getTexture());
		glBindVertexArray(rectvao);
		std::wstring::const_iterator c;



		for (int i = 0; i < Ttext.glyphCount; ++i) {

			if (posx + Ttext.Tglyph[i].Size.x > Ttext.pos.x + Ttext.size.x)
			{
				if (!Ttext.oneLine)
				{
					posy += CharHeightMax * Ttext.scale;
					posx = Ttext.pos.x;
				}
			}
			float xpos = posx + Ttext.Tglyph[i].Bearing.x * Ttext.scale;
			float ypos = posy + ((CharHeightMax - Ttext.Tglyph[i].Bearing.y)) * Ttext.scale;
			//getModernGlyphList()[HighestCharHeight].Bearing.y
			float w = Ttext.Tglyph[i].Size.x * Ttext.scale;
			float h = Ttext.Tglyph[i].Size.y * Ttext.scale;
			float vertices[] = {
				xpos,     ypos,			0,Tcolor.x, Tcolor.y, Tcolor.z, Tcolor.w,0.0, 0.0 ,
				xpos,     ypos + h,		0,Tcolor.x, Tcolor.y, Tcolor.z, Tcolor.w, 0.0, 1.0 ,
				xpos + w, ypos,			0,Tcolor.x, Tcolor.y, Tcolor.z, Tcolor.w, 1.0, 0.0 ,
				xpos + w, ypos + h,		0,Tcolor.x, Tcolor.y, Tcolor.z, Tcolor.w, 1.0, 1.0
			};

			char log[1000];
			moderntext_shader.getLog(OpenGL::Shader::ShaderType::Fragment, log, 1000);
			char loga[1000];
			moderntext_shader.getLog(OpenGL::Shader::ShaderType::Vertex, loga, 1000);

			if (Ttext.oneLine)
			{
				if (!deadend)
				{
					/*if (posx + Ttext.Tglyph[i].Size.x < Ttext.pos.x + Ttext.size.x - (Ttext.font->GlyphList[63].Size.x))
					glBindTexture(GL_TEXTURE_2D, Ttext.Tglyph[i].TextureID);
					else
					{
					glBindTexture(GL_TEXTURE_2D, Ttext.font->GlyphList[63].TextureID);
					deadend = true;
					}
					glBindBuffer(GL_ARRAY_BUFFER, moderntextvbo);
					memcpy(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY), vertices, sizeof(vertices));
					glUnmapBuffer(GL_ARRAY_BUFFER);
					glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);*/

					if (posx + Ttext.Tglyph[i].Size.x < Ttext.pos.x + Ttext.size.x - (Ttext.font->GlyphList[392].Size.x))
					{
						glBindTexture(GL_TEXTURE_2D, Ttext.Tglyph[i].TextureID);
						glBindBuffer(GL_ARRAY_BUFFER, moderntextvbo);
						memcpy(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY), vertices, sizeof(vertices));
						glUnmapBuffer(GL_ARRAY_BUFFER);
						glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
					}
					else
					{
						float xpos = posx + Ttext.font->GlyphList[392].Bearing.x * Ttext.scale;
						float ypos = posy + ((CharHeightMax - Ttext.font->GlyphList[392].Bearing.y)) * Ttext.scale;
						//getModernGlyphList()[HighestCharHeight].Bearing.y
						float w = Ttext.font->GlyphList[392].Size.x * Ttext.scale;
						float h = Ttext.font->GlyphList[392].Size.y * Ttext.scale;
						float newvertices[] = {
							Ttext.pos.x + Ttext.size.x - (Ttext.font->GlyphList[392].Size.x),     ypos,			0,Tcolor.x, Tcolor.y, Tcolor.z, Tcolor.w,Toutcolor.x, Toutcolor.y, Toutcolor.z, Toutcolor.w,0.0, 0.0 ,
							Ttext.pos.x + Ttext.size.x - (Ttext.font->GlyphList[392].Size.x),     ypos + h,		0,Tcolor.x, Tcolor.y, Tcolor.z, Tcolor.w,Toutcolor.x, Toutcolor.y, Toutcolor.z, Toutcolor.w, 0.0, 1.0 ,
							Ttext.pos.x + Ttext.size.x, ypos,			0,Tcolor.x, Tcolor.y, Tcolor.z, Tcolor.w,Toutcolor.x, Toutcolor.y, Toutcolor.z, Toutcolor.w, 1.0, 0.0 ,
							Ttext.pos.x + Ttext.size.x, ypos + h,		0,Tcolor.x, Tcolor.y, Tcolor.z, Tcolor.w,Toutcolor.x, Toutcolor.y, Toutcolor.z, Toutcolor.w, 1.0, 1.0
						};
						//*this << Drawing::Rectangle(Vec3(Ttext.pos.x + Ttext.size.x - (Ttext.font->GlyphList[392].Size.x), ypos, 0), Vec3(Ttext.pos.x + Ttext.size.x - (Ttext.font->GlyphList[392].Size.x) + (Ttext.font->GlyphList[392].Size.x), ypos + h, 0), Color::Blue, Color::Green, Color::Red, Color::Yellow, Vec2(0, 0), Vec2(0, 1), Vec2(1, 0), Vec2(1, 1), false);
						glBindTexture(GL_TEXTURE_2D, Ttext.font->GlyphList[392].TextureID);
						glBindBuffer(GL_ARRAY_BUFFER, moderntextvbo);
						memcpy(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY), newvertices, sizeof(newvertices));
						glUnmapBuffer(GL_ARRAY_BUFFER);
						glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
						deadend = true;
					}
				}
			}
			else
			{
				glBindTexture(GL_TEXTURE_2D, Ttext.Tglyph[i].TextureID);
				glBindBuffer(GL_ARRAY_BUFFER, moderntextvbo);
				memcpy(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY), vertices, sizeof(vertices));
				glUnmapBuffer(GL_ARRAY_BUFFER);
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			}
			posx += (Ttext.Tglyph[i].Advance >> 6) * Ttext.scale;
			UseSolidTexture();
			//Ttext.free();

			//*this << Drawing::Rectangle(Vec3(xpos, ypos, 0), Vec3(xpos + w, ypos + h, 0), Color::Blue, Color::Green, Color::Red, Color::Yellow, Vec2(0, 0), Vec2(0, 1), Vec2(1, 0), Vec2(1, 1), false);
		}


		//*this << Drawing::Rectangle(Vec3(Ttext.pos.x, Ttext.pos.y, 0), Vec3(Ttext.pos.x + Ttext.size.x, Ttext.pos.y + Ttext.size.y, 0), Color::Blue, Color::Green, Color::Red, Color::Yellow, Vec2(0, 0), Vec2(0, 1), Vec2(1, 0), Vec2(1, 1), false);
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
		moderntext_shader.Use();
		return *this;

	}


	//Renderer& Renderer::operator<< (const ext::Subwindow& gui)
	//{
	//	*this << Drawing::Rectangle(Vec3(gui.getWidgetBound().x, gui.getWidgetBound().y, 0), Vec3(gui.getWidgetBound().x + gui.getWidgetBound().z, gui.getWidgetBound().y + gui.getWidgetBound().w, 0), Color::Blue, Color::Green, Color::Red, Color::Yellow, Vec2(0, 0), Vec2(0, 1), Vec2(1, 0), Vec2(1, 1), false);
	//	return *this;
	//}
}