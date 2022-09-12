#pragma once
#include <math.h>

namespace sgl {
	struct Vec2i {
		int x, y, z;
	};

	struct Vec2f {
		float x, y, z;
	};

	struct Vec3i {
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

	int mini(const int x, const int y, const int z);

	int maxi(const int& x, const int& y, const int& z);

	Vec3f MultMatVec(Vec3f& i, mat4& m);

	void normalize(Vec3f& i);

	mat4 MatProjection(float fov, float AspectRatio, float fNear, float fFar);

	mat4 MatRotationX(float& angle);

	mat4 MatRotationY(float angle);

	mat4 MultMat(mat4& a, mat4& b);

	mat4 Mat_MakeIdentity();

	float dotProduct(const Vec3f& a, const Vec3f& b);

	Vec3f addVec(const Vec3f& a, const Vec3f& b);

	Vec3f subVec(const Vec3f& a, const Vec3f& b);

	Vec3f multVec(const Vec3f& a, float k);

	Vec3f crossProd(const Vec3f& a, const Vec3f& b);

	mat4 lookAt(Vec3f& from, Vec3f& to, Vec3f& vup);

	mat4 MatInv(mat4& m);

}