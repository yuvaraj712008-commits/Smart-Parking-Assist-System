
#include "ir_sensor.h"

// Initialize the IR sensor by configuring its pin as an input.
void HAL_IR_init(IR_Sensor *sensor)
{
    // Set the IR sensor output pin as an input
    // so the microcontroller can read the sensor's digital signal.
    HAL_GPIO_input(sensor->port, sensor->pin);
}

// Read the current digital output from the IR sensor.
uint8_t HAL_IR_read(IR_Sensor *sensor)
{
    // Read the logic level on the sensor pin.
    // Returns 0 when LOW and 1 when HIGH.
    return HAL_GPIO_read(sensor->port, sensor->pin);
}

// Check whether the IR sensor detects an object.
uint8_t HAL_IR_isDetected(IR_Sensor *sensor)
{
    // This assumes the IR module is active-LOW:
    // LOW (0) means an object is detected.
    // HIGH (1) means no object is detected.
    return (HAL_IR_read(sensor) == 0);
}
