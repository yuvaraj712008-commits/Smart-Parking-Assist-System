
#include <stdint.h>
#include "gpio.h"
#include "ultrasonic.h"
#include "timer.h"

#define ULTRASONIC_TIMEOUT 60000UL

void HAL_ULTRASONIC_init(Ultrasonic *sensor)
{
    HAL_GPIO_output(sensor->port, sensor->trig_pin);
    HAL_GPIO_input(sensor->port, sensor->echo_pin);
    HAL_GPIO_low(sensor->port, sensor->trig_pin);
}

static void ultrasonic_trigger(Ultrasonic *sensor)
{
    volatile uint8_t i;

    HAL_GPIO_low(sensor->port, sensor->trig_pin);

    for (i = 0; i < 10; i++)
        __asm__ __volatile__("nop");

    HAL_GPIO_high(sensor->port, sensor->trig_pin);

    /* Approximately 10 us; depends on generated instructions */
    for (i = 0; i < 40; i++)
        __asm__ __volatile__("nop");

    HAL_GPIO_low(sensor->port, sensor->trig_pin);
}

uint16_t HAL_ULTRASONIC_getDistance(Ultrasonic *sensor)
{
    uint32_t timeout;
    uint16_t count;

    ultrasonic_trigger(sensor);

    /* Wait for ECHO to rise */
    timeout = ULTRASONIC_TIMEOUT;
    while (HAL_GPIO_read(sensor->port, sensor->echo_pin) == 0)
    {
        if (--timeout == 0)
            return 0;
    }

    /* Start timing the ECHO HIGH pulse */
    HAL_TIMER_measure_start();

    timeout = ULTRASONIC_TIMEOUT;
    while (HAL_GPIO_read(sensor->port, sensor->echo_pin) != 0)
    {
        if (--timeout == 0)
        {
            HAL_TIMER_measure_stop();
            return 0;
        }
    }

    HAL_TIMER_measure_stop();
    count = HAL_TIMER_getCount();

    /* Timer1 at 16 MHz / 8: approximately 116 counts per cm */
    return (uint16_t)(count / 116U);
}