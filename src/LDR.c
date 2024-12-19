#include "LDR.h"
#include <stdio.h>
#include "string.h"

extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim1;
extern UART_HandleTypeDef huart2;


void Leitura_ADC_PWM(void) {
    HAL_ADC_Start(&hadc1);
    if (HAL_ADC_PollForConversion(&hadc1, 100) == HAL_OK) {
        uint16_t adc_value = HAL_ADC_GetValue(&hadc1);

        if (adc_value < 250) {  //threshold, pra resolver imprecisão :)
            adc_value = 0;  // Assume que é escuro, ajustando o ADC para o valor mínimo
        }
       char buffer[10];
       snprintf(buffer, sizeof(buffer), "%u\n", adc_value);  // Converte para string

       HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), HAL_MAX_DELAY);
        // Mapeamento do valor do ADC para o intervalo de 0 a 999 (para o PWM)
        uint16_t pwm_value = (adc_value * 999) / 4095;

        // Atualiza o ciclo de trabalho do PWM
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, pwm_value);

    }
}


//sensor LDR
void PWM_Init(void) {
    __HAL_RCC_TIM1_CLK_ENABLE(); // Habilita o clock do TIM1

    TIM_OC_InitTypeDef sConfigOC = {0};

    // Configura o Timer TIM2
    htim1.Instance = TIM1;
    htim1.Init.Prescaler = 83; // 84-1
    htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim1.Init.Period = 999; // ARR = 999 -> Frequência PWM de 1 kHz
    htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(&htim1);

    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 500;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2);

    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
}
