#ifndef JOGADOR_H
#define JOGADOR_H
#include "raylib.h"
#include "mapa.h"

typedef struct {
    Vector2 posicao;
    float tamanho;
    float velocidade;
} Jogador;

void iniciar_jogador(Jogador *jogador, float x, float y);
void atualizar_jogador(Jogador *jogador, int mapa[LINHAS][COLUNAS], float dt);
void desenhar_jogador(const Jogador *jogador);
Vector2 centro_do_jogador(const Jogador *jogador);

#endif