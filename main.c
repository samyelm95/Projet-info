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

int main() {
    Noeud *racine = NULL;

    Trajet trajet1 = {1, "Paris"};
    Trajet trajet2 = {2, "Lyon"};
    Trajet trajet3 = {3, "Marseille"};

    racine = inserer(racine, trajet1);
    racine = inserer(racine, trajet2);
    racine = inserer(racine, trajet3);

    printf("Trajets triés par identifiant :\n");
    parcoursInfixe(racine);

    libererArbre(racine);

    return 0;
}







// Fonctions pour les traitements T et S
void traitementT(FILE *file, AVLNode **root);
void traitementS(FILE *file, AVLNode **root);




 // Initialisation de la racine de l'AVL
    AVLNode *root = NULL;

    // Ajoutez ici la logique pour gérer les arguments et les traitements demandés
    // Utilisez les fonctions de traitement définies ci-dessus

    // Fermeture du fichier
    fclose(file);

    return 0;
}

int main(int argc, char *argv[]) {
    // Vérification du nombre d'arguments
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <chemin_fichier_csv>\n", argv[0]);
        return 1;
    }

    // Ouverture du fichier CSV
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

// Implémentation des fonctions de traitement T et S
void traitementT(FILE *file, AVLNode **root) {
    // Ajoutez ici la logique pour le traitement T en utilisant l'AVL
}

void traitementS(FILE *file, AVLNode **root) {
   // Ajoutez ici la logique pour le traitement S en utilisant l'AVL
}



