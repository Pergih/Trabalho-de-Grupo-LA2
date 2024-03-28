#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>

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
