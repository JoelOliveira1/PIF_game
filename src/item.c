#include <stdlib.h>
#include "item.h"

#define TAMANHO_ITEM 16
#define VIDA_ITEM 30
#define MUNICAO_ITEM 6
#define VIDA_MAXIMA 100

static Rectangle area_do_item(const Item *item) {
    return (Rectangle){
        item->posicao.x,
        item->posicao.y,
        TAMANHO_ITEM,
        TAMANHO_ITEM
    };
}

int criar_item(Item **lista, int linha, int coluna, TipoItem tipo) {

    Item *novo = malloc(sizeof(Item));

    if (novo == NULL)
        return 0;

    novo->posicao = (Vector2){
        coluna * TAMANHO + (TAMANHO - TAMANHO_ITEM) / 2,
        linha * TAMANHO + (TAMANHO - TAMANHO_ITEM) / 2
    };
    novo->tipo = tipo;

    novo->prox = *lista;
    *lista = novo;

    return 1;
}

void coletar_itens(Item **lista, Jogador *jogador, int *municao) {

    Vector2 centro = centro_do_jogador(jogador);

    Rectangle area = {centro.x - 12, centro.y - 12, 24, 24};

    Item **atual = lista;

    while (*atual != NULL) {

        Item *item = *atual;
        int coletou = 0;

        if (CheckCollisionRecs(area, area_do_item(item))) {

            if (item->tipo == ITEM_VIDA && jogador->vida < VIDA_MAXIMA) {

                jogador->vida += VIDA_ITEM;

                if (jogador->vida > VIDA_MAXIMA)
                    jogador->vida = VIDA_MAXIMA;

                coletou = 1;
            }
            else if (item->tipo == ITEM_MUNICAO) {

                *municao += MUNICAO_ITEM;
                coletou = 1;
            }
        }

        if (coletou) {
            *atual = item->prox;
            free(item);
        } else {
            atual = &item->prox;
        }
    }
}

void desenhar_itens(const Item *lista) {

    const Item *atual = lista;

    while (atual != NULL) {

        Color cor = ORANGE;
        if (atual->tipo == ITEM_VIDA)
            cor = GREEN;

        DrawRectangleRec(area_do_item(atual), cor);

        atual = atual->prox;
    }
}

void liberar_itens(Item **lista) {

    Item *atual = *lista;

    while (atual != NULL) {

        Item *proximo = atual->prox;

        free(atual);

        atual = proximo;
    }

    *lista = NULL;
}
