#include <stdio.h> /* bibliotheque d'affichage a l'ecran et ecriture clavier */
#include <time.h> /* bibliotheque pour utiliser un timer */
#include <stdlib.h> /* bibliotheque d'utilisation des fonctions generales */
#include "parking.h" /* inclure le header de parking.h*/
#include <windows.h> /* pour arreter le temps */

#define NBT 10// pour un nombre de places fixe


extern time_t zero;
extern const int unit ;
extern int mtb0, mtb1, total; /* Le nombre de places de parking, variable globale moteur de la berrieres entree et sortie*/
extern time_t Tp[NBT];

int recupere(){ // recupere la valeur de la recette enregistré dans le fichier parking.txt
    int v; // variable pour stocker la valeur recuepre de la recette
    FILE * fp;
    fp = fopen ("parking.txt", "r+");
    fscanf(fp,"%d",&v);
    fclose(fp);
    return v;
}
int capteur(char *cap){
    int c;
    do{
            printf("Introduire la valeur du capteur %s vehicule [1/0] : ", cap); //on entre manuellement l'etat des capteur pour la simulation
            scanf("%d",&c); // lis les valeurs des capteur d'entree et de sortie
            if (c>1 || c<-1)
            {
                printf("Erreur capteur ...\n"); // si la valeur reçu pour le capteur est differente de 0 et 1 un message d'erreur est affiché
            }
        } while (c>1 || c<-1); //verifier que la valeur de ve est entre 0 et 1
    return c;
}

void barriere(char bar, int *v) /* fonction pour ouvrir la barriere */
{
    int e = *v;
    switch(bar) // selon la valeur du caractere bar
            {
                case 'e': // si bar == 'e'
                    mtb0 = 1; /* si c'est la barriere d'entree qui doit s'ouvrir avec le moteur 0*/
                    printf("la barriere d'entree se leve\n");
                    break;

                case 's': // si bar == 's'
                    mtb1 = 1; /* si c'est la barriere de sortie qui doit s'ouvrir avec le moteur 1*/
                    printf("la barriere de sortie se leve\n");
                break;
            }
    while (e) /* tant que le vehicule n'est pas passe¦ la barriere reste ouverte */
        {
            printf("Indiquer l'etat du capteur vehicule [1/0] : ");
            scanf("%d", &e); /* detecte si le vehicule est passe */
            if (e==0){
                Sleep(2); //le programme s'arrete deux secondes pour que le vehicule passe
                printf("Le vehicule est passee.\n");
                switch(bar)
                    {
                        case 'e': mtb0 = 0; /* si c'est la barriere d'entree qui doit se fermer le moteur 0*/
                        printf("La barriere d'entree se referme\n");
                        break;
                        case 's': mtb1 = 0; /* si c'est la barriere de sortie qui doit se fermer le moteur 1*/
                        printf("La barriere de sortie se referme\n");
                        break;
                    }
                *v = e;
                break ; /* une fois la barriere abaissé la fonction barriere acheve son execution */
            }
        }
}
void depart (int vs) // la fonction depart recoit la valeur du capteur de sortie vehicule
{
    int tk;
    printf("Introduire le numero du ticket : ");
    scanf("%d", &tk); // lis le numero du ticket
    ticket_depart(tk-1); //
    barriere('s', &vs); /* ouverture barriere  sortie*/
}
void ticket_depart(int tk) /* prends en entree le temps d'arrivee et de depart et calcule le prix a payer en sortie */
{
    int e, montant, paye =0,prix=0; //temps total initialise a zero
    time_t now;
    double ecart;
    // recuperer le ticket cad le temps d'entree
    // prendre le temps de sortie = temps actuel
    time(&now);
    ecart = difftime(now, Tp[tk]); // on va obtenir un ecart en secondes
    e=(int)ecart/(60*30)+1; // nombre de demi-heures passees
    prix = e * unit; // le prix a payer est egale au nombre des demi heures passees * le prix unitaire de la demi heure
    do {
        printf("Lecture du ticket N : %d\n",tk+1);
        printf("Le motant a payer est de : %d millimes \nMontant introduit = ", prix);
        scanf("%d",&montant); // lire le montant paye par le chauffeur du vehicule
        total = total+montant; // on rajoute le montant paye a la recette du parking
        if ( montant>= prix)
        {
            printf("Payement valide. Merci de votre visite !\n");
            Tp[tk] = zero;
            paye = 1;
        }
        else
        {
            prix = prix - montant;
            printf("Reste a payer : %d\n",prix);
        }
    } while (!paye);
}

void ticket_arrive() /* enregistre un nouveau ticket de parking : le temps d'arrivé du vehicule */
{
    time_t now;
    int i = 0;

    //parcourir le tableau pour trouver une case vide
    while ((Tp[i]!=zero )&& i < NBT)
        {
            i++;//parcours du tableau
        }
    time(&now); // Renvoie l'heure actuelle
    Tp[i] = now; //affecter le temps dans une case
    printf("Votre ticket est le Numero \"%d\".\nDate et heure d'entree : %s", i+1, ctime(&now)); //renvoyer le numero de case

}

void arrive(int ve)
{
    ticket_arrive(); // doit retourner un numero de ticket
    barriere('e', &ve); /* ouverture barriere entree */
}
int park(int ve, int vs, int nb) // declaration de la fonction patk
{
    if (ve==1 && nb<NBT && !vs) /* si voiture ¨a l'entree et pas de voiture ¨a la sortie et parking pas complet */
        {
            printf("Un vehicule entree dans le parking \n");
            arrive(ve); // normalement on aura un return le numero de ticket a conserver
            nb++; // incrementer le nb de vehicules dans le parking
        }
    if (vs==1 && !ve && nb>0) /* vehicule qui sort du parking */
        {
            printf("Un vehicule sort du parking \n");
            depart (vs);
            nb--;
        }
    if (ve==1 && vs==1 && nb>0)
        {
            depart (vs); // un vehicule sort du parking
            arrive(ve); // un vehicule rentre dans le parking
            printf("Un vehicule est sorti et un vehicule est entree dans le parking\n");
        }
    if (nb==NBT) /* si le parking est complet on affiche un message disant que le parking est complet */
        {
            printf("Le parking est complet !\n");
        }
    if (vs==1 && !nb)
        {
            printf("Erreur sortie !\n");
        }
    if (vs==-1 || ve==-1)
        {
            nb = -1;
        }
    return nb;
}
void enregistre(){
    FILE * fp;
    fp = fopen ("parking.txt", "w+");
    fprintf(fp,"%d",total);
    fclose(fp);
}
