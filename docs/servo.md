# Controle de Servo Motor com PWM no STM32

Este documento descreve como controlar a posição de um servo motor utilizando PWM no **STM32**, com a biblioteca HAL. O servo motor é controlado através de um sinal PWM de frequência constante, e a posição do servo é ajustada com base na largura do pulso do PWM.

## 1. Visão Geral

O código realiza as seguintes funções:
- Configura o timer do STM32 para gerar um sinal PWM de 50 Hz.
- Converte um valor de ângulo (0° a 180°) em um valor de ciclo de trabalho PWM.
- Ajusta o ciclo de trabalho do PWM para controlar a posição do servo motor.
- Usa o Timer 3 e o canal 1 para gerar o sinal PWM que é enviado ao servo motor.

## 2. Configuração do STM32CubeMX

Antes de usar o código fornecido, é necessário configurar o STM32CubeMX para garantir que os pinos e periféricos necessários estejam corretamente configurados. Aqui estão os passos para configurar:

### 2.1. Configuração do Timer para PWM

1. **Habilitar o Timer 3**:
   - Acesse a aba de **Peripherals** no STM32CubeMX.
   - Habilite o **Timer 3** e configure o **modo PWM** para gerar um sinal com uma frequência de 50 Hz, que é a frequência padrão utilizada para controlar servos.

2. **Configuração do Clock**:
   - Configure o **Prescaler** e o **Period** do timer de forma a gerar uma frequência de 50 Hz.
     - Exemplo: Com um **prescaler de 83**, o período seria ajustado para 999 para gerar uma frequência de 50 Hz (1 ciclo a cada 20 ms).

3. **Configuração do Canal PWM**:
   - Configure o **canal 1 do Timer 3** para o **modo PWM**.
   - Defina o ciclo de trabalho inicial (largura do pulso), que será ajustado com base no valor do ângulo desejado.

### 2.2. Configuração do Pino de Controle do Servo

1. **Configuração do Pino**:
   - Configure o pino que será utilizado para gerar o sinal PWM, por exemplo, **PA6** (ou outro pino adequado para o seu modelo de STM32).
   - O pino deve ser configurado como **Alternate Function (AF)** para o **Timer 3**.

### 2.3. Configuração Final

Após configurar os periféricos no STM32CubeMX, gere o código e abra no **STM32CubeIDE** para programar e depurar o código.

## 3. Funções e Explicação Detalhada

### 3.1. Função `Servo_Init`

Esta função inicializa o Timer 3 para gerar o sinal PWM necessário para controlar o servo motor.

```c
void Servo_Init(void) {
    // Inicializa o PWM para o servo
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
}
## 4. Referências

- [Datasheet do SG90s](http://www.ee.ic.ac.uk/pcheung/teaching/DE1_EE/stores/sg90_datasheet.pdf) 
