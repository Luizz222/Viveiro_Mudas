#include<stdlib.h>
#include<stdio.h>
#include <direct.h>
#include "../ libraries/Arquivo.h"

#include "../ libraries/Avl.h"
#include "../ libraries/Bst.h"
#include "../ libraries/Structs.h"


/* =================================================================
  Função ler um arquivo e colocar os dados dentro de uma avl e bst
  Parâmetros:
  1 - arquivo - Nome do arquivo que será lido
  2- raizBst - A raiz da arvore Bst, onde os dados serão armazenados
  3- raizAvl - A raiz da arvore Avl, onde os dados serão armazenados
 ===================================================================*/
void lerArquivo(char arquivo[100],No **raizBst,No **raizAvl) {
    int compAvl =0, compBst = 0;
    char linha[300];
    int lidos,reg=0;
    FILE *arq = fopen(arquivo,"r");
    if (arq == NULL) {
        char pasta[260];
        perror("Erro ao abrir dados.txt");
        printf("Pasta atual: %s\n", _getcwd(pasta, sizeof(pasta)));
        printf("O arquivo nao existe\n");
        exit(1);
    }

    while (fgets(linha,sizeof(linha),arq) != NULL) {

        Muda muda;
        lidos = sscanf(linha,"%d;%49[^;];%d;%10[^;];%19[^;\r\n]",
            &muda.numero_lote,
            muda.especie,
            &muda.quantidade_mudas,
            muda.data_germinacao,
            muda.status);

        if (lidos == 5) {

            //Inserção na AVL
            if (buscar(*raizAvl,muda.numero_lote,&compAvl)==NULL) {
                reg++;
                *raizAvl =inserir(*raizAvl,muda);
            }
            //Inserção na BST
            if (buscar(*raizBst,muda.numero_lote,&compBst)==NULL) {
                *raizBst =inserirBst(*raizBst,muda);
            }
            else {
                printf("Essa chave já existe, não pode ter duas iguais!\n");
            }

        }
        else {
            printf("numero de dados da linha está incorreto\n");
        }
    }
    printf("Registros carregados: %d\n",reg);
    printf("BST simples -> altura: %d\n",alturaBst(*raizBst));
    printf("AVL         -> altura: %d   raiz: %d\n",altura(*raizAvl),(*raizAvl)->muda.numero_lote);
    printf("Rotacoes na carga: ");
    imprimirContadores();
    fclose(arq);

}