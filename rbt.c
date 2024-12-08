#include "rbt.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define max(a, b) ((a > b) ? a : b)

// struct dos nós das árvores
typedef struct NO {
  struct NO *esq;
  struct NO *dir;
  int chave;
  bool cor;
} NO;

struct rbt_ {
  NO *raiz;
};

// função para criar uma nova rbt, retorna nulo se malloc não funcionar
RBT *rbt_criar(void) {
  RBT *rbt = malloc(sizeof(RBT));

  if (rbt != NULL) {
    rbt->raiz = NULL;
  }

  return rbt;
}

// funcao para criar um no e inicializar os seus valores
static NO *criar_no(int chave) {
  NO *no = malloc(sizeof(NO));

  if (no != NULL) {
    no->chave = chave;
    no->esq = NULL;
    no->dir = NULL;
    no->cor = 1;
  }

  return no;
}

// funcao para recursivamente apagar os filhos de um nó, então ele mesmo
static void apagar_no(NO **no) {
  if (no != NULL) {
    if ((*no)->esq != NULL)
      apagar_no(&(*no)->esq);
    if ((*no)->dir != NULL)
      apagar_no(&(*no)->dir);

    free(*no);
    *no = NULL;
  }
}

// funcao para apagar a rbt, inteira usando a funcao apagar_no na raiz
void rbt_apagar(RBT **rbt) {
  if ((*rbt)->raiz != NULL)
    apagar_no(&(*rbt)->raiz);
  free(*rbt);
  *rbt = NULL;
}

// função para realizar rotação direita em um nó
NO *rbt_rot_dir(NO *A) {
  NO *B = A->esq;
  A->esq = B->dir;
  B->dir = A;

  // atualizar cores
  B->cor = A->cor;
  A->cor = 1;
  return B;
}

// função para realizar rotação esquerda em um nó
NO *rbt_rot_esq(NO *A) {
  NO *B = A->dir;
  A->dir = B->esq;
  B->esq = A;

  // atualizar cores
  B->cor = A->cor;
  A->cor = 1;
  return B;
}

// inverter cores de um nó e seus filhos
void inverte(NO *no) {
  no->cor = !no->cor;
  if (no->esq)
    no->esq->cor = !no->esq->cor;
  if (no->dir)
    no->dir->cor = !no->dir->cor;
}

// checar se um nó é vermelho
bool eh_vermelho(NO *no) {
  if (no == NULL)
    return false;
  return (no->cor == 1);
}

// corrigir eventuais violações das propriedades da llrb
NO *ajeita(NO *no) {
  if (eh_vermelho(no->dir) && !eh_vermelho(no->esq))
    no = rbt_rot_esq(no);
  if (eh_vermelho(no->esq) && eh_vermelho(no->esq->esq))
    no = rbt_rot_dir(no);
  if (eh_vermelho(no->esq) && eh_vermelho(no->dir))
    inverte(no);
  return no;
}

static NO *inserir_no(NO *raiz, int chave) {
  if (raiz == NULL)
    return criar_no(chave);

  if (chave < raiz->chave) // se a chave é menor, vai pra esquerda
    raiz->esq = inserir_no(raiz->esq, chave);
  else if (chave > raiz->chave) // se a chave é maior, vai pra direita
    raiz->dir = inserir_no(raiz->dir, chave);

  return ajeita(raiz); // ajeita o nó
}

// inserir nó em uma llrb
bool rbt_inserir(RBT *rbt, int chave) {
  if (rbt == NULL) {
    return false;
  }

  rbt->raiz = inserir_no(rbt->raiz, chave);
  rbt->raiz->cor = 0; // seta a cor da raiz como preto
  return true;
}

// função de balanceamento para a esquerda
NO *move_vermelho_esq(NO *no) {
  inverte(no);
  if (eh_vermelho(no->dir->esq)) {
    no->dir = rbt_rot_dir(no->dir);
    no = rbt_rot_esq(no);
    inverte(no);
  }
  return no;
}

// função de balanceamento para a direita
NO *move_vermelho_dir(NO *no) {
  inverte(no);
  if (eh_vermelho(no->esq->esq)) {
    no = rbt_rot_dir(no);
    inverte(no);
  }
  return no;
}

// retorna o valor mínimo da árvore
NO *min(NO *raiz) {
  while (raiz->esq)
    raiz = raiz->esq;
  return raiz;
}

// remove o valor mínimo da árvore
NO *remover_min(NO *raiz) {
  if (raiz->esq == NULL) {
    free(raiz);
    return NULL;
  }

  if (!eh_vermelho(raiz->esq) && !eh_vermelho(raiz->esq->esq))
    raiz = move_vermelho_esq(raiz);

  raiz->esq = remover_min(raiz->esq);

  return ajeita(raiz);
}

static NO *remover_no(NO *raiz, int chave) {
  if (raiz == NULL)
    return NULL;

  if (chave <
      raiz->chave) { // se a chave é menor, balanceia e chama para a esquerda
    if (!eh_vermelho(raiz->esq) && !eh_vermelho(raiz->esq->esq)) {
      raiz = move_vermelho_esq(raiz);
    }
    raiz->esq = remover_no(raiz->esq, chave);
  } else {                        // se não
    if (eh_vermelho(raiz->esq)) { // balanceia
      raiz = rbt_rot_dir(raiz);
    }
    if (chave == raiz->chave &&
        raiz->dir == NULL) { // se achou a chave correta, remove
      free(raiz);
      return NULL;
    }
    if (!eh_vermelho(raiz->dir) && !eh_vermelho(raiz->dir->esq)) { // balanceia
      raiz = move_vermelho_dir(raiz);
    }
    if (chave == raiz->chave) { // se achou a chave mas não é folha, realiza a
                                // troca com folha
      NO *x = min(raiz->dir);
      raiz->chave = x->chave;
      raiz->dir = remover_min(raiz->dir);
    } else { // se não achou a chave, chama para a direita
      raiz->dir = remover_no(raiz->dir, chave);
    }
  }
  return ajeita(raiz); // ajeitar o nó
}

// remover nó de uma RBT por chave
bool rbt_remover(RBT *rbt, int chave) {
  if (rbt == NULL)
    return false;

  if (!rbt_busca(rbt, chave))
    return false;

  rbt->raiz = remover_no(rbt->raiz, chave);
  if (rbt->raiz)
    rbt->raiz->cor = 0;
  return true;
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

// busca por chave em rbt realizando busca em sua raíz
bool rbt_busca(RBT *rbt, int chave) {
  if (rbt == NULL) {
    return false;
  }

  return busca_no(rbt->raiz, chave);
}

// imprime a árvore bonitinho
static void imprimir_subarvore(NO *no, int profundidade) {
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

void rbt_imprimir_arvore(RBT *rbt) {
  if (rbt == NULL || rbt->raiz == NULL) {
    printf("Árvore vazia\n");
    return;
  }

  imprimir_subarvore(rbt->raiz, 0);
}

// imprime nó em ordem
static void imprimir_no(NO *raiz) { // em ordem
  if (raiz == NULL) {
    return;
  }

  imprimir_no(raiz->esq);
  printf("%i ", raiz->chave);
  imprimir_no(raiz->dir);
}

// imprime o nó raiz e seus filhos
void rbt_imprimir(RBT *rbt) {
  if (rbt == NULL) {
    return;
  }

  imprimir_no(rbt->raiz);
  printf("\n");
}

static void copy_no(NO *no, RBT *dest) {
  if (no == NULL) {
    return;
  }

  copy_no(no->esq, dest);
  rbt_inserir(dest, no->chave);
  copy_no(no->dir, dest);
}

// insere todos os nós de uma RBT source, em uma outra RBT dest
void copy_rbt(RBT *source, RBT *dest) {
  if (source == NULL || dest == NULL) {
    return;
  }

  copy_no(source->raiz, dest);
}

// insere todo nó de uma subárvore de raiz *no* em uma RBT dest, somente se a
// mesma chave estiver presente em uma outra RBT comp, em ordem
static void intersect_no(NO *no, RBT *comp, RBT *dest) {
  if (no == NULL) {
    return;
  }

  intersect_no(no->esq, comp, dest);
  if (rbt_busca(comp, no->chave)) {
    rbt_inserir(dest, no->chave);
  }
  intersect_no(no->dir, comp, dest);
}

// insere todos os nós presentes tanto na RBT source e comp em uma RBT dest
void intersect_rbt(RBT *source, RBT *comp, RBT *dest) {
  if (source == NULL || comp == NULL || dest == NULL) {
    return;
  }

  intersect_no(source->raiz, comp, dest);
}

static bool no_pertence(NO *raiz, int chave) {
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

bool rbt_pertence(RBT *rbt, int chave) {
  if (rbt == NULL) {
    return NULL;
  }

  return no_pertence(rbt->raiz, chave);
}
