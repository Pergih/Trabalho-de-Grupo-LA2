#include <stdio.h>
#include <wchar.h>
#include <locale.h>

int DSequencia (wchar_t *s) {
    setlocale(LC_CTYPE, "C.UTF-8");
    wprintf (L"%ls\n", s);
    return 2;
}



