/**
 * @file Scheduler.c
 * @author Andreas Schmidt (a.v.schmidt81@gmail.com)
 * @brief Implementation of the cooperative scheduler with a 
 * pre-defined set of cyclic "task slots"
 *
 * @version 0.1
 * @date 2023-02-16
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "Scheduler.h"

/*
 * Private Defines
*/
#define HAL_TICK_VALUE_1MS      1       //!< Number of HAL Ticks used for 1ms Tasks
#define HAL_TICK_VALUE_10MS     10      //!< Number of HAL Ticks used for 10ms Tasks
#define HAL_TICK_VALUE_100MS    100     //!< Number of HAL Ticks used for 100ms Tasks
#define HAL_TICK_VALUE_250MS    250     //!< Number of HAL Ticks used for 250ms Tasks
#define HAL_TICK_VALUE_1000MS   1000    //!< Number of HAL Ticks used for 1000ms Tasks


int32_t schedInitialize(Scheduler* pScheduler)
{

    return SCHED_ERR_OK;
}


int32_t schedCycle(Scheduler* pScheduler)
{


    return SCHED_ERR_OK;
}
