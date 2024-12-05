#include "avl.h"
#include <stdbool.h>
#include <stdio.h>

int main(void) {
  AVL *tree = avl_criar();

  for (int i = 0; i < 15; i++) {
    if (!avl_inserir(tree, i)) {
      printf("insertion error\n");
      break;
    }
  }

  printf("inserted all\n");
  avl_imprimir_arvore(tree);

  int no = 8;

  printf("%i in tree: %i\n", no, avl_busca(tree, no));
  avl_remover(tree, no);
  printf("removed\n");
  printf("%i in tree: %i\n", no, avl_busca(tree, no));
  avl_imprimir_arvore(tree);
}
