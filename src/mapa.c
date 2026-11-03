#include <stdio.h>
#include "mapa.h"

int carregar_mapa(int mapa[LINHAS][COLUNAS], const char *arquivo)
{
    FILE *fp = fopen(arquivo, "r");

    if (fp == NULL) {
        return 0;
    }
    char c;

    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {

            if (fscanf(fp, " %c", &c) != 1) {
                fclose(fp);
                return 0;
            }
            if (c == '#') {
                mapa[i][j] = PAREDE;
            }
            else if (c == '.') {
                mapa[i][j] = CHAO;
            }
            else {
                fclose(fp);
                return 0;
            }
        }
    }

    fclose(fp);
    return 1;
}

void desenhar_mapa(int mapa[LINHAS][COLUNAS])
{
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            int x = j * TAMANHO;
            int y = i * TAMANHO;

            if (mapa[i][j] == PAREDE) {
                DrawRectangle(x, y, TAMANHO, TAMANHO, (Color){70, 70, 80, 255});

                DrawRectangleLines(x, y, TAMANHO, TAMANHO,(Color){40, 40, 50, 255});
            }
            else {
                DrawRectangle(x, y, TAMANHO, TAMANHO,(Color){25, 25, 30, 255});
            }
        }
    }
}

int colide_parede(int mapa[LINHAS][COLUNAS], Rectangle area)
{
    if (area.x < 0 || area.y < 0 || area.x + area.width > LARGURA_TELA || 
    area.y + area.height > ALTURA_TELA) {
        
        return 1;
    }

    int inicioX = (int)(area.x / TAMANHO);
    int fimX = (int)((area.x + area.width - 0.001f) / TAMANHO);

    int inicioY = (int)(area.y / TAMANHO);
    int fimY = (int)((area.y + area.height - 0.001f)/ TAMANHO);

    for (int i = inicioY; i <= fimY; i++) {
        for (int j = inicioX; j <= fimX; j++) {
            if (mapa[i][j] == PAREDE) {
                return 1;
            }
        }
    }

    return 0;
}