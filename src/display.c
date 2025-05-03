/**
 * @file washer.c
 * @brief Washer control logic with temperature-based water control and real-time clock display.
 *
 * This source file implements the washer control state machine and extends the functionality
 * by incorporating temperature-based decision making and real-time clock updates.
 *
 * Main Features:
 * - Initialization of the washer state machine and display.
 * - Reading temperature data from the ADC to determine hot/cold water valve control during the FILL_WATER phase.
 * - Step-by-step state machine progression through FILL_WATER → WASH → RINSE → SPIN → IDLE.
 * - Handling user button inputs for starting, stopping, and selecting wash programs.
 * - Reading and displaying the 24-hour clock time from the RTC module.
 *
 * Main Functions:
 * - Washer_Init(WasherControl *washer): Initializes washer control structure and updates display.
 * - Read_Temperature(void): Reads ADC value and converts it to a float temperature (°C).
 * - Washer_Update(WasherControl *washer): Advances washer through its states, uses temperature to control valves.
 * - Washer_HandleButtonPress(WasherControl *washer, int button): Responds to button input to start, stop, or select a program.
 * - Display_UpdateTime(void): Fetches current time from RTC and updates it on the display.
 *
 * Dependencies:
 * - washer.h (WasherControl structure and state definitions)
 * - display.h (functions for updating display)
 * - main.h (button definitions, GPIO pin definitions)
 * - rtc.h (for accessing RTC time and date)
 * - adc.h (for reading temperature from ADC)
 *
 * Notes:
 * - Temperature reading assumes a 0–100°C mapping based on a 12-bit ADC.
 * - Hot and cold water control is based on simple threshold comparison:
 *     - Below 25°C → use hot water
 *     - Above 35°C → use cold water
 *     - Between 25°C and 35°C → mix hot and cold
 * - Time is displayed in HH:MM:SS format and refreshed frequently.
 */



 #include "washer.h"
 #include "display.h"
 #include "main.h"
 #include "rtc.h"
 #include "adc.h"
 
 #define TEMP_SENSOR_ADC_CHANNEL ADC_CHANNEL_0
 #define TEMP_SENSOR_PORT GPIOA
 #define TEMP_SENSOR_PIN GPIO_PIN_0
 
 // Initialize washer state
 void Washer_Init(WasherControl *washer) {
     washer->state = IDLE;
     washer->programIndex = 0;
     washer->stepIndex = 0;
     washer->timer = 0;
     washer->direction = FORWARD;
     Display_UpdateWasherState(washer->state, washer->programIndex);
     Display_UpdateTime();
 }
 
 // Read temperature from ADC
 float Read_Temperature(void) {
     HAL_ADC_Start(&hadc1);
     HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
     uint32_t adcValue = HAL_ADC_GetValue(&hadc1);
     HAL_ADC_Stop(&hadc1);
 
     // Convert ADC value to temperature (simple linear approximation)
     float temperature = (adcValue / 4095.0) * 100.0; // Example conversion
     return temperature;
 }
 
 // Update washer state machine
 void Washer_Update(WasherControl *washer) {
     float temperature = Read_Temperature();
     switch (washer->state) {
         case IDLE:
             // Wait for start button press
             break;
         case FILL_WATER:
             Display_UpdateWasherState(FILL_WATER, washer->programIndex);
             // Handle fill water logic based on temperature
             if (temperature < 25.0) {
                 HAL_GPIO_WritePin(HOT_WATER_PORT, HOT_WATER_PIN, GPIO_PIN_SET);
                 HAL_GPIO_WritePin(COLD_WATER_PORT, COLD_WATER_PIN, GPIO_PIN_RESET);
             } else if (temperature > 35.0) {
                 HAL_GPIO_WritePin(HOT_WATER_PORT, HOT_WATER_PIN, GPIO_PIN_RESET);
                 HAL_GPIO_WritePin(COLD_WATER_PORT, COLD_WATER_PIN, GPIO_PIN_SET);
             } else {
                 HAL_GPIO_WritePin(HOT_WATER_PORT, HOT_WATER_PIN, GPIO_PIN_SET);
                 HAL_GPIO_WritePin(COLD_WATER_PORT, COLD_WATER_PIN, GPIO_PIN_SET);
             }
             washer->state = WASH;
             break;
         case WASH:
             Display_UpdateWasherState(WASH, washer->programIndex);
             // Handle washing logic
             washer->state = RINSE;
             break;
         case RINSE:
             Display_UpdateWasherState(RINSE, washer->programIndex);
             // Handle rinsing logic
             washer->state = SPIN;
             break;
         case SPIN:
             Display_UpdateWasherState(SPIN, washer->programIndex);
             // Handle spinning logic
             washer->state = IDLE;
             break;
         case ERROR:
             Display_UpdateWasherState(ERROR, washer->programIndex);
             // Handle error condition
             break;
         default:
             Display_UpdateWasherState(ERROR, washer->programIndex);
             break;
     }
     Display_UpdateTime(); // Refresh time display
 }
 
 // Handle button inputs
 void Washer_HandleButtonPress(WasherControl *washer, int button) {
     if (button == BUTTON_START && washer->state == IDLE) {
         washer->state = FILL_WATER;
         Display_UpdateWasherState(washer->state, washer->programIndex);
     } else if (button == BUTTON_STOP) {
         washer->state = IDLE;
         Display_UpdateWasherState(washer->state, washer->programIndex);
     } else if (button == BUTTON_UP && washer->state == IDLE) {
         if (washer->programIndex < 29) {
             washer->programIndex++;
             Display_ShowSelectedProgram(washer->programIndex);
         }
     } else if (button == BUTTON_DOWN && washer->state == IDLE) {
         if (washer->programIndex > 0) {
             washer->programIndex--;
             Display_ShowSelectedProgram(washer->programIndex);
         }
     }
     Display_UpdateTime(); // Ensure time updates when buttons are pressed
 }
 
 // Function to update the 24-hour clock on the display
 void Display_UpdateTime(void) {
     RTC_TimeTypeDef sTime;
     RTC_DateTypeDef sDate;
     char timeString[10];
 
     HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
     HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
 
     sprintf(timeString, "%02d:%02d:%02d", sTime.Hours, sTime.Minutes, sTime.Seconds);
     Display_ShowTime(timeString);
 }
 