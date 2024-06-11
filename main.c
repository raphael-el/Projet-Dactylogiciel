#include <stdio.h>
#include <stdlib.h>
#include "jeu.h"
#include "config.h"
#include "aide.h"
#include "utils.h"

// Fonction principale
int main() {
    // Afficher l'équipe au lancement
    effacerEcran();
    positionnerCurseur(50, 10); // Centrer verticalement à 10 lignes du haut
    //definirCouleur(10); // Vert clair
    printf("============ UDBL - DACTYLOGICIEL ============\n");
    positionnerCurseur(47, 12);
    printf("Presente par : \n");
    positionnerCurseur(60, 13);
    printf("MULAJA ILUNGA Berlice \n");
    positionnerCurseur(60, 14);
    printf("MUKENDI CIBALA Samy \n");
    positionnerCurseur(60, 15);
    printf("MUKENDI KALOMBO Joel\n");
    positionnerCurseur(60, 16);
    printf("MUKWEKWA KABAMBA Eliel\n");
    Sleep(10000); // Pause de 10 secondes

    // Afficher le menu principal
    afficherMenu();

    return 0;
}

// Afficher le menu principal
void afficherMenu() {
    int choix;
    do {
        effacerEcran();
        positionnerCurseur(50, 10); // Centrer horizontalement
        definirCouleur(11); // Cyan clair
        printf("=== Menu Principal ===\n");
        positionnerCurseur(50, 12); // Ajuster la position
        printf("1. Demarrer\n");
        positionnerCurseur(50, 13); // Ajuster la position
        printf("2. Configurer\n");
        positionnerCurseur(50, 14); // Ajuster la position
        printf("3. Historique\n");
        positionnerCurseur(50, 15); // Ajuster la position
        printf("4. Aide\n");
        positionnerCurseur(50, 16); // Ajuster la position
        printf("5. Quitter\n");
        positionnerCurseur(50, 18); // Ajuster la position
        printf("Choisissez une option: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                demarrerJeu();
                break;
            case 2:
                configurerJeu();
                break;
            case 3:
                afficherHistorique();
                break;
            case 4:
                afficherAide();
                break;
            case 5:
                effacerEcran();
                positionnerCurseur(50, 10); // Centrer horizontalement
                definirCouleur(12); // Rouge clair
                printf("Au revoir!\n");
                Sleep(2000);
                exit(0);
                break;
            default:
                effacerEcran();
                positionnerCurseur(50, 10); // Centrer horizontalement
                definirCouleur(12); // Rouge clair
                printf("Choix invalide, veuillez reessayer.\n");
                Sleep(2000);
        }
    } while (choix != 5);
}
