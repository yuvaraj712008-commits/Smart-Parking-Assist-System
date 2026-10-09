#include "switch.h"

// Initialize the switch
void HAL_SWITCH_init(Switch *sw)
{
    // Configure the selected GPIO pin as an input
    // and enable the internal pull-up resistor.
    //
    // When the switch is released:
    //     GPIO input = HIGH
    //
    // When the switch is pressed:
    //     GPIO input = LOW
    //
    // The port and pin are obtained from the Switch structure.
    HAL_GPIO_enablepullup(sw->port, sw->pin);
}

// Check whether the switch is pressed
uint8_t HAL_SWITCH_isPressed(Switch *sw)
{
    // Read the current logic level of the selected GPIO pin.
    //
    // With the internal pull-up configuration:
    //     HIGH (1) = switch not pressed
    //     LOW  (0) = switch pressed
    //
    // The ! operator reverses the result:
    //     Read HIGH (1) → !1 = 0 → not pressed
    //     Read LOW  (0) → !0 = 1 → pressed
    //
    // Therefore, this function returns:
    //     1 → switch is pressed
    //     0 → switch is not pressed
    return !HAL_GPIO_read(sw->port, sw->pin);
}