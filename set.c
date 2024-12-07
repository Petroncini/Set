#include "set.h"
#include "avl.h"
#include <stdlib.h>
#define avl 0
#define rubronegra 1

// struct do set, contém um ponteiro void para o TAD escolhido, determinado por
// type
struct set_ {
  void *tree;
  int type;
};

// cria e configura o set de acordo com input
SET *set_criar(int type) {
  SET *set = malloc(sizeof(SET));

  if (set != NULL) {
    set->type = type;
    if (type == avl)
      set->tree = avl_criar();
  }

  return set;
}

// insere chave no set
bool set_inserir(SET *set, int chave) {
  if (set == NULL) {
    return false;
  }
  if (set->type == avl)
    return avl_inserir(set->tree, chave);
  else
    return false;
}

// remove chave do set
bool set_remover(SET *set, int chave) {
  if (set == NULL) {
    return false;
  }

  if (set->type == avl)
    return avl_remover(set->tree, chave);
  else
    return false;
}

// imprime o set, por sinal em ordem
void set_imprimir(SET *set) {
  if (set == NULL) {
    return;
  }

  if (set->type == avl) {
    avl_imprimir(set->tree);
  }
}

bool set_pertence(SET *set, int chave) {
  if (set == NULL) {
    return false;
  }

  if (set->type == avl) {
    return avl_pertence(set->tree, chave);
  } else {
    return false;
  }
}

// retorna um set contendo a união dos elementos de set 1 e set 2
SET *set_uniao(SET *set1, SET *set2) {
  if (set1 == NULL) { // sets must be of the same type?
    return NULL;
  }

  SET *uniao = set_criar(set1->type);

  if (set1->type == avl && set2->type == avl) {
    copy_avl(set1->tree, uniao->tree);
    copy_avl(set2->tree, uniao->tree);
  }

  return uniao;
}

// retorna um set contendo a interseção dos elementos do set 1 e do set 2
SET *set_interseccao(SET *set1, SET *set2) {
  if (set1 == NULL || set2 == NULL) {
    return NULL;
  }

  SET *intersecao = set_criar(set1->type);

  if (set1->type == avl) {
    intersect_avl(set1->tree, set2->tree, intersecao->tree);
  }

  return intersecao;
}
