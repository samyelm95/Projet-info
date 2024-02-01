#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct _trajet {
  struct _trajet *fg;
  struct _trajet *fd;
  int id_trajet;
  int eq;
} Trajet;

typedef struct _arbre {
  struct _arbre *fg;
  struct _arbre *fd;
  Trajet *pTrajet;
  char nom[35];
  int eq;
  int ville;
  int nb_trajet;
  int nb_trajet_depart;
} Arbre;

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

//Rempilssage d'un AVL avec les identifiants de trajet 
Trajet *creerTrajet(int id_trajet) {
  Trajet *trajet = malloc(sizeof(Trajet));
  trajet->id_trajet = id_trajet;
  trajet->eq = 0;
  trajet->fd = NULL;
  trajet->fg = NULL;
  return trajet;
}

//Rempilssage de l'AVL principal avec toutes les données du data.csv 
Arbre *creerArbre(char nom[35], int ville, int id_trajet, int id_depart) {
  Arbre *avl = malloc(sizeof(Arbre));
  avl->ville = ville;
  avl->nb_trajet = 1;
  avl->eq = 0;
  strncpy(avl->nom, nom, sizeof(avl->nom) - 1);
  if (id_depart == 1) {
    avl->nb_trajet_depart = 1;
  }
  avl->pTrajet = creerTrajet(id_trajet);
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

Trajet *rotationGauche_trajet(Trajet *trajet) {
  Trajet *pivot = trajet->fd;
  trajet->fd = pivot->fg;
  pivot->fg = trajet;

  int eq_trajet = trajet->eq;
  int eq_piv = pivot->eq;

  trajet->eq = eq_trajet - max(eq_piv, 0) - 1;
  pivot->eq = min2(eq_trajet - 2, eq_trajet + eq_piv - 2, eq_piv - 1);

  return pivot;
}

Trajet *rotationDroite_trajet(Trajet *trajet) {
  Trajet *pivot = trajet->fg;
  trajet->fg = pivot->fd;
  pivot->fd = trajet;

  int eq_trajet = trajet->eq;
  int eq_piv = pivot->eq;

  trajet->eq = eq_trajet - min(eq_piv, 0) + 1;
  pivot->eq = max2(eq_trajet + 2, eq_trajet + eq_piv + 2, eq_piv + 1);

  return pivot;
}

Trajet *rotationDoubleGauche_trajet(Trajet *trajet) {
  trajet->fd = rotationDroite_trajet(trajet->fd);
  return rotationGauche_trajet(trajet);
}

Trajet *rotationDoubleDroite_trajet(Trajet *trajet) {
  trajet->fg = rotationGauche_trajet(trajet->fg);
  return rotationDroite_trajet(trajet);
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

Trajet *equilibreTrajet(Trajet *trajet) {
  if (trajet->eq >= 2) {
    if (trajet->fd->eq >= 0) {
      return rotationGauche_trajet(trajet);
    } else {
      return rotationDoubleGauche_trajet(trajet);
    }
  } else if (trajet->eq <= -2) {
    if (trajet->fg->eq <= 0) {
      return rotationDroite_trajet(trajet);
    } else {
      return rotationDoubleDroite_trajet(trajet);
    }
  }
  return trajet;
}

Arbre *insertion(Arbre *avl, char nom[35], int ville, int id_trajet, int id_depart, int *h) {
    if (avl == NULL) {
        *h = 1;
        return creerArbre(nom, ville, id_trajet, id_depart);
    } else if (ville < avl->ville) {
        avl->fg = insertion(avl->fg, nom, ville, id_trajet, id_depart, h);
        avl->eq--;
        avl = equilibreAvl(avl);
    } else if (ville > avl->ville) {
        avl->fd = insertion(avl->fd, nom, ville, id_trajet, id_depart, h);
        avl->eq++;
        avl = equilibreAvl(avl);
    } else {
        *h = 0;
    }
    
    return avl;
}


Trajet *insertion_trajet(Trajet *trajet, int id_trajet, int *h) {
    if (trajet == NULL) {
        *h = 1;
        return creerTrajet(id_trajet);
    } else if (id_trajet < trajet->id_trajet) {
        trajet->fg = insertion_trajet(trajet->fg, id_trajet, h);
        trajet->eq--;
        trajet = equilibreTrajet(trajet);
    } else if (id_trajet > trajet->id_trajet) {
        trajet->fd = insertion_trajet(trajet->fd, id_trajet, h);
        trajet->eq++;
        trajet = equilibreTrajet(trajet);
    } else {
        *h = 0;
    }
    
    return trajet;
}

Arbre *recherche(Arbre *avl, int id) {
  if (avl == NULL) {
    return NULL;
  } else if (avl->ville == id) {
    return avl;
  } else if (id < avl->ville) {
    return recherche(avl->fg, id);
  } else {
    return recherche(avl->fd, id);
  }
}

Trajet *recherche_trajet(Trajet *trajet, int id) {
  if (trajet == NULL) {
    return NULL;
  } else if (trajet->id_trajet == id) {
    return trajet;
  } else if (id < trajet->id_trajet) {
    return recherche_trajet(trajet->fg, id);
  } else {
    return recherche_trajet(trajet->fd, id);
  }
}

void maj_arbre(Arbre *avl, int id_trajet, int id_etape) {
  if (avl != NULL) {
    if (id_etape == 1) {
      avl->nb_trajet_depart += 1;
    }

    if (recherche_trajet(avl->pTrajet, id_trajet) == NULL) {
      int h = 0;
      avl->pTrajet = insertion_trajet(avl->pTrajet, id_trajet, &h);
      avl->nb_trajet += 1;
    }
  }
}

void trouverTop10(Arbre *arbre, Arbre *top[], int *index) {
  if (arbre == NULL) {
    return;
  }

  trouverTop10(arbre->fd, top, index);

  if (*index <10) {
    top[*index] = arbre;
    (*index)++;
  } else {

    int minIndex = 0;
    for (int i = 1; i <10; i++) {
      if (top[i]->nb_trajet < top[minIndex]->nb_trajet) {
        minIndex = i;
      }
    }

    if (arbre->nb_trajet > top[minIndex]->nb_trajet) {
      top[minIndex] = arbre;
    }
  }
  trouverTop10(arbre->fg, top, index);
}
unsigned int hash(char *str) {
  unsigned int hash = 5381;
  int c;

  while ((c = *str++)) {
    hash = ((hash << 5) + hash) + c;
  }
  return hash;
}



int comparerChaines(const char *chaine1, const char *chaine2) {
  while (*chaine1 && *chaine2) {

    if (*chaine1 == ' ') {
      chaine1++;
      continue;
    }
    if (*chaine2 == ' ') {
      chaine2++;
      continue;
    }

    if (*chaine1 < *chaine2) {
      return -1;
    } else if (*chaine1 > *chaine2) {
      return 1;
    }

    chaine1++;
    chaine2++;
  }

  if (*chaine1) {
    return 1;
  } else if (*chaine2) {
    return -1;
  }

  return 0;
}

void trierListe(Arbre *top[], int taille) {
  int i, j;
  Arbre *temp;

  for (i = 0; i < taille - 1; i++) {
    for (j = 0; j < taille - 1 - i; j++) {
      if (top[j] != NULL && top[j + 1] != NULL && comparerChaines(top[j]->nom, top[j + 1]->nom) > 0) {

        temp = top[j];
        top[j] = top[j + 1];
        top[j + 1] = temp;
      }
    }
  }
}


void afficherTop10(Arbre *avl) {
  Arbre *top[10];
  for (int i = 0; i <10; i++) {
    top[i] = NULL;
  }

  int index = 0;
  trouverTop10(avl, top, &index);

  trierListe(top,10);

  for (int i = 0; i <10; i++) {
    if (top[i] != NULL) {
      printf("%s;%d;%d\n",  top[i]->nom,top[i]->nb_trajet,top[i]->nb_trajet_depart);
    }
  }
}

void libererMemoireTrajet(Trajet *trajet) {
  if (trajet != NULL) {
 
    libererMemoireTrajet(trajet->fg);
    libererMemoireTrajet(trajet->fd);
    free(trajet);
  }
}

void libererMemoireArbre(Arbre *avl) {
  if (avl != NULL) {
 
   libererMemoireTrajet(avl->pTrajet);
    libererMemoireArbre(avl->fg);
    libererMemoireArbre(avl->fd);
 
    
    free(avl);
  }
}

int main() {
  char villeA[35];
  char villeB[35];
  int trajet, etape;
  Arbre *avl = NULL;
  int h = 0;

  while (scanf("%d;%d;%[^;];%[^\n]\n", &trajet, &etape, villeA, villeB)==4) {
   

      int id_villeA = hash(villeA);
      int id_villeB = hash(villeB);

      Arbre *temp1 = recherche(avl, id_villeA);
      if (temp1 == NULL) {
        avl = insertion(avl, villeA, id_villeA, trajet, etape, &h);
      } else {
        
        maj_arbre(temp1, trajet, etape);
      }

      Arbre *temp2 = recherche(avl, id_villeB);
      if (temp2 == NULL) {
        avl = insertion(avl, villeB, id_villeB, trajet, 0, &h);
      } else {
      	
        maj_arbre(temp2, trajet, 0);
      }
  }
  
  afficherTop10(avl);
  libererMemoireArbre(avl);

  return 0;
}
