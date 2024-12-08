#include "set.h"
#include <stdio.h>

int main(void) {
  SET *A, *B;
  int n_a, n_b, x;
  int op;
  int tipo;

  printf("Tipo do set (0 - AVL, 1 - RedBlack): ");
  scanf("%d", &tipo); /*0 -> ED1, 1 -> ED2*/

  A = set_criar(tipo);
  B = set_criar(tipo);

  printf("Tamanhos dos sets A e B: ");
  scanf("%d %d", &n_a, &n_b);

  printf("Elementos de A: ");
  for (int i = 0; i < n_a; i++) {
    scanf("%d", &x);
    set_inserir(A, x);
  }

  printf("Elementos de B: ");
  for (int i = 0; i < n_b; i++) {
    scanf("%d", &x);
    set_inserir(B, x);
  }

  printf("\nOperações:\n1: Pertence\n2: União\n3: Intersecção\n4: "
         "Remoção\n5: Inserir\n6: Sair\n\n");

  while (true) {

    printf("\nOperação: ");
    scanf("%d", &op);

    switch (op) {
    case 1: {
      // pertence
      int elemento;
      printf("Elemento procurado: ");

      scanf("%d", &elemento);
      if (set_pertence(A, elemento)) {
        printf("Pertence\n");
      } else {
        printf("Nao pertence\n");
      }

      break;
    }

    case 2: {
      // união
      SET *uniao = set_uniao(A, B);
      printf("União dos sets: ");
      set_imprimir(uniao);
      break;
    }

    case 3: {
      // intersecção
      SET *interseccao = set_interseccao(A, B);
      printf("Intersecção dos sets: ");
      set_imprimir(interseccao);
      break;
    }

    case 4: {
      // remover
      int elemento;
      printf("Elementos para remover: ");
      scanf("%d", &elemento);
      set_remover(A, elemento);
      printf("Set sem \"%d\": ", elemento);
      set_imprimir(A);
      break;
    }

    case 5: {
      // inserir
      int elemento;
      printf("Elemento para inserir: ");
      scanf("%d", &elemento);
      set_inserir(A, elemento);
      printf("Set com \"%d\": ", elemento);
      set_imprimir(A);
      break;
    }

    default: {
      set_apagar(&A);
      set_apagar(&B);
      return 0;
      break;
    }
    }
  }
}
