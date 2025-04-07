import matplotlib.pyplot as plt
import os
print("Répertoire actuel:", os.getcwd())

# Chargement des résultats depuis le fichier
n_values = []
temps_lc = []  # Temps pour la liste chaînée
temps_hachage = []  # Temps pour la table de hachage

# Ouvrir le fichier contenant les résultats
with open("resultats.txt", "r") as file:
    lines = file.readlines()[1:]  # Ignorer la première ligne (en-tête)

    # Parcourir chaque ligne et extraire les valeurs de n et des temps
    for line in lines:
        data = line.split()
        n = int(data[0])  # La valeur de n
        lc_time = float(data[1])  # Temps pour la liste chaînée
        hachage_time = float(data[2])  # Temps pour la table de hachage

        # Ajouter les données aux listes
        n_values.append(n)
        temps_lc.append(lc_time)
        temps_hachage.append(hachage_time)

# Création des courbes
plt.figure(figsize=(10, 6))
plt.plot(n_values, temps_lc, label="Liste Chaînée", marker='o', color='b')
plt.plot(n_values, temps_hachage, label="Table de Hachage", marker='x', color='r')

# Titre et labels
plt.title("Temps de Recherche pour Liste Chaînée et Table de Hachage", fontsize=14)
plt.xlabel("Nombre de livres (n)", fontsize=12)
plt.ylabel("Temps (secondes)", fontsize=12)

# Affichage de la légende
plt.legend()

# Affichage des courbes
plt.grid(True)
plt.show()



