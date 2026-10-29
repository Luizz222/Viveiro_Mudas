#include <stdio.h>
#include <string.h>
#include "../ libraries/Structs.h"
#include "../ libraries/Bst.h"
#include "../ libraries/Avl.h"

// Declarando as variáveis globais que estão no Avl.c
extern int contLL, contRR, contLR, contRL, visitados;

int main() {
    int i;
    No *raizAvl = NULL;

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

    // Limpeza final
    liberarArvore(raizAvl);
    return 0;
}