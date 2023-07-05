#ifndef D_Adjustable_blinky_H
#define D_Adjustable_blinky_H

/// Included for unity test:
void set_voltage_in_mV_temp(uint16_t voltage);
void sleep_with_intermediate_voltage_poll(float duration_in_s);

void adjustable_blinky_create(void);
void adjustable_blinky_run(void);



#endif  /* D_Adjustable_blinky_H */