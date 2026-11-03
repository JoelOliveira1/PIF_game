#ifndef TELA_H
#define TELA_H
#include "raylib.h"

typedef struct {
    RenderTexture2D alvo;
    float escala;
    Vector2 deslocamento;
} Tela;

void iniciar_tela(Tela *tela);
void comecar_desenho_tela(Tela *tela);
void terminar_desenho_tela(const Tela *tela);
void descarregar_tela(Tela *tela);

#endif