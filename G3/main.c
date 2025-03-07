#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>
#include "Combinacao.h"
#include "Sort.h"

// output do exemplo de input 4 e 3 teste 2 tao errados


void testa2(int number, int *testNumber);
void verificaComMesa(wchar_t *mesa, wchar_t *mao, int numP);
int verificaJogada (wchar_t *mesa, wchar_t *jogada);
void testa(int *testNumber);
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
        testa(&i);
    }

    return 0;
}

void testa(int *testNumber) {
    wprintf(L"Teste %d\n", *testNumber); //print o numero do teste
    
    wchar_t mao[14]; // a mao do jogador


    int numP; //numero de jogadas anteriores 
    wscanf(L"%d", &numP);
    wchar_t mesa[28];
    verificaComMesa(mesa, mao, numP);
    



    wchar_t jogada[28];
    wscanf (L"%ls", jogada);

    wchar_t *endptr;
    long number = wcstol(jogada, &endptr, 10);

    if (number != 0) {
        wcsncpy (jogada, L"PASSO", 5);
    }
    else sortCartas (jogada, wcslen(jogada));

    verificaJogadaFinal (mao, jogada, mesa);

    printMao (mao);
    if (number != 0 && number < 200) {
        *testNumber = *testNumber + 1;
        testa2(number, testNumber);
    }
}

void testa2(int number, int *testNumber) {
    wprintf(L"Teste %d\n", *testNumber); //print o numero do teste
    
    wchar_t mao[28];
    wchar_t mesa[28];
    verificaComMesa(mesa, mao, number);
    



    wchar_t jogada[28];
    wscanf (L"%ls", jogada);

    wchar_t *endptr;
    number = wcstol(jogada, &endptr, 10);

    if (number != 0) {
        wcsncpy (jogada, L"PASSO", 5);
    }
    else sortCartas (jogada, wcslen(jogada));

    verificaJogadaFinal (mao, jogada, mesa);

    printMao (mao);
    if (number != 0 && number < 200) {
        *testNumber = *testNumber + 1;
        testa2(number, testNumber);
    }


}


void removeJogada(wchar_t *mao, wchar_t *jogada) {
    wchar_t resultado[28]; // Array para armazenar a mao resultante apos a remoção
    int i = 0, j = 0, k = 0;

    while (mao[i] != L'\0' && jogada[j] != L'\0') {
        int cmp = compare(&mao[i], &jogada[j]);

        if (cmp < 0) {
            resultado[k++] = mao[i++];
        } else if (cmp > 0) {
            j++; // Avançar para o próximo elemento na jogada
        } else {
            // Elementos são iguais, avançar para o próximo elemento em ambas as sequências
            i++;
            j++;
        }
    }


    while (mao[i] != L'\0') {
        resultado[k] = mao[i];
        i++;
        k++;
    }

    resultado[k] = L'\0'; 
    wcscpy(mao, resultado);
}

int validaJogada (wchar_t *jogada) {
    if ((Conjunto(jogada) == 0 && DSequencia (jogada) == 0 && Sequencia (jogada) == 0)) return 0;
    else return 1;
}



void verificaComMesa(wchar_t *mesa, wchar_t *mao, int numP) //isto aqui ja se pressupoe que a jogada é valida
{
    mesa[0] = '\0';
    

    wscanf(L"%ls", mao);
    sortCartas (mao, wcslen(mao)); // fica sorted

    int c = 0;
    wchar_t play[28];
    if (numP > 0) wscanf(L"%ls",mesa);
    sortCartas (mesa, wcslen(mesa));
    removeJogada (mao, play);

    for(int i = 0; i < numP-1; i++)
    {
        wscanf(L"%ls",play);
        int t = wcscmp(play, L"PASSO");
        
        if (t == 0) c++; // se é passo
        
        else if(verificaJogada (mesa, play) == 1) // se for valida
        {
            wcscpy(mesa, play);
            c = 0;
        }
        if (c == 3) mesa[0] = L'\0'; // se passou 3 vezes a mesa fica livre
        
        else if (verificaJogada (mesa, play) == 0 && t == 0) {
            c++;
        }
        else if (c == 4) {
            return;
        }
    }

    
    
    if (numP == 0 || c == 3)mesa[0] = L'\0';
    else sortCartas (mesa, wcslen(mesa));
}

void printMao(wchar_t *mao) {
    short int i;
    if (mao[0] != L'\0') { // Verifica se a mao não está vazia
        // Loop para imprimir os caracteres com um espaço entre eles
        for (i = 0; mao[i+1] != L'\0'; i++) {
            wprintf(L"%lc ", (wint_t)mao[i]);
        }
    wprintf(L"%lc\n", (wint_t)mao[i]); // Imprime o último caractere
    } else {
        wprintf(L"\n"); // Se a mao estiver vazia, imprime uma nova linha
    }
}

int conjuntoRei (wchar_t *jogada) {
    if (Conjunto (jogada) > 0 && jogada[0]%16 == 14) return 1;
    else return 0;
}

int sameType (wchar_t *mesa, wchar_t *jogada) {
    short int verificar, verificar2;

    verificar = DSequencia(mesa);
    verificar2 = DSequencia(jogada);

    if (verificar == verificar2 && verificar2 != 0) {
        return 1;
    }
    verificar = Sequencia(mesa); 
    verificar2 = Sequencia(jogada);

    if (verificar == verificar2 && verificar2 != 0) {
        return 1;
    }
    verificar = Conjunto(mesa);
    verificar2 = Conjunto(jogada);

    if (verificar == verificar2 && verificar2 != 0) {
        return 1;
    }
    return 0;
}

int verificaJogada (wchar_t *mesa, wchar_t *jogada) {
    if (wcscmp (jogada, L"PASSO") == 0) return 1;
    sortCartas (jogada, wcslen (jogada));
    if (validaJogada (jogada) == 0) return 0;
    if ((conjuntoRei(mesa) == 0 && sameType(jogada, mesa)) || ((conjuntoRei (mesa) && conjuntoRei (jogada)))) { // se nao for um conjunto de rei e se forem do mesmo tipo
        return 1;
    }
    else if (mesa[0] == L'\0') {
        return 1;
    }
    else if (conjuntoRei (mesa)){
        int c = Conjunto (mesa);
        if (c == 1) { // um rei na mesa
            if (Conjunto (jogada) == 4 || DSequencia (jogada) >= 3) { // se a jogada é um conjunto de 4 ou DSeq de 3
                return 1;
            }
            return 0;
        }
        else if (c == 2) {
            if (DSequencia (jogada) >= 4) {
                return 1;
            }
            return 0;
        }
        else if (c == 3) {
            if (DSequencia (jogada) >= 5) {
                return 1;
            }
            return 0;
        }
    }
    return 0;
}

void verificaJogadaFinal (wchar_t *mao, wchar_t *jogada, wchar_t *mesa) {
    if (validaJogada (jogada) == 0) return;
    else if (((conjuntoRei(mesa) == 0 && sameType(jogada, mesa)) && compare (&jogada[wcslen(jogada) - 1], &mesa[wcslen(mesa) - 1]) > 0) || mesa[0] == L'\0' || wcscmp (jogada, L"PASSO") == 0 || (conjuntoRei (mesa) && conjuntoRei (jogada))) { // se nao for um conjunto de rei e se forem do mesmo tipo
        removeJogada (mao, jogada);
        return;
    }
    else if (conjuntoRei (mesa)){
        int c = Conjunto (mesa);
        if (c == 1) { // um rei na mesa
            if (Conjunto (jogada) == 4 || DSequencia (jogada) == 3) { // se a jogada é um conjunto de 4 ou DSeq de 3
                removeJogada (mao, jogada);
                return;
            }
            return;
        }
        else if (c == 2) {
            if (DSequencia (jogada) == 4) {
                removeJogada (mao, jogada);
                return;
            }
            return;
        }
        else if (c == 3) {
            if (DSequencia (jogada) == 5) {
                removeJogada (mao, jogada);
                return;
            }
            return;
        }

    }
    return;
}

