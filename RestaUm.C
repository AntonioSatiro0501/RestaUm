#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define TAM 9
#define P 'O'

bool validaDirecao(int direcao, char matriz[TAM][TAM], int linha, int coluna){

    if(direcao == 0){
        if(linha - 2 >= 0){
            if(matriz[linha - 1][coluna] == P && matriz[linha - 2][coluna] == P){
                return true;
            }
        }
        return false;
    }
    if(direcao == 1){
        if(linha + 2 <= 8){
            if(matriz[linha + 1][coluna] == P && matriz[linha + 2][coluna] == P){
                return true;
            }
        }
        return false;
    }
    if(direcao == 2){
        if(coluna - 2 >= 0){
            if(matriz[linha][coluna - 1] == P && matriz[linha - 2][coluna] == P){
                return true;
            }
        }
        return false;
    }
    if(direcao == 3){
        if(coluna + 2 <= 8){
            if(matriz[linha][coluna + 1] == P && matriz[linha][coluna + 2] == P){
                return true;
            }
        }
        return false;
    }

    return false;
}

char fazJogada(int direcao,char matriz[TAM][TAM], int linha,int coluna){

    char aux[TAM][TAM] = matriz;

    if(direcao == 0){
        aux[linha][coluna] = P;
        aux[linha - 1][coluna], aux[linha - 2][coluna] = ' ';
        return aux;
    }
    if(direcao == 1){
        aux[linha][coluna] = P;
        aux[linha + 1][coluna], aux[linha + 2][coluna] = ' ';
        return aux;
    }
    if(direcao == 2){
        aux[linha][coluna] = P;
        aux[linha][coluna - 1], aux[linha][coluna - 2] = ' ';
        return aux;
    }
    if(direcao == 3){
        aux[linha][coluna] = P;
        aux[linha][coluna + 1], aux[linha][coluna + 2] = ' ';
        return aux;
    }

}

bool valida(int direcao, char matriz[TAM][TAM], int posicao){

    int linha = posicao/9;
    int coluna = posicao % 9;

    if(matriz[linha][coluna] != ' '){
        return false;
    }

    if(validaDirecao(direcao,matriz,linha,coluna)){
        matriz = fazJogada(direcao, matriz, linha, coluna);
        return true;
    }

    return false;
}

