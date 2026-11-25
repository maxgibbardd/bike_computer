#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>

void toggle_LED(void *arg)
{
    int LED_level = 0;

    // set pin 13 as an output
    gpio_set_direction(GPIO_NUM_13, GPIO_MODE_OUTPUT);

    // flip the LED every 500ms
    while (1)
    {
        LED_level = !LED_level;
        gpio_set_level(GPIO_NUM_13, LED_level);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void print_sec(void *arg)
{
    float sec = 0.0;

    // print the seconds passed every 2000ms
    while (1)
    {
        printf("%.1fs\n", sec);
        vTaskDelay(pdMS_TO_TICKS(2000));
        sec += 2.0;
    }
}

void app_main(void)
{
    // Two task functions
    xTaskCreate(toggle_LED, "toggle_LED", 2048, NULL, 5, NULL); // Toggles red LED
    xTaskCreate(print_sec, "print_sec", 2048, NULL, 5, NULL);   // Print seconds
}