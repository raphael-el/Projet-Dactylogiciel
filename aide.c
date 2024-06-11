#include <stdio.h>
#include <stdlib.h>
#include "aide.h"
#include "utils.h"

// Fonction pour afficher l'aide
void afficherAide() {
    effacerEcran();
    positionnerCurseur(50, 10); // Centrer horizontalement
    definirCouleur(11); // Cyan clair
    printf("=== Aide ===\n");
    positionnerCurseur(50, 12); // Ajuster la position
    printf("Description de l'application: UDBL - DACTYLOGICIEL\n");
    positionnerCurseur(50, 13); // Ajuster la position
    printf("Version: 1.0\n");
    positionnerCurseur(50, 14); // Ajuster la position
    printf("Concepteurs: Équipe Projet\n");
    positionnerCurseur(50, 15); // Ajuster la position
    printf("Date de conception: 2024\n");

    positionnerCurseur(50, 17); // Ajuster la position
    definirCouleur(15); // Blanc
    printf("Appuyez sur une touche pour revenir au menu principal...");
    getchar(); // Attendre que l'utilisateur appuie sur une touche
    getchar();
}

// Fonction pour afficher l'historique
void afficherHistorique() {
    int choix;
    do {
        effacerEcran();
        positionnerCurseur(50, 10); // Centrer horizontalement
        definirCouleur(11); // Cyan clair
        printf("=== Historique ===\n");

        FILE *fichier = fopen("database/history.txt", "r");
        if (fichier == NULL) {
            positionnerCurseur(50, 12); // Ajuster la position
            definirCouleur(12); // Rouge clair
            printf("Erreur d'ouverture du fichier d'historique.\n");
            Sleep(3000);
            return;
        }

        char ligne[256];
        int y = 12; // Position de départ pour l'affichage des lignes
        while (fgets(ligne, sizeof(ligne), fichier)) {
            positionnerCurseur(30, y++); // Ajuster la position pour chaque ligne
            printf("%s", ligne);
        }
        fclose(fichier);

        positionnerCurseur(50, y + 2); // Ajuster la position pour le message de retour
        definirCouleur(15); // Blanc
        printf("1. Vider l'historique\n");
        positionnerCurseur(50, y + 3); // Ajuster la position pour le message de retour
        printf("2. Retour au menu principal\n");
        positionnerCurseur(50, y + 4); // Ajuster la position pour le message de retour
        printf("Choisissez une option: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                viderHistorique();
                break;
            case 2:
                return;
            default:
                positionnerCurseur(50, y + 5); // Ajuster la position pour le message d'erreur
                definirCouleur(12); // Rouge clair
                printf("Choix invalide, veuillez réessayer.\n");
                Sleep(2000);
        }
    } while (choix != 2);
}

// Fonction pour vider l'historique
void viderHistorique() {
    FILE *fichier = fopen("database/history.txt", "w");
    if (fichier == NULL) {
        effacerEcran();
        positionnerCurseur(50, 10); // Centrer horizontalement
        definirCouleur(12); // Rouge clair
        printf("Erreur d'ouverture du fichier d'historique.\n");
        Sleep(3000);
        return;
    }
    fclose(fichier);

    effacerEcran();
    positionnerCurseur(50, 10); // Centrer horizontalement
    definirCouleur(10); // Vert clair
    printf("Historique vidé avec succès !\n");
    Sleep(2000);
}

