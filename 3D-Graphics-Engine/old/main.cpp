#include <windows.h>
#include <iostream>
#include <cmath> 
#include "math.h"
#include "renderer.h"
#include "platform_common.cpp"
bool running = true;
void* buffer_memory;
int w = 1280;
int h = 720;
float t=0;
BITMAPINFO buffer_bitmap_info;

mat4 projection;
mat4 rotationX,rotationY;
Vec3f cameraPos = { 0.0f,0.0f,-1.0f };
Vec3f lookDir;


LRESULT CALLBACK WindowPrecedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM  lParam) {
	LRESULT result = 0;
	switch (uMsg) {
		case WM_CLOSE:
		case WM_DESTROY: {
			running = false;
		} break;
		case WM_SIZE: {
			RECT rect;
			GetClientRect(hwnd, &rect);
			w = rect.right - rect.left;
			h = rect.bottom- rect.top;
			int buffer_size = w * h * sizeof(unsigned int);
			if (buffer_memory) VirtualFree(buffer_memory,0 , MEM_RELEASE);
			buffer_memory = VirtualAlloc(0, buffer_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
			buffer_bitmap_info.bmiHeader.biSize = sizeof(buffer_bitmap_info.bmiHeader);
			buffer_bitmap_info.bmiHeader.biWidth = w;
			buffer_bitmap_info.bmiHeader.biHeight = h;
			buffer_bitmap_info.bmiHeader.biPlanes = 1;
			buffer_bitmap_info.bmiHeader.biBitCount = 32;
			buffer_bitmap_info.bmiHeader.biCompression = BI_RGB;
		}
		default: {
			result = DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	}
	return result;
}


Vec2i transform(Vec3f vertices) {
	lookDir = { 0,0,1 };
	Vec3f up = { 0,1,0 };
	Vec3f target = addVec(up, lookDir);
	mat4 camera = lookAt(cameraPos, target, up);
	mat4 view = MatInv(camera);

	mat4 world = MultMat(view,projection);

	Vec3f proj;
	MultMatVec(vertices, proj, world);
	Vec2i v;
	v.x = (int)((proj.x+1) * 0.5f * (float)w);
	v.y = (int)((proj.y+1) * 0.5f * (float)h);
	return v;
}
bool edge(const Vec2i& P, const Vec2i& V0, const  Vec2i& V1) {
	return ((V1.x - V0.x) * (P.y - V0.y) - (V1.y - V0.y) * (P.x - V0.x)) > 0;
}
void draw(const Triangle& triangle) {
	Vec3f normal, line1, line2;

	line1 = subVec(triangle.v[1], triangle.v[0]);

	line2 = subVec(triangle.v[2], triangle.v[0]);

	normal = crossProd(line1, line2);

	normalize(normal);

	if (normal.x * (triangle.v[0].x - cameraPos.x)+normal.y * (triangle.v[0].y - cameraPos.y)+normal.z*(triangle.v[0].z -cameraPos.z)>0.0f) {
		Vec3f light = { 0.0f,0.0f,-1.0f };
		normalize(light);
		float dp = dotProduct(normal, light);

		Vec2i V0 = transform(triangle.v[0]);
		Vec2i V1 = transform(triangle.v[1]);
		Vec2i V2 = transform(triangle.v[2]);

		int minx = mini(V0.x, V1.x, V2.x);
		int miny = mini(V0.y, V1.y, V2.y);
		int maxx = maxi(V0.x, V1.x, V2.x);
		int maxy = maxi(V0.y, V1.y, V2.y);

		minx = max(minx, 0);
		miny = max(miny, 0);
		maxx = min(maxx, w);
		maxy = min(maxy, h);

		Vec2i p;
		for (p.y = miny; p.y < maxy - 10; p.y++) {
			for (p.x = minx; p.x < maxx - 10; p.x++) {
				unsigned int* pixel = (unsigned int*)buffer_memory + int(p.y) * w + int(p.x);

				bool a = edge(p, V0, V1);
				bool b = edge(p, V1, V2);
				bool c = edge(p, V2, V0);

				if ((a and b and c) or (not(a) and not(b) and not(c))) {
					*pixel++ = 0xffffff;

				}

			}
		}
	}
	
}

int WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
	//Renderer renderer(w,h);
	
	WNDCLASS wc = {};
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpszClassName = L"myWindowClass";
	wc.lpfnWndProc = WindowPrecedure;

	RegisterClass(&wc);

	HWND window = CreateWindow(wc.lpszClassName, L"window", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, w, h, 0, 0, hInst, 0);
	HDC hdc = GetDC(window);

	MatProjection(90, (float)h / (float)w, 0.1f, 1000.0f, projection);


	Triangle t1 = {
		-0.5f,
		-0.5f,
		.0f,

		0.5f,
		-0.5f,
		.0f,

		0.0f,
		0.5f,
		.0f,
	};
	Triangle t2 = {
		-0.5f,
		-0.5f,
		1.0f,

		0.5f,
		-0.5f,
		1.0f,

		0.0f,
		0.5f,
		1.0f,
	};
	Triangle t3 = {
		-0.5f,
		-0.5f,
		1.0f,

		0.5f,
		-0.5f,
		1.0f,

		0.0f,
		0.5f,
		1.0f,
	};

	Input input = {};
	while (running)
	{
		MSG message;

		for (int i = 0; i < BUTTON_COUNT; i++) {
			input.buttons[i].changed = false;
		}

		while (PeekMessage(&message, window, 0, 0, PM_REMOVE)) {
			switch (message.message) {
				case WM_KEYUP:
				case WM_KEYDOWN:
				{
					UINT32 vk_code = (UINT32)message.wParam;
					bool is_down = ((message.lParam & (1 << 31)) == 0);
#define process_button(b, vk)\
case vk: {\
input.buttons[b].is_down = is_down;\
input.buttons[b].changed = true;\
} break;
					switch (vk_code)
					{
						process_button(BUTTON_UP, VK_UP);
						process_button(BUTTON_DOWN, VK_DOWN);
						process_button(BUTTON_LEFT, VK_LEFT);
						process_button(BUTTON_RIGHT, VK_RIGHT);
						process_button(BUTTON_SHIFT, VK_SHIFT);
						process_button(BUTTON_SPACE, VK_SPACE);
					} 
				} break;

				default: {
					TranslateMessage(&message);
					DispatchMessage(&message);
				}
			}
			
		}

		unsigned int* pixel = (unsigned int*)buffer_memory;
		for (int y = 0; y < h; y++) {
			for (int x = 0; x < w; x++) {
				*pixel++ = 0x000000;
			}
		}

		MatRotationY(rotationX, t);
		
		t+=0.01f;
		
		

		if (input.buttons[BUTTON_UP].is_down)
			cameraPos.y += 0.01f;
		if (input.buttons[BUTTON_DOWN].is_down)
			cameraPos.y -= 0.01f;
		if (input.buttons[BUTTON_LEFT].is_down)
			cameraPos.x -= 0.01f;
		if (input.buttons[BUTTON_RIGHT].is_down)
			cameraPos.x += 0.01f;
		if (input.buttons[BUTTON_SHIFT].is_down)
			cameraPos.z += 0.01f;
		if (input.buttons[BUTTON_SPACE].is_down)
			cameraPos.z -= 0.01f;
		
		draw(t1);
		//draw(t2, renderer);

		StretchDIBits(hdc, 0, 0, w, h, 0, 0, w, h, buffer_memory, &buffer_bitmap_info, DIB_RGB_COLORS, SRCCOPY);

		//renderer.render(hdc,buffer_memory, buffer_bitmap_info);
	}
}
