#include <stdio.h>
#include <math.h>

#define MAX_LIGNE 10
#define MAX_COLONNE 10

// Définitions des types de défenseurs
#define TYPE_DEFENSEUR_1 1 // Portée 3, dégâts 10
#define TYPE_DEFENSEUR_2 2 // Portée 5, dégâts 15
#define TYPE_DEFENSEUR_3 3 // Portée 2, dégâts 20

// Structure pour représenter une unité (attaquant ou défenseur)
typedef struct {
    int x; // Position en ligne
    int y; // Position en colonne
    int pointsDeVie; // Points de vie de l'unité
    int type; // Type de défenseur (0 pour attaquant)
} Unite;

// Fonction pour calculer la distance euclidienne entre deux unités
double calculerDistance(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

// Fonction pour obtenir la portée d'un défenseur en fonction de son type
int obtenirPortee(int type) {
    switch (type) {
        case TYPE_DEFENSEUR_1: return 3;
        case TYPE_DEFENSEUR_2: return 5;
        case TYPE_DEFENSEUR_3: return 2;
        default: return 0; // Type inconnu
    }
}

// Fonction pour obtenir les dégâts d'un défenseur en fonction de son type
int obtenirDegats(int type) {
    switch (type) {
        case TYPE_DEFENSEUR_1: return 10;
        case TYPE_DEFENSEUR_2: return 15;
        case TYPE_DEFENSEUR_3: return 20;
        default: return 0; // Type inconnu
    }
}

// Fonction pour permettre aux défenseurs d'attaquer les attaquants
void attaquer(Unite defenseurs[], int nbDefenseurs, Unite attaquants[], int nbAttaquants) {
    for (int i = 0; i < nbDefenseurs; i++) {
        for (int j = 0; j < nbAttaquants; j++) {
            if (attaquants[j].pointsDeVie <= 0) continue; // Attaquant mort, passe au suivant

            int portee = obtenirPortee(defenseurs[i].type);
            double distance = calculerDistance(defenseurs[i].x, defenseurs[i].y, attaquants[j].x, attaquants[j].y);
            if (distance <= portee) {
                // L'attaquant est à portée, il subit des dégâts
                int degats = obtenirDegats(defenseurs[i].type);
                attaquants[j].pointsDeVie -= degats;
                printf("Défenseur (type %d) en (%d, %d) attaque attaquant en (%d, %d). PV restants de l'attaquant : %d\n",
                       defenseurs[i].type, defenseurs[i].x, defenseurs[i].y, attaquants[j].x, attaquants[j].y, attaquants[j].pointsDeVie);

                if (attaquants[j].pointsDeVie <= 0) {
                    printf("Attaquant en (%d, %d) est éliminé !\n", attaquants[j].x, attaquants[j].y);
                }
            }
        }
    }
}

void attaquer_defenseurs(Case** carte, Defenseur* defenseurs, int nbDefenseurs, EnnemiActif* ennemis, int nbEnnemis, int* score) {
    for (int i = 0; i < nbDefenseurs; i++) {
        Defenseur def = defenseurs[i];
        for (int j = 0; j < nbEnnemis; j++) {
            EnnemiActif ennemi = ennemis[j];

            // Vérifie si l'ennemi est encore en vie
            if (ennemi.attaquant.vie <= 0) continue;

            // Calcul de la distance entre le défenseur et l'ennemi
            double distance = sqrt(pow(def.coordx - ennemi.x, 2) + pow(def.coordy - ennemi.y, 2));

            // Si l'ennemi est à portée
            if (distance <= def.portee) {
                // Applique les dégâts au hasard en fonction de l'esquive
                if ((rand() % 100) / 100.0 > ennemi.attaquant.esquive) {
                    ennemis[j].attaquant.vie -= def.degats;
                    printf("%s en (%d, %d) attaque %s en (%d, %d). PV restants de l'ennemi : %d\n",
                           def.emoji, def.coordx, def.coordy, ennemi.attaquant.emoji, ennemi.x, ennemi.y, ennemis[j].attaquant.vie);

                    // Si l'ennemi est éliminé
                    if (ennemis[j].attaquant.vie <= 0) {
                        printf("%s en (%d, %d) est éliminé !\n", ennemi.attaquant.emoji, ennemi.x, ennemi.y);
                        carte[ennemi.x][ennemi.y].type = 6; // Remet la case à "chemin"
                        (*score)++; // Incrémente le score
                        printf("Score actuel : %d\n", *score);
                    }
                } else {
                           ennemi.attaquant.emoji, ennemi.x, ennemi.y, def.emoji, def.coordx, def.coordy);
                }
            }
        }
    }
}







