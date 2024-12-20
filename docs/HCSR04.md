# Leitura de Distância com o Sensor HC-SR04

Este documento descreve detalhadamente o funcionamento do código para leitura de distância utilizando o sensor **HC-SR04**, que mede a distância com base no tempo de voo de um pulso ultrassônico. A comunicação com o sensor é realizada através dos pinos **TRIG** e **ECHO**.

## 1. Funcionamento do Sensor HC-SR04

O **HC-SR04** é um sensor de distância ultrassônico que funciona medindo o tempo que um pulso de som leva para ir até um objeto e retornar. A operação do sensor envolve dois pinos principais: **TRIG** e **ECHO**.

### **Pino TRIG**
- O pino **TRIG** é utilizado para gerar um pulso ultrassônico. Quando o microcontrolador envia um sinal **HIGH** no pino **TRIG**, o sensor gera um pulso ultrassônico.

### **Pino ECHO**
- O pino **ECHO** detecta o pulso refletido pelo objeto. Quando o pulso ultrassônico atinge um objeto, ele é refletido e retorna ao sensor, fazendo com que o pino **ECHO** fique **HIGH** durante o tempo que o som leva para retornar.

O cálculo da distância é feito com base no tempo entre o início e o fim do sinal **ECHO**. O tempo de retorno do pulso é dividido por 58 para obter a distância em centímetros.

## 2. Como Configurar no STM32CubeMX

Para configurar o sensor **HC-SR04** no **STM32CubeMX**, siga os passos abaixo:

### **Passo 1: Configuração dos Pinos**

1. Abra o **STM32CubeMX** e crie um novo projeto para o seu microcontrolador.
2. No painel de configuração de **Pinout & Configuration**, atribua os pinos:
   - **TRIG_PIN** como **GPIO_Output**.
   - **ECHO_PIN** como **GPIO_Input**.
3. Certifique-se de habilitar o **Timer** necessário para medir o tempo do pulso (normalmente **TIM2** ou outro timer disponível).

### **Passo 2: Configuração do Timer**

Para medir o tempo com precisão, o timer precisa ser configurado no **STM32CubeMX**. O **prescaler** e a **frequência do timer** são essenciais para garantir que o tempo medido seja em **microsegundos**.

1. **Prescaler**: O **prescaler** define o divisor do clock do timer. Por exemplo, se o **prescaler** for 16 e a frequência do timer for 1 MHz (1 µs por contagem), o timer contará a cada 16 ciclos do clock do sistema. O **prescaler** ajusta a resolução do timer, ou seja, a precisão do tempo que o microcontrolador pode medir. Para medir o tempo de voo do pulso ultrassônico em microsegundos, o **prescaler** deve ser configurado adequadamente.
   
   **Exemplo**:
   - Se o sistema está rodando a 72 MHz e o **prescaler** é 72, o timer terá uma resolução de 1 µs, ou seja, cada contagem do timer corresponderá a 1 microsegundo.

2. **Contador do Timer**: O timer começa a contar a partir de 0 quando o pino **TRIG** gera o pulso, e o valor do contador é lido quando o pino **ECHO** retorna ao **LOW**.

3. No painel de configuração de **Peripherals**, habilite o **Timer** desejado (por exemplo, **TIM2**).
4. Configure o **Timer** para ser utilizado em **modo de contagem básica**, sem interrupção, apenas para contar o tempo de pulso.

### **Passo 3: Configuração da UART (opcional)**

Se você deseja enviar os dados via UART para um terminal, habilite a **UART** no **STM32CubeMX**:
1. Atribua os pinos de **TX** e **RX** para comunicação serial.
2. Configure a **UART** para uma velocidade de transmissão adequada (exemplo: 115200 bps).

### **Passo 4: Geração do Código**

Após configurar os pinos e periféricos necessários, clique em "Project" e gere o código para sua IDE (por exemplo, **STM32CubeIDE**).

## 3. Código para Leitura de Distância

O código a seguir configura os pinos **TRIG** e **ECHO**, gera o pulso ultrassônico e calcula a distância com base no tempo de voo do sinal. Além disso, o código utiliza um **Timer** para medir o tempo entre o sinal **ECHO** ficar **HIGH** e **LOW**.

### **Configuração dos Pinos**

Primeiramente, os pinos **TRIG** e **ECHO** são configurados. O pino **TRIG** é configurado como **saída** para gerar o pulso, enquanto o pino **ECHO** é configurado como **entrada** para capturar a resposta do sensor.

```c
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
```
## 4. Referências

- [Datasheet do HCSR04](https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf) 
