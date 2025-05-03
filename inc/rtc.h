/**
 * @file rtc.h
 * @brief Header file for Real-Time Clock (RTC) management.
 *
 * This file declares the external RTC handle and provides the prototype
 * for initializing the RTC peripheral.
 *
 * Functionality:
 * - Defines the external `RTC_HandleTypeDef` used across the system.
 * - Declares `MX_RTC_Init()` function for setting up the RTC hardware.
 *
 * Notes:
 * - `MX_RTC_Init()` must be called during system initialization to configure the RTC.
 * - Supports both C and C++ compilation by wrapping in `extern "C"`.
 *
 * Dependencies:
 * - Requires the STM32 HAL RTC driver (`stm32c0xx_hal.h`).
 *
 * Usage:
 * - Call `MX_RTC_Init()` once at startup.
 * - Use `hrtc` handle to access HAL RTC functions throughout the project.
 */



 #ifndef __RTC_H__
 #define __RTC_H__
 
 #ifdef __cplusplus
 extern "C" {
 #endif
 
 #include "stm32c0xx_hal.h"
 
 extern RTC_HandleTypeDef hrtc;
 
 void MX_RTC_Init(void);
 
 #ifdef __cplusplus
 }
 #endif
 
 #endif /* __RTC_H__ */
 