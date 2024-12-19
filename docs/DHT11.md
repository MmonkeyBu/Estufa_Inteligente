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
