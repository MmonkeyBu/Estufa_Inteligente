# buzzer.md

Este documento descreve o processo de configuração do buzzer utilizando PWM no microcontrolador STM32, com base no Timer 3, Canal 2. A configuração é feita no STM32CubeMX, e as funções de controle do buzzer são implementadas no código.

## Passo a Passo para Configuração no STM32CubeMX

### 1. Abrindo o STM32CubeMX

- Abra o STM32CubeMX e crie um novo projeto para o seu microcontrolador STM32 (neste caso, o STM32F446RE).
  
### 2. Habilitando o Timer 3

- No STM32CubeMX, selecione a aba **"Peripherals"** e depois clique em **"Timers"**.
- Habilite o **"TIM3"**, que será utilizado para gerar o sinal PWM.
- Defina o **Mode** como **PWM Generation CH2** (Canal 2).
  
### 3. Configurando o Timer 3

- **Prescaler:** Configure o prescaler do timer para controlar a frequência do PWM. Por exemplo, se você deseja uma frequência de 1 kHz, defina o prescaler para 84 (dependendo do clock do sistema).
- **Auto-reload:** Defina o valor de auto-reload para determinar o ciclo completo do PWM. Para uma frequência de 1 kHz com um clock de 84 MHz, configure o valor de auto-reload como 840.
- **PWM Mode:** Certifique-se de que o modo PWM esteja ativo e que o Timer 3 esteja configurado no **PWM Generation Mode**.

### 4. Configurando o Pino de Saída

- Na aba **"Pinout & Configuration"**, localize o pino que será utilizado para o sinal PWM (geralmente, o pino **PA6** no STM32F446RE para o Canal 2 do Timer 3).
- Configure este pino para **TIM3_CH2** (o Canal 2 do Timer 3).

### 5. Configurando a Interrupt (se necessário)

- Caso deseje utilizar interrupções, habilite a interrupção do Timer 3 na aba **NVIC**.

### 6. Gerando o Código

- Após todas as configurações, clique em **"Project"** e defina o nome do projeto.
- Clique em **"Generate Code"** para gerar o código de inicialização automaticamente no STM32CubeIDE.

## Passo a Passo para Implementação no Código

### 1. Iniciando o PWM

A função `Buzzer_Init` é responsável por iniciar o PWM para controlar o buzzer. Aqui, usamos a função `HAL_TIM_PWM_Start` para ativar o PWM do Timer 3, Canal 2.

```c
void Buzzer_Init(void) {
    // Inicializa o PWM para o buzzer
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
}
```
## 7. Referências

- [Datasheet do SG90s](https://www.farnell.com/datasheets/2171929.pdf) 


