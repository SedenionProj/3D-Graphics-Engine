#pragma once
#include <windows.h>

namespace sgl{
	namespace screen {
		extern int width;
		extern int height;
		extern BITMAPINFO buffer_bitmap_info;
		extern void* buffer_memory;
		extern HDC hdc;
		extern MSG Message;
		extern bool running;
		LRESULT CALLBACK WindowProc(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam);
		void draw();
		void clear(unsigned int color);
		void msg();
		int init(HINSTANCE& Instance);
	}
};