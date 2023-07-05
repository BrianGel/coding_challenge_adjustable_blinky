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
    uint16_t voltage_in_mV_temp = 1000;
    uint64_t start_time = esp_timer_get_time();

    vTaskDelay(110);
    

    // check if the function returns within 100ms
    uint64_t end_time = esp_timer_get_time();
    uint32_t elapsed_time = end_time - start_time;
    TEST_ASSERT_TRUE(elapsed_time <= 100);
}

void setUp(void)
{
    // set up test environment
}

void tearDown(void)
{
    // clean up test environment
}