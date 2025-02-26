/******************************************************************************
 * @file DistanceSensor.h
 *
 * @author Andreas Schmidt (a.v.schmidt81@googlemail.com
 * @date   08.02.2025
 *
 * @copyright Copyright (c) 2025
 *
 ******************************************************************************
 *
 * @brief Public Header for Distance Sensor Module
 *
 *
 *****************************************************************************/
#ifndef SRC_SERVICE_DISTANCESENSOR_H_
#define SRC_SERVICE_DISTANCESENSOR_H_

/***** INCLUDES **************************************************************/
#include <stdint.h>

/***** CONSTANTS *************************************************************/


/***** MACROS ****************************************************************/


/***** TYPES *****************************************************************/


/***** PROTOTYPES ************************************************************/
int32_t sensorInitialize();
int32_t sensorCycle();

int32_t sensorGetDistance();


#endif /* SRC_SERVICE_DISTANCESENSOR_H_ */
