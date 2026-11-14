#ifndef MENU_H
#define MENU_H

#include "raylib.h"

typedef enum {
    MENU,
    JOGANDO,
    RANKING
} EstadoJogo;

void desenhar_menu(void);
int atualizar_menu(void);

void desenhar_ranking(void);
int atualizar_ranking(void);

#endif