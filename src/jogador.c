#include <math.h>
#include "jogador.h"

#define AJUSTE_SPRITE -90.0f
#define HITBOX_JOGADOR 24

static Rectangle area_do_jogador(const Jogador *jogador){
    Vector2 centro = centro_do_jogador(jogador);
    return (Rectangle){
        centro.x - HITBOX_JOGADOR / 2,
        centro.y - HITBOX_JOGADOR / 2,
        HITBOX_JOGADOR,
        HITBOX_JOGADOR
    };
}

void iniciar_jogador(Jogador *jogador, float x, float y){
    jogador->posicao = (Vector2){x, y};
    jogador->tamanho = 32;
    jogador->velocidade = 180;
    jogador->angulo = 0;
    jogador->textura = LoadTexture("assets/personagem/personagem.png");
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

    float passo_x = dx * jogador->velocidade * dt;
    float passo_y = dy * jogador->velocidade * dt;

    Rectangle area;

    area = area_do_jogador(jogador);
    area.x += passo_x;

    if (!colide_parede(mapa, area))
        jogador->posicao.x += passo_x;

    area = area_do_jogador(jogador);
    area.y += passo_y;

    if (!colide_parede(mapa, area))
        jogador->posicao.y += passo_y;

    Vector2 mouse = GetMousePosition();
    Vector2 centro = centro_do_jogador(jogador);
    jogador->angulo = atan2f(mouse.y - centro.y, mouse.x - centro.x) * RAD2DEG + AJUSTE_SPRITE;
}

void desenhar_jogador(const Jogador *jogador){

    Rectangle origem = {
        0,
        0,
        jogador->textura.width,
        jogador->textura.height / 2
        
    };
    
    Vector2 centro = centro_do_jogador(jogador);

    Rectangle destino = {
        centro.x,
        centro.y,
        jogador->tamanho,
        jogador->tamanho
    };

    DrawTexturePro(
        jogador->textura,
        origem,
        destino,
        (Vector2){jogador->tamanho / 2, jogador->tamanho / 2},
        jogador->angulo,
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