#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "arbres.h"
#include "arbresphylo.h"
#include "listes.h"


void analyse_arbre_rec (arbre racine, int* nb_esp, int* nb_carac)
{  

   // le cas de l'arbre est vide  
   if (racine==NULL){
      return ; // car la fonction est void 
   }
   if ((racine->gauche==NULL) && (racine->droit==NULL)) {
      (*nb_esp)=(*nb_esp)+1; //incrémenter les espèces 
   }
   else {   
   *nb_carac=*nb_carac+1;   //incrémenter les caractèristiques 

   //  pour des cas ou on a des arbres droits ou gauches ....
   if ((racine->gauche)==NULL) { analyse_arbre_rec(racine->gauche,nb_esp,nb_carac);}
   if ((racine->droit)==NULL) { analyse_arbre_rec(racine->gauche,nb_esp,nb_carac);}

   else {    
   analyse_arbre_rec(racine->gauche,nb_esp,nb_carac);
   analyse_arbre_rec(racine->droit,nb_esp,nb_carac);
   }
   }
   
} 

//  Initialiser les especes et les caractèrestiques a zero
void analyse_arbre (arbre racine, int* nb_esp, int* nb_carac) {
   *nb_esp=0;
   *nb_carac=0;
   analyse_arbre_rec( racine, nb_esp, nb_carac);
}






/* ACTE II */                  
/* Recherche l'espece dans l'arbre. Modifie la liste passée en paramètre pour y mettre les
 * caractéristiques. Retourne 0 si l'espèce a été retrouvée, 1 sinon.
*/
int rechercher_espece_rec(arbre racine, char *espece, liste_t* seq) {
   if (racine == NULL) {
      return 1; // Aucune espèce trouvée
   }

   if ((racine->gauche == NULL) && (racine->droit == NULL)) {
      if (strcmp(racine->valeur, espece) == 0) {
         return 0; // Espèce trouvée
      }
   }

   if (rechercher_espece_rec(racine->droit, espece, seq) == 0) {
      ajouter_tete(seq, racine->valeur);
      return 0; // Espèce trouvée à droite
   }

   if (rechercher_espece_rec(racine->gauche, espece, seq) == 0) {
      return 0; // Espèce trouvée à gauche
   }

   return rechercher_espece_rec(racine->gauche,espece,seq) ; // Espèce non trouvée
}

int rechercher_espece(arbre racine, char *espece, liste_t* seq) {
   init_liste_vide(seq);
   return rechercher_espece_rec(racine, espece, seq);
}



/* Doit renvoyer 0 si l'espece a bien ete ajoutee, 1 sinon, et ecrire un 
 * message d'erreur.
 */
int ajouter_espece (arbre* racine, char* espece, cellule_t* seq) {
   
   if(*racine == NULL){
         if(seq == NULL){ //Si la racine et la séquence sont nuls, on ajoute juste l'espèce
             noeud* a = nouveau_noeud ();
             a -> valeur = espece;
             *racine = a;
             return 0;
         }
         else{ // Si la racine est nul et la séquence n'est pas nul, on ajoute
               //juste au côté droit, càd un appel récursif sur le ss arbre droit
             noeud* a = nouveau_noeud ();
             a -> valeur =seq ->val;
             *racine = a;
             return ajouter_espece(&((*racine)->droit),espece,seq->suivant);
         }
     }
   //   Si on tombe sur une feuille 
   // Si la séquence est vide, une autre espèce possède les mêmes carctéristiques
   else if((*racine)->gauche == NULL && (*racine)->droit == NULL){
          if(seq == NULL){
            printf("Erreur: Ne peut ajouter %s car possède les mêmes caractéristiques que %s.",espece,(*racine) ->valeur);
            return 1;
          }
         //il reste encore des caractéristiques dans seq : l'espèce a 
         // des carctéristiques qui ne sont pas dans l'arbre
         noeud* a = nouveau_noeud ();
         a -> valeur = seq->val;
         a->gauche = *racine;
         *racine = a;
         return ajouter_espece(&((*racine)->droit),espece,(seq)->suivant);
     }
   else 
         if(seq == NULL){
         return 1;
      }
      // L'arbre n'est pas nul et la séquence non plus
     {
         if(strcmp(seq->val,(*racine)->valeur) == 0){ //Si la racine et la première caractéristique correspondent,
         // on fait un appel récursif sur le côté droit
               return ajouter_espece(&((*racine)->droit),espece,seq->suivant);
         }
         else{// Sinon, ajouter complètement à gauche
               return ajouter_espece(&((*racine)->gauche),espece,seq);
         }
     }

   return 0;
}

/* Doit afficher la liste des caractéristiques niveau par niveau, de gauche
 * à droite, dans le fichier fout.
 * Appeler la fonction avec fout=stdin pour afficher sur la sortie standard.
 */

//  utilisant deux files pour réaliser le parcours en largeur de l'arbre.
void afficher_par_niveau (arbre racine, FILE* fout) {
   
   if (racine == NULL) {
        return;
    }

    file f1, f2;
    initialiser_file(&f1, 1000);
    initialiser_file(&f2, 1000);

    enfiler(&f1, racine);

    while (!file_est_vide(&f1) || !file_est_vide(&f2)) {
        while (!file_est_vide(&f1)) {
            arbre noeud_courant = defiler(&f1);

            // Vérifier si le nœud actuel est une feuille
            if (noeud_courant->gauche != NULL || noeud_courant->droit != NULL) {
                fprintf(fout, "%s ", noeud_courant->valeur);

                if (noeud_courant->gauche != NULL) {
                    enfiler(&f2, noeud_courant->gauche);
                }

                if (noeud_courant->droit != NULL) {
                    enfiler(&f2, noeud_courant->droit);
                }
            }
        }

        fprintf(fout, "\n");  // Nouvelle ligne pour le prochain niveau

        // Échanger les files
        file tmp = f1;
        f1 = f2;
        f2 = tmp;
    }
}

// Acte 4


int ajouter_carac(arbre* a, char* carac, cellule_t* seq) {
   
   return 0;
}
