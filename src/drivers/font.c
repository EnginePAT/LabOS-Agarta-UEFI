#include <drivers/font.h>

void draw_char(char c, int x, int y, RGB color, struct limine_framebuffer* fb, volatile uint32_t* fb_ptr)
{
    const uint8_t* glyph = vga_font[(uint8_t)c];
    for (int row = 0; row < FONT_HEIGHT; row++) {
        for (int col = 0; col < FONT_WIDTH; col++) {
            if (glyph[row] & (0x80 >> col)) {
                putpixel(x + col, y + row, color, fb, fb_ptr);
            }
        }
    }
}

void draw_string(const char* str, int x, int y, RGB color, struct limine_framebuffer* fb, volatile uint32_t* fb_ptr)
{
    while (*str)
    {
        draw_char(*str++, x, y, color, fb, fb_ptr);
        x += FONT_WIDTH;
    }
}
