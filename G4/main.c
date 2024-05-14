#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>
#include "Combinacao.h"
#include "Sort.h"

// fazer os casos especiais nos conjuntos

void verificaJogadaFinal (wchar_t *mao, wchar_t *jogada, wchar_t *mesa);
void testa(int testNumber);
void testaRei (int verificar_conjunto, wchar_t *temp, int *flag, int *t);
int conjuntoRei (wchar_t *jogada);
void removeMenores (wchar_t cmp, wchar_t *mesa, int tamanho);
int casoEspecial (wchar_t cmp, wchar_t *mesa, wchar_t *dest);
int combinaConjuntos(int mesa, int mao, wchar_t* cartas);
int testaCombinaConjuntos(int mesa, int mao, wchar_t *cartas);
void combinaSequencia (wchar_t mao[], wchar_t jogadas[], int inicio, int length, int index, int size, wchar_t maior, int *flag);
void combinaDSequencia (wchar_t mao[], wchar_t jogadas[], int inicio, int length, int index, int size, wchar_t maior, int *flag);
void testaConjunto (wchar_t *mao, wchar_t *mesa, int verificar_conjunto, int *flag);


int main() {
    setlocale(LC_CTYPE, "C.UTF-8");
    int numTests;
    wscanf(L"%d", &numTests); //Numero de testes

    for (int i = 1; i <= numTests; i++) {
        testa(i);
    }

    return 0;
}

void testa(int testNumber) {
    wprintf(L"Teste %d\n", testNumber); //print o numero do teste
    
    
    wchar_t mesa[28];
    wscanf (L"%ls", mesa);
    sortCartas (mesa, wcslen(mesa));

    wchar_t mao[56]; // a mao do jogador
    wscanf (L"%ls", mao);
    sortCartas (mao, wcslen(mao));

    short int verificar_dsequencia; //vai verificar e vai ser o numero de cartas
    verificar_dsequencia = DSequencia (mesa); //0 se não for Dupla Sequencia, != 0 se é

    short int verificar_sequencia = Sequencia (mesa);

    short int verificar_conjunto = Conjunto (mesa);

    int flag = 0;
    if (verificar_dsequencia) { // se a mesa for DSeq
        wchar_t jogadas[14];
        combinaDSequencia (mao, jogadas, 0, wcslen(mao) - 1, 0, verificar_dsequencia * 2, mesa[wcslen(mesa)-1], &flag);
        if (flag == 0) wprintf (L"PASSO\n");
    }

    
    else if (verificar_sequencia) { // se a mesa for Seq
        wchar_t jogadas[14];
        combinaSequencia (mao, jogadas, 0, wcslen(mao) - 1, 0, verificar_sequencia, mesa[wcslen(mesa)-1], &flag);
        if (flag == 0) wprintf (L"PASSO\n");
    }

    
    else if (verificar_conjunto) { // se a mesa for Conj
        testaConjunto (mao, mesa, verificar_conjunto, &flag);
    }
    
    else if (verificar_dsequencia == 0 && verificar_sequencia == 0 && verificar_conjunto == 0) {
        wprintf(L"Nada!\n");
    }
}

void testaConjunto (wchar_t *mao, wchar_t *mesa, int verificar_conjunto, int *flag) {
    wchar_t temp[56];
        wcscpy (temp, mao);
        removeMenores (mesa[wcslen(mesa)-1], mao, verificar_conjunto);
        int t = testaCombinaConjuntos(verificar_conjunto, wcslen(mao), mao);
        if (conjuntoRei (mesa)) {
            testaRei (verificar_conjunto, temp, flag, &t);
        }
        else if ((t || mao[0] == L'\0')) wprintf (L"PASSO\n");
}

void testaRei (int verificar_conjunto, wchar_t *temp, int *flag, int *t) {
    wchar_t jogadas[14];
    if (verificar_conjunto == 1) {
        //conjunto de 4 e dseqs
        int alt = testaCombinaConjuntos (4, wcslen(temp), temp);
        combinaDSequencia (temp, jogadas, 0, wcslen(temp) - 1, 0, 6, 0, flag);
        if (alt == 0) *t = alt;
       
    }
    else if (verificar_conjunto == 2)  {
        combinaDSequencia (temp, jogadas, 0, wcslen(temp) - 1, 0, 8, 0, flag);
    }
    else if (verificar_conjunto == 3) combinaDSequencia (temp, jogadas, 0, wcslen(temp) - 1, 0, 10, 0, flag);
    if (*flag == 0 && *t) wprintf (L"PASSO\n");
}

int conjuntoRei (wchar_t *jogada) {
    if (Conjunto (jogada) > 0 && jogada[0]%16 == 14) return 1;
    else return 0;
}

void combinaDSequencia (wchar_t mao[], wchar_t jogadas[], int inicio, int length, int index, int size, wchar_t maior, int *flag) {
    if (index == size && compare(jogadas + size - 1, &maior) > 0) {
        // Print the combination
        *flag = 1;
        int i;
        for (i = 0; i < size - 1; i++) {
            wprintf(L"%lc ", jogadas[i]);
        }
        wprintf(L"%lc\n", jogadas[i]);
        return;
    }

    // vai gerar recursivamente
    for (int i = inicio; i <= length && length - i + 1 >= size - index; i++) {
        // verificar
        if ((index == 0 || (jogadas[index - 1] %16 == jogadas[index - 2]%16 && // pares iguais
            mao[i]%16 == jogadas[index - 1]%16 + 1 && mao[i + 1]%16 == jogadas[index - 1]%16 + 1))) {
            jogadas[index] = mao[i];
            jogadas[index + 1] = mao[i + 1];
            combinaDSequencia(mao, jogadas, i + 2, length, index + 2, size, maior, flag);
        }
        if ((index == 0 || (jogadas[index - 1] %16 == jogadas[index - 2]%16 && // pares iguais
            mao[i]%16 == jogadas[index - 1]%16 + 1 && mao[i + 2]%16 == jogadas[index - 1]%16 + 1))&& i + 2 <= length) {
            jogadas[index] = mao[i];
            jogadas[index + 1] = mao[i + 2];
            combinaDSequencia(mao, jogadas, i + 2, length, index + 2, size, maior, flag);
        }
        if ((index == 0 || (jogadas[index - 1] %16 == jogadas[index - 2]%16 && // pares iguais
            mao[i]%16 == jogadas[index - 1]%16 + 1 && mao[i + 3]%16 == jogadas[index - 1]%16 + 1)) && i + 3 <= length) {
            jogadas[index] = mao[i];
            jogadas[index + 1] = mao[i + 3];
            combinaDSequencia(mao, jogadas, i + 2, length, index + 2, size, maior, flag);
        }
    }
}


void combinaSequencia (wchar_t mao[], wchar_t jogadas[], int inicio, int length, int index, int size, wchar_t maior, int *flag) {
    if (index == size && compare(jogadas + size - 1, &maior) > 0) { // com esta condicao, nunca vai ser printada de inicio
        // Printa a combinacao
        *flag = 1;
        int i;
        for (i = 0; i < size-1; i++) {
            wprintf(L"%lc ", jogadas[i]);
        }
        wprintf(L"%lc\n", jogadas[i]);
        return;
    }

    // Vai gerar recursivamente
    for (int i = inicio; i <= length && length - i + 1 >= size - index; i++) {
        
        if (index == 0 || mao[i] % 16 == (jogadas[index - 1] % 16 )+ 1) {
            // caso base e verifica se é seguido no que ja esta na mao
            jogadas[index] = mao[i];
            combinaSequencia(mao, jogadas, i + 1, length, index + 1, size, maior, flag);
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
    int acc = 0, index = 0, i, t = 1, alt;
    for (i = 0; i < mao-1; i++) {
        if (cartas[i]%16 == cartas[i+1]%16) {
            acc++;
        }
        else {
            acc++;
            alt = combinaConjuntos (mesa, acc, cartas + index);
            if (alt == 0) t = alt;
            index += acc;
            acc = 0;
        }
    }
    if (cartas[i]%16 != cartas[i-1]%16) { // quado ela estiver isolada
        alt = combinaConjuntos (mesa, 1, cartas+i);
        if (alt == 0) t = alt;
    }
    else {
        acc++;
        alt = combinaConjuntos (mesa, acc, cartas + index);
        if (alt == 0) t = alt;
    }
    return t;
}





// esta funçao aqui ja é pro guiao 4 é a aquela funçao que determina o conjunto.

int combinaConjuntos(int mesa, int mao, wchar_t* cartas){ //funçao horrivel!!! basicamente vem daquele 'brute forcing' que fizemos dia 19; 
                        //NOTA: o array tem que ter como primeiro indice o a primeira carta do conjunto!;
    if(mao == 0 || mesa == 0 || mesa > mao || cartas[0] == L'\0') {
        return 1; //aqui logo elimina todos os casos impossiveis;
    }
    
    if(mesa == 1){
        for(int i = 0; i < mao; i++){
            wprintf(L"%lc\n",cartas[i]);
        }
        return 0;
    }
    if(mesa == 2){
        if(mao == 2){
            wprintf(L"%lc %lc\n",cartas[0],cartas[1]);
            return 0;
        }
        if(mao == 3){
            wprintf(L"%lc %lc\n%lc %lc\n%lc %lc\n", 
            cartas[0], cartas[1], 
            cartas[0], cartas[2], 
            cartas[1], cartas[2]);
            return 0;

        }
        if(mao == 4){
            wprintf(L"%lc %lc\n%lc %lc\n%lc %lc\n%lc %lc\n%lc %lc\n%lc %lc\n", 
            cartas[0], cartas[1], 
            cartas[0], cartas[2], 
            cartas[0], cartas[3], 
            cartas[1], cartas[2], 
            cartas[1], cartas[3], 
            cartas[2], cartas[3]);
            return 0;
        }
    }
    if(mesa == 3){
        if(mao == 3){
            wprintf(L"%lc %lc %lc\n",cartas[0],cartas[1],cartas[2]);
            return 0;
        }
        if(mao == 4){
            wprintf(L"%lc %lc %lc\n%lc %lc %lc\n%lc %lc %lc\n%lc %lc %lc\n", 
            cartas[0], cartas[1], cartas[2], 
            cartas[0], cartas[1], cartas[3], 
            cartas[0], cartas[2], cartas[3], 
            cartas[1], cartas[2], cartas[3]);
            return 0;
        }
    }
    if(mesa == 4){
        wprintf(L"%lc %lc %lc %lc\n",cartas[0],cartas[1],cartas[2],cartas[3]);
        return 0;
    }

    return 1; //acaba a funçao gg ;
}


 


