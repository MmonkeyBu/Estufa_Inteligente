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
1. 🔊 [**Buzzer (`buzzer.c`)**](docs/buzzer.md) - Controle de som para alertas.
2. 🌡️ [**DHT11 (`DHT11.c`)**](docs/DHT11.md) - Leitura de temperatura e umidade.
3. 📏 [**HC-SR04 (`HCSR04.c`)**](docs/HCSR04.md) - Leitura de distância por ultrassom.
4. 💡 [**LDR (`LDR.c`)**](docs/LDR.md) - Monitoramento de luminosidade.
5. 📟 [**Menu (`menu.c`)**](docs/menu.md) - Interface de navegação no display OLED.
6. 🛠️ [**Servo (`servo.c`)**](docs/servo.md) - Controle de um servo motor.
7. 🧠 [**Principal (`main.c`)**](docs/main.md) - Integração dos módulos.

---

## 📜 Licença
Este projeto é licenciado sob a [MIT License](https://opensource.org/licenses/MIT).
****
