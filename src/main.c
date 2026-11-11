#include <stdlib.h>
#include <time.h>
#include "raylib.h"
#include "mapa.h"
#include "jogador.h"
#include "lanterna.h"
#include "tela.h"
#include "tiro.h"

#define RAIO_LANTERNA 160

int main(void){

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(LARGURA_TELA, ALTURA_TELA, "Paranoia");
    ToggleBorderlessWindowed();
    SetTargetFPS(60);

    Tela tela;
    iniciar_tela(&tela);

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
    Tiro *tiros = NULL;
    int municao = 12;

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        atualizar_jogador(&jogador, mapa, dt);
        
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && municao > 0) {
            if (criar_tiro(&tiros, centro_do_jogador(&jogador), GetMousePosition())) {
                municao--;
            }
        }
        atualizar_tiros(&tiros, mapa, dt);

        comecar_desenho_tela(&tela);
            ClearBackground(BLACK);
            desenhar_mapa(mapa);
            desenhar_tiros(tiros);
            desenhar_jogador(&jogador);
            desenhar_lanterna(&lanterna, centro_do_jogador(&jogador));
            DrawText(TextFormat("Municao: %d", municao), 20, 20, 20, WHITE);
        terminar_desenho_tela(&tela);
    }
    liberar_tiros(&tiros);
    descarregar_jogador(&jogador);
    descarregar_lanterna(&lanterna);
    descarregar_tela(&tela);
    CloseWindow();
    return 0;
}