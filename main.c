/*
 * Copyright (c) 2022 Mr. Green's Workshop https://www.MrGreensWorkshop.com
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "keyboard_tasks.h"
#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"
#include "btstack_run_loop.h"
#include "hardware/uart.h"
#include "tusb.h"

int btstack_main(int argc, const char* argv[]);

/* Stubs for FreeRTOS */
void vApplicationStackOverflowHook(TaskHandle_t pxTask, char* pcTaskName)
{
}
void vApplicationMallocFailedHook(void)
{
}

static void task_ble(void* pv)
{
	if(cyw43_arch_init())
	{
		printf("cyw43_arch_init() failed.\n");
		while(1)
			;
	}

	// run the app
	btstack_main(0, NULL);
	while(1)
	{
		btstack_run_loop_execute(); /* Does not return */
	}
}

void main_ble_setup(void)
{
	if(xTaskCreate(task_ble, "ble_task", 1200 / sizeof(StackType_t), (void*)NULL, BLE_TASK_PRIORITY,
				   (TaskHandle_t*)NULL) != pdPASS)
	{
		printf("BLE task creat fail.\n");
		for(;;)
		{
		} /* error! probably out of memory */
	}
}
int main()
{
	stdio_init_all();
	// To make execution wait for usb serial connection
	while(!tud_cdc_connected())
	{
		sleep_ms(100);
	};
	main_ble_setup();
	vTaskStartScheduler();
}
