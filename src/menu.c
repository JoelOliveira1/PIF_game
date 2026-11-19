#include "menu.h"

void desenhar_menu(int jogo_em_andamento) {

    int offset = jogo_em_andamento ? 70 : 0;

    DrawText("PARANOIA", 520, 200, 40, RED);

    if (jogo_em_andamento) {
        DrawRectangle(520, 280, 200, 50, DARKGRAY);
        DrawText("CONTINUAR", 560, 295, 20, WHITE);
    }

    DrawRectangle(520, 280 + offset, 200, 50, DARKGRAY);
    if (jogo_em_andamento) {
        DrawText("NOVO JOGO", 560, 295 + offset, 20, WHITE);
    } else {
        DrawText("JOGAR", 585, 295 + offset, 20, WHITE);
    }

    DrawRectangle(520, 350 + offset, 200, 50, DARKGRAY);
    DrawText("RANKING", 570, 365 + offset, 20, WHITE);

    DrawRectangle(520, 420 + offset, 200, 50, DARKGRAY);
    DrawText("SAIR", 595, 435 + offset, 20, WHITE);
}

int atualizar_menu(int jogo_em_andamento) {

    if (jogo_em_andamento && IsKeyPressed(KEY_ESCAPE)) {
        return 4;
    }

    int offset = jogo_em_andamento ? 70 : 0;

    Rectangle botao_continuar = {520, 280, 200, 50};
    Rectangle botao_jogar     = {520, 280 + offset, 200, 50};
    Rectangle botao_ranking   = {520, 350 + offset, 200, 50};
    Rectangle botao_sair      = {520, 420 + offset, 200, 50};

    Vector2 mouse = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

        if (jogo_em_andamento && CheckCollisionPointRec(mouse, botao_continuar))
            return 4;
        if (CheckCollisionPointRec(mouse, botao_jogar))
            return 1;
        if (CheckCollisionPointRec(mouse, botao_ranking))
            return 2;
        if (CheckCollisionPointRec(mouse, botao_sair))
            return 3;
    }
    return 0;
}

void desenhar_ranking(void) {
    DrawText("RANKING", 300, 100, 40, GOLD);
    DrawText("ESC - Voltar ao menu", 250, 400, 20, WHITE);
}

int atualizar_ranking(void) {
    return IsKeyPressed(KEY_ESCAPE);
}