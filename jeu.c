
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "jeu.h"
#include "utils.h"

// Déclaration des joueurs
Joueur joueurs[MAX_JOUEURS];

// Fonction pour démarrer le jeu
void demarrerJeu() {
    int nombreMots;
    int nombreJoueurs;
    char mots[MAX_MOTS][MAX_LONGUEUR_MOT];

    effacerEcran();
    positionnerCurseur(50, 10); // Centrer horizontalement
    definirCouleur(14); // Jaune clair
    printf("Entrez le nombre de joueurs: ");
    scanf("%d", &nombreJoueurs);

    for (int i = 0; i < nombreJoueurs; i++) {
        positionnerCurseur(50, 11 + i); // Ajuster la position
        printf("Entrez le pseudo du Joueur %d: ", i + 1);
        scanf("%s", joueurs[i].nom);
    }

    positionnerCurseur(50, 11 + nombreJoueurs); // Ajuster la position
    printf("Entrez le nombre de mots à saisir: ");
    scanf("%d", &nombreMots);

    // Charger les mots depuis la base de données
    chargerMots(mots, nombreMots);

    // Logique de saisie pour chaque joueur
    for (int i = 0; i < nombreJoueurs; i++) {
        joueurs[i].motsCorrects = jouerJeu(joueurs[i].nom, mots, nombreMots, &joueurs[i].tempsPris, &joueurs[i].tentativesErreurs);
    }

    // Afficher les résultats
    afficherResultats(nombreJoueurs);
}

// Fonction pour jouer le jeu
int jouerJeu(char* joueur, char mots[MAX_MOTS][MAX_LONGUEUR_MOT], int nombreMots, double *tempsPris, int *tentativesErreurs) {
    char saisie[MAX_LONGUEUR_MOT];
    int corrects = 0;
    *tentativesErreurs = 0;
    clock_t debut, fin;

    effacerEcran();
    positionnerCurseur(50, 10); // Centrer horizontalement
    definirCouleur(15); // Blanc
    printf("%s, preparez-vous a commencer dans 5 secondes...\n", joueur);
    Sleep(5000); // Pause de 5 secondes

    effacerEcran();
    positionnerCurseur(50, 10); // Centrer horizontalement
    definirCouleur(15); // Blanc
    printf("%s, a votre tour !\n", joueur);
    debut = clock();

    for (int i = 0; i < nombreMots; i++) {
        positionnerCurseur(50, 12 + i); // Ajuster la position pour chaque mot
        printf("Mot %d: %s\n", i + 1, mots[i]);
        positionnerCurseur(50, 13 + i); // Ajuster la position pour la saisie
        scanf("%s", saisie);
        while (strcmp(saisie, mots[i]) != 0) {
            positionnerCurseur(50, 14 + i); // Ajuster la position pour le message d'erreur
            printf("Incorrect, essayez a nouveau : %s\n", mots[i]);
            (*tentativesErreurs)++;
            positionnerCurseur(50, 15 + i); // Ajuster la position pour la saisie
            scanf("%s", saisie);
        }
        corrects++;
    }

    fin = clock();
    *tempsPris = ((double) (fin - debut)) / CLOCKS_PER_SEC;
    positionnerCurseur(50, 12 + nombreMots + 1); // Ajuster la position pour le résultat
    printf("%s a fini en %f secondes avec %d mots corrects.\n", joueur, *tempsPris, corrects);

    return corrects;
}

// Fonction pour charger les mots depuis la base de données
void chargerMots(char mots[MAX_MOTS][MAX_LONGUEUR_MOT], int nombreMots) {
    FILE *fichier = fopen("database/words.txt", "r");
    if (fichier == NULL) {
        effacerEcran();
        positionnerCurseur(50, 10); // Centrer horizontalement
        definirCouleur(12); // Rouge clair
        printf("Erreur d'ouverture du fichier de mots.\n");
        Sleep(3000);
        exit(1);
    }

    for (int i = 0; i < nombreMots && fgets(mots[i], MAX_LONGUEUR_MOT, fichier) != NULL; i++) {
        // Supprimer le saut de ligne à la fin du mot
        size_t len = strlen(mots[i]);
        if (len > 0 && mots[i][len - 1] == '\n') {
            mots[i][len - 1] = '\0';
        }
    }

    fclose(fichier);
}

// Fonction pour afficher les résultats du jeu
void afficherResultats(int nombreJoueurs) {
    effacerEcran();
    positionnerCurseur(50, 10); // Centrer horizontalement
    definirCouleur(13); // Magenta clair
    printf("=== Resultats du jeu ===\n");

    for (int i = 0; i < nombreJoueurs; i++) {
        double vitesseFrappe = joueurs[i].motsCorrects / joueurs[i].tempsPris;
        positionnerCurseur(50, 12 + i * 4); // Ajuster la position
        printf("%s a fini en %f secondes avec %d mots corrects.\n", joueurs[i].nom, joueurs[i].tempsPris, joueurs[i].motsCorrects);
        positionnerCurseur(50, 13 + i * 4); // Ajuster la position
        printf("Vitesse de frappe : %.2f mots/seconde\n", vitesseFrappe);
        positionnerCurseur(50, 14 + i * 4); // Ajuster la position
        printf("Tentatives d'erreurs : %d\n", joueurs[i].tentativesErreurs);
    }

    // Tri des joueurs par nombre de mots corrects, puis par temps si égalité
    for (int i = 0; i < nombreJoueurs - 1; i++) {
        for (int j = 0; j < nombreJoueurs - i - 1; j++) {
            if (joueurs[j].motsCorrects < joueurs[j + 1].motsCorrects ||
                (joueurs[j].motsCorrects == joueurs[j + 1].motsCorrects && joueurs[j].tempsPris > joueurs[j + 1].tempsPris)) {
                Joueur temp = joueurs[j];
                joueurs[j] = joueurs[j + 1];
                joueurs[j + 1] = temp;
            }
        }
    }

    positionnerCurseur(50, 12 + nombreJoueurs * 4); // Ajuster la position
    printf("=== Classement ===\n");
    for (int i = 0; i < nombreJoueurs; i++) {
        positionnerCurseur(50, 13 + nombreJoueurs * 4 + i); // Ajuster la position
        printf("%d. %s\n", i + 1, joueurs[i].nom);
    }

    sauvegarderResultats(joueurs, nombreJoueurs);

    positionnerCurseur(50, 14 + nombreJoueurs * 4 + nombreJoueurs); // Ajuster la position
    definirCouleur(15); // Blanc
    printf("Appuyez sur enter pour revenir au menu principal...");
    getchar(); // Attendre que l'utilisateur appuie sur une touche
    getchar();
}

// Fonction pour sauvegarder les résultats du jeu
void sauvegarderResultats(Joueur joueurs[], int nombreJoueurs) {
    FILE *fichier = fopen("database/history.txt", "a");
    if (fichier == NULL) {
        effacerEcran();
        positionnerCurseur(50, 10); // Centrer horizontalement
        definirCouleur(12); // Rouge clair
        printf("Erreur d'ouverture du fichier d'historique.\n");
        Sleep(3000);
        return;
    }

    time_t maintenant = time(NULL);
    struct tm *t = localtime(&maintenant);
    fprintf(fichier, "Date: %02d-%02d-%04d %02d:%02d:%02d\n", t->tm_mday, t->tm_mon + 1, t->tm_year + 1900, t->tm_hour, t->tm_min, t->tm_sec);

    for (int i = 0; i < nombreJoueurs; i++) {
        fprintf(fichier, "Joueur %d: %s, Mots corrects: %d, Temps: %f, Erreurs: %d, Vitesse: %.2f mots/seconde\n",
                i + 1, joueurs[i].nom, joueurs[i].motsCorrects, joueurs[i].tempsPris, joueurs[i].tentativesErreurs,
                joueurs[i].motsCorrects / joueurs[i].tempsPris);
    }

    fprintf(fichier, "--------------------------------------\n");

    fclose(fichier);
}
