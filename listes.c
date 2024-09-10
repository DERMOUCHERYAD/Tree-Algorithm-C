#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "listes.h"

/* fichier à compléter au besoin */

void init_liste_vide(liste_t* L) {
    
    /* a completer */
    L->tete =NULL;
}

void liberer_liste(liste_t* L) {
    /* a completer */
    // Attention ici c'est libérer une liste pas une cellule 
    cellule_t* p1; 
    cellule_t* p2;
    p1=L->tete;
    while (p1 != NULL) // N'est pas arriver a la fin 
    {
        p2 = p1;
        p1 = p1->suivant;
        free(p2);   // Liberer la cellule pointée par p2
    } 
}


int ajouter_tete(liste_t* L, string c) { /* retourne 0 si OK, 1 sinon  */
    
    /* a completer */
          
     cellule_t *C= malloc(sizeof(cellule_t));
     C->val=c;
     C->suivant=L->tete;
     L->tete=C;
     return 0 ;    
} 

int taille_liste(liste_t* L) {
    int taille = 0;
    cellule_t* courant = L->tete;
    while (courant != NULL) {
        taille++;
        courant = courant->suivant;
    }
    return taille;
}


 

 

