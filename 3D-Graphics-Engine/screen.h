#pragma once
#include <windows.h>

namespace sgl{
	namespace screen {
		extern int width;
		extern int height;
		extern BITMAPINFO buffer_bitmap_info;
		extern void* buffer_memory;
		extern HDC hdc;
		LRESULT CALLBACK WindowProc(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam);
		void draw();
		void clear(unsigned int color);
		int init(HINSTANCE& Instance);
	}
};