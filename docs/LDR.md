# Leitura e Controle de LDR com PWM no STM32

Este documento descreve como ler os valores de um sensor LDR (Light Dependent Resistor) utilizando o conversor analógico-digital (ADC) do STM32, gerar um sinal PWM proporcional à intensidade da luz e enviar os valores lidos via UART. O código foi desenvolvido para a plataforma STM32, utilizando a biblioteca HAL.

## 1. Visão Geral

O código realiza as seguintes funções:
- Lê o valor do sensor LDR através de um ADC.
- Mapeia o valor lido para um intervalo adequado para controle de PWM.
- Envia o valor lido do ADC pela interface UART.
- Controla a intensidade de um sinal PWM com base na leitura do LDR, permitindo ajustar a luminosidade de um LED ou outro dispositivo com controle de brilho.

## 2. Configuração do STM32CubeMX

Antes de usar o código fornecido, é necessário configurar o STM32CubeMX para garantir que os pinos e periféricos necessários estejam corretamente configurados. Aqui estão os passos para configurar:

### 2.1. Configuração do ADC

1. **Habilitar o ADC**:
   - Acesse a aba de **Peripherals** no STM32CubeMX.
   - Selecione o **ADC1**.
   - Configure o canal que estará sendo usado para o sensor LDR, por exemplo, **Channel 1 (PA1)**.
   - Defina a resolução para 12 bits (4095 valores possíveis) e o modo de conversão.
   
2. **Configuração do Clock**:
   - No **Clock Configuration**, defina o **Prescaler** e o **Clock ADC** para garantir que a taxa de amostragem seja apropriada para a aplicação.

### 2.2. Configuração do PWM

1. **Habilitar o Timer para PWM**:
   - Acesse a aba de **Peripherals** no STM32CubeMX.
   - Habilite o **Timer 1 (TIM1)** para ser usado no modo PWM.
   - Configure o **Prescaler** para **83** para gerar uma frequência de **1 kHz** (arranjo de timer de 999).
   
2. **Configuração do Canal de PWM**:
   - Configure o canal 2 do **Timer 1 (TIM1 Channel 2)** no modo **PWM Generation CH2**.
   - O ciclo de trabalho inicial é definido como 500 (50%) no código, mas ele será ajustado dinamicamente com base na leitura do LDR.

### 2.3. Configuração da UART

1. **Habilitar a UART**:
   - Habilite a **UART2** para comunicação serial.
   - Configure os pinos de TX e RX de acordo com a sua placa, por exemplo, **PA2 (TX)** e **PA3 (RX)**.
   - Defina a taxa de baud, por exemplo, 9600 bps.
   
2. **Configuração do GPIO**:
   - Configure o pino **PA1** (ou o pino que você está utilizando para o LDR) como **Analog Input**.

### 2.4. Configuração Final

- Após configurar os periféricos no STM32CubeMX, gere o código e abra no **STM32CubeIDE** para programar e depurar o código.

## 3. Funções e Explicação Detalhada

### 3.1. Função `Leitura_ADC_PWM`

A função `Leitura_ADC_PWM` realiza a leitura do valor do LDR através do ADC, envia esse valor via UART e ajusta o ciclo de trabalho do PWM com base na leitura.

#### Passos:
1. **Leitura do ADC**:
   - A função `HAL_ADC_Start` inicia a conversão do ADC.
   - A função `HAL_ADC_PollForConversion` aguarda a conversão ser concluída.
   - O valor lido do ADC é obtido com `HAL_ADC_GetValue`.

2. **Processamento do Valor do ADC**:
   - Se o valor lido do ADC for abaixo de 250 (um valor arbitrário para considerar o ambiente como "escuro"), ele é ajustado para 0. Esse valor é usado para melhorar a precisão da leitura, considerando que o sensor pode não ser preciso em ambientes muito escuros.
   
3. **Envio dos Dados via UART**:
   - O valor lido é convertido para string usando `snprintf` e transmitido via UART com a função `HAL_UART_Transmit`.

4. **Mapeamento do ADC para PWM**:
   - O valor do ADC (que varia de 0 a 4095) é mapeado para o intervalo de 0 a 999 (para o controle do PWM).
   - A expressão `(adc_value * 999) / 4095` realiza esse mapeamento.
   
5. **Controle do PWM**:
   - O ciclo de trabalho do PWM é ajustado dinamicamente usando a função `__HAL_TIM_SET_COMPARE`, que modifica o valor de comparação do timer, alterando assim a intensidade do sinal PWM.

### 3.2. Função `PWM_Init`

Esta função configura o **Timer 1 (TIM1)** para operar em modo PWM e inicializa o sinal PWM com uma frequência de 1 kHz.

#### Passos:
1. **Habilitação do Clock**:
   - O clock do **Timer 1 (TIM1)** é habilitado com `__HAL_RCC_TIM1_CLK_ENABLE()`.

2. **Configuração do Timer**:
   - O timer é configurado para uma frequência de 1 kHz, com um **Prescaler** de 83 e **Period** de 999.
   - O **Prescaler** é definido como 83 para garantir que o timer conte até 1000 a cada segundo (considerando um relógio de 84 MHz).

3. **Configuração do PWM**:
   - O modo PWM é configurado com `TIM_OCMODE_PWM1`.
   - O ciclo de trabalho inicial é definido como 500, ou seja, 50% de brilho.

4. **Início do PWM**:
   - O PWM é iniciado com a função `HAL_TIM_PWM_Start`.

## 4. Conclusão

Este código oferece uma solução simples para controle de brilho de LED (ou outro dispositivo controlado por PWM) baseado na intensidade da luz capturada por um sensor LDR. Ele também fornece um método eficiente de monitoramento da intensidade da luz por meio da leitura do ADC e comunicação via UART. A configuração do STM32CubeMX e a implementação do código no STM32CubeIDE facilitam a integração desses componentes em um sistema embarcado.

## 5. Referências

- [Datasheet do Sensor LDR](https://components101.com/sites/default/files/component_datasheet/LDR%20Datasheet.pdf) 

