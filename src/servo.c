#include "servo.h"

extern TIM_HandleTypeDef htim3; // Supondo que o servo esteja no Timer 3, ajuste conforme necessário

void Servo_Init(void) {
    // Inicializa o PWM para o servo
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
}

void Servo_SetAngle(uint8_t angle) {
    // Converte o ângulo para o valor do ciclo de trabalho do PWM
    uint16_t pulse_length = (500 + (angle * 2000) / 180); // Ajuste conforme necessário
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, pulse_length);
}

