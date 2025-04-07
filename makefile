# Variables
CC = gcc
CFLAGS = -Wall
LDFLAGS = -lm  # Ajout de la bibliothèque mathématique
OBJ = main.o biblioLC.o entreeSortieLC.o biblioH.o entreeSortieH.o

# Règle par défaut pour créer l'exécutable
all: main

# Règle pour créer l'exécutable
main: $(OBJ)
	$(CC) $(OBJ) -o main $(LDFLAGS)

# Compilation des fichiers objets
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

biblioLC.o: biblioLC.c
	$(CC) $(CFLAGS) -c biblioLC.c -o biblioLC.o

entreeSortieLC.o: entreeSortieLC.c
	$(CC) $(CFLAGS) -c entreeSortieLC.c -o entreeSortieLC.o

biblioH.o: biblioH.c
	$(CC) $(CFLAGS) -c biblioH.c -o biblioH.o

entreeSortieH.o: entreeSortieH.c
	$(CC) $(CFLAGS) -c entreeSortieH.c -o entreeSortieH.o

# Nettoyage des fichiers objets et de l'exécutable
clean:
	rm -f $(OBJ) main






