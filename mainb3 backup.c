#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>
#include "Combinacao.h"
#include "Sort.h"

// fazer os casos especiais nos conjuntos



void verificaComMesa(wchar_t *mesa, wchar_t *mao);
int verificaJogada (wchar_t *mesa, wchar_t *jogada);
void testa(int testNumber);
void removeJogada (wchar_t *mao, wchar_t *jogada);
int validaJogada (wchar_t *jogada);
int Repetidas (wchar_t *s);
int contemCartas (wchar_t *mao, wchar_t *jogada);
void printMao(wchar_t *mao);
int conjuntoRei (wchar_t *jogada);
void verificaJogadaFinal (wchar_t *mao, wchar_t *jogada, wchar_t *mesa);

void print_seq (wchar_t *cartas, int indices[], int tamanho);
void removeMenores (wchar_t cmp, wchar_t *mesa);
int combinaConjuntos(int mesa, int mao, wchar_t* cartas);
void testaCombinaConjuntos(int mesa, int mao, wchar_t *cartas);
void combinaSequencia (int tamanho, wchar_t maior, wchar_t *cartas, int indices[]);
void initIndices (int tamanho, int indices[]);

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

    wchar_t mao[54]; // a mao do jogador
    wscanf (L"%ls", mao);
    sortCartas (mao, wcslen(mao));

    short int verificar_dsequencia; //vai verificar e vai ser o numero de cartas
    verificar_dsequencia = DSequencia (mesa); //0 se não for Dupla Sequencia, != 0 se é
    
    if (verificar_dsequencia) { // se a mesa for DSeq
        
    }

    short int verificar_sequencia = Sequencia (mesa);
    if (verificar_sequencia) { // se a mesa for Seq
        int indices[verificar_sequencia];
        initIndices (verificar_sequencia, indices);
        combinaSequencia (verificar_sequencia, mesa[verificar_sequencia-1], mao, indices);
    }

    short int verificar_conjunto = Conjunto (mesa);
    if (verificar_conjunto) { // se a mesa for Conj
        removeMenores (mesa[wcslen(mesa)-1], mao);
        testaCombinaConjuntos(verificar_conjunto, wcslen(mao), mao);
    }
    
    if (verificar_dsequencia == 0 && verificar_sequencia == 0 && verificar_conjunto == 0) {
        wprintf(L"Nada!\n");
    }
}

void initIndices (int tamanho, int indices[]) {
    for (int i = 0; i < tamanho; i++) {
        indices[i] = i;
    }
}

void print_seq (wchar_t *cartas, int indices[], int tamanho) {
    int i;
    for (i = 0; i < tamanho-1; i++) {
        wprintf (L"%lc ", cartas[indices[i]]);
    }
    wprintf (L"%lc\n", cartas[indices[i]]);
}

int indicesUltimo (wchar_t *cartas, int tamanho, int indices[]) {
    return 1; // ainda fase de teste


    int ultimo_seguidos = 1;
    int tudo_seguido = 1;
    for (int i = 0; i < tamanho - 1; i++) {
        if (indices[i] == indices[i+1] + 1) tudo_seguido++;
    }
    if (tudo_seguido == tamanho) return 1;
    for (int i = tamanho - 1; i - tamanho < 4; i--) {
        if (cartas[indices[i]]%16 == cartas[indices[i] - 1]%16) ultimo_seguidos++;
    }
    return 0;

}

int indicesReset (int tamanho, int indices[], int diferente, wchar_t *cartas) {
    if (indices[tamanho-1] == wcslen(cartas)) { //caso o ultimo indice ja e a ultima carta
            int t = indicesUltimo (cartas, tamanho, indices);
            if (t) return 1;
    }

    if (cartas[indices[diferente] + 1] != L'\0') indices[diferente]++;
    for (int i = diferente; i < tamanho; i++) {
        indices[i] = i;
    }
    return 0;
}

void combinaSequencia (int tamanho, wchar_t maior, wchar_t *cartas, int indices[]) {
    
    int diferente = 0;
    
    for (int i = 0; i < tamanho-1; i++) {
        if (cartas[indices[i]]%16 == (cartas[indices[i+1]]%16) - 1) diferente++;
        else break;
    }
    if (diferente == tamanho - 1 && compare (cartas + indices[tamanho-1], &maior) > 0) {
        print_seq (cartas, indices, tamanho);
        if (indices[tamanho - 1] != wcslen(cartas))indices[tamanho - 1]++;
        else return;
    }
    else {
        int t = indicesReset (tamanho, indices, diferente, cartas);
        if (t) return;
        combinaSequencia (tamanho, maior, cartas, indices);
    }


}


void testaCombinaConjuntos(int mesa, int mao, wchar_t *cartas) {
    int acc = 0, index = 0, i;
    for (i = 0; i < mao-1; i++) {
        if (cartas[i]%16 == cartas[i+1]%16) {
            acc++;
        }
        else {
            acc++;
            combinaConjuntos (mesa, acc, cartas + index);
            index += acc;
            acc = 0;
        }
    }
    if (cartas[i]%16 != cartas[i-1]%16) { // quado ela estiver isolada
        combinaConjuntos (mesa, 1, cartas+i);
    }
    else {
        acc++;
        combinaConjuntos (mesa, acc, cartas + index);
    }
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

void removeMenores (wchar_t cmp, wchar_t *mesa) {
    wchar_t temp[56];
    int c = 0, i;
    for (i = 0; compare (mesa+i, &cmp) < 0; i++) {
        if (mesa[i]%16 == cmp%16) {
            c = casoEspecial (cmp, mesa + i, temp);
            i += c;
            break;
        }
    }
    for (; mesa[i] != L'\0'; i++) {
        temp[c] = mesa[i];
        c++;
    }
    temp[c] = L'\0';
    wcscpy(mesa, temp);
}

// esta funçao aqui ja é pro guiao 4 é a aquela funçao que determina o conjunto.

int combinaConjuntos(int mesa, int mao, wchar_t* cartas){ //funçao horrivel!!! basicamente vem daquele 'brute forcing' que fizemos dia 19; 
                                                                //NOTA: o array tem que ter como primeiro indice o a primeira carta do conjunto!;

    if(mao == 0 || mesa == 0 || mesa > mao) {
        wprintf(L"PASSO\n");
        return 0; //aqui logo elimina todos os casos impossiveis;
    }

    if(mesa == 1){
        for(int i = 0; i < mao; i++){
            wprintf(L"%lc\n",cartas[i]);
            
        }
    }
    if(mesa == 2){
        if(mao == 2){
            wprintf(L"%lc %lc\n",cartas[0],cartas[1]);
        }
        if(mao == 3){
            wprintf(L"%lc %lc\n%lc %lc\n%lc %lc\n", 
            cartas[0], cartas[1], 
            cartas[0], cartas[2], 
            cartas[1], cartas[2]);

        }
        if(mao == 4){
            wprintf(L"%lc %lc\n%lc %lc\n%lc %lc\n%lc %lc\n%lc %lc\n%lc %lc\n", 
            cartas[0], cartas[1], 
            cartas[0], cartas[2], 
            cartas[0], cartas[3], 
            cartas[1], cartas[2], 
            cartas[1], cartas[3], 
            cartas[2], cartas[3]);

        }
    }
    if(mesa == 3){
        if(mao == 3){
            wprintf(L"%lc %lc %lc\n",cartas[0],cartas[1],cartas[2]);
        }
        if(mao == 4){
            wprintf(L"%lc %lc %lc\n%lc %lc %lc\n%lc %lc %lc\n%lc %lc %lc\n", 
            cartas[0], cartas[1], cartas[2], 
            cartas[0], cartas[1], cartas[3], 
            cartas[0], cartas[2], cartas[3], 
            cartas[1], cartas[2], cartas[3]);

        }
    }
    if(mesa == 4){
        wprintf(L"%lc %lc %lc %lc\n",cartas[0],cartas[1],cartas[2],cartas[3]);
    }

    return 1; //acaba a funçao gg ;
}


 


