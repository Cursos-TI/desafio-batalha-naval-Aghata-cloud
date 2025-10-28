#include <stdio.h>

#define TAM 10      // Tamanho do tabuleiro (10x10)
#define TAM_NAVIO 3 // Tamanho fixo dos navios
#define AGUA 0      // Representa água
#define NAVIO 3     // Representa navio

// Função para verificar se uma posição está dentro dos limites do tabuleiro
int dentroDoLimite(int linha, int coluna) {
    return (linha >= 0 && linha < TAM && coluna >= 0 && coluna < TAM);
}

// Função para verificar se há sobreposição antes de posicionar
int podePosicionar(int tabuleiro[TAM][TAM], int linha, int coluna) {
    return (tabuleiro[linha][coluna] == AGUA);
}

// Função para exibir o tabuleiro formatado
void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("\n=== TABULEIRO DE BATALHA NAVAL ===\n\n");

    // Cabeçalho de colunas
    printf("    ");
    for (int c = 0; c < TAM; c++) printf("%d ", c);
    printf("\n");

    for (int i = 0; i < TAM; i++) {
        printf("%2d | ", i); // Número da linha
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Função para posicionar um navio horizontal
void posicionarHorizontal(int tabuleiro[TAM][TAM], int linha, int colunaInicial) {
    if (colunaInicial + TAM_NAVIO <= TAM) {
        for (int i = 0; i < TAM_NAVIO; i++) {
            if (podePosicionar(tabuleiro, linha, colunaInicial + i))
                tabuleiro[linha][colunaInicial + i] = NAVIO;
        }
    }
}

// Função para posicionar um navio vertical
void posicionarVertical(int tabuleiro[TAM][TAM], int linhaInicial, int coluna) {
    if (linhaInicial + TAM_NAVIO <= TAM) {
        for (int i = 0; i < TAM_NAVIO; i++) {
            if (podePosicionar(tabuleiro, linhaInicial + i, coluna))
                tabuleiro[linhaInicial + i][coluna] = NAVIO;
        }
    }
}

// Função para posicionar navio na diagonal principal (↘)
void posicionarDiagonalPrincipal(int tabuleiro[TAM][TAM], int linhaInicial, int colunaInicial) {
    if (linhaInicial + TAM_NAVIO <= TAM && colunaInicial + TAM_NAVIO <= TAM) {
        for (int i = 0; i < TAM_NAVIO; i++) {
            if (podePosicionar(tabuleiro, linhaInicial + i, colunaInicial + i))
                tabuleiro[linhaInicial + i][colunaInicial + i] = NAVIO;
        }
    }
}

// Função para posicionar navio na diagonal secundária (↙)
void posicionarDiagonalSecundaria(int tabuleiro[TAM][TAM], int linhaInicial, int colunaInicial) {
    if (linhaInicial + TAM_NAVIO <= TAM && colunaInicial - (TAM_NAVIO - 1) >= 0) {
        for (int i = 0; i < TAM_NAVIO; i++) {
            if (podePosicionar(tabuleiro, linhaInicial + i, colunaInicial - i))
                tabuleiro[linhaInicial + i][colunaInicial - i] = NAVIO;
        }
    }
}

int main() {
    int tabuleiro[TAM][TAM];

    // --- 1. Inicializar o tabuleiro com 0 (água) ---
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tabuleiro[i][j] = AGUA;

    // --- 2. Posicionar quatro navios ---
    // Dois horizontais/verticais
    posicionarHorizontal(tabuleiro, 1, 2);   // Linha 1, colunas 2-4
    posicionarVertical(tabuleiro, 5, 7);     // Coluna 7, linhas 5-7

    // Dois diagonais
    posicionarDiagonalPrincipal(tabuleiro, 3, 1); // ↘ Começa em (3,1)
    posicionarDiagonalSecundaria(tabuleiro, 2, 8); // ↙ Começa em (2,8)

    // --- 3. Exibir o tabuleiro ---
    exibirTabuleiro(tabuleiro);

    return 0;
}