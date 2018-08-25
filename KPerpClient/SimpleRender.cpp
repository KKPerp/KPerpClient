#include <string>

#include <time.h>

#include <thread>

//#include "KPerpEngine.hpp"

#include "KPerpCore\Main.hpp"
#include "KPerpCore\OpenGLTools.hpp"
#include "KPerpCore\Drawing.hpp"
#include "KPerpCore\Resource.hpp"

#include <iostream>

#include <map>

//#include <chrono>

using namespace kp;
//using namespace kp::Tools;
//using namespace kp::Maths;

//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
int main() {
	Window window(40, 1000, 600, "KPerp Beta", WindowStyle::OverlappedWindow);
	//window.useView(1);
	Font font;

	ImageFile _fontf("Font.png", 1);

	//MODERN TEXT
	ModernFont mfont = ModernFont("PlataleDef.ttf", 72);

	kp::Texture _font(window, _fontf);
	
	_fontf.Free();

	{
		font = Font(_font, 24, 32, 56, '!', '~', 0, 1);

		int _CharacterWidth[] = {
		  //!  "  #  $  %  &  '  (  )  *  +  ,  -  .  /  0  1  2  3  4  5  6  7  8  9
			1 ,5 ,18,12,18,18,2 ,18,18,9 ,9 ,2 ,9 ,2 ,24,24,24,24,24,24,24,24,24,24,24,
		  //:  ;  <  =  >  ?  @  A  B  C  D  E  F  G  H  I  J  K  L  M  N  O  P  Q  R
			2 ,2 ,24,24,24,12,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,
		  //S  T  U  V  W  X  Y  Z  [  \  ]  ^  _  `  a  b  c  d  e  f  g  h  i  j  k
			24,24,24,24,24,24,24,24,24,24,24,12,24,6 ,15,15,12,15,15,12,15,14,12,15,12,
		  //l  m  n  o  p  q  r  s  t  u  v  w  x  y  z  {  |  }  ~
			12,22,12,15,15,15,12,12,15,12,12,23,16,12,12,11,1 ,1 ,20

		};

		font.setWidth(_CharacterWidth);
	}

	window.EnableBlending(BlendFactor::SourceAlpha, BlendFactor::OneMinusSourceAlpha);

	ImageFile _framef("Frame.png", 1);

	kp::Texture frame = kp::Texture(window, _framef);

	_framef.Free();

	
	Drawing::VertexArray v;
	v << Drawing::Vertex(Vec3(500, 100, 0), Vec4(1, 0, 0, 1), Vec2(0, 0));
	v << Drawing::Vertex(Vec3(800, 500, 0), Vec4(0, 1, 0, 1), Vec2(1, 0));
	v << Drawing::Vertex(Vec3(200, 500, 0), Vec4(0, 0, 1, 1), Vec2(0, 1));
	v.setType(Drawing::VertexArray::Triangles);

	//Graphic g(v, gg);
	

	glClearColor(0, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	float varray[] = {
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,1.0f,   1.0f, 1.0f,
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,1.0f,   1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,1.0f,   0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,1.0f,   0.0f, 1.0f
	};

	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	using Shader = kp::OpenGL::Shader;

	OpenGL::VertexArray va(varray, sizeof(varray), indices, sizeof(indices));
	va.Section(0, 3, 9, 0);
	va.Section(1, 4, 9, 3);
	va.Section(2, 2, 9, 7);

	Shader shader = Shader(NULL, NULL);

	float _f[] = { 0.0f, 1.0f, 2.0f, 3.0f, 4.0f };

	shader.Begin(Shader::Vertex, 1);
	Vector<double, 5> v5(0.0, 1.0, 2.0, 3.0, 4.0);
	v5 += Vector<double, 5>(3.0, 4.0, 5.0, 6.0, 7.0);
	shader += "#version 330 core";
	shader << "layout (location = 0) in vec3 aPos;";
	shader << "layout (location = 1) in vec4 aColor;";
	shader << "layout (location = 2) in vec2 aTexCoord;";
	shader << "out vec2 TexCoord;";
	shader << "out vec4 Color;";
	shader << ShaderDeclare;
	shader << "void main() {";
	shader << "    gl_Position = " << ShaderMultiply << " * vec4(aPos.x, aPos.y, aPos.z, 1.0);";
	shader << "    TexCoord = aTexCoord;";
	shader << "    Color = aColor;";
	shader << "}";

	shader.Submit();

	shader.End();

	shader.Begin(Shader::Fragment, 1);

	shader += "#version 330 core";
	shader << "out vec4 FragColor;";
	shader << "in vec2 TexCoord;";
	shader << "in vec4 Color;";
	shader << "uniform sampler2D tex;";
	shader << "void main() {";
	//shader << "    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);";
	shader << "    FragColor = texture(tex,TexCoord) * Color * ;";// 
	shader << "}";

	shader.Submit();

	shader.End();

	shader.Compile();

	//shader.Use();

	char log[1000];
	shader.getLog(Shader::ShaderType::Fragment, log, 1000);

	//shader.Use();

	frame.Bind();

	//va.Bind();
	//va.Draw(GL_TRIANGLES, 6);

	//window.LoadIdentity();

	Matrix<float, 4, 4> testmatrix;

	testmatrix = Translate(testmatrix, Vec3(50, 50, 0));
	testmatrix = Rotate(testmatrix, radians_const(0.0f), Vec3(0, 0, 1));
	//testmatrix = Scale(testmatrix, Vec3(1, 0.5, 1));

	Vec4 testvec4(1, 0, 0, 0);

	Vector4<float> _v4 = testvec4;

	//window.Combine(testmatrix);

	//testvec4 = testmatrix * testvec4;

	//window.setTarget(gg);
	//window.Draw(Drawing::Triangle(Vec3(0, 0, 0),
	//	Vec3(100, 50, 0),
	//	Vec3(50, 100, 0)));
	//window.resetTarget();

	//View primaryview({ 0, 0, 250, 500 }, { 0, 0, (float)window.ClientSize().x, (float)window.ClientSize().y });
	View primaryview({ 0, 0, 500, 300 }, { 100, 0, 1000, 600 });
	View secondaryview({ 0, 0, 250, 500 }, { 250, 0, 500, 500 });

	View transformingview({ 0, 0, 500, 500 }, { 500, 0, 1000, 500 });

	//window.setTarget(primaryview);
	//window.resetTarget();

	Text simpletext(font, Vec2(100, 200), "~#00ffffSimple Text LOL~~");
	
	while (window.isActive()) {
		window.Clear(Color(0, 64, 64, 255));

		Vec2 mousepos = window.ViewMousePosFloat();

		window << Text(font, Vec2(50, 200), "~#00ffffSimple ~#ffff00Text ~#ff00ffLOL");
		
		window << Sprite(frame, Vec2(10, 10));

		window << (Sprite(frame, Vec2(116, 42)) * Transform(Vec2(32,32),Vec2(1,1), mousepos.x));

		window.UseSolidTexture();

		window << v;
		window << ModernText(mfont, Vec2(50, 300), "This is Modern Text", Color(128, 128, 128, 255));
		//window << Sprite(_font, 10, 10);
		window.Update();
		kp::Event e = window.getEvent();
		//std::cout << time(0) << "\n";
		if (e == kp::Event::MouseWheelMoved) {
			std::cout << window.MouseWheel() << "\n";
		}

		if (e == kp::Event::WindowChanged) {
			std::cout << "CHANGE";
			window.updateViewPosition();
			//window.restoreView();
		}
		if (e == kp::Event::WindowMoved) {
			std::cout << "MOVE";
		}
		if (window.keyPressed(Key::Escape)) {
			window.ExitFullScreen(WindowStyle::OverlappedWindow);
		}
		//if (e == kp::Event::MouseMove) {
		//std::cout << w.MousePos().x << "," << w.MousePos().y << "\n";
		//}

		if (e != kp::Event::Close) {
			window.popEvent();
		}
		else {
			window.Destroy();
		}
	}

	return 0;
}