#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// Initialize Timer1
void HAL_TIMER_init(void);

// Generate delay in milliseconds
void HAL_TIMER_delay_ms(uint16_t ms);

// Start timer for pulse-width measurement
void HAL_TIMER_measure_start(void);

// Stop timer for pulse-width measurement
void HAL_TIMER_measure_stop(void);

// Reset Timer1 counter
void HAL_TIMER_reset(void);

// Read Timer1 counter
uint16_t HAL_TIMER_getCount(void);

#ifdef __cplusplus
}
#endif

#endif