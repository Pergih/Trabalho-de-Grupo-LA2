#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>

int Conjunto (wchar_t *s) {
    setlocale(LC_CTYPE, "C.UTF-8");
    int i, numero;
    int l = wcslen(s);

    if(s[0] == '\0') { return 0; } // se ele colocar nada isto deveria acabar

    numero = s[0] % 16; 

    for(i = 1; i < l; i++)
    { 
        if (numero != s[i] % 16) { return 0; } // se ja tiver diferente do primeiro ja morre tudo e acaba
    }
    return l; 
}


int DSequencia (wchar_t *s) {
    setlocale(LC_CTYPE, "C.UTF-8");
    int r = 0; // o int que vai dar return
    int c = 1; // condição para o loop
    int l = wcslen(s);

    //verifica se a dupla sequencia tem pelo menos 6, pq e o minimo
    if (l < 6) return 0;


    
    if (s[0]%16 == s[1]%16) r++; // verifica se o primeiro par sao iguais

    for (int i = 2; i < l && c != 0; i += 2) {
        // neste loop vai verificar em cada posição par e o proximo se são iguais em termos de numeros e não de naipe
        if (s[i]%16 == s[i+1]%16 && (s[i-1]%16) + 1 == s[i]%16) r++; // verificar se sao seguidos
        else c = 0;                        // o C é uma codição para acabar o loop mais cedo
    }
    
    return c == 0 ? 0 : r;
}



int Sequencia(wchar_t *s)
{
    setlocale(LC_CTYPE, "C.UTF-8");
    int r = 0; // o int que vai dar return
    int c = 1; // condição para o loop
    int l = wcslen(s);

    // verifica se a dupla sequencia tem pelo menos 3, pq e o minimo
    if (l < 3)
        c = 0;

    int i;
    for (i = 0; i < l-1 && c != 0; i++)
    { // neste loop vai verificar se na mão ordenada a proxima carta é consecutiva da anterior
        if (s[i + 1]%16 == (s[i]%16 + 1))
            r++;
        else
            c = 0; // o C é uma codição para acabar o loop mais cedo
    }
    r++; // quando o loop acaba, verifica tambem o ultimo elemento contudo não incrementa

    return c == 0 ? 0 : r;
}
