#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "listes.h"
#include "arbres.h"

noeud* nouveau_noeud(void)
{
    noeud *n = (noeud*)malloc(sizeof(noeud));
    assert (n!=NULL);
    n->valeur = NULL;
    n->gauche = NULL;
    n->droit  = NULL;
    return n;
}


/* buffer pour lire les caractères des espèces sous forme de "mots" (words) */
#define MAX_WORD_SIZE 255
char buffer[MAX_WORD_SIZE+1];

/* Variable globale qui contient le prochain caractère à traiter */
static char next_char = ' ';

/* Supprime tous les espaces, tabulations, retour à la ligne */
#define GLOB(f) \
    while(isspace(next_char)) { \
        next_char = fgetc(f);\
    }


/* Fonction récursive qui lit un sous-arbre */
/* Appelée une fois à la racine (debut du fichier), puis récursivement
 * pour chaque nœud interne rencontré. */
arbre lire_arbre (FILE *f)
{
    arbre racine;

    GLOB(f); /* lit dans next_char le premier caractère non vide */

    if (next_char == '/') {
        next_char = ' '; /* on ne garde pas '/' en mémoire */
        return NULL;
    }

    if (next_char == ')') {
        return NULL;
    }

    if (next_char != '(') {
        fprintf(stderr, "Error while reading binary tree : '(' or ')' expected at position %ld\n", ftell(f));
        exit (1);
    }

    /* On remplit le buffer tant qu'on lit des caractères alphanumériques */
    char *p = buffer; /* début du buffer */
    next_char = ' '; GLOB(f);

    do {
        *p = next_char;       /* sauvegarde du char courant */
        next_char = fgetc(f);
        p++;
        assert (p < buffer + MAX_WORD_SIZE);
    } while (! isspace (next_char) && next_char != '(' && next_char != ')');
    /* on arrète si le char suivant est un espace ou une parenthèse */
    *p='\0'; /* on ferme la chaîne de caractères dans le buffer */

    racine = nouveau_noeud();
    racine->valeur = strdup(buffer); /* dupliquer le mot lu */

    GLOB(f);

    if (next_char == ')') {
        next_char = ' '; /* on est sur une feuille, on prépare la lecture du prochain nœud */
    }
    else {
        racine->gauche = lire_arbre (f); /* appel récursif pour le fils gauche */
        racine->droit  = lire_arbre (f); /* idem pour le droit */

        GLOB(f); /* lit jusqu'au ')' fermant */

        if (next_char != ')') {
            fprintf(stderr, "Error while reading binary tree: ')' expected\n");
            exit(1);
        }
        next_char = ' '; /* on ne garde pas la parenthèse en mémoire */
    }
    return racine;
}



void gen_dot(noeud *racine, FILE* f){
    if(racine == NULL){  //* Fichier vide donc on a rien 
        return;
    }
    // On remarque que tous les noeuds gauches sont de label "Non"
    gen_dot(racine->gauche, f);
    if(racine->gauche != NULL){
        // Affichage selon le format demandé
        fprintf(f, "    %s -> %s [label = \"%s\"]\n", racine->valeur, racine->gauche->valeur, "non");
    }
    // Pareil pour les noueds droits
    gen_dot(racine->droit, f);
    if(racine->droit != NULL){
        fprintf(f, "    %s -> %s [label = \"%s\"]\n", racine->valeur, racine->droit->valeur, "oui");
    }
}
// On utilise la fonction gen_dot dans notre affichage 
void affiche_arbre (noeud *racine)
{
    FILE* f = fopen("arbre_modifie.dot", "w"); // Ecrire dans un ficher.dot
    fprintf(f, "digraph arbre {\n"); // On suit toujours le format donné
    if(racine == NULL){
        return;        // Arbre vide 
    }
    gen_dot(racine, f);   
    fprintf(f, "}");
    fclose(f); 
}


 void initialiser_file(file* file, int capacite) { 
    file->elements = malloc(sizeof(arbre) * capacite);
    file->taille = 0;
    file->capacite = capacite;
    file->avant = 0;
    file->arriere = -1;
}   
int file_est_vide(file* file) {
    return file->taille == 0;
}
int file_est_pleine(file* file) {
    return file->taille == file->capacite;
}
void enfiler(file* file, arbre element) {
    if (!file_est_pleine(file)) {
        file->arriere = (file->arriere + 1) % file->capacite;
        file->elements[file->arriere] = element;
        file->taille++;
    }
}
arbre defiler(file* file) {
    if (!file_est_vide(file)) {
        arbre element = file->elements[file->avant];
        file->avant = (file->avant + 1) % file->capacite;
        file->taille--;
        return element;
    }
    return NULL;
}

    
    


