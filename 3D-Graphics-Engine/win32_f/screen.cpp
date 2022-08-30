#include "declaration.cpp"
#include <windows.h>
#include "../main.cpp"

bool running = true;
void* buffer_memory;
int w = 1280;
int h = 720;
BITMAPINFO buffer_bitmap_info;

#include "../utils/math.h"

mat4 projection;
mat4 rotationX, rotationY;
Vec3f cameraPos = { 0.0f,0.0f,-1.0f };
Vec3f lookDir;

#include "renderer.cpp"
#include "../utils/raster.cpp"

LRESULT CALLBACK WindowProc(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam) {
    switch (Message) {
        case WM_DESTROY: { PostQuitMessage(0); } break;
        case WM_SIZE: {
            RECT rect;
            GetClientRect(Window, &rect);
            w = rect.right - rect.left;
            h = rect.bottom - rect.top;

            int buffer_size = w * h * sizeof(unsigned int);
            if (buffer_memory) VirtualFree(buffer_memory, 0, MEM_RELEASE);
            buffer_memory = VirtualAlloc(0, buffer_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
            buffer_bitmap_info.bmiHeader.biSize = sizeof(buffer_bitmap_info.bmiHeader);
            buffer_bitmap_info.bmiHeader.biWidth = w;
            buffer_bitmap_info.bmiHeader.biHeight = h;
            buffer_bitmap_info.bmiHeader.biPlanes = 1;
            buffer_bitmap_info.bmiHeader.biBitCount = 32;
            buffer_bitmap_info.bmiHeader.biCompression = BI_RGB;
        }
        default: { return DefWindowProc(Window, Message, WParam, LParam); }
    }
    return 0;
}

int WINAPI wWinMain(HINSTANCE Instance, HINSTANCE PrevInstance, PWSTR CmdLine, int CmdShow) {

    WNDCLASS WindowClass = {};
    const wchar_t ClassName[] = L"MyWindowClass";
    WindowClass.lpfnWndProc = WindowProc;
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
    init();
    while (Running) {
        
        clear_screen(0x000000);
        MSG Message;
        while (PeekMessage(&Message, nullptr, 0, 0, PM_REMOVE)) {
            switch (Message.message) {
                case WM_QUIT: {Running = false;}
            }
            TranslateMessage(&Message);
            DispatchMessage(&Message);
        }

        main_loop(dt);

        StretchDIBits(hdc, 0, 0, w, h, 0, 0, w, h, buffer_memory, &buffer_bitmap_info, DIB_RGB_COLORS, SRCCOPY);
        LARGE_INTEGER frame_end;
        QueryPerformanceCounter(&frame_end);
        dt = (float)(frame_end.QuadPart - frame_begin.QuadPart)/ performance_frequency;
        frame_begin = frame_end;
    }

    return 0;
}