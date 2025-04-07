#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entreeSortieLC.h"

Biblio* charger_n_entrees(const char* nomfic, int n) {
    FILE* f = fopen(nomfic, "r");
    if (!f) {
        printf("Erreur ouverture fichier\n");
        return NULL;
    }

    Biblio* b = creer_biblio();
    if (!b) {
        fclose(f);
        return NULL;
    }

    int num;
    char titre[256], auteur[256];
    
    for (int i = 0; i < n; i++) {
        if (fscanf(f, "%d ", &num) != 1) break;
        if (!fgets(titre, sizeof(titre), f) || !fgets(auteur, sizeof(auteur), f)) break;

        // Suppression du saut de ligne (\n) final
        titre[strcspn(titre, "\n")] = '\0';
        auteur[strcspn(auteur, "\n")] = '\0';

        inserer_en_tete(b, num, titre, auteur);
    }
    fclose(f);
    return b;
}

void enregistrer_biblio(Biblio* b,const char* nomfic) {
    FILE* f = fopen(nomfic, "w");
    if (!f) {
        printf("Erreur écriture fichier\n");
        return;
    }

    Livre* tmp = b->L;
    while (tmp) {
        fprintf(f, "%d %s %s\n", tmp->num, tmp->titre, tmp->auteur);
        tmp = tmp->suiv;
    }

    fclose(f);
}

