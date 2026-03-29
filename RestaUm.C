#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//escreve o Arquivo txt de resultados
void escreveArquivo(char solucao[32][9][9]){

    FILE *file = fopen("Resultados.txt", "w");

    fprintf(file, "\nSolucao\n");
        for (int i = 0; i < 32; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                for (int k = 0; k < 9; k++)
                {
                    fprintf(file,"%c", solucao[i][j][k]);
                }
                fprintf(file, "\n");
            }
            fprintf(file, "\n");
        }
    
    fclose(file);
}

// Copia uma matriz no terminal
void printMatriz(char matriz[9][9])
{

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            printf("%c", matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Verifica se o estado atual do jogo é a resposta
bool verificaResultado(char matriz[9][9])
{
    if ( matriz[4][4] == 'o'){
        return true;
    }
    return false;
}

// verifica se a jogada é ou não permitida
bool validaDirecao(int direcao, char matriz[9][9], int linha, int coluna)
{

    if (direcao == 0)
    { // jogada de peca vindo de cima para baixo
        if (linha - 2 >= 0)
        {
            if (matriz[linha - 1][coluna] == 'o' && matriz[linha - 2][coluna] == ' ')
            {
                return true;
            }
        }
        return false;
    }
    if (direcao == 1)
    { // jogada de peca vindo da direita pra esquerda
        if (coluna + 2 <= 8)
        {
            if (matriz[linha][coluna + 1] == 'o' && matriz[linha][coluna + 2] == ' ')
            {
                return true;
            }
        }
        return false;
    }

    if (direcao == 2)
    { // jogada de peca vindo de baixo para cima
        if (linha + 2 <= 8)
        {
            if (matriz[linha + 1][coluna] == 'o' && matriz[linha + 2][coluna] == ' ')
            {
                return true;
            }
        }
        return false;
    }

    if (direcao == 3)
    { // jogada de peca vindo da esqueda pra direita
        if (coluna - 2 >= 0)
        {
            if (matriz[linha][coluna - 1] == 'o' && matriz[linha][coluna - 2] == ' ')
            {
                return true;
            }
        }
        return false;
    }

    return false;
}

// altera o estado do tabuleiro baseado na direcao da jogada
void fazJogada(int direcao, char matriz[9][9], int linha, int coluna)
{

    if (direcao == 0)
    {
        matriz[linha][coluna] = ' ';
        matriz[linha - 1][coluna] = ' ';
        matriz[linha - 2][coluna] = 'o';
        return;
    }
    if (direcao == 1)
    {
        matriz[linha][coluna] = ' ';
        matriz[linha][coluna + 1] = ' ';
        matriz[linha][coluna + 2] = 'o';
        return;
    }
    if (direcao == 2)
    {

        matriz[linha][coluna] = ' ';
        matriz[linha + 1][coluna] = ' ';
        matriz[linha + 2][coluna] = 'o';
        return;
    }
    if (direcao == 3)
    {
        matriz[linha][coluna] = ' ';
        matriz[linha][coluna - 1] = ' ';
        matriz[linha][coluna - 2] = 'o';
        return;
    }
}

// Valida se a posicao atual é um espaço com pino e se a jogada é válida
bool valida(int direcao, char matriz[9][9], int posicao)
{

    int linha = posicao / 9;
    int coluna = posicao % 9;

    // O programa procura pelos espacos vazios para a realizacao de jogadas
    if (matriz[linha][coluna] != 'o')
    {
        return false;
    }

    if (validaDirecao(direcao, matriz, linha, coluna))
    {
        return true;
    }

    return false;
}

// funcao recursiva para resolucao do jogo
void resolve(char matriz[9][9], char solucao[32][9][9], int jogada)
{
    char backtrack[9][9];

    // caso estejamos na jogada 31 e o estado atual do tabuleiro for coerente com a respota, fazemos o print do caminho das solucoes
    if (jogada == 31 && verificaResultado(matriz))
    {

        memcpy(solucao[jogada], matriz, sizeof(backtrack));

        printf("\nSolucao\n");
        for (int i = 0; i < 32; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                for (int k = 0; k < 9; k++)
                {
                    printf("%c", solucao[i][j][k]);
                }
                printf("\n");
            }
            printf("\n");
        }
        escreveArquivo(solucao);
        exit(0);
    }
    else if (jogada == 31)
    {
        return;
    }

    
    memcpy(backtrack, matriz, sizeof(backtrack));
    memcpy(solucao[jogada], matriz, sizeof(backtrack));

    for (int i = 0; i < 81; i++)
    {
        if (matriz[i / 9][i % 9] != 'o')
        {
            continue;
        }

        for (int d = 0; d < 4; d++)
        {
            if (valida(d, matriz, i))
            {

                fazJogada(d, matriz, i / 9, i % 9);
                resolve(matriz, solucao, jogada + 1);

                memcpy(matriz, backtrack, sizeof(backtrack));
            }
        }
    }
}

int main()
{
    char solucao[32][9][9];
    char matriz[9][9] = {{'#', '#', '#', '#', '#', '#', '#', '#', '#'},
                         {'#', '#', '#', 'o', 'o', 'o', '#', '#', '#'},
                         {'#', '#', '#', 'o', 'o', 'o', '#', '#', '#'},
                         {'#', 'o', 'o', 'o', 'o', 'o', 'o', 'o', '#'},
                         {'#', 'o', 'o', 'o', ' ', 'o', 'o', 'o', '#'},
                         {'#', 'o', 'o', 'o', 'o', 'o', 'o', 'o', '#'},
                         {'#', '#', '#', 'o', 'o', 'o', '#', '#', '#'},
                         {'#', '#', '#', 'o', 'o', 'o', '#', '#', '#'},
                         {'#', '#', '#', '#', '#', '#', '#', '#', '#'}};


    resolve(matriz, solucao, 0);
}