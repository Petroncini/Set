#include "set.h"
#include "avl.h"
#include <stdlib.h>
#define avl 0
#define rubronegra 1

struct set_ {
  void *tree;
  int type;
};

SET *set_criar(int type) {
  SET *set = malloc(sizeof(SET));

  if (set != NULL) {
    set->type = type;
    if (type == avl)
      set->tree = avl_criar();
  }

  return set;
}

bool set_inserir(SET *set, int chave) {
  if (set == NULL) {
    return false;
  }
  if (set->type == avl)
    return avl_inserir(set->tree, chave);
  else
    return false;
}

bool set_remover(SET *set, int chave) {
  if (set == NULL) {
    return false;
  }

  if (set->type == avl)
    return avl_remover(set->tree, chave);
  else
    return false;
}

void set_imprimir(SET *set) {
  if (set == NULL) {
    return;
  }

  if (set->type == avl) {
    avl_imprimir(set->tree);
  }
}

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

SET *set_intersecao(SET *set1, SET *set2) {
  if (set1 == NULL || set2 == NULL) {
    return NULL;
  }

  SET *intersecao = set_criar(set1->type);

  if (set1->type == avl) {
    intersect_avl(set1->tree, set2->tree, intersecao->tree);
  }

  return intersecao;
}
