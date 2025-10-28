#include <stdio.h>

#define TAM 10      // Tamanho do tabuleiro (10x10)
#define TAM_NAVIO 3 // Tamanho fixo dos navios
#define AGUA 0      // Representa água no tabuleiro
#define NAVIO 3     // Representa parte de um navio

int main() {
    int tabuleiro[TAM][TAM]; // Matriz do tabuleiro
    int i, j;

    // --- 1. Inicializa o tabuleiro com 0 (água) ---
    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAM; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    // --- 2. Define as coordenadas iniciais dos navios ---
    // Navio horizontal: começa na linha 2, coluna 4
    int linha_horizontal = 2;
    int coluna_horizontal = 4;

    // Navio vertical: começa na linha 5, coluna 7
    int linha_vertical = 5;
    int coluna_vertical = 7;

    // --- 3. Posiciona o navio horizontal ---
    // Verifica se cabe no tabuleiro (coluna + tamanho <= limite)
    if (coluna_horizontal + TAM_NAVIO <= TAM) {
        for (i = 0; i < TAM_NAVIO; i++) {
            tabuleiro[linha_horizontal][coluna_horizontal + i] = NAVIO;
        }
    }

    // --- 4. Posiciona o navio vertical ---
    // Verifica se cabe no tabuleiro (linha + tamanho <= limite)
    if (linha_vertical + TAM_NAVIO <= TAM) {
        for (i = 0; i < TAM_NAVIO; i++) {
            // Verifica se não sobrepõe o navio horizontal
            if (tabuleiro[linha_vertical + i][coluna_vertical] == AGUA) {
                tabuleiro[linha_vertical + i][coluna_vertical] = NAVIO;
            }
        }
    }

    // --- 5. Exibe o tabuleiro ---
    printf("\n=== TABULEIRO DE BATALHA NAVAL ===\n\n");
    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}