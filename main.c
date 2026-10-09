
#include <stdint.h>
#include "gpio.h"
#include "timer.h"
#include "ultrasonic.h"
#include "ir_sensor.h"
#include "seven_segment.h"

// =====================================================
// SMART PARKING ASSIST SYSTEM
// Board: Arduino Mega 2560
// =====================================================

// HC-SR04: TRIG = PC0 (D37), ECHO = PC1 (D36)
Ultrasonic ultrasonic1 = {&GPIO_C, 0, 1};

// IR sensor OUT = PC7 (D30)
IR_Sensor parkingIR = {&GPIO_C, 7};

// Distance LEDs: D22, D23, D24 = PA0, PA1, PA2
#define GREEN_LED_PIN       0
#define YELLOW_LED_PIN      1
#define RED_LED_PIN         2

// Active buzzer: D51 = PB2
#define BUZZER_PIN          2

// Slot indicator LEDs: D40 = PG1, D39 = PG2
#define SLOT_AVAILABLE_LED  1
#define SLOT_OCCUPIED_LED   2

// Tens display: D42-D48 = PL7-PL1
// Segment order: A, B, C, D, E, F, G
SevenSegment tensDisplay = {
    &GPIO_L, {7, 6, 5, 4, 3, 2, 1}
};

// Units display: D62-D68 = PK0-PK6
SevenSegment unitsDisplay = {
    &GPIO_K, {0, 1, 2, 3, 4, 5, 6}
};

typedef enum
{
    PARKING_SAFE,
    PARKING_CAUTION,
    PARKING_WARNING,
    PARKING_VERY_CLOSE,
    PARKING_STOP,
    PARKING_SENSOR_ERROR
} ParkingStatus;

// =====================================================
// BUZZER CONTROL
// =====================================================

void buzzerOn(void)
{
    HAL_GPIO_high(&GPIO_B, BUZZER_PIN);
}

void buzzerOff(void)
{
    HAL_GPIO_low(&GPIO_B, BUZZER_PIN);
}

// =====================================================
// DISTANCE LED CONTROL
// =====================================================

void allDistanceLEDsOff(void)
{
    HAL_GPIO_low(&GPIO_A, GREEN_LED_PIN);
    HAL_GPIO_low(&GPIO_A, YELLOW_LED_PIN);
    HAL_GPIO_low(&GPIO_A, RED_LED_PIN);
}

void setLEDs(ParkingStatus status)
{
    allDistanceLEDsOff();

    switch (status)
    {
        case PARKING_SAFE:
            HAL_GPIO_high(&GPIO_A, GREEN_LED_PIN);
            break;

        case PARKING_CAUTION:
            HAL_GPIO_high(&GPIO_A, YELLOW_LED_PIN);
            break;

        case PARKING_WARNING:
        case PARKING_VERY_CLOSE:
        case PARKING_STOP:
            HAL_GPIO_high(&GPIO_A, RED_LED_PIN);
            break;

        case PARKING_SENSOR_ERROR:
        default:
            break;
    }
}

// =====================================================
// DISTANCE CLASSIFICATION
// =====================================================

ParkingStatus getParkingStatus(uint16_t distance)
{
    if (distance == 0)
        return PARKING_SENSOR_ERROR;

    if (distance > 30)
        return PARKING_SAFE;

    if (distance > 15)
        return PARKING_CAUTION;

    if (distance > 10)
        return PARKING_WARNING;

    if (distance >= 5)
        return PARKING_VERY_CLOSE;

    return PARKING_STOP;
}

// =====================================================
// SEVEN-SEGMENT DISPLAY
// Displays distance in centimetres (00-99).
// =====================================================

void showDistance(uint16_t distance)
{
    if (distance == 0)
    {
        HAL_7SEG_blank(&tensDisplay);
        HAL_7SEG_blank(&unitsDisplay);
        return;
    }

    if (distance > 99)
        distance = 99;

    HAL_7SEG_showDigit(&tensDisplay, distance / 10);
    HAL_7SEG_showDigit(&unitsDisplay, distance % 10);
}

// =====================================================
// SLOT INDICATOR
// Assumes IR output is LOW when an object is detected.
// =====================================================

void updateSlotIndicator(void)
{
    uint8_t raw = HAL_IR_read(&parkingIR);

    if (raw == 0)
    {
        // Object detected: slot occupied
        HAL_GPIO_low(&GPIO_G, SLOT_AVAILABLE_LED);
        HAL_GPIO_high(&GPIO_G, SLOT_OCCUPIED_LED);

        Serial.println("Slot: OCCUPIED");
    }
    else
    {
        // No object detected: slot available
        HAL_GPIO_high(&GPIO_G, SLOT_AVAILABLE_LED);
        HAL_GPIO_low(&GPIO_G, SLOT_OCCUPIED_LED);

        Serial.println("Slot: AVAILABLE");
    }
}

// =====================================================
// BUZZER ALERT PATTERNS
// =====================================================
void updateBuzzer(ParkingStatus status)
{
    switch (status)
    {
        case PARKING_SAFE:
        case PARKING_SENSOR_ERROR:
            buzzerOn();
            break;

        case PARKING_CAUTION:
            // Slow beep
            buzzerOn();
            HAL_TIMER_delay_ms(200);
            buzzerOff();
            HAL_TIMER_delay_ms(800);
            break;

        case PARKING_WARNING:
            // Medium-speed beep
            buzzerOn();
            HAL_TIMER_delay_ms(300);
            buzzerOff();
            HAL_TIMER_delay_ms(300);
            break;

        case PARKING_VERY_CLOSE:
            // Fast beep
            buzzerOn();
            HAL_TIMER_delay_ms(250);
            buzzerOff();
            HAL_TIMER_delay_ms(100);
            break;

        case PARKING_STOP:
            // Urgent repeating beep
            buzzerOn();
            HAL_TIMER_delay_ms(50);
            buzzerOff();
            HAL_TIMER_delay_ms(50);
            break;
    }
}



// =====================================================
// SETUP
// =====================================================

void setup()
{
    Serial.begin(9600);

    // Configure distance LEDs
    HAL_GPIO_output(&GPIO_A, GREEN_LED_PIN);
    HAL_GPIO_output(&GPIO_A, YELLOW_LED_PIN);
    HAL_GPIO_output(&GPIO_A, RED_LED_PIN);

    // Configure buzzer
    HAL_GPIO_output(&GPIO_B, BUZZER_PIN);

    // Configure slot indicator LEDs
    HAL_GPIO_output(&GPIO_G, SLOT_AVAILABLE_LED);
    HAL_GPIO_output(&GPIO_G, SLOT_OCCUPIED_LED);

    // Initial safe output states
    allDistanceLEDsOff();
    buzzerOff();

    HAL_GPIO_low(&GPIO_G, SLOT_AVAILABLE_LED);
    HAL_GPIO_low(&GPIO_G, SLOT_OCCUPIED_LED);

    // Initialize hardware drivers
    HAL_TIMER_init();
    HAL_ULTRASONIC_init(&ultrasonic1);
    HAL_IR_init(&parkingIR);

    HAL_7SEG_init(&tensDisplay);
    HAL_7SEG_init(&unitsDisplay);

    HAL_7SEG_blank(&tensDisplay);
    HAL_7SEG_blank(&unitsDisplay);

    Serial.println();
    Serial.println("SMART PARKING ASSIST SYSTEM");
    Serial.println("----------------------------");
}

// =====================================================
// MAIN LOOP
// =====================================================

void loop()
{
    uint16_t distance;
    ParkingStatus status;

    // 1. Read ultrasonic distance
    distance = HAL_ULTRASONIC_getDistance(&ultrasonic1);

    // 2. Print raw distance reading for debugging
    Serial.print("Distance = ");
    Serial.print(distance);
    Serial.println(" cm");

    // 3. Determine parking status
    status = getParkingStatus(distance);

    // 4. Update display and distance LEDs
    showDistance(distance);
    setLEDs(status);

    // 5. Update IR slot indicator
    updateSlotIndicator();

    // 6. Print parking status
    Serial.print("Status: ");

    switch (status)
    {
        case PARKING_SAFE:
            Serial.println("SAFE - GREEN LED");
            break;

        case PARKING_CAUTION:
            Serial.println("CAUTION - YELLOW LED");
            break;

        case PARKING_WARNING:
            Serial.println("WARNING - RED LED");
            break;

        case PARKING_VERY_CLOSE:
            Serial.println("VERY CLOSE - RED LED");
            break;

        case PARKING_STOP:
            Serial.println("STOP - RED LED");
            break;

        case PARKING_SENSOR_ERROR:
            Serial.println("SENSOR ERROR - ALL DISTANCE LEDS OFF");
            break;
    }

    // 7. Generate the appropriate buzzer pattern
    updateBuzzer(status);

    // Brief pause between readings
    HAL_TIMER_delay_ms(100);
}

