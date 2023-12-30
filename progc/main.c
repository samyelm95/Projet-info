#include <stdio.h>
#include <stdlib.h>
#include "trajet.h"
#include "avl.c"

void parcoursInfixe(Noeud *racine) {
    if (racine != NULL) {
        parcoursInfixe(racine->gauche);
        printf("ID: %d, Ville: %s\n", racine->trajet.id, racine->trajet.ville);
        parcoursInfixe(racine->droite);
    }
}

// Structure pour représenter une étape
typedef struct {
    int id_trajet;
    char ville_depart[50];
    char ville_arrivee[50];
    int est_depart;
} Etape;

// Structure pour représenter une ville avec le nombre de trajets total et le nombre de départs
typedef struct {
    char nom[50];
    int trajets_total;
    int departs;
} Ville;

// Structure pour représenter la distance d'une étape
typedef struct {
    int id_trajet;
    int id_etape;
    int distance;
} Distance;

// ... Autres fonctions pour AVL, tri, etc.

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <option> <fichier.csv>\n", argv[0]);
        return 1;
    }

    char option = argv[1][0];
    char *fichier_csv = argv[2];

A INSERER DANS LES OPTION SELON LES FICHIER DONT ON AURA BESOIN
     // Ouverture du fichier CSV en mode lecture (créer un fichier éphémaire pour chaque élément de la structure)
    FILE *fichier = fopen(fichier_csv, "r");
    if (fichier == NULL) {
        fprintf(stderr, "Erreur d'ouverture du fichier.\n");
        return 1;
    }

OPTION T
// Liste pour stocker les etapes par exemple
    Etape *p1 = NULL;
    int nombre_etapes = 0;

    // Lire le fichier CSV éphémaire et attribuer les valeurs à chaque nœud 
    while (fscanf(data.csv, "%d,%49[^,],%49[^,],%d\n", &etapes[nombre_etapes].id_trajet, etapes[nombre_etapes].ville_depart, etapes[nombre_etapes].ville_arrivee,
                  &etapes[nombre_etapes].est_depart) == 4) {
        // Incrémenter le nombre d'étapes
        nombre_etapes++;
        // Réallouer la mémoire pour le tableau d'étapes
        etapes = realloc(etapes, (nombre_etapes + 1) * sizeof(Etape));
        if (etapes == NULL) {
            fprintf(stderr, "Erreur d'allocation de mémoire.\n");
            return 1;
        }
    }

OPTION S
// Liste pour stocker les distances
    Trajet *p1 = NULL;
    int nombre_etapes = 0;

// Lire le fichier CSV éphémaire et attribuer les valeurs à chaque nœud 
    while (fscanf(data.csv, "%d,%d,%d\n", &etapes[nombre_etapes].id_trajet, &etapes[nombre_etapes].id_etape, &etapes[nombre_etapes].est_depart) == 3) {
        // Incrémenter le nombre d'étapes
        nombre_etapes++;
        // Réallouer la mémoire pour le tableau d'étape
        etapes = realloc(etapes, (nombre_etapes + 1) * sizeof(Etape));
        if (etapes == NULL) {
            fprintf(stderr, "Erreur d'allocation de mémoire.\n");
            return 1;
        }
    }


    if (option == 't') {
        // ... Traitement pour obtenir les 10 villes les plus traversées ...
    } else if (option == 's') {
        // ... Traitement pour obtenir les statistiques sur les étapes ...
    } else {
        fprintf(stderr, "Option non reconnue.\n");
        return 1;
    }

    // Afficher les résultats ou les stocker dans des structures de données selon vos besoins
    // ...

    return 0;
