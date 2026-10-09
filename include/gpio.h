#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    volatile uint8_t *pin;
    volatile uint8_t *ddr;
    volatile uint8_t *port;

} GPIO_Port;


// GPIO FUNCTIONS

void HAL_GPIO_output(GPIO_Port *reg, uint8_t pin);

void HAL_GPIO_input(GPIO_Port *reg, uint8_t pin);

void HAL_GPIO_high(GPIO_Port *reg, uint8_t pin);

void HAL_GPIO_low(GPIO_Port *reg, uint8_t pin);

void HAL_GPIO_toggle(GPIO_Port *reg, uint8_t pin);

void HAL_GPIO_enablepullup(GPIO_Port *reg, uint8_t pin);

uint8_t HAL_GPIO_read(GPIO_Port *reg, uint8_t pin);


// ATmega2560 PORTS

extern GPIO_Port GPIO_A;
extern GPIO_Port GPIO_B;
extern GPIO_Port GPIO_C;
extern GPIO_Port GPIO_D;
extern GPIO_Port GPIO_E;
extern GPIO_Port GPIO_F;
extern GPIO_Port GPIO_G;
extern GPIO_Port GPIO_H;
extern GPIO_Port GPIO_J;
extern GPIO_Port GPIO_K;
extern GPIO_Port GPIO_L;

#ifdef __cplusplus
}
#endif

#endif