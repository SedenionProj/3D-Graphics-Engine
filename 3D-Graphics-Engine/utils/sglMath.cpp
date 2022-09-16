#include "sglMath.h"

int sgl::mini(const int x, const int y, const int z) {
	return x < y ? (x < z ? x : z) : (y < z ? y : z);
}
int sgl::maxi(const int& x, const int& y, const int& z) {
	return x > y ? (x > z ? x : z) : (y > z ? y : z);
}
sgl::Vec3f sgl::MultMatVec(Vec3f& i, mat4& m) {
	Vec3f o;
	o.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
	o.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
	o.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
	float w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];

	if (w != 0.0f) {
		o.x /= w; o.y /= w; o.z /= w;
	}
	return o;
}
void sgl::normalize(Vec3f& i) {
	float l = sqrt(i.x * i.x + i.y * i.y + i.z * i.z);
	i.x /= l; i.y /= l; i.z /= l;
}

sgl::mat4 sgl::MatProjection(float fov, float AspectRatio, float fNear, float fFar) {
	mat4 proj;
	float fovRad = 1.0f / tanf((fov * 3.14159f / 180.0f) * 0.5f);
	proj.m[0][0] = fovRad * AspectRatio;
	proj.m[1][1] = fovRad;
	proj.m[2][2] = fFar / (fFar - fNear);
	proj.m[3][2] = (-fFar * fNear) / (fFar - fNear);
	proj.m[2][3] = 1.0f;
	proj.m[3][3] = 0.0f;
	return proj;
}

sgl::mat4 sgl::MatRotationX(float& angle) {
	mat4 o;
	o.m[0][0] = 1.0f;
	o.m[1][1] = cosf(angle);
	o.m[1][2] = -sinf(angle);
	o.m[2][1] = sinf(angle);
	o.m[2][2] = cosf(angle);
	o.m[3][3] = 1.0f;
	return o;
}

sgl::mat4 sgl::MatRotationY(float angle) {
	mat4 o;
	o.m[0][0] = cosf(angle);
	o.m[0][2] = sinf(angle);
	o.m[1][1] = 1.0f;
	o.m[2][0] = -sinf(angle);
	o.m[2][2] = cosf(angle);
	o.m[3][3] = 1.0f;
	return o;
}

sgl::mat4 sgl::MultMat(mat4& a, mat4& b) {
	mat4 c;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			c.m[j][i] = a.m[j][0] * b.m[0][i] + a.m[j][1] * b.m[1][i] + a.m[j][2] * b.m[2][i] + a.m[j][3] * b.m[3][i];
		}
	}
	return c;
}

sgl::mat4 sgl::Mat_MakeIdentity()
{
	mat4 matrix;
	matrix.m[0][0] = 1.0f;
	matrix.m[1][1] = 1.0f;
	matrix.m[2][2] = 1.0f;
	matrix.m[3][3] = 1.0f;
	return matrix;
}

float sgl::dotProduct(const Vec3f& a, const Vec3f& b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

sgl::Vec3f sgl::addVec(const Vec3f& a, const Vec3f& b) {
	return { a.x + b.x, a.y + b.y, a.z + b.z };
}

sgl::Vec3f sgl::subVec(const Vec3f& a, const Vec3f& b) {
	return { a.x - b.x, a.y - b.y, a.z - b.z };
}

sgl::Vec3f sgl::multVec(const Vec3f& a, float k) {
	return { a.x * k, a.y * k, a.z * k };
}

sgl::Vec3f sgl::crossProd(const Vec3f& a, const Vec3f& b) {
	return { a.y * b.z - a.z * b.y,a.z * b.x - a.x * b.z,a.x * b.y - a.y * b.x };
}

sgl::mat4 sgl::lookAt(Vec3f& from, Vec3f& to, Vec3f& vup) {
	Vec3f forward = subVec(from, to);
	normalize(forward);
	Vec3f right = crossProd(vup, forward);
	Vec3f up = crossProd(forward, right);

	mat4 camToWorld;

	camToWorld.m[0][0] = right.x;
	camToWorld.m[0][1] = right.y;
	camToWorld.m[0][2] = right.z;
	camToWorld.m[1][0] = up.x;
	camToWorld.m[1][1] = up.y;
	camToWorld.m[1][2] = up.z;
	camToWorld.m[2][0] = forward.x;
	camToWorld.m[2][1] = forward.y;
	camToWorld.m[2][2] = forward.z;
	camToWorld.m[3][0] = from.x;
	camToWorld.m[3][1] = from.y;
	camToWorld.m[3][2] = from.z;
	camToWorld.m[3][3] = 1.0f;

	return camToWorld;
}

sgl::mat4 sgl::MatInv(mat4& m) {
	mat4 matrix;
	matrix.m[0][0] = m.m[0][0]; matrix.m[0][1] = m.m[1][0]; matrix.m[0][2] = m.m[2][0]; matrix.m[0][3] = 0.0f;
	matrix.m[1][0] = m.m[0][1]; matrix.m[1][1] = m.m[1][1]; matrix.m[1][2] = m.m[2][1]; matrix.m[1][3] = 0.0f;
	matrix.m[2][0] = m.m[0][2]; matrix.m[2][1] = m.m[1][2]; matrix.m[2][2] = m.m[2][2]; matrix.m[2][3] = 0.0f;
	matrix.m[3][0] = -(m.m[3][0] * matrix.m[0][0] + m.m[3][1] * matrix.m[1][0] + m.m[3][2] * matrix.m[2][0]);
	matrix.m[3][1] = -(m.m[3][0] * matrix.m[0][1] + m.m[3][1] * matrix.m[1][1] + m.m[3][2] * matrix.m[2][1]);
	matrix.m[3][2] = -(m.m[3][0] * matrix.m[0][2] + m.m[3][1] * matrix.m[1][2] + m.m[3][2] * matrix.m[2][2]);
	matrix.m[3][3] = 1.0f;
	return matrix;
}
