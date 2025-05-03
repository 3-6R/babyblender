/**
 * @file adc.h
 * @brief Interface for ADC-based temperature reading on STM32C0 series.
 *
 * This header file provides the declaration for accessing the ADC hardware
 * (hadc1) and reading temperature values through the function Read_Temperature().
 * It includes:
 * - External declaration of the ADC handle (hadc1) used for ADC operations.
 * - Prototype for the Read_Temperature() function, which reads an analog
 *   value from the ADC, converts it to a floating-point temperature value,
 *   and returns it.
 *
 * This file uses include guards to prevent multiple inclusions and relies
 * on the STM32 HAL library for hardware abstraction.
 *
 * Usage:
 * Include this header in any source file that needs to initiate ADC readings
 * or read temperature data.
 */


 #ifndef ADC_H
 #define ADC_H
 
 #include "stm32c0xx_hal.h"
 
 extern ADC_HandleTypeDef hadc1;
 
 // Function prototype to read temperature from ADC
 float Read_Temperature(void);
 
 #endif // ADC_H
 