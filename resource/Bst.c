/*
* Resposta à pergunta da missão1:
 * Os dados do sistema de viveiro de mudas tendem a chegar em ordem porque os lotes sao cadastrados sequencialmente no dia a dia.
 * Por exemplo, ao registrar lotes de mudas produzidos diariamente, o numero do lote e incrementado de forma automatica e crescente (1001, 1002, 1003...).
 */
#include<stdlib.h>
#include <stdio.h>
#include"../ libraries/Structs.h"
#include"../ libraries/Bst.h"

/* =================================================================
  Função para recalcular a altura de um nó: NULL = 0, folha = 1
  Parâmetros:
  1 - raiz - ponteiro para de um nó da arvore
 ===================================================================*/
int alturaBst(No *raiz) {
    int altEsq;
    int altDir;

    if (raiz == NULL) {
        return 0;
    }

    altEsq = alturaBst(raiz->esq);
    altDir = alturaBst(raiz->dir);

    if (altEsq > altDir) {
        return 1 + altEsq;
    } else {
        return 1 + altDir;
    }
}

/* =================================================================
  Função para criação do nó
  Parâmetros:
  1 - muda - valor que será inserido no nó
 ===================================================================*/
No* criarNoBst(Muda muda) {
    No *novo = (No*) malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro: sem memoria disponivel.\n");
        exit(1);
    }

    novo->muda = muda;
    novo->altura = 0; /* A BST simples não usa/atualiza este campo diretamente */
    novo->esq = NULL;
    novo->dir = NULL;

    return novo;
}

/* =================================================================
  Função para inserção simples sem rotação e sem balanceamento
  Parâmetros:
  1 - raiz - ponteiro indicando a raiz da árvore
  2 - muda - valor que será inserido no nó
 ===================================================================*/
No* inserirBst(No *raiz, Muda muda) {
    if (raiz == NULL) {
        return criarNoBst(muda);
    }

    if (muda.numero_lote < raiz->muda.numero_lote) {
        raiz->esq = inserirBst(raiz->esq, muda);
    } else if (muda.numero_lote > raiz->muda.numero_lote) {
        raiz->dir = inserirBst(raiz->dir, muda);
    }

    return raiz;
}

/* =================================================================
  Função para percurso em ordem para imprimir os registros da árvore
  Parâmetros:
  1 - raiz - ponteiro indicando a raiz da árvore
 ===================================================================*/
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
/* =================================================================
  Função para liberar o espaço acupado pela árvore
  Parâmetros:
  1 - raiz - ponteiro indicando a raiz da árvore
 ===================================================================*/
void liberarArvore(No *raiz) {
    if (raiz == NULL) {
        return;
    }
    liberarArvore(raiz->esq);
    liberarArvore(raiz->dir);
    free(raiz);
}

