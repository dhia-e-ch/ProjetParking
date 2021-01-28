#ifndef PARKING_H_INCLUDED
#define PARKING_H_INCLUDED

int recupere(); /* recupere la valeur de la recette enregistre dans le fichier parking.txt */
void enregistre(); /* enregistre la valeur de la recette totale dans le fichier parking.txt */
int capteur(char *cap); /* fonction qui verifine l'etat des capteurs */
void arrive (int ve); /* fonction qui gere l'arrive d'un vehicule */
void depart (int vs); /* fonction qui gere le depart d'un vehicule */
void ticket_depart(int tk); /* fonction qui gere le ticket de parking numero tk */
void barriere(char i , int* v); /* fonction qui ouvre la berriere i */
int park(int ve, int vs, int nbp); /* fonction de gestion du parking */

#endif // PARKING_H_INCLUDED
