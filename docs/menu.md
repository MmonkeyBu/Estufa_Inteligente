# Controle de Relé e Menu com STM32

Este documento descreve como controlar um relé e um menu utilizando um display OLED e botões no **STM32**. Utiliza a biblioteca HAL e bibliotecas específicas para o display OLED.

## 1. Visão Geral

O código realiza as seguintes funções:
- Controla o estado de um relé.
- Navega e seleciona opções de um menu exibido em um display OLED.
- Usa os botões para navegação e seleção de opções.
- Exibe informações de temperatura e umidade lidas de um sensor DHT11.

## 2. Configuração de Hardware e Bibliotecas

### 2.1. Pinos e Periféricos Utilizados

- **Relé**: Pino **PC0**
- **Botão de Navegação**: Pino **PB12**
- **Botão de Seleção**: Pino **PB13**
- **Display OLED**: Utiliza a biblioteca `ssd1306`.
- **Sensor DHT11**: Sensores de temperatura e umidade.

### 2.2. Configuração do STM32CubeMX

Para garantir que os periféricos necessários estejam configurados corretamente, siga os seguintes passos no STM32CubeMX:

#### 2.2.1. Configuração dos Pinos

1. **Relé (PC0)**:
   - Configure o pino **PC0** como **Output** no modo **GPIO_Output**.

2. **Botão de Navegação (PB12)**:
   - Configure o pino **PB12** como **Input** no modo **GPIO_Input**.

3. **Botão de Seleção (PB13)**:
   - Configure o pino **PB13** como **Input** no modo **GPIO_Input**.

4. **Display OLED (I2C)**:
   - Habilite o periférico **I2C** correspondente.
   - Configure os pinos **SCL** e **SDA** de acordo com o seu hardware específico.

#### 2.2.2. Configuração do Clock

- Configure o **prescaler** e o **clock source** para garantir que o sistema esteja operando na frequência desejada.

#### 2.2.3. Configuração Adicional

- Certifique-se de que as interrupções necessárias estejam habilitadas para os botões, caso estejam utilizando um método baseado em interrupção.

## 3. Explicação das Funções

### 3.1. Funções de Controle do Relé

#### Função `Relay_Start`

Ativa o relé e armazena o tempo de início da ativação.

```c
void Relay_Start(void) {
    printf("Relé Ativado\n");
    HAL_GPIO_WritePin(RELAY_PORT, RELAY_PIN, GPIO_PIN_SET);  // Ativa o relé
    relay_active = 1;
    last_relay_time = HAL_GetTick();  // Armazena o tempo atual
}
