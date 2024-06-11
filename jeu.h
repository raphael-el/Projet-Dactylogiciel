#ifndef JEU_H
#define JEU_H

#define MAX_JOUEURS 10
#define MAX_MOTS 100
#define MAX_LONGUEUR_MOT 100

typedef struct {
    char nom[50];
    int motsCorrects;
    double tempsPris;
    int tentativesErreurs;
} Joueur;

void demarrerJeu();
int jouerJeu(char* joueur, char mots[MAX_MOTS][MAX_LONGUEUR_MOT], int nombreMots, double *tempsPris, int *tentativesErreurs);
void chargerMots(char mots[MAX_MOTS][MAX_LONGUEUR_MOT], int nombreMots);
void afficherResultats(int nombreJoueurs);
void sauvegarderResultats(Joueur joueurs[], int nombreJoueurs);

#endif // JEU_H

