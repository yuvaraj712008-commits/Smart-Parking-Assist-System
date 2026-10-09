#include "gpio.h"

// REGISTER DEFINITIONS
//
// PINx  -> Read the pin state
// DDRx  -> Configure INPUT or OUTPUT
// PORTx -> Write HIGH/LOW and enable pull-up
//
// Register naming convention used in this project:
//
// YUVA_PINx
// YUVA_DDRx
// YUVA_PORTx


// PORT A

#define YUVA_PINA   (*(volatile uint8_t *)0x20)
#define YUVA_DDRA   (*(volatile uint8_t *)0x21)
#define YUVA_PORTA  (*(volatile uint8_t *)0x22)


// PORT B

#define YUVA_PINB   (*(volatile uint8_t *)0x23)
#define YUVA_DDRB   (*(volatile uint8_t *)0x24)
#define YUVA_PORTB  (*(volatile uint8_t *)0x25)


// PORT C

#define YUVA_PINC   (*(volatile uint8_t *)0x26)
#define YUVA_DDRC   (*(volatile uint8_t *)0x27)
#define YUVA_PORTC  (*(volatile uint8_t *)0x28)


// PORT D

#define YUVA_PIND   (*(volatile uint8_t *)0x29)
#define YUVA_DDRD   (*(volatile uint8_t *)0x2A)
#define YUVA_PORTD  (*(volatile uint8_t *)0x2B)


// PORT E

#define YUVA_PINE   (*(volatile uint8_t *)0x2C)
#define YUVA_DDRE   (*(volatile uint8_t *)0x2D)
#define YUVA_PORTE  (*(volatile uint8_t *)0x2E)


// PORT F

#define YUVA_PINF   (*(volatile uint8_t *)0x2F)
#define YUVA_DDRF   (*(volatile uint8_t *)0x30)
#define YUVA_PORTF  (*(volatile uint8_t *)0x31)


// PORT G

#define YUVA_PING   (*(volatile uint8_t *)0x32)
#define YUVA_DDRG   (*(volatile uint8_t *)0x33)
#define YUVA_PORTG  (*(volatile uint8_t *)0x34)


// PORT H

#define YUVA_PINH   (*(volatile uint8_t *)0x100)
#define YUVA_DDRH   (*(volatile uint8_t *)0x101)
#define YUVA_PORTH  (*(volatile uint8_t *)0x102)


// PORT J

#define YUVA_PINJ   (*(volatile uint8_t *)0x103)
#define YUVA_DDRJ   (*(volatile uint8_t *)0x104)
#define YUVA_PORTJ  (*(volatile uint8_t *)0x105)


// PORT K

#define YUVA_PINK   (*(volatile uint8_t *)0x106)
#define YUVA_DDRK   (*(volatile uint8_t *)0x107)
#define YUVA_PORTK  (*(volatile uint8_t *)0x108)


// PORT L

#define YUVA_PINL   (*(volatile uint8_t *)0x109)
#define YUVA_DDRL   (*(volatile uint8_t *)0x10A)
#define YUVA_PORTL  (*(volatile uint8_t *)0x10B)


// GPIO PORT OBJECTS

GPIO_Port GPIO_A = {&YUVA_PINA, &YUVA_DDRA, &YUVA_PORTA};

GPIO_Port GPIO_B = {&YUVA_PINB, &YUVA_DDRB, &YUVA_PORTB};

GPIO_Port GPIO_C = {&YUVA_PINC, &YUVA_DDRC, &YUVA_PORTC};

GPIO_Port GPIO_D = {&YUVA_PIND, &YUVA_DDRD, &YUVA_PORTD};

GPIO_Port GPIO_E = {&YUVA_PINE, &YUVA_DDRE, &YUVA_PORTE};

GPIO_Port GPIO_F = {&YUVA_PINF, &YUVA_DDRF, &YUVA_PORTF};

GPIO_Port GPIO_G = {&YUVA_PING, &YUVA_DDRG, &YUVA_PORTG};

GPIO_Port GPIO_H = {&YUVA_PINH, &YUVA_DDRH, &YUVA_PORTH};

GPIO_Port GPIO_J = {&YUVA_PINJ, &YUVA_DDRJ, &YUVA_PORTJ};

GPIO_Port GPIO_K = {&YUVA_PINK, &YUVA_DDRK, &YUVA_PORTK};

GPIO_Port GPIO_L = {&YUVA_PINL, &YUVA_DDRL, &YUVA_PORTL};


// GPIO FUNCTIONS

// Configure a GPIO pin as OUTPUT

void HAL_GPIO_output(GPIO_Port *reg, uint8_t pin)
{
    *(reg->ddr) |= (1 << pin);
}


// Configure a GPIO pin as INPUT

void HAL_GPIO_input(GPIO_Port *reg, uint8_t pin)
{
    *(reg->ddr) &= ~(1 << pin);
}


// Set GPIO pin HIGH

void HAL_GPIO_high(GPIO_Port *reg, uint8_t pin)
{
    *(reg->port) |= (1 << pin);
}


// Set GPIO pin LOW

void HAL_GPIO_low(GPIO_Port *reg, uint8_t pin)
{
    *(reg->port) &= ~(1 << pin);
}


// Toggle GPIO pin

void HAL_GPIO_toggle(GPIO_Port *reg, uint8_t pin)
{
    *(reg->port) ^= (1 << pin);
}


// Enable internal pull-up resistor

void HAL_GPIO_enablepullup(GPIO_Port *reg, uint8_t pin)
{
    *(reg->ddr) &= ~(1 << pin);

    *(reg->port) |= (1 << pin);
}


// Read GPIO input pin
//
// Returns:
// 0 -> LOW
// 1 -> HIGH

uint8_t HAL_GPIO_read(GPIO_Port *reg, uint8_t pin)
{
    return (*(reg->pin) >> pin) & 1;
}