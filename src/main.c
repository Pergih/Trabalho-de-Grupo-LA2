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
    wscanf(L"%d", &n);   

    wchar_t s[100];
    wchar_t sorted[100];
    wcscpy (sorted, s);


    while (n > 0){
        wscanf (L"%ls", s);
        sortCartas (sorted, wcslen(s));
        DSequencia (sorted);


        n--;
    }
    

    

    return 0;
}


