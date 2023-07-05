#ifndef D_ADCDriver_H
#define D_ADCDriver_H
#include <stdint.h>

void ADCDriver_Create(void);
void ADCDriver_Destroy(void);

uint32_t ADCDriver_get_voltage(void);


#endif  /* D_ADCDriver_H */