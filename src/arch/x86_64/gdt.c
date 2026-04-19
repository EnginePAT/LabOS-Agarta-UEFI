#include <arch/x86_64/gdt.h>
#include <stdint.h>

struct gdt_entry_t gdt_entries[3];              // NULL, kernel and user segments

bool gdt_init() {
    // Initialize the GDT here
    gdt_entries[0] = (struct gdt_entry_t){0, 0, 0, 0, 0, 0};        // NULL segment
    gdt_entries[1] = (struct gdt_entry_t){0, 0, 0, 0x9A, 0x20, 0};  // Kernel code segment
    gdt_entries[2] = (struct gdt_entry_t){0, 0, 0, 0x92, 0, 0};     // Kernel data segment

    struct gdtr_t gdtr;
    gdtr.limit = (sizeof(struct gdt_entry_t) * 3) - 1;
    gdtr.base = (uint64_t)&gdt_entries;
    gdt_load(&gdtr);
    return true;
}
