#ifndef FASE_H
#define FASE_H

#include "jogador.h"
#include "mapa.h"
#include "tiro.h"
#include "inimigo.h"

int iniciar_fase(int mapa[LINHAS][COLUNAS]);

int atualizar_fase(
    Jogador *jogador,
    int mapa[LINHAS][COLUNAS],
    Tiro **tiros,
    Inimigo **inimigos
);

void desenhar_fase(void);

#endif