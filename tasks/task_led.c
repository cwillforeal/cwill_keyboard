#include "pico/stdlib.h"
#include "WS2812.h"
#include "FreeRTOS.h"
#include "tasks.h"
#include <stdio.h>

static void task_led(void* p);

static ws2812_t led;

void task_led_init(uint8_t led_pin, uint32_t led_count)
{
	// This uses a sk6812 led
	ws2812_initialize(&led, led_pin, led_count, pio0, 0, FORMAT_GRB);

	if(xTaskCreate(task_led, "led_task", 1200 / sizeof(StackType_t), (void*)NULL, LED_TASK_PRIORITY,
				   (TaskHandle_t*)NULL) != pdPASS)
	{
		printf("LED Task Failed\n");
	}
}

#define DELAY 25
#define MAX_BRIGHT 40
#define CHANGE ((DELAY * MAX_BRIGHT) / 1000)
static void task_led(void* p)
{
	bool led_increment = true;
	printf("Starting LED Task Init");
	rgbw_t color;

	color.blue = 0;
	color.green = 0;
	color.red = 0;

	while(1)
	{
		ws2812_fill(&led, ws2812_RGBW(&led, color), 0, led.length);
		ws2812_show(&led);

		if(led_increment)
		{
			if((color.red + CHANGE) >= MAX_BRIGHT)
			{
				color.red = MAX_BRIGHT;
				led_increment = false; // Flip directions we reached the top
			}
			else
			{
				color.red += CHANGE;
			}
		}
		else
		{
			if((color.red <= CHANGE))
			{
				color.red = 0;
				led_increment = true;
			}
			else
			{
				color.red -= CHANGE;
			}
		}
		vTaskDelay(DELAY);
	}
}