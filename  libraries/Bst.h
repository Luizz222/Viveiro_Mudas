/*
* Resposta à pergunta da missão1:
 * Os dados do sistema de viveiro de mudas tendem a chegar em ordem porque os lotes sao cadastrados sequencialmente no dia a dia.
 * Por exemplo, ao registrar lotes de mudas produzidos diariamente, o numero do lote e incrementado de forma automatica e crescente (1001, 1002, 1003...).
 */
#ifndef BST_H
#define BST_H

#include <stdlib.h>
#include "Structs.h"

/* =================================================================
  Função para recalcular a altura de um nó: NULL = 0, folha = 1
  Parâmetros:
  1 - raiz - ponteiro para de um nó da arvore
 ===================================================================*/
int alturaBst(No *raiz);

/* =================================================================
  Função para criação do nó
  Parâmetros:
  1 - muda - valor que será inserido no nó
 ===================================================================*/
No* criarNoBst(Muda muda);

/* =================================================================
  Função para inserção simples sem rotação e sem balanceamento
  Parâmetros:
  1 - raiz - ponteiro indicando a raiz da árvore
  2 - muda - valor que será inserido no nó
 ===================================================================*/
No* inserirBst(No *raiz, Muda muda);

/* =================================================================
  Função para percurso em ordem para imprimir os registros da árvore
  Parâmetros:
  1 - raiz - ponteiro indicando a raiz da árvore
 ===================================================================*/
void emOrdem(No *raiz);

/* =================================================================
  Função para liberar o espaço acupado pela árvore
  Parâmetros:
  1 - raiz - ponteiro indicando a raiz da árvore
 ===================================================================*/
void liberarArvore(No *raiz);

#endif //BST_H