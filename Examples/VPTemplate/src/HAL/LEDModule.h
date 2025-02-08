/**
 * @file LEDModule.h
 * @author Andreas Schmidt (a.v.schmidt81@gmail.com)
 * @brief Header file for the LED module
 *
 * @version 0.1
 * @date 2023-02-13
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef _LED_MODULE_H_
#define _LED_MODULE_H_

#include "stm32g4xx_hal.h"

#include <stdint.h>

/*
 * Public Defines
*/
#define LED_ERR_OK      0               //!< No error occured

/**
 * @brief Enumeration of available LEDs and their usage
 *
 */
typedef enum _LED_t
{
    LED0,                    			//!< LED0 used for Mode indication
    LED1,                   			//!< LED1
    LED2,                     			//!< LED2
	LED3,                  				//!< LED3 used for Motor indication
    LED4                   				//!< LED4 used for Sensor Failure/OK
} LED_t;

/**
 * @brief Enumeration of possible LED status
 *
 */
typedef enum _LED_Status_t
{
    LED_ON  = GPIO_PIN_SET,             //!< Value to turn a LED on
    LED_OFF = GPIO_PIN_RESET            //!< Value to turn a LED off
} LED_Status_t;

/**
 * @brief Initialize the GPIOs for the LED outouts
 *
 * @return Returns LED_ERR_OK if no error occured
 */
int32_t ledInitialize();

/**
 * @brief Toggles the provided LED
 *
 * @param led LED to toggle
 */
void ledToggleLED(LED_t led);

/**
 * @brief Allows to set (turn on) or reset (turn off) a LED
 *
 * @param led LED which should be changed
 * @param ledStatus New status of the LED
 */
void ledSetLED(LED_t led, LED_Status_t ledStatus);

#endif
