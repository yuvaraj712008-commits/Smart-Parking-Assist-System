#ifndef SWITCH_H
#define SWITCH_H

#include <stdint.h>
#include "gpio.h"

// Switch configuration structure
typedef struct
{
    GPIO_Port *port;    // GPIO port used by the switch
    uint8_t pin;        // GPIO pin number
} Switch;


// Initialize the switch
void HAL_SWITCH_init(Switch *sw);

// Check whether the switch is pressed
// Returns 1 if pressed, 0 if not pressed
uint8_t HAL_SWITCH_isPressed(Switch *sw);

#endif