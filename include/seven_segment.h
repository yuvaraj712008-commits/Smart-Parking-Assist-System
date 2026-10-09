#ifndef SEVEN_SEGMENT_H
#define SEVEN_SEGMENT_H

#include <stdint.h>
#include "gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    GPIO_Port *port;
    uint8_t pins[7];  // A, B, C, D, E, F, G
} SevenSegment;

void HAL_7SEG_init(SevenSegment *display);
void HAL_7SEG_showDigit(SevenSegment *display, uint8_t digit);
void HAL_7SEG_blank(SevenSegment *display);

#ifdef __cplusplus
}
#endif

#endif