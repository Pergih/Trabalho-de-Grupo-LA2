#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>
#include "Combinacao.h"
#include "Sort.h"

// statements a mais no main


#define MAX_TESTS 30
#define MAX_SIZE 100


void processTest(int testNumber);
void printCardsInOrder(wchar_t s[][MAX_SIZE],wchar_t highest[] , int k); //funções auxiliares
int areAllEqual(short int arr[], int size);

int main() {
    setlocale(LC_CTYPE, "C.UTF-8");
    int numTests; 
    wscanf(L"%d", &numTests); //Numero de testes

    for (int i = 1; i <= numTests; i++) {
        processTest(i);
    }

    return 0;
}
//função proccessTest vai ao numero do teste e executa o teste correspondente
void processTest(int testNumber) {
    int numSets; 
    wprintf(L"Teste %d\n", testNumber); //print o numero do teste
    wscanf(L"%d", &numSets); // Numero de mãos/jogadas

    wchar_t s[MAX_TESTS][MAX_SIZE]; //lista original
    wchar_t highest[MAX_TESTS]; //lista das cartas maiores de cada mão
    short int verificar_dsequencia[MAX_TESTS];
    short int verificar_sequencia[MAX_TESTS];
    short int verificar_conjunto[MAX_TESTS];

    for (int i = 0; i < numSets; i++) {
        wscanf(L"%ls", s[i]);      //scan da jogada
        //falta aqui um sort, vou por mas vê depois pedro

        sortCartas(s[i], wcslen(s[i]));

        verificar_dsequencia[i] = DSequencia(s[i]); // vai por os valores se é alguma das combinacoes
        verificar_sequencia[i] = Sequencia(s[i]);
        verificar_conjunto[i] = Conjunto(s[i]);

        highest[i] = s[i][wcslen(s[i]) - 1]; // diz qual é a maior carta de cada jogada
    }

    if (areAllEqual(verificar_dsequencia, numSets) || // vai verificar se sao todos iguais exceto o zero
        areAllEqual(verificar_sequencia, numSets) ||
        areAllEqual(verificar_conjunto, numSets)) {
        printCardsInOrder(s, highest, numSets);
    }
    else {
        wprintf(L"Combinações não iguais!\n");
    }
}

void printCardsInOrder(wchar_t s[][MAX_SIZE], wchar_t highest[], int k) {
    short int v[k];
    find_indices(highest, k, v); // vai pegar os indices e ordena los por maior ate o menor

    for (int i = 0; i < k; i++) {
        int j;
        for (j = 0; s[v[k-i-1]][j+1] != '\0'; j++){ // loop para printar os chars com um ' ' no meio
            wprintf(L"%lc ", s[v[k-i-1]][j]);
        }
        wprintf(L"%lc\n", s[v[k-i-1]][j]);
    }
}

int areAllEqual(short int arr[], int size) {
    short int first = arr[0];
    if (first == 0) return 0;
    for (int i = 1; i < size; i++) {
        if (arr[i] != first || arr[i] == 0) {
            return 0; // nao sao todos iguais ou tem zeros
        }
    }
    return 1; // todos os elementos sao iguais
}


