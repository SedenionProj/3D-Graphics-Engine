#include "draw.h"


bool std::edge(const sgl::Vec2i& P, const sgl::Vec2i& V0, const sgl::Vec2i& V1)
{
	return ((V1.x - V0.x) * (P.y - V0.y) - (V1.y - V0.y) * (P.x - V0.x)) > 0;
}

void std::triangle(const sgl::Vec2i& V0, const sgl::Vec2i& V1, const sgl::Vec2i& V2)
{
	int minx = sgl::mini(V0.x, V1.x, V2.x);
	int miny = sgl::mini(V0.y, V1.y, V2.y);
	int maxx = sgl::maxi(V0.x, V1.x, V2.x);
	int maxy = sgl::maxi(V0.y, V1.y, V2.y);

	minx = max(minx, 0);
	miny = max(miny, 0);
	maxx = min(maxx, sgl::screen::width);
	maxy = min(maxy, sgl::screen::height);

	sgl::Vec2i p;
	for (p.y = miny; p.y < maxy; p.y++) {
		for (p.x = minx; p.x < maxx; p.x++) {
			unsigned int* pixel = (unsigned int*)sgl::screen::buffer_memory + int(p.y) * sgl::screen::width + int(p.x);

			bool a = edge(p, V0, V1);
			bool b = edge(p, V1, V2);
			bool c = edge(p, V2, V0);

			if ((a and b and c) or (not(a) and not(b) and not(c))) {
				*pixel++ = 0xffffff;

			}

		}
	}
}