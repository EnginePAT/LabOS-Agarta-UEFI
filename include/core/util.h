#ifndef UTIL_H
#define UTIL_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <core/limine.h>

#define CEIL_DIV(a,b) (((a + b) - 1)/b)

void *memcpy(void *restrict dest, const void *restrict src, size_t n);
void *memset(void *s, int c, size_t n);
void *memmove(void *dest, const void *src, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);

void outPortB(uint16_t Port, uint8_t Value);
char inPortB(uint16_t port);

struct InterruptRegisters{
    uint32_t cr2;
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, csm, eflags, useresp, ss;
};

static inline void outb(uint16_t port, uint8_t val) {
    __asm__ volatile ("outb %0, %1" :: "a"(val), "Nd"(port));
}

static inline uint8_t inb(uint16_t port) {
    uint8_t val;
    __asm__ volatile ("inb %1, %0" : "=a"(val) : "Nd"(port));
    return val;
}

static inline void debug_print_char(char c) {
    __asm__ volatile ("outb %0, %1" :: "a"(c), "Nd"(0xe9));
}

static inline void debug_print(const char* str) {
    while (*str) debug_print_char(*str++);
}

static inline void debug_print_hex(uint64_t val) {
    debug_print("0x");
    for (int i = 60; i >= 0; i -= 4) {
        uint8_t nibble = (val >> i) & 0xF;
        debug_print_char(nibble < 10 ? '0' + nibble : 'a' + nibble - 10);
    }
}

#endif      // UTIL_H
