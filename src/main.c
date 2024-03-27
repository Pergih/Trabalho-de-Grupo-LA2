#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include "Pedro.h"
#include "Ze.h"
#include "Joao.h"
#include "Luis.h"




int main () {
    
    setlocale(LC_CTYPE, "C.UTF-8");
    int n; // numero de inputs
    wscanf(L"%d", &n);   

    wchar_t s[100];


    while (n > 0){
        wscanf (L"%ls", s);
        DSequencia (s);


        n--;
    }
    

    

    return 0;
}


