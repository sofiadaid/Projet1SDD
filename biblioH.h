#ifndef BIBLIOH_H
#define BIBLIOH_H
#include <stdio.h>


typedef struct livreh {
    int clef;
    int num;
    char *titre;
    char *auteur;
    struct livreh *suivant;
} LivreH;

typedef struct table {
    int nE; /* Nombre d'elements contenus dans la table de hachage */
    int m;  /* Taille de la table de hachage */
    LivreH **T; /* Table de hachage avec resolution des collisions par chainage */
} BiblioH;



int fonctionClef(const char* auteur);

LivreH* creer_livreH(int num,const char* titre,const char* auteur);
void liberer_livreH(LivreH* l);

BiblioH* creer_biblioH(int m);
void liberer_biblioH(BiblioH *biblio);

int fonctionHachage(int cle, int m);

void insererH(BiblioH* b,int num,const char* titre,const char* auteur);
void affichageLivreH(const LivreH* l);
void affichageBiblioH(const BiblioH *b);

LivreH *rechercheNumH(BiblioH *b, int num);
LivreH *rechercheTitreH(BiblioH *b,const char* titre);
BiblioH *rechercheAuteurH(BiblioH* b,const char *auteur);

void suppressionOuvrageH(BiblioH *b,int num,const char *titre,const char *auteur);

void fusionner_bibliosH(BiblioH* b1, BiblioH* b2);
BiblioH* rechercher_ouvrages_avec_exemplairesH(BiblioH* b);
BiblioH* rechercher_exemplairesH2(BiblioH* b_h, int n);

#endif 

