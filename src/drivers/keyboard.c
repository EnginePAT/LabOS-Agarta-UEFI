#include <drivers/framebuffer.h>
#include <core/util.h>
#include <drivers/keyboard.h>
#include <drivers/font.h>
#include <stdint.h>

void keyboard_handler() {
    uint8_t scancode = inb(0x60);       // Get the scancode from port 0x60

    if (scancode & 0x80) return;        // Ignore key release

    static int x = 0;
    static int y = 0;

    // Convert the scancode to ascii
    if (scancode < sizeof(scancode_map) && scancode_map[scancode]) {

        char c = scancode_map[scancode];
        // Print it to the screen!
        draw_char(c, x, y, (RGB){255});

        x += 8; // FONT_WIDTH
    }
}
