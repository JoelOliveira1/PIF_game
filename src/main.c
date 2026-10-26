#include "raylib.h"
#define TAMANHO_TILE 32
#define COLUNAS 40
#define LINHAS 22
#define LARGURA_TELA (COLUNAS * TAMANHO_TILE) 
#define ALTURA_TELA  (LINHAS  * TAMANHO_TILE)
#define TILE_CHAO   0
#define TILE_PAREDE 1


void gerar_mapa(int mapa[LINHAS][COLUNAS]){

    for (int linha = 0; linha < LINHAS; linha++) {
        for (int coluna = 0; coluna < COLUNAS; coluna++) {
            int eborda = (linha == 0 || linha == LINHAS - 1 || coluna == 0 || coluna == COLUNAS - 1);

            if (eborda) {
                mapa[linha][coluna] = TILE_PAREDE;
            } else {
                mapa[linha][coluna] = TILE_CHAO;
            }
        }
    }
}

void desenhar_mapa(int mapa[LINHAS][COLUNAS]){

    for (int linha = 0; linha < LINHAS; linha++) {
        for (int coluna = 0; coluna < COLUNAS; coluna++) {
            int x = coluna * TAMANHO_TILE;
            int y = linha  * TAMANHO_TILE; 

            if (mapa[linha][coluna] == TILE_PAREDE) {
                DrawRectangle(x, y, TAMANHO_TILE, TAMANHO_TILE, (Color){70, 70, 80, 255});
                DrawRectangleLines(x, y, TAMANHO_TILE, TAMANHO_TILE, (Color){40, 40, 50, 255});
            } else {
                DrawRectangle(x, y, TAMANHO_TILE, TAMANHO_TILE, (Color){25, 25, 30, 255}); 
            }
        }
    }
}

int main(void)
{
    InitWindow(LARGURA_TELA, ALTURA_TELA, "Paranoia");
    SetTargetFPS(60);

    int mapa[LINHAS][COLUNAS];
    gerar_mapa(mapa);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        desenhar_mapa(mapa);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}