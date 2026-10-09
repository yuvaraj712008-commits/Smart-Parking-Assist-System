#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <stdint.h>
#include "gpio.h"


#ifdef __cplusplus
extern "C" {
#endif


// Ultrasonic sensor structure
typedef struct
{
    GPIO_Port *port;
    uint8_t trig_pin;
    uint8_t echo_pin;
} Ultrasonic;

// Initialize ultrasonic sensor
void HAL_ULTRASONIC_init(Ultrasonic *sensor);

// Measure distance in centimeters
uint16_t HAL_ULTRASONIC_getDistance(Ultrasonic *sensor);

#ifdef __cplusplus
}
#endif


#endif