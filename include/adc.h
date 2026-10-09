#ifndef ADC_H
#define ADC_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// Initialize ADC
void HAL_ADC_init(void);

// Read ADC value from channel 0 to 15
uint16_t HAL_ADC_read(uint8_t channel);


#ifdef __cplusplus
}
#endif

#endif