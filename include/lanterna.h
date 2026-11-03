#ifndef LANTERNA_H
#define LANTERNA_H
#include "raylib.h"

typedef struct {
    Texture2D textura;
    int raio;
} Lanterna;

void iniciar_lanterna(Lanterna *lanterna, int raio);
void desenhar_lanterna(const Lanterna *lanterna, Vector2 centro);
void descarregar_lanterna(Lanterna *lanterna);

#endif