#include "Biblio.h"

int main (){
    MenuDemarrage();
    srand(time(NULL));
    int taillecarte; //Variable pour la taille de la carte

    // On génère une taille de carte aléatoire entre 15 et 25
    taillecarte=rand()%11+15;

    int **carte=(int**)malloc(taillecarte*sizeof(int*)); //Allocation dynamique de la mémoire pour la carte
    creer_carte(carte, taillecarte);
    creer_chemin(carte, taillecarte);
    afficher_carte(carte, taillecarte);

    while(){
        
    }

    //On libère la mémoire allouée pour la carte
    for (int i=0; i<taillecarte; i++) {
    free(carte[i]);
    }
    free(carte);
    return 0;
}
