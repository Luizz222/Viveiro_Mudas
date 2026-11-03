
#ifndef ARQUIVO_H
#define ARQUIVO_H
#include <stdio.h>

#include "Structs.h"
/* =================================================================
  Função ler um arquivo e colocar os dados dentro de uma avl e bst
  Parâmetros:
  1 - arquivo - Nome do arquivo que será lido
  2- raizBst - A raiz da arvore Bst, onde os dados serão armazenados
  3- raizAvl - A raiz da arvore Avl, onde os dados serão armazenados
 ===================================================================*/
void lerArquivo(char arquivo[100],No **raizBst,No **raizAvl);

#endif //ARARQUIVO_H