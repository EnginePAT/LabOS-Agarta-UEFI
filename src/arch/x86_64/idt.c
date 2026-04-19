#include <arch/x86_64/idt.h>
#include <stdbool.h>
#include <stdint.h>

struct idt_entry_t idt_entries[256];        // There are 256 IDT entries required
extern void* isr_stub_table[256];

void idt_set_entry(uint8_t vector, void* handler);

bool idt_init()
{
    for (int i = 0; i < 256; i++)
    {
        idt_set_entry(i, isr_stub_table[i]);
    }

    struct idtr_t idtr;
    idtr.limit = (sizeof(struct idt_entry_t) * 256) - 1;
    idtr.base = (uint64_t)&idt_entries;
    idt_load(&idtr);

    return true;
}

void idt_set_entry(uint8_t vector, void* handler) {
    // Fill in idt_entries[vector] here
    // selector = 0x08
    // flags = 0x8E
    // reserved = 0
    uint64_t addr = (uint64_t)handler;

    idt_entries[vector].base_low = addr & 0xFFFF;
    idt_entries[vector].base_mid = (addr >> 16) & 0xFFFF;
    idt_entries[vector].base_high = (addr >> 32) & 0xFFFFFFFF;

    idt_entries[vector].selector = 0x08;
    idt_entries[vector].flags = 0x8E;
    idt_entries[vector].reserved = 0;
    idt_entries[vector].ist = 0;
}

void isr_handler(uint64_t* stack) {
    // stack[0] = r15, ... stack[15] = rax
    // stack[16] = vector number
    // stack[17] = error code
    uint64_t vector = stack[16];
    uint64_t error  = stack[17];
    (void)vector;
    (void)error;
    // handle interrupt here later
}
