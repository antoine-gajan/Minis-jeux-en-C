void menu(int *nb_erreurs_restant);
char *LireUnMot();
char LireUneLettre();
void InitialiserTableau(int tableau[], int taille);
int LettreCorrecte(char lettre, char mot[], int tableau[], int *nb_erreurs_restant);
void viderBuffer();
void AfficheRestant(char motSecret[], int tableau[]);
void AGagner(int tableau[], int taille_mot_secret, int *gagne);

