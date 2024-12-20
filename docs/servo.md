# Controle de Servo Motor

Este documento descreve o funcionamento do código para controlar um servo motor utilizando PWM no STM32, incluindo a configuração do timer, o controle do ângulo do servo e a explicação de como o PWM é gerado para controlar o movimento do servo motor.

## 1. Configuração do PWM

Para controlar um servo motor, é necessário gerar um sinal PWM (modulação por largura de pulso) com um ciclo de trabalho variável, o que fará o servo motor se mover para diferentes posições.

### **Inicialização do PWM**

O código começa com a inicialização do PWM utilizando o **Timer 3** e o **canal 1**. A função `Servo_Init` é responsável por configurar o PWM para o servo motor:

```c
void Servo_Init(void) {
    // Inicializa o PWM para o servo
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
}
