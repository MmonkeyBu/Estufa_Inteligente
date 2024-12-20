#ifndef SERVO_H
#define SERVO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"

void Servo_Init(void);
void Servo_SetAngle(uint8_t angle);

#ifdef __cplusplus
}
#endif

#endif /* SERVO_H */
