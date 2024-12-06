#ifndef RBT_H
#define RBT_H
#include <stdbool.h>
typedef struct rbt_ RBT;

RBT *rbt_criar(void);
void rbt_apagar(RBT **rbt);
bool rbt_inserir(RBT *rbt, int chave);
bool rbt_remover(RBT *rbt, int chave);
bool rbt_busca(RBT *rbt, int chave);
void rbt_imprimir(RBT *rbt);
void copy_rbt(RBT *source, RBT *dest);
void intersect_rbt(RBT *source, RBT *comp, RBT *dest);
#endif
