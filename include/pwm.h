#ifndef PWM_H
#define PWM_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif



// Initialize Timer3 PWM on OC3A / PE3
void HAL_PWM_init(void);

// Set PWM duty cycle from 0 to 100%
void HAL_PWM_setDuty(uint8_t duty);

// Start PWM
void HAL_PWM_start(void);

// Stop PWM
void HAL_PWM_stop(void);

#ifdef __cplusplus
}
#endif

#endif