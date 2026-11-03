#ifndef MAPA_H
#define MAPA_H
#include "raylib.h"

#define TAMANHO 32
#define COLUNAS 40
#define LINHAS 22

#define LARGURA_TELA (COLUNAS * TAMANHO)
#define ALTURA_TELA (LINHAS * TAMANHO)
#define CHAO 0
#define PAREDE 1

int carregar_mapa(int mapa[LINHAS][COLUNAS], const char *arquivo);
void desenhar_mapa(int mapa[LINHAS][COLUNAS]);
int colide_parede(int mapa[LINHAS][COLUNAS], Rectangle area);

#endif