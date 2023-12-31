#include <stdio.h>
#include "LedDriver.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "led_strip.h"
#include "sdkconfig.h"
#include "ADCDriver.h"

#define POLLING_PERIOD_IN_MS 90
// TODO: Get accurate maximal voltage from ADCDriver
#define MAX_VOLTAGE_VREF 1000
#define MAX_FREQUENCY 10
#define HYSTRERESIS_VOLTAGE_MESSURSMENT 20  
#define FREQUENCY_ALWAYS_ON_THRESHOLD 0.4

static uint16_t voltage_in_mV;
static uint16_t voltage_in_mV_temp;
static const char *TAG = "Main";
static float frequency_in_Hz;
float period; 
float half_period;

void set_voltage_in_mV_temp(uint16_t voltage)
{
    voltage_in_mV_temp = voltage;
}

static float convert_cached_voltage_to_frequency(void)
{
    // convert voltage to frequency
    float max_voltage_float = (float)MAX_VOLTAGE_VREF;
    float ratio = (voltage_in_mV / max_voltage_float);
    float frequency = ratio * MAX_FREQUENCY;

    return frequency;
}

static bool check_for_voltage_change(uint16_t recent_voltage_reading_in_mV)
{
    // ADCDriver_read_voltage(&voltage_in_mV_temp);
    // ESP_LOGI("check_for_voltage_change", "voltage %d", voltage_in_mV_temp);
    // TODO: replace argument with voltage_in_mV_temp interna
    if(voltage_in_mV > (recent_voltage_reading_in_mV + HYSTRERESIS_VOLTAGE_MESSURSMENT) ||
        voltage_in_mV < (recent_voltage_reading_in_mV - HYSTRERESIS_VOLTAGE_MESSURSMENT) )
    {
        return true;
    }
    else
    {
        return false;
    }
}

static void set_voltage()
{
    voltage_in_mV = voltage_in_mV_temp;
}

static void convert_frequency_to_period(float frequency)
{
    period = (1 / frequency);
    // return period;
}

void sleep_with_intermediate_voltage_poll(float duration_in_s)
{    
    
    uint16_t interval_count = (uint16_t)(duration_in_s * 1000 / POLLING_PERIOD_IN_MS);
    for(int i = 0; i <= interval_count; i++) 
    {
        ADCDriver_read_voltage(&voltage_in_mV_temp);
        vTaskDelay(pdMS_TO_TICKS((POLLING_PERIOD_IN_MS)));
        if(check_for_voltage_change(voltage_in_mV_temp))
        {
            set_voltage();
            return;
        } 
       
    }
    return; 
    
}

void adjustable_blinky_create(void)
{   
    /* Configure the peripheral according to the LED type */
    LedDriver_Create();
    ESP_LOGI(TAG, "Initialized LED Driver");
    ADCDriver_Create();    
    ESP_LOGI(TAG, "Initialized ADC Driver");
    ADCDriver_read_voltage(&voltage_in_mV);
}

void adjustable_blinky_run(void) 
{
    while(1){
        frequency_in_Hz = convert_cached_voltage_to_frequency();
        convert_frequency_to_period(frequency_in_Hz);
        half_period = period / 2;
        // ESP_LOGI(TAG, "Frequency is %f", frequency_in_Hz); 

        LED_Driver_Turn_LED_on();

        // TODO: Update ADC Driver to get value directly from DMA and Timer
        // from ADC Interrupt. Due to time project time constrain, polling was implemented. 
        
        sleep_with_intermediate_voltage_poll(half_period);
        
        if (!(frequency_in_Hz < FREQUENCY_ALWAYS_ON_THRESHOLD)) {
            LED_Driver_Turn_LED_off();
            sleep_with_intermediate_voltage_poll(half_period);
        }
        // ESP_LOGI(TAG, "Frequency %f", frequency_in_Hz);
    }
}
