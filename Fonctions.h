//inclusion des bibliothèques nécessaires
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// On définit les emojis
#define EMOJI_NEIGE           "\xE2\x97\xBB\xEF\xB8\x8F"
#define EMOJI_PIERRE          "\xF0\x9F\xAA\xA8"
#define EMOJI_DRAPEAU         "\xF0\x9F\x9A\xA9"
#define EMOJI_SAPIN           "\xF0\x9F\x8C\xB2"
#define EMOJI_PINGOUIN        "\xF0\x9F\x90\xA7"
#define EMOJI_BONHOMMENEIGE   "\xE2\x9B\x84"
#define EMOJI_OURS            "\xF0\x9F\x90\xBB"
#define EMOJI_SKIEUR          "\xE2\x9B\xB7\xEF\xB8\x8F"
#define EMOJI_SNOWBOARDER     "\xF0\x9F\x8F\x82"
#define EMOJI_LUGISTE         "\xF0\x9F\x9B\xB7"
#define EMOJI_COURONNE        "\xF0\x9F\x91\x91"

// On définit les constantes
#define TAILLECHAINE 16

// On définit les structures
typedef struct{
        char emoji[TAILLECHAINE]; //code UTF8 emoji du defenseur
        int portee;
        int degats;
        float vitessetir;
        int prix;
        int coordx;
        int coordy;
}Defenseur;

typedef struct{
        char emoji[TAILLECHAINE]; //code UTF8 emoji de l'attaquant
        int vie;
        float esquive;
        int gain;
}Attaquant;

Defenseur constructeur_PinguPatrouilleur(Defenseur a){
        strcpy(a.emoji, EMOJI_PINGOUIN);
        a.portee=5;
        a.degats=30;
        a.vitessetir=0.5;
        a.prix=100;
        return a;
}

Defenseur constructeur_FloconPerceCiel(Defenseur a){
        strcpy(a.emoji, EMOJI_BONHOMMENEIGE);
        a.portee=10;
        a.degats=300;
        a.vitessetir=2;
        a.prix=200;
        return a;
}

Defenseur constructeur_GardePolaire(Defenseur a){
        strcpy(a.emoji, EMOJI_OURS);
        a.portee=2;
        a.degats=70;
        a.vitessetir=1;
        a.prix=150;
        return a;
}

Attaquant constructeur_SkieurFrenetique(Attaquant a){ //attaquant rapide et faible, petit taux d'esquive 
        strcpy(a.emoji, EMOJI_SKIEUR);
        a.vie=250;
        a.esquive=0.15;
        a.gain=20;
        return a;
}

Attaquant constructeur_SnowboarderAcrobate(Attaquant a){ //attaquant vitesse moyenne, vie moyenne mais bonne esquive
        strcpy(a.emoji, EMOJI_SNOWBOARDER);
        a.vie=500;
        a.esquive=0.30;
        a.gain=30;
        return a;
}

Attaquant constructeur_LugisteBarjo(Attaquant a){ //attaquant lent et resistant
        strcpy(a.emoji, EMOJI_LUGISTE);
        a.vie=2000;
        a.esquive=0;
        a.gain=50;
        return a;
}

// On définit les fonctions
int** chargement(const char* nom_fichier, int* ligne, int* colonne);
void amelioration(Case carte[]);
void afficher_carte(int **carte, int taillecarte);
void creer_carte(int **carte, int taillecarte);
void creer_chemin(int **carte, int taillecarte);
void defaite();
void deplacement_attaquant(int** carte, int i, int j);
int generer_attaquant(Case carte[], Attaquant liste_attaquant[], int avancee_vague, int vagues[][], int numero_vague);
oid lancerpartie ();
void menuDemarrage();
void placement_de_defenseur(int carte[][], int taillecarte);
void sauvegarde(const char* nom_fichier, int** tab, int ligne, int colonne);
