#include <arch/x86_64/gdt.h>
#include <arch/x86_64/pic.h>
#include <stdint.h>

static tss_t tss;

struct {
    struct gdt_entry_t entries[3];
    tss_entry_t tss_entry;
    uint64_t tss_entry_high; // padding for 16 byte TSS descriptor
} __attribute__((packed)) gdt;

bool gdt_init() {
    gdt.entries[0] = (struct gdt_entry_t){0, 0, 0, 0, 0, 0};
    gdt.entries[1] = (struct gdt_entry_t){0, 0, 0, 0x9A, 0x20, 0};
    gdt.entries[2] = (struct gdt_entry_t){0, 0, 0, 0x92, 0, 0};

    // Set up TSS descriptor
    uint64_t tss_base = (uint64_t)&tss;
    uint32_t tss_limit = sizeof(tss_t) - 1;

    gdt.tss_entry.len        = tss_limit;
    gdt.tss_entry.base_low   = tss_base & 0xFFFF;
    gdt.tss_entry.base_mid   = (tss_base >> 16) & 0xFF;
    gdt.tss_entry.flags      = 0x89; // present, ring 0, TSS available
    gdt.tss_entry.gran       = 0x00;
    gdt.tss_entry.base_high  = (tss_base >> 24) & 0xFF;
    gdt.tss_entry.base_upper = (tss_base >> 32) & 0xFFFFFFFF;
    gdt.tss_entry.reserved   = 0;

    // Set kernel stack in TSS
    extern uint8_t kernel_stack_top;
    tss.rsp0 = (uint64_t)&kernel_stack_top;
    tss.iopb = sizeof(tss_t);

    struct gdtr_t gdtr;
    gdtr.limit = sizeof(gdt) - 1;
    gdtr.base  = (uint64_t)&gdt;
    gdt_load(&gdtr);

    // Load TSS — selector 0x18 (index 3, GDT entry 3)
    __asm__ volatile ("ltr %0" :: "r"((uint16_t)0x18));

    return true;
}
