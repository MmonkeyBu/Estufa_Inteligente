# **Configuração do Sensor DHT11 no STM32**

Este tutorial descreve o processo para configurar o sensor de temperatura e umidade **DHT11** no microcontrolador **STM32** utilizando a **IDE STM32CubeMX**. Ele inclui as configurações necessárias de GPIO e TIM para a leitura dos dados do sensor.

## **1. Configuração do pino GPIO no STM32CubeMX**

1. **Abrir o STM32CubeMX** e criar ou abrir o projeto para o microcontrolador STM32 desejado.
2. **Configuração do Pino GPIO**:
    - O DHT11 utiliza um único pino para comunicação de dados, que deve ser configurado tanto como **saída** (para gerar o pulso de inicialização) quanto como **entrada** (para receber os dados).
    - No exemplo acima, estamos utilizando o **GPIOA_PIN_8**.
    - Configure o pino no modo **GPIO_Output** inicialmente, para gerar o pulso de inicialização.
    - Após o pulso de inicialização, configure o pino como **GPIO_Input** para leitura dos dados do sensor.

## **2. Configuração do Timer**

1. **Adicionar o Timer**:
    - O código utiliza o **TIM2** para medir a duração dos pulsos recebidos do DHT11. No STM32CubeMX, habilite o **Timer 2**.
    - Defina o timer como **Time Base** e escolha um prescaler adequado para medir os tempos dos pulsos em microsegundos.
    - No exemplo, o **TIM2** é utilizado para contar o tempo de duração dos sinais HIGH e LOW durante a comunicação com o sensor.

2. **Configuração do Timer no código**:
    - A função `__HAL_TIM_SET_COUNTER(&htim2, 0)` é usada para resetar o contador do timer e iniciar a captura dos pulsos.
    - Os tempos dos pulsos são lidos utilizando a função `__HAL_TIM_GET_COUNTER(&htim2)`.

# Leitura de Dados do Sensor DHT11

Este documento descreve detalhadamente o funcionamento do código para leitura do sensor **DHT11**, que mede temperatura e umidade, e como o STM32 interage com ele. A comunicação com o DHT11 é feita através de pulsos de alta e baixa tensão, e a troca de dados é realizada por meio de sinais **HIGH** e **LOW**.

## 1. Geração e Leitura dos Pulsos

O sensor **DHT11** utiliza um protocolo de comunicação baseado em pulsos de alta e baixa tensão. O processo de leitura dos dados envolve a troca de sinais entre o microcontrolador (STM32) e o sensor.

### **Pulso de Início (Start Pulse)**

- O STM32 envia um sinal **LOW** (0) por um período de **20 ms** para iniciar a comunicação com o sensor.
- O sensor responde com um sinal **HIGH** (1) por **80 ms**, seguido por um sinal **LOW** (0) por **80 ms**.

### **Leitura dos Dados**

- O sensor envia **40 bits** de dados: 16 bits para **umidade**, 16 bits para **temperatura**, e 8 bits de **verificação**.
- Cada bit é enviado por meio de pulsos **HIGH**, com a duração do pulso determinando o valor do bit:
  - Pulso **HIGH** mais longo (> 50 microsegundos) representa **bit 1**.
  - Pulso **HIGH** mais curto (< 50 microsegundos) representa **bit 0**.

## 2. Função `dht11`

A função `dht11` tem como objetivo ler os dados de temperatura e umidade enviados pelo sensor. A seguir, detalhamos cada parte dessa função.

### **Configuração Inicial do Pino GPIO**

A função `DHT11_SetPinMode` configura o pino GPIO como **saída** para gerar o pulso de início e como **entrada** para ler os sinais de resposta do sensor.

```c
DHT11_SetPinMode(GPIOA, GPIO_PIN_8, GPIO_MODE_OUTPUT_PP);
