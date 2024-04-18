#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>

#define MAX_COLS 100


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

// funcao para chamar o qsort com o novo compare
void sortCartas(wchar_t *s, size_t n) {
    qsort(s, n, sizeof(wchar_t), compare);
}

void find_indices(wchar_t m[], int N, short int v[]) {
    wchar_t temp[N];
    wcscpy (temp, m);

    sortCartas (temp, N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++){
            if (temp[N-i-1] == m[j]) v[i] = j; // vai guardar o indice do maior
        }
    }
}






