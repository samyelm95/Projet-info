#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// structure de l'AVL
typedef struct _arbre {
  struct _arbre *fg;
  struct _arbre *fd;
  int id_trajet;
  int nb_trajet;
  int distance;
  int eq;
  int min;
  int max;
  float diff;
  float moy;
} Arbre;

// structure de la liste qui trie les noeud de l'AVL
typedef struct _liste {
    Arbre *noeud;
    struct _liste *next;
} liste;
 


int max(int a, int b) {
 return (a > b) ? a : b;
}
int min(int a, int b) {
 return (a < b) ? a : b;
}

int max2(int a, int b, int c) {
return max(max(a, b), c);
}

int min2(int a, int b, int c) {
 return min(min(a, b), c);
}

//Rempilssage de l'AVL avec les données du data.csv 
Arbre *creerArbre(int id_trajet, int distance) {
  Arbre *avl = malloc(sizeof(Arbre));
  avl->nb_trajet = 1;
  avl->eq = 0;
  avl->max=distance;
  avl->min=distance;
  avl->diff = 0;
  avl->moy=distance/avl->nb_trajet;
  avl->fg = NULL;
  avl->fd = NULL;
  return avl;
}

Arbre *rotationGauche(Arbre *avl) {
  Arbre *pivot = avl->fd;
  avl->fd = pivot->fg;
  pivot->fg = avl;

  int eq_avl = avl->eq;
  int eq_piv = pivot->eq;

  avl->eq = eq_avl - max(eq_piv, 0) - 1;
  pivot->eq = min2(eq_avl - 2, eq_avl + eq_piv - 2, eq_piv - 1);

  return pivot;
}

Arbre *rotationDroite(Arbre *avl) {
  Arbre *pivot = avl->fg;
  avl->fg = pivot->fd;
  pivot->fd = avl;

  int eq_avl = avl->eq;
  int eq_piv = pivot->eq;

  avl->eq = eq_avl - min(eq_piv, 0) + 1;
  pivot->eq = max2(eq_avl + 2, eq_avl + eq_piv + 2, eq_piv + 1);

  return pivot;
}

Arbre *rotationDoubleGauche(Arbre *avl) {
  avl->fd = rotationDroite(avl->fd);
  return rotationGauche(avl);
}

Arbre *rotationDoubleDroite(Arbre *avl) {
  avl->fg = rotationGauche(avl->fg);
  return rotationDroite(avl);
}

Arbre *equilibreAvl(Arbre *avl) {
  if (avl->eq >= 2) {
    if (avl->fd->eq >= 0) {
      avl = rotationGauche(avl);
    } else {
      avl = rotationDoubleGauche(avl);
    }
  } else if (avl->eq <= -2) {
    if (avl->fg->eq <= 0) {
      avl = rotationDroite(avl);
    } else {
      avl = rotationDoubleDroite(avl);
    }
  }
  return avl;
}

// Fonction remplissage de l'AVL avec actualisation du min, max et moyenne
Arbre *insertion(Arbre *avl, int id_trajet, int distance, int *h) {
    if (avl == NULL) {
        *h = 1;
        return creerArbre(id_trajet, distance);
    } else if (id_trajet < avl->id_trajet) {
        avl->fg = insertion(avl->fg, id_trajet, distance, h);
       *h = -*h;
        
    } else if (id_trajet > avl->id_trajet) {
        avl->fd = insertion(avl->fd, id_trajet,distance, h);
        
       
    } else {
        *h = 0;
        avl->nb_trajet ++;
        avl->distance=avl->distance+distance;
        avl->moy=distance/avl->nb_trajet;
        if (avl->max<distance){
          avl->max=distance;
        }
        if (avl->min>distance){
          avl->min=distance;
        }
        avl->diff = avl->max - avl->min;       
    }
    if (h*==0){
        avl->eq = avl->eq + *h;
        avl = equilibrage(avl);
        if (a->equilibre == 0){
            *h = 0;
        }
        else {
          h* = 1;
        }
    return avl;
}


Arbre *insertionv2(Arbre *avl, Arbre* new, int *h) {
    Arbre* n  = malloc(sizeof(Arbre));
    n->nb_trajet = avl->nb_trajet;
    n->eq = avl->eq 
    n->max =avl->max
    n->min = avl->min 
    n->diff = avl->diff
    n -> moy = avl->moy
    n->moy = avl->fg = NULL;
    n-> moy = avl->fd = NULL;
    if (avl == NULL) {
        *h = 1;
        return n;
    } else if (n->diff =< avl->diff) {
        avl->fg = insertionv2(avl->fg, new, h);
       *h = -*h;
        
    } else if (id_trajet > avl->id_trajet) {
        avl->fd = insertionv2(avl->fd, new, h);
        
       
    }
    if (h*==0){
        avl->eq = avl->eq + *h;
        avl = equilibrage(avl);
        if (a->equilibre == 0){
            *h = 0;
        }
        else {
          h* = 1;
        }
    return avl;
}
//Insertion dans la liste par ordre décroissant en fonction du max et du min de chaque noeud 
liste* insert_liste(liste* p1,Arbre* avl){
  liste *tmp;
  liste *new;
  tmp=p1;
  if (p1 == NULL || avl->max > p1->noeud->max) {
        new = (liste *)malloc(sizeof(liste));
        new->noeud=avl;
        new->next = p1->next;
        p1 = new;
  } else {
        while (tmp->next != NULL && tmp->next->noeud->max > avl->max) {
            tmp = tmp->next;
        }
        if(tmp->next->noeud->max = avl->max){
          if(tmp->next->noeud->min>avl->min){
            new = (liste *)malloc(sizeof(liste));
            new->noeud=avl;
            new->next = tmp->next;
            tmp->next = new;
          }else{
            tmp=tmp->next;0
            new = (liste *)malloc(sizeof(liste));
            new->noeud=avl;
            new->next = tmp->next;
            tmp->next = new;
          }
        }
      }
}

//Parcours de l'AVL et insertion de tous les noeuds dans la liste
void parcours_scan(Arbre* avl){
  liste* p1;
  p1=insert_liste(p1,avl);
  parcours_scan(avl->fg);
  parcours_scan(avl->fd);
};

Arbre* parcours_scanv2(Arbre* avl, Arbre* avl2, int *h){
  liste* p1;
  avl = insertionv2(avl, avl2,h);
  parcours_scan(avl->fg);
  parcours_scan(avl->fd);
  return avl2;
};

//Affichage 50 première valeurs de la liste
void afficherTop50(liste *p1, int nombreElements) {
    liste *tmp = p1;
    int i = 0;
    while (tmp != NULL && i < nombreElements) {
        printf("%d,%d,%f/n ", tmp->noeud->max,tmp->noeud->min,tmp->noeud->moy);
        tmp = tmp->next;
        i++;
    }
    printf("\n");
}

void libererMemoire(liste *p1) {
    liste *tmp = p1;
    liste *next;

    while (tmp != NULL) {
        next= tmp->next;
        free(tmp->noeud);
        free(tmp);
        tmp = next;
    }

    p1 = NULL; // La tête de la liste est maintenant NULL car la liste est vide
}

int main() {
  int distance;
  int id_trajet;
  Arbre *avl = NULL;
  Abre *avl2 = NULL;
  liste* p1;
  int* h = 0;

  while (scanf("%d;%d\n", &id_trajet, &distance)==2) {
      avl=insertion(avl,id_trajet,distance,h);
  };

  avl2 = parcours_scanv2(avl,avl2,h);  
  //parcours_scan(avl);
  afficherTop50(p1,50);
  //libererMemoire(p1);

  return 0;
}
