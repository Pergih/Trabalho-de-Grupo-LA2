#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>
#include "Pedro.h"
#include "Ze.h"
#include "Joao.h"
#include "Luis.h"




int main () {
    
    setlocale(LC_CTYPE, "C.UTF-8");
    int n; // numero de inputs
    
    wscanf(L"%d", &n); //vai pegar o numero de testes

    wchar_t s[20];      // input original
    wchar_t sorted[20]; // input ordenado

    while (n > 0){
        wscanf (L"%ls", s);

        wcscpy (sorted, s); //ter duas strings, uma do input normal e uma que vai ser ordenada
        sortCartas (sorted, wcslen(sorted));
        short int maior; //indice da maior carta
        maior = (wcslen(sorted)-1); //o maior é o elemento mais a direita de uma string ordenada

        short int verificar; //vai verificar e vai ser o numero de cartas
        verificar = DSequencia (sorted); //0 se não for Dupla Sequencia, != 0 se é
        
        if (verificar) {
            wprintf (L"dupla sequência com %d cartas onde a carta mais alta é %lc\n", verificar, (unsigned long) sorted[maior]);
        }

        n--;
    }
    

    

    return 0;
}


