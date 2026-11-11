
#include <stdlib.h>
#include <math.h>
#include "tiro.h"

#define VELOCIDADE_TIRO 600
#define TAMANHO_TIRO 4

int criar_tiro(Tiro **lista, Vector2 origem, Vector2 alvo) {

    float dx = alvo.x - origem.x;
    float dy = alvo.y - origem.y;

    float distancia = sqrtf(dx * dx + dy * dy);

    if (distancia == 0)
        return 0;

    Tiro *novo = malloc(sizeof(Tiro));

    if (novo == NULL)
        return 0;

    novo->posicao = origem;

    novo->direcao = (Vector2){
        dx / distancia,
        dy / distancia
    };

    novo->velocidade = VELOCIDADE_TIRO;

    novo->prox = *lista;
    *lista = novo;

    return 1;
}

void atualizar_tiros(Tiro **lista, int mapa[LINHAS][COLUNAS], float dt) {

    Tiro **atual = lista;

    while (*atual != NULL) {

        Tiro *tiro = *atual;

        tiro->posicao.x += tiro->direcao.x * tiro->velocidade * dt;
        tiro->posicao.y += tiro->direcao.y * tiro->velocidade * dt;

        Rectangle area = {
            tiro->posicao.x - TAMANHO_TIRO / 2,
            tiro->posicao.y - TAMANHO_TIRO / 2,
            TAMANHO_TIRO,
            TAMANHO_TIRO
        };

        if (colide_parede(mapa, area)) {

            *atual = tiro->prox;
            free(tiro);

        } else {

            atual = &tiro->prox;
        }
    }
}

void desenhar_tiros(const Tiro *lista) {

    const Tiro *atual = lista;

    while (atual != NULL) {

        DrawCircleV(atual->posicao, TAMANHO_TIRO / 2, YELLOW);

        atual = atual->prox;
    }
}

void liberar_tiros(Tiro **lista) {

    Tiro *atual = *lista;

    while (atual != NULL) {

        Tiro *proximo = atual->prox;

        free(atual);

        atual = proximo;
    }

    *lista = NULL;
}
