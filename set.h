#ifndef SET_H
#define SET_H
#include <stdbool.h>
typedef struct set_ SET;
SET *set_criar(int type);
bool set_pertence(SET *set, int chave);
bool set_inserir(SET *set, int chave);
bool set_remover(SET *set, int chave);
void set_apagar(SET **set);
void set_imprimir(SET *set);
SET *set_uniao(SET *set1, SET *set2);
SET *set_interseccao(SET *set1, SET *set2);
#endif
