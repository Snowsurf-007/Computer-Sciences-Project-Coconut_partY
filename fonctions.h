//inclusion des bibliothèques nécessaires
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

// On définit les emojis utilisés pour la carte
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
typedef enum{// Enum pour les types de cases
    NEIGE=0,
    PIERRE,
    SAPIN,
    DRAPEAU,
    COURONNE,
    SKIEUR,
    SNOWBOARDER,
    LUGISTE,
    PINGOUIN,
    BONHOMMENEIGE,
    OURS
} TypeCase;

typedef struct{
        int portee;
        int degats;
        float vitessetir;
        int prix;
        int coordx;
        int coordy;
        int niveau;
}Defenseur;

typedef struct{
    int type; // 0=neige, 1=pierre, ..., 13=ours
    int x;    // ligne
    int y;    // colonne
    Defenseur defenseur;
}Case;

typedef struct{
        int vie;
        float esquive;
        int gain;
}Attaquant;

typedef struct {
    Attaquant attaquant;
    int x;
    int y;
}EnnemiActif;

// On définit les fonctions
Defenseur constructeur_PinguPatrouilleur(Defenseur a);
Defenseur constructeur_FloconPerceCiel(Defenseur a);
Defenseur constructeur_GardePolaire(Defenseur a);
Attaquant constructeur_SkieurFrenetique(Attaquant a);
Attaquant constructeur_SnowboarderAcrobate(Attaquant a);
Attaquant constructeur_LugisteBarjo(Attaquant a);
void deplacement_attaquant(Case** carte, EnnemiActif*ennemis, int nbEnnemis, int taillecarte);
int** chargement(const char* nom_fichier, int* ligne, int* colonne);
void amelioration(Case** carte, int taillecarte, int monnaie);
void afficher_carte(Case **carte, int taillecarte);
void creer_carte(Case **carte, int taillecarte);
void creer_chemin(Case **carte, int taillecarte);
void defaite();
void generer_attaquant(Case** carte, int debut, EnnemiActif** ennemis, int* nbEnnemis, int* compteur);
//void generer_attaquant(Case carte[], Attaquant liste_attaquant[], int avancee_vague, int vagues[][], int numero_vague);
void lancerpartie ();
void placement_de_defenseur(Case** carte, int taillecarte, int monnaie);
void sauvegarde(const char* nom_fichier, int** tab, int ligne, int colonne);
