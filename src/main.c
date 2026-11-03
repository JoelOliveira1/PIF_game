#include <stdlib.h>
#include <time.h>
#include "raylib.h"
#include "mapa.h"
#include "jogador.h"
#include "lanterna.h"

#define RAIO_LANTERNA 160

int main(void){

    InitWindow(LARGURA_TELA, ALTURA_TELA, "Paranoia");
    SetTargetFPS(60);

    srand(time(NULL));

    int mapa[LINHAS][COLUNAS];
    
    if (!carregar_mapa(mapa, "assets/paredes/mapa1.txt")) {
        CloseWindow();
        return 1;
    }

    Jogador jogador;
    iniciar_jogador(&jogador, 2 * TAMANHO + 6, 2 * TAMANHO + 6);

    Lanterna lanterna;
    iniciar_lanterna(&lanterna, RAIO_LANTERNA);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        atualizar_jogador(&jogador, mapa, dt);

        BeginDrawing();
            ClearBackground(BLACK);
            desenhar_mapa(mapa);
            desenhar_jogador(&jogador);
            desenhar_lanterna(&lanterna, centro_do_jogador(&jogador));
        EndDrawing();
    }
    descarregar_jogador(&jogador);
    descarregar_lanterna(&lanterna);
    CloseWindow();
    return 0;
}