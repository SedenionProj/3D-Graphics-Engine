#include "math.h"

Vec2i transform(Vec3f vertices) {
	lookDir = { 0,0,1 };
	Vec3f up = { 0,1,0 };
	Vec3f target = addVec(up, lookDir);
	mat4 camera = lookAt(cameraPos, target, up);
	mat4 view = MatInv(camera);

	mat4 world = MultMat(view, projection);

	Vec3f proj;
	MultMatVec(vertices, proj, world);
	Vec2i v;
	v.x = (int)((proj.x + 1) * 0.5f * (float)w);
	v.y = (int)((proj.y + 1) * 0.5f * (float)h);
	return v;
}
bool edge(const Vec2i& P, const Vec2i& V0, const  Vec2i& V1) {
	return ((V1.x - V0.x) * (P.y - V0.y) - (V1.y - V0.y) * (P.x - V0.x)) > 0;
}
void draw(const Vec2i& V0, const Vec2i& V1, const Vec2i& V2, const float& dp, void* buffer_memory) {
	int minx = mini(V0.x, V1.x, V2.x);
	int miny = mini(V0.y, V1.y, V2.y);
	int maxx = maxi(V0.x, V1.x, V2.x);
	int maxy = maxi(V0.y, V1.y, V2.y);

	minx = max(minx, 0);
	miny = max(miny, 0);
	maxx = min(maxx, w);
	maxy = min(maxy, h);

	Vec2i p;
	for (p.y = miny; p.y < maxy - 10; p.y++) {
		for (p.x = minx; p.x < maxx - 10; p.x++) {
			unsigned int* pixel = (unsigned int*)buffer_memory + int(p.y) * w + int(p.x);

			bool a = edge(p, V0, V1);
			bool b = edge(p, V1, V2);
			bool c = edge(p, V2, V0);

			if ((a and b and c) or (not(a) and not(b) and not(c))) {
				*pixel++ = 0xffffff;

			}

		}
	}
}