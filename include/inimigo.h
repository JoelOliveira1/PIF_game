#ifndef INIMIGO_H
#define INIMIGO_H

#include "raylib.h"
#include "mapa.h"
#include "tiro.h"

typedef struct Inimigo {
    Vector2 posicao;
    float angulo;
    int vida;
    float tempo_dano;
    struct Inimigo *prox;
} Inimigo;

void gerar_inimigos(Inimigo **lista, int mapa[LINHAS][COLUNAS], int quantidade, Vector2 jogador);

void atualizar_inimigos(Inimigo *lista, int mapa[LINHAS][COLUNAS], Vector2 alvo, float dt);

int atingir_inimigos(Inimigo **inimigos, Tiro **tiros);

void desenhar_inimigos(const Inimigo *lista, Texture2D textura);

void liberar_inimigos(Inimigo **lista);

#endif