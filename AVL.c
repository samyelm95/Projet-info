#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure AVL pour les villes
typedef struct AVLville {
    int id_trajet;
    int d;
    int hauteur;
    struct AVLville *gauche;
    struct AVLville *droite;
} AVLville;

//structure liste des différentes villes
typedef struct{
    char ville[50];
    struct ville* next;
}ville;

// Structure pour représenter une étape
typedef struct {
    int id_trajet;
    char ville_depart[50];
    char ville_arrivee[50];
} Etape;

// Structure pour représenter une ville avec le nombre de trajets total et le nombre de départs
typedef struct Ville {
    char nom[50];
    int trajet_total;
    int departs;
    struct Ville* next
} Ville;

// Structure pour représenter la distance d'une étape
typedef struct {
    int id_trajet;
    int id_etape;
    int distance;
} Distance;


int max(int a, int b) {
    return (a > b) ? a : b;
}

int getBalance(AVLville *node) {
    if (node == NULL) {
        return 0; // Le facteur d'équilibre d'un nœud vide est 0
    } else {
        return height(node->gauche) - height(node->droite);
    }
}

int height(AVLville *node) {
    if (node == NULL) {
        return 0; // La hauteur d'un nœud vide est 0
    } else {
        int gauche_height = height(node->gauche);
        int droite_height = height(node->droite);

        return 1 + max(gauche_height, droite_height);
    }
}

AVLville *newAVLville(int id_trajet, int a) {
    AVLville *node = (AVLville *)malloc(sizeof(AVLville));
    if (node == NULL) {
        perror("Erreur d'allocation mémoire");
        exit(EXIT_FAILURE);
    }
    node->id_trajet = id_trajet;
    node->d = a;
    node->gauche = NULL;
    node->droite = NULL;
    node->hauteur = 1;
    return node;
}

AVLville *rotateRight(AVLville *y) {
    AVLville *x = y->gauche;
    AVLville *T2 = x->droite;

    // Rotation
    x->droite = y;
    y->gauche = T2;

    // Mise à jour des hauteurs
    y->hauteur = max(height(y->gauche), height(y->droite)) + 1;
    x->hauteur = max(height(x->gauche), height(x->droite)) + 1;

    return x;
}

AVLville *rotateLeft(AVLville *x) {
    AVLville *y = x->droite;
    AVLville *T2 = y->gauche;

    // Rotation
    y->gauche = x;
    x->droite = T2;

    // Mise à jour des hauteurs
    x->hauteur = max(height(x->gauche), height(x->droite)) + 1;
    y->hauteur = max(height(y->gauche), height(y->droite)) + 1;

    return y;
}


AVLville *insert(AVLville *root, int id_trajet, int a) {
    // Effectuer l'insertion de manière normale
    if (root == NULL) {
        return newAVLville(id_trajet, a);
    }
    if (id_trajet < root->id_trajet) {
        root->gauche = insert(root->gauche, id_trajet, a);
    } else if (id_trajet > root->id_trajet) {
        root->droite = insert(root->droite, id_trajet, a);
    } else {
        return root;
    }
    // Mettre à jour la hauteur du nœud actuel
    root->hauteur = 1 + max(height(root->gauche), height(root->droite));

    // Obtenir le facteur d'équilibre du nœud
    int balance = getBalance(root);

    // Cas de déséquilibre à gauche
    if (balance > 1) {
        if (id_trajet < root->gauche->id_trajet) {
            return rotateRight(root);
        } else if (id_trajet > root->gauche->id_trajet) {
            root->gauche = rotateLeft(root->gauche);
            return rotateRight(root);
        }
    }
}


//fonction insertion ville liste des villes
ville* insertionville(ville* pliste, char vil){
    ville* tmp=pliste;
    if (tmp==NULL){
        strcpy(tmp->ville, vil);
        tmp->next=NULL;
        return pliste;
    }else if(strcpy(tmp->ville, vil)){
        exit(1);
    }else{
        tmp=tmp->next;
    }
 }

//Fonction insertion liste par ordre décroissant des villes les plus traversées
Ville *insert_stat(Ville* l1,ville *pliste,int k,int l){
    Ville *tmp=NULL;
    tmp=l1;
    Ville* new = (Ville*)malloc(sizeof(ville));
    if (new == NULL) {
        perror("Erreur d'allocation mémoire");
        exit(EXIT_FAILURE);
    };
    strcpy(new->nom, pliste->ville);
    new->trajet_total=k;
    new->departs=l;
    if(tmp=NULL){
        new->next=NULL;
        l1->next=new;
        return l1;
    };
    if(l1==NULL && k>=l1->trajet_total){
        new->next=l1->next;
        l1->next=new;
        return l1;
    };
    while (tmp->next != NULL && (tmp->next)->trajet_total > k) {
        tmp=tmp->next;
    };
    new->next=tmp->next;
    tmp->next=new;
    return l1;
};

//Fonctio1n compter nombre villes diff
int nombre_chainon(ville* pliste){
    int v=0;
    while(pliste!=NULL){
        v++;
        pliste=pliste->next;
    };
    return v;
};

//Fonction parcoursInfixe
void parcoursInfixe(AVLville *racine) {
    if (racine != NULL) {
        parcoursInfixe(racine->gauche);
        parcoursInfixe(racine->droite);
    }
}

//Fonction pour compter le nombre de noeuds départ dans un avl
int compterDépart(AVLville *racine){
    int v=0;
    if (racine != NULL && racine->d==1) {
        v++;
        parcoursInfixe(racine->gauche);
        parcoursInfixe(racine->droite);
    }else{
        parcoursInfixe(racine->gauche);
        parcoursInfixe(racine->droite);
    };
    return v;
};

// Fonction pour compter le nombre de nœuds dans un arbre AVL
int compterNoeuds(AVLville *racine) {
    if (racine == NULL) {
        return 0;
    }
    return 1 + compterNoeuds(racine->gauche) + compterNoeuds(racine->droite);
}

void desalouerVille(Ville* l1){
    while (l1 != NULL) {
        Ville *aLiberer = l1;
        l1 = l1->next;
        free(aLiberer);
    };
};

void desalouerville(ville* l1){
    while (l1 != NULL) {
        Ville *aLiberer = l1;
        l1 = l1->next;
        free(aLiberer);
    };
};
