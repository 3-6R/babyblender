/**
 * @file adc.c
 * @brief ADC temperature reading implementation for STM32C0 series.
 *
 * This source file implements the function declared in adc.h for reading
 * a temperature value from the ADC peripheral (hadc1). The process includes:
 * - Starting an ADC conversion.
 * - Waiting for the conversion to complete.
 * - Reading the raw ADC value.
 * - Stopping the ADC.
 * - Converting the raw ADC value into a temperature (in degrees) using
 *   a simple linear formula.
 *
 * The current conversion assumes a 12-bit ADC resolution (0-4095 range) 
 * and maps the value proportionally to a 0-100°C temperature scale.
 * Adjust the conversion formula based on the actual sensor characteristics.
 *
 * Dependencies:
 * - adc.h (for function prototype and external ADC handle)
 * - stm32c0xx_hal.h (for HAL ADC functions)
 *
 * Usage:
 * Call Read_Temperature() to get the current temperature reading as a float.
**/


#include "adc.h"

// Function to read temperature from ADC
float Read_Temperature(void) {
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
    uint32_t adcValue = HAL_ADC_GetValue(&hadc1);
    HAL_ADC_Stop(&hadc1);

    // Convert ADC value to temperature (example linear conversion)
    float temperature = (adcValue / 4095.0) * 100.0; // Adjust as needed
    return temperature;
}
