#include<stdio.h>
#include<string.h>
#include"../ libraries/Structs.h"
#include"../ libraries/Bst.h"
#include"../ libraries/Avl.h"


int main() {
    /*na BST  com 15 registros será percorrido 15 nós ja na AVl será apenas 4 nós.
     * Com 1000 registros uma busca na BST seria totalmente enviavel já que seriam percorridos 1000 nós
     */
    int i;
    No *raizAvl = NULL;
    No *raizBst = NULL;

    //BST


     //Carregamento de 15 registros com chave em ordem crescente (1001 a 1015)
    for (i = 1; i <= 15; i++) {
        Muda m;
        m.numero_lote = 1000 + i;
        strcpy(m.especie, "Ipe Amarelo");
        m.quantidade_mudas = 100 * i;
        strcpy(m.data_germinacao, "01/10/2026");
        strcpy(m.status, "Em crescimento");

        raizAvl = inserir(raizAvl, m);
        raizBst = inserirBst(raizBst,m);
    }

    // Impressão dos registros em ordem
    printf("--- Lista BST emOrdem ---\n");
    emOrdem(raizBst);
    printf("\n");

    printf("--- Lista AVL emOrdem ---\n");
    emOrdem(raizAvl);
    printf("\n");

    // Saída padrão exigida no documento
    printf("BST simples -> altura: %d\n", alturaBst(raizBst));
    printf("AVL simples -> altura: %d\n", altura(raizAvl));

    liberarArvore(raizBst);
    return 0;
}