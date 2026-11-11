#ifndef TIRO_H
#define TIRO_H

#include "raylib.h"
#include "mapa.h"

typedef struct Tiro {
    Vector2 posicao;
    Vector2 direcao;
    float velocidade;
    struct Tiro *prox;
} Tiro;

int criar_tiro(Tiro **lista, Vector2 origem, Vector2 alvo);

void atualizar_tiros(Tiro **lista, int mapa[LINHAS][COLUNAS], float dt);

void desenhar_tiros(const Tiro *lista);

void liberar_tiros(Tiro **lista);

#endif