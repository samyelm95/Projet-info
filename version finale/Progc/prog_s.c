#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stdbool.h>

typedef struct EtapeAVL {
int id_trajet;
double distance;
double distance_min;
double distance_max;
double distance_max_min;
double distance_moyenne;
int hauteur;
int nombre_etapes;
struct EtapeAVL *gauche;
struct EtapeAVL *droite;
} EtapeAVL;


typedef struct Trajet {
  EtapeAVL* noeud;
  struct Trajet* next;
    struct Trajet *end;
} Trajet;

//fonctions de recherch de max
int max(int a, int b) {
    return (a > b) ? a : b;
}
// rotations de l'AVL
EtapeAVL *rotateRight(EtapeAVL *y) {
    EtapeAVL *x = y->gauche;
    EtapeAVL *t2 = x->droite;

   / Rotation
    x->droite = y;
    y->gauche = t2;

   
    y->hauteur = max(height(y->gauche), height(y->droite)) + 1;
    x->hauteur = max(height(x->gauche), height(x->droite)) + 1;

    return x;
}


EtapeAVL *rotateLeft(EtapeAVL *x) {
    EtapeAVL *y = x->droite;
    EtapeAVL *t2 = y->gauche;

   
    y->gauche = x;
    x->droite = t2;

   
    x->hauteur = max(height(x->gauche), height(x->droite)) + 1;
    y->hauteur = max(height(y->gauche), height(y->droite)) + 1;

    return y;
}
//Creation d'un noeud
EtapeAVL *newEtapeAVL(int id_trajet,double distance) {
    EtapeAVL *node = (EtapeAVL *)malloc(sizeof(EtapeAVL));
    if (node == NULL) {
        perror("Erreur d'allocation memoire");
        exit(EXIT_FAILURE);
    }
    node->distance=distance;
    node->distance_max=distance;
    node->distance_min=distance;
    node->distance_max_min=0;
    node->nombre_etapes=1;
    node->distance_moyenne=distance/node->nombre_etapes;
    node->id_trajet = id_trajet;
    node->gauche = NULL;
    node->droite = NULL;
    node->hauteur = 1;
    return node;
}
//Etude de l'équilibre
int getBalance(EtapeAVL *node) {
    if (node == NULL) {
        return 0; // Le facteur d'equilibre d'un noeud vide est 0
    } else {
        return height(node->gauche) - height(node->droite);
    }
}


// fonction pour calculer hauteur d'un arbre
int height(EtapeAVL *node) {
    if (node == NULL) {
        return 0; // La hauteur d'un noeud vide est 0
    } else {
        int gauche_height = height(node->gauche);
        int droite_height = height(node->droite);

        return 1 + max(gauche_height, droite_height);
    }
}

// rotation droite de l'AVL
EtapeAVL *rotateRight(EtapeAVL *y) {
    EtapeAVL *x = y->gauche;
    EtapeAVL *T2 = x->droite;

    // Rotation
    x->droite = y;
    y->gauche = T2;

    // Mise à jour des hauteurs
    y->hauteur = max(height(y->gauche), height(y->droite)) + 1;
    x->hauteur = max(height(x->gauche), height(x->droite)) + 1;

    return x;
}

// rotation gauche de l'AVL
EtapeAVL *rotateLeft(EtapeAVL *x) {
    EtapeAVL *y = x->droite;
    EtapeAVL *T2 = y->gauche;

    // Rotation
    y->gauche = x;
    x->droite = T2;

    // Mise à jour des hauteurs
    x->hauteur = max(height(x->gauche), height(x->droite)) + 1;
    y->hauteur = max(height(y->gauche), height(y->droite)) + 1;

    return y;
}

// l'AVL est-il equilibre
int getBalance(EtapeAVL *node) {
    if (node == NULL) {
        return 0; // Le facteur d'equilibre d'un noeud vide est 0
    } else {
        return height(node->gauche) - height(node->droite);
    }
}

// creation d'un nouveau noeud
EtapeAVL *newEtapeAVL(int id_trajet,double distance) {
    EtapeAVL *node = (EtapeAVL *)malloc(sizeof(EtapeAVL));
    if (node == NULL) {
        perror("Erreur d'allocation memoire");
        exit(EXIT_FAILURE);
    }
    node->distance=distance;
    node->distance_max=distance;
    node->distance_min=distance;
    node->distance_max_min=0;
    node->nombre_etapes=1;
    node->distance_moyenne=distance/node->nombre_etapes;
    node->id_trajet = id_trajet;
    node->gauche = NULL;
    node->droite = NULL;
    node->hauteur = 1;
    return node;
}

// modification du noeud
Trajet* modifierTrajet(Trajet* root, EtapeAVL* nouvelle_etape) {
    if (root == NULL || root->noeud == NULL) {
        // Gérer le cas où root ou root->noeud est NULL
        return root;
    }

    root->noeud->distance += nouvelle_etape->distance;

    if (root->noeud->distance_max < nouvelle_etape->distance) {
        root->noeud->distance_max = nouvelle_etape->distance;
    }

    if (root->noeud->distance_min > nouvelle_etape->distance) {
        root->noeud->distance_min = nouvelle_etape->distance;
    }

    root->noeud->distance_max_min = root->noeud->distance_max - root->noeud->distance_min;
    root->noeud->nombre_etapes += 1;
    root->noeud->distance_moyenne = root->noeud->distance / root->noeud->nombre_etapes;

    return root;
}



Trajet *insertPliste(Trajet *pliste, EtapeAVL *nouvelle_etape) {
    Trajet *newNode = (Trajet *)malloc(sizeof(Trajet));
    if (newNode == NULL) {
        perror("Erreur d'allocation mémoire");
        exit(EXIT_FAILURE);
    }
    newNode->noeud = nouvelle_etape;
    newNode->next = NULL;

    if (pliste == NULL) {
        // Si la liste est vide, le nouveau nœud devient la tête de la liste
        Trajet * inter = newNode;
        inter->end = newNode;
        return inter;
    }

    Trajet *tmp = pliste;
        if (tmp->end->noeud->id_trajet == nouvelle_etape->id_trajet) {
            tmp = modifierTrajet(tmp->end, nouvelle_etape);
            free(newNode); // Libérer le nœud nouvellement alloué car il n'est pas nécessaire
            return pliste; // Pas besoin d'ajouter un nouveau nœud à la liste
    }

    tmp->end->next = newNode;
    tmp->end = tmp->end->next;
    return pliste;
}


void affichePliste(Trajet* pliste) {
    Trajet* tmp = pliste;

    printf("Contenu de la liste :\n");
    while (tmp != NULL) {
        printf("ID_trajet : %d, Distance : %.3lf\n, Distance_max_min : %.3lf\n", tmp->noeud->id_trajet, tmp->noeud->distance, tmp->noeud->distance_max_min);
        tmp = tmp->next;
    }
}
   

// Fonction pour insérer un nouveau noeud dans l'arbre AVL
EtapeAVL *insertAVLNode(EtapeAVL *root, EtapeAVL *nouvelle_etape) {
    // Effectuer l'insertion de manière normale
    if (root == NULL) {
        return nouvelle_etape;
    }
    if (nouvelle_etape->distance_max_min < root->distance_max_min) {
        root->gauche = insertAVLNode(root->gauche, nouvelle_etape);
    } else if (nouvelle_etape->distance_max_min >= root->distance_max_min) {
        root->droite = insertAVLNode(root->droite, nouvelle_etape);
    }

    // Mettre à jour la hauteur du noeud actuel
    root->hauteur = 1 + max(height(root->gauche), height(root->droite));

    // Obtenir le facteur d'équilibre du noeud
    int balance = getBalance(root);

    // Cas de déséquilibre à gauche
    if (balance > 1) {
        if (nouvelle_etape->distance_max_min < root->gauche->distance_max_min) {
            return rotateRight(root);
        } else if (nouvelle_etape->distance_max_min >= root->gauche->distance_max_min) {
            root->gauche = rotateLeft(root->gauche);
            return rotateRight(root);
        }
    }

    // Cas de déséquilibre à droite
    if (balance < -1) {
        if (nouvelle_etape->distance_max_min >= root->droite->distance_max_min) {
            return rotateLeft(root);
        } else if (nouvelle_etape->distance_max_min < root->droite->distance_max_min) {
            root->droite = rotateRight(root->droite);
            return rotateLeft(root);
        }
    }

    return root;
}
EtapeAVL *rechercherPlusPetit(EtapeAVL *racine) {
    // Parcours vers le plus à gauche
    while (racine != NULL && racine->gauche != NULL) {
        racine = racine->gauche;
    }
    return racine;
}

EtapeAVL *mettreAJourHauteurEquilibre(EtapeAVL *racine) {
    if (racine == NULL) {
        return NULL;
    }

    // Mettre à jour la hauteur du nœud actuel
    racine->hauteur = 1 + max(height(racine->gauche), height(racine->droite));

    // Calculer le facteur d'équilibre
    int balance = getBalance(racine);

    // Cas de déséquilibre à gauche
    if (balance > 1) {
        if (getBalance(racine->gauche) >= 0) {
            // Cas de la rotation simple à droite
            return rotateRight(racine);
        } else {
            // Cas de la double rotation gauche-droite
            racine->gauche = rotateLeft(racine->gauche);
            return rotateRight(racine);
        }
    }

    // Cas de déséquilibre à droite
    if (balance < -1) {
        if (getBalance(racine->droite) <= 0) {
            // Cas de la rotation simple à gauche
            return rotateLeft(racine);
        } else {
            // Cas de la double rotation droite-gauche
            racine->droite = rotateRight(racine->droite);
            return rotateLeft(racine);
        }
    }

    return racine;
}

EtapeAVL *supprimerPlusPetit(EtapeAVL *racine) {
    // Cas de base : arbre vide
    if (racine == NULL) {
        return NULL;
    }

    // Trouver le plus petit nœud (le plus à gauche)
    if (racine->gauche != NULL) {
        racine->gauche = supprimerPlusPetit(racine->gauche);
    } else {
        // Le plus petit nœud est trouvé, le supprimer
        EtapeAVL *temp = racine->droite;
        free(racine);
        return temp;
    }

    // Mettre à jour la hauteur et équilibrer l'arbre après la suppression
    // (Cela dépend de l'implémentation spécifique des fonctions d'équilibrage AVL)
    // ...

    return racine;
}
// Fonction pour insérer tous les noeuds de la liste dans l'arbre AVL
EtapeAVL *insertAVLFromList(Trajet *pliste, EtapeAVL *arbre) {
    Trajet *tmp = pliste;
    int compter = 0;
    while (tmp != NULL) {
        if ( compter >= 50){
            //si la distance max min supérieur au plus petit de l'arbre, on l'intégre
            if(rechercherPlusPetit(arbre)->distance_max_min < tmp->noeud->distance_max_min){
                arbre = supprimerPlusPetit(arbre);
                arbre = mettreAJourHauteurEquilibre(arbre);
                arbre = insertAVLNode(arbre, tmp->noeud);
            }
            //arbre = mettreAJourHauteurEquilibre(arbre);
        }
        else{
            arbre = insertAVLNode(arbre, tmp->noeud);
        }
        compter ++;
        tmp = tmp->next;
    }
    return arbre;
}

void parcourirEtAfficherAVL(EtapeAVL* root) {
    if (root != NULL) {
        // Parcourir le sous-arbre gauche
        parcourirEtAfficherAVL(root->gauche);

        // Afficher les informations du noeud courant
        printf("ID_trajet : %d, Distance : %.3lf\n", root->id_trajet, root->distance);

        // Parcourir le sous-arbre droit
        parcourirEtAfficherAVL(root->droite);
    }
}

void parcourirEtAfficherAVLDecroissant(EtapeAVL* root) {
    if (root != NULL) {
        // Parcourir le sous-arbre droit en premier (parcours décroissant)
        parcourirEtAfficherAVLDecroissant(root->droite);

        // Afficher les informations du noeud courant
        printf("ID_trajet : %d, Distance : %.3lf, Distance_max_min : %.3lf\n", root->id_trajet, root->distance, root->distance_max_min);

        // Parcourir le sous-arbre gauche
        parcourirEtAfficherAVLDecroissant(root->gauche);
    }
}


// Fonction auxiliaire pour parcourir l'arbre et remplir le tableau
void fillSortedDataDecreasing(struct EtapeAVL* node, struct EtapeAVL* sortedData[50], int* currentIndex) {
    if (node != NULL && *currentIndex < 50) {
        fillSortedDataDecreasing(node->droite, sortedData, currentIndex);

        // Comparaison avec le pointeur node
        if (*currentIndex < 50) {
            sortedData[*currentIndex] = node;
            *currentIndex = *currentIndex + 1;
        }

        fillSortedDataDecreasing(node->gauche, sortedData, currentIndex);
    }
}



// Fonction pour libérer la mémoire allouée pour chaque élément de sortedData
void freeSortedData(struct EtapeAVL* sortedData[50], int currentIndex) {
    for (int i = 0; i < currentIndex; ++i) {
        free(sortedData[i]);
    }
}

// Fonction pour traiter les statistiques et générer le fichier de sortie
void processStats(struct EtapeAVL* root) {
    // Tableau pour stocker les données triées
    struct EtapeAVL* sortedData[50];
    int currentIndex = 0;

    // Fonction auxiliaire pour parcourir l'arbre et remplir le tableau
    fillSortedDataDecreasing(root, sortedData, &currentIndex);

    // Afficher les statistiques et générer les données pour le graphique
    FILE* dataFile = fopen("Temp/Resultat_s2.txt", "w");
    fprintf(dataFile, "#ID Distance_mini Distance_moyenne Distance_maxi Distance_max-Distance_min\n");
    for (int i = 0; i < currentIndex; ++i) {
        fprintf(dataFile, "%d %.2lf %.2lf %.2lf %.2lf\n", sortedData[i]->id_trajet, sortedData[i]->distance_min, sortedData[i]->distance_moyenne, sortedData[i]->distance_max, sortedData[i]->distance_max_min);
    }
    fclose(dataFile);

    // Libération de la mémoire allouée pour chaque élément de sortedData
    freeSortedData(sortedData, currentIndex);
}



int main(){
    FILE *fichier = fopen("Temp/Resultat_s.txt", "r");
    if (fichier == NULL) {
    fprintf(stderr, "Erreur d'ouverture du fichier.\n");
        return 1;
    }
    int id_trajet;
    double distance;
    int compteur;
    EtapeAVL *arbre = NULL;
    Trajet *pliste = NULL; // Initialisez votre liste à NULL
    Trajet *tmp = pliste;
      while (feof(fichier) != true){
      compteur++;
      fscanf(fichier, "%d", &id_trajet);
      fscanf(fichier, "%lf", &distance);
    //printf("ID_trajet : %d, Distance : %.3lf %d\n", id_trajet, distance,compteur);
    EtapeAVL *nouvelle_etape = newEtapeAVL(id_trajet, distance);
    pliste = insertPliste(pliste, nouvelle_etape);
}
    arbre = insertAVLFromList(pliste, arbre);
    //parcourirEtAfficherAVLDecroissant(arbre);
    pliste=NULL;
    processStats(arbre);
    fclose(fichier);
    while (pliste != NULL) {
    Trajet *temp = pliste;
    pliste = pliste->next;
    free(temp);
}

    return 0;
}
