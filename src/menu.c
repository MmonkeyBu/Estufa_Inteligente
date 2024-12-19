#include "menu.h"
#include "ssd1306.h" // Biblioteca da tela OLED
#include "ssd1306_fonts.h"
#include "DHT11.h"
#include <stdio.h>
#include <main.h>

#define NAV_BUTTON_PIN GPIO_PIN_12
#define SELECT_BUTTON_PIN GPIO_PIN_13
#define BUTTON_PORT GPIOB
#define RELAY_PIN GPIO_PIN_0
#define RELAY_PORT GPIOC

extern TIM_HandleTypeDef htim10;

uint16_t rega_time = 0; // Tempo de rega em segundos
uint8_t relay_active = 0; // Estado do relé
uint32_t relay_start_time = 0; // Tempo de início da rega
uint32_t last_relay_time = 0;
// Protótipos de todas as funções usadas
void Relay_Start(void);
void Relay_Stop(void);
void Relay_Interval(void);
void Menu_Display(void);
void Menu_Navigate(void);
void Menu_Select(void);
void Menu_HandleButtons(void);

// Estrutura para armazenar o estado do menu
typedef struct {
    uint8_t currentItem;
    uint8_t numItems;
    char **items;
} Menu;

typedef enum {
    MENU_STATE_MAIN,
    MENU_STATE_SELECTED,
    MENU_STATE_ADJUST_REGA_TIME
} MenuState;

MenuState menuState;

uint8_t reading_active = 0;

Menu mainMenu;

// Funções de controle do relé
void Relay_Start(void) {
    printf("Relé Ativado\n");
    HAL_GPIO_WritePin(RELAY_PORT, RELAY_PIN, GPIO_PIN_SET);  // Ativa o relé
    relay_active = 1;
    last_relay_time = HAL_GetTick();  // Armazena o tempo atual
}

void Relay_Stop(void) {
    printf("Relé Desativado\n");
    HAL_GPIO_WritePin(RELAY_PORT, RELAY_PIN, GPIO_PIN_RESET);  // Desativa o relé
    relay_active = 0;
}

void Relay_Interval(void) {
    if (!relay_active) {
        uint32_t current_time = HAL_GetTick();
        uint32_t elapsed_time = (current_time - last_relay_time) / 1000; // Tempo passado em segundos

        // Ativa o relé a cada "rega_time" segundos por 2 segundos
        if (elapsed_time >= rega_time) {
            Relay_Start();  // Ativa o relé
        }
    } else {
        uint32_t current_time = HAL_GetTick();
        uint32_t elapsed_time = (current_time - last_relay_time) / 1000;  // Tempo passado desde que o relé foi ativado

        // Desativa o relé após 2 segundos de ativação
        if (elapsed_time >= 2) {
            Relay_Stop();  // Desativa o relé
        }
    }
}
// Funçoes do controle do menu
void Menu_Init(void) {
    menuState = MENU_STATE_MAIN;

    static char *menuItems[] = {
        "Temp/Umidade",
        "Tempo de Regar"
    };

    mainMenu.currentItem = 0;
    mainMenu.numItems = sizeof(menuItems) / sizeof(menuItems[0]);
    mainMenu.items = menuItems;

    ssd1306_Init();
    Menu_Display();
}

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

void Menu_Select(void) {
    if (menuState == MENU_STATE_MAIN) {
        if (mainMenu.currentItem == 0) {
            // Exibe Temp/Umid
            menuState = MENU_STATE_SELECTED;
            char buffer[32];
            ssd1306_Fill(Black);
            ssd1306_SetCursor(10, 10);
            snprintf(buffer, sizeof(buffer), "Temp: %dC", tempdht11);
            ssd1306_WriteString(buffer, Font_7x10, White);
            ssd1306_SetCursor(10, 25);
            snprintf(buffer, sizeof(buffer), "Umid: %d%%", umidht11);
            ssd1306_WriteString(buffer, Font_7x10, White);
            ssd1306_UpdateScreen();
        } else if (mainMenu.currentItem == 1) {
            // Ajusta tempo de rega
            menuState = MENU_STATE_ADJUST_REGA_TIME;
            char buffer[32];
            ssd1306_Fill(Black);
            ssd1306_SetCursor(10, 10);
            snprintf(buffer, sizeof(buffer), "Ajuste: %d seg", rega_time);
            ssd1306_WriteString(buffer, Font_7x10, White);
            ssd1306_UpdateScreen();
        }
    } else if (menuState == MENU_STATE_ADJUST_REGA_TIME) {
        // Salva automaticamente o tempo de rega e volta para o menu principal
        menuState = MENU_STATE_MAIN;  // Volta para o menu principal
        Menu_Display(); // Atualiza a tela para o menu principal
    } else if (menuState == MENU_STATE_SELECTED) {
        // Voltar ao menu principal a partir da tela de Temp/Umidade
        menuState = MENU_STATE_MAIN;
        Menu_Display();
    }
}

void Menu_Display(void) {
    ssd1306_Fill(Black);
    for (uint8_t i = 0; i < mainMenu.numItems; i++) {
        ssd1306_SetCursor(10, 10 + (i * 10));
        if (i == mainMenu.currentItem) {
            ssd1306_WriteString("-> ", Font_7x10, White);
        }
        ssd1306_WriteString(mainMenu.items[i], Font_7x10, White);
    }
    ssd1306_UpdateScreen();
}

void Menu_HandleButtons(void) {
    if (HAL_GPIO_ReadPin(BUTTON_PORT, NAV_BUTTON_PIN) == GPIO_PIN_RESET) {
        HAL_Delay(50); // Debounce
        if (HAL_GPIO_ReadPin(BUTTON_PORT, NAV_BUTTON_PIN) == GPIO_PIN_RESET) {
            Menu_Navigate();
            while (HAL_GPIO_ReadPin(BUTTON_PORT, NAV_BUTTON_PIN) == GPIO_PIN_RESET);
        }
    }

    if (HAL_GPIO_ReadPin(BUTTON_PORT, SELECT_BUTTON_PIN) == GPIO_PIN_RESET) {
        HAL_Delay(50); // Debounce
        if (HAL_GPIO_ReadPin(BUTTON_PORT, SELECT_BUTTON_PIN) == GPIO_PIN_RESET) {
            Menu_Select();
            while (HAL_GPIO_ReadPin(BUTTON_PORT, SELECT_BUTTON_PIN) == GPIO_PIN_RESET);
        }
    }
}
