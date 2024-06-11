#include <windows.h>
#include "utils.h"

// Fonction pour effacer l'écran
void effacerEcran() {
    system("cls");
}

// Fonction pour positionner le curseur
void positionnerCurseur(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Fonction pour définir la couleur du texte
void definirCouleur(int couleur) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), couleur);
}

