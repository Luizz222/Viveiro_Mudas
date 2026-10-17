#include <stdio.h>
#include <string.h>
#include "../ libraries/Structs.h"
#include "../ libraries/Bst.h"
#include "../ libraries/Avl.h"
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

    
    // ====================================================== MISSÃO 3 =================================================
    // -- Impressão conforme a MISSÃO 3 pede --
    printf ("\n================================================= TESTE DA MISSAO 3 =================================================\n");
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
    inOrder(raizAvl);
    printf("==============================================================================================================\n");

    // ================================================================================================================
    
    return 0;
}