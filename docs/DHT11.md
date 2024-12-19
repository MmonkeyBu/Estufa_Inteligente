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

## **3. Código para Leitura dos Dados do Sensor**

O código de leitura do sensor **DHT11** envolve a troca de sinais entre o microcontrolador e o sensor para coletar os dados de temperatura e umidade.

### Passos principais:

1. **Configuração Inicial do Pino GPIO**:
    - O pino GPIO que conecta o sensor é configurado como saída para gerar o pulso de inicialização.
    - O pino é então configurado como entrada para ler os dados de resposta do sensor.

2. **Geração do Pulso de Início**:
    - O pino é definido como LOW por 20 ms, depois é definido como HIGH, e após isso, o pino é configurado como entrada.

3. **Leitura dos Dados**:
    - Utilizando o timer **TIM2**, o código monitora os pulsos HIGH e LOW para calcular os valores binários enviados pelo sensor.
    - A duração de cada pulso é medida e, com base nisso, os valores de temperatura e umidade são extraídos.

4. **Decodificação dos Dados**:
    - O código converte os sinais recebidos em bits, e a sequência de bits é convertida para os valores de temperatura e umidade.

## **Conclusão**

Este tutorial mostra como configurar o sensor **DHT11** para medir temperatura e umidade utilizando o STM32. Ele cobre as configurações de pinos GPIO e timers no **STM32CubeMX** e apresenta a estrutura de código necessária para integrar o sensor ao microcontrolador.

Essa configuração permite capturar os dados de temperatura e umidade de forma precisa, utilizando o **TIM2** para medir a duração dos pulsos e calcular os valores a partir dos dados recebidos.

---
