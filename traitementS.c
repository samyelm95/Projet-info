#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure pour représenter la distance d'une étape
typedef struct {
    int id_trajet; 
    float distance;
} distance;


typedef struct{
    int id_trajet;
    float distance;
    int v;
    float moyenne;
    float max;
    float min;
    struct trajet_stats* next;
}trajet_stats;



//création chainon trajet_stats
trajet_stats* creer(distance p1[],int nombre_trajets){
    trajet_stats* a;
    a=malloc(sizeof(trajet_stats));
    if(a==NULL){
        exit(1);
    }else{
        a->id_trajet=p1[nombre_trajets].id_trajet;
        a->distance=p1[nombre_trajets].distance;
        a->v=1;
        a->moyenne=a->distance/a->v;
        a->max=p1[nombre_trajets].distance;
        a->min=p1[nombre_trajets].distance;
        a->next=NULL;
    }
    return a;
};

//insertion liste moyenne par id trajet
trajet_stats *insertstat(trajet_stats *m,distance p1[],int nombre_trajets){ 
        trajet_stats* tmp;
        tmp=m;
        if(tmp==NULL){
             trajet_stats* a;
             a=creer(p1,nombre_trajets);
             tmp->next=a;
             return m;
        }else if(tmp->id_trajet=p1[nombre_trajets].id_trajet){
             tmp->distance=tmp->distance+p1[nombre_trajets].distance;
             tmp->v++;
             tmp->moyenne=tmp->distance/tmp->v;
             if(p1[nombre_trajets].distance<tmp->min){
                tmp->min=p1[nombre_trajets].distance;
             }else if(p1[nombre_trajets].distance>tmp->max){
                tmp->max=p1[nombre_trajets].distance;
             };
             return m;
        }else if (tmp->id_trajet>p1[nombre_trajets].id_trajet){
             tmp=insertstat(tmp->next,p1,nombre_trajets);
        }else{
             trajet_stats* a;
             a=creer(p1,nombre_trajets);
             a->next=tmp->next;
             tmp->next=a;
             return m;
        }
};

typedef struct AVLNode {
    trajet_stats* data;
    struct AVLNode* left;
    struct AVLNode* right;
    int height;
} AVLNode;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(AVLNode* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

int getBalance(AVLNode* node) {
    if (node == NULL) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

AVLNode* insertAVL(AVLNode* node, trajet_stats* data) {
    if (node == NULL) {
        AVLNode* newNode = (AVLNode*)malloc(sizeof(AVLNode));
        newNode->data = data;
        newNode->left = newNode->right = NULL;
        newNode->height = 1;
        return newNode;
    }

    if (data->max < node->data->max ||
        (data->max == node->data->max && data->min < node->data->min) ||
        (data->max == node->data->max && data->min == node->data->min && data->moyenne < node->data->moyenne)) {
        node->left = insertAVL(node->left, data);
    } else {
        node->right = insertAVL(node->right, data);
    }

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && data->max < node->left->data->max) {
        return rightRotate(node);
    }

    // Right Right Case
    if (balance < -1 && data->max > node->right->data->max) {
        return leftRotate(node);
    }

    // Left Right Case
    if (balance > 1 && data->max > node->left->data->max) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && data->max < node->right->data->max) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

AVLNode* minValueNode(AVLNode* node) {
    AVLNode* current = node;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

AVLNode* deleteNode(AVLNode* root, trajet_stats* data) {
    if (root == NULL) {
        return root;
    }

    if (data->max < root->data->max ||
        (data->max == root->data->max && data->min < root->data->min) ||
        (data->max == root->data->max && data->min == root->data->min && data->moyenne < root->data->moyenne)) {
        root->left = deleteNode(root->left, data);
    } else if (data->max > root->data->max ||
               (data->max == root->data->max && data->min > root->data->min) ||
               (data->max == root->data->max && data->min == root->data->min && data->moyenne > root->data->moyenne)) {
        root->right = deleteNode(root->right, data);
    } else {
        if (root->left == NULL) {
            AVLNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            AVLNode* temp = root->left;
            free(root);
            return temp;
        }

        AVLNode* temp = minValueNode(root->right);

        root->data = temp->data;

        root->right = deleteNode(root->right, temp->data);
    }

    if (root == NULL) {
        return root;
    }

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0) {
        return rightRotate(root);
    }

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0) {
        return leftRotate(root);
    }

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

AVLNode* suppMin(AVLNode* root) {
    if (root == NULL) {
        return root;
    }

    AVLNode* minNode = minValueNode(root);
    root = deleteNode(root, minNode->data);

    return root;
}

//Fonctio1n compter nombre chainons
int nombrechainon(AVLNode* root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + nombrechainon(root->left) + nombrechainon(root->right);
}

//parcours ordre decroissant
void parcours(AVLNode* root) {
    if (root != NULL) {
        parcours(root->right);
        float c;
        c=root->data->distance/root->data->v;
        printf("Max: %.2f, Min: %.2f, Moyenne: %.2f\n", root->data->max, root->data->min,c) ;
        parcours(root->left);  
    }
}

//supp trajet_stats
void suppliste(trajet_stats* head) {
    trajet_stats* current = head;
    trajet_stats* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <option> <fichier.csv>\n", argv[0]);
        return 1;
    }
    int nombre_trajets = 0;
    char option = argv[1][0];
    char *fichier_csv = argv[2];

    if (option == 's') {
        FILE *fichier = fopen(fichier_csv, "r");
        if (fichier == NULL) {
            fprintf(stderr, "Erreur d'ouverture du fichier.\n");
            return 1;
        }

        distance *p1= NULL;
        int nombre_trajets = 0;
        while (fscanf(fichier, "%d,%f\n", &p1[nombre_trajets].id_trajet, &p1[nombre_trajets].distance) == 2) {
            nombre_trajets++;
            p1 = realloc(p1, (nombre_trajets + 1) * sizeof(distance));
            if (p1 == NULL) {
                fprintf(stderr, "Erreur d'allocation de mémoire.\n");
                return 1;
            }
        }

        trajet_stats* m = NULL;
        for (int i = 0; i < nombre_trajets; i++) {
            m = insertstat(m, p1,i);
        }

        AVLNode *ordre = NULL;
        trajet_stats *tmp = m;
        while (tmp != NULL) {
            ordre = insertAVL(ordre, tmp);
            tmp = tmp->next;
        }

        while (nombrechainon(ordre) > 50) {
            ordre = suppMin(ordre);
        }

        parcours(ordre);
        suppliste(m); // Libérer mémoire allouée à la liste

        while (nombrechainon(ordre) > 0) {
            ordre = suppMin(ordre);
        } // Supprimer l'AVL

        free(p1);      // Libérer la mémoire allouée
        fclose(fichier); // Fermer le fichier
    } else {
        fprintf(stderr, "Option non reconnue.\n");
        return 1;
    }

    return 0;
}
