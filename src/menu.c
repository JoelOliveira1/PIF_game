#include "menu.h"

static Rectangle botao_jogar = {520, 280, 200, 50};
static Rectangle botao_ranking = {520, 350, 200, 50};
static Rectangle botao_sair = {520, 420, 200, 50};

void desenhar_menu(void) {

    DrawText("PARANOIA", 520, 200, 40, RED);
    
    DrawRectangle(520, 280, 200, 50, DARKGRAY);
    DrawText("JOGAR", 585, 295, 20, WHITE);

    DrawRectangle(520, 350, 200, 50, DARKGRAY);
    DrawText("RANKING", 570, 365, 20, WHITE);

    DrawRectangle(520, 420, 200, 50, DARKGRAY);
    DrawText("SAIR", 595, 435, 20, WHITE);
}

int atualizar_menu(void) {

    Vector2 mouse = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

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