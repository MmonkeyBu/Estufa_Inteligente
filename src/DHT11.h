#ifndef DHT11_H
#define DHT11_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"
#include "main.h"

void dht11(uint16_t *temperatura, uint16_t *umidade);
 extern uint16_t tempdht11;
 extern uint16_t umidht11;
	#ifdef __cplusplus
}
#endif

#endif /* DHT11_H */
