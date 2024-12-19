# Controle de Buzzer com PWM

Este módulo controla um buzzer utilizando PWM no microcontrolador STM32. O código utiliza o Timer 3, Canal 2 para gerar o sinal PWM, que é usado para ligar e desligar o buzzer com intensidade ajustável.

# Configuração do Timer 3 (TIM3) e Canal 2 para Controle de Buzzer

No projeto **Estufa Inteligente**, o buzzer é controlado por um sinal PWM gerado pelo Timer 3 (TIM3), Canal 2. A seguir, estão os passos necessários para configurar o TIM3 no CubeMX e os detalhes sobre o código gerado.

## 1. Configuração do Timer 3 (TIM3) no CubeMX

### Passos:
1. **Abrir o CubeMX**:
   - Inicie o STM32CubeMX e abra seu projeto existente.

2. **Configurar o Timer 3**:
   - Vá até a aba **Pinout & Configuration** e localize o **TIM3**.
   - Configure o **PWM Generation CH2** para o Canal 2 do TIM3.

3. **Configuração do GPIO para o PWM**:
   - Identifique o pino associado ao **TIM3 Channel 2** (geralmente `PA7` ou `PB5`).
   - No painel **Pinout & Configuration**, configure o pino como **PWM Generation Output**.

4. **Configuração do Timer**:
   - Vá para a aba **Configuration** e selecione **TIM3**.
   - Ajuste os parâmetros do timer, como **Prescaler** e **Auto-Reload Register (ARR)**. Para gerar um sinal PWM de 1 kHz com o sistema a 72 MHz, configure o **Prescaler** para 71 e o **ARR** para 999.
     - A frequência do PWM é calculada pela fórmula:
       \[
       f_{\text{PWM}} = \frac{f_{\text{Timer}}}{(Prescaler + 1) \times (ARR + 1)}
       \]
     - Onde `f_Timer` é a frequência do timer (geralmente igual ao clock do sistema).

5. **Gerar o Código**:
   - Após configurar o timer, clique em **Project** e depois em **Generate Code** para gerar o código de inicialização do CubeMX.
