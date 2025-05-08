//inclusion des bibliothèques nécessaires
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

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
typedef struct{
    int type; // 0=neige, 1=pierre, ..., 13=ours
    int x;    // ligne
    int y;    // colonne
}Case;

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

typedef struct {
    Attaquant attaquant;
    int x;
    int y;
}EnnemiActif;

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

void afficher_carte(Case** carte, int taillecarte){
    
    // On affiche la carte
    printf("    ");
    for (int i=0; i<taillecarte; i++){
    	if(i<26){
        	printf("%c ", 'a'+i);// minuscules jusqu'à 26
    	}
    	else{
    		printf("%c ", 'A'+(i-26));// majuscules après
    	}
    }
    printf("\n");
    printf("    ");
    for (int i=0; i<taillecarte; i++){
        printf("__");
    }
    printf("\n");
    
    for (int i=0; i<taillecarte; i++) {
    	printf("%02d |", i+1);  // Numéro de ligne
    	for (int j=0; j<taillecarte; j++) {
    		switch (carte[i][j].type){
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
            			exit(5);
    		}
    	}
    	printf("|\n");
    	}
    	printf("    ");
    	for (int i=0; i<taillecarte; i++){
    	    printf("‾‾");
    	}
    	printf("\n");
}

void creer_carte(Case** carte, int taillecarte) {
    for (int i=0; i<taillecarte; i++){
        carte[i]=(Case*)malloc(taillecarte*sizeof(Case));
        if (carte[i]==NULL) {
            printf("Erreur d'allocation mémoire\n");
            exit(1); //Terminer le programme si l'allocation échoue
        }
        for (int j=0; j<taillecarte; j++){
            carte[i][j].type=rand()%6; //Remplir la carte avec des valeurs aléatoires
        }
    }
}

void creer_chemin(Case** carte, int taillecarte){
    int j=rand()%(taillecarte-6)+3; //Colonne de départ
    int direction, directionprecedente;
    
    // Premier mouvement, on va tout droit (vers le bas)
    direction=0;
    carte[0][j].type=6; // Placement du drapeau sur la premiere case
    carte[1][j].type=6; // Placement du drapeau sur la deuxieme case
    
    directionprecedente=direction;

    // Créer le chemin en suivant la logique aléatoire mais en garantissant le premier et le dernier mouvement vers le bas
    for (int i=2; i<taillecarte-1; i++) {
        //Déplacement latéral aléatoire (mais pas l'opposé de la direction precedente) : -1 (gauche), 0 (tout droit), 1 (droite)
        do{
        	direction=rand()%3-1;
        }while (directionprecedente==-direction);
        
        directionprecedente=direction;

        //Calcul de la nouvelle position (temporaire pour vérification)
        int nouvellecolonne=j+direction;

        //Vérification des bornes
        if (nouvellecolonne<0){
            nouvellecolonne=0;
        }
        if (nouvellecolonne>=taillecarte){
            nouvellecolonne=taillecarte-1;
        }

        //Si on change de colonne, on met un drapeau au dessus de la nouvelle case
        if (direction!=0 && i>0) {
            carte[i-1][nouvellecolonne].type=6;
        }

        //Mise à jour de la position j
        j=nouvellecolonne;

        //On place le drapeau sur la case actuelle
        carte[i][j].type=6;
    }
    //On place la couronne sur la derniere case en allant tout droit (vers le bas)
	carte[taillecarte-1][j].type=7;
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

void generer_attaquant(Case** carte, int debut, EnnemiActif** ennemis, int* nbEnnemis){
	int attaquant=rand()%3;
	Attaquant nouv_ennemi;

	if(attaquant==0){
		nouv_ennemi=constructeur_SkieurFrenetique(nouv_ennemi);
		carte[0][debut].type=8;
	}
	else if(attaquant==1){
		nouv_ennemi=constructeur_SnowboarderAcrobate(nouv_ennemi);
		carte[0][debut].type=9;
	}
	else if(attaquant==2){
		nouv_ennemi=constructeur_LugisteBarjo(nouv_ennemi);
		carte[0][debut].type=10;
	}
	// Ajouter l'ennemi au tableau dynamique
    	EnnemiActif* temp=(EnnemiActif*)realloc(*ennemis,(*nbEnnemis+1)*sizeof(EnnemiActif));
   	if (temp==NULL){
        	printf("Erreur d'allocation mémoire.\n");
        	free(*ennemis);
        	exit(1);
    	}
    	*ennemis=temp;
    	(*ennemis)[*nbEnnemis].attaquant=nouv_ennemi;
    	(*ennemis)[*nbEnnemis].x=0;
    	(*ennemis)[*nbEnnemis].y=debut;
    	(*nbEnnemis)++;
}

void defaite(){
	int choix=0;
	do{ 
		printf("\n \t== Vous avez perdu ! ==\n");
		sleep(2);
		printf("\n \t Taper 1 pour retourner au menu\n");
		printf("\n \t Taper 2 pour quitter\n");
		printf("\n \t Votre choix : ");
		scanf("%d", &choix);
	}while(choix!=1 && choix!=2);
	
	if(choix==1){
		menuDemarrage();
	}
	else if(choix==2){
		printf("A plus 👋😊\n");
		exit(0);
	}
}


void lancerpartie() {
	srand(time(NULL));
    	int taillecarte;
    	int colonneCouronne, colonneDebut;
	int flocons = 120;
	EnnemiActif* ennemis = NULL;
	int nbEnnemis = 0;
    int score = 0; // Initialisation du score

    // Génération de la carte (entre 25 et 40) et du chemin
    taillecarte = rand() % 16 + 25;
    Case** carte = (Case**)malloc(taillecarte * sizeof(Case*));    
    	creer_carte(carte, taillecarte);
    	creer_chemin(carte, taillecarte);
    	printf("\nPour cette partie, la carte est de taille %d x %d\n", taillecarte, taillecarte); // On affiche la taille de la carte
    	//sleep(2); // On fait une pause de deux secondes pour laisser le temps de lire
    	printf("La carte est en cours de création...\n");
    	//sleep(2); // On fait une pause de deux secondes pour laisser le temps de lire
    	printf("Voici la carte :\n\n");
    	//sleep(1); // On fait une pause d'une seconde pour laisser le temps de lire
    	afficher_carte(carte, taillecarte);
    	
    
    	for (int i=0; i<taillecarte; i++) {
    		if (carte[0][i].type==6) {
        		colonneDebut=i;
        		break;
    		}
	}
	for (int j=0; j<taillecarte; j++) {
    		if (carte[taillecarte-1][j].type==7) {
        		colonneCouronne=j;
        		break;
    		}
	}
    
    	generer_attaquant(carte, colonneDebut, &ennemis, &nbEnnemis);
    	afficher_carte(carte, taillecarte);
    	//placement_de_defenseur(Case carte[], flocons);
    	//amelioration(flocons);
    	
	while (carte[taillecarte-1][colonneCouronne].type==7){
		usleep(500000);  // pause

    		deplacement_attaquant(carte, ennemis, nbEnnemis, taillecarte);
		
		// Vérifier si un ennemi atteint la couronne
		for (int i = 0; i < nbEnnemis; i++) {
			if (ennemis[i].x == taillecarte - 1 && ennemis[i].y == colonneCouronne) {
				defaite(); //L'ennemi a atteint la couronne
				return; //Quitter la boucle, fin de la partie
			}
		}
		
    		// Génère un nouvel attaquant seulement si la case est vide
    		if (carte[0][colonneDebut].type == 6) {
        		generer_attaquant(carte, colonneDebut, &ennemis, &nbEnnemis);
    		}

    		afficher_carte(carte, taillecarte);
    		//attaque_defenseurs();
        	//placement_de_defenseur(Case carte[], flocons);
        	//amelioration(flocons);
	}
    	
	// Libération de la mémoire
	free(ennemis);
    	
	for (int i=0; i<taillecarte; i++){
		free(carte[i]);
    	}
    
	free(carte);

void menuDemarrage() {	
	int choix_menu=0;  //choix + vérificfiication de la mémoire rentrée au clavier
    
	
	printf("\n \t=== MENU PRINCIPAL === \n"); //On libère la mémoire allouée pour la carte
    printf=("\n \t Nouvelle Partie (1) \t \n");
	printf("\n \t Reprendre (2) \t \n");
	printf("\n \t Quitter (3) \t \n\n");
	printf("Votre choix : ");
	scanf("%d",&choix_menu);
		
	while(choix_menu<1 || choix_menu>3) {
		
		printf("\n Veuillez entrer une valeur correcte : \n");
		printf("1 pour démarrer une nouvelle partie \n");
		printf("2 pour reprendre la dernière partie \n");
		printf("3 pour quitter le jeu \n");
			
		printf("\n \t Nouvelle Partie (1) \t \n");
		printf("\n \t Reprendre (2) \t \n");
		printf("\n \t Quitter (3) \t \n");
			
		scanf("%d",&choix_menu);
	}
		
	//application du choix fait par l'utilisateur 
	if(choix_menu==1) {
		lancerpartie();
	}
	//else if(choix_menu==2) {
	//	reprendrePartie();
	//}
	else if(choix_menu==3) {
		printf("A plus 👋😊\n");
		exit(0);
	}
	else {
		printf("Erreur : Le choix n'a pas pu être pris en compte \n");
		printf("Veuillez relancer \n");
		exit(1);
	}
}

int main (){
        menuDemarrage();

	/*	proposition du menu principal pour éviter les appels récursifs de fonctions 
	
		int choix_menu = 0; // Variable pour stocker le choix de l'utilisateur
		int jeu_en_cours = 1; // Variable pour contrôler la boucle principale
	
		while (jeu_en_cours) {
			printf("\n \t=== MENU PRINCIPAL ===\n");
			printf("\n \t Nouvelle Partie (1) \t \n");
			printf("\n \t Quitter (2) \t \n\n");
			printf("Votre choix : ");
			scanf("%d", &choix_menu);
	
			switch (choix_menu) {
				case 1:
					lancerpartie(); // Lance une nouvelle partie
					break;
				case 2:
					printf("A plus 👋😊\n");
					jeu_en_cours = 0; // Quitte la boucle principale
					break;
				default:
					printf("Choix invalide. Veuillez réessayer.\n");
			}
		} */






        return 0;
}

/* fonctions modifiées en consequence : 

	int menuDemarrage() {
    int choix_menu = 0; // Variable pour stocker le choix de l'utilisateur

    printf("\n \t=== MENU PRINCIPAL === \n");
    printf("\n \t Nouvelle Partie (1) \t \n");
    printf("\n \t Quitter (2) \t \n\n");
    printf("Votre choix : ");
    scanf("%d", &choix_menu);

    while (choix_menu < 1 || choix_menu > 2) {
        printf("\n Veuillez entrer une valeur correcte : \n");
        printf("1 pour démarrer une nouvelle partie \n");
        printf("2 pour quitter le jeu \n");
        printf("Votre choix : ");
        scanf("%d", &choix_menu);
    }

    return choix_menu; // Retourne le choix de l'utilisateur
}


void defaite() {
    printf("\n \t== Vous avez perdu ! ==\n");
    sleep(2);
    printf("\nRetour au menu principal...\n");
}



void lancerpartie() {
    srand(time(NULL));
    int taillecarte;
    int colonneCouronne, colonneDebut;
    int flocons = 120;
    EnnemiActif* ennemis = NULL;
    int nbEnnemis = 0;
    int score = 0; // Initialisation du score

    // Génération de la carte (entre 25 et 40) et du chemin
    taillecarte = rand() % 16 + 25;
    Case** carte = (Case**)malloc(taillecarte * sizeof(Case*));
    creer_carte(carte, taillecarte);
    creer_chemin(carte, taillecarte);
    printf("\nPour cette partie, la carte est de taille %d x %d\n", taillecarte, taillecarte);
    afficher_carte(carte, taillecarte);

    for (int i = 0; i < taillecarte; i++) {
        if (carte[0][i].type == 6) {
            colonneDebut = i;
            break;
        }
    }
    for (int j = 0; j < taillecarte; j++) {
        if (carte[taillecarte - 1][j].type == 7) {
            colonneCouronne = j;
            break;
        }
    }

    generer_attaquant(carte, colonneDebut, &ennemis, &nbEnnemis);
    afficher_carte(carte, taillecarte);

    while (carte[taillecarte - 1][colonneCouronne].type == 7) {
        usleep(500000); // Pause

        deplacement_attaquant(carte, ennemis, nbEnnemis, taillecarte);

        // Vérifier si un ennemi atteint la couronne
        for (int i = 0; i < nbEnnemis; i++) {
            if (ennemis[i].x == taillecarte - 1 && ennemis[i].y == colonneCouronne) {
                defaite(); // Affiche le message de défaite
                goto fin_partie; // Quitte la boucle et termine la partie
            }
        }

        // Génère un nouvel attaquant seulement si la case est vide
        if (carte[0][colonneDebut].type == 6) {
            generer_attaquant(carte, colonneDebut, &ennemis, &nbEnnemis);
        }

        afficher_carte(carte, taillecarte);
    }

fin_partie:
    // Libération de la mémoire
    free(ennemis);
    for (int i = 0; i < taillecarte; i++) {
        free(carte[i]);
    }
    free(carte);
}




int main() {
    int jeu_en_cours = 1; // Variable pour contrôler la boucle principale

    while (jeu_en_cours) {
        int choix_menu = menuDemarrage(); // Affiche le menu principal et récupère le choix

        switch (choix_menu) {
            case 1:
                lancerpartie(); // Lance une nouvelle partie
                break;
            case 2:
                printf("A plus 👋😊\n");
                jeu_en_cours = 0; // Quitte la boucle principale
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    }

    return 0;
}


*/



