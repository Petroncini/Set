#include "avl.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define max(a, b) ((a > b) ? a : b)

// struct dos nós das árvores
typedef struct NO {
  struct NO *esq;
  struct NO *dir;
  int chave;
  int altura;
} NO;

struct avl_ {
  NO *raiz;
};

// função para criar uma nova avl, retorna nulo se malloc não funcionar
AVL *avl_criar(void) {
  AVL *avl = malloc(sizeof(AVL));

  if (avl != NULL) {
    avl->raiz = NULL;
  }

  return avl;
}

// funcao para criar um no e inicializar os seus valores
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

// funcao para recursivamente apagar os filhos de um nó, então ele mesmo
void apagar_no(NO **no) {
  if (no != NULL) {
    apagar_no(&(*no)->esq);
    apagar_no(&(*no)->dir);
    free(*no);
    *no = NULL;
  }
}

// funcao para apagar a avl, inteira usando a funcao apagar_no na raiz
void avl_apagar(AVL **avl) {
  apagar_no(&(*avl)->raiz);
  free(*avl);
  *avl = NULL;
}

// funcao para retornar a altura de um no, retorna -1 se o nó for nulo
int avl_altura_no(NO *no) {
  if (no == NULL) {
    return -1;
  } else {
    return no->altura;
  }
}

// função para realizar rotação direita em um nó
// exemplo de uso: X->esq = avl_rot_direita(X->esq);
NO *avl_rot_dir(NO *A) {
  NO *B = A->esq;
  A->esq = B->dir;
  B->dir = A;

  // atualizar alturas
  A->altura = max(avl_altura_no(A->esq), avl_altura_no(A->dir)) + 1;
  B->altura = max(avl_altura_no(B->esq), avl_altura_no(B->dir)) + 1;
  return B;
}

// função para realizar rotação esquerda em um nó
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

// função para realizar rotação esquerda direita em um nó
NO *avl_rot_esq_dir(NO *A) {
  A->esq = avl_rot_esq(A->esq);
  return avl_rot_dir(A);
}

// função para realizar rotação direita esquerda em um nó
NO *avl_rot_dir_esq(NO *A) {
  A->dir = avl_rot_dir(A->dir);
  return avl_rot_esq(A);
}

// função para calcular o fato de balandeamento de um nó (diferença da altura
// dos filhos), retorna 0 se o no for nulo
int calc_fb(NO *no) {
  if (no == NULL) {
    return 0;
  } else {
    return avl_altura_no(no->esq) - avl_altura_no(no->dir);
  }
}

// função para inserir no com chave *chave* em uma subárvore de nó raiz *raiz*
NO *inserir_no(NO *raiz, int chave) {
  if (raiz == NULL) {
    raiz = criar_no(chave); // se nó for nulo, criar novo no com a chave dada e
                            // inserir nessa posição
  } else if (chave ==
             raiz->chave) { // se a chave já estiver presente, não insira denovo
    return raiz;
  } else if (chave < raiz->chave) { // se a chave for menor que o nó atual,
                                    // insira na esquerda
    raiz->esq = inserir_no(raiz->esq, chave);
  } else if (chave > raiz->chave) { // se a chave for maior que o nó atual,
                                    // insira na direita
    raiz->dir = inserir_no(raiz->dir, chave);
  }

  // recalcular a altura do nó depois da inserção
  raiz->altura = max(avl_altura_no(raiz->esq), avl_altura_no(raiz->dir)) + 1;
  /* printf("Currently at %i, recalced height is %i\n", raiz->chave,
   * raiz->altura); */

  // recalcular o fator de balandeamento depois da inserção
  int fb = calc_fb(raiz);

  // conferir casos de violação de balanceamento
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

  // retornar raiz
  return raiz;
}

// função para inserir uma chave na avl, usa a função de inserção em nó
bool avl_inserir(AVL *avl, int chave) {
  if (avl == NULL) {
    return false;
  }

  avl->raiz = inserir_no(avl->raiz, chave);
  return true;
}

// encontra maior nó em uma sub-árvore, mais pra frente é utilizado para achar o
// máximo na esquerda de um certo nó
NO *max_esq(NO *raiz, NO *prev, NO *curr) {
  if (curr->dir != NULL) {
    max_esq(raiz, curr, curr->dir);
  }

  return curr;
}

// função para remover nó com certa chave de uma subárvore
bool remover_no(NO **raiz, int chave) { // bool?
  if (*raiz == NULL) {
    return false;
  }

  bool removed = false;

  if (chave == (*raiz)->chave) { // se encontrar a chave, remova
    NO *p = *raiz;               // guardar temporariamene o nó a ser removido
    removed = true;

    if ((*raiz)->esq == NULL ||
        (*raiz)->dir == NULL) { // se algum dos filhos dos nó for nulo
      if ((*raiz)->dir != NULL) {
        *raiz = (*raiz)->dir; // puxe para cima o nó direito
      } else {
        *raiz =
            (*raiz)->esq; // puxe para cima o nó esquerdo, mesmo que for nulo
      }

      free(p); // apagar nó removido
      p = NULL;

    } else { // se o nó tiver dois filhos
      NO *temp =
          max_esq(*raiz, *raiz, (*raiz)->esq); // procura o maior nó na esquerda

      (*raiz)->chave =
          temp->chave; // troque a chave da raiz para a chave desse maior nó

      remover_no(&(*raiz)->esq,
                 temp->chave); // remova esse maior nó (recursivamente)
    }

  } else if (chave < (*raiz)->chave) { // se a chave for menor, procure para
                                       // remover na esquerda
    removed = removed || remover_no(&(*raiz)->esq, chave);
  } else { // se a chave for maio, procure para remover na direita
    removed = removed || remover_no(&(*raiz)->dir, chave);
  }

  // se o nó atual não foi removido, ou foi substituido por um filho
  if (*raiz != NULL) {

    // atualizar altura
    (*raiz)->altura =
        max(avl_altura_no((*raiz)->esq), avl_altura_no((*raiz)->dir)) + 1;

    // recalcular fator de balanceamento
    int fb = calc_fb(*raiz);

    // casos de violação de desbalanceamento
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

// função para remover chave de avl usando função recursiva de remoção no nó da
// avl
bool avl_remover(AVL *avl, int chave) {
  if (avl == NULL) {
    return false;
  } else {
    return remover_no(&avl->raiz, chave);
  }
}

// busca recursiva em subárvore por chave
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

// busca por chave em avl realizando busca em sua raíz
bool avl_busca(AVL *avl, int chave) {
  if (avl == NULL) {
    return false;
  }

  return busca_no(avl->raiz, chave);
}

// imprime a árvore bonitinho
void imprimir_subarvore(NO *no, int profundidade) {
  if (no == NULL) {
    printf("\n");
    return;
  }
  imprimir_subarvore(no->dir, profundidade + 1);
  for (int i = 0; i < profundidade; i++) {
    printf("     ");
  }

  printf("%i \n", no->chave);

  imprimir_subarvore(no->esq, profundidade + 1);
}

void avl_imprimir_arvore(AVL *avl) {
  if (avl == NULL || avl->raiz == NULL) {
    printf("Árvore vazia\n");
    return;
  }

  imprimir_subarvore(avl->raiz, 0);
}

// imprime nó em ordem
void imprimir_no(NO *raiz) { // em ordem
  if (raiz == NULL) {
    return;
  }

  imprimir_no(raiz->esq);
  printf("%i ", raiz->chave);
  imprimir_no(raiz->dir);
}

// imprime o nó raiz e seus filhos
void avl_imprimir(AVL *avl) {
  if (avl == NULL) {
    return;
  }

  imprimir_no(avl->raiz);
  printf("\n");
}

// insere todo nó de uma subárvore dada, em uma outra AVL, em ordem
void copy_no(NO *no, AVL *dest) {
  if (no == NULL) {
    return;
  }

  copy_no(no->esq, dest);
  avl_inserir(dest, no->chave);
  copy_no(no->dir, dest);
}

// insere todos os nós de uma AVL source, em uma outra AVL dest
void copy_avl(AVL *source, AVL *dest) {
  if (source == NULL || dest == NULL) {
    return;
  }

  copy_no(source->raiz, dest);
}

// insere todo nó de uma subárvore de raiz *no* em uma AVL dest, somente se a
// mesma chave estiver presente em uma outra AVL comp, em ordem
void intersect_no(NO *no, AVL *comp, AVL *dest) {
  if (no == NULL) {
    return;
  }

  intersect_no(no->esq, comp, dest);
  if (avl_busca(comp, no->chave)) {
    avl_inserir(dest, no->chave);
  }
  intersect_no(no->dir, comp, dest);
}

// insere todos os nós presentes tanto na AVL source e comp em uma AVL dest
void intersect_avl(AVL *source, AVL *comp, AVL *dest) {
  if (source == NULL || comp == NULL || dest == NULL) {
    return;
  }

  intersect_no(source->raiz, comp, dest);
}

bool no_pertence(NO *raiz, int chave) {
  if (raiz == NULL) {
    return false;
  }

  if (chave == raiz->chave) {
    return true;
  }

  if (chave < raiz->chave) {
    return no_pertence(raiz->esq, chave);
  } else {
    return no_pertence(raiz->dir, chave);
  }
}

bool avl_pertence(AVL *avl, int chave) {
  if (avl == NULL) {
    return NULL;
  }

  return no_pertence(avl->raiz, chave);
}
