#ifndef D_ADCDriver_H
#define D_ADCDriver_H
#include <stdint.h>

void ADCDriver_Create(void);
void ADCDriver_Destroy(void);

bool ADCDriver_read_voltage(uint16_t *voltage_in_mV);


#endif  /* D_ADCDriver_H */