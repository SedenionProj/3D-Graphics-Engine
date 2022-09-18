#pragma once
#include "../../sgl.h"

namespace std {
	bool edge(const sgl::Vec2i& P, const sgl::Vec2i& V0, const  sgl::Vec2i& V1);
	void triangle(const sgl::Vec2i& V0, const sgl::Vec2i& V1, const sgl::Vec2i& V2);
}