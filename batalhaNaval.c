#include <stdio.h>

#define TAM 10       // Tamanho do tabuleiro principal (10x10)
#define TAM_HAB 5    // Tamanho das matrizes de habilidade (5x5)
#define AGUA 0       // Representa água
#define NAVIO 3      // Representa navio
#define HABILIDADE 5 // Representa área afetada pela habilidade

// ---------- FUNÇÃO: Inicializa o tabuleiro com água ----------
void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// ---------- FUNÇÃO: Exibe o tabuleiro formatado ----------
void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("\n=== TABULEIRO DE BATALHA NAVAL ===\n\n");
    printf("    ");
    for (int c = 0; c < TAM; c++) printf("%d ", c);
    printf("\n");

    for (int i = 0; i < TAM; i++) {
        printf("%2d | ", i);
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j] == AGUA) printf("~ ");      // Água
            else if (tabuleiro[i][j] == NAVIO) printf("# "); // Navio
            else if (tabuleiro[i][j] == HABILIDADE) printf("* "); // Habilidade
        }
        printf("\n");
    }
}

// ---------- FUNÇÃO: Cria uma matriz de habilidade tipo CONE ----------
void criarCone(int cone[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            // A lógica cria uma forma triangular (cone apontando para baixo)
            if (j >= (TAM_HAB / 2 - i) && j <= (TAM_HAB / 2 + i))
                cone[i][j] = 1;
            else
                cone[i][j] = 0;
        }
    }
}

// ---------- FUNÇÃO: Cria uma matriz de habilidade tipo CRUZ ----------
void criarCruz(int cruz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (i == TAM_HAB / 2 || j == TAM_HAB / 2)
                cruz[i][j] = 1;
            else
                cruz[i][j] = 0;
        }
    }
}

// ---------- FUNÇÃO: Cria uma matriz de habilidade tipo OCTAEDRO ----------
void criarOctaedro(int octaedro[TAM_HAB][TAM_HAB]) {
    int centro = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            // Distância de Manhattan até o centro (forma de losango)
            int distancia = abs(i - centro) + abs(j - centro);
            if (distancia <= centro)
                octaedro[i][j] = 1;
            else
                octaedro[i][j] = 0;
        }
    }
}

// ---------- FUNÇÃO: Sobrepõe a matriz de habilidade no tabuleiro ----------
void aplicarHabilidade(int tabuleiro[TAM][TAM], int habilidade[TAM_HAB][TAM_HAB], int origemLinha, int origemColuna) {
    int centro = TAM_HAB / 2;

    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            // Calcula posição correspondente no tabuleiro
            int linha = origemLinha - centro + i;
            int coluna = origemColuna - centro + j;

            // Garante que a posição está dentro dos limites
            if (linha >= 0 && linha < TAM && coluna >= 0 && coluna < TAM) {
                if (habilidade[i][j] == 1 && tabuleiro[linha][coluna] == AGUA)
                    tabuleiro[linha][coluna] = HABILIDADE;
            }
        }
    }
}

// ---------- FUNÇÃO: Posiciona navios simples (para referência visual) ----------
void posicionarNavios(int tabuleiro[TAM][TAM]) {
    // Navio horizontal
    for (int j = 2; j < 5; j++)
        tabuleiro[2][j] = NAVIO;

    // Navio vertical
    for (int i = 6; i < 9; i++)
        tabuleiro[i][5] = NAVIO;
}

// ---------- PROGRAMA PRINCIPAL ----------
int main() {
    int tabuleiro[TAM][TAM];
    int cone[TAM_HAB][TAM_HAB];
    int cruz[TAM_HAB][TAM_HAB];
    int octaedro[TAM_HAB][TAM_HAB];

    // 1. Inicializa tabuleiro e navios
    inicializarTabuleiro(tabuleiro);
    posicionarNavios(tabuleiro);

    // 2. Cria as matrizes de habilidades
    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octaedro);

    // 3. Aplica habilidades em diferentes pontos do tabuleiro
    aplicarHabilidade(tabuleiro, cone, 1, 4);       // Cone próximo ao topo
    aplicarHabilidade(tabuleiro, cruz, 5, 5);       // Cruz no centro
    aplicarHabilidade(tabuleiro, octaedro, 8, 8);   // Octaedro no canto inferior

    // 4. Exibe tabuleiro final
    exibirTabuleiro(tabuleiro);

    return 0;
}