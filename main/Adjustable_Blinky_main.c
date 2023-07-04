#include <stdio.h>
#include "LedDriver.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "led_strip.h"
#include "sdkconfig.h"


void app_main(void)
{

    /* Configure the peripheral according to the LED type */
    LedDriver_Create();
    // ADC_Create();
    

    while (1) {
        /* Toggle the LED state */
        toggle_led();
        vTaskDelay(CONFIG_BLINK_PERIOD / portTICK_PERIOD_MS);
    }
}