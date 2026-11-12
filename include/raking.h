#ifndef RAKING_H
#define RAKING_H

typedef struct NodoPlacar {
    char nome[20];
    int pontuacao;
    float tempo;
    struct NodoPlacar* prox; 
} RegistroPlacar;


RegistroPlacar* InserirPlacar(RegistroPlacar* cabeca, const char* nome, int pontuacao, float tempo);
void SalvarPlacar(RegistroPlacar* cabeca, const char* arquivo);
RegistroPlacar* CarregarPlacar(const char* arquivo);
void LiberarPlacar(RegistroPlacar* cabeca);

#endif