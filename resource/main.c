#include <stdio.h>
#include <string.h>
#include "../ libraries/Structs.h"
#include "../ libraries/Bst.h"
#include "../ libraries/Avl.h"


// Declarando as variáveis globais que estão no Avl.c
extern int contLL, contRR, contLR, contRL, visitados;

// Função auxiliar para criar uma muda padrão rapidamente
Muda criarMudaTeste(int lote) {
    Muda m;
    m.numero_lote = lote;
    strcpy(m.especie, "Ipe Amarelo");
    m.quantidade_mudas = 100;
    strcpy(m.data_germinacao, "01/10/2026");
    strcpy(m.status, "Em crescimento");
    return m;
}

// Função auxiliar para contar a quantidade total de nós na árvore
int contarNos(No *raiz) {
    if (raiz == NULL) return 0;
    return 1 + contarNos(raiz->esq) + contarNos(raiz->dir);
}

// Função auxiliar para imprimir o status atual formatado como exigido na Missão 3
void imprimirStatus(No *raiz, const char *mensagem) {
    int h = altura(raiz);
    int r = raiz ? raiz->muda.numero_lote : 0;
    int n = contarNos(raiz);
    int valida = ehAVL(raiz);

    if (mensagem != NULL && strlen(mensagem) > 0) {
        printf("%-28s -> altura: %d  raiz: %d  nos: %-2d | AVL valida: %s\n",
               mensagem, h, r, n, valida ? "SIM" : "NAO");
    } else {
        printf("Carga de 15 registros -> altura: %d | raiz: %d | nos: %d\n", h, r, n);
    }
}


int main() {
    int i;
    No *raizAvl = NULL;

    // 1. CARGA ASCENDENTE (1001 a 1015)
    zerarContadores();
    for (i = 1; i <= 15; i++) {
        raizAvl = inserir(raizAvl, criarMudaTeste(1000 + i));
    }

    printf("Carga ascendente 1001 ate 1015 -> ");
    imprimirContadores();

    // Testes de Faixa
    printf("Faixa 1004 a 1010: ");
    visitados = 0;
    listarFaixa(raizAvl, 1004, 1010);
    printf(" (%d nos visitados de 15)\n", visitados);

    printf("Faixa 1010 a 1020: ");
    visitados = 0;
    listarFaixa(raizAvl, 1010, 1020);
    printf(" (%d nos visitados de 15)\n", visitados);

    printf("Faixa 1100 a 1200: ");
    visitados = 0;
    listarFaixa(raizAvl, 1100, 1200);
    printf("nenhum registro (%d nos visitados de 15)\n", visitados);


    // Carga Descendente
    liberarArvore(raizAvl); // Limpa a árvore anterior
    raizAvl = NULL;
    zerarContadores();

    for (i = 15; i >= 1; i--) {
        raizAvl = inserir(raizAvl, criarMudaTeste(1000 + i));
    }

    printf("Carga descendente 1015 ate 1001 -> ");
    imprimirContadores();
    printf("altura: %d raiz: %d\n", altura(raizAvl), raizAvl->muda.numero_lote);

    // Testes zigue zague
    // Teste LR (1003, 1001, 1002)
    liberarArvore(raizAvl);
    raizAvl = NULL;
    zerarContadores();

    raizAvl = inserir(raizAvl, criarMudaTeste(1003));
    raizAvl = inserir(raizAvl, criarMudaTeste(1001));
    raizAvl = inserir(raizAvl, criarMudaTeste(1002));

    printf("Insercao 1003,1001,1002    -> ");
    imprimirContadores();
    printf("raiz: %d\n", raizAvl->muda.numero_lote);

    // Teste RL (1001, 1003, 1002)
    liberarArvore(raizAvl);
    raizAvl = NULL;
    zerarContadores();

    raizAvl = inserir(raizAvl, criarMudaTeste(1001));
    raizAvl = inserir(raizAvl, criarMudaTeste(1003));
    raizAvl = inserir(raizAvl, criarMudaTeste(1002));

    printf("Insercao 1001,1003,1002    -> ");
    imprimirContadores();
    printf("raiz: %d\n", raizAvl->muda.numero_lote);

    // Limpa a árvore antes da Missão 3
    liberarArvore(raizAvl);
    raizAvl = NULL;


    // ====================================================== MISSÃO 3 =================================================
    // -- Impressão conforme a MISSÃO 3 pede --
    printf("\n================================================= TESTE DA MISSAO 3 =================================================\n");

    // Recarrega os 15 registros (1001 a 1015) para os testes de remoção
    zerarContadores();
    for (i = 1; i <= 15; i++) {
        raizAvl = inserir(raizAvl, criarMudaTeste(1000 + i));
    }
    imprimirStatus(raizAvl, NULL);

    // Removeu 1001 (folha - Caso 1)
    raizAvl = remover(raizAvl, 1001);
    imprimirStatus(raizAvl, "Removeu 1001 (folha)");

    // Removeu 1002 (1 filho - Caso 2)
    raizAvl = remover(raizAvl, 1002);
    imprimirStatus(raizAvl, "Removeu 1002 (1 filho)");

    // Removeu 1008 (2 filhos - Caso 3)
    raizAvl = remover(raizAvl, 1008);
    imprimirStatus(raizAvl, "Removeu 1008 (2 filhos)");

    // Chave 1999 nao encontrada
    raizAvl = remover(raizAvl, 1999);
    imprimirStatus(raizAvl, "Chave 1999 nao encontrada");

    // Removeu 1013
    raizAvl = remover(raizAvl, 1013);
    imprimirStatus(raizAvl, "Removeu 1013");

    // Removeu 1015
    raizAvl = remover(raizAvl, 1015);
    imprimirStatus(raizAvl, "Removeu 1015");

    // Removeu 1014
    raizAvl = remover(raizAvl, 1014);
    imprimirStatus(raizAvl, "Removeu 1014");

    // Impressão final emOrdem dos nós restantes
    printf("\nemOrdem: ");
    emOrdem(raizAvl);
    printf("\n==============================================================================================================\n");

    // ================================================================================================================

    // Limpeza final
    liberarArvore(raizAvl);

    return 0;
}