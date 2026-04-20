#include "drivers/keyboard.h"
#include <arch/x86_64/idt.h>
#include <stdint.h>
#include <stdbool.h>
#include <drivers/framebuffer.h>
#include <drivers/font.h>
#include <arch/x86_64/pic.h>

volatile struct idt_entry_t idt_entries[256];
extern uint64_t isr_stub_table[256];

char* exception_messages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",
    "Double fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment not present",
    "Stack fault",
    "General protection fault",
    "Page fault",
    "Unknown Interrupt",
    "Coprocessor Fault",
    "Alignment Fault",
    "Machine Check", 
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

void idt_set_entry(uint8_t vector, void* handler) {
    uint64_t addr = (uint64_t)handler;
    idt_entries[vector].base_low  = addr & 0xFFFF;
    idt_entries[vector].base_mid  = (addr >> 16) & 0xFFFF;
    idt_entries[vector].base_high = (addr >> 32) & 0xFFFFFFFF;
    idt_entries[vector].selector  = 0x08;
    idt_entries[vector].flags     = 0x8E;
    idt_entries[vector].ist       = 0;
    idt_entries[vector].reserved  = 0;
}

void isr_handler(uint64_t* stack) {
    (void)stack;

    // TODO: Print an exception message
    RGB red = { 255, 0, 0 };
    // draw_string(exception_messages[stack], 10, 10, color, struct limine_framebuffer *fb, volatile uint32_t *fb_ptr);

    uint64_t vector = stack[15];

    draw_string("INT", 0, 10, (RGB){255, 255, 0});
    
    if (vector < 32) {
        // CPU exception — print and hang
        draw_string(exception_messages[vector], 0, 0, red);
        for(;;);
    } else if (vector == 33) {
        draw_string("KEY!", 400, 400, (RGB){255, 0, 0});
        keyboard_handler();
        pic_send_eoi(1);
    } else if (vector < 48) {
        // Hardware IRQ — send EOI and return
        pic_send_eoi(vector - 32);
    }
}

bool idt_init(struct limine_framebuffer* _fb, volatile uint32_t* _fb_ptr) {
    fb = _fb;
    fb_ptr = _fb_ptr;

    for (int i = 0; i < 256; i++) {
        idt_set_entry(i, (void*)isr_stub_table[i]);
    }
    struct idtr_t idtr;
    idtr.limit = (sizeof(struct idt_entry_t) * 256) - 1;
    idtr.base  = (uint64_t)&idt_entries;
    idt_load(&idtr);
    return true;
}
