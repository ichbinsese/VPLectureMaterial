/**
 * @file main.c
 * @author Andreas Schmidt (a.v.schmidt81@gmail.com)
 * @brief Main file for the VP Template Project
 *
 * @version 0.1
 * @date 2023-02-13
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "stm32g4xx_hal.h"

#include "Util/Global.h"
#include "Util/printf.h"
#include "LogOutput.h"

#include "System.h"

#include "UARTModule.h"
#include "ButtonModule.h"
#include "LEDModule.h"
#include "ADCModule.h"
#include "TimerModule.h"
#include "DisplayModule.h"
#include "Scheduler.h"

#include "GlobalObjects.h"


static char gMsgBuffer[128];			// Only for Test-Message Outputs

static Scheduler gScheduler;			// Global Scheduler instance

/**
 * @brief Initializes the used peripherals like GPIO,
 * ADC, DMA and Timer Interrupts
 *
 * @return Returns ERROR_OK if no error occurred
 */
static int32_t initializePeripherals()
{
    // Initialize UART used for Debug-Outputs
    uartInitialize(115200);

    // Initialize GPIOs for Buttons
    buttonInitialize();

    // Initialize GPIOs for LED and 7-Segment output
    ledInitialize();
    displayInitialize();

    // Initialize Timer, DMA and ADC for sensor measurements
    timerInitialize();
    adcInitialize();

    return ERROR_OK;
}

int main(void)
{
    // Initialize the HAL
    HAL_Init();

    SystemClock_Config();

    // Initialize Peripherals
    initializePeripherals();

    // Prepare Scheduler
    // ...

    // Initialize Scheduler
    schedInitialize(&gScheduler);

    int globalCounter = 0;
    int currentDisplay = 0;

    while (1)
    {
    	// Toggle all LEDs to the their functionality (Toggle frequency depends on HAL_Delay at end of loop)
    	ledToggleLED(LED0);
    	ledToggleLED(LED1);
    	ledToggleLED(LED2);
    	ledToggleLED(LED3);
    	ledToggleLED(LED4);

    	// Read to buttons
    	Button_Status_t but1 = buttonGetButtonStatus(BTN_SW1);
    	Button_Status_t but2 = buttonGetButtonStatus(BTN_SW2);
    	Button_Status_t but3 = buttonGetButtonStatus(BTN_B1);

    	// Read the POT1 input from ADC
    	int adcValue = adcReadChannel(ADC_INPUT0);

    	// If SW1 is pressed, print some debug message on the terminal
    	if (but1 == BUTTON_PRESSED)
    	{
    		sprintf_(gMsgBuffer, "Some Message %d\n\r", globalCounter);
    		outputLog(gMsgBuffer);
    	}

    	// If SW2 is pressed, print the ADC digit value on the terminal
    	if (but2 == BUTTON_PRESSED)
		{
			sprintf_(gMsgBuffer, "ADC Val: %d\n\r", adcValue);
			outputLog(gMsgBuffer);
		}

    	// If B1 is pressed, print the ADC digit value on the terminal
		if (but3 == BUTTON_PRESSED)
		{
			sprintf_(gMsgBuffer, "Button B1\n\r");
			outputLog(gMsgBuffer);
		}

    	// Do some random stuff with the 7-Segment displays
    	globalCounter++;

    	if (currentDisplay <= 9)
    	{
			displayShowDigit(FLOOR_DISPLAY, currentDisplay);
			currentDisplay++;
    	}
    	else
    	{
			displayShowDigit(ERROR_DISPLAY, currentDisplay);

			currentDisplay++;

			if (currentDisplay >= 19)
				currentDisplay = 0;
    	}


    	// Remove this HAL_Delay as soon as there is a Scheduler used
    	HAL_Delay(100);

    	// Call the Scheduler
    	schedCycle(&gScheduler);
    }
}
