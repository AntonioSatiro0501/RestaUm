#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TAM 9
#define P 'o'

//Copia uma matriz no terminal
void printMatriz(char matriz[TAM][TAM]){

    for(int i =0; i < TAM; i++){
        for(int j = 0; j < TAM; j++){
            printf("%c", matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

//Verifica se o estado atual do jogo é a resposta
bool verificaResultado(char matriz[TAM][TAM], char resposta[TAM][TAM]){
    for(int i =0; i < TAM; i++){
        for(int j = 0; j< TAM; j++){
            if(matriz[i][j] != resposta[i][j]){
                return false;
            }
        }
    }
    return true;
}

//verifica se a jogada é ou não permitida
bool validaDirecao(int direcao, char matriz[TAM][TAM], int linha, int coluna){

    if(direcao == 0){ //jogada de peca vindo de cima para baixo
        if(linha - 2 >= 0){
            if(matriz[linha - 1][coluna] == P && matriz[linha - 2][coluna] == P){
                return true;
            }
        }
        return false;
    }
    if(direcao == 1){ //jogada de peca vindo de baixo para cima
        if(linha + 2 <= 8){
            if(matriz[linha + 1][coluna] == P && matriz[linha + 2][coluna] == P){
                return true;
            }
        }
        return false;
    }
    if(direcao == 2){ //jogada de peca vindo da esqueda pra direita
        if(coluna - 2 >= 0){
            if(matriz[linha][coluna - 1] == P && matriz[linha][coluna - 2] == P){
                return true;
            }
        }
        return false;
    }
    if(direcao == 3){ //jogada de peca vindo da direita pra esquerda
        if(coluna + 2 <= 8){
            if(matriz[linha][coluna + 1] == P && matriz[linha][coluna + 2] == P){
                return true;
            }
        }
        return false;
    }

    return false;
}

//altera o estado do tabuleiro baseado na direcao da jogada
void fazJogada(int direcao,char matriz[TAM][TAM], int linha,int coluna){

    if(direcao == 0){ 
        matriz[linha][coluna] = P;
        matriz[linha - 1][coluna] = ' '; 
        matriz[linha - 2][coluna] = ' ';
        return;
    }
    if(direcao == 1){
        matriz[linha][coluna] = P;
        matriz[linha + 1][coluna] = ' '; 
        matriz[linha + 2][coluna] = ' ';
        return;
    }
    if(direcao == 2){
        matriz[linha][coluna] = P;
        matriz[linha][coluna - 1] = ' ';
        matriz[linha][coluna - 2] = ' ';
        return;
    }
    if(direcao == 3){
        matriz[linha][coluna] = P;
        matriz[linha][coluna + 1] = ' '; 
        matriz[linha][coluna + 2] = ' ';
        return;
    }

}

//Valida se a posicao atual é um espaço vazio e se a jogada é válida
bool valida(int direcao, char matriz[TAM][TAM], int posicao){

    int linha = posicao/9;
    int coluna = posicao%9;

    //O programa procura pelos espacos vazios para a realizacao de jogadas
    if(matriz[linha][coluna] != ' '){
        return false;
    }

    if(validaDirecao(direcao,matriz,linha,coluna)){
        fazJogada(direcao, matriz, linha, coluna);
        printMatriz(matriz);
        return true;
    }

    return false;
}

//funcao recursiva para resolucao do jogo
void resolve(char matriz[TAM][TAM],char solucao[31][TAM][TAM], int jogada, char resposta[TAM][TAM]){
    
    //caso estejamos na jogada 31 e o estado atual do tabuleiro for coerente com a respota, fazemos o print do caminho das solucoes
    if(verificaResultado(matriz, resposta)){
        printf("\nSolucao\n");
        for(int i = 0; i < 31; i++){
            for(int j = 0; j < 9; j++){
                for(int k =0; k < 9; k++){
                    printf("%c", solucao[i][j][k]);
                }
                printf("\n");
            }
        }
        exit(0);
    }
    else if(jogada == 32){
        return;
    }
    
    for(int i = 0; i < 81; i++){
        for(int d = 0;d < 4; d++){
            if(valida(d,matriz,i)){
                for(int j = 0; j < 9; j++){
                    for(int k =0; k < 9; k++){
                        solucao[jogada][j][k] = matriz[j][k];
                    }
                }
                resolve(matriz,solucao,jogada + 1,resposta);

                for(int j = 0; j < 9; j++){
                    for(int k =0; k < 9; k++){
                        matriz[j][k] = solucao[jogada][j][k];
                    }
                }
            }
        }
    }
}

int main(){
    char solucao[31][TAM][TAM];
    char matriz[TAM][TAM] = {{'#','#','#','#','#','#','#','#','#'},
                             {'#','#','#','o','o','o','#','#','#'},
                             {'#','#','#','o','o','o','#','#','#'},
                             {'#','o','o','o','o','o','o','o','#'},
                             {'#','o','o','o',' ','o','o','o','#'},
                             {'#','o','o','o','o','o','o','o','#'},
                             {'#','#','#','o','o','o','#','#','#'},
                             {'#','#','#','o','o','o','#','#','#'},
                             {'#','#','#','#','#','#','#','#','#'}};

    char resposta[TAM][TAM] ={{'#','#','#','#','#','#','#','#','#'},
                             {'#','#','#',' ',' ',' ','#','#','#'},
                             {'#','#','#',' ',' ',' ','#','#','#'},
                             {'#',' ',' ',' ',' ',' ',' ',' ','#'},
                             {'#',' ',' ',' ','o',' ',' ',' ','#'},
                             {'#',' ',' ',' ',' ',' ',' ',' ','#'},
                             {'#','#','#',' ',' ',' ','#','#','#'},
                             {'#','#','#',' ',' ',' ','#','#','#'},
                             {'#','#','#','#','#','#','#','#','#'}};

    resolve(matriz,solucao,0,resposta);
}