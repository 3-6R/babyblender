/**
 * @file spi.h
 * @brief Interface for SPI communication with the display module.
 *
 * This header defines SPI communication functions and display control operations,
 * along with GPIO pin configuration for the display chip select (CS) line.
 *
 * Functionality:
 * - `SPI_Init()` initializes the SPI peripheral for communication.
 * - `SPI_SendCommand(uint8_t cmd)` sends a command byte to the display.
 * - `SPI_SendData(uint8_t data)` sends a data byte to the display.
 * - `SPI_DisplayClear()` clears the entire display buffer.
 * - `SPI_WriteString(uint8_t row, uint8_t col, const char *text)` writes a string at the specified row and column.
 * - `SPI_CheckStatus()` returns the SPI status via HAL.
 *
 * Display Control:
 * - `DISPLAY_CS_GPIO_Port` and `DISPLAY_CS_Pin` define the chip select pin used to initiate communication with the display.
 *
 * Dependencies:
 * - Requires STM32 HAL (`stm32c0xx_hal.h`).
 * - Uses `stdint.h` and `stddef.h` for standard data types.
 *
 * Usage:
 * - Call `SPI_Init()` during system setup.
 * - Use the provided functions to control and update display content via SPI.
 */



 #ifndef SPI_H
 #define SPI_H
 
 #include "stm32c0xx_hal.h"
 #include <stdint.h>
 #include <stddef.h>
 
 // Define SPI-related GPIO pins
 #define DISPLAY_CS_GPIO_Port GPIOB
 #define DISPLAY_CS_Pin GPIO_PIN_6
 
 // SPI communication functions
 void SPI_Init();
 void SPI_SendCommand(uint8_t cmd);
 void SPI_SendData(uint8_t data);
 void SPI_DisplayClear();
 void SPI_WriteString(uint8_t row, uint8_t col, const char *text);
 HAL_StatusTypeDef SPI_CheckStatus();
 
 #endif // SPI_H
 