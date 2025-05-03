/**
 * @file spi.c
 * @brief SPI communication driver for display control.
 *
 * This file provides implementations for initializing and using the SPI interface
 * to communicate with a character or graphical display. It includes basic SPI
 * transmit functions and high-level display control features.
 *
 * Features:
 * - `SPI_Init()` assumes CubeMX handles peripheral init but is available for extensions.
 * - `SPI_SendCommand()` transmits command bytes with CS toggling.
 * - `SPI_SendData()` transmits data bytes with CS toggling.
 * - `SPI_DisplayClear()` sends a display clear command and waits briefly.
 * - `SPI_WriteString()` sends a formatted string with position data (for debugging or display logic simulation).
 * - `SPI_CheckStatus()` transmits a dummy byte to test SPI bus functionality.
 *
 * Note:
 * - Actual display protocol may require adjusting `SPI_WriteString()` formatting or using specific controller commands.
 * - Make sure `DISPLAY_CS_Pin` and `DISPLAY_CS_GPIO_Port` are properly initialized.
 * - Ensure `hspi1` is declared and initialized via CubeMX or manually before use.
 */



 #include "spi.h"
 #include "main.h"
 #include <string.h>
 
 extern SPI_HandleTypeDef hspi1; // Assuming SPI1 is used
 
 // Function to initialize SPI
 void SPI_Init() {
     // This function assumes SPI is configured in CubeMX
     // Any additional low-level configurations can be added here if needed
 }
 
 // Function to send a command to the display
 void SPI_SendCommand(uint8_t cmd) {
     HAL_GPIO_WritePin(DISPLAY_CS_GPIO_Port, DISPLAY_CS_Pin, GPIO_PIN_RESET);
     HAL_SPI_Transmit(&hspi1, &cmd, 1, HAL_MAX_DELAY);
     HAL_GPIO_WritePin(DISPLAY_CS_GPIO_Port, DISPLAY_CS_Pin, GPIO_PIN_SET);
 }
 
 // Function to send data to the display
 void SPI_SendData(uint8_t data) {
     HAL_GPIO_WritePin(DISPLAY_CS_GPIO_Port, DISPLAY_CS_Pin, GPIO_PIN_RESET);
     HAL_SPI_Transmit(&hspi1, &data, 1, HAL_MAX_DELAY);
     HAL_GPIO_WritePin(DISPLAY_CS_GPIO_Port, DISPLAY_CS_Pin, GPIO_PIN_SET);
 }
 
 // Function to clear the display
 void SPI_DisplayClear() {
     SPI_SendCommand(0x01); // Command to clear display (depends on display controller)
     HAL_Delay(2); // Delay for command execution
 }
 
 // Function to write a string to the display at a specific row and column
 void SPI_WriteString(uint8_t row, uint8_t col, const char *text) {
     char buffer[20];
     snprintf(buffer, sizeof(buffer), "[%d,%d] %s", row, col, text);
 
     HAL_GPIO_WritePin(DISPLAY_CS_GPIO_Port, DISPLAY_CS_Pin, GPIO_PIN_RESET);
     HAL_SPI_Transmit(&hspi1, (uint8_t *)buffer, strlen(buffer), HAL_MAX_DELAY);
     HAL_GPIO_WritePin(DISPLAY_CS_GPIO_Port, DISPLAY_CS_Pin, GPIO_PIN_SET);
 }
 
 // Function to check SPI communication status
 HAL_StatusTypeDef SPI_CheckStatus() {
     uint8_t dummyData = 0x00;
     return HAL_SPI_Transmit(&hspi1, &dummyData, 1, 100);
 }
 