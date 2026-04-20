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

typedef struct {
    uint32_t reserved0;
    uint64_t rsp0;      // kernel stack pointer (ring 0)
    uint64_t rsp1;
    uint64_t rsp2;
    uint64_t reserved1;
    uint64_t ist[7];    // interrupt stack table
    uint64_t reserved2;
    uint16_t reserved3;
    uint16_t iopb;      // I/O permission bitmap offset
} __attribute__((packed)) tss_t;

typedef struct {
    uint16_t len;
    uint16_t base_low;
    uint8_t  base_mid;
    uint8_t  flags;
    uint8_t  gran;
    uint8_t  base_high;
    uint32_t base_upper;
    uint32_t reserved;
} __attribute__((packed)) tss_entry_t;

bool gdt_init();
extern void gdt_load(struct gdtr_t* gdtr);

#endif      // GDT_H
