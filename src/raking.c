#include "raking.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

RegistroPlacar* InserirPlacar(RegistroPlacar* cabeca, const char* nome, int pontuacao, float tempo) {
    // Alocação dinâmica de memória
    RegistroPlacar* novo = (RegistroPlacar*)malloc(sizeof(RegistroPlacar));
    strcpy(novo->nome, nome);
    novo->pontuacao = pontuacao;
    novo->tempo = tempo;
    novo->prox = NULL;

    if (cabeca == NULL || cabeca->pontuacao < pontuacao) {
        novo->prox = cabeca;
        return novo;
    }

    RegistroPlacar* atual = cabeca;
    while (atual->prox != NULL && atual->prox->pontuacao >= pontuacao) {
        atual = atual->prox;
    }
    novo->prox = atual->prox;
    atual->prox = novo;
    return cabeca;
}

void SalvarPlacar(RegistroPlacar* cabeca, const char* arquivo) {
    FILE* f = fopen(arquivo, "w");
    if (!f) return;
    RegistroPlacar* atual = cabeca;
    while (atual != NULL) {
        fprintf(f, "%s %d %.2f\n", atual->nome, atual->pontuacao, atual->tempo);
        atual = atual->prox;
    }
    fclose(f);
}

RegistroPlacar* CarregarPlacar(const char* arquivo) {
    FILE* f = fopen(arquivo, "r");
    if (!f) return NULL;
    RegistroPlacar* cabeca = NULL;
    char nome[20];
    int pontuacao;
    float tempo;
    while (fscanf(f, "%19s %d %f", nome, &pontuacao, &tempo) == 3) {
        cabeca = InserirPlacar(cabeca, nome, pontuacao, tempo);
    }
    fclose(f);
    return cabeca;
}

void LiberarPlacar(RegistroPlacar* cabeca) {
    RegistroPlacar* atual = cabeca;
    while (atual != NULL) {
        RegistroPlacar* temp = atual;
        atual = atual->prox;
        free(temp); // Liberando a memória
    }
}