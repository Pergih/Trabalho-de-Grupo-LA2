#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>
#include "Combinacao.h"
#include "Sort.h"

// output do exemplo de input 4 e 3 teste 2 tao errados



void verificaComMesa(wchar_t *mesa, wchar_t *mao);
int verificaJogada (wchar_t *mesa, wchar_t *jogada);
void testa(int testNumber);
void removeJogada (wchar_t *mao, wchar_t *jogada);
int validaJogada (wchar_t *jogada);
int Repetidas (wchar_t *s);
int contemCartas (wchar_t *mao, wchar_t *jogada);
void printMao(wchar_t *mao);
int conjuntoRei (wchar_t *jogada);
void verificaJogadaFinal (wchar_t *mao, wchar_t *jogada, wchar_t *mesa);

int main() {
    setlocale(LC_CTYPE, "C.UTF-8");
    int numTests;
    wscanf(L"%d", &numTests); //Numero de testes

    for (int i = 1; i <= numTests; i++) {
        testa(i);
    }

    return 0;
}

void testa(int testNumber) {
    wprintf(L"Teste %d\n", testNumber); //print o numero do teste
    
    wchar_t mao[14]; // a mao do jogador

    wchar_t mesa[28];
    verificaComMesa(mesa, mao);

    wchar_t jogada[28];
    wscanf (L"%ls", jogada);
    sortCartas (jogada, wcslen(jogada));
    verificaJogadaFinal (mao, jogada, mesa);

    printMao (mao);
}



// esta funçao aqui ja é pro guiao 4 é a aquela funçao que determina o conjunto.

int combinaConjuntos(int mesa, int mao, wchar_t* cartas){ //funçao horrivel!!! basicamente vem daquele 'brute forcing' que fizemos dia 19; 
                                                                //NOTA: o array tem que ter como primeiro indice o a primeira carta do conjunto!;

    if(mao == 0 || mesa == 0 || mesa > mao) return 0; //aqui logo elimina todos os casos impossiveis;

    if(mesa == 1){
        for(int i = 0; i < mao; i++){
            wprintf(L"%lc\n",cartas[i]);
            return 1;
        }
    }
    if(mesa == 2){
        if(mao == 2){
            wprintf(L"%lc %lc\n",cartas[0],cartas[1]);
        }
        if(mao == 3){
            wprintf(L"%lc %lc\n",cartas[0],cartas[1]);
            wprintf(L"%lc %lc\n",cartas[0],cartas[2]);
            wprintf(L"%lc %lc\n",cartas[1],cartas[2]);
        }
        if(mao == 4){
            wprintf(L"%lc %lc\n",cartas[0],cartas[1]);
            wprintf(L"%lc %lc\n",cartas[0],cartas[2]);
            wprintf(L"%lc %lc\n",cartas[1],cartas[2]);
            wprintf(L"%lc %lc\n",cartas[0],cartas[3]);
            wprintf(L"%lc %lc\n",cartas[1],cartas[3]);
            wprintf(L"%lc %lc\n",cartas[2],cartas[3]);
            }
    }
    if(mesa == 3){
        if(mao == 3){
            wprintf(L"%lc %lc %lc\n",cartas[0],cartas[1],cartas[2]);
        }
        if(mao == 4){
            wprintf(L"%lc %lc %lc\n",cartas[0],cartas[1],cartas[2]);
            wprintf(L"%lc %lc %lc\n",cartas[0],cartas[1],cartas[3]);
            wprintf(L"%lc %lc %lc\n",cartas[0],cartas[2],cartas[3]);
            wprintf(L"%lc %lc %lc\n",cartas[1],cartas[2],cartas[3]);
        }
    }
    if(mesa == 4){
        wprintf(L"%lc %lc %lc %lc\n",cartas[0],cartas[1],cartas[2],cartas[3]);
    }

    return 1; //acaba a funçao gg ;
}


 


// esta funçao aqui ja é pro guiao 4 é a aquela funçao que determina o conjunto.

int combinaConjuntos(int mesa, int mao, wchar_t* cartas){ //funçao horrivel!!! basicamente vem daquele 'brute forcing' que fizemos dia 19; 
                                                                //NOTA: o array tem que ter como primeiro indice o a primeira carta do conjunto!;

    if(mao == 0 || mesa == 0 || mesa > mao) return 0; //aqui logo elimina todos os casos impossiveis;

    if(mesa == 1){
        for(int i = 0; i < mao; i++){
            wprintf(L"%lc\n",cartas[i]);
            
        }
    }
    if(mesa == 2){
        if(mao == 2){
            wprintf(L"%lc %lc\n",cartas[0],cartas[1]);
        }
        if(mao == 3){
            wprintf(L"%lc %lc\n",cartas[0],cartas[1]);
            wprintf(L"%lc %lc\n",cartas[0],cartas[2]);
            wprintf(L"%lc %lc\n",cartas[1],cartas[2]);
        }
        if(mao == 4){
            wprintf(L"%lc %lc\n",cartas[0],cartas[1]);
            wprintf(L"%lc %lc\n",cartas[0],cartas[2]);
            wprintf(L"%lc %lc\n",cartas[1],cartas[2]);
            wprintf(L"%lc %lc\n",cartas[0],cartas[3]);
            wprintf(L"%lc %lc\n",cartas[1],cartas[3]);
            wprintf(L"%lc %lc\n",cartas[2],cartas[3]);
            }
    }
    if(mesa == 3){
        if(mao == 3){
            wprintf(L"%lc %lc %lc\n",cartas[0],cartas[1],cartas[2]);
        }
        if(mao == 4){
            wprintf(L"%lc %lc %lc\n",cartas[0],cartas[1],cartas[2]);
            wprintf(L"%lc %lc %lc\n",cartas[0],cartas[1],cartas[3]);
            wprintf(L"%lc %lc %lc\n",cartas[0],cartas[2],cartas[3]);
            wprintf(L"%lc %lc %lc\n",cartas[1],cartas[2],cartas[3]);
        }
    }
    if(mesa == 4){
        wprintf(L"%lc %lc %lc %lc\n",cartas[0],cartas[1],cartas[2],cartas[3]);
    }

    return 1; //acaba a funçao gg ;
}


 


