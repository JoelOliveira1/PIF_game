#include "fase.h"

static int fase_atual = 1;

static int tem_chave = 0;
static int tem_cartao = 0;

static Rectangle porta = {1152, 320, 32, 64};
static Rectangle chave = {7 * TAMANHO+4, 3*TAMANHO+4, 24, 24};
static Rectangle cartao = {35 * TAMANHO+4, 2 *TAMANHO + 4, 24, 24};

static Texture2D textura_chave;
static Texture2D textura_cracha;

static void posicionar_porta(void) {

    switch (fase_atual) {

        case 1:
            porta = (Rectangle){35*TAMANHO, 7*TAMANHO, 32, 32};
            break;

        case 2:
            porta = (Rectangle){37*TAMANHO, 20*TAMANHO, 32, 32};
            break;

        case 3:
            porta = (Rectangle){7*TAMANHO, 20*TAMANHO, 32, 32};
            break;
    }
}

static void posicionar_itens(Item **itens){

    liberar_itens(itens);

    switch(fase_atual){

        case 1:
            criar_item(itens, 2, 35, ITEM_VIDA);
            criar_item(itens, 8, 4, ITEM_MUNICAO);
            break;

        case 2:
            criar_item(itens, 9, 3, ITEM_VIDA);
            criar_item(itens, 19, 14, ITEM_MUNICAO);
            criar_item(itens, 2, 37, ITEM_MUNICAO);
            break;

        case 3:
            criar_item(itens, 12, 4, ITEM_VIDA);
            criar_item(itens, 19, 30, ITEM_VIDA);
            criar_item(itens, 9, 20, ITEM_MUNICAO);
            criar_item(itens, 3, 35, ITEM_MUNICAO);
            break;
    }
}

int iniciar_fase(int mapa[LINHAS][COLUNAS], Item **itens){

    fase_atual = 1;
    tem_chave = 0;
    tem_cartao = 0;

    textura_chave = LoadTexture("assets/itens/chave.png");
    textura_cracha = LoadTexture("assets/itens/cracha.png");

    posicionar_porta();
    posicionar_itens(itens);

    return carregar_fase(1, mapa);
}

int atualizar_fase(
    Jogador *jogador, int mapa[LINHAS][COLUNAS], Tiro **tiros, Inimigo **inimigos, Item **itens){

    Vector2 centro = centro_do_jogador(jogador);

    Rectangle area = {
        centro.x - 12,
        centro.y - 12,
        24,
        24
    };
    // Pegar chave
    if (fase_atual == 1 && !tem_chave) {
        if (CheckCollisionRecs(area, chave)){
            tem_chave = 1;
        }
    }

    // Pegar cartão
    if (fase_atual == 2 && !tem_cartao) {
        if (CheckCollisionRecs(area, cartao)){
            tem_cartao = 1;
        }
    }

    // Verificar porta
    if (!CheckCollisionRecs(area, porta)){
        return 0;
    }

    // Verificar se pode passar
    if (fase_atual == 1 && !tem_chave){
        return 0;
    }

    if (fase_atual == 2 && !tem_cartao){
        return 0;
    }

    // Terminou a terceira fase
    if (fase_atual == 3){
        return 1;
    }

    // Carregar next fase
    int proxima_fase = fase_atual + 1;

    if (!carregar_fase(proxima_fase, mapa)){
        return 0;
    }

    liberar_tiros(tiros);
    liberar_inimigos(inimigos);

    fase_atual = proxima_fase;
    posicionar_porta();
    posicionar_itens(itens);
    jogador->posicao = (Vector2){70, 70};

    gerar_inimigos(inimigos, mapa, 7, jogador->posicao);

    return 0;
}

void desenhar_fase(void){

    if (fase_atual == 1 && !tem_chave){
        DrawTextureRec(textura_chave,
        (Rectangle){0, 0, textura_chave.width, textura_chave.height},
        (Vector2){chave.x, chave.y}, WHITE);
    }
    if (fase_atual == 2 && !tem_cartao){
        DrawTextureRec(textura_cracha,(Rectangle){0, 0, textura_cracha.width, textura_cracha.height},
        (Vector2){cartao.x, cartao.y},WHITE);
    }

    DrawRectangleRec(porta, RED);
}

void liberar_texturas_fase(void){
    
    UnloadTexture(textura_chave);
    UnloadTexture(textura_cracha);
}