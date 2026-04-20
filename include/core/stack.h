#ifndef STACK_H
#define STACK_H

#include <stdint.h>

extern uint8_t kernel_stack[16384]; // 16KB stack
extern uint8_t kernel_stack_top;    // linker puts this right after

#endif      // STACK_H
