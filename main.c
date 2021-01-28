#include <stdio.h> /* bibliotheque d'affichage a l'ecran et ecriture clavier */
#include <time.h> /* bibliotheque pour utiliser un timer */
#include <stdlib.h> /* bibliotheque d'utilisation des fonctions generales */
#include "parking.h" /* inclure le header de parking.h*/

#define NBT 30 // pour un nombre de places fixe et pas d'erreus au noiveau du tableau

const int unit = 1200; //prinx d'une demis heure au parking
int mtb0, mtb1; // variable globale moteur de la berrieres entree et sortie
time_t Tp[NBT]; // Tableau contenant les tickets de parking : heures d'entree des vehicules dans le parking
time_t zero; // L'instant de reference pour la RAZ des cases du tableau des tickets
int total;

int main(){

	int nbp=0, ve=0, vs=0; /* Le parking est initialement vide:nbp=noombre de place occupés ,ve capteur entre ,vs: capteur sortie */

    total = recupere(); //
    while (nbp>=0) /*boucle infinie*/
    {
        printf("Nombre de places disponibles dans le parking : %d \n", (NBT-nbp)); // afficher le nb de places disponibles dans le parking
        ve = capteur("entree"); //verifie l'etat du capteur vehicule entree
        vs = capteur("sortie"); //verifie l'etat du capteur vehicule entree
        nbp = park(ve, vs, nbp); //appel à la fonction de gestion du parking - park
        printf("\n********************************************\n\n");

    }
    printf("Total de recette = %d\n", total);
    enregistre(); //
return 0;}
