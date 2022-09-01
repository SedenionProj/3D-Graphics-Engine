#include "sgl.h"

int WINAPI wWinMain(HINSTANCE Instance, HINSTANCE PrevInstance, PWSTR CmdLine, int CmdShow) {

    
    sgl::screen::init(Instance);
    
    

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
    }

    return 0;
}