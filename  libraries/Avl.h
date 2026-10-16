#ifndef AVL_H
#define AVL_H
#include "Structs.h"

/* =================================================================
  Função para criar um no da arvore
  Parâmetros:
  1 - muda - valor a ser inserido no nó
 ===================================================================*/
No* criarNo(Muda muda);

/* =================================================================
  Função para recalcular a altura de um nó
  Parâmetros:
  1 - n - ponteiro para de um nó da arvore
 ===================================================================*/
int altura(No *n);

/* =================================================================
  Função para caulcular o fator de balanceamento da arvore
  Parâmetros:
  1 - n - ponteiro para de um nó da arvore
 ===================================================================*/
int fb(No *n);


/* =================================================================
  Função para atualizar a altura do no
  Parâmetros:
  1 - n - ponteiro para de um nó da arvore
 ===================================================================*/
void atualizaAltura(No *n);

/* =================================================================
  Função para fazer a rotação a direita
  Parâmetros:
  1 - y - ponteiro que representa a raiz da arvore
 ===================================================================*/
No* rotacaoDireita(No *y);


/* =================================================================
  Função para fazer a rotação a esquerda
  Parâmetros:
  1 - y - ponteiro que representa a raiz da arvore
 ===================================================================*/
No* rotacaoEsquerda(No *x);
/* =================================================================
  Função para fazer a rotação a esquerda e depois a direita (rotação dupla)
  Parâmetros:
  1 - z - ponteiro que representa a raiz da arvore
 ===================================================================*/
No* rotacaoLR(No *z);

/* =================================================================
  Função para fazer a rotação a direita e depois a esquerda (rotação dupla)
  Parâmetros:
  1 - z - ponteiro que representa a raiz da arvore
 ===================================================================*/
No* rotacaoRL(No *z);


/* =================================================================
  Função para balancear a arvore
  Parâmetros:
  1 - raiz - ponteiro que representa a raiz da arvore
 ===================================================================*/
No* balancear(No *raiz);

/* =================================================================
  Função para inserir um novo nó na arvore
  Parâmetros:
  1 - raiz - ponteiro que representa a raiz da arvore
  2 - muda - valor a ser inserido no nó
 ===================================================================*/
No* inserir(No *raiz, Muda muda);

/* =================================================================
  Função para imprimir a arvore em ordem
  Parâmetros:
  1 - raiz - ponteiro que representa a raiz da arvore
 ===================================================================*/
void inOrder(No *raiz);

#endif //AVL_H