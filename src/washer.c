/**
 * @file washer.c
 * @brief Washer control state machine implementation for STM32 washer controller.
 *
 * This file manages washer operation including filling, washing, rinsing, and spinning,
 * as well as handling manual button input and updating the display accordingly.
 *
 * =============================
 *        PIN DEFINITIONS
 * =============================
 * Replace the following macros with actual values in main.h or pin configuration file:
 *   - MOTOR_FORWARD_PIN
 *   - MOTOR_REVERSE_PIN
 *   - MOTOR_GPIO_PORT
 *   - WATER_HOT_PIN
 *   - WATER_COLD_PIN
 *   - WATER_GPIO_PORT
 *
 * =============================
 *        STATE MACHINE
 * =============================
 * WasherState Enum:
 *   - IDLE        : All outputs off; waiting for Start input.
 *   - FILL_WATER  : Turns on water valves for fixed duration (10s), then transitions to WASH.
 *   - WASH        : (To be implemented) Forward/Reverse motor logic, then transitions to RINSE.
 *   - RINSE       : (To be implemented) Motor rinse logic, then transitions to SPIN.
 *   - SPIN        : Forward spin only, then transitions to IDLE.
 *   - ERROR       : All outputs off, shows error on display.
 *
 * =============================
 *        FUNCTIONS
 * =============================
 *
 * void Washer_Init(WasherControl *washer)
 *   - Initializes the washer state machine structure.
 *   - Resets state, program index, timer, and motor direction.
 *   - Updates display to reflect washer state.
 *
 * void Washer_Update(WasherControl *washer)
 *   - Main logic handler. Called periodically in main loop.
 *   - Transitions between states and controls outputs based on elapsed time.
 *   - Uses HAL_GetTick() for timing fill duration.
 *   - Motor control logic for WASH/RINSE is currently a placeholder.
 *
 * void Washer_HandleButtonPress(WasherControl *washer, int button)
 *   - Handles manual button input:
 *       * Start: Begins cycle from IDLE.
 *       * Stop : Forces state to IDLE.
 *       * Up   : Increments program index (max 29).
 *       * Down : Decrements program index (min 0).
 *   - Updates display when program index or state changes.
 *
 * =============================
 *        TODO / FUTURE
 * =============================
 * - Implement timed motor control for WASH and RINSE:
 *     * Forward 16s → Stop 4s → Reverse 16s (repeat or advance step)
 * - Implement spinTimer logic to allow SPIN to run for specific time.
 * - Store/execute multiple steps per program (future enhancement).
 * - Replace placeholder GPIO_PIN_X/Y macros with actual pin assignments.
 */



 #include "washer.h"
 #include "display.h"
 #include "main.h"
 
 #define MOTOR_FORWARD_PIN GPIO_PIN_X  // Replace X with actual pin number
 #define MOTOR_REVERSE_PIN GPIO_PIN_Y  // Replace Y with actual pin number
 #define MOTOR_GPIO_PORT GPIOB         // Adjust as needed
 
 // Initialize washer state
 void Washer_Init(WasherControl *washer) {
     washer->state = IDLE;
     washer->programIndex = 0;
     washer->stepIndex = 0;
     washer->timer = 0;
     washer->direction = FORWARD;
     Display_UpdateWasherState(washer->state, washer->programIndex);
 }
 
 void Washer_Update(WasherControl *washer) {
     static uint32_t lastTime = 0;
     uint32_t currentTime = HAL_GetTick();
 
     switch (washer->state) {
         case IDLE:
             // Ensure all outputs are off
             HAL_GPIO_WritePin(MOTOR_GPIO_PORT, MOTOR_FORWARD_PIN | MOTOR_REVERSE_PIN, GPIO_PIN_RESET);
             HAL_GPIO_WritePin(WATER_GPIO_PORT, WATER_HOT_PIN | WATER_COLD_PIN, GPIO_PIN_RESET);
             break;
 
         case FILL_WATER:
             Display_UpdateWasherState(FILL_WATER, washer->programIndex);
             HAL_GPIO_WritePin(WATER_GPIO_PORT, WATER_HOT_PIN, GPIO_PIN_SET);
             HAL_GPIO_WritePin(WATER_GPIO_PORT, WATER_COLD_PIN, GPIO_PIN_SET);
 
             // Simulate a fill duration
             if (currentTime - lastTime >= 10000) {  // 10s fill time (adjust as needed)
                 HAL_GPIO_WritePin(WATER_GPIO_PORT, WATER_HOT_PIN | WATER_COLD_PIN, GPIO_PIN_RESET);
                 washer->state = WASH;
                 lastTime = currentTime;
             }
             break;
 
         case WASH:
             Display_UpdateWasherState(WASH, washer->programIndex);
             // Motor control logic remains the same
             washer->state = RINSE;
             break;
 
         case RINSE:
             Display_UpdateWasherState(RINSE, washer->programIndex);
             // Motor control logic remains the same
             washer->state = SPIN;
             break;
 
         case SPIN:
             Display_UpdateWasherState(SPIN, washer->programIndex);
             HAL_GPIO_WritePin(MOTOR_GPIO_PORT, MOTOR_FORWARD_PIN, GPIO_PIN_SET);
             HAL_GPIO_WritePin(MOTOR_GPIO_PORT, MOTOR_REVERSE_PIN, GPIO_PIN_RESET);
             washer->state = IDLE;
             break;
 
         case ERROR:
             Display_UpdateWasherState(ERROR, washer->programIndex);
             HAL_GPIO_WritePin(MOTOR_GPIO_PORT, MOTOR_FORWARD_PIN | MOTOR_REVERSE_PIN, GPIO_PIN_RESET);
             HAL_GPIO_WritePin(WATER_GPIO_PORT, WATER_HOT_PIN | WATER_COLD_PIN, GPIO_PIN_RESET);
             break;
 
         default:
             washer->state = ERROR;
             break;
     }
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
 }
 