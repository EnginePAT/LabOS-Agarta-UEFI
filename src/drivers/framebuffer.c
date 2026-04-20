#include <drivers/framebuffer.h>

// __attribute__((used, section(".limine_requests")))
// static volatile struct limine_framebuffer_request framebuffer_request = {
//     .id = LIMINE_FRAMEBUFFER_REQUEST_ID,
//     .revision = 0
// };

void putpixel(int x, int y, RGB color, struct limine_framebuffer* fb, volatile uint32_t* fb_ptr) {
    fb_ptr[y * (fb->pitch / 4) + x] = (color.r << 16) | (color.g << 8) | color.b;
}
