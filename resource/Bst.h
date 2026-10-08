/*
* Resposta à pergunta da missão1:
 * Os dados do sistema de viveiro de mudas tendem a chegar em ordem porque os lotes sao cadastrados sequencialmente no dia a dia.
 * Por exemplo, ao registrar lotes de mudas produzidos diariamente, o numero do lote e incrementado de forma automatica e crescente (1001, 1002, 1003...).
 */
#include<stdlib.h>
#include"Structs.h"
#ifndef BST_H
#define BST_H

/* Função recursiva de altura conforme regra da missão: NULL = 0, folha = 1 */
int altura(No *raiz) {
    int altEsq;
    int altDir;

    if (raiz == NULL) {
        return 0;
    }

    altEsq = altura(raiz->esq);
    altDir = altura(raiz->dir);

    if (altEsq > altDir) {
        return 1 + altEsq;
    } else {
        return 1 + altDir;
    }
}

/* Criação do nó usando os ponteiros esq e dir do seu struct */
No* criarNo(Mudas muda) {
    No *novo = (No*) malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro: sem memoria disponivel.\n");
        exit(1);
    }

    novo->numero_lote = muda.numero_lote;
    novo->muda = muda;
    novo->altura = 0; /* A BST simples não usa/atualiza este campo diretamente */
    novo->esq = NULL;
    novo->dir = NULL;

    return novo;
}

/* Inserção simples sem rotação e sem balanceamento */
No* inserir(No *raiz, Mudas muda) {
    if (raiz == NULL) {
        return criarNo(muda);
    }

    if (muda.numero_lote < raiz->numero_lote) {
        raiz->esq = inserir(raiz->esq, muda);
    } else if (muda.numero_lote > raiz->numero_lote) {
        raiz->dir = inserir(raiz->dir, muda);
    }

    return raiz;
}

/* Percurso emOrdem para imprimir os registros da árvore */
void emOrdem(No *raiz) {
    if (raiz == NULL) {
        return;
    }

    emOrdem(raiz->esq);
    printf("Lote: %d | Especie: %s | Qtd: %d | Data: %s | Status: %s\n",
           raiz->muda.numero_lote,
           raiz->muda.especie,
           raiz->muda.quantidade_mudas,
           raiz->muda.data_germinacao,
           raiz->muda.status);
    emOrdem(raiz->dir);
}

void liberarArvore(No *raiz) {
    if (raiz == NULL) {
        return;
    }
    liberarArvore(raiz->esq);
    liberarArvore(raiz->dir);
    free(raiz);
}
#endif //BST_H
