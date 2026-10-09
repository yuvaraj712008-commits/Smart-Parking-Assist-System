
#ifndef IR_SENSOR_H
#define IR_SENSOR_H

#include <stdint.h>
#include "gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

// IR sensor configuration
typedef struct
{
    GPIO_Port *port;
    uint8_t pin;
} IR_Sensor;

// Initialize the IR sensor output pin as input
void HAL_IR_init(IR_Sensor *sensor);

// Read the raw digital output
// Returns 1 if HIGH, 0 if LOW
uint8_t HAL_IR_read(IR_Sensor *sensor);

// Active-LOW detection logic
// Returns 1 if detected, 0 if not detected
uint8_t HAL_IR_isDetected(IR_Sensor *sensor);

#ifdef __cplusplus
}
#endif

#endif