//inclusion des bibliothèques nécessaires
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// On définit les emojis utilisés pour la carte
#define EMOJI_NEIGE "\xE2\x97\xBB"
#define EMOJI_PIERRE "\xE2\x96\xA0"

int main (){
    srand(time(NULL));
    int taillecarte; // Variable pour la taille de la carte

    // On génère une taille de carte aléatoire entre 15 et 30
    taillecarte=rand()%16+15;

    // On crée la carte (sous forme de tableau 2D)
    char map[taillecarte][taillecarte];

    // On initialise la carte avec de la "neige"
    for (int i=0; i<taillecarte; i++){
        for (int j=0; j<taillecarte; j++){
            map[i][j]=EMOJI_NEIGE;
        }
    }

    // On affiche la carte
    for (int i=0; i<taillecarte; i++){
        for (int j=0; j<taillecarte; j++){
            printf("%s", map[i][j]=EMOJI_NEIGE);
        }
        printf("\n"); // On passe à la ligne suivante
    }

    free(map); // On libère la mémoire allouée pour la carte
    return 0;
}
