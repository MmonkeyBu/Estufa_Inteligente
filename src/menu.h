#ifndef MENU_H
#define MENU_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"

void Menu_Init(void);
void Menu_Navigate(void);
void Menu_Select(void);
void Menu_Display(void);
void Relay_Interval(void);
void Menu_HandleButtons(void); // Adicione esta linha

void ativar_rele(void);
void Relay_Start(void);
void Relay_Stop(void);
#ifdef __cplusplus
}
#endif

#endif /* MENU_H */
