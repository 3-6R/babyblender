/**
 * @file main.h
 * @brief Core hardware definitions and initialization prototypes for washer control system.
 *
 * This header file contains all the essential hardware configuration macros, external timer handles,
 * and function prototypes needed to initialize and manage the basic system setup for the washer controller.
 *
 * Contents:
 * - GPIO pin assignments for user interface buttons (Start, Stop, Up, Down).
 * - GPIO pin assignments for motor and water valve control outputs (Forward, Reverse, Hot Water, Cold Water).
 * - External declarations of timer handles for motor operation and water filling management.
 * - Prototypes for system clock, GPIO, and timer initialization functions.
 *
 * Definitions:
 * - Button Inputs (connected to GPIOA):
 *   - `BUTTON_START_PIN`, `BUTTON_STOP_PIN`, `BUTTON_UP_PIN`, `BUTTON_DOWN_PIN`
 * - Motor and Water Outputs (connected to GPIOB):
 *   - `MOTOR_FORWARD_PIN`, `MOTOR_REVERSE_PIN`, `WATER_HOT_PIN`, `WATER_COLD_PIN`
 * - Output Ports:
 *   - `BUTTON_GPIO_PORT` (GPIOA)
 *   - `OUTPUT_GPIO_PORT` (GPIOB)
 *
 * External Variables:
 * - `htim3`: Timer used for motor control timing sequences.
 * - `htim14`: Timer used for water filling timeouts.
 *
 * Function Prototypes:
 * - `SystemClock_Config(void)`: Configures the main system clock.
 * - `GPIO_Init(void)`: Sets up GPIO ports for inputs and outputs.
 * - `Timer_Init(void)`: Initializes timers for motor and water control operations.
 *
 * Usage:
 * - Include this file in any module that needs access to core hardware definitions or 
 *   system initialization routines.
 *
 * Dependencies:
 * - STM32C0 HAL libraries (`stm32c0xx_hal.h`).
 */



 #ifndef MAIN_H
 #define MAIN_H
 
 #include "stm32c0xx_hal.h"
 
 // Button Definitions
 #define BUTTON_START_PIN    GPIO_PIN_0
 #define BUTTON_STOP_PIN     GPIO_PIN_1
 #define BUTTON_UP_PIN       GPIO_PIN_2
 #define BUTTON_DOWN_PIN     GPIO_PIN_3
 #define BUTTON_GPIO_PORT    GPIOA
 
 // Motor and Water Outputs
 #define MOTOR_FORWARD_PIN   GPIO_PIN_0
 #define MOTOR_REVERSE_PIN   GPIO_PIN_1
 #define WATER_HOT_PIN       GPIO_PIN_2
 #define WATER_COLD_PIN      GPIO_PIN_3
 #define OUTPUT_GPIO_PORT    GPIOB
 
 // Timer Handles
 extern TIM_HandleTypeDef htim3;  // Motor Control Timer
 extern TIM_HandleTypeDef htim14; // Fill Water Timer
 
 // Function Prototypes
 void SystemClock_Config(void);
 void GPIO_Init(void);
 void Timer_Init(void);
 
 #endif // MAIN_H
 