#include "../sgl.h"

int WINAPI wWinMain(HINSTANCE Instance, HINSTANCE PrevInstance, PWSTR CmdLine, int CmdShow) {
    sgl::screen::init(Instance);
    sgl::init();
    while (sgl::screen::running) {
        sgl::screen::clear(0x000000);
        sgl::screen::msg();

        sgl::loop();
        sgl::screen::draw();
    }

    return 0;
}