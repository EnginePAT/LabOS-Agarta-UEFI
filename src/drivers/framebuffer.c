#include "core/limine.h"
#include <drivers/framebuffer.h>
#include <stdint.h>

struct limine_framebuffer* fb;
volatile uint32_t* fb_ptr;

bool fb_init(struct limine_framebuffer* _fb, volatile uint32_t* _fb_ptr) {
    fb = _fb;
    fb_ptr = _fb_ptr;
    return true;
}

void putpixel(int x, int y, RGB color) {
    fb_ptr[y * (fb->pitch / 4) + x] = (color.r << 16) | (color.g << 8) | color.b;
}
