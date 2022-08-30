void clear_screen(unsigned int color) {
    unsigned int* pixel = (unsigned int*)buffer_memory;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            *pixel++ = color;
        }
    }
}