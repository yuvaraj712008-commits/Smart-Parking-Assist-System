#ifndef LED_H
#define LED_H

#include <stdint.h>
#include "gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    GPIO_Port *port;
    uint8_t pin;
} LED;

void HAL_LED_init(LED *led);
void HAL_LED_on(LED *led);
void HAL_LED_off(LED *led);
void HAL_LED_toggle(LED *led);

#ifdef __cplusplus
}
#endif

#endif