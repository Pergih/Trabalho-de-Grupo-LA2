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

// funcao para chamar o qsort com o novo compare
void sortCartas(wchar_t *s, size_t n) {
    qsort(s, n, sizeof(wchar_t), compare);
}

int DSequencia (wchar_t *s) {
    setlocale(LC_CTYPE, "C.UTF-8");
    int r = 0; // o int que vai dar return
    int c = 1; // condição para o loop
    int l = wcslen(s);

    //verifica se a dupla sequencia tem pelo menos 6, pq e o minimo
    if (l < 6) c = 0;


    int i;
    for (i = 0; i < l && c != 0; i += 2) { // neste loop vai verificar em cada posição par e o proximo
        if (s[i]%16 == s[i+1]%16) r++;     // se são iguais em termos de numeros e não de naipe
        else c = 0;                        // o C é uma codição para acabar o loop mais cedo
    }
    
    return r;
}



