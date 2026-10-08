#include<stdio.h>
#include<string.h>
#include"resource/Structs.h"
#include"resource/Bst.h"


int main() {
    int i;
    No *raiz = NULL;

    /* Carregamento de 15 registros com chave em ordem crescente (1001 a 1015) */
    for (i = 1; i <= 15; i++) {
        Mudas m;
        m.numero_lote = 1000 + i;
        strcpy(m.especie, "Ipe Amarelo");
        m.quantidade_mudas = 100 * i;
        strcpy(m.data_germinacao, "01/10/2026");
        strcpy(m.status, "Em crescimento");

        raiz = inserir(raiz, m);
    }

    /* Impressão dos registros em ordem */
    printf("--- Lista emOrdem ---\n");
    emOrdem(raiz);
    printf("\n");

    /* Saída padrão exigida no documento */
    printf("BST simples -> altura: %d\n", altura(raiz));

    liberarArvore(raiz);
    return 0;
}