#include <stdlib.h>
#include <time.h>
#include "raylib.h"
#include "mapa.h"
#include "jogador.h"
#include "lanterna.h"
#include "tela.h"
#include "tiro.h"
#include "inimigo.h"
#include "raking.h" // 1. Incluindo o sistema de ranking

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

    Texture2D textura_inimigo = LoadTexture("assets/personagem/inimigo.png");
    Inimigo *inimigos = NULL;
    gerar_inimigos(&inimigos, mapa, 5, jogador.posicao);
    int abates = 0;

    // --- 2. INICIALIZAÇÃO DO RANKING, CRONÔMETRO E PONTUAÇÃO ---
    RegistroPlacar* placar = CarregarPlacar("top_scores.txt");
    float cronometro = 0.0f;
    int pontuacao = 0;
    bool jogoFinalizado = false; // Controle de estado (Jogando ou Tela Final)

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        // --- 3. LÓGICA DO JOGO (Só roda se não tiver dado Game Over) ---
        if (!jogoFinalizado) {
            cronometro += dt; // Atualiza o cronômetro
            
            // Exemplo de aumento de pontuação: Aqui você pode colocar a lógica
            // para ganhar pontos (ex: matar um inimigo, pegar um item no mapa, etc)
            pontuacao = (int)cronometro * 10 + abates * 100;

            atualizar_jogador(&jogador, mapa, dt);
            
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && municao > 0) {
                if (criar_tiro(&tiros, centro_do_jogador(&jogador), GetMousePosition())) {
                    municao--;
                }
            }
            atualizar_tiros(&tiros, mapa, dt);

            atualizar_inimigos(inimigos, mapa, centro_do_jogador(&jogador), dt);
            abates += atingir_inimigos(&inimigos, &tiros);

            // --- 4. CONDIÇÃO PARA FINALIZAR O JOGO E SALVAR ---
            // Simulando o fim de jogo ao apertar ENTER
            if (IsKeyPressed(KEY_ENTER)) {
                jogoFinalizado = true;
                // Insere dinamicamente na lista encadeada e salva no arquivo txt
                placar = InserirPlacar(placar, "Jogador1", pontuacao, cronometro);
                SalvarPlacar(placar, "top_scores.txt");
            }
        }

        comecar_desenho_tela(&tela);
            ClearBackground(BLACK);
            
            if (!jogoFinalizado) {
                // Desenha o jogo rolando normalmente
                desenhar_mapa(mapa);
                desenhar_tiros(tiros);
                desenhar_inimigos(inimigos, textura_inimigo);
                desenhar_jogador(&jogador);
                desenhar_lanterna(&lanterna, centro_do_jogador(&jogador));
                
                // --- 5. DESENHANDO A HUD DO JOGADOR ---
                DrawText(TextFormat("Municao: %d", municao), 20, 20, 20, WHITE);
                DrawText(TextFormat("Tempo: %.2f", cronometro), 20, 50, 20, LIGHTGRAY);
                DrawText(TextFormat("Pontos: %d", pontuacao), 20, 80, 20, GOLD);
                DrawText("Aperte ENTER para simular Game Over e salvar", 20, ALTURA_TELA - 40, 20, GRAY);
            } 
            else {
                // --- 6. TELA DE FIM DE JOGO / LEADERBOARD ---
                // Navega pelos ponteiros da Lista Encadeada para exibir os scores
                DrawText("JOGO FINALIZADO", LARGURA_TELA/2 - 130, 50, 30, RED);
                DrawText("LEADERBOARD (Top Scores):", LARGURA_TELA/2 - 160, 120, 25, GOLD);
                
                RegistroPlacar* atual = placar;
                int y = 170;
                
                // Percorre a lista encadeada
                while (atual != NULL && y < ALTURA_TELA - 50) {
                    DrawText(TextFormat("%s | %d pts | %.2fs", atual->nome, atual->pontuacao, atual->tempo), 
                             LARGURA_TELA/2 - 140, y, 20, WHITE);
                    y += 30;
                    atual = atual->prox; // Avança o ponteiro
                }
                
                DrawText("Pressione ESC para sair do jogo", LARGURA_TELA/2 - 160, ALTURA_TELA - 50, 20, GRAY);
            }
            
        terminar_desenho_tela(&tela);
    }
    
    // --- 7. LIMPEZA DE MEMÓRIA (Evitar Memory Leaks das Structs dinâmicas) ---
    LiberarPlacar(placar);
    
    liberar_tiros(&tiros);
    liberar_inimigos(&inimigos);
    UnloadTexture(textura_inimigo);
    descarregar_jogador(&jogador);
    descarregar_lanterna(&lanterna);
    descarregar_tela(&tela);
    CloseWindow();
    return 0;
}