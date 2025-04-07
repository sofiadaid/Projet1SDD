#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entreeSortieLC.h"
#include "biblioH.h"

BiblioH* charger_n_entreesH(const char* nomfic, int n) {
    FILE *f = fopen(nomfic, "r");
    if (!f) {
        printf("Erreur ouverture fichier");
        return NULL;
    }

    BiblioH *b = creer_biblioH(10); // Choisir une taille initiale pour la table de hachage
    if (!b) {
        fclose(f);
        return NULL;
    }

    int num;
    char titre[256], auteur[256];
    int count = 0;

    while (count < n && fscanf(f, "%d %255s %255s", &num, titre, auteur) == 3) {
        insererH(b, num, titre, auteur);
        count++;
    }

    fclose(f);
    return b;
}

void enregistrer_biblioH(BiblioH *b,const char* nomfic) {
    if (!b) return;
    FILE *f = fopen(nomfic, "w");
    if (!f) {
        perror("Erreur ouverture fichier");
        return;
    }

    for (int i = 0; i < b->m; i++) {
        LivreH *livre = b->T[i];
        while (livre) {
            fprintf(f, "%d %s %s\n", livre->num, livre->titre, livre->auteur);
            livre = livre->suivant;
        }
    }

    fclose(f);
}

