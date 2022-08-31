#include "sgl.h"

int WINAPI wWinMain(HINSTANCE Instance, HINSTANCE PrevInstance, PWSTR CmdLine, int CmdShow) {

    WNDCLASS WindowClass = {};
    const wchar_t ClassName[] = L"MyWindowClass";
    WindowClass.lpfnWndProc = sgl::screen::WindowProc;
    WindowClass.hInstance = Instance;
    WindowClass.lpszClassName = ClassName;

    if (!RegisterClass(&WindowClass)) {
        MessageBox(0, L"RegisterClass failed", 0, 0);
        return GetLastError();
    }

    HWND Window = CreateWindowEx(0, ClassName, L"Program",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT,
        0, 0, Instance, 0);
    HDC hdc = GetDC(Window);
    if (!Window) {
        MessageBox(0, L"CreateWindowEx failed", 0, 0);
        return GetLastError();
    }
    bool Running = true;
    float dt = 0.166666f;
    LARGE_INTEGER frame_begin;
    QueryPerformanceCounter(&frame_begin);
    float performance_frequency;
    {
        LARGE_INTEGER perf;
        QueryPerformanceFrequency(&perf);
        performance_frequency = (float)perf.QuadPart;
    }
    while (Running) {
        
        sgl::screen::clear_screen(0x000000);
        MSG Message;
        while (PeekMessage(&Message, nullptr, 0, 0, PM_REMOVE)) {
            switch (Message.message) {
                case WM_QUIT: {Running = false;}
            }
            TranslateMessage(&Message);
            DispatchMessage(&Message);
        }

        sgl::screen::draw(hdc);
        
        LARGE_INTEGER frame_end;
        QueryPerformanceCounter(&frame_end);
        dt = (float)(frame_end.QuadPart - frame_begin.QuadPart)/ performance_frequency;
        frame_begin = frame_end;
    }

    return 0;
}