#pragma once
#include <windows.h>

namespace sgl{
	namespace screen {
		extern int width;
		extern int height;
		extern BITMAPINFO buffer_bitmap_info;
		extern void* buffer_memory;
		LRESULT CALLBACK WindowProc(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam);
		void draw(HDC& hdc);
		void clear_screen(unsigned int color);
	}
	
};