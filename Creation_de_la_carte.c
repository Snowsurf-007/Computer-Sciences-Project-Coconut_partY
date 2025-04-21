//inclusion des bibliothèques nécessaires
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// On définit les emojis utilisés pour la carte
#define EMOJI_NEIGE "\xE2\x97\xBB"
#define EMOJI_PIERRE "\xE2\x96\xA0"
#define EMOJI_DRAPEAU "\xF0\x9F\x9A\xA9"
#define EMOJI_SAPIN "\xF0\x9F\x8C\xB8"

int main (){
    srand(time(NULL));
    int taillecarte; // Variable pour la taille de la carte

    // On génère une taille de carte aléatoire entre 15 et 25
    taillecarte=rand()%11+15;

    int **carte; //Déclaration de la carte

    // Allocation dynamique de la mémoire pour la carte
    carte=malloc(taillecarte*sizeof(int*));
    for (int i=0; i<taillecarte; i++){
        carte[i]=malloc(taillecarte*sizeof(int));
        for (int j=0; j<taillecarte; j++){
            carte[i][j]=rand()%11; // Remplir la carte avec des valeurs aléatoires
        }
    }

    printf("Pour cette partie, la carte est de taille %d x %d\n", taillecarte, taillecarte); // On affiche la taille de la carte
    sleep(3); // On fait une pause de trois secondes pour laisser le temps de lire
    printf("La carte est en cours de création...\n");
    sleep(2); // On fait une pause de deux secondes pour laisser le temps de lire
    printf("Voici la carte :\n\n");
    sleep(1); // On fait une pause d'une seconde pour laisser le temps de lire
    
    // On affiche la carte
    for (int i=0; i<taillecarte; i++){
        for (int j=0; j<taillecarte; j++){
            if(carte[i][j]==0 || carte[i][j]==1 || carte[i][j]==2 || carte[i][j]==3 || carte[i][j]==4 || carte[i][j]==5 || carte[i][j]==6){
                printf("%s", EMOJI_NEIGE);
            }
            else if(carte[i][j]==7 || carte[i][j]==8){
                printf("%s", EMOJI_PIERRE);
            }
            else if(carte[i][j]==9 || carte[i][j]==10){
                printf("%s", EMOJI_SAPIN);
            }
            else if(carte[i][j]==11){
                printf("%s", EMOJI_DRAPEAU);
            }
        }
        printf("\n"); // On passe à la ligne suivante
    }
    printf("\n");

    // On libère la mémoire allouée pour la carte
    for (int i=0; i<taillecarte; i++) {
    free(carte[i]);
    }
    free(carte);
    return 0;
}
