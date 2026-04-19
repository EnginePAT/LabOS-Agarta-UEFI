#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

// LabOS specific includes
#include <core/limine.h>
#include <core/util.h>
#include <core/requests.h>
#include <arch/x86_64/gdt.h>
#include <arch/x86_64/idt.h>

typedef struct RGB {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} RGB;

// Halt and catch fire function.
static void hcf(void) {
    for (;;) {
        asm ("hlt");
    }
}

void putpixel(int x, int y, RGB color, struct limine_framebuffer* fb, volatile uint32_t* fb_ptr) {
    fb_ptr[y * (fb->pitch / 4) + x] = (color.r << 16) | (color.g << 8) | color.b;
}

void drawrect(int x, int y, int w, int h, RGB color, struct limine_framebuffer* fb, volatile uint32_t* fb_ptr)
{
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            // Now we can compute the pixel offsets
            int offsetX = (x + w) - i;
            int offsetY = (y + h) - j;
            putpixel(offsetX, offsetY, color, fb, fb_ptr);
        }
    }
}

// The following will be our kernel's entry point.
// If renaming kernel_main() to something else, make sure to change the
// linker script accordingly.
void kernel_main(void) {
    // Ensure the bootloader actually understands our base revision (see spec).
    if (LIMINE_BASE_REVISION_SUPPORTED(limine_base_revision) == false) {
        hcf();
    }

    // Ensure we got a framebuffer.
    if (framebuffer_request.response == NULL
     || framebuffer_request.response->framebuffer_count < 1) {
        hcf();
    }

    // Initialize the GDT & IDT
    gdt_init();
    idt_init();

    struct limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];
    volatile uint32_t *fb_ptr = framebuffer->address;

    // Print a nice pattern to screen as an example.
    // Note: we assume the framebuffer model is RGB with 32-bit pixels.
    for (size_t y = 0; y < framebuffer->height; y++) {
        for (size_t x = 0; x < framebuffer->width; x++) {
            uint32_t nX = x * 255 / framebuffer->width;
            uint32_t nY = y * 255 / framebuffer->height;
            fb_ptr[y * (framebuffer->pitch / 4) + x] = (nY << 8) | nX;
        }
    }

    RGB color = { 255, 255, 255 };
    drawrect(100, 100, 200, 300, color, framebuffer, fb_ptr);

    // We're done, just hang...
    hcf();
}
