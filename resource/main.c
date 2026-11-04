#include <stdio.h>
#include <string.h>

#include "../ libraries/Arquivo.h"
#include "../ libraries/Structs.h"
#include "../ libraries/Bst.h"
#include "../ libraries/Avl.h"


// Declarando as variáveis globais que estão no Avl.c
extern int contLL, contRR, contLR, contRL, visitados;



int menu(int *op);



int main() {
    No* no;
    int chave,comp=0;

    int op;
    No *raizAvl = NULL,*raizBst = NULL;
    lerArquivo("dados.txt",&raizBst,&raizAvl);

    do {
        menu(&op);
        switch (op) {
            case 1: {
                //Buscar

                no = NULL;
                comp=0;
                printf("Digite o lote que deseja buscar: ");
                scanf("%d",&chave);
                no=buscar(raizAvl,chave,&comp);
                if (no == NULL) {
                    printf("O lote buscado nao existe!\n");
                }
                else {
                    printf("Lote: %d | Especie: %s | Qtd: %d | Data: %s | Status: %s\n",
                      no->muda.numero_lote,
                      no->muda.especie,
                      no->muda.quantidade_mudas,
                      no->muda.data_germinacao,
                      no->muda.status);
                    printf("Comparacoes: %d\n",comp);
                }
            }
                break;

            case 2: {
                // Inserir

                comp = 0;
                Muda muda;

                printf("Numero do lote: ");
                scanf("%d", &muda.numero_lote);

                if (buscar(raizAvl, muda.numero_lote, &comp) != NULL) {
                    printf("Essa chave ja existe, nao pode ter duas iguais!\n");
                    break;
                }

                printf("Especie: ");
                scanf(" %49[^\n]", muda.especie);

                printf("Quantidade de mudas: ");
                scanf("%d", &muda.quantidade_mudas);

                printf("Data de germinacao (dd/mm/aaaa): ");
                scanf(" %10[^\n]", muda.data_germinacao);

                printf("Status: ");
                scanf(" %19[^\n]", muda.status);

                raizAvl = inserir(raizAvl, muda);
                raizBst = inserirBst(raizBst, muda);
                printf("Lote %d inserido com sucesso.\n", muda.numero_lote);
                break;
            }


            case 3: {
                // Remover

                no=NULL;
                comp=0;
                printf("Digite o lote que deseja remover: ");
                scanf("%d",&chave);
                no=buscar(raizAvl,chave,&comp);
                if (no == NULL) {
                    printf("Lote não encontrado!\n");
                    break;
                }
                Muda removida = no->muda;
                raizAvl = remover(raizAvl, chave);
                raizBst = removerBst(raizBst, chave);

                printf("Lote %d (%s) removido.\n", removida.numero_lote, removida.especie);
                break;
            }

            case 4: {
                // Listar tudo

                inOrder(raizAvl);
                break;
            }

            case 5: {
                // Listar por faixa

                int a, b;
                printf("Lote inicial: ");
                scanf("%d", &a);
                printf("Lote final: ");
                scanf("%d", &b);

                if (a > b) {
                    printf("Faixa invalida: o inicial deve ser menor ou igual ao final.\n");
                    break;
                }

                visitados = 0;                  // zera antes de cada listagem
                listarFaixa(raizAvl, a, b);
                printf("\nNos visitados: %d\n", visitados);
                break;
            }

            case 6: {
                // Estatisticas (altura, nos, rotacoes)


                printf("Altura: %d\n",altura(raizAvl));
                imprimirContadores();
                printf("Nos: %d\n",contarNos(raizAvl));
                break;
            }

            case 7: {
                // Comparar BST x AVL

                int compAvl = 0, compBst = 0;
                printf("Numero do lote: ");
                scanf("%d", &chave);

                No *noBst = buscar(raizBst, chave, &compBst);
                No *noAvl = buscar(raizAvl, chave, &compAvl);

                if (noAvl == NULL) {
                    printf("Lote %d nao encontrado.\n", chave);
                }
                printf("BST: %d comparacoes | AVL: %d comparacoes\n", compBst, compAvl);
                break;
            }
                case 0:
                    printf("Saindo...\n");
                break;
                default:
                    printf("Opcao invalida!\n");
                break;

        }

    }while (op != 0);
    return 0;
}

int menu(int *op) {

    printf("\n========== MENU ==========\n");
    printf("1 - Buscar\n");
    printf("2 - Inserir\n");
    printf("3 - Remover\n");
    printf("4 - Listar tudo\n");
    printf("5 - Listar por faixa\n");
    printf("6 - Estatisticas (altura, nos, rotacoes)\n");
    printf("7 - Comparar BST x AVL\n");
    printf("0 - Sair\n");
    printf("==========================\n");
    printf("Escolha uma opcao: ");
    scanf("%d",op);
}