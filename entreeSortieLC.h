#ifndef ENTREE_SORTIE_LC_H
#define ENTREE_SORTIE_LC_H
#include <stdio.h>
#include "biblioLC.h"
 
Biblio* charger_n_entrees(const char* nomfic, int n);
void enregistrer_biblio(Biblio *b,const char* nomfic);
#endif
