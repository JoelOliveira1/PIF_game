#include "jogador.h"

void iniciar_jogador(Jogador *jogador, float x, float y){
    jogador->posicao = (Vector2){x, y};
    jogador->tamanho = 32;
    jogador->velocidade = 180;
    jogador->textura = LoadTexture("assets/personagem/32x.png");
}

void atualizar_jogador(Jogador *jogador, int mapa[LINHAS][COLUNAS], float dt){
    float dx = 0, dy = 0;

    if (IsKeyDown(KEY_D)) dx++;
    if (IsKeyDown(KEY_A)) dx--;
    if (IsKeyDown(KEY_S)) dy++;
    if (IsKeyDown(KEY_W)) dy--;

    if (dx != 0 && dy != 0) {
        dx *= 0.7071f;
        dy *= 0.7071f;
    }

    Rectangle area;

    area = (Rectangle){
        jogador->posicao.x + dx * jogador->velocidade * dt,
        jogador->posicao.y,
        jogador->tamanho,
        jogador->tamanho
    };

    if (!colide_parede(mapa, area))
        jogador->posicao.x = area.x;

    area = (Rectangle){
        jogador->posicao.x,
        jogador->posicao.y + dy * jogador->velocidade * dt,
        jogador->tamanho,
        jogador->tamanho
    };

    if (!colide_parede(mapa, area))
        jogador->posicao.y = area.y;
}

void desenhar_jogador(const Jogador *jogador){

    Rectangle origem = {
        0,
        0,
        jogador->textura.width,
        jogador->textura.height / 2
        
    };

    Rectangle destino = {
        jogador->posicao.x,
        jogador->posicao.y,
        jogador->tamanho,
        jogador->tamanho
    };

    DrawTexturePro(
        jogador->textura,
        origem,
        destino,
        (Vector2){0, 0},
        0,
        WHITE
    );
}

void descarregar_jogador(Jogador *jogador){
    UnloadTexture(jogador->textura);
}

Vector2 centro_do_jogador(const Jogador *jogador){
    return (Vector2){
        jogador->posicao.x + jogador->tamanho / 2,
        jogador->posicao.y + jogador->tamanho / 2
    };
}
