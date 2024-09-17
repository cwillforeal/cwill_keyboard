#include "FreeRTOS.h"
#include "task.h"
#include "pico/stdlib.h"

/* We want this to be just above the idle task, we will sit here most of the time */
#define BLE_TASK_PRIORITY (tskIDLE_PRIORITY + 2)
/* Above BLE but below most other things */
#define LED_TASK_PRIORITY (tskIDLE_PRIORITY + 3)

void task_led_init(uint8_t led_pin, uint32_t led_count);
