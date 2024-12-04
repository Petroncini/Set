#include "avl.h"
#include <stdbool.h>
#include <stdio.h>

int main(void) {
  AVL *tree = avl_criar();

  for (int i = 0; i < 31; i++) {
    if (!avl_inserir(tree, i)) {
      printf("insertion error\n");
      break;
    }
  }

  printf("inserted all\n");
  avl_imprimir(tree);

  printf("%i in tree: %i\n", 21, avl_busca(tree, 21));
  avl_remover(tree, 21);
  printf("%i in tree: %i\n", 21, avl_busca(tree, 21));
  avl_imprimir(tree);
}
