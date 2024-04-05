#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>
#include "Combinacao.h"
#include "Sort.h"

// statements a mais no main


int main () {
    
    setlocale(LC_CTYPE, "C.UTF-8");
    int n; // numero de inputs
    
    wscanf(L"%d", &n); //vai pegar o numero de testes

    wchar_t s[10][100];      // input original
    wchar_t sorted[10][100]; // input ordenado
    int c = 1;

    while (n > 0){       
        int m;
        wscanf (L"%d", &m);
        short int verificar_dsequencia[10];
        short int verificar_sequencia[10];
        short int verificar_conjunto[10];
        wchar_t maiores[10];

        wprintf (L"Teste %d\n", c); // o c é um contador
        
        int k = m;

        while (m > 0) {    
            wscanf (L"%ls", s[m-1]);
            
            wcscpy (sorted[m-1], s[m-1]);
            sortCartas (sorted[m-1], wcslen(sorted[m-1]));

            maiores[m-1] = sorted[m-1][(wcslen(sorted[m-1])-1)];

            
            verificar_dsequencia[m-1] = DSequencia (sorted[m-1]);
            verificar_sequencia[m-1] = Sequencia (sorted[m-1]);
            verificar_conjunto[m-1] = Conjunto (sorted[m-1]);
            m--;
        }

        long unsigned int primeiro = wcslen(sorted[0]);
        int mesmo_tamanho = 1;

        for (int i = 1; i < k; i++) {
            if (wcslen(sorted[i]) != primeiro) {
                mesmo_tamanho = 0;
            }
        }

        
        if (mesmo_tamanho == 0) {
            wprintf (L"Combinações não iguais!\n");
        }

        else {
            short int v[k];
            find_indices(maiores, k, v); // vai guardar no v os indices do maior ate o menor combinacao
            for (int i = 0; i < k; i++) {
                for (int j = 0; s[v[k-i-1]][j] != '\0'; j++){ // loop para printar os chars com um ' ' no meio
                    wprintf(L"%lc ", s[v[k-i-1]][j]);
                }
                wprintf(L"\n");
            }
        }
        c++;
        n--;
    }
    

    

    return 0;
}


