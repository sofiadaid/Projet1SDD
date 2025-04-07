#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include <math.h>
#include <string.h>

#include "entreeSortieLC.h"
#include "biblioLC.h"
#include "entreeSortieH.h"
#include "biblioH.h"


 
 
 



void menu(){

	printf("Bienvenue, voici le menu d'aujourd'hui :)\n");
	printf("==========================================\n");
	printf("0-Sortie du programme\n"); 
	  
	printf("==========================================\n");
	printf("1-Affichage d'une bibliotheque \n");
	
	printf("==========================================\n");
	printf("2-Ajout d'un livre par son numéro le titre et l'auteur de l'ouvrage.\n");
	    
	printf("==========================================\n");
	printf("3-Rcherche d'un livre par son num \n");
	
	printf("==========================================\n");
	printf("4-Rcherche d'un livre par son titre \n");
	
	printf("==========================================\n");
	printf("5-Recherche de tous les livres qui ont le meme auteur\n");
	   
	printf("==========================================\n");
	printf("6-Supprimer un ouvrage \n");
	
	printf("==========================================\n");
	printf("7-Fusionner deux bibliothéques\n");  
	
	printf("==========================================\n");
	printf("8-Recherche de tous les ouvrages\n");
	
	printf("==========================================\n");
	printf("9-Enregister la bibliotheque dans un fichier\n");
	printf("******************************************\n");
}
int main(int argc, char** argv){
 
 
 	if(argc >= 3){
		charger_n_entrees(argv[1], atoi(argv[2]));
		printf("on est entrée dans le if\n");
	}
	int rep,R;
	char titre[256];
	char auteur[256];
	int num;
	
	printf("Vous voulez utiliser les listes ou bien la table de hachage \n");
	printf(" 1 pour liste 2 pour table de hachage");
	scanf("%d",&R);
	
	
	
	if(R==1){ //liste
	
	    Biblio *B = creer_biblio();
	    if (B == NULL) {
        	printf("Erreur lors de la création de la bibliothèque.\n");
        	return 1;
    	    }

	    inserer_en_tete(B, 1, "Prince", "sofia");
    	    inserer_en_tete(B, 2, "1984", "kamelia");
    	    inserer_en_tete(B, 3, "Misérables", "nass");

	
	
	    do{
		menu();
		printf("Entrez une ligne de texte : ");
		scanf("%d",&rep);
		switch(rep){
			case 1:
				printf("Affichage : \n");
				affichageBiblio(B);
				break;
			case 2: 
				
				printf("Veuillez ecrire le numero, le titre et l'auteur de l'ouvrage. \n");
				if(scanf(" %d %s %s",&num,titre,auteur)==3){
					inserer_en_tete(B,num,titre,auteur);
					printf("Ajout fait. \n");
				}else{
					printf("Erreur format.\n");
				}
				break;
			case 3:
				printf("entrez le numero du livre a chercher");
				if(scanf(" %d",&num)==1){
					Livre *l=rechercheNum(B,num);
					if(l){
						affichageLivre(l);
					}else{
						printf("livre introuvable \n");
					}
				}else{
					printf("Erreur format.\n");
				}
				break;
			case 4:
				printf("Rcherche d'un livre par son titre \n");
                		printf("Veuillez entrer le titre du livre recherché : ");
                		scanf(" %[^\n]", titre);
                		  // Pour lire une ligne entière
                		Livre* livre = rechercheTitre(B, titre);
                		if (livre) {
                    			printf("Livre trouvé : %d - %s - %s\n", livre->num, livre->titre, livre->auteur);	
                		} else {
                    			printf("Aucun livre trouvé avec ce titre.\n");
                		}
                		break;
                	
            		case 5: 
            			printf("Recherche de tous les livres qui ont le meme auteur\n");
                		printf("Veuillez entrer le nom de l'auteur : ");
                		scanf(" %[^\n]", auteur);
                		Biblio* result =rechercheAuteur(B, auteur);
                		if (result->L) {
                    			printf("Livres de l'auteur %s :\n", auteur);
                    			affichageBiblio(result);
                		} else {
                    			printf("Aucun livre trouvé pour cet auteur.\n");
                		}
                		liberer_biblio(result);
                		break;

            		case 6: 
                		
                		printf("Veuillez entrer le numéro du livre à supprimer ainsi que le titre ensuite le nom de l'auteur: ");
                		scanf("%d", &num);
                		scanf(" %[^\n]", titre);
                		scanf(" %[^\n]", auteur);
                		suppressionOuvrage(B, num,titre,auteur);
                		printf("Suppression effectuée.\n");
                		break;

            		case 7: 
                		char autre_fichier[256];
                		printf("Veuillez entrer le nom du fichier de la deuxième bibliothèque : ");
                		scanf(" %[^\n]", autre_fichier);

                		int n2;
                		printf("Veuillez entrer le nombre de lignes à lire dans ce fichier : ");
                		scanf("%d", &n2);

                		Biblio* B2 = charger_n_entrees(autre_fichier, n2);
                		if (B2) {
                    		fusion_biblio(B, B2);
                    		printf("Fusion réussie !\n");
                    		liberer_biblio(B2);
                		} else {
                    		printf("Erreur lors du chargement de la deuxième bibliothèque.\n");
                		}
                		break;

           		case 8: 
               			//char fichier_sortie[256];
                		//printf("Veuillez entrer le nom du fichier où enregistrer la bibliothèque : ");
                		/*scanf(" %[^\n]", fichier_sortie);
                		enregistrer_biblio(B, fichier_sortie);
                		printf("Bibliothèque enregistrée dans %s.\n", fichier_sortie);*/
                		Biblio* B3=rechercher_exemplaires(B);
                		affichageBiblio(B3);
                		break;
                	case 9:
                		char fichier_sortie[256];
                		printf("Veuillez entrer le nom du fichier où enregistrer la bibliothèque : ");
                		scanf(" %[^\n]", fichier_sortie);
                		enregistrer_biblio(B, fichier_sortie);
                		printf("Bibliothèque enregistrée dans %s.\n", fichier_sortie);
            

            		default:
                		printf("Option invalide, veuillez réessayer.\n");
				
				
			}	
	}while (rep != 0);
	
	liberer_biblio(B);
	
	
	
      	}else{
      	
		BiblioH *biblio=creer_biblioH(10); // Créer une bibliothèque avec une table de hachage de taille 10

    	// Insérer quelques livres
    		insererH(biblio, 101, "Djurdjura", "Sofia");
    		insererH(biblio, 102, "cartel", "nass");
    		insererH(biblio, 103, "1984", "kam");
    		insererH(biblio, 104, "pere riche", "Herbert");
	
	
	
	
		do{
			menu();
			printf("Entrez une ligne de texte : ");
			scanf("%d",&rep);
			switch(rep){
				case 1:
					printf("Affichage : \n");
					affichageBiblioH(biblio);
					break;
				case 2: 
				
					printf("Veuillez ecrire le numero, le titre et l'auteur de l'ouvrage. \n");
					if(scanf(" %d %s %s",&num,titre,auteur)==3){
						insererH(biblio,num,titre,auteur);
						printf("Ajout fait. \n");
					}else{
						printf("Erreur format.\n");
					}
					break;
				case 3:
					printf("entrez le numero du livre a chercher");
					if(scanf(" %d",&num)==1){
						LivreH *livre = rechercheNumH(biblio,num);
    						if (livre) {
        						affichageLivreH(livre);
    						} else {
        						printf("Livre non trouvé.\n");
    						}
					}else{
						printf("Erreur format.\n");
					}	
					break;
					case 4:
					printf("Rcherche d'un livre par son titre \n");
                			printf("Veuillez entrer le titre du livre recherché : ");
                			scanf(" %[^\n]", titre);
                		  	// Pour lire une ligne entière
                			LivreH* livre =rechercheTitreH(biblio,titre);
                			if (livre) {
                    				printf("Livre trouvé");
                    				affichageLivreH(livre);
                			} else {
                    				printf("Aucun livre trouvé avec ce titre.\n");
                			}
                			break;
                	
            			case 5: 
            				printf("Recherche de tous les livres qui ont le meme auteur\n");
                			printf("Veuillez entrer le nom de l'auteur : ");
                			scanf(" %[^\n]", auteur);
                			BiblioH*result=rechercheAuteurH(biblio,auteur);
                			if (result->T) {
                    				printf("Livres de l'auteur %s :\n", auteur);
                    				affichageBiblioH(result);
                			} else {
                    				printf("Aucun livre trouvé pour cet auteur.\n");
                			}
                			liberer_biblioH(result);
                			break;

            			case 6: 
                		
                			printf("Veuillez entrer le numéro du livre à supprimer ainsi que le titre ensuite le nom de l'auteur: ");
                			scanf("%d", &num);
                			scanf(" %[^\n]", titre);
                			scanf(" %[^\n]", auteur);
                			suppressionOuvrageH(biblio,num,titre,auteur);
   					affichageBiblioH(biblio);
                			printf("Suppression effectuée.\n");
                			break;

            			case 7: 
                			char autre_fichier[256];
                			printf("Veuillez entrer le nom du fichier de la deuxième bibliothèque : ");
                			scanf(" %[^\n]", autre_fichier);

                			int n2;
                			printf("Veuillez entrer le nombre de lignes à lire dans ce fichier : ");
                			scanf("%d", &n2);
	
                			BiblioH* B2=charger_n_entreesH(autre_fichier, n2);
                			if (B2) {
                    			fusionner_bibliosH(biblio, B2);
                    			printf("Fusion réussie !\n");
                    			liberer_biblioH(B2);
                			} else {
                    			printf("Erreur lors du chargement de la deuxième bibliothèque.\n");
                			}
                			break;

           			case 8: 
            
                			BiblioH *B3=rechercher_ouvrages_avec_exemplairesH(biblio);
                			if(!B3){
                				printf("pas d'ouvrage avec le meme auteur et titre \n");
                			}
                			else{
                				affichageBiblioH(B3);
                			}
                			break;
                		case 9:
                			char fichier_sortie[256];
                			printf("Veuillez entrer le nom du fichier où enregistrer la bibliothèque : ");
                			scanf(" %[^\n]", fichier_sortie);
                			enregistrer_biblioH(biblio,fichier_sortie );
                			printf("Bibliothèque enregistrée dans %s.\n", fichier_sortie);
                			break;
                	            

            			default:
                			printf("Option invalide, veuillez réessayer.\n");
				
				
			}	
	}while (rep != 0);
	
	// Libération de la mémoire
    	liberer_biblioH(biblio);
    	}
    
	
	return 0;
}
	
	

