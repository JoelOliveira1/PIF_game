#ifndef FASE_H
#define FASE_H

#include "jogador.h"
#include "mapa.h"
#include "tiro.h"
#include "inimigo.h"
#include "item.h"

int iniciar_fase(int mapa[LINHAS][COLUNAS], Item **itens);

int atualizar_fase(
    Jogador *jogador,
    int mapa[LINHAS][COLUNAS],
    Tiro **tiros,
    Inimigo **inimigos,
    Item **itens
);

void desenhar_fase(void);

#endif