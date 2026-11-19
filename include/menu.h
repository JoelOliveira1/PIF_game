#ifndef MENU_H
#define MENU_H

#include "raylib.h"

typedef enum {
    MENU,
    JOGANDO,
    RANKING
} EstadoJogo;

void desenhar_menu(int jogo_em_andamento);
int atualizar_menu(int jogo_em_andamento);

void desenhar_ranking(void);
int atualizar_ranking(void);

#endif