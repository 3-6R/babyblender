/**
 * @file washer.h
 * @brief Washer control state machine definitions and data structures.
 *
 * This header defines the washer control logic, including the state machine
 * states, the WasherControl data structure, and associated function prototypes
 * for managing program flow in an industrial or household washer system.
 *
 * Definitions:
 * - `WasherState` enum: Enumerates all washer operation states such as IDLE,
 *   FILL_WATER, WASH, RINSE, SPIN, and DONE.
 * - `WasherControl` struct: Holds state information for a washer program, including:
 *   - current state
 *   - selected program index
 *   - individual timers for motor, fill, and spin phases
 *
 * Note:
 * - Replace `GPIO_PIN_X` and `GPIO_PIN_Y` with actual pin assignments in `main.h`.
 * - This module interacts with GPIO and should be synchronized with HAL or LL drivers.
 *
 * Function Prototypes:
 * - `updateWasher()`: Call this regularly to advance the washer through its steps
 *   based on timers, inputs, and temperature conditions.
 */

//Also, consider these two suggestions to improve washer.h:
//You may want to remove WATER_HOT_PIN, WATER_COLD_PIN, and WATER_GPIO_PORT from this header — they’re better placed and centralized in main.h, which already has them.
//Rename the prototype updateWasher() to Washer_Update() to match the implementation and be consistent with the rest of your naming.



#ifndef WASHER_H
#define WASHER_H

#include "main.h"

#define WATER_HOT_PIN   GPIO_PIN_X  // Replace X with actual pin
#define WATER_COLD_PIN  GPIO_PIN_Y  // Replace Y with actual pin
#define WATER_GPIO_PORT GPIOB       // Adjust based on actual wiring

// Washer States
typedef enum {
    IDLE,
    FILL_WATER,
    WASH,
    RINSE,
    SPIN,
    DONE
} WasherState;

// Washer Control Structure
typedef struct {
    WasherState state;
    int programIndex;
    int motorTimer;
    int fillTimer;
    int spinTimer;
} WasherControl;

// Function Prototypes
void updateWasher(WasherControl *washer);

#endif // WASHER_H
