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

static uint16_t voltage_in_mV;
static const char *TAG = "Main";

void app_main(void)
{   
    ESP_LOGI(TAG, "Initialized ADC");
    /* Configure the peripheral according to the LED type */
    LedDriver_Create();
    ADCDriver_Create();    
    ESP_LOGI(TAG, "Initialized ADC");
    // voltage = ADCDriver_get_voltage();
    // ESP_LOGI(TAG, "Value: %d", voltage);

    while (1) {
        ADCDriver_read_voltage(&voltage_in_mV);
        ESP_LOGI(TAG, " Cali Voltage: %d mV", voltage_in_mV);
        /* Toggle the LED state */
        toggle_led();

        vTaskDelay(pdMS_TO_TICKS(90));
        vTaskDelay(CONFIG_BLINK_PERIOD / portTICK_PERIOD_MS);
    }
}

static void adjustable_blink_sleep(void)
{
    vTaskDelay(pdMS_TO_TICKS(90));
}