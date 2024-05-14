#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include "Combinacao.h"
#include "Sort.h"

// Melhorias:
// quando a mesa não tem nada, fazer a melhor jogada
// quanto a minha mao é uma jogada valida, assim gg ez




void verificaComMesa(wchar_t *mesa, int numP);
void removeJogada (wchar_t *mao, wchar_t *jogada);
int verificaJogada (wchar_t *mesa, wchar_t *jogada);

void verificaJogadaFinal (wchar_t *mao, wchar_t *jogada, wchar_t *mesa);
void testa(int numJogadasAnt);
void testaRei (int verificar_conjunto, wchar_t *temp, int *flag, int *t);
int conjuntoRei (wchar_t *jogada);
void removeMenores (wchar_t cmp, wchar_t *mesa, int tamanho);
int casoEspecial (wchar_t cmp, wchar_t *mesa, wchar_t *dest);
void combinaConjuntos(int mesa, int mao, wchar_t* cartas, wchar_t results[][56], int *resultCount);
int testaCombinaConjuntos(int mesa, int mao, wchar_t *cartas);
void combinaSequencia (wchar_t mao[], wchar_t jogadas[], int inicio, int length, int index, int size, wchar_t maior, int *flag, wchar_t results[][56], int *resultCount);
void combinaDSequencia (wchar_t mao[], wchar_t jogadas[], int inicio, int length, int index, int size, wchar_t maior, int *flag, wchar_t results[][56], int *resultCount);
void testaConjunto (wchar_t *mao, wchar_t *mesa, int verificar_conjunto, int *flag);

void processaConjunto(wchar_t mao[], wchar_t mesa[], short int verificar_conjunto);
void processaDSequencia(wchar_t mao[], wchar_t mesa[], short int verificar_Dsequencia);
void processaSequencia(wchar_t mao[], wchar_t mesa[], short int verificar_sequencia);

void combinaQuatro(wchar_t* cartas, int mao, wchar_t results[][56], int *resultCount);
void combinaTres(wchar_t* cartas, int mao, wchar_t results[][56], int *resultCount);
void combinaDois(wchar_t* cartas, int mao, wchar_t results[][56], int *resultCount);
void combinaUm(wchar_t* cartas, int mao, wchar_t results[][56], int *resultCount);
int testaCombinaConjuntos2 (int mesa, int mao, wchar_t *cartas, wchar_t results[][56], int *resultCount);


int main() {
    setlocale(LC_CTYPE, "C.UTF-8");
    srand(time(NULL)); // Initialize random number generator
    int numJogadasAnt;
    wscanf(L"%d", &numJogadasAnt); // Numero de testes

    testa(numJogadasAnt);

    return 0;
}

void testa(int numJogadasAnt) {
    wchar_t mao[56]; // a mao do jogador
    wscanf (L"%ls", mao);
    sortCartas (mao, wcslen(mao));

    wchar_t mesa[28];
    verificaComMesa(mesa, numJogadasAnt);

    short int verificar_dsequencia = DSequencia (mesa); // vai verificar e vai ser o numero de cartas
    short int verificar_sequencia = Sequencia (mesa);
    short int verificar_conjunto = Conjunto (mesa);

    if (verificar_dsequencia)
        processaDSequencia(mao, mesa, verificar_dsequencia);
    else if (verificar_sequencia)
        processaSequencia(mao, mesa, verificar_sequencia);
    else if (verificar_conjunto)
        processaConjunto(mao, mesa, verificar_conjunto);
    else
        processaConjunto(mao, mesa, verificar_conjunto);
}

void processaDSequencia(wchar_t mao[], wchar_t mesa[], short int verificar_Dsequencia) {
    int flag = 0;
    wchar_t jogadas[14];
    wchar_t results[10000][56];
    int resultCount = 0;

    
    combinaDSequencia (mao, jogadas, 0, wcslen(mao) - 1, 0, verificar_Dsequencia, mesa[wcslen(mesa)-1], &flag, results, &resultCount);
    if (resultCount > 0) {
        int randomIndex = rand() % resultCount;
        wprintf(L"%ls", results[randomIndex]);
    } else {
        wprintf (L"PASSO\n");
    }
}

void processaSequencia(wchar_t mao[], wchar_t mesa[], short int verificar_sequencia) {
    int flag = 0;
    wchar_t jogadas[14];
    wchar_t results[10000][56];
    int resultCount = 0;
    combinaSequencia (mao, jogadas, 0, wcslen(mao) - 1, 0, verificar_sequencia, mesa[wcslen(mesa)-1], &flag, results, &resultCount);
    if (resultCount > 0) {
        int randomIndex = rand() % resultCount;
        wprintf(L"%ls", results[randomIndex]);
    } else {
        wprintf (L"PASSO\n");
    }
}

void processaConjunto(wchar_t mao[], wchar_t mesa[], short int verificar_conjunto) {
    int flag = 0;
    testaConjunto (mao, mesa, verificar_conjunto, &flag);
}


void verificaComMesa(wchar_t *mesa, int numP) {
    mesa[0] = '\0';

    int c = 0;
    wchar_t play[28];
    if (numP > 0) wscanf(L"%ls", mesa);
    sortCartas (mesa, wcslen(mesa));

    for(int i = 0; i < numP-1; i++) {
        wscanf(L"%ls", play);
        int t = wcscmp(play, L"PASSO");

        if (t == 0) c++; // se é passo

        else if(verificaJogada (mesa, play) == 1) { // se for valida
            wcscpy(mesa, play);
            c = 0;
        }
        if (c == 3) mesa[0] = L'\0'; // se passou 3 vezes a mesa fica livre

        else if (verificaJogada (mesa, play) == 0 && t == 0) {
            c++;
        }
        else if (c == 4) {
            return;
        }
    }

    if (numP == 0 || c == 3) mesa[0] = L'\0';
    else sortCartas (mesa, wcslen(mesa));
}

void removeJogada(wchar_t *mao, wchar_t *jogada) {
    wchar_t resultado[28]; // Array para armazenar a mao resultante apos a remoção
    int i = 0, j = 0, k = 0;

    while (mao[i] != L'\0' && jogada[j] != L'\0') {
        int cmp = compare(&mao[i], &jogada[j]);

        if (cmp < 0) {
            resultado[k++] = mao[i++];
        } else if (cmp > 0) {
            j++; // Avançar para o próximo elemento na jogada
        } else {
            // Elementos são iguais, avançar para o próximo elemento em ambas as sequências
            i++;
            j++;
        }
    }

    while (mao[i] != L'\0') {
        resultado[k] = mao[i];
        i++;
        k++;
    }

    resultado[k] = L'\0'; 
    wcscpy(mao, resultado);
}

int validaJogada (wchar_t *jogada) {
    if ((Conjunto(jogada) == 0 && DSequencia (jogada) == 0 && Sequencia (jogada) == 0)) return 0;
    else return 1;
}

int sameType (wchar_t *mesa, wchar_t *jogada) {
    short int verificar, verificar2;

    verificar = DSequencia(mesa);
    verificar2 = DSequencia(jogada);

    if (verificar == verificar2 && verificar2 != 0) {
        return 1;
    }
    verificar = Sequencia(mesa); 
    verificar2 = Sequencia(jogada);

    if (verificar == verificar2 && verificar2 != 0) {
        return 1;
    }
    verificar = Conjunto(mesa);
    verificar2 = Conjunto(jogada);

    if (verificar == verificar2 && verificar2 != 0) {
        return 1;
    }
    return 0;
}

int verificaJogada (wchar_t *mesa, wchar_t *jogada) {
    if (wcscmp (jogada, L"PASSO") == 0) return 1;
    sortCartas (jogada, wcslen (jogada));
    if (validaJogada (jogada) == 0) return 0;
    if ((conjuntoRei(mesa) == 0 && sameType(jogada, mesa)) || ((conjuntoRei (mesa) && conjuntoRei (jogada)))) {
        return 1;
    }
    else if (mesa[0] == L'\0') {
        return 1;
    }
    else if (conjuntoRei (mesa)){
        int c = Conjunto (mesa);
        if (c == 1) {
            if (Conjunto (jogada) == 4 || DSequencia (jogada) >= 3) {
                return 1;
            }
            return 0;
        }
        else if (c == 2) {
            if (DSequencia (jogada) >= 4) {
                return 1;
            }
            return 0;
        }
        else if (c == 3) {
            if (DSequencia (jogada) >= 5) {
                return 1;
            }
            return 0;
        }
    }
    return 0;
}

void testaConjunto (wchar_t *mao, wchar_t *mesa, int verificar_conjunto, int *flag) {
    wchar_t temp[56];
    wcscpy (temp, mao);

    removeMenores (mesa[wcslen(mesa)-1], mao, verificar_conjunto);

    int t = testaCombinaConjuntos(verificar_conjunto, wcslen(mao), mao);
    if (conjuntoRei (mesa)) {
        testaRei (verificar_conjunto, temp, flag, &t);
        wcscpy (mao, temp);
    }
    else if ((t || mao[0] == L'\0')) wprintf (L"PASSO\n");
}

void testaRei (int verificar_conjunto, wchar_t *temp, int *flag, int *t) {
    wchar_t jogadas[14];
    wchar_t results[10000][56];
    int resultCount = 0;
    if (verificar_conjunto == 1) {
        int alt = testaCombinaConjuntos2 (4, wcslen(temp), temp, results, &resultCount);
        combinaDSequencia (temp, jogadas, 0, wcslen(temp) - 1, 0, 6, 0, flag, results, &resultCount);
        if (alt == 0) *t = alt;
    } else if (verificar_conjunto == 2) {
        combinaDSequencia (temp, jogadas, 0, wcslen(temp) - 1, 0, 8, 0, flag, results, &resultCount);
    } else if (verificar_conjunto == 3) {
        combinaDSequencia (temp, jogadas, 0, wcslen(temp) - 1, 0, 10, 0, flag, results, &resultCount);
    }

    if (resultCount > 0) {
        wcscpy (results[resultCount], L"PASSO\n");
        resultCount++;
        int randomIndex = rand() % resultCount;
        wprintf(L"%ls \n---%ls", results[randomIndex], temp);
        removeJogada (temp, results[randomIndex]);
    }
    else wprintf (L"PASSO\n");

}

int testaCombinaConjuntos2 (int mesa, int mao, wchar_t *cartas, wchar_t results[][56], int *resultCount) {
    int acc = 0, index = 0, i;
    
    for (i = 0; i < mao-1; i++) {
        if (cartas[i]%16 == cartas[i+1]%16) {
            acc++;
        } else {
            acc++;
            combinaConjuntos(mesa, acc, cartas + index, results, resultCount);
            index += acc;
            acc = 0;
        }
    }
    if (cartas[i]%16 != cartas[i-1]%16) { // Quando ela estiver isolada
        combinaConjuntos(mesa, 1, cartas+i, results, resultCount);
    } else {
        acc++;
        combinaConjuntos(mesa, acc, cartas + index, results, resultCount);
    }

    return 1;
}

int conjuntoRei (wchar_t *jogada) {
    if (Conjunto (jogada) > 0 && jogada[0]%16 == 14) return 1;
    else return 0;
}

void combinaDSequencia (wchar_t mao[], wchar_t jogadas[], int inicio, int length, int index, int size, wchar_t maior, int *flag, wchar_t results[][56], int *resultCount) {
    if (index == size && compare(jogadas + size - 1, &maior) > 0){
        wchar_t result[56] = L"";
        *flag = 1;
        int i;
        for (i = 0; i < size-1; i++) {
            swprintf(result + wcslen(result), 56 - wcslen(result), L"%lc ", jogadas[i]);
        }
        swprintf(result + wcslen(result), 56 - wcslen(result), L"%lc\n", jogadas[i]);
        wcscpy(results[(*resultCount)++], result);
        return;
    }

    for (int i = inicio; i <= length && length - i + 1 >= size - index; i++) {
        if ((index == 0 || (jogadas[index - 1] %16 == jogadas[index - 2]%16 && 
            mao[i]%16 == jogadas[index - 1]%16 + 1 && mao[i + 1]%16 == jogadas[index - 1]%16 + 1))) {
            jogadas[index] = mao[i];
            jogadas[index + 1] = mao[i + 1];
            combinaDSequencia(mao, jogadas, i + 1, length, index + 1, size, maior, flag, results, resultCount);
        }
        if ((index == 0 || (jogadas[index - 1] %16 == jogadas[index - 2]%16 && 
            mao[i]%16 == jogadas[index - 1]%16 + 1 && mao[i + 2]%16 == jogadas[index - 1]%16 + 1)) && i + 2 <= length) {
            jogadas[index] = mao[i];
            jogadas[index + 1] = mao[i + 2];
            combinaDSequencia(mao, jogadas, i + 1, length, index + 1, size, maior, flag, results, resultCount);
        }
        if ((index == 0 || (jogadas[index - 1] %16 == jogadas[index - 2]%16 && 
            mao[i]%16 == jogadas[index - 1]%16 + 1 && mao[i + 3]%16 == jogadas[index - 1]%16 + 1)) && i + 3 <= length) {
            jogadas[index] = mao[i];
            jogadas[index + 1] = mao[i + 3];
            combinaDSequencia(mao, jogadas, i + 1, length, index + 1, size, maior, flag, results, resultCount);
        }
    }
}
void combinaSequencia (wchar_t mao[], wchar_t jogadas[], int inicio, int length, int index, int size, wchar_t maior, int *flag, wchar_t results[][56], int *resultCount) {
    if (index == size && compare(jogadas + size - 1, &maior) > 0) {
        wchar_t result[56] = L"";
        *flag = 1;
        int i;
        for (i = 0; i < size-1; i++) {
            swprintf(result + wcslen(result), 56 - wcslen(result), L"%lc ", jogadas[i]);
        }
        swprintf(result + wcslen(result), 56 - wcslen(result), L"%lc\n", jogadas[i]);
        wcscpy(results[(*resultCount)++], result);
        return;
    }

    for (int i = inicio; i <= length && length - i + 1 >= size - index; i++) {
        if (index == 0 || mao[i] % 16 == (jogadas[index - 1] % 16 )+ 1) {
            jogadas[index] = mao[i];
            combinaSequencia(mao, jogadas, i + 1, length, index + 1, size, maior, flag, results, resultCount);
        }
    }
}

void removeMenores (wchar_t cmp, wchar_t *mao, int tamanho) {
    wchar_t temp[56];
    int c = 0, i;
    for (i = 0; compare (mao+i, &cmp) < 0 && mao[i] != L'\0'; i++) {
        if (mao[i]%16 == cmp%16 && tamanho > 1 && (cmp/16)%16 != 13) {
            c = casoEspecial (cmp, mao + i, temp);
            i += c;
            break;
        }
    }
    for (; mao[i] != L'\0'; i++) {
        temp[c] = mao[i];
        c++;
    }
    temp[c] = L'\0';
    wcscpy(mao, temp);
}

int casoEspecial (wchar_t cmp, wchar_t *mesa, wchar_t *dest) {
    int naipeCmp = (cmp/16) %16;

    int seguidos = 0;
    if (naipeCmp == 13) return 0;
    else {
        for (int i = 0; mesa[i+1] != L'\0'; i++) {
            if (mesa[i]%16 == mesa[i+1]%16) {
                seguidos++;
            }
            else break;
        }
        seguidos++;

        if ((mesa[seguidos - 1]/16)%16 < naipeCmp) return 0;
        for (int i = 0; i < seguidos; i++) {
            dest[i] = mesa[i];
        }
    }
    dest[seguidos] = L'\0';
    return seguidos;
}

int testaCombinaConjuntos(int mesa, int mao, wchar_t *cartas) {
    int acc = 0, index = 0, i;
    wchar_t results[10000][56]; // Adjust the size if needed
    int resultCount = 0;
    
    for (i = 0; i < mao-1; i++) {
        if (cartas[i]%16 == cartas[i+1]%16) {
            acc++;
        } else {
            acc++;
            combinaConjuntos(mesa, acc, cartas + index, results, &resultCount);
            index += acc;
            acc = 0;
        }
    }
    if (cartas[i]%16 != cartas[i-1]%16) { // Quando ela estiver isolada
        combinaConjuntos(mesa, 1, cartas+i, results, &resultCount);
    } else {
        acc++;
        combinaConjuntos(mesa, acc, cartas + index, results, &resultCount);
    }

    if (resultCount > 0) {
        wcscpy (results[resultCount], L"PASSO\n");
        resultCount++;
        int randomIndex = rand() % resultCount;
        wprintf(L"%ls", results[randomIndex]);
        removeJogada (cartas, results[randomIndex]);
        return 0;
    }

    return 1;
}

void combinaConjuntos(int mesa, int mao, wchar_t* cartas, wchar_t results[][56], int *resultCount) {
    if (mao == 0 || mesa == 0 || mesa > mao || cartas[0] == L'\0') {
        return; // Eliminate all impossible cases
    }

    switch (mesa) {
        case 1:
            combinaUm(cartas, mao, results, resultCount);
            break;
        case 2:
            combinaDois(cartas, mao, results, resultCount);
            break;
        case 3:
            combinaTres(cartas, mao, results, resultCount);
            break;
        case 4:
            combinaQuatro(cartas, mao, results, resultCount);
            break;
        default:
            // Handle invalid mesa value
            break;
    }
}

void combinaUm(wchar_t* cartas, int mao, wchar_t results[][56], int *resultCount) {
    for (int i = 0; i < mao; i++) {
        swprintf(results[(*resultCount)++], 56, L"%lc\n", cartas[i]);
    }
}

void combinaDois(wchar_t* cartas, int mao, wchar_t results[][56], int *resultCount) {
    if (mao == 2) {
        swprintf(results[(*resultCount)++], 56, L"%lc %lc\n", cartas[0], cartas[1]);
    } else if (mao == 3) {
        swprintf(results[(*resultCount)++], 56, L"%lc %lc\n", cartas[0], cartas[1]);
        swprintf(results[(*resultCount)++], 56, L"%lc %lc\n", cartas[0], cartas[2]);
        swprintf(results[(*resultCount)++], 56, L"%lc %lc\n", cartas[1], cartas[2]);
    } else if (mao == 4) {
        swprintf(results[(*resultCount)++], 56, L"%lc %lc\n", cartas[0], cartas[1]);
        swprintf(results[(*resultCount)++], 56, L"%lc %lc\n", cartas[0], cartas[2]);
        swprintf(results[(*resultCount)++], 56, L"%lc %lc\n", cartas[0], cartas[3]);
        swprintf(results[(*resultCount)++], 56, L"%lc %lc\n", cartas[1], cartas[2]);
        swprintf(results[(*resultCount)++], 56, L"%lc %lc\n", cartas[1], cartas[3]);
        swprintf(results[(*resultCount)++], 56, L"%lc %lc\n", cartas[2], cartas[3]);
    }
}

void combinaTres(wchar_t* cartas, int mao, wchar_t results[][56], int *resultCount) {
    if (mao == 3) {
        swprintf(results[(*resultCount)++], 56, L"%lc %lc %lc\n", cartas[0], cartas[1], cartas[2]);
    } else if (mao == 4) {
        swprintf(results[(*resultCount)++], 56, L"%lc %lc %lc\n", cartas[0], cartas[1], cartas[2]);
        swprintf(results[(*resultCount)++], 56, L"%lc %lc %lc\n", cartas[0], cartas[1], cartas[3]);
        swprintf(results[(*resultCount)++], 56, L"%lc %lc %lc\n", cartas[0], cartas[2], cartas[3]);
        swprintf(results[(*resultCount)++], 56, L"%lc %lc %lc\n", cartas[1], cartas[2], cartas[3]);
    }
}

void combinaQuatro(wchar_t* cartas, int mao, wchar_t results[][56], int *resultCount) {
    if (mao == 4) {
        swprintf(results[(*resultCount)++], 56, L"%lc %lc %lc %lc\n", cartas[0], cartas[1], cartas[2], cartas[3]);
    }
}

