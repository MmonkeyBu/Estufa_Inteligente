#include "HCSR04.h"
#include "stm32f4xx_hal.h"
#include <stdio.h>
#include <string.h>

extern TIM_HandleTypeDef htim2; // Timer configurado externamente
extern UART_HandleTypeDef huart2;

// Inicializa os pinos TRIG e ECHO
void HCSR04_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Habilita o clock da porta GPIOA
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // Configura o pino TRIG como saída push-pull
    GPIO_InitStruct.Pin = TRIG_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(TRIG_PORT, &GPIO_InitStruct);

    // Configura o pino ECHO como entrada
    GPIO_InitStruct.Pin = ECHO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(ECHO_PORT, &GPIO_InitStruct);

    // Inicia o Timer
    HAL_TIM_Base_Start(&htim2);
}

// Lê a distância usando o sensor HC-SR04
uint32_t HCSR04_ReadDistance(void) {
    uint32_t start_time = 0, end_time = 0;

    // Gera um pulso de 10 µs no TRIG
    HAL_GPIO_WritePin(TRIG_PORT, TRIG_PIN, GPIO_PIN_RESET);
    HAL_Delay(2);
    HAL_GPIO_WritePin(TRIG_PORT, TRIG_PIN, GPIO_PIN_SET);
    __HAL_TIM_SET_COUNTER(&htim2, 0); // Zera o contador
    HAL_Delay(1);  // Pulso de 10 µs
    HAL_GPIO_WritePin(TRIG_PORT, TRIG_PIN, GPIO_PIN_RESET);

    // Aguarda o ECHO subir
    while (HAL_GPIO_ReadPin(ECHO_PORT, ECHO_PIN) == GPIO_PIN_RESET);

    // Inicia a medição do tempo
    start_time = __HAL_TIM_GET_COUNTER(&htim2);

    // Aguarda o ECHO descer
    while (HAL_GPIO_ReadPin(ECHO_PORT, ECHO_PIN) == GPIO_PIN_SET);

    // Captura o tempo de descida
    end_time = __HAL_TIM_GET_COUNTER(&htim2);

    // Calcula a duração do pulso (tempo em µs)
    uint32_t pulse_duration = end_time - start_time;

    // Calcula a distância em centímetros (tempo em µs / 58)
    uint32_t distance_cm = pulse_duration / 58;

    // Transmite a distância via UART
    char buffer[30];
    snprintf(buffer, sizeof(buffer), "Distancia: %lu cm\n", distance_cm);
    HAL_UART_Transmit(&huart2, (uint8_t *)buffer, strlen(buffer), HAL_MAX_DELAY);

    // Retorna a distância
    return distance_cm;
}
