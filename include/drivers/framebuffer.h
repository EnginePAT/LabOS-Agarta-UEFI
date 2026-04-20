#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <core/limine.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct RGB {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} RGB;

extern struct limine_framebuffer* fb;
extern volatile uint32_t* fb_ptr;

bool fb_init(struct limine_framebuffer* _fb, volatile uint32_t* _fb_ptr);
void putpixel(int x, int y, RGB color);

#endif      // FRAMEBUFFER_H
