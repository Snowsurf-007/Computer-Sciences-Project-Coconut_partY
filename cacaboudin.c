#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

// Définitions des constantes et structures
#define EMOJI_NEIGE "\xE2\x97\xBB\xEF\xB8\x8F"
#define EMOJI_PIERRE "\xF0\x9F\xAA\xA8"
#define EMOJI_DRAPEAU "\xF0\x9F\x9A\xA9"
#define EMOJI_SAPIN "\xF0\x9F\x8C\xB2"
#define EMOJI_PINGOUIN "\xF0\x9F\x90\xA7"
#define EMOJI_BONHOMMENEIGE "\xE2\x9B\x84"
#define EMOJI_OURS "\xF0\x9F\x90\xBB"
#define EMOJI_SKIEUR "\xE2\x9B\xB7\xEF\xB8\x8F"
#define EMOJI_SNOWBOARDER "\xF0\x9F\x8F\x82"
#define EMOJI_LUGISTE "\xF0\x9F\x9B\xB7"
#define EMOJI_COURONNE "\xF0\x9F\x91\x91"
#define EMOJI_FLOCON "\xE2\x9D\x84\xEF\xB8\x8F"

#define MAX_LIGNE 10
#define MAX_COLONNE 10

// Enum pour les types de cases
typedef enum{
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
} Defenseur;

typedef struct{
    TypeCase type;
    int x;    // ligne
    int y;    // colonne
    Defenseur defenseur;
} Case;

typedef struct{
    int vie;
    float esquive;
    int gain;
    int coordx;
    int coordy;
} Attaquant;

typedef struct {
    Attaquant attaquant;
    int x;
    int y;
} EnnemiActif;

Defenseur constructeur_PinguPatrouilleur(Defenseur a){
    a.portee=5;
    a.degats=50;
    a.vitessetir=0.5;
    a.prix=100;
    return a;
}

Defenseur constructeur_FloconPerceCiel(Defenseur a){
    a.portee=10;
    a.degats=300;
    a.vitessetir=2;
    a.prix=200;
    return a;
}

Defenseur constructeur_GardePolaire(Defenseur a){
    a.portee=2;
    a.degats=100;
    a.vitessetir=1;
    a.prix=150;
    return a;
}

Attaquant constructeur_SkieurFrenetique(Attaquant a){ //attaquant rapide et faible, petit taux d'esquive 
    a.vie=250;
    a.esquive=0.15;
    a.gain=20;
    return a;
}

Attaquant constructeur_SnowboarderAcrobate(Attaquant a){ //attaquant vitesse moyenne, vie moyenne mais bonne esquive
    a.vie=500;
    a.esquive=0.30;
    a.gain=30;
    return a;
}

Attaquant constructeur_LugisteBarjo(Attaquant a){ //attaquant lent et resistant
    a.vie=2000;
    a.esquive=0.01;
    a.gain=40;
    return a;
}

// Prototypes des fonctions
void afficher_carte(Case** carte, int taillecarte);
void creer_carte(Case*** carte, int taillecarte);
void creer_chemin(Case** carte, int taillecarte);
void deplacement_attaquant(Case** carte, EnnemiActif* ennemis, int nbEnnemis, int taillecarte);
void generer_attaquant(Case** carte, int debut, EnnemiActif** ennemis, int* nbEnnemis, int* compteur, int* vague);
void lancerpartie(Case*** carte, int* taillecarte, Defenseur** defenseurs, int* nbDefenseurs, EnnemiActif** ennemis, int* nbEnnemis, int* score, int* flocons, int* vague);
int menuDemarrage();
void defaite(int* score);
void victoire(int* score);
void placement_de_defenseur(Case** carte, int taillecarte, int* flocons, Defenseur* liste_defenseur, int* nb_defenseur);
void chargement(const char* nom_fichier, Case*** carte, int* taillecarte, Defenseur** defenseurs, int* nbDefenseurs, EnnemiActif** ennemis, int* nbEnnemis, int* score, int* flocons, int* vague);
void sauvegarde(const char* nom_fichier, Case** carte, int taillecarte, Defenseur* defenseurs, int nbDefenseurs, EnnemiActif* ennemis, int nbEnnemis, int score, int flocons, int vague);

// Définitions des fonctions

// Fonction pour calculer la distance euclidienne entre deux unités
double calculerDistance(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

// Fonction pour permettre aux défenseurs d'attaquer les attaquants
void attaquer (Defenseur* defenseur, int nbDefenseurs, Attaquant* attaquants, int nbAttaquants) {
    for (int i = 0; i < nbDefenseurs; i++) {
        for (int j = 0; j < nbAttaquants; j++) {
            if (attaquants[j].vie <= 0) {
                
            }

            double distance = calculerDistance(defenseur[i].coordx, defenseur[i].coordy, attaquants[j].coordx, attaquants[j].coordy);
            if (distance <= defenseur[i].portee) {
                // L'attaquant est à portée, il subit des dégâts
                attaquants[j].vie -= defenseur[i].degats;

                if (attaquants[j].vie <= 0) {
                    
                }
            }
        }
    }
}

void attaquer_defenseurs(Case*** carte, Defenseur** defenseurs, int* nbDefenseurs, EnnemiActif** ennemis, int* nbEnnemis, int* score) {
    for (int i = 0; i < *nbDefenseurs; i++) {
        Defenseur def = *defenseurs[i];
        for (int j = 0; j < *nbEnnemis; j++) {
            EnnemiActif ennemi = *ennemis[j];

            // Vérifie si l'ennemi est encore en vie
            if (ennemi.attaquant.vie > 0) {
                // Calcul de la distance entre le défenseur et l'ennemi
                double distance = sqrt(pow(def.coordx - ennemi.x, 2) + pow(def.coordy - ennemi.y, 2));

                // Si l'ennemi est à portée
                if (distance <= def.portee) {
                    // Applique les dégâts au hasard en fonction de l'esquive
                    if ((rand() % 100) / 100.0 > ennemi.attaquant.esquive) {
                        ennemis[j]->attaquant.vie -= def.degats;

                        // Si l'ennemi est éliminé
                        if (ennemis[j]->attaquant.vie <= 0) {
                            carte[ennemi.x][ennemi.y]->type = 6; // Remet la case à "chemin"
                            (*score)++; // Incrémente le score
                        }
                    }
                }
            }
        }
    }
}


void afficher_carte(Case** carte, int taillecarte) {
    printf("    ");
    for (int i = 0; i < taillecarte; i++) {
        if (i < 26) {
            printf("%c ", 'a' + i);
        } else {
            printf("%c ", 'A' + (i - 26));
        }
    }
    printf("\n    ");
    for (int i = 0; i < taillecarte; i++) {
        printf("__");
    }
    printf("\n");

    for (int i = 0; i < taillecarte; i++) {
        printf("%02d |", i + 1);
        for (int j = 0; j < taillecarte; j++) {
            switch (carte[i][j].type) {
                case 0:
                case 1:
                case 2:
                case 3:
                    printf("%s ", EMOJI_NEIGE);
                    break;
                case 4:
                    printf("%s", EMOJI_PIERRE);
                    break;
                case 5:
                    printf("%s", EMOJI_SAPIN);
                    break;
                case 6:
                    printf("%s", EMOJI_DRAPEAU);
                    break;
                case 7:
                    printf("%s", EMOJI_COURONNE);
                    break;
                case 8:
                    printf("%s ", EMOJI_SKIEUR);
                    break;
                case 9:
                    printf("%s", EMOJI_SNOWBOARDER);
                    break;
                case 10:
                    printf("%s", EMOJI_LUGISTE);
                    break;
                case 11:
                    printf("%s", EMOJI_PINGOUIN);
                    break;
                case 12:
                    printf("%s", EMOJI_BONHOMMENEIGE);
                    break;
                case 13:
                    printf("%s", EMOJI_OURS);
                    break;
                default:
                    exit(1);
            }
        }
        printf("|\n");
    }
    printf("    ");
    for (int i = 0; i < taillecarte; i++) {
        printf("‾‾");
    }
    printf("\n");
}

void creer_carte(Case*** carte, int taillecarte) {
    *carte = (Case**)malloc(taillecarte * sizeof(Case*));
    for (int i = 0; i < taillecarte; i++) {
        (*carte)[i] = (Case*)malloc(taillecarte * sizeof(Case));
        if ((*carte)[i] == NULL) {
            printf("\t Erreur d'allocation mémoire\n");
            exit(2);
        }
        for (int j = 0; j < taillecarte; j++) {
            (*carte)[i][j].type = rand() % 6;
	    if (((*carte)[i][j].type == 0) || ((*carte)[i][j].type == 1) || ((*carte)[i][j].type == 2)){
	        (*carte)[i][j].type = 3;
	    }
        }
    }
}

void creer_chemin(Case** carte, int taillecarte) {
    int j = rand() % (taillecarte - 6) + 3;
    int direction, directionprecedente = 0;

    carte[0][j].type = 6;
    carte[1][j].type = 6;

    for (int i = 2; i < taillecarte - 1; i++) {
        do {
            direction = rand() % 3 - 1;
        } while (directionprecedente == -direction);

        directionprecedente = direction;
        int nouvellecolonne = j + direction;

        if (nouvellecolonne < 0) nouvellecolonne = 0;
        if (nouvellecolonne >= taillecarte) nouvellecolonne = taillecarte - 1;

        if (direction != 0 && i > 0) {
            carte[i - 1][nouvellecolonne].type = 6;
        }

        j = nouvellecolonne;
        carte[i][j].type = 6;
    }
    carte[taillecarte - 1][j].type = 7;
}

void deplacement_attaquant(Case** carte, EnnemiActif* ennemis, int nbEnnemis, int taillecarte){
    for (int i=0; i<nbEnnemis; i++){
        int x=ennemis[i].x;
        int y=ennemis[i].y;

        // Sauvegarde le type pour pouvoir déplacer
        int type_attaquant=carte[x][y].type;

        // Déplacement bas > droite > gauche
        if (x+1<taillecarte && (carte[x+1][y].type==6 || carte[x+1][y].type==7)){
            carte[x+1][y].type=type_attaquant;
            carte[x][y].type=6;
            ennemis[i].x++;
        }
        else if (y+1<taillecarte && (carte[x][y+1].type==6 || carte[x][y+1].type==7)){
            carte[x][y+1].type=type_attaquant;
            carte[x][y].type=6;
            ennemis[i].y++;
        }
        else if (y-1>=0 && (carte[x][y-1].type==6 || carte[x][y-1].type==7)){
            carte[x][y-1].type=type_attaquant;
            carte[x][y].type=6;
            ennemis[i].y--;
        }
        // Sinon : ne bouge pas
    }
}

void generer_attaquant(Case** carte, int debut, EnnemiActif** ennemis, int* nbEnnemis, int* compteur, int* vague){
	int attaquant=-1;
	Attaquant nouv_ennemi;
	
	// Limiter le nombre d'ennemis par vague
        int max_ennemis=5+(((*vague)-1)*2);
        if (*compteur>=max_ennemis) {
            return;
        }
	
	if (*vague<=2){
		attaquant=0;
	}
	else if (*vague<=4){
		attaquant=rand()%2;
	}
	else{
		attaquant=rand()%3;
	}

	if(attaquant==0){
        	Attaquant temp_ennemi;
        	nouv_ennemi = constructeur_SkieurFrenetique(temp_ennemi);
		carte[0][debut].type=8;
	}
	else if(attaquant==1){
        	Attaquant temp_ennemi;
        	nouv_ennemi = constructeur_SnowboarderAcrobate(temp_ennemi);
		carte[0][debut].type=9;
	}
	else if(attaquant==2){
        	Attaquant temp_ennemi;
        	nouv_ennemi = constructeur_LugisteBarjo(temp_ennemi);
		carte[0][debut].type=10;
	}
	
	// Ajouter l'ennemi au tableau dynamique
    	EnnemiActif* temp=(EnnemiActif*)realloc(*ennemis,(*nbEnnemis+1)*sizeof(EnnemiActif));
   	if (temp==NULL){
        	printf("\t Erreur d'allocation mémoire.\n");
        	free(*ennemis);
        	temp = NULL;
        	exit(2);
    	}
    	*ennemis=temp;
    	(*ennemis)[*nbEnnemis].attaquant=nouv_ennemi;
    	(*ennemis)[*nbEnnemis].x=0;
    	(*ennemis)[*nbEnnemis].y=debut;
    	(*nbEnnemis)++;
    	(*compteur)++;
}

void chargement(const char* nom_fichier, Case*** carte, int* taillecarte, Defenseur** defenseurs, int* nbDefenseurs, EnnemiActif** ennemis, int* nbEnnemis, int* score, int* flocons, int* vague) {
    FILE* fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        printf("\t Erreur : le fichier %s n'a pas pu être ouvert \n", nom_fichier);
        exit(3);
    }

    fscanf(fichier, "%d", taillecarte);

    *carte = (Case**)malloc(*taillecarte * sizeof(Case*));
    for (int i = 0; i < *taillecarte; i++) {
        (*carte)[i] = (Case*)malloc(*taillecarte * sizeof(Case));
    }

    for (int i = 0; i < *taillecarte; i++) {
        for (int j = 0; j < *taillecarte; j++) {
            fscanf(fichier, "%d", &((*carte)[i][j].type));
        }
    }

    fscanf(fichier, "%d", nbDefenseurs);
    *defenseurs = (Defenseur*)malloc(*nbDefenseurs * sizeof(Defenseur));
    for (int i = 0; i < *nbDefenseurs; i++) {
        fscanf(fichier, "%d %d %d %d %d", &(*defenseurs)[i].portee, &(*defenseurs)[i].degats, &(*defenseurs)[i].prix, &(*defenseurs)[i].coordx, &(*defenseurs)[i].coordy);
    }

    fscanf(fichier, "%d", nbEnnemis);
    *ennemis = (EnnemiActif*)malloc(*nbEnnemis * sizeof(EnnemiActif));
    for (int i = 0; i < *nbEnnemis; i++) {
        fscanf(fichier, "%d %f %d %d %d", &(*ennemis)[i].attaquant.vie, &(*ennemis)[i].attaquant.esquive, &(*ennemis)[i].attaquant.gain, &(*ennemis)[i].x, &(*ennemis)[i].y);
    }

    fscanf(fichier, "%d", score);
    fscanf(fichier, "%d", flocons);
    fscanf(fichier, "%d", vague);

    fclose(fichier);
}

void sauvegarde(const char* nom_fichier, Case** carte, int taillecarte, Defenseur* defenseurs, int nbDefenseurs, EnnemiActif* ennemis, int nbEnnemis, int score, int flocons, int vague) {
    // Ouverture du fichier en mode écriture
    FILE* fichier = fopen(nom_fichier, "w");

    // Vérification du bon déroulement de l'ouverture
    if (fichier == NULL) {
        printf("\t Erreur : le fichier %s n'a pas pu être ouvert \n", nom_fichier);
        exit(3);
    }

    // Sauvegarde des dimensions de la carte
    fprintf(fichier, "%d\n", taillecarte);

    // Sauvegarde de la carte
    for (int i = 0; i < taillecarte; i++) {
        for (int j = 0; j < taillecarte; j++) {
            fprintf(fichier, "%d ", carte[i][j].type);
        }
        fprintf(fichier, "\n");
    }

    // Sauvegarde des défenseurs
    fprintf(fichier, "%d\n", nbDefenseurs); // Nombre de défenseurs
    for (int i = 0; i < nbDefenseurs; i++) {
        fprintf(fichier, "%d %d %d %d %d\n", defenseurs[i].portee, defenseurs[i].degats, defenseurs[i].prix, defenseurs[i].coordx, defenseurs[i].coordy);
    }

    // Sauvegarde des ennemis actifs
    fprintf(fichier, "%d\n", nbEnnemis); // Nombre d'ennemis
    for (int i = 0; i < nbEnnemis; i++) {
        fprintf(fichier, "%d %f %d %d %d\n", ennemis[i].attaquant.vie, ennemis[i].attaquant.esquive, ennemis[i].attaquant.gain, ennemis[i].x, ennemis[i].y);
    }

    // Sauvegarde des autres variables importantes
    fprintf(fichier, "%d\n", score);   // Score
    fprintf(fichier, "%d\n", flocons); // Monnaie
    fprintf(fichier, "%d\n", vague);   // Numéro de la vague

    fclose(fichier); // Fermeture du fichier
}

void placement_de_defenseur(Case** carte, int taillecarte, int* flocons, Defenseur* liste_defenseur, int* nb_defenseur) {
    int placer = -1;
    
    do {
        printf("\t Souhaitez-vous placer un défenseur ?\n\t 1 pour oui ou 0 pour non\n");
        printf("\t Votre choix : ");
        if (scanf(" %d", &placer) != 1) {
            printf("\t Entrée invalide (entier attendu). Fin du programme.\n");
            exit(4);
        }

        while (placer != 0 && placer != 1) {
            printf("\tValeur incorrecte. Réessayez :\n");
            printf("\t Votre choix : ");
            if (scanf(" %d", &placer) != 1) {
                printf("\tEntrée invalide (entier attendu). Fin du programme.\n");
                exit(4);
            }
        }

        if (placer == 0) {
            break;
        }

        int choix_defenseur = 0;
        Defenseur nouv_def;

        // Boucle jusqu'à ce que le joueur choisisse un défenseur qu'il peut se payer
        do {
            printf("\n\t Choisissez un défenseur à placer :\n");
            printf("\t 1 - Pingu-Patrouilleur (100 %s )\n", EMOJI_FLOCON);
            printf("\t 2 - Flocon-Perce-Ciel (200 %s )\n", EMOJI_FLOCON);
            printf("\t 3 - Garde Polaire (150 %s )\n", EMOJI_FLOCON);
            printf("\t Votre choix : ");

            if (scanf(" %d", &choix_defenseur) != 1) {
                printf("\t Entrée invalide. Fin du programme.\n");
                exit(4);
            }

            while (choix_defenseur < 1 || choix_defenseur > 3) {
                printf("\t Choix invalide. Réessayez :\n");
                printf("\t Votre choix : ");
                if (scanf(" %d", &choix_defenseur) != 1) {
                    printf("\t Entrée invalide. Fin du programme.\n");
                    exit(4);
                }
            }

            // Crée le défenseur selon le choix
            if (choix_defenseur == 1) {
                nouv_def = constructeur_PinguPatrouilleur(nouv_def);
            } 
            else if (choix_defenseur == 2) {
                nouv_def = constructeur_FloconPerceCiel(nouv_def);
            } 
            else {
                nouv_def = constructeur_GardePolaire(nouv_def);
            }

            if (*flocons < nouv_def.prix) {
                printf("\t Vous n'avez pas assez de flocons(%s ) (%d requis, %d disponibles).\n",EMOJI_FLOCON, nouv_def.prix, *flocons);
                printf("\t Souhaitez-vous choisir un autre défenseur ?\n1 pour oui ou 0 pour non\n");
                printf("\t Votre choix : ");
                
                if (scanf(" %d", &placer) != 1 || (placer != 0 && placer != 1)) {
                    printf("\t Entrée invalide. Fin du programme.\n");
                    exit(4);
                }
                if (placer == 0) {
                    return;
                }
            }

        } while (*flocons < nouv_def.prix);

        // Lecture coordonnées de placement
        int coord_x_index = 0, coord_y = 0;
        char coord_x_char;
        do {
            printf("\n\t Choisissez une coordonnée x (lettre a-%c) :\n", 'A' + taillecarte - 27);
            printf("\t Votre choix : ");
            
            if (scanf(" %c", &coord_x_char) != 1) {
                printf("\t Entrée invalide. Fin du programme.");
                exit(4);
            }

            if (coord_x_char >= 'a' && coord_x_char <= 'z') {
                coord_x_index = coord_x_char - 'a';
            }
            else if (coord_x_char >= 'A' && coord_x_char <= 'Z') {
                coord_x_index = coord_x_char - 'A' + 26;
            }
            else {
                coord_x_index = -1;
            }

        } while (coord_x_index < 0 || coord_x_index >= taillecarte);

        do {
            printf("\t Choisissez une coordonnée y (entre 1 et %d) :\n", taillecarte);
            printf("\t Votre choix : ");
            
            if (scanf(" %d", &coord_y) != 1) {
                printf("\t Entrée invalide. Fin du programme.\n");
                exit(4);
            }
            coord_y -= 1;
        } while (coord_y < 0 || coord_y >= taillecarte);

        if (carte[coord_y][coord_x_index].type != 0 && carte[coord_y][coord_x_index].type != 1 && carte[coord_y][coord_x_index].type != 2 && carte[coord_y][coord_x_index].type != 3) {
            printf("\t Cette case n'est pas de la neige. Recommencez.\n");
            continue;
        }

        // Placement du défenseur
        carte[coord_y][coord_x_index].type = choix_defenseur + 10;
        carte[coord_y][coord_x_index].defenseur = nouv_def;
        *flocons -= nouv_def.prix;
        liste_defenseur[*nb_defenseur] = nouv_def;
        (*nb_defenseur)++;
        
        afficher_carte(carte, taillecarte);
        
        printf("\n\t Défenseur placé. Il vous reste %d %s .\n", *flocons, EMOJI_FLOCON);

    } while (placer == 1);
}

void lancerpartie(Case*** carte, int* taillecarte, Defenseur** defenseurs, int* nbDefenseurs, EnnemiActif** ennemis, int* nbEnnemis, int* score, int* flocons, int* vague) {
    
    int colonneCouronne, colonneDebut;
    int compteur=0;
    char choix;

    if(*taillecarte==0){
        // Génération de la carte (entre 30 et 45) et du chemin
        *taillecarte = rand() % 16 + 30;
        creer_carte(carte, *taillecarte);
        creer_chemin(*carte, *taillecarte);
    }
    printf("\n\t Pour cette partie, la carte est de taille %d x %d\n", *taillecarte, *taillecarte);
    afficher_carte(*carte, *taillecarte);

    for (int i = 0; i < *taillecarte; i++) {
        if ((*carte)[0][i].type == 6) {
            colonneDebut = i;
            break;
        }
    }
    for (int j = 0; j < *taillecarte; j++) {
        if ((*carte)[*taillecarte - 1][j].type == 7) {
            colonneCouronne = j;
            break;
        }
    }
	
	for(; *vague<11; (*vague)++){
		compteur=0;
		placement_de_defenseur(*carte, *taillecarte, flocons, *defenseurs, nbDefenseurs);
		while ((*carte)[*taillecarte-1][colonneCouronne].type==7){
		    usleep(400000); // Pause
			
		    deplacement_attaquant(*carte, *ennemis, *nbEnnemis, *taillecarte);
		    attaquer_defenseurs(carte, defenseurs, nbDefenseurs, ennemis, nbEnnemis, score);

		    // Vérifier si un ennemi atteint la couronne
		    for (int i = 0; i < *nbEnnemis; i++) {
                        if ((*ennemis)[i].x == *taillecarte - 1 && (*ennemis)[i].y == colonneCouronne){
		            defaite(score);
        		    // Libérer mémoire proprement avant de quitter
        		    free(*ennemis);
        		    *ennemis = NULL;
        		    for (int k = 0; k < *taillecarte; k++){
        			free((*carte)[k]);
        			free(*carte);
        			(*carte)[k] = NULL;
        			*carte = NULL;
        			return;
        		    }
		        }
		    }

		    // Génère un nouvel attaquant seulement si la case est vide
		    if ((*carte)[0][colonneDebut].type == 6 && compteur<=8){
		        generer_attaquant(*carte, colonneDebut, ennemis, nbEnnemis, &compteur, vague);
		    }
		    system("clear");
		    afficher_carte(*carte, *taillecarte);
		}
		printf("\n \tScore=%d\n", *score);
		sleep(2);
		do{
		    printf("\t Souhaitez-vous sauvegarder la partie ? (o/n)\n");
		    printf("\t Votre choix : ");
		    
                    if (scanf(" %c", &choix) != 1) {
                        printf("\t Entrée invalide (lettre attendue). Fin du programme.\n");
                        exit(4);
                    }
                    if (choix == 'o') {
                        sauvegarde("sauvegarde.txt", *carte, *taillecarte, *defenseurs, *nbDefenseurs, *ennemis, *nbEnnemis, *score, *flocons, *vague);
                        printf("\t Partie sauvegardée !\n");
                    }
                }while(choix != 'o' && choix != 'n');
	}
	victoire(score);
    // Libération de la mémoire
    free(*ennemis);
    *ennemis = NULL;
    for (int i = 0; i < *taillecarte; i++) {
        free((*carte)[i]);
        (*carte)[i] = NULL;
    }
    free(*carte);
    *carte = NULL;
}

int menuDemarrage(){
    int choix_menu=0; //Variable pour stocker le choix de l'utilisateur
    
    printf("\n \t=== %s%s%s OPERATION FLOCON %s %s%s === \n", EMOJI_PINGOUIN, EMOJI_BONHOMMENEIGE, EMOJI_OURS, EMOJI_SKIEUR, EMOJI_SNOWBOARDER, EMOJI_LUGISTE);

    printf("\n \t=== MENU PRINCIPAL === \n");
    printf("\n \t Nouvelle Partie (1) \t \n");
    printf("\n \t Reprendre une partie (2) \t \n");
    printf("\n \t Quitter (3) \t \n");
    printf("\n \t Votre choix : ");
    if (scanf(" %d", &choix_menu) != 1) {
        printf("\t Entrée invalide (entier attendu). Fin du programme.\n");
        exit(4);
    }

    while (choix_menu < 1 || choix_menu > 3) {
        printf("\n \t Veuillez entrer une valeur correcte : \n");
        printf("\t 1 pour démarrer une nouvelle partie \n");
        printf("\t 2 pour reprendre une ancienne partie \n");
        printf("\t 3 pour quitter le jeu \n");
        printf("\t Votre choix : ");
        if (scanf(" %d", &choix_menu) != 1) {
                printf("\t Entrée invalide (entier attendu). Fin du programme.\n");
                exit(4);
            }
    }
    return choix_menu; // Retourne le choix de l'utilisateur
}

void defaite(int* score) {
    printf("\n \t== Vous avez perdu ! ==\n");
    printf("\n \tScore=%d\n", *score);
    sleep(2);
    printf("\n \tRetour au menu principal...\n");
    sleep(2);
}

void victoire(int* score) {
    printf("\n \t== Vous avez gagné ! ==\n");
    printf("\n \tScore=%d\n", *score);
    sleep(2);
    printf("\n \tRetour au menu principal...\n");
    sleep(2);
}

int main() {
    system("clear");
    int jeu_en_cours=1; // Variable pour contrôler la boucle principale
    srand(time(NULL));   
    // Initialisation des variables
    Case** carte=NULL; 
    int taillecarte=0;
    int nbDefenseurs=0;
    EnnemiActif* ennemis = NULL;
    int nbEnnemis=0;
    int score=0;
    int flocons=350;
    int vague=0;
    Defenseur* defenseurs=(Defenseur*)malloc(100 * sizeof(Defenseur)); // Pre-allocation d'espace pour 100 defenseurs
    if (defenseurs == NULL) {
        printf("\t Erreur d'allocation mémoire pour les défenseurs\n");
        exit(2);
    }

    while (jeu_en_cours==1){
        int choix_menu=menuDemarrage(); // Affiche le menu principal et récupère le choix

        switch (choix_menu){
            case 1:
                lancerpartie(&carte, &taillecarte, &defenseurs, &nbDefenseurs, &ennemis, &nbEnnemis, &score, &flocons, &vague); // Lance une nouvelle partie
                break;
            case 2:
                chargement("sauvegarde.txt", &carte, &taillecarte, &defenseurs, &nbDefenseurs, &ennemis, &nbEnnemis, &score, &flocons, &vague);
                lancerpartie(&carte, &taillecarte, &defenseurs, &nbDefenseurs, &ennemis, &nbEnnemis, &score, &flocons, &vague); // Reprend la partie chargée
            break;
            case 3:
                printf("A plus 👋😊\n");
                jeu_en_cours=0; // Quitte la boucle principale
                break;
            default:
                printf("\t Choix invalide. Veuillez réessayer.\n");
        }
    }
    
    free(defenseurs);
    defenseurs = NULL;

    return 0;
}
