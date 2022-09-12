#include "screen.h"
#include "timeStep.h"

void*  sgl::screen::buffer_memory;
int sgl::screen::width;
int sgl::screen::height;
BITMAPINFO sgl::screen::buffer_bitmap_info;
HDC sgl::screen::hdc;
MSG sgl::screen::Message;
bool sgl::screen::running;

LRESULT sgl::screen::WindowProc(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam) {
    switch (Message) {
    case WM_DESTROY: { PostQuitMessage(0); } break;
    case WM_SIZE: {
        RECT rect;
        GetClientRect(Window, &rect);
        width = rect.right - rect.left;
        height = rect.bottom - rect.top;

        int buffer_size = width * height * sizeof(unsigned int);
        if (sgl::screen::buffer_memory) VirtualFree(sgl::screen::buffer_memory, 0, MEM_RELEASE);
        sgl::screen::buffer_memory = VirtualAlloc(0, buffer_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
        buffer_bitmap_info.bmiHeader.biSize = sizeof(buffer_bitmap_info.bmiHeader);
        buffer_bitmap_info.bmiHeader.biWidth = width;
        buffer_bitmap_info.bmiHeader.biHeight = height;
        buffer_bitmap_info.bmiHeader.biPlanes = 1;
        buffer_bitmap_info.bmiHeader.biBitCount = 32;
        buffer_bitmap_info.bmiHeader.biCompression = BI_RGB;
    }
    default: { return DefWindowProc(Window, Message, WParam, LParam); }
    }
    return 0;
}

void sgl::screen::clear(unsigned int color) {
    unsigned int* pixel = (unsigned int*)sgl::screen::buffer_memory;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            *pixel++ = color;
        }
    }
}

void sgl::screen::draw() {
	StretchDIBits(hdc, 0, 0, width, height, 0, 0, width, height, buffer_memory, &buffer_bitmap_info, DIB_RGB_COLORS, SRCCOPY);
    time_update();
}

int sgl::screen::init(HINSTANCE &Instance) {
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
    
    if (!Window) {
        MessageBox(0, L"CreateWindowEx failed", 0, 0);
        return GetLastError();
    }
    hdc = GetDC(Window);
    time_begin();
    running = true;
};

void sgl::screen::msg() {
    while (PeekMessage(&Message, nullptr, 0, 0, PM_REMOVE)) {
        switch (Message.message) {
        case WM_QUIT: {running = false; }
        }
        TranslateMessage(&Message);
        DispatchMessage(&Message);
    }
};