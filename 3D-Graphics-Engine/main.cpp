#include "sgl.h"

sgl::mat4 projection;
sgl::mat4 view;
sgl::mat4 model;

sgl::Vec3f cameraPos = { 0.0f,0.0f,-2.0f };
sgl::Vec3f cameraFront = { 0,0,1 };
sgl::Vec3f cameraUp = { 0,-1,0 };

float cameraRotX = 0.57f;
float cameraRotY = 0.f;

float t = 0;
float flag = 0;

sgl::Triangle t1 = {
		-0.5f,
		-0.5f,
		.0f,

		0.5f,
		-0.5f,
		.0f,

		0.0f,
		0.5f,
		.0f,
};

sgl::Vec2i transform(sgl::Vec3f vertices) {
	
	sgl::Vec3f proj =  projection * view * model * vertices;
	sgl::Vec2i v;
	v.x = (int)((proj.x + 1) * 0.5f * (float)sgl::screen::width);
	v.y = (int)((proj.y + 1) * 0.5f * (float)sgl::screen::height);
	return v;
}

void sgl::init() {

	model = sgl::Mat_MakeIdentity();
	projection = sgl::MatProjection(90, (float)sgl::screen::height / (float)sgl::screen::width, 0.1f, 1000.0f);
}

void rot(float x, float y) {
	cameraRotX += x;
	cameraRotY += y;
	sgl::Vec3f dir = { 0,0,0 };;
	dir.x = cos(cameraRotX) * cos(cameraRotY);
	dir.y = sin(cameraRotY);
	dir.z = sin(cameraRotX) * cos(cameraRotY);
	sgl::normalize(dir);
	cameraFront = dir;
}

void sgl::loop() {
	//model = MatRotationX(t);
	view = sgl::MatInv(lookAt(cameraPos, cameraPos + cameraFront, cameraUp));

	if (GetAsyncKeyState(VK_SPACE))
		cameraPos.y += 0.05f;
	if (GetAsyncKeyState(VK_SHIFT))
		cameraPos.y -= 0.05f;
	if (GetAsyncKeyState(VK_Q))
		cameraPos = cameraPos + sgl::crossProd(cameraFront, cameraUp) * 0.05f;
	if (GetAsyncKeyState(VK_D))
		cameraPos = cameraPos + sgl::crossProd(cameraFront,cameraUp) * -0.05f;
	if (GetAsyncKeyState(VK_Z))
		cameraPos = cameraPos + cameraFront * 0.05f;
	if (GetAsyncKeyState(VK_S))
		cameraPos = cameraPos + cameraFront * -0.05f;
	if (GetAsyncKeyState(VK_LEFT))
		rot(-0.01, 0);
	if (GetAsyncKeyState(VK_RIGHT))
		rot(0.01, 0);
	if (GetAsyncKeyState(VK_UP))
		rot(0, 0.01);
	if (GetAsyncKeyState(VK_DOWN))
		rot(0, -0.01);

	sgl::Vec2i V0 = transform(t1.v[0]);
	sgl::Vec2i V1 = transform(t1.v[1]);
	sgl::Vec2i V2 = transform(t1.v[2]);

	t += 0.01f;

	std::triangle(V0,V1,V2);
}