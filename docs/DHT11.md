# Leitura de Temperatura e Umidade com DHT11 no STM32

Este documento descreve como configurar e ler os dados de um sensor **DHT11** utilizando um STM32, com a ajuda da biblioteca HAL. O sensor DHT11 fornece medições de temperatura e umidade, que podem ser usadas em uma variedade de aplicações.

## 1. Visão Geral

O código realiza as seguintes funções:
- Configura o pino GPIO do STM32 para comunicação com o sensor DHT11.
- Envia um sinal de inicialização ao sensor e lê os pulsos de resposta para extrair os dados.
- Converte os pulsos de resposta em valores digitais de temperatura e umidade.
- Utiliza um temporizador para medir a duração dos pulsos de resposta do sensor.

### **Pulso de Início (Start Pulse)**

- O STM32 envia um sinal **LOW** (0) por um período de **20 ms** para iniciar a comunicação com o sensor.
- O sensor responde com um sinal **HIGH** (1) por **80 ms**, seguido por um sinal **LOW** (0) por **80 ms**.

### **Leitura dos Dados**

- O sensor envia **40 bits** de dados: 16 bits para **umidade**, 16 bits para **temperatura**, e 8 bits de **verificação**.
- Cada bit é enviado por meio de pulsos **HIGH**, com a duração do pulso determinando o valor do bit:
  - Pulso **HIGH** mais longo (> 50 microsegundos) representa **bit 1**.
  - Pulso **HIGH** mais curto (< 50 microsegundos) representa **bit 0**.

## 2. Configuração do STM32CubeMX

Antes de utilizar o código fornecido, é necessário configurar o STM32CubeMX para garantir que o pino correto do GPIO e o temporizador (Timer 2) estejam configurados adequadamente. Aqui estão os passos:

### 2.1. Configuração do Pino de Comunicação com o DHT11

1. **Habilitar o pino GPIO**:
   - Acesse a aba de **Peripherals** no STM32CubeMX.
   - Configure o pino GPIO **PA8** (ou outro pino de sua escolha) como **GPIO_MODE_OUTPUT_PP** para comunicação com o sensor.

2. **Configuração do Timer**:
   - Habilite o **Timer 2** e configure-o para medir os pulsos de resposta do DHT11.
   - Configure o timer para uma resolução de tempo adequada para medir os pulsos.

### 2.2. Configuração do Timer para Medição de Pulsos

1. **Habilitar o Timer 2**:
   - Acesse a aba de **Timers** no STM32CubeMX.
   - Configure o **Timer 2** para medir os tempos de duração dos pulsos HIGH e LOW durante a comunicação com o sensor.

2. **Configuração de Clock**:
   - Ajuste os parâmetros de clock do timer para garantir que os pulsos possam ser medidos com precisão.

Após configurar os periféricos no STM32CubeMX, gere o código e abra no **STM32CubeIDE** para programar e depurar o código.

## 3. Funções e Explicação Detalhada

### 3.1. Função `DHT11_SetPinMode`

Esta função configura o pino GPIO para o modo desejado, como **saída** ou **entrada**.

```c
void DHT11_SetPinMode(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint32_t Mode) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_Pin;
    GPIO_InitStruct.Mode = Mode;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}
```
1. **Configuração de Pinos GPIO:**
   - Selecione os pinos conectados aos botões, por exemplo, `Botton_1_Pin` e `Botton_2_Pin`.
   - Configure os pinos como **GPIO_EXTI** no modo de entrada.

2. **Habilitação das Interrupções:**
   - Vá até a aba de interrupções e habilite as linhas EXTI correspondentes aos pinos (ex.: `EXTI15_10`).

3. **Gerar Código:**
   - Clique em `Project -> Generate Code` e abra o projeto no STM32CubeIDE.

### 2. Implementação no Código
No arquivo `stm32f4xx_it.c`, configure os callbacks para as interrupções:

#### Declaração de Variáveis e Definições
No início do arquivo, declare variáveis para controle de debounce:

```c
static uint32_t last_debounce_time_nav = 0;
static uint32_t last_debounce_time_select = 0;
#define DEBOUNCE_DELAY 50 // 50 ms debounce delay
```

#### Callback para GPIO (Botões)
Implemente o callback para capturar os eventos de interrupção:

```c
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == Botton_2_Pin) {
        uint32_t current_time = HAL_GetTick();
        if ((current_time - last_debounce_time_nav) > DEBOUNCE_DELAY) {
            last_debounce_time_nav = current_time;
            Menu_Navigate(); // Função que implementa a navegação do menu
        }
    } else if (GPIO_Pin == Botton_1_Pin) {
        uint32_t current_time = HAL_GetTick();
        if ((current_time - last_debounce_time_select) > DEBOUNCE_DELAY) {
            last_debounce_time_select = current_time;
            Menu_Select(); // Função que implementa a seleção no menu
        }
    }
}
```

#### Configuração de Interrupção de Timer (Opcional)
No caso de usar um Timer para leituras periódicas de sensores, como no exemplo com o DHT11:

```c
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM10) {
        if (reading_active) {
            dht11(&tempdht11, &umidht11); // Função que lê dados do sensor DHT11
        }
    }
}
```


## 4. Referências

- [Datasheet do DHT11](https://www.mouser.com/datasheet/2/758/DHT11-Technical-Data-Sheet-Translated-Version-1143054.pdf) 
