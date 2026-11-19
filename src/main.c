#include <stdlib.h>
#include <time.h>
#include "raylib.h"
#include "mapa.h"
#include "jogador.h"
#include "lanterna.h"
#include "tela.h"
#include "tiro.h"
#include "inimigo.h"
#include "raking.h"
#include "menu.h"
#include "fase.h"
#include "item.h"

#define RAIO_LANTERNA 140

void reiniciar_jogo( Jogador *jogador, Tiro **tiros, Inimigo **inimigos, Item **itens, int mapa[LINHAS][COLUNAS],
int *municao, int *abates, float *cronometro, int *pontuacao){

    liberar_tiros(tiros);
    liberar_inimigos(inimigos);
    descarregar_jogador(jogador);
    iniciar_fase(mapa, itens);
    iniciar_jogador(jogador, 2 * TAMANHO + 6, 2 * TAMANHO + 6);
    
    *municao = 15;
    *abates = 0;
    *cronometro = 0.0f;
    *pontuacao = 0;

    gerar_inimigos(inimigos, mapa, 5, jogador->posicao);
}

int main(void){

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(LARGURA_TELA, ALTURA_TELA, "Paranoia");
    SetExitKey(KEY_NULL);
    ToggleBorderlessWindowed();
    SetTargetFPS(60);

    Tela tela;
    iniciar_tela(&tela);

    srand((unsigned int)time(NULL));

    int mapa[LINHAS][COLUNAS];
    
    if (!carregar_mapa(mapa, "assets/paredes/mapa1.txt")){
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

    Item *itens = NULL;
    Texture2D textura_vida = LoadTexture("assets/itens/remedio.png");
    Texture2D textura_municao = LoadTexture("assets/itens/municao.png");

    // --- 2. INICIALIZAÇÃO DO RANKING, CRONÔMETRO E PONTUAÇÃO ---
    RegistroPlacar* placar = CarregarPlacar("top_scores.txt");
    float cronometro = 0.0f;
    int pontuacao = 0;
    int jogo_em_andamento = 0;
    EstadoJogo estado = MENU;

    while (!WindowShouldClose()){
        
        float dt = GetFrameTime();

        if (estado == MENU){

            int opcao = atualizar_menu(jogo_em_andamento);

            // jogar / novo jogo
            if (opcao == 1){

                reiniciar_jogo(
                    &jogador,
                    &tiros,
                    &inimigos,
                    &itens,
                    mapa,
                    &municao,
                    &abates,
                    &cronometro,
                    &pontuacao
                );
                jogo_em_andamento = 1;
                estado = JOGANDO;
            }
            // ranking
            else if (opcao == 2){
                estado = RANKING;
            }
            // sair
            else if (opcao == 3){
                break;
            }
            // continuar
            else if (opcao == 4 && jogo_em_andamento){
                estado = JOGANDO;
            }
        }

        else if (estado == RANKING){

            if (atualizar_ranking()){
                estado = MENU;
            }
        }

        else if (estado == JOGANDO) {

            if (IsKeyPressed(KEY_ESCAPE)) {
                estado = MENU;
            }
            else {
                cronometro += dt;

                atualizar_jogador(&jogador, mapa, dt);

                coletar_itens(&itens, &jogador, &municao);

                if (atualizar_fase(&jogador, mapa, &tiros, &inimigos, &itens, &pontuacao)){
                    placar = InserirPlacar(
                        placar,
                        "Jogador1",
                        pontuacao,
                        cronometro
                    );
                    SalvarPlacar(placar, "top_scores.txt");
                    jogo_em_andamento = 0;
                    estado = MENU;
                } 
                else {
                    // Disparo
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && municao > 0) {

                        if (criar_tiro(&tiros,centro_do_jogador(&jogador),GetMousePosition())){
                            municao--;
                        }
                    }

                    verificar_colisao_jogador(inimigos, &jogador);

                    atualizar_tiros(&tiros, mapa, dt);

                    atualizar_inimigos(
                        inimigos,
                        mapa,
                        centro_do_jogador(&jogador),
                        dt
                    );

                    int novos_abates = atingir_inimigos(&inimigos, &tiros);
                    if (novos_abates > 0) {
                        abates += novos_abates;
                        pontuacao += novos_abates * 100;
                    }

                    if (jogador.vida <= 0) {

                        jogador.vida = 0;

                        placar = InserirPlacar(
                            placar,
                            "Jogador1",
                            pontuacao,
                            cronometro
                        );

                        SalvarPlacar(placar, "top_scores.txt");
                        jogo_em_andamento = 0;
                        estado = MENU;
                    }
                }
            }
        }

        comecar_desenho_tela(&tela);

        ClearBackground(BLACK);

        // MENU INICIAL
        if (estado == MENU) {

            desenhar_menu(jogo_em_andamento);
        }

        // TELA DE RANKING
        else if (estado == RANKING){

            desenhar_ranking();
            RegistroPlacar *atual = placar;
            int y = 170;

            while (atual != NULL && y < ALTURA_TELA - 50){

                DrawText(
                    TextFormat(
                        "%s | %d pts | %.2fs",
                        atual->nome,
                        atual->pontuacao,
                        atual->tempo
                    ),
                    LARGURA_TELA / 2 - 140, y, 20, WHITE
                );

                y += 30;

                atual = atual->prox;
            }
        }

        else if (estado == JOGANDO){

            desenhar_mapa(mapa);
            desenhar_fase();
            desenhar_itens(itens, textura_vida, textura_municao);
            desenhar_tiros(tiros);
            desenhar_inimigos(inimigos, textura_inimigo);
            desenhar_jogador(&jogador);
            desenhar_lanterna(&lanterna, centro_do_jogador(&jogador));

            DrawText(
                TextFormat("Vida: %d", jogador.vida), 20, 110, 20, RED
            );
            DrawText(
                TextFormat("Municao: %d", municao), 20, 20, 20, WHITE
            );
            DrawText(
                TextFormat("Tempo: %.2f", cronometro), 20,50,20, LIGHTGRAY
            );
            DrawText(
                TextFormat("Pontos: %d", pontuacao), 20, 80, 20, GOLD
            );
        }
        terminar_desenho_tela(&tela);
    }

    LiberarPlacar(placar);
    liberar_tiros(&tiros);
    liberar_inimigos(&inimigos);
    liberar_itens(&itens);
    UnloadTexture(textura_inimigo);
    UnloadTexture(textura_vida);
    UnloadTexture(textura_municao);
    liberar_texturas_fase();
    descarregar_jogador(&jogador);
    descarregar_lanterna(&lanterna);
    descarregar_tela(&tela);
    CloseWindow();

    return 0;
}