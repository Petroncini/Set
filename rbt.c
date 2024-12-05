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
RBT *rvt_criar(void) {
  RBT *rbt = malloc(sizeof(RBT));

  if (rbt != NULL) {
    rbt->raiz = NULL;
  }

  return rbt;
}

// funcao para criar um no e inicializar os seus valores
NO *criar_no(int chave) {
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
void apagar_no(NO **no) {
  if (no != NULL) {
    apagar_no(&(*no)->esq);
    apagar_no(&(*no)->dir);
    free(*no);
    *no = NULL;
  }
}

// funcao para apagar a rbt, inteira usando a funcao apagar_no na raiz
void avl_apagar(RBT **rbt) {
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

void inverte(NO *no) {
  no->cor = !no->cor;
  if (no->esq)
    no->esq->cor = !no->esq->cor;
  if (no->dir)
    no->dir->cor = !no->dir->cor;
}

bool eh_vermelho(NO *no) {
  if (no == NULL) return false;
  return (no->cor == 1);
}

NO *inserir_no(NO *raiz, int chave) {
  if (raiz == NULL) return criar_no(chave);

  if (chave < raiz->chave)
    raiz->esq = inserir_no(raiz->esq, chave);
  else if (chave > raiz->chave)
    raiz->dir = inserir_no(raiz->dir, chave);

  if (eh_vermelho(raiz->dir) && !eh_vermelho(raiz->esq)) raiz = rbt_rot_esq(raiz);
  if (eh_vermelho(raiz->esq) && eh_vermelho(raiz->esq->esq)) raiz = rbt_rot_dir(raiz);
  if (eh_vermelho(raiz->esq) && eh_vermelho(raiz->dir)) inverte(raiz);

  return raiz;
}

bool rbt_inserir(RBT *rbt, int chave) {
  if (rbt == NULL) {
    return false;
  }

  rbt->raiz = inserir_no(rbt->raiz, chave);
  rbt->raiz->cor = 0;
  return true;
}

NO* move_vermelho_esq(NO* no) {
  inverte(no);
  if (eh_vermelho(no->dir->esq)) {
    no->dir = rbt_rot_dir(no->dir);
    no = rbt_rot_esq(no);
    inverte(no);
  }
  return no;
} 

NO* move_vermelho_dir(NO* no) {
  inverte(no);
  if (eh_vermelho(no->esq->esq)) {
    no = rbt_rot_dir(no);
    inverte(no);
  }
  return no;
}

NO *remover_no(NO *raiz, int chave) {

}

bool rbt_remover(RBT *rbt, int chave) {
  if (rbt == NULL)
    return false;

  return 
}