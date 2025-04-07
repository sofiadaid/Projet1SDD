#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioLC.h"

Livre* creer_livre(int num,const char* titre,const char* auteur){
	Livre* l = malloc(sizeof(Livre));
	l->num = num;
	l->titre=strdup(titre);
	l->auteur=strdup(auteur);
	l->suiv = NULL;
	
	return l;
}

void liberer_livre(Livre* l){ // qui realise une d´esallocation.
	if(l){
		free(l->titre);
		free(l->auteur);
		free(l);
	}
}

Biblio* creer_biblio(){ //qui cree une bibliotheque vide.
	Biblio* b = malloc(sizeof(Biblio));
	if (!b) return NULL;
	b->L = NULL;
	return b;
}

void liberer_biblio(Biblio* b){ //qui libere la m´emoire occupee par une bibliotheque.
	if (!b) return;
	Livre *tmp=b->L;
	while(b->L){
		b->L=b->L->suiv;
		liberer_livre(tmp);
		tmp=b->L;
	}
	free(b);
}

void inserer_en_tete(Biblio* b,int num,const char* titre,const char* auteur){ //qui ajoute un nouveau livre a la bibliotheque.
	if (!b) return;
	Livre* l = creer_livre(num,titre,auteur);
	
	if(!l) return;
	
	l->suiv = b->L;  
	b->L= l;
}

void affichageLivre(const Livre* l){
	if(l){
		printf(" livre numero %d écrit par: %s intituler %s \n", l->num,l->auteur,l->titre);
	}else{
		printf("livre non trouvé \n");
	}
}

void affichageBiblio(const Biblio* b){
	if(!b || !(b->L)){
		printf("Bibliotheque vide \n");
	}
	Livre* tmp = b->L;
	while(tmp){
		affichageLivre(tmp);
		tmp=tmp->suiv;
	}
	
}

Livre *rechercheNum(Biblio *b, int num){
	if (!b) return NULL;
    	Livre* tmp = b->L;
    	while (tmp) {
        	if (tmp->num == num) {
            	return tmp;
        	}
        	tmp = tmp->suiv;
    	}
    	return NULL;
}

Livre *rechercheTitre(Biblio *b,const char* titre){
	if(!b) return NULL;
	Livre* tmp = b->L;
    	while (tmp) {
		if(strcmp(tmp->titre, titre)==0){
			return tmp;
		}
		tmp=tmp->suiv;
	}
	return NULL;
}

Biblio *rechercheAuteur(Biblio* b,const char *auteur){
	if(!b){
		return NULL;
	}
	Biblio* new=creer_biblio();
	Livre* tmp = b->L;
   	while (tmp) {
		if(strcmp(tmp->auteur, auteur)==0){
			inserer_en_tete(new,tmp->num,tmp->titre,tmp->auteur);
		}
		tmp=tmp->suiv;
	}	
	return new;
}

void suppressionOuvrage(Biblio *b,int num,const char *titre,const char *auteur){
	if(!b || !b->L){
		printf("bibliotheque vide \n");
		return ;
	}
	Livre *curr = b->L, *prev = NULL;
    while (curr) {
        if (curr->num == num && strcmp(curr->titre, titre) == 0 && strcmp(curr->auteur, auteur) == 0) {
            if (!prev) {  // Suppression en tête
                b->L = curr->suiv;
            } else {
                prev->suiv = curr->suiv;
            }
            liberer_livre(curr);
            return;
        }
        prev = curr;
        curr = curr->suiv;
    }
}

void fusion_biblio(Biblio *b1, Biblio *b2){
	if(!b1 || !b2 || !b2->L){
		return ;
	}
	Livre* tmp = b2->L;
    	while (tmp) {
		inserer_en_tete(b1, tmp->num, tmp->titre, tmp->auteur);
        tmp = tmp->suiv;
    }
    liberer_biblio(b2);
}




Biblio* rechercher_exemplaires(Biblio* b) {
    if (!b || !b->L) return NULL;  // Vérifier si la bibliothèque est valide

    Biblio* result = creer_biblio();  // Créer une nouvelle bibliothèque pour stocker les résultats
    Livre* courant1 = b->L;  // Pointeur pour parcourir la bibliothèque

    // Parcours des livres de la bibliothèque
    while (courant1 != NULL) {

        // Comparer ce livre avec tous les autres livres dans la bibliothèque
        Livre* courant2 = courant1->suiv;  // Pointeur pour comparer avec les livres suivants
        while (courant2 != NULL) {
            // Vérifier si deux livres ont le même auteur et le même titre
            if (strcmp(courant1->titre, courant2->titre) == 0 &&
                strcmp(courant1->auteur, courant2->auteur) == 0) {
                
                // Ajouter le livre à la bibliothèque de résultats
                inserer_en_tete(result, courant1->num, courant1->titre, courant1->auteur);
                inserer_en_tete(result, courant2->num, courant2->titre, courant2->auteur);
                
            }
            courant2 = courant2->suiv;  // Avancer au livre suivant
        }
        courant1 = courant1->suiv;  // Avancer au livre suivant
    }

    return result;  // Retourner la bibliothèque contenant les ouvrages avec plusieurs exemplaires
}



/*Exercice3 */
//Modification de la fonction de recherche des ouvrages avec plusieurs exemplaires pour qu'elle puisse accepter un paramètre n qui spécifie le nombre de premiers livres à lire.

Biblio* rechercher_exemplaires2(Biblio* b, int n) {
    if (!b || !b->L) return NULL;
    
    Biblio* result = creer_biblio();
    Livre* courant1 = b->L;
    int count = 0;

    while (courant1 != NULL && count < n) {
        Livre* courant2 = courant1->suiv;
        while (courant2 != NULL) {
            if (strcmp(courant1->titre, courant2->titre) == 0 &&
                strcmp(courant1->auteur, courant2->auteur) == 0) {
                inserer_en_tete(result, courant1->num, courant1->titre, courant1->auteur);
            }
            courant2 = courant2->suiv;
        }
        courant1 = courant1->suiv;
        count++;
    }
    return result;
}






