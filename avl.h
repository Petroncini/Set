#ifndef AVL_H
#define AVL_H
#include <stdbool.h>
typedef struct avl_ AVL;

AVL *avl_criar(void);
void avl_apagar(AVL **avl);
bool avl_inserir(AVL *avl, int chave);
bool avl_remover(AVL *avl, int chave);
bool avl_busca(AVL *avl, int chave);
void avl_imprimir(AVL *avl);
#endif
