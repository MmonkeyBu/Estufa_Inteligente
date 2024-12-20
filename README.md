# 🌱 STM32 Estufa Inteligente

Este repositório contém o código-fonte e a documentação do sistema automatizado baseado na STM32F446RE.

## 🌟 Visão Geral
O projeto implementa sensores:
- 📏 **HC-SR04**: Sensor ultrassônico para medir distâncias.
- 🌡️ **DHT11**: Sensor para leitura de temperatura e umidade.
- 💡 **LDR**: Sensor para monitoramento da luminosidade.

O projeto implementa os atuadores:
- 🛠️ **Servo Motor**: Utilizado para controle mecânico.
- 📟 **Painel OLED I2C**: Interface para exibição de informações (biblioteca utilizada mencionada abaixo).
- 🔊 **Buzzer**: Emissor de alertas sonoros.

---

### 📂 Conteúdo
- **`src/`**: Código-fonte do projeto (arquivos `.c` e `.h`).(caso você procure apenas os perifericos e função main, ignore os arquivos iniciados em sys e stm32)
  - Os arquivos `.h` contêm as definições de funções e constantes usadas em seus respectivos módulos.
- **`docs/`**: Imagens e documentação sobre configurações no STM32CubeMX.

---

## 📜 Módulos
1. 🔊 [**Buzzer (`buzzer.c`)**](src/buzzer.c) - Controle de som para alertas.
2. 🌡️ [**DHT11 (`DHT11.c`)**](src/DHT11.c) - Leitura de temperatura e umidade.
3. 📏 [**HC-SR04 (`HCSR04.c`)**](src/HCSR04.c) - Leitura de distância por ultrassom.
4. 💡 [**LDR (`LDR.c`)**](src/LDR.c) - Monitoramento de luminosidade.
5. 📟 [**Menu (`menu.c`)**](src/menu.c) - Interface de navegação no display OLED.
6. 🛠️ [**Servo (`servo.c`)**](src/servo.c) - Controle de um servo motor.
7. 🧠 [**Principal (`main.c`)**](src/main.c) - Integração dos módulos.

---

## 📜 Licença
Este projeto é licenciado sob a [MIT License](https://opensource.org/licenses/MIT).
****
