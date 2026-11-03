#include "lanterna.h"
#include "mapa.h"

void iniciar_lanterna(Lanterna *lanterna, int raio)
{
    lanterna->raio = raio;

    Image imagem = GenImageGradientRadial(raio * 2, raio * 2, 0.3f, BLANK, BLACK);
    lanterna->textura = LoadTextureFromImage(imagem);
    UnloadImage(imagem);
}

void desenhar_lanterna(const Lanterna *lanterna, Vector2 centro)
{
    int lado = lanterna->raio * 2;
    int x = (int)centro.x - lanterna->raio;
    int y = (int)centro.y - lanterna->raio;

    DrawTexture(lanterna->textura, x, y, WHITE);

    if (y > 0) {
        DrawRectangle(0, 0, LARGURA_TELA, y, BLACK);
    }
    if (y + lado < ALTURA_TELA) {
        DrawRectangle(0, y + lado, LARGURA_TELA, ALTURA_TELA - (y + lado), BLACK);
    }
    if (x > 0) {
        DrawRectangle(0, y, x, lado, BLACK);
    }
    if (x + lado < LARGURA_TELA) {
        DrawRectangle(x + lado, y, LARGURA_TELA - (x + lado), lado, BLACK);
    }
}

void descarregar_lanterna(Lanterna *lanterna)
{
    UnloadTexture(lanterna->textura);
}