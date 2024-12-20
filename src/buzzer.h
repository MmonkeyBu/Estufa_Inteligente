#ifndef BUZZER_H
#define BUZZER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"

void Buzzer_Init(void);
void Buzzer_On(void);
void Buzzer_Off(void);

void estados(void);

#ifdef __cplusplus
}
#endif

#endif /* BUZZER_H */
