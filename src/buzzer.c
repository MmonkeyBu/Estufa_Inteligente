#include "buzzer.h"

extern TIM_HandleTypeDef htim3; 

void Buzzer_Init(void) {
    // Inicializa o PWM para o buzzer
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
}

void Buzzer_On(void) {
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 1000); // Ajuste conforme necessário
}

void Buzzer_Off(void) {
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);
}

