#ifndef BIBLIOLC_H
#define BIBLIOLC_H

typedef struct livre {
	int num ;
	char *titre ;
	char *auteur ;
	struct livre *suiv ;
}Livre ;

typedef struct { /* Tete fictive */
	Livre *L ; /* Premier element */
}Biblio ;


Livre* creer_livre(int num,const char* titre,const char* auteur); //crée un livre
void liberer_livre(Livre* l);// qui realise une d´esallocation.

Biblio* creer_biblio(); //qui cree une bibliotheque vide.

void liberer_biblio(Biblio* b); //qui libere la m´emoire occupee par une bibliotheque.

void inserer_en_tete(Biblio* b,int num,const char* titre,const char* auteur); //qui ajoute un nouveau livre a la bibliotheque.

void affichageLivre(const Livre* l);
void affichageBiblio(const Biblio* b);
Livre *rechercheNum(Biblio *b, int num);
Livre *rechercheTitre (Biblio *b,const char* titre);
Biblio *rechercheAuteur(Biblio* b,const char *auteur);
void suppressionOuvrage(Biblio *b,int num,const char *titre,const char *auteur);

void fusion_biblio(Biblio *b1, Biblio *b2);

Biblio *rechercher_exemplaires(Biblio *b);
Biblio* rechercher_exemplaires2(Biblio* b, int n);

#endif
