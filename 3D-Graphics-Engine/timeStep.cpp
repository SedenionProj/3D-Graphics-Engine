#include "timeStep.h"
float sgl::screen::dt;
float sgl::screen::performance_frequency;
LARGE_INTEGER sgl::screen::frame_begin;
LARGE_INTEGER sgl::screen::perf;
LARGE_INTEGER sgl::screen::frame_end;

void sgl::screen::time_begin(){
    dt = 0.166666f;
    LARGE_INTEGER frame_begin;
    QueryPerformanceCounter(&frame_begin);
    float performance_frequency;
    {
        LARGE_INTEGER perf;
        QueryPerformanceFrequency(&perf);
        performance_frequency = (float)perf.QuadPart;
    }
}
void sgl::screen::time_update() {
    LARGE_INTEGER frame_end;
    QueryPerformanceCounter(&frame_end);
    dt = (float)(frame_end.QuadPart - frame_begin.QuadPart) / performance_frequency;
    frame_begin = frame_end;
}