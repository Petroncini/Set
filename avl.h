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
void copy_avl(AVL *source, AVL *dest);
void intersect_avl(AVL *source, AVL *comp, AVL *dest);
void avl_imprimir_arvore(AVL *avl);

#endif
