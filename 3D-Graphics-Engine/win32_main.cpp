#include "sgl.h"

int WINAPI wWinMain(HINSTANCE Instance, HINSTANCE PrevInstance, PWSTR CmdLine, int CmdShow) {

    
    sgl::screen::init(Instance);
    
    float dt = 0.166666f;
    LARGE_INTEGER frame_begin;
    QueryPerformanceCounter(&frame_begin);
    float performance_frequency;
    {
        LARGE_INTEGER perf;
        QueryPerformanceFrequency(&perf);
        performance_frequency = (float)perf.QuadPart;
    }

    bool Running = true;
    while (Running) {
        
        sgl::screen::clear(0x000000);
        MSG Message;
        while (PeekMessage(&Message, nullptr, 0, 0, PM_REMOVE)) {
            switch (Message.message) {
                case WM_QUIT: {Running = false;}
            }
            TranslateMessage(&Message);
            DispatchMessage(&Message);
        }

        sgl::screen::draw();
        
        LARGE_INTEGER frame_end;
        QueryPerformanceCounter(&frame_end);
        dt = (float)(frame_end.QuadPart - frame_begin.QuadPart)/ performance_frequency;
        frame_begin = frame_end;
        
    }

    return 0;
}