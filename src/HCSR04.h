#ifndef HCSR04_H
#define HCSR04_H

#include "stm32f4xx_hal.h"

#define TRIG_PIN GPIO_PIN_6
#define TRIG_PORT GPIOA
#define ECHO_PIN GPIO_PIN_7
#define ECHO_PORT GPIOA

void HCSR04_Init(void);
uint32_t HCSR04_ReadDistance(void);

#endif
