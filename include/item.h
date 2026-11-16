#ifndef ITEM_H
#define ITEM_H

#include "raylib.h"
#include "mapa.h"
#include "jogador.h"

typedef enum{
    ITEM_VIDA,
    ITEM_MUNICAO
} TipoItem;

typedef struct Item{
    Vector2 posicao;
    TipoItem tipo;
    struct Item *prox;
} Item;

int criar_item(Item **lista, int linha, int coluna, TipoItem tipo);

void coletar_itens(Item **lista, Jogador *jogador, int *municao);

void desenhar_itens(const Item *lista);

void liberar_itens(Item **lista);

#endif
