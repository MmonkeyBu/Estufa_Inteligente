# Controle de Rega Automática no STM32

Este documento descreve como controlar um sistema de rega automática utilizando o STM32, com a biblioteca HAL. O sistema de rega é controlado através de um relé, e o tempo de rega é ajustado dinamicamente através de um menu exibido em uma tela OLED I2C.

## 1. Visão Geral

O código realiza as seguintes funções:
- Configura o timer do STM32 para controlar o relé que ativa e desativa a rega.
- Permite a navegação e seleção de opções de menu utilizando dois botões.
- Exibe a temperatura e umidade atual na tela OLED, com base nos dados fornecidos por um sensor DHT11.
- Permite ajustar o tempo de rega (de 0 a 60 segundos) através do menu.

## 2. Configuração do STM32CubeMX

Antes de usar o código fornecido, é necessário configurar o STM32CubeMX para garantir que os pinos e periféricos necessários estejam corretamente configurados. Aqui estão os passos para configurar:

### 2.1. Configuração do Relé

1. **Configuração do Relé**:
   - O relé será controlado por um pino de GPIO, por exemplo, **PC0**.
   - Configure o pino **PC0** como **GPIO Output** no STM32CubeMX.

### 2.2. Configuração do Timer para Controle do Relé

1. **Habilitar o Timer 10**:
   - Acesse a aba de **Peripherals** no STM32CubeMX.
   - Habilite o **Timer 10** para controlar a ativação e desativação do relé com base no tempo de rega.

2. **Configuração do Clock**:
   - Configure o **Prescaler** e o **Period** do timer para gerar um intervalo adequado de tempo para o controle de rega.

### 2.3. Configuração do Sensor DHT11

1. **Configuração do Pino de Dados**:
   - Configure o pino utilizado para se comunicar com o sensor DHT11, como **PA0** (ou outro pino adequado).
   - O DHT11 envia os dados de temperatura e umidade para o microcontrolador via sinal digital.

### 2.4. Configuração da Tela OLED

1. **Configuração do I2C**:
   - Habilite a interface **I2C** no STM32CubeMX.
   - Configure os pinos de **SCL** e **SDA** (por exemplo, **PB6** e **PB7**, respectivamente) para se comunicar com a tela OLED.

### 2.5. Configuração Final

Após configurar os periféricos no STM32CubeMX, gere o código e abra no **STM32CubeIDE** para programar e depurar o código.

## 3. Funções e Explicação Detalhada

### 3.1. Função `Relay_Start`

Esta função ativa o relé, iniciando o processo de rega.

```c
void Relay_Start(void) {
    printf("Relé Ativado\n");
    HAL_GPIO_WritePin(RELAY_PORT, RELAY_PIN, GPIO_PIN_SET);  // Ativa o relé
    relay_active = 1;
    last_relay_time = HAL_GetTick();  // Armazena o tempo atual
}
```
### 3.2. Navegação do Menu

A navegação do menu é realizada com dois botões: um para navegar entre os itens do menu e outro para selecionar a opção. A função de navegação do menu (`Menu_Navigate`) e de seleção de itens (`Menu_Select`) gerencia o estado do menu e a interação com o usuário.

### 3.2.1. Funcionalidade dos Botões

- **Botão de Navegação** (`NAV_BUTTON_PIN`): Este botão é usado para navegar entre os itens do menu. Quando pressionado, o menu muda para o próximo item. Se o último item for atingido, ele retorna para o primeiro item. Esse botão permite ao usuário percorrer as opções do menu.
  
- **Botão de Seleção** (`SELECT_BUTTON_PIN`): Este botão é utilizado para selecionar a opção do menu atual. Se o item selecionado for uma opção de exibição, como "Temp/Umidade", o sistema exibirá os dados de temperatura e umidade. Se o item selecionado for "Tempo de Regar", permitirá ao usuário ajustar o tempo de rega.

### 3.2.2. Função `Menu_Navigate`

A função `Menu_Navigate` é responsável por navegar entre os itens do menu. Quando o botão de navegação é pressionado, o item selecionado é incrementado, e o sistema exibe a próxima opção do menu. Se o último item for alcançado, a navegação retorna para o primeiro item.

```c
void Menu_Navigate(void) {
    if (menuState == MENU_STATE_MAIN) {
        // Navegar entre os itens do menu
        mainMenu.currentItem++;
        if (mainMenu.currentItem >= mainMenu.numItems) {
            mainMenu.currentItem = 0;
        }
        Menu_Display();
    } else if (menuState == MENU_STATE_ADJUST_REGA_TIME) {
        // Ajusta o tempo de rega enquanto está nessa opção
        rega_time += 10; // Incrementa em 10 segundos
        if (rega_time > 60) {
            rega_time = 0; // Reseta ao passar de 60 segundos
        }
        char buffer[32];
        ssd1306_Fill(Black);
        ssd1306_SetCursor(10, 10);
        snprintf(buffer, sizeof(buffer), "Ajuste: %d seg", rega_time);
        ssd1306_WriteString(buffer, Font_7x10, White);
        ssd1306_UpdateScreen(); // Atualiza a tela com o novo valor
    }
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
