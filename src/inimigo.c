#include <stdlib.h>
#include <math.h>
#include "inimigo.h"

#define TAMANHO_INIMIGO 32
#define HITBOX_INIMIGO 24
#define VELOCIDADE_INIMIGO 60
#define VIDA_INIMIGO 3
#define TEMPO_DANO 0.1f
#define DISTANCIA_MINIMA 256
#define AJUSTE_SPRITE -90.0f

static Vector2 centro_do_inimigo(const Inimigo *inimigo) {
    return (Vector2){
        inimigo->posicao.x + TAMANHO_INIMIGO / 2,
        inimigo->posicao.y + TAMANHO_INIMIGO / 2
    };
}

static Rectangle area_do_inimigo(const Inimigo *inimigo) {
    Vector2 centro = centro_do_inimigo(inimigo);
    return (Rectangle){
        centro.x - HITBOX_INIMIGO / 2,
        centro.y - HITBOX_INIMIGO / 2,
        HITBOX_INIMIGO,
        HITBOX_INIMIGO
    };
}

static int criar_inimigo(Inimigo **lista, float x, float y) {

    Inimigo *novo = malloc(sizeof(Inimigo));

    if(novo == NULL)
        return 0;

    novo->posicao = (Vector2){x, y};
    novo->angulo = 0;
    novo->vida = VIDA_INIMIGO;
    novo->tempo_dano = 0;

    novo->prox = *lista;
    *lista = novo;

    return 1;
}

void gerar_inimigos(Inimigo **lista, int mapa[LINHAS][COLUNAS], int quantidade, Vector2 jogador) {

    int criados = 0;
    int tentativas = 0;

    while(criados < quantidade && tentativas < 1000) {

        tentativas++;

        int linha = rand() % LINHAS;
        int coluna = rand() % COLUNAS;

        if (mapa[linha][coluna] != CHAO)
            continue;

        float x = coluna * TAMANHO;
        float y = linha * TAMANHO;

        float dx = x - jogador.x;
        float dy = y - jogador.y;

        if (sqrtf(dx * dx + dy * dy) < DISTANCIA_MINIMA)
            continue;

        if(criar_inimigo(lista, x, y))
            criados++;
    }
}

void atualizar_inimigos(Inimigo *lista, int mapa[LINHAS][COLUNAS], Vector2 alvo, float dt) {

    Inimigo *atual = lista;

    while(atual != NULL) {

        Vector2 centro = centro_do_inimigo(atual);

        float dx = alvo.x - centro.x;
        float dy = alvo.y - centro.y;
        float distancia = sqrtf(dx * dx + dy * dy);

        if (distancia > 1) {

            dx /= distancia;
            dy /= distancia;

            float passo_x = dx * VELOCIDADE_INIMIGO * dt;
            float passo_y = dy * VELOCIDADE_INIMIGO * dt;

            Rectangle area = area_do_inimigo(atual);
            area.x += passo_x;

            if (!colide_parede(mapa, area))
                atual->posicao.x += passo_x;

            area = area_do_inimigo(atual);
            area.y += passo_y;

            if(!colide_parede(mapa, area))
                atual->posicao.y += passo_y;

            atual->angulo = atan2f(dy, dx) * RAD2DEG + AJUSTE_SPRITE;
        }

        if (atual->tempo_dano > 0)
            atual->tempo_dano -= dt;

        atual = atual->prox;
    }
}

int atingir_inimigos(Inimigo **inimigos, Tiro **tiros){

    int abates = 0;
    Tiro **tiro_atual = tiros;

    while (*tiro_atual != NULL) {

        Tiro *tiro = *tiro_atual;
        int acertou = 0;

        Inimigo **inimigo_atual = inimigos;

        while(*inimigo_atual != NULL) {

            Inimigo *inimigo = *inimigo_atual;

            if (CheckCollisionCircleRec(tiro->posicao, TAMANHO_TIRO / 2, area_do_inimigo(inimigo))) {

                acertou = 1;
                inimigo->vida--;
                inimigo->tempo_dano = TEMPO_DANO;

                if(inimigo->vida <= 0){
                    *inimigo_atual = inimigo->prox;
                    free(inimigo);
                    abates++;
                }

                break;
            }

            inimigo_atual = &inimigo->prox;
        }

        if (acertou) {
            *tiro_atual = tiro->prox;
            free(tiro);
        }else{
            tiro_atual = &tiro->prox;
        }
    }

    return abates;
}

void desenhar_inimigos(const Inimigo *lista, Texture2D textura) {

    Rectangle origem = {0, 0, textura.width, textura.height / 2};

    const Inimigo *atual = lista;

    while(atual != NULL){

        Vector2 centro = centro_do_inimigo(atual);

        Rectangle destino = {centro.x, centro.y, TAMANHO_INIMIGO, TAMANHO_INIMIGO};

        Color cor = WHITE;
        if (atual->tempo_dano > 0)
            cor = RED;

        DrawTexturePro(
            textura,
            origem,
            destino,
            (Vector2){TAMANHO_INIMIGO / 2, TAMANHO_INIMIGO / 2},
            atual->angulo,
            cor
        );

        atual = atual->prox;
    }
}

void verificar_colisao_jogador(Inimigo *lista, Jogador *jogador) {

    Vector2 centro = centro_do_jogador(jogador);

    Rectangle area = {centro.x - 12, centro.y - 12, 24, 24};

      while (lista != NULL) {

        if (CheckCollisionRecs(area, area_do_inimigo(lista))) {

            if (jogador->tempo_dano <= 0) {
                jogador->vida -= 20;
                jogador->tempo_dano = 1.0f;
            }
            break;
        }
        lista = lista->prox;
    }
}

void liberar_inimigos(Inimigo **lista){

    Inimigo *atual = *lista;

    while (atual != NULL) {

        Inimigo *proximo = atual->prox;

        free(atual);

        atual = proximo;
    }

    *lista = NULL;
}
