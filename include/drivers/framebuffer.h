#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <core/limine.h>

typedef struct RGB {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} RGB;

void putpixel(int x, int y, RGB color, struct limine_framebuffer* fb, volatile uint32_t* fb_ptr);

#endif      // FRAMEBUFFER_H
