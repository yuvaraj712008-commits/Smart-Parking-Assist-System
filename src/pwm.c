#include "pwm.h"

// PORT E registers

#define YUVA_DDRE   (*(volatile uint8_t *)0x2D)

// TIMER3 registers

#define YUVA_TCCR3A (*(volatile uint8_t *)0x90)
#define YUVA_TCCR3B (*(volatile uint8_t *)0x91)

#define YUVA_OCR3AL (*(volatile uint8_t *)0x98)
#define YUVA_OCR3AH (*(volatile uint8_t *)0x99)


// Initialize Timer3 PWM on OC3A / PE3
void HAL_PWM_init(void)
{
    // Configure PE3 / OC3A as output
    YUVA_DDRE |= (1 << 3);

    // Stop Timer3 during configuration
    YUVA_TCCR3B = 0x00;

    // Fast PWM 8-bit
    //
    // WGM33 = 0
    // WGM32 = 1
    // WGM31 = 0
    // WGM30 = 1

    // COM3A1 = 1
    // COM3A0 = 0
    //
    // Non-inverting PWM

    YUVA_TCCR3A = (1 << 7) | (1 << 0);

    YUVA_TCCR3B = (1 << 3);

    // Initial duty cycle = 0%
    YUVA_OCR3AH = 0;
    YUVA_OCR3AL = 0;
}


// Set PWM duty cycle
void HAL_PWM_setDuty(uint8_t duty)
{
    uint8_t value;

    // Limit duty cycle
    if (duty > 100)
    {
        duty = 100;
    }

    // Convert 0-100% to 0-255
    value = (uint8_t)(((uint16_t)duty * 255U) / 100U);

    YUVA_OCR3AH = 0;
    YUVA_OCR3AL = value;
}


// Start PWM
void HAL_PWM_start(void)
{
    // Prescaler = 64
    //
    // CS32 = 0
    // CS31 = 1
    // CS30 = 1

    YUVA_TCCR3B |= (1 << 1) | (1 << 0);
}


// Stop PWM
void HAL_PWM_stop(void)
{
    // Stop Timer3
    YUVA_TCCR3B &= ~((1 << 2) |
                     (1 << 1) |
                     (1 << 0));
}