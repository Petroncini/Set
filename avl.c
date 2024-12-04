#include "avl.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define max(a, b) ((a > b) ? a : b)

typedef struct NO {
  struct NO *esq;
  struct NO *dir;
  int chave;
  int altura;
} NO;

struct avl_ {
  NO *raiz;
};

AVL *avl_criar(void) {
  AVL *avl = malloc(sizeof(AVL));

  if (avl != NULL) {
    avl->raiz = NULL;
  }

  return avl;
}

NO *criar_no(int chave) {
  NO *no = malloc(sizeof(NO));

  if (no != NULL) {
    no->chave = chave;
    no->esq = NULL;
    no->dir = NULL;
    no->altura = 0;
  }

  return no;
}

void apagar_no(NO **no) {
  if (no != NULL) {
    apagar_no(&(*no)->esq);
    apagar_no(&(*no)->dir);
    free(*no);
    *no = NULL;
  }
}

void avl_apagar(AVL **avl) {
  apagar_no(&(*avl)->raiz);
  free(*avl);
  *avl = NULL;
}

int avl_altura_no(NO *no) {
  if (no == NULL) {
    return -1;
  } else {
    return no->altura;
  }
}

// use example: X->esq = avl_rot_direita(X->esq);
NO *avl_rot_dir(NO *A) {
  NO *B = A->esq;
  A->esq = B->dir;
  B->dir = A;

  // atualizar alturas
  A->altura = max(avl_altura_no(A->esq), avl_altura_no(A->dir)) + 1;
  B->altura = max(avl_altura_no(B->esq), avl_altura_no(B->dir)) + 1;
  return B;
}

// use example: X->dir = avl_rot_esquerda(X->dir);
NO *avl_rot_esq(NO *A) {
  NO *B = A->dir;
  A->dir = B->esq;
  B->esq = A;

  // atualizar alturas
  A->altura = max(avl_altura_no(A->esq), avl_altura_no(A->dir)) + 1;
  B->altura = max(avl_altura_no(B->esq), avl_altura_no(B->dir)) + 1;
  return B;
}

NO *avl_rot_esq_dir(NO *A) {
  A->esq = avl_rot_esq(A->esq);
  return avl_rot_dir(A);
}

NO *avl_rot_dir_esq(NO *A) {
  A->dir = avl_rot_dir(A->dir);
  return avl_rot_esq(A);
}

int calc_fb(NO *no) {
  if (no == NULL) {
    return 0;
  } else {
    return avl_altura_no(no->esq) - avl_altura_no(no->dir);
  }
}

NO *inserir_no(NO *raiz, int chave) {
  if (raiz == NULL) {
    raiz = criar_no(chave);
  } else if (chave < raiz->chave) {
    raiz->esq = inserir_no(raiz->esq, chave);
  } else if (chave > raiz->chave) {
    raiz->dir = inserir_no(raiz->dir, chave);
  }

  raiz->altura = max(avl_altura_no(raiz->esq), avl_altura_no(raiz->dir)) + 1;
  /* printf("Currently at %i, recalced height is %i\n", raiz->chave,
   * raiz->altura); */

  int fb = calc_fb(raiz);

  if (fb > 1) {
    int fb_esq = calc_fb(raiz->esq);

    if (fb_esq >= 0) {
      raiz = avl_rot_dir(raiz);
    } else {
      raiz = avl_rot_esq_dir(raiz);
    }
  } else if (fb < -1) {
    int fb_dir = calc_fb(raiz->dir);

    if (fb_dir <= 0) {
      raiz = avl_rot_esq(raiz);
    } else {
      raiz = avl_rot_dir_esq(raiz);
    }
  }

  return raiz;
}

bool avl_inserir(AVL *avl, int chave) {
  if (avl == NULL) {
    return false;
  }

  avl->raiz = inserir_no(avl->raiz, chave);
  return true;
}

NO *max_esq(NO *raiz, NO *prev, NO *curr) {
  if (curr->dir != NULL) {
    max_esq(raiz, curr, curr->dir);
  }

  return curr;
}

bool remover_no(NO **raiz, int chave) { // bool?
  if (raiz == NULL) {
    return false;
  }

  bool removed = false;

  if (chave == (*raiz)->chave) {
    NO *p = *raiz;
    removed = true;

    if ((*raiz)->esq == NULL || (*raiz)->dir == NULL) {
      if ((*raiz)->dir != NULL) {
        *raiz = (*raiz)->dir;
      } else {
        *raiz = (*raiz)->esq;
      }

      free(p);
      p = NULL;

    } else {
      NO *temp = max_esq(*raiz, *raiz, (*raiz)->esq);

      (*raiz)->chave = temp->chave;

      remover_no(&(*raiz)->esq, temp->chave);
    }

  } else if (chave < (*raiz)->chave) {
    removed = removed || remover_no(&(*raiz)->esq, chave);
  } else {
    removed = removed || remover_no(&(*raiz)->dir, chave);
  }

  // rotacionar
  if (*raiz != NULL) {
    // atualizar altura
    (*raiz)->altura =
        max(avl_altura_no((*raiz)->esq), avl_altura_no((*raiz)->dir)) + 1;

    int fb = calc_fb(*raiz);

    if (fb > 1) {
      int fb_esq = calc_fb((*raiz)->esq);

      if (fb_esq >= 0) {
        *raiz = avl_rot_dir(*raiz);
      } else {
        *raiz = avl_rot_esq_dir(*raiz);
      }
    } else if (fb < -1) {
      int fb_dir = calc_fb((*raiz)->dir);

      if (fb_dir <= 0) {
        *raiz = avl_rot_esq(*raiz);
      } else {
        *raiz = avl_rot_dir_esq(*raiz);
      }
    }
  }

  return removed;
}

bool avl_remover(AVL *avl, int chave) {
  if (avl == NULL) {
    return false;
  } else {
    return remover_no(&avl->raiz, chave);
  }
}

bool busca_no(NO *raiz, int chave) {
  if (raiz == NULL) {
    return false;
  }
  bool found = false;

  if (chave == raiz->chave) {
    found = true;
  } else if (chave < raiz->chave) {
    found = found || busca_no(raiz->esq, chave);
  } else {
    found = found || busca_no(raiz->dir, chave);
  }

  return found;
}

bool avl_busca(AVL *avl, int chave) {
  if (avl == NULL) {
    return false;
  }

  return busca_no(avl->raiz, chave);
}

// by claude, for debugging purposes
void print_tree_helper(NO *node, int depth) {
  if (node == NULL)
    return;

  // Print right subtree first (top of the visual tree)
  if (node->dir != NULL) {
    print_tree_helper(node->dir, depth + 1);
  }

  // Print current node with appropriate indentation
  for (int i = 0; i < depth; i++) {
    printf("    ");
  }
  printf("%d\n", node->chave);

  // Print left subtree
  if (node->esq != NULL) {
    print_tree_helper(node->esq, depth + 1);
  }
}

void avl_imprimir(AVL *avl) {
  if (avl == NULL || avl->raiz == NULL) {
    printf("Árvore vazia\n");
    return;
  }

  print_tree_helper(avl->raiz, 0);
}
