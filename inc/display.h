/**
 * @file washer.c
 * @brief Washer control state machine implementation for STM32-based system.
 *
 * This source file defines the core behavior of the washer control system, 
 * managing different operating states and responding to user inputs.
 * It includes:
 * - Initialization of the washer control structure.
 * - Periodic updating of the washer's operating state (state machine).
 * - Handling of button presses (Start, Stop, Up, Down) to control program selection and operation.
 * - Interaction with the display module to reflect the current washer state and selected program.
 *
 * Main Functions:
 * - Washer_Init(WasherControl *washer): Initializes the washer to the IDLE state and updates the display.
 * - Washer_Update(WasherControl *washer): Progresses the washer through its operation cycle 
 *   (FILL_WATER → WASH → RINSE → SPIN → IDLE) based on the current state.
 * - Washer_HandleButtonPress(WasherControl *washer, int button): Handles user button input to 
 *   start/stop the washer or change the selected program when idle.
 *
 * Dependencies:
 * - washer.h (for WasherControl struct and state definitions)
 * - display.h (for updating the display based on washer state)
 * - main.h (for button definitions)
 * - rtc.h (for updating real-time clock display)
 *
 * Notes:
 * - State transitions are linear and automatic after each phase (fill → wash → rinse → spin).
 * - Button handling only affects operation when the washer is IDLE.
 * - The time display is refreshed both during state changes and button presses.
 */


 #include "washer.h"
 #include "display.h"
 #include "main.h"
 #include "rtc.h"
 
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
 
 // Update washer state machine
 void Washer_Update(WasherControl *washer) {
     switch (washer->state) {
         case IDLE:
             // Wait for start button press
             break;
         case FILL_WATER:
             Display_UpdateWasherState(FILL_WATER, washer->programIndex);
             // Handle fill water logic
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
 