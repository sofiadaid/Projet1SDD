#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "biblioH.h"
#include <math.h>
#define Beta 19

/*int fonctionClef(const char* auteur){
	unsigned long hash_accu = 0;
        unsigned int i = strlen(auteur);
        for (const char *p = auteur; i > 0; i--, p++) {
        	hash_accu = hash_accu * Beta+ *p; //on peut faire ca pour eviter les collisions et pour avoir une meilleur approche 
    	}
    	return (int) hash_accu;
}
*/

int fonctionClef(const char* auteur){
	int res=0;
	while(*auteur !='\0'){
		res+=(int) *auteur;
		auteur++;
	}
	return res;
}



LivreH* creer_livreH(int num,const char* titre,const char* auteur){
	LivreH* livre=(LivreH *)malloc(sizeof(LivreH));
	livre->clef=fonctionClef(auteur);
	livre->num=num;
	livre->titre=strdup(titre);
	livre->auteur=strdup(auteur);
	livre->suivant=NULL;
	return livre;
}



void liberer_livreH(LivreH* l){
	if(l){
		free(l->titre);
		free(l->auteur);
		free(l);
	}
}

BiblioH* creer_biblioH(int m){
	BiblioH *new=(BiblioH *)malloc(sizeof(BiblioH));
	if(!new) return NULL;
	new->nE=0;
	new->m=m;
	new->T = (LivreH **)calloc(m, sizeof(LivreH *));  //tableau de pointeur 
        if (!new->T) {  
        	free(new);
        	return NULL;
    	}
	return new;
}

void liberer_biblioH(BiblioH *biblio){
    if (!biblio) return;
    for (int i = 0; i < biblio->m; i++) {
        LivreH *courant = biblio->T[i];
        while (courant) {
            LivreH *tmp = courant;
            courant = courant->suivant;
            liberer_livreH(tmp);
        }
    }
    free(biblio->T);
    free(biblio);
}



int fonctionHachage(int cle, int m) {
    double kA = cle * ((sqrt(5) - 1) / 2);
    return floor(m * (kA - (int)(kA)));
}



void insererH(BiblioH* b,int num,const char* titre,const char* auteur){
	int cle=fonctionClef(auteur);
	int pos=fonctionHachage(cle,b->m);
	LivreH* livre=creer_livreH(num,titre,auteur);
	livre->suivant=b->T[pos];
	b->T[pos]=livre;
	b->nE++;
}

void affichageLivreH(const LivreH* l){
	if(l){
		printf("Clé: %d |Numero: %d écrit par: %s intituler: %s \n",l->clef, l->num,l->auteur,l->titre);
	}else{
		printf("livre non trouvé \n");
	}
}

void affichageBiblioH(const BiblioH *b){
	if(b->nE ==0){
		printf("Bibliotheque vide \n");
	}
	for(int i=0; i< b->m ;i++){
		LivreH* livre = b->T[i];
        	while (livre) {
			affichageLivreH(b->T[i]);
			livre=livre->suivant;	
		}
	}
}


LivreH *rechercheNumH(BiblioH *b, int num){
	for(int i=0;i< b->m; i++){
		LivreH* livre = b->T[i];
        	while (livre) {
            		if (livre->num == num) return livre;
            		livre = livre->suivant;
        	}
    	}
	return NULL;
}

LivreH *rechercheTitreH(BiblioH *b,const char* titre){
	for(int i=0;i< b->m; i++){
		LivreH* livre = b->T[i];
        	while (livre) {
			if(strcmp(livre->titre, titre)==0){
				return livre;
			}
			livre=livre->suivant;
		}
	}
	return NULL;
}

BiblioH* rechercheAuteurH(BiblioH* b, const char* auteur){
    BiblioH* new = creer_biblioH(b->m);
    for (int i = 0; i < b->m; i++) {
        LivreH* livre = b->T[i];
        while (livre) {
            if (strcmp(livre->auteur, auteur) == 0) {
                insererH(new, livre->num, livre->titre, livre->auteur);
            }
            livre = livre->suivant;
        }
    }
    return new;
}

void suppressionOuvrageH(BiblioH *b,int num,const char *titre,const char *auteur){
	if(b->nE==0){
		printf("bibliotheque vide \n");
		return ;
	}
	int pos = fonctionHachage(fonctionClef(auteur), b->m);
    	LivreH *livre = b->T[pos];
    	LivreH *t =livre;
	while (livre) {
        	if (livre->num == num && strcmp(livre->titre, titre) == 0 && strcmp(livre->auteur, auteur) == 0) {
            	if (t == livre) {
                	b->T[pos] = livre->suivant;
            	} else {
                	t->suivant = livre->suivant;
            	}
            	liberer_livreH(livre);
            	b->nE--;  
            	return;
        	}
       		t= livre;
        	livre = livre->suivant;
    	}
    	printf("Livre non trouvé.\n");
}

void fusionner_bibliosH(BiblioH* b1, BiblioH* b2) {
    if (!b1 || !b2) return;

    for (int i = 0; i < b2->m; i++) {
        LivreH* livre = b2->T[i];
        while (livre != NULL) {
            insererH(b1, livre->num, livre->titre, livre->auteur);  // Correction ici
            livre = livre->suivant;
        }
    }

    // Libérer la mémoire de b2
    liberer_biblioH(b2);  // Appelle directement la fonction de libération
}


BiblioH* rechercher_ouvrages_avec_exemplairesH(BiblioH* b) {
    if (!b) return NULL;  // Vérification si la bibliothèque existe

    BiblioH* result = creer_biblioH(b->m);  // Créer une bibliothèque pour stocker les résultats
    LivreH* courant1;
    LivreH* courant2;

    // Parcourir chaque case de la table de hachage
    for (int i = 0; i < b->m; i++) {
        courant1 = b->T[i];

        // Parcours des livres dans la liste chaînée à cet indice
        while (courant1 != NULL) {
            courant2 = courant1->suivant;

            // Comparer courant1 avec tous les suivants dans la même liste chaînée
            while (courant2 != NULL) {
                if (strcmp(courant1->titre, courant2->titre) == 0 &&
                    strcmp(courant1->auteur, courant2->auteur) == 0) {
                    
                    // Vérifier si ce livre est déjà dans result
                    if (!rechercheNumH(result, courant1->num)) {
                        insererH(result, courant1->num, courant1->titre, courant1->auteur);
                    }
                    if (!rechercheNumH(result, courant2->num)) {
                        insererH(result, courant2->num, courant2->titre, courant2->auteur);
                    }
                }
                courant2 = courant2->suivant;
            }
            courant1 = courant1->suivant;
        }
    }

    return result;  // Retourner la bibliothèque avec les doublons trouvés
}


/*Exercice3 */
//Modification de la fonction de recherche des ouvrages avec plusieurs exemplaires

BiblioH* rechercher_exemplairesH2(BiblioH* b_h, int n) {
    if (!b_h || !b_h->T) return NULL;

    BiblioH* result = creer_biblioH();  // Crée une nouvelle table de hachage pour les résultats
    int count = 0;

    // Parcours de la table de hachage
    for (int i = 0; i < b_h->m; i++) {
        LivreH* courant1 = b_h->T[i];  // Parcours de la liste chaînée à l'indice i

        while (courant1 != NULL && count < n) {
            LivreH* courant2 = courant1->suivant;  // Comparaison avec les livres suivants dans la même chaîne
            while (courant2 != NULL) {
                if (strcmp(courant1->titre, courant2->titre) == 0 &&
                    strcmp(courant1->auteur, courant2->auteur) == 0) {
                    // Ajouter le livre à la table de résultats
                    inserer_en_tete_H(result, courant1->num, courant1->titre, courant1->auteur);
                }
                courant2 = courant2->suivant;
            }
            courant1 = courant1->suivant;
            count++;
        }
    }
    return result;
}



