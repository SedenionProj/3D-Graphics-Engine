#include "sgl.h"

sgl::mat4 projection;
sgl::mat4 rotationX, rotationY;
sgl::Vec3f cameraPos = { 0.0f,0.0f,-2.0f };
sgl::Vec3f lookDir = { 0,0,1 };
sgl::Vec3f up = { 0,1,0 };

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
	projection = sgl::MatProjection(90, (float)sgl::screen::height / (float)sgl::screen::width, 0.1f, 1000.0f);
	sgl::Vec3f proj = MultMatVec(vertices, MultMat(MatInv(lookAt(cameraPos, addVec(up, lookDir), up)), projection));
	sgl::Vec2i v;
	v.x = (int)((proj.x + 1) * 0.5f * (float)sgl::screen::width);
	v.y = (int)((proj.y + 1) * 0.5f * (float)sgl::screen::height);
	return v;
}

void sgl::loop() {

	if (GetAsyncKeyState(VK_SPACE))
		cameraPos.y += 0.01f;
	if (GetAsyncKeyState(VK_SHIFT))
		cameraPos.y -= 0.01f;
	if (GetAsyncKeyState(VK_Q))
		cameraPos.x -= 0.01f;
	if (GetAsyncKeyState(VK_D))
		cameraPos.x += 0.01f;
	if (GetAsyncKeyState(VK_Z))
		cameraPos.z += 0.01f;
	if (GetAsyncKeyState(VK_S))
		cameraPos.z -= 0.01f;

	sgl::Vec2i V0 = transform(t1.v[0]);
	sgl::Vec2i V1 = transform(t1.v[1]);
	sgl::Vec2i V2 = transform(t1.v[2]);

	t += 0.01f;
	rotationX = MatRotationY(t);
	std::triangle(V0,V1,V2);
}