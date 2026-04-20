#ifndef IDT_H
#define IDT_H

#include <core/limine.h>
#include <stdbool.h>
#include <stdint.h>

struct idt_entry_t {
    uint16_t base_low;
    uint16_t selector;
    uint8_t  ist;
    uint8_t  flags;
    uint16_t base_mid;
    uint32_t base_high;
    uint32_t reserved;
} __attribute__((packed));

struct idtr_t {
    uint16_t limit;
    uint64_t base;
} __attribute__((packed));

bool idt_init(struct limine_framebuffer* _fb, volatile uint32_t* _fb_ptr);
void idt_set_entry(uint8_t vector, void* handler);
void isr_handler(uint64_t* stack);

extern void idt_load(struct idtr_t* idtr);
extern uint64_t isr_stub_table[256];

#endif  // IDT_H
