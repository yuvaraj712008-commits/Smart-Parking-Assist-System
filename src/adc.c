#include "adc.h"

// ADC registers

#define YUVA_ADCL    (*(volatile uint8_t *)0x78)
#define YUVA_ADCH    (*(volatile uint8_t *)0x79)

#define YUVA_ADCSRA  (*(volatile uint8_t *)0x7A)
#define YUVA_ADCSRB  (*(volatile uint8_t *)0x7B)

#define YUVA_ADMUX   (*(volatile uint8_t *)0x7C)


// Initialize ADC
void HAL_ADC_init(void)
{
    // Reference voltage = AVCC
    // Result = right adjusted
    YUVA_ADMUX = (1 << 6);

    // Enable ADC
    // Prescaler = 128
    //
    // ADEN = 1
    // ADPS2 = 1
    // ADPS1 = 1
    // ADPS0 = 1

    YUVA_ADCSRA =
        (1 << 7) |
        (1 << 2) |
        (1 << 1) |
        (1 << 0);

    // Clear ADCSRB
    YUVA_ADCSRB = 0x00;
}


// Read ADC value
uint16_t HAL_ADC_read(uint8_t channel)
{
    uint16_t result;

    // Only channels 0 to 15 are valid
    if (channel > 15)
    {
        return 0;
    }

    /*
       Select ADC channel.

       MUX4:MUX0 are used for channel selection.
    */

    YUVA_ADMUX &= 0xE0;
    YUVA_ADMUX |= (channel & 0x1F);

    /*
       For ADC8-ADC15,
       MUX5 in ADCSRB must be set.
    */

    if (channel >= 8)
    {
        YUVA_ADCSRB |= (1 << 3);
    }
    else
    {
        YUVA_ADCSRB &= ~(1 << 3);
    }

    // Start conversion
    YUVA_ADCSRA |= (1 << 6);

    // Wait until conversion finishes
    while (YUVA_ADCSRA & (1 << 6))
    {
    }

    /*
       Read ADCL first.
       Then read ADCH.
    */

    result = YUVA_ADCL;
    result |= ((uint16_t)YUVA_ADCH << 8);

    return result;
}