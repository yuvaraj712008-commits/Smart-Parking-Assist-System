#include "seven_segment.h"

/* Common-cathode patterns; bit 0=A, bit 6=G */
static const uint8_t digitPatterns[10] =
{
    0x3F,  // 0
    0x06,  // 1
    0x5B,  // 2
    0x4F,  // 3
    0x66,  // 4
    0x6D,  // 5
    0x7D,  // 6
    0x07,  // 7
    0x7F,  // 8
    0x6F   // 9
};

void HAL_7SEG_init(SevenSegment *display)
{
    uint8_t i;

    for (i = 0; i < 7; i++)
    {
        HAL_GPIO_output(display->port, display->pins[i]);
        HAL_GPIO_low(display->port, display->pins[i]);
    }
}

void HAL_7SEG_blank(SevenSegment *display)
{
    uint8_t i;

    for (i = 0; i < 7; i++)
    {
        HAL_GPIO_low(display->port, display->pins[i]);
    }
}

void HAL_7SEG_showDigit(SevenSegment *display, uint8_t digit)
{
    uint8_t i;
    uint8_t pattern;

    if (digit > 9)
    {
        HAL_7SEG_blank(display);
        return;
    }

    pattern = digitPatterns[digit];

    for (i = 0; i < 7; i++)
    {
        if (pattern & (1U << i))
            HAL_GPIO_high(display->port, display->pins[i]);
        else
            HAL_GPIO_low(display->port, display->pins[i]);
    }
}