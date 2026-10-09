
#include "timer.h"

/* ATmega2560 Timer1 registers */
#define TCCR1A (*(volatile uint8_t *)0x80)
#define TCCR1B (*(volatile uint8_t *)0x81)
#define TCNT1L (*(volatile uint8_t *)0x84)
#define TCNT1H (*(volatile uint8_t *)0x85)
#define OCR1AL (*(volatile uint8_t *)0x88)
#define OCR1AH (*(volatile uint8_t *)0x89)
#define TIFR1  (*(volatile uint8_t *)0x36)

/* Timer1 bit positions */
#define WGM12 3
#define CS11  1
#define CS10  0
#define OCF1A 1
#define TOV1  0

static void TIMER1_setCount(uint16_t value)
{
    /* AVR requires high byte first when writing a 16-bit timer */
    TCNT1H = (uint8_t)(value >> 8);
    TCNT1L = (uint8_t)value;
}

static uint16_t TIMER1_readCount(void)
{
    /* Read low byte first; AVR latches the high byte */
    uint8_t low = TCNT1L;
    uint8_t high = TCNT1H;

    return ((uint16_t)high << 8) | low;
}

void HAL_TIMER_init(void)
{
    TCCR1A = 0;
    TCCR1B = 0;

    OCR1AH = 0;
    OCR1AL = 249;
    TIMER1_setCount(0);

    TIFR1 = (1 << OCF1A) | (1 << TOV1);
}

void HAL_TIMER_delay_ms(uint16_t ms)
{
    TCCR1A = 0;
    TCCR1B = 0;

    OCR1AH = 0;
    OCR1AL = 249;

    while (ms > 0)
    {
        TIMER1_setCount(0);
        TIFR1 = (1 << OCF1A);

        TCCR1B = (1 << WGM12) | (1 << CS11) | (1 << CS10);

        while ((TIFR1 & (1 << OCF1A)) == 0)
        {
        }

        TCCR1B = 0;
        ms--;
    }
}

void HAL_TIMER_measure_start(void)
{
    TCCR1A = 0;
    TCCR1B = 0; /* Normal mode, stopped */

    TIMER1_setCount(0);
    TIFR1 = (1 << TOV1);

    TCCR1B = (1 << CS11); /* Normal mode, prescaler 8 */
}

void HAL_TIMER_measure_stop(void)
{
    TCCR1B = 0;
}

void HAL_TIMER_reset(void)
{
    TIMER1_setCount(0);
}

uint16_t HAL_TIMER_getCount(void)
{
    return TIMER1_readCount();
}