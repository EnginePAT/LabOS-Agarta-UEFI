#include "core/util.h"
#include <arch/x86_64/pic.h>
#include <stdint.h>

bool pic_init() {
    // Get the masks
    uint8_t mask0 = inb(0x21);
    uint8_t mask1 = inb(0xA1);

    // Send 0x11 to master and slave to initialize them
    outb(0x20, 0x11);       // Master
    outb(0xA0, 0x11);       // Slave

    outb(0x21, 0x20);
    outb(0xA1, 0x28);

    outb(0x21, 0x04);
    outb(0xA1, 0x02);

    outb(0x21, 0x01);
    outb(0xA1, 0x01);

    // Restore masks
    outb(0x21, mask0);
    outb(0xA1, mask1);

    return true;
}

void pic_send_eoi(uint8_t irq) {
    if (irq >= 8)
        outb(0xA0, 0x20); // slave
    outb(0x20, 0x20);     // master
}
