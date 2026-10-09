#include "led.h"

// Initialize the LED
void HAL_LED_init(LED *led)
{
    // Configure the selected GPIO pin as an output
    HAL_GPIO_output(led->port, led->pin);

    // Initially turn the LED OFF
    HAL_GPIO_low(led->port, led->pin);
}


// Turn the LED ON
void HAL_LED_on(LED *led)
{
    // Set the selected GPIO pin HIGH
    HAL_GPIO_high(led->port, led->pin);
}


// Turn the LED OFF
void HAL_LED_off(LED *led)
{
    // Set the selected GPIO pin LOW
    HAL_GPIO_low(led->port, led->pin);
}


// Toggle the LED state
void HAL_LED_toggle(LED *led)
{
    // Change the current LED state
    // ON  → OFF
    // OFF → ON
    HAL_GPIO_toggle(led->port, led->pin);
}