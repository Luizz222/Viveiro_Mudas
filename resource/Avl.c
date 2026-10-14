#include<stdlib.h>
#include<stdio.h>
#include"../ libraries/Structs.h"
#include "../ libraries/Avl.h"




/* =================================================================
  Função para recalcular a altura de um nó
  Parâmetros:
  1 - n - ponteiro para de um nó da arvore
 ===================================================================*/
int altura(No *n) {
    return n ? n->altura : 0;
}

/* =================================================================
  Função para caulcular o fator de balanceamento da arvore
  Parâmetros:
  1 - n - ponteiro para de um nó da arvore
 ===================================================================*/
int fb(No *n) {
    return n ? altura(n->esq) - altura(n->dir) : 0;
}


/* =================================================================
  Função para atualizar a altura do no
  Parâmetros:
  1 - n - ponteiro para de um nó da arvore
 ===================================================================*/
void atualizaAltura(No *n) {
    if (n) {
        int ae = altura(n->esq);
        int ad = altura(n->dir);
        n->altura = 1 + (ae > ad ? ae : ad);
    }
}


/* =================================================================
  Função para fazer a rotação a direita
  Parâmetros:
  1 - y - ponteiro que representa a raiz da arvore
 ===================================================================*/
No* rotacaoDireita(No *y) {
    No *x  = y->esq;   /* x é o filho esquerdo — vai subir        */
    No *T2 = x->dir;   /* T2 é o filho direito de x — muda de pai */

    /* --- o giro acontece aqui --- */
    x->dir = y;        /* y desce: vira filho DIREITO de x        */
    y->esq = T2;       /* T2 passa a ser filho esquerdo de y      */

    /* atualiza alturas: y primeiro pois agora está ABAIXO de x */
    atualizaAltura(y);
    atualizaAltura(x);

    return x;   /* x é a nova raiz desta subárvore */
}


/* =================================================================
  Função para fazer a rotação a esquerda
  Parâmetros:
  1 - y - ponteiro que representa a raiz da arvore
 ===================================================================*/
No* rotacaoEsquerda(No *x) {

    No *y  = x->dir;   /* y é o filho direito — vai subir         */
    No *T2 = y->esq;   /* T2 é o filho esquerdo de y — muda de pai */

    /* --- o giro acontece aqui --- */
    y->esq = x;        /* x desce: vira filho ESQUERDO de y       */
    x->dir = T2;       /* T2 passa a ser filho direito de x       */

    /* atualiza alturas: x primeiro pois agora está ABAIXO de y */
    atualizaAltura(x);
    atualizaAltura(y);

    return y;   /* y é a nova raiz desta subárvore */
}

/* =================================================================
  Função para fazer a rotação a esquerda e depois a direita (rotação dupla)
  Parâmetros:
  1 - z - ponteiro que representa a raiz da arvore
 ===================================================================*/
No* rotacaoLR(No *z) {
    z->esq = rotacaoEsquerda(z->esq);   /* passo 1: gira o filho esquerdo */
    return rotacaoDireita(z);            /* passo 2: gira a raiz           */
}


/* =================================================================
  Função para fazer a rotação a direita e depois a esquerda (rotação dupla)
  Parâmetros:
  1 - z - ponteiro que representa a raiz da arvore
 ===================================================================*/
No* rotacaoRL(No *z) {
    z->dir = rotacaoDireita(z->dir);    /* passo 1: gira o filho direito  */
    return rotacaoEsquerda(z);           /* passo 2: gira a raiz           */
}



No* balancear(No *raiz) {
    if (raiz == NULL) {
        return NULL;
    }
    atualizaAltura(raiz);
    int Fb = fb(raiz);
    

}



