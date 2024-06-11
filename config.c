#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "utils.h"

#define MAX_PLAYERS 10
#define MAX_MOTS 100
#define MAX_LONGUEUR_MOT 100

// Fonction pour configurer le jeu
void configurerJeu() {
    int choix;
    do {
        effacerEcran();
        positionnerCurseur(50, 10); // Centrer horizontalement
        definirCouleur(11); // Cyan clair
        printf("=== Configuration ===\n");
        positionnerCurseur(50, 12); // Ajuster la position
        printf("1. Ajouter un mot\n");
        positionnerCurseur(50, 13); // Ajuster la position
        printf("2. Voir les mots\n");
        positionnerCurseur(50, 14); // Ajuster la position
        printf("3. Effacer un mot\n");
        positionnerCurseur(50, 15); // Ajuster la position
        printf("4. Retour au menu principal\n");
        positionnerCurseur(50, 17); // Ajuster la position
        printf("Choisissez une option: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                ajouterMot();
                break;
            case 2:
                voirMots();
                break;
            case 3:
                effacerMot();
                break;
            case 4:
                return; // Retour au menu principal
            default:
                effacerEcran();
                positionnerCurseur(50, 10); // Centrer horizontalement
                definirCouleur(12); // Rouge clair
                printf("Choix invalide, veuillez reessayer.\n");
                Sleep(2000);
        }
    } while (choix != 4);
}

// Fonction pour ajouter un mot
void ajouterMot() {
    char mot[MAX_LONGUEUR_MOT];
    FILE *fichier = fopen("database/words.txt", "a"); // Ajouter des mots à la fin du fichier

    if (fichier == NULL) {
        effacerEcran();
        positionnerCurseur(50, 10); // Centrer horizontalement
        definirCouleur(12); // Rouge clair
        printf("Erreur d'ouverture du fichier de mots.\n");
        Sleep(3000);
        return;
    }

    effacerEcran();
    positionnerCurseur(50, 10); // Centrer horizontalement
    definirCouleur(14); // Jaune clair
    printf("Entrez les mots a ajouter (entrez 'exit' pour terminer) :\n");

    while (1) {
        positionnerCurseur(50, 12); // Ajuster la position pour la saisie
        printf("Mot : ");
        scanf("%s", mot);

        if (strcmp(mot, "exit") == 0) {
            break;
        }

        fprintf(fichier, "%s\n", mot);

        effacerEcran();
        positionnerCurseur(50, 10); // Centrer horizontalement
        definirCouleur(10); // Vert clair
        printf("Mot '%s' ajoute avec succes !\n", mot);
        positionnerCurseur(50, 12); // Ajuster la position pour le message de retour
        definirCouleur(15); // Blanc
        printf("Appuyez sur la touche enter pour continuer...");
        getchar(); // Attendre que l'utilisateur appuie sur une touche
        getchar();
        effacerEcran();
        positionnerCurseur(50, 10); // Centrer horizontalement
        definirCouleur(14); // Jaune clair
        printf("Entrez les mots a ajouter (entrez 'exit' pour terminer) :\n");
    }

    fclose(fichier);
    effacerEcran();
    positionnerCurseur(50, 10); // Centrer horizontalement
    definirCouleur(10); // Vert clair
    printf("Tous les mots ont ete ajoutes avec succes !\n");
    positionnerCurseur(50, 12); // Ajuster la position pour le message de retour
    definirCouleur(15); // Blanc
    printf("Appuyez sur une touche pour revenir au menu precedent...");
    getchar(); // Attendre que l'utilisateur appuie sur une touche
    getchar();
}

// Fonction pour voir les mots
void voirMots() {
    effacerEcran();
    positionnerCurseur(50, 10); // Centrer horizontalement
    definirCouleur(11); // Cyan clair
    printf("=== Liste des mots ===\n");

    FILE *fichier = fopen("database/words.txt", "r");
    if (fichier == NULL) {
        positionnerCurseur(50, 12); // Ajuster la position
        definirCouleur(12); // Rouge clair
        printf("Erreur d'ouverture du fichier de mots.\n");
        Sleep(3000);
        return;
    }

    char mot[MAX_LONGUEUR_MOT];
    int y = 12; // Position de départ pour l'affichage des mots
    while (fgets(mot, sizeof(mot), fichier)) {
        size_t len = strlen(mot);
        if (len > 0 && mot[len - 1] == '\n') {
            mot[len - 1] = '\0'; // Enlever le saut de ligne
        }
        positionnerCurseur(30, y++); // Ajuster la position pour chaque mot
        printf("%s\n", mot);
    }
    fclose(fichier);

    positionnerCurseur(50, y + 2); // Ajuster la position pour le message de retour
    definirCouleur(15); // Blanc
    printf("Appuyez sur  enter pour revenir au menu precedent...");
    getchar(); // Attendre que l'utilisateur appuie sur une touche
    getchar();
}

// Fonction pour effacer un mot
void effacerMot() {
    effacerEcran();
    positionnerCurseur(50, 10); // Centrer horizontalement
    definirCouleur(11); // Cyan clair
    printf("=== Supprimer un mot ===\n");

    FILE *fichier = fopen("database/words.txt", "r");
    if (fichier == NULL) {
        positionnerCurseur(50, 12); // Ajuster la position
        definirCouleur(12); // Rouge clair
        printf("Erreur d'ouverture du fichier de mots.\n");
        Sleep(3000);
        return;
    }

    char mots[MAX_MOTS][MAX_LONGUEUR_MOT];
    int nombreMots = 0;
    while (fgets(mots[nombreMots], sizeof(mots[nombreMots]), fichier) && nombreMots < MAX_MOTS) {
        size_t len = strlen(mots[nombreMots]);
        if (len > 0 && mots[nombreMots][len - 1] == '\n') {
            mots[nombreMots][len - 1] = '\0'; // Enlever le saut de ligne
        }
        nombreMots++;
    }
    fclose(fichier);

    for (int i = 0; i < nombreMots; i++) {
        positionnerCurseur(30, 12 + i); // Ajuster la position pour chaque mot
        printf("%d. %s\n", i + 1, mots[i]);
    }

    int choix;
    positionnerCurseur(50, 12 + nombreMots + 1); // Ajuster la position pour le message de saisie
    definirCouleur(14); // Jaune clair
    printf("Entrez le numero du mot a supprimer (0 pour annuler) : ");
    scanf("%d", &choix);

    if (choix > 0 && choix <= nombreMots) {
        fichier = fopen("database/words.txt", "w");
        if (fichier == NULL) {
            effacerEcran();
            positionnerCurseur(50, 12); // Ajuster la position
            definirCouleur(12); // Rouge clair
            printf("Erreur d'ouverture du fichier de mots.\n");
            Sleep(3000);
            return;
        }

        for (int i = 0; i < nombreMots; i++) {
            if (i != choix - 1) {
                fprintf(fichier, "%s\n", mots[i]);
            }
        }
        fclose(fichier);

        effacerEcran();
        positionnerCurseur(50, 10); // Centrer horizontalement
        definirCouleur(10); // Vert clair
        printf("Mot supprime avec succes !\n");
    } else {
        effacerEcran();
        positionnerCurseur(50, 10); // Centrer horizontalement
        definirCouleur(12); // Rouge clair
        printf("Annulation de la suppression.\n");
    }
    Sleep(3000);
}

