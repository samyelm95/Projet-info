#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure AVL pour les données des trajets
typedef struct AVLNode {
    int id_trajet;
    int id_etape;
    char ville_A;
    char Ville_B;
    float distance;
    char conducteur;
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
} AVLNode;

// Implémentation des opérations AVL

void parcoursInfixe(Noeud *racine) {
    if (racine != NULL) {
        parcoursInfixe(racine->gauche);
        printf("ID: %d, Ville: %s\n", racine->trajet.id, racine->trajet.ville);
        parcoursInfixe(racine->droite);
    }
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(AVLNode *node) {
    if (node == NULL) {
        return 0; // La hauteur d'un nœud vide est 0
    } else {
        int left_height = height(node->left);
        int right_height = height(node->right);

        return 1 + max(left_height, right_height);
    }
}

AVLNode *newAVLNode(int id_trajet, double distance) {
    AVLNode *node = (AVLNode *)malloc(sizeof(AVLNode));
    if (node == NULL) {
        perror("Erreur d'allocation mémoire");
        exit(EXIT_FAILURE);
    }
    node->id_trajet = id_trajet;
    node->distance = distance;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

AVLville *insert(AVLville *root, int id_trajet, int a) {
    // Effectuer l'insertion de manière normale
    if (root == NULL) {
        return newAVLNode(id_trajet, distance);
    }
    if (id_trajet < root->id_trajet) {
        root->left = insert(root->left, id_trajet, distance);
    } else if (id_trajet > root->id_trajet) {
        root->right = insert(root->right, id_trajet, distance);
    } else {
        // Si l'identifiant du trajet est déjà présent, faites la gestion appropriée
        return root;
    }
    // Mettre à jour la hauteur du nœud actuel
    root->height = 1 + max(height(root->left), height(root->right));

    // Obtenir le facteur d'équilibre du nœud
    int balance = getBalance(root);

    // Cas de déséquilibre à gauche
    if (balance > 1) {
        if (id_trajet < root->left->id_trajet) {
            return rotateRight(root);
        } else if (id_trajet > root->left->id_trajet) {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
    }
AVLNode *insert(AVLNode *root, int id_trajet, double distance) {
    // Effectuer l'insertion de manière normale
    if (root == NULL) {
        return newAVLNode(id_trajet, distance);
    }
    if (id_trajet < root->id_trajet) {
        root->left = insert(root->left, id_trajet, distance);
    } else if (id_trajet > root->id_trajet) {
        root->right = insert(root->right, id_trajet, distance);
    } else {
        // Si l'identifiant du trajet est déjà présent, faites la gestion appropriée
        return root;
    }
    // Mettre à jour la hauteur du nœud actuel
    root->height = 1 + max(height(root->left), height(root->right));

    // Obtenir le facteur d'équilibre du nœud
    int balance = getBalance(root);

    // Cas de déséquilibre à gauche
    if (balance > 1) {
        if (id_trajet < root->left->id_trajet) {
            return rotateRight(root);
        } else if (id_trajet > root->left->id_trajet) {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
    }

    // Cas de déséquilibre à droite
    if (balance < -1) {
        if (id_trajet > root->right->id_trajet) {
            return rotateLeft(root);
        } else if (id_trajet < root->right->id_trajet) {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
    }

    return root;
}

AVLNode *rotateRight(AVLNode *y) {
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;

    // Rotation
    x->right = y;
    y->left = T2;

    // Mise à jour des hauteurs
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

AVLNode *rotateLeft(AVLNode *x) {
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;

    // Rotation
    y->left = x;
    x->right = T2;

    // Mise à jour des hauteurs
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(AVLNode *node) {
    if (node == NULL) {
        return 0; // Le facteur d'équilibre d'un nœud vide est 0
    } else {
        return height(node->left) - height(node->right);
    }
}



