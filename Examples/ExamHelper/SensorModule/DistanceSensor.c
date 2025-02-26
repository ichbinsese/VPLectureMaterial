/******************************************************************************
 * @file DistanceSensor.c
 *
 * @author Andreas Schmidt (a.v.schmidt81@googlemail.com
 * @date   08.02.2025
 *
 * @copyright Copyright (c) 2025
 *
 ******************************************************************************
 *
 * @brief Sensor Module for Distance Sensor
 *
 *
 *****************************************************************************/


/***** INCLUDES **************************************************************/
#include "ADCModule.h"

#include "Filter/Filter.h"
#include "DistanceSensor.h"

/***** PRIVATE CONSTANTS *****************************************************/


/***** PRIVATE MACROS ********************************************************/
#define MIN_DISTANCE			50			// Min distance 50cm (5m)
#define MAX_DISTANCE			10000		// Max distance 10000cm (100m)

#define MIN_DISTANCE_VOLTAGE	500000		// µV of min voltage (0,5V) for valid distance (5m)
#define MAX_DISTANCE_VOLTAGE	2500000  	// µV of max voltage for valid distance (100m)

#define MICROVOLT_PER_CM		((MAX_DISTANCE_VOLTAGE - MIN_DISTANCE_VOLTAGE) / (MAX_DISTANCE - MIN_DISTANCE))

#define MIN_OUTOFRANGE_VOLTAGE	(1000 * MICROVOLT_PER_CM)

#define MIN_VALID_VOLTAGE		500000		// µV for voltage of sensor defect (min)
#define MAX_VALID_VOLTAGE		3000000	    // µV for voltage of sensor defect (max)

#define SENSOR_OUT_OF_RANGE		-1
#define SENSOR_DEFECT			-2

/***** PRIVATE TYPES *********************************************************/


/***** PRIVATE PROTOTYPES ****************************************************/
static int32_t sensorCalculateDistance(int32_t inputVoltage);


/***** PRIVATE VARIABLES *****************************************************/
static EMAFilterData_t gSensor1Filter;

static int32_t gSensor1Voltage;
static int32_t gSensor1VoltageFiltered;
static int32_t gSensor1Distance;


/***** PUBLIC FUNCTIONS ******************************************************/

int32_t sensorInitialize()
{
	gSensor1Voltage  		= 0;
	gSensor1VoltageFiltered = 0;
	gSensor1Distance 		= 0;

	filterInitEMA(&gSensor1Filter, 100, 70, true);

	return 0;
}

int32_t sensorCycle()
{
	gSensor1Voltage 			= adcReadChannel(ADC_INPUT0);
	gSensor1VoltageFiltered		= filterEMA(&gSensor1Filter, gSensor1Voltage);

	gSensor1Distance = sensorCalculateDistance(gSensor1VoltageFiltered);

	return 0;
}

int32_t sensorGetDistance()
{
	return gSensor1Distance;
}


/***** PRIVATE FUNCTIONS *****************************************************/

/**
 * Calculates the distance in cm for the provided input voltage
 * Input voltage in µV
 *
 * If the voltage if smaller than MIN_VALID_VOLTAGE, sensor defect is returned
 * If the voltage is greater than MAX_VALID_VOLTAGE, sensor out of range is returned
 * If the voltage is greater than MAX_DEFECT_VOLTAGE
 */
static int32_t sensorCalculateDistance(int32_t inputVoltage)
{
	if (inputVoltage < MIN_VALID_VOLTAGE || inputVoltage > MAX_VALID_VOLTAGE)
		return SENSOR_DEFECT;

	if (inputVoltage >= MIN_VALID_VOLTAGE && inputVoltage < MIN_OUTOFRANGE_VOLTAGE)
		return SENSOR_OUT_OF_RANGE;

	if (inputVoltage > MAX_DISTANCE_VOLTAGE && inputVoltage < MAX_VALID_VOLTAGE)
		return SENSOR_OUT_OF_RANGE;

	if (inputVoltage > MAX_VALID_VOLTAGE)
		return SENSOR_DEFECT;

	int32_t distanceCm = ((inputVoltage - MIN_VALID_VOLTAGE) / MICROVOLT_PER_CM) + MIN_DISTANCE;

	return distanceCm;
}
