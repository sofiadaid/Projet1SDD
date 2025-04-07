#include <stdio.h>
#include <time.h>

// Fonction pour mesurer le temps de recherche des exemplaires dans la liste chaînée
void mesurerTempsLC(Biblio* b, int n, FILE* file) {
    clock_t start, end;
    double cpu_time_used;

    // Démarrer la mesure du temps pour la liste chaînée
    start = clock();
    rechercher_exemplaires2(b, n);  // Appeler la fonction de recherche pour la liste chaînée avec n
    end = clock();

    // Calculer le temps écoulé pour la liste chaînée
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    // Sauvegarder le temps dans le fichier
    fprintf(file, "%d\t%f\t", n, cpu_time_used);  // Sauvegarder le temps pour la liste chaînée
}

// Fonction pour mesurer le temps de recherche des exemplaires dans la table de hachage
void mesurerTempsH(BiblioH* b_h, int n, FILE* file) {
    clock_t start, end;
    double cpu_time_used;

    // Démarrer la mesure du temps pour la table de hachage
    start = clock();
    rechercher_exemplairesH2(b_h, n);  // Appeler la fonction de recherche pour la table de hachage avec n
    end = clock();

    // Calculer le temps écoulé pour la table de hachage
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    // Sauvegarder le temps dans le fichier
    fprintf(file, "%f\n", cpu_time_used);  // Sauvegarder le temps pour la table de hachage
}

int main() {
    // Initialisation de la bibliothèque pour la liste chaînée
    Biblio* bibliotheque = creer_biblio();
    // Initialisation de la bibliothèque pour la table de hachage
    BiblioH* b_hachage = creer_biblioH(1000);  // Par exemple, taille de table de hachage 1000

    // Ajouter des livres à la bibliothèque pour les deux structures ici...
    // Ajouter les livres à la liste chaînée et à la table de hachage

    // Ouvrir le fichier en mode ajout pour sauvegarder les résultats
    FILE *file = fopen("resultats.txt", "a");
    if (!file) {
        perror("Erreur d'ouverture du fichier");
        return 1;
    }

    // Ajouter un en-tête pour les résultats dans le fichier
    fprintf(file, "n\tListe_Chaînée\tTable_de_Hachage\n");

    // Mesurer les temps pour différentes valeurs de n pour les deux structures
    for (int n = 1000; n <= 50000; n *= 2) {
        mesurerTempsLC(bibliotheque, n, file);  // Mesurer pour la liste chaînée
        mesurerTempsH(b_hachage, n, file);  // Mesurer pour la table de hachage
    }

    // Fermer le fichier
    fclose(file);

    return 0;
}



//gcc -Wall -o exo3 exo3.c biblioLC.c entreeSortieLC.c biblioH.c entreeSortieH.c -lm

