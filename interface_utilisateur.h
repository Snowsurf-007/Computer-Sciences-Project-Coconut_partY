#include "fonctions.h"
void afficher_carte(Case** carte, int taillecarte);
void placement_de_defenseur(Case** carte, int taillecarte, int* flocons, Defenseur* liste_defenseur, int* nb_defenseur);
void lancerpartie(Case*** carte, int* taillecarte, Defenseur** defenseurs, int* nbDefenseurs, EnnemiActif** ennemis, int* nbEnnemis, int* score, int* flocons, int* vague);
int menuDemarrage();
void defaite(int* score);
void victoire(int* score);
