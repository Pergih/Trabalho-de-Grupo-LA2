#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>
#include "Combinacao.h"
#include "Sort.h"

// output do exemplo de input 4 e 3 teste 2 tao errados




void testa(int testNumber);
void removeJogada (wchar_t *mao, wchar_t *jogada);
int validaJogada (wchar_t *jogada);
int Repetidas (wchar_t *s);
int contemCartas (wchar_t *mao, wchar_t *jogada);
void printMao(wchar_t *mao);

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
    int c = 1;
    int numPlays;
    wscanf(L"%d", &numPlays); // Numero de mãos/jogadas
    
    wchar_t mao[100]; // a mao do jogador
    wchar_t sorted[100];
    wscanf(L"%ls", mao);
    sortCartas (mao, wcslen(mao));
    
    wcscpy (sorted, mao);

    wchar_t jogada[100];
    for (int i = 0; i < numPlays; i++){

        wscanf (L"%ls", jogada);

        // verificar se jogou no turno errado e verificar se esta a ver a ultima jogada ou n
        sortCartas (jogada, wcslen(jogada));
        if (wcscmp (jogada, L"PASSO") != 0 && validaJogada (jogada) && jogada[0] != L'\0' && contemCartas (mao, jogada))removeJogada (mao, jogada);
    }    
    
    wscanf (L"%ls", jogada);
    sortCartas (jogada, wcslen(jogada));
    if (wcscmp (jogada, L"PASSO") != 0 && validaJogada (jogada) && jogada[0] != L'\0' && contemCartas (mao, jogada))removeJogada (mao, jogada); // jogada final
    else c = 0; // flag q o ultimo n foi possivel

    
    if (c == 0) {
        wcscpy (mao, sorted);
    }
    printMao (mao);
}

void removeJogada(wchar_t *mao, wchar_t *jogada) {
    wchar_t resultado[100]; // Array para armazenar a mao resultante apos a remoção
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
    if ((Conjunto(jogada) == 0 && DSequencia (jogada) == 0 && Sequencia (jogada) == 0)|| Repetidas(jogada)) return 0;
    else return 1;
}

int Repetidas (wchar_t *s) { // retorna 1 se existir repetidas
    for (int i = 0; s[i+1] != L'\0'; i++) {
        if (s[i] == s[i+1]) return 1; // repetiu-se
    }
    return 0; // nao existe repetida
}


int contemCartas(wchar_t *mao, wchar_t *jogada) {
    int i, j, contem;
    
    for (i = 0; jogada[i] != L'\0'; i++) {
        contem = 0;
        for (j = 0; mao[j] != L'\0'; j++) {
            // Se um caractere da jogada for encontrado na mao, marca contem como 1 e para a busca neste caractere
            if (jogada[i] == mao[j]) {
                contem = 1;
                break;
            }
        }
        // Se o caractere atual da jogada não estiver na mao, retorna 0
        if (!contem) {
            return 0;
        }
    }
    // Se todos os caracteres da jogada estiverem na mao, retorna 1
    return 1;
}

void printMao(wchar_t *mao) {
    int i;
    if (mao[0] != L'\0') { // Verifica se a mao não está vazia
        // Loop para imprimir os caracteres com um espaço entre eles
        for (i = 0; mao[i+1] != L'\0'; i++) {
            wprintf(L"%lc ", mao[i]);
        }
    wprintf(L"%lc\n", mao[i]); // Imprime o último caractere
    } else {
        wprintf(L"\n"); // Se a mao estiver vazia, imprime uma nova linha
    }
}