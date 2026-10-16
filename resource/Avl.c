#include<stdlib.h>
#include<stdio.h>
#include"../ libraries/Structs.h"
#include "../ libraries/Avl.h"


/* =================================================================
  Função para criar um no da arvore
  Parâmetros:
  1 - muda - valor a ser inserido no nó
 ===================================================================*/
No* criarNo(Muda muda) {
    No *novo = (No*) malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro: sem memoria disponivel.\n");
        exit(1);
    }

    novo->muda = muda;
    novo->esq    = NULL;
    novo->dir    = NULL;
    novo->altura = 1;    /* folha recém-criada tem altura 1 */
    return novo;
}



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





/* =================================================================
  Função para balancear a arvore
  Parâmetros:
  1 - raiz - ponteiro que representa a raiz da arvore
 ===================================================================*/
No* balancear(No *raiz) {
    if (raiz == NULL) {
        return NULL;
    }
    atualizaAltura(raiz);
    int Fb = fb(raiz);
    int Fbe = fb(raiz->esq);
    int Fbd = fb(raiz->dir);
    if (Fb ==2 && Fbe >=0) {
        raiz = rotacaoDireita(raiz);
    }
    else if (Fb ==-2 && Fbd <=0) {
        raiz = rotacaoEsquerda(raiz);
    }
    else if (Fb == 2 && Fbe <0) {
        raiz = rotacaoLR(raiz);
    }
    else if (Fb == -2 && Fbd >0) {
        raiz = rotacaoRL(raiz);
    }

    return raiz;

}



/* =================================================================
  Função para inserir um novo nó na arvore
  Parâmetros:
  1 - raiz - ponteiro que representa a raiz da arvore
  2 - muda - valor a ser inserido no nó
 ===================================================================*/
No* inserir(No *raiz, Muda muda) {

    /* --- Passo 1: inserção normal de BST --- */
    if (raiz == NULL)
        return criarNo(muda);

    if (muda.numero_lote < raiz->muda.numero_lote)
        raiz->esq = inserir(raiz->esq, muda);
    else if (muda.numero_lote > raiz->muda.numero_lote)
        raiz->dir = inserir(raiz->dir, muda);
    else
        return raiz;   /* duplicata — ignora */

    /* --- Passo 2: atualiza altura deste nó --- */
    atualizaAltura(raiz);

    /* --- Passo 3: verifica FB e rotaciona se necessário --- */
    int f = fb(raiz);

    /* LL: pesado à esquerda, inserção no filho esquerdo do filho esquerdo */
    if (f > 1 && muda.numero_lote < raiz->esq->muda.numero_lote)
        return rotacaoDireita(raiz);

    /* RR: pesado à direita, inserção no filho direito do filho direito */
    if (f < -1 && muda.numero_lote > raiz->dir->muda.numero_lote)
        return rotacaoEsquerda(raiz);

    /* LR: pesado à esquerda, inserção no filho direito do filho esquerdo */
    if (f > 1 && muda.numero_lote > raiz->esq->muda.numero_lote)
        return rotacaoLR(raiz);

    /* RL: pesado à direita, inserção no filho esquerdo do filho direito */
    if (f < -1 && muda.numero_lote < raiz->dir->muda.numero_lote)
        return rotacaoRL(raiz);

    return raiz;   /* sem rotação necessária */
}

/* =================================================================
  Função para imprimir a arvore em ordem
  Parâmetros:
  1 - raiz - ponteiro que representa a raiz da arvore
 ===================================================================*/
void inOrder(No *raiz) {
    if (raiz == NULL) return;
    inOrder(raiz->esq);
    printf("Lote: %d | Especie: %s | Qtd: %d | Data: %s | Status: %s\n",
          raiz->muda.numero_lote,
          raiz->muda.especie,
          raiz->muda.quantidade_mudas,
          raiz->muda.data_germinacao,
          raiz->muda.status);
    inOrder(raiz->dir);
}








