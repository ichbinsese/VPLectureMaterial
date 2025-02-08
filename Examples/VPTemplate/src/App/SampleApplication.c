/**
 * @file SampleApplication.c
 * @author Andreas Schmidt (a.v.schmidt81@gmail.com)
 * @brief Implementation of small sample application based on
 * state machine table
 *
 * @version 0.1
 * @date 2023-02-24
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <string.h>
#include "Util/Global.h"
#include "Util/printf.h"

#include "UARTModule.h"
#include "ButtonModule.h"
#include "LEDModule.h"

#include "Util/StateTable/StateTable.h"

#include "SampleApplication.h"

/*
 * Private Functions
*/

// State realte functions (on-Entry, on-State and on-Exit)
static int32_t onEntryStartup(State_t* pState, int32_t eventID);
static int32_t onStateRunning(State_t* pState, int32_t eventID);
static int32_t onExitRunning(State_t* pState, int32_t eventID);
static int32_t onEntryFailure(State_t* pState, int32_t eventID);

/**
 * @brief List of State for the State Machine
 *
 * This list only constructs the state objects for each possible state
 * in the state machine. There are no transistions or events defined
 *
 */
static State_t gStateList[] =
{
    {STATE_ID_STARTUP, onEntryStartup,  0,                  0,              false},
    {STATE_ID_RUNNING, 0,               onStateRunning,     onExitRunning,  false},
    {STATE_ID_FAILURE, onEntryFailure,  0,                  0,              false}
};

/**
 * @brief Definition of the transistion table of the state machine. Each row
 * contains FROM_STATE_ID, TO_STATE_ID, EVENT_ID, Function Pointer Guard Function
 *
 * The last two members of a transistion row are only the initialization of dynamic
 * members used durin runtim
 */
static StateTableEntry_t gStateTableEntries[] =
{
    {STATE_ID_STARTUP,          STATE_ID_RUNNING,           EVT_ID_INIT_READY,          0,      0,      0},
    {STATE_ID_STARTUP,          STATE_ID_FAILURE,           EVT_ID_SENSOR_FAILED,       0,      0,      0},
    {STATE_ID_RUNNING,          STATE_ID_FAILURE,           EVT_ID_SENSOR_FAILED,       0,      0,      0}
};

/**
 * @brief Global State Table instance
 *
 */
static StateTable_t gStateTable;


int32_t sampleAppInitialize()
{
    gStateTable.pStateList = gStateList;
    gStateTable.stateCount = sizeof(gStateList) / sizeof(State_t);
    int32_t result = stateTableInitialize(&gStateTable, gStateTableEntries, sizeof(gStateTableEntries) / sizeof(StateTableEntry_t), STATE_ID_STARTUP);

    return result;
}

int32_t sampleAppRun()
{
    int32_t result = stateTableRunCyclic(&gStateTable);
    return result;
}

int32_t sameplAppSendEvent(int32_t eventID)
{
    int32_t result = stateTableSendEvent(&gStateTable, eventID);
    return result;
}

static int32_t onEntryStartup(State_t* pState, int32_t eventID)
{
    return sameplAppSendEvent(EVT_ID_INIT_READY);
}

static int32_t onStateRunning(State_t* pState, int32_t eventID)
{
    ledToggleLED(LED1_DOOR_STATUS);
    return 0;
}

static int32_t onExitRunning(State_t* pState, int32_t eventID)
{
    return 0;
}

static int32_t onEntryFailure(State_t* pState, int32_t eventID)
{
    ledSetLED(LED3_MOTOR_STATUS, LED_ON);
    return 0;
}