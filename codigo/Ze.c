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
        if (s[i] != ' ')
        {;} // se for espaço isto aqui ignora 
        if (numero != s[i] % 16) { return 0; } // se ja tiver diferente do primeiro ja morre tudo e acaba
    }
    return l; 
}