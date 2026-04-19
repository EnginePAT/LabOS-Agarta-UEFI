#ifndef GDT_H
#define GDT_H

#include <stdint.h>
#include <stdbool.h>

struct gdt_entry_t {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t gran;           // High 4-bits = flags, low 4-bits = limit 16-19
    uint8_t base_high;
} __attribute__((packed));

struct gdtr_t {
    uint16_t limit;         // Size of GDT in bytes - 1
    uint64_t base;          // Address of GDT
} __attribute__((packed));

bool gdt_init();
extern void gdt_load(struct gdtr_t* gdtr);

#endif      // GDT_H
