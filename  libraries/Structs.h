

#ifndef STRUCTS_H
#define STRUCTS_H
typedef struct {
    int numero_lote;
    char especie[50];
    int quantidade_mudas;
    char data_germinacao[11];
    char status[20];
}Muda ;


typedef struct No {
      Muda muda;
      int altura;
      struct No *esq;
      struct No *dir;
 } No;




#endif //STRUCTS_H
