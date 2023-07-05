/* test_mean.c: Implementation of a testable component.

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <limits.h>
#include "unity.h"
#include "Adjustable_blinky.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

TEST_CASE("LED frequency change response time is lower then 100ms", "[]")
{
    adjustable_blinky_create();
    set_voltage_in_mV_temp(1000);
    float loop_duration_in_s = 0.1;

    // Observation: pdMS_TO_TICKS is off by times 10. pdMS_TO_TICKS(10) are 100ms
    vTaskDelay(pdMS_TO_TICKS(10));

    uint64_t start_time = esp_timer_get_time();
    sleep_with_intermediate_voltage_poll(loop_duration_in_s);

    // check if the function returns within 100ms
    uint64_t end_time = esp_timer_get_time();
    uint32_t elapsed_time = end_time - start_time;
    TEST_ASSERT_TRUE(elapsed_time <= 100);
}