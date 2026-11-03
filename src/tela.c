#include <math.h>
#include "tela.h"
#include "mapa.h"

void iniciar_tela(Tela *tela) {
    tela->alvo = LoadRenderTexture(LARGURA_TELA, ALTURA_TELA);
    SetTextureFilter(tela->alvo.texture, TEXTURE_FILTER_POINT);
    tela->escala = 1;
    tela->deslocamento = (Vector2){0, 0};
}

void comecar_desenho_tela(Tela *tela) {
    tela->escala = fminf((float)GetScreenWidth() / LARGURA_TELA, (float)GetScreenHeight() / ALTURA_TELA);

    tela->deslocamento.x = (GetScreenWidth() - LARGURA_TELA * tela->escala) / 2;
    tela->deslocamento.y = (GetScreenHeight() - ALTURA_TELA * tela->escala) / 2;

    SetMouseOffset(-(int)tela->deslocamento.x, -(int)tela->deslocamento.y);
    SetMouseScale(1 / tela->escala, 1 / tela->escala);

    BeginTextureMode(tela->alvo);
}

void terminar_desenho_tela(const Tela *tela) {
    EndTextureMode();
    Rectangle origem = {0, 0, LARGURA_TELA, -ALTURA_TELA};

    Rectangle destino = {
        tela->deslocamento.x,
        tela->deslocamento.y,
        LARGURA_TELA * tela->escala,
        ALTURA_TELA * tela->escala
    };

    BeginDrawing();
        ClearBackground(BLACK);
        DrawTexturePro(tela->alvo.texture, origem, destino, (Vector2){0, 0}, 0, WHITE);
    EndDrawing();
}

void descarregar_tela(Tela *tela) {
    UnloadRenderTexture(tela->alvo);
}
