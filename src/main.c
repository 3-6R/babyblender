/**
 * @file main.c
 * @brief Main application entry point for the washer control system.
 *
 * This source file contains the core logic for initializing all system peripherals,
 * setting up the washer control state machine, and running the main application loop.
 * 
 * Functionality:
 * - Initializes the HAL library, system clock, GPIO, ADC, RTC, SPI display, and washer control.
 * - Monitors button inputs for Start, Stop, Up, and Down buttons.
 * - Manages program selection and controls washer state transitions based on user input.
 * - Periodically updates the washer operation state through `Washer_Update()`.
 * 
 * Global Variables:
 * - `selectedProgram`: Tracks the currently selected washing program (0-29).
 * - `washer`: Structure holding the current washer state, program index, step index, timer, and motor direction.
 * 
 * Main Loop Tasks:
 * - Detects button presses:
 *   - Start: Begins the fill water process if the washer is idle.
 *   - Stop: Returns washer to idle state.
 *   - Up: Increments the selected program index (if below maximum).
 *   - Down: Decrements the selected program index (if above zero).
 * - Calls `Washer_Update()` to advance the washer's state machine as needed.
 * - Introduces a 100ms delay between iterations for simple button debouncing and pacing.
 * 
 * Functions:
 * - `main(void)`: Initializes the system and enters the infinite control loop.
 * - `SystemClock_Config(void)`: Configures the system clock to use HSE (external oscillator) without PLL.
 * - `Error_Handler(void)`: Blinks an LED on GPIOB pin 0 at 500ms intervals when a critical error occurs.
 * 
 * Dependencies:
 * - `main.h`, `spi.h`, `washer.h`, `font.h`, `display.h`, `gpio.h`, `adc.h`, `rtc.h`
 * 
 * Notes:
 * - Button inputs are active-low (pressed state reads as `GPIO_PIN_RESET`).
 * - System initialization sequence is critical before entering the main loop.
 * - `Error_Handler` provides basic fault indication via an LED blink pattern.
 */



 #include "main.h"
 #include "spi.h"
 #include "washer.h"
 #include "font.h"
 #include "display.h"
 #include "gpio.h"
 #include "adc.h"
 #include "rtc.h"
 
 // Global variables
 int selectedProgram = 0;
 WasherControl washer = {IDLE, 0, 0, 0, 0};
 
 int main(void) {
     // Initialize the system
     HAL_Init();
     SystemClock_Config();
     GPIO_Init();
     ADC_Init();
     RTC_Init();
 
     // Initialize the display
     SPI_InitDisplay();
     SPI_DisplayClear();
     SPI_WriteCharacter('A');
 
     // Initialize washer
     Washer_Init(&washer);
 
     while (1) {
         // Handle button presses
         if (HAL_GPIO_ReadPin(GPIOA, BUTTON_START_PIN) == GPIO_PIN_RESET) {
             if (washer.state == IDLE) {
                 washer.state = FILL_WATER;
             }
         }
 
         if (HAL_GPIO_ReadPin(GPIOA, BUTTON_STOP_PIN) == GPIO_PIN_RESET) {
             washer.state = IDLE;
         }
 
         if (HAL_GPIO_ReadPin(GPIOA, BUTTON_UP_PIN) == GPIO_PIN_RESET) {
             if (selectedProgram < 29) {
                 selectedProgram++;
             }
         }
 
         if (HAL_GPIO_ReadPin(GPIOA, BUTTON_DOWN_PIN) == GPIO_PIN_RESET) {
             if (selectedProgram > 0) {
                 selectedProgram--;
             }
         }
 99-4589676
         // Call washer update function
         Washer_Update(&washer);
 
         HAL_Delay(100);
     }
 }
 
 void SystemClock_Config(void) {
     RCC_OscInitTypeDef RCC_OscInitStruct = {0};
     RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
 
     RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
     RCC_OscInitStruct.HSEState = RCC_HSE_ON;
     RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
 
     if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
         Error_Handler();
     }
 
     RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK;
     RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
 
     if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
         Error_Handler();
     }
 }
 
 void Error_Handler(void) {
     while (1) {
         HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
         HAL_Delay(500);
     }
 }
 