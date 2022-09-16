#pragma once
#include <Windows.h>
namespace sgl {
	namespace screen {
		extern float dt;
		extern float performance_frequency;
		extern LARGE_INTEGER frame_begin;
		extern LARGE_INTEGER perf;
		extern LARGE_INTEGER frame_end;
		void time_begin();
		void time_update();
	}
}