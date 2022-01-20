#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "pendu.h"


int main(int argc, char *argv[])
{
    //Affichage du titre du jeu
    printf("JEU DU PENDU\n\n");
    //initialisation des variables
    int gagne = 0;
    int nb_erreurs_restant = 10;
    //Affichage du menu
    menu(&nb_erreurs_restant);
    //Demande du mot secret de moins de 30 lettres
    printf("=== JOUEUR 1 ===\n\nMot secret (�crit en majuscules) de moins de 30 mots � faire deviner � votre partenaire : ");
    char motSecret[30] = "";
    scanf("%s", motSecret);
    //On vide le buffer par s�curit�
    viderBuffer();

    //Tableau de bool�en avec allocation de m�moire dynamique
    int *tableau_booleen = malloc(taille_mot(motSecret) * sizeof(int));
    InitialiserTableau(tableau_booleen, taille_mot(motSecret));

    printf("\n\n=== JOUEUR 2 ===\n\nVous devez d�couvrir un mot de %d lettres.\n\nVous avez le droit � %d erreurs maximum.\n", taille_mot(motSecret), nb_erreurs_restant);
    //boucle principale
    while (!gagne && nb_erreurs_restant > 0)
    {
        char lettre = 0;
        lettre = LireUneLettre();
        LettreCorrecte(lettre, motSecret, tableau_booleen, &nb_erreurs_restant);
        AfficheRestant(motSecret, tableau_booleen);
        AGagner(tableau_booleen, taille_mot(motSecret), &gagne);
    }
    if (gagne)
    {
        printf("\nBravo ! Vous avez gagn� ! Vous avez d�couvert le mot : %s", motSecret);
    }
    else
    {
        printf("\nDommage ! Le mot � d�couvrir �tait : %s", motSecret);
    }
    return 0;
}


void menu(int *nb_erreurs_restant){
    //Demande du choix de la difficult�
    int reponse = 0;
    do{
        printf("Choisir un niveau de difficult� :\n1. Facile (10 erreurs autoris�es)\n2. Moyen (8 erreurs autoris�es)\n3. Difficile (5 erreurs autoris�es)\n\nVotre choix :");
        scanf("%d", &reponse);
        viderBuffer();
    }while(reponse != 1 && reponse != 2 && reponse !=3);

    //Changement de la difficult� du jeu
    switch(reponse){
    case 1:
        *nb_erreurs_restant = 10;
        break;
    case 2:
        *nb_erreurs_restant = 8;
        break;
    case 3:
        *nb_erreurs_restant = 5;
    }
}

//Fonction pour trouver la taille d'un mot
int taille_mot(char mot[])
{
    int taille = 0, i = 0;
    //tant qu'on n'est pas � la fin du mot, on incr�mente la longueur du mot
    for (i = 0; mot[i] != '\0'; i++)
    {
        taille++;
    }
    return taille;
}

//Fonction qui lit une lettre de l'utilisateur
char LireUneLettre()
{
    //Initialisation des variables
    char caractere = 0;
    char chaine_rentree_utilisateur = 0;
    //Saisie d'un caract�re par l'utilisateur
    printf("Entrez une lettre : ");
    caractere = fgetc(stdin);
    //On le met en majuscule
    caractere = toupper(caractere);
    //On vide le buffer
    viderBuffer();
    //On retourne le caract�re
    return caractere;
}

void InitialiserTableau(int tableau[], int taille)
{
    int i = 0;
    //Toutes les valeurs mises � 0
    for (i = 0; i < taille; i++)
    {
        tableau[i] = 0;
    }
}

//Fonction pour mettre � jour le mot � trouver si la lettre donn�e est dans le mot
int LettreCorrecte(char lettre, char mot[], int tableau[], int *nb_erreurs_restant)
{
    //Si la lettre est bien dans le mot
    if (strchr(mot, lettre) != NULL)
    {
        //On modifie le tableau de bool�en
        int i = 0;
        for (i = 0; i < taille_mot(mot); i++)
        {
            if (mot[i] == lettre)
            {
                tableau[i] = 1;
            }
        }
        printf("La lettre %c est dans le mot secret ! \n", lettre);
        return 1;
    }
    //Si une erreur a �t� rencontr�e, on enl�ve une erreur possible et on renvoie 0
    else
    {
        printf("Dommage ! La lettre %c n'est pas dans le mot secret... \n", lettre);
        *nb_erreurs_restant = *nb_erreurs_restant - 1;
        printf("Nombre d'erreurs restant autoris� : %d\n", *nb_erreurs_restant);
        return 0;
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

//Fonction pour afficher le mot avec des �toiles
void AfficheRestant(char motSecret[], int tableau[])
{
    //Taille du mot secret
    int taille = taille_mot(motSecret);
    int i = 0;
    printf("Mot � d�couvrir : ");
    for (i = 0; i < taille_mot(motSecret); i++)
    {
        if (tableau[i] == 1)
        {
            printf("%c", motSecret[i]);
        }
        else
        {
            printf("*");
        }
    }
    printf("\n\n");
}

//Fonction qui met � jour le bool�en gagner
void AGagner(int tableau[], int taille_mot_secret, int *gagne)
{
    int i = 0;
    *gagne = 1;
    for (i = 0; i < taille_mot_secret; i++)
    {
        if (tableau[i] == 0)
        {
            *gagne = 0;
        }
    }
}

