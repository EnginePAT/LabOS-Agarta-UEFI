#ifndef PIC_H
#define PIC_H

#include <stdint.h>
#include <core/util.h>

bool pic_init();
void pic_send_eoi(uint8_t irq);

#endif      // PIC_H
