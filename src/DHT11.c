#include "dht11.h"

/* Definição das variáveis globais */
uint16_t tempdht11 = 0;
uint16_t umidht11 = 0;

void DHT11_SetPinMode(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint32_t Mode) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_Pin;
    GPIO_InitStruct.Mode = Mode;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void dht11(uint16_t *temperatura, uint16_t *umidade) {
    uint8_t bits[40] = {0};
    uint16_t dados[42] = {0};
    uint32_t timeout;
    uint16_t tempcalc = 0, umidcalc = 0;

    // Configura o pino como saída
    DHT11_SetPinMode(GPIOA, GPIO_PIN_8, GPIO_MODE_OUTPUT_PP);

    // Pulso de início
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
    HAL_Delay(20); // Mínimo de 18ms
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);

    // Configura o pino como entrada
    DHT11_SetPinMode(GPIOA, GPIO_PIN_8, GPIO_MODE_INPUT);

    // Inicializa o contador do Timer
    __HAL_TIM_SET_COUNTER(&htim2, 0);

    // Captura os pulsos de resposta e dados do sensor
    for (int i = 0; i < 42; i++) {
        // Aguarda sinal LOW
        timeout = __HAL_TIM_GET_COUNTER(&htim2);
        while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_RESET) {
            if ((__HAL_TIM_GET_COUNTER(&htim2) - timeout) > 100) return; // Timeout
        }

        // Marca o início do pulso HIGH
        uint16_t start = __HAL_TIM_GET_COUNTER(&htim2);

        // Aguarda sinal HIGH
        timeout = __HAL_TIM_GET_COUNTER(&htim2);
        while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_SET) {
            if ((__HAL_TIM_GET_COUNTER(&htim2) - timeout) > 100) return; // Timeout
        }

        // Calcula a duração do pulso HIGH
        uint16_t duration = __HAL_TIM_GET_COUNTER(&htim2) - start;
        dados[i] = duration;
    }

    // Decodifica os bits com base nos tempos
    for (int i = 0; i < 40; i++) {
        if (dados[i + 2] > 50) {
            bits[i] = 1;
        } else {
            bits[i] = 0;
        }
    }

    // Converte os bits para temperatura e umidade
    for (int i = 0; i < 8; i++) {
        umidcalc |= (bits[i] << (7 - i));
        tempcalc |= (bits[i + 16] << (7 - i));
    }

    // Retorna os valores calculados
    *temperatura = tempcalc;
    *umidade = umidcalc;
}
