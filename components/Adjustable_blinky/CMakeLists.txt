idf_component_register(SRCS "Adjustable_blinky.c"
                    REQUIRES led_strip
                    REQUIRES driver
                    # REQUIRES esp_log
                    REQUIRES freertos
                    REQUIRES LedDriver
                    REQUIRES ADCDriver
                    INCLUDE_DIRS "include")
