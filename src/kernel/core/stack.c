#include <core/stack.h>

uint8_t kernel_stack[16384];    // 16KB stack
uint8_t kernel_stack_top;       // Linker puts this right after
