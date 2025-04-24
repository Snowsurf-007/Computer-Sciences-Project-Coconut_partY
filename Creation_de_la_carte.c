//inclusion des bibliothèques nécessaires
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
// On définit les emojis utilisés pour la carte
#define EMOJI_NEIGE    " "
#define EMOJI_PIERRE   "O"
#define EMOJI_DRAPEAU  "F"
#define EMOJI_SAPIN    "A"

//""\xE2\x97\xBB"
//"\xF0\x9F\xAA\xA8"
//"\xF0\x9F\x9A\xA9"
//"\xF0\x9F\x8C\xB8"

void afficher_carte(int **carte, int taillecarte) {
    printf("\n Pour cette partie, la carte est de taille %d x %d\n", taillecarte, taillecarte); // On affiche la taille de la carte
    sleep(2); // On fait une pause de deux secondes pour laisser le temps de lire
    printf("La carte est en cours de création...\n");
    sleep(2); // On fait une pause de deux secondes pour laisser le temps de lire
    printf("Voici la carte :\n\n");
    sleep(1); // On fait une pause d'une seconde pour laisser le temps de lire
    
    // On affiche la carte
    int car='A';
    printf("    ");
    for (int i=0; i<taillecarte; i++){
        printf("%c  ", car+i);
    }
    printf("\n");
    printf("    ");
    for (int i=0; i<taillecarte; i++){
        printf("_  ");
    }
    printf("\n");
    
    for (int i=0; i<taillecarte; i++){
        printf("%02d |", i+1);
        for (int j=0; j<taillecarte; j++){
            if(carte[i][j]==0 || carte[i][j]==1 || carte[i][j]==2 || carte[i][j]==3 || carte[i][j]==4 || carte[i][j]==5 || carte[i][j]==6){
                printf("%s  ", EMOJI_NEIGE);
            }
            else if(carte[i][j]==7 || carte[i][j]==8){
                printf("%s  ", EMOJI_PIERRE);
            }
            else if(carte[i][j]==9 || carte[i][j]==10){
                printf("%s  ", EMOJI_SAPIN);
            }
            else if(carte[i][j]==11){
                printf("%s  ", EMOJI_DRAPEAU);
            }
        }
        printf("|\n");
    }
    printf("    ");
    for (int i=0; i<taillecarte; i++){
        printf("‾  ");
    }
}

void creer_carte(int **carte, int taillecarte) {
    for (int i=0; i<taillecarte; i++){
        carte[i]=malloc(taillecarte*sizeof(int));
        if (carte[i]==NULL) {
            printf("Erreur d'allocation mémoire\n");
            exit(1); //Terminer le programme si l'allocation échoue
        }
        for (int j=0; j<taillecarte; j++){
            carte[i][j]=rand()%11; //Remplir la carte avec des valeurs aléatoires
        }
    }
}

void creer_chemin(int **carte, int taillecarte){
    int j=rand()%(taillecarte-6)+3; //Colonne de départ
    int direction;

    for (int i=0; i<taillecarte; i++) {
        //Déplacement latéral aléatoire : -1 (gauche), 0 (tout droit), 1 (droite)
        direction=rand()%3-1;

        //Calcul de la nouvelle position (temporaire pour vérification)
        int nouvelle_colonne=j+direction;

        //Vérification des bornes
        if (nouvelle_colonne<0){
            nouvelle_colonne=0;
        }
        if (nouvelle_colonne>=taillecarte){
            nouvelle_colonne=taillecarte-1;
        }

        //Si on change de colonne, on met un drapeau au-dessus de la nouvelle case
        if (direction!=0 && i>0) {
            carte[i-1][nouvelle_colonne]=11;
        }

        //Mise à jour de la position j
        j=nouvelle_colonne;

        //On place le drapeau sur la case actuelle
        carte[i][j]=11;
    }
}

int main (){
    srand(time(NULL));
    int taillecarte; //Variable pour la taille de la carte

    // On génère une taille de carte aléatoire entre 15 et 25
    taillecarte=rand()%11+15;

    int **carte; //Déclaration de la carte
    carte=malloc(taillecarte*sizeof(int*)); //Allocation dynamique de la mémoire pour la carte
    
    creer_carte(carte, taillecarte);
    creer_chemin(carte, taillecarte);
    afficher_carte(carte, taillecarte);

    //On libère la mémoire allouée pour la carte
    for (int i=0; i<taillecarte; i++) {
    free(carte[i]);
    }
    free(carte);
    return 0;
}
