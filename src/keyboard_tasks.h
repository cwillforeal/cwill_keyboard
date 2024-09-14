#include "FreeRTOS.h"
#include "task.h"

/* We want this to be just above the idle task, we will sit here most of the time */
#define BLE_TASK_PRIORITY (tskIDLE_PRIORITY + 2)
