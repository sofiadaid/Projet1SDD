#ifndef ENTREE_SORTIE_H
#define ENTREE_SORTIE_H
#include <stdio.h>
#include "biblioH.h"



BiblioH* charger_n_entreesH(const char* nomfic, int n);
void enregistrer_biblioH(BiblioH *b,const char* nomfic);

#endif
