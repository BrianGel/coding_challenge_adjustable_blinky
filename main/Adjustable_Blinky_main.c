#include <stdio.h>
#include "LedDriver.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "led_strip.h"
#include "sdkconfig.h"
#include "ADCDriver.h"

static uint32_t data;
static const char *TAG = "Main";

void app_main(void)
{   
    ESP_LOGI(TAG, "Initialized ADC");
    /* Configure the peripheral according to the LED type */
    LedDriver_Create();
    ADCDriver_Create();    
    ESP_LOGI(TAG, "Initialized ADC");
    data = ADCDriver_get_voltage();
    ESP_LOGI(TAG, "Value: %"PRIx32, data);

    while (1) {
        // ESP_LOGI(TAG, "Value: %"PRIx32, mydata);
        /* Toggle the LED state */
        toggle_led();
        vTaskDelay(CONFIG_BLINK_PERIOD / portTICK_PERIOD_MS);
    }
}