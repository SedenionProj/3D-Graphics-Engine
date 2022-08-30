#pragma once
struct Vec2i {
	int x, y, z;
};
struct Vec3f {
	float x, y, z;
};

struct mat4
{
	float m[4][4] = { 0 };
};

struct Triangle {
	Vec3f v[3];
};


int mini(const int x, const int y, const int z) {
	return x < y ? (x < z ? x : z) : (y < z ? y : z);
}
int maxi(const int& x, const int& y, const int& z) {
	return x > y ? (x > z ? x : z) : (y > z ? y : z);
}
void MultMatVec(Vec3f& i, Vec3f& o, mat4& m) {
	o.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
	o.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
	o.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
	float w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];

	if (w != 0.0f) {
		o.x /= w;o.y /= w;o.z /= w;
	}
}
void normalize(Vec3f& i) {
	float l = sqrtf(i.x * i.x + i.y * i.y + i.z * i.z);
	i.x /= l; i.y /= l; i.z /= l;
}

void MatProjection(float fov, float AspectRatio, float fNear, float fFar,mat4& proj) {
	float fovRad = 1.0f / tanf((fov * 3.14159f / 180.0f) * 0.5f);
	proj.m[0][0] = fovRad * AspectRatio;
	proj.m[1][1] = fovRad;
	proj.m[2][2] = fFar / (fFar - fNear);
	proj.m[3][2] = (-fFar * fNear) / (fFar - fNear);
	proj.m[2][3] = 1.0f;
	proj.m[3][3] = 0.0f;
}

void MatRotationX(mat4 &o, float &angle) {
	o.m[0][0] = 1.0f;
	o.m[1][1] = cosf(angle);
	o.m[1][2] = -sinf(angle);
	o.m[2][1] = sinf(angle);
	o.m[2][2] = cosf(angle);
	o.m[3][3] = 1.0f;
}

void MatRotationY(mat4& o, float angle) {
	o.m[0][0] = cosf(angle);
	o.m[0][2] = sinf(angle);
	o.m[1][1] = 1.0f;
	o.m[2][0] = -sinf(angle);
	o.m[2][2] = cosf(angle);
	o.m[3][3] = 1.0f;
}

mat4 MultMat(mat4& a, mat4& b) {
	mat4 c;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			c.m[j][i] = a.m[j][0] * b.m[0][i] + a.m[j][1] * b.m[1][i] + a.m[j][2] * b.m[2][i] + a.m[j][3] * b.m[3][i];
		}
	}
	return c;
}

mat4 Mat_MakeIdentity()
{
	mat4 matrix;
	matrix.m[0][0] = 1.0f;
	matrix.m[1][1] = 1.0f;
	matrix.m[2][2] = 1.0f;
	matrix.m[3][3] = 1.0f;
	return matrix;
}

float dotProduct(const Vec3f& a, const Vec3f& b) {
	return a.x* b.x + a.y * b.y + a.z * b.z;
}

Vec3f addVec(const Vec3f& a, const Vec3f& b) {
	return { a.x + b.x, a.y + b.y, a.z + b.z };
}

Vec3f subVec(const Vec3f &a, const Vec3f &b) {
	return { a.x - b.x, a.y - b.y, a.z - b.z };
}

Vec3f multVec(const Vec3f& a, float k) {
	return { a.x * k, a.y * k, a.z * k };
}

Vec3f crossProd(const Vec3f& a, const Vec3f& b) {
	return { a.y * b.z - a.z * b.y,a.z * b.x - a.x * b.z,a.x * b.y - a.y * b.x };
}

mat4 lookAt(Vec3f& from, Vec3f& to, Vec3f& vup) {
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

mat4 MatInv(mat4& m){
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