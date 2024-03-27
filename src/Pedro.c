#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>

// Função Compare para o qsort
int compare(const void *a, const void *b) {
    const wchar_t wchar_a = *(const wchar_t *)a;
    const wchar_t wchar_b = *(const wchar_t *)b;

    // converte o wchar_t para int e pega o ulimo digito (Numero)
    int digito_a = wchar_a % 16;
    int digito_b = wchar_b % 16;

    // CComapra os ultimos digitos
    if (digito_a < digito_b)
        return -1;
    else if (digito_a > digito_b)
        return 1;
    else {
        // se os ultimos digitos sao iguais, compara o penultimo digito (Naipe)
        int pdigito_a = wchar_a / 16 % 16;
        int pdigito_b = wchar_b / 16 % 16;

        if (pdigito_a < pdigito_b)
            return -1;
        else if (pdigito_a > pdigito_b)
            return 1;
        else
            return 0;
    }
}

// Function to sort an array of wchar_t using qsort
void sortCartas(wchar_t *s, size_t n) {
    // Call qsort to sort the array
    qsort(s, n, sizeof(wchar_t), compare);
}

int DSequencia (wchar_t *s) {
    setlocale(LC_CTYPE, "C.UTF-8");
    int r = 0;
    wprintf (L"%ls\n", s);
    
    
    
    
    return r;
}



