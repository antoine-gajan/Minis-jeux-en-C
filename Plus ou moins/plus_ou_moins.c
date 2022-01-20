#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "plus_ou_moins.h"

int main(int argc, char *argv[])
{
    //Affichage du titre du jeu
    printf("JEU DU PLUS OU MOINS\n\n");

    //initialisation des variables
    int gagne = 0, nb_coups = 0, max = 10, proposition = 0;

    //Affichage du menu
    menu(&max);

    //Génération du nombre aléatoire
    srand(time(NULL));
    int nombreMystere = (rand() % (max + 1));
    //Boucle principale
    do{
        //Demande du nombre
        printf("Nombre : ");
        //Vider le buffer par sécurité
        scanf("%d", &proposition);
        viderBuffer();
        //Incrémentation du nombre de coups
        nb_coups ++;

        //Disjonction de cas en fonction de ce que l'utilisateur a rentré (on supposera un utilisateur qui rentre des valeurs correctes)
        if (proposition > nombreMystere){
            printf("C'est moins ! \n\n");
        }
        //Si le joueur a gagné
        else if (proposition == nombreMystere)
        {
            printf("Bien joué ! Vous avez trouvé le nombre mystère %d en %d coups !", nombreMystere, nb_coups);
            gagne = 1;
        }
        else{
            printf("C'est plus ! \n\n");
        }
    }while (!(gagne));
    return 0;
}

void menu(int *max){
    //Demande du choix de la difficulté
    int reponse = 0;
    do{
        printf("Choisir un niveau de difficulté :\n1. Facile (nombre entre 0 et 10)\n2. Moyen (nombre entre 0 et 100)\n3. Difficile (nombre entre 0 et 1 000)\n\nVotre choix :");
        scanf("%d", &reponse);
        viderBuffer();
    }while(reponse != 1 && reponse != 2 && reponse !=3);

    //Changement du nombre maximum aléatoire généré par le jeu
    switch(reponse){
    case 1:
        *max = 10;
        break;
    case 2:
        *max = 100;
        break;
    case 3:
        *max = 1000;
    }
}

//Fonction pour vider le buffer
void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}
