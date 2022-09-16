#include "sgl.h"

void sgl::loop() {
	sgl::Vec3f a = {4,5,6};
	sgl::Vec3f b = { 6,7 ,8};
	sgl::mat4 projection = sgl::MatProjection(90, (float)1 / (float)1, 0.1f, 1000.0f);

	sgl::Vec3f d = sgl::addVec(a, b);
	sgl::Vec3f e = sgl::addVec(d, d);
}