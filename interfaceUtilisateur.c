#include"interfaceUtilisateur.h"

int menuDemarrage(){
    int choix_menu=0; //Variable pour stocker le choix de l'utilisateur
    
    printf("\n \t=== %s%s%s OPERATION FLOCON %s %s%s === \n", EMOJI_PINGOUIN, EMOJI_BONHOMMENEIGE, EMOJI_OURS, EMOJI_SKIEUR, EMOJI_SNOWBOARDER, EMOJI_LUGISTE);

    printf("\n \t=== MENU PRINCIPAL === \n");
    printf("\n \t Nouvelle Partie (1) \t \n");
    printf("\n \t Reprendre une partie (2) \t \n");
    printf("\n \t Quitter (3) \t \n\n");
    printf("Votre choix : ");
    scanf("%d", &choix_menu);

    while (choix_menu < 1 || choix_menu > 3) {
        printf("\n Veuillez entrer une valeur correcte : \n");
        printf("1 pour démarrer une nouvelle partie \n");
        printf("2 pour reprendre une ancienne partie \n");
        printf("3 pour quitter le jeu \n");
        printf("Votre choix : ");
        scanf("%d", &choix_menu);
    }
    return choix_menu; // Retourne le choix de l'utilisateur
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

void placement_de_defenseur(int carte[][], int taillecarte){
        int placer = -1; //quand le joueur decidera s'il veut placer un défenseur
        int choix_defenseur = 0;
        int coord_x = 0; //choix de la position du defenseur à placer
        int coord_y = 0;

//Choix du placement d'un défenseur
        printf("souhaitez-vous placer un défenseur ?\n1 pour oui ou 0 pour non\n");
        scanf("%d", &placer);
        
        while(placer != 0 || placer != 1){
                printf("La valeur entrée est incorrecte, veuillez réessayer.\n");
                scanf("%d", &placer);
        }
        while(placer == 1){
                printf("choisissez le défenseur à placer :\n 1 pour le Pingu-Patrouilleur\n");
                printf("2 pour le Flocon_Perce-Ciel\n3 pour le garde polaire\n");
                scanf("%d", &choix_defenseur);
                
                while(choix_defenseur != 1 || choix_defenseur != 2 || choix_defenseur != 3){
                        printf("La valeur entrée est incorrecte, veuillez réessayer.\n");
                        scanf("%d", &choix_defenseur);
                }
                while(monnaie < liste_defenseur[choix_defenseur].prix){
                        printf("monnaie insuffisante, souhaitez vous toujours placer un defenseur ?\n");
                        printf("1 pour oui ou 0 pour non\n");
                        scanf("%d", &placer);
                        
                        while(placer != 0 || placer != 1){
                                printf("La valeur entrée est incorrecte, veuillez réessayer.\n");
                                scanf("%d", &placer);
                        }
                if(placer == 0){
                        break;
                }
                printf("choisissez le défenseur à placer :\n 1 pour le Pingu-Patrouilleur\n");
                printf("2 pour le Flocon_Perce-Ciel\n3 pour le garde polaire\n");
                scanf("%d", &choix_defenseur);
                }
                printf("Où souhaitez-vous placer le défenseur, choisissez une coordonnées x.\n");
                scanf("%d", &coord_x);
                while(coord_x > taillecarte || coord_x < 0){
                        printf("La valeur entrée est incorrecte veuillez réessayer.\n");
                        printf("Où souhaitez-vous placer le défenseur, choisissez une coordonnées x.\n");
                        scanf("%d", &coord_x);
                }
                printf("Veuillez maintenant choisir la coordonnées y.\n");
                scanf("%d", &coord_y)
                while(coord_y > taillearte || coord_y < 0){
                        printf("La valeur entrée est incorrecte veuillez réessayer.\n");
                        printf("Veuillez maintenant choisir la coordonnées y.\n");
                        scanf("%d", &coord_y);
                }
                while(carte[coord_x][coord_y] != 0 || carte[coord_x][coord_y] != 1 || carte[coord_x][coord_y] != 2 || carte[coord_x][coord_y] != 3){ //la case doit etre une case avec de la neige
                        printf("Impossible de mettre un defenseur sur cette case veuillez en choisir une autre.\n");
                        printf("Où souhaitez-vous placer le défenseur, choisissez une coordonnées x.\n");
                        scanf("%d", &coord_x);
                        while(coord_x > taillecarte || coord_x < 0){
                                printf("La valeur entrée est incorrecte veuillez réessayer.\n");
                                printf("Où souhaitez-vous placer le défenseur, choisissez une coordonnées x.\n");
                                scanf("%d", &coord_x);
                        }
                        printf("Veuillez maintenant choisir la coordonnées y.\n");
                        scanf("%d", &coord_y);
                        while(coord_y > taillecarte || coord_y < 0){
                                printf("La valeur entrée est incorrecte veuillez réessayer.\n");
                                printf("Veuillez maintenant choisir la coordonnées y.\n");
                                scanf("%d", &coord_y);
                        }
                }
                monnaie -= carte[coord_x][coord_y].defenseur.prix;
                carte[coord_x][coord_y] == choix_defenseur + 10;
        }
}

void lancerpartie() {
    srand(time(NULL));
    int taillecarte;
    int colonneCouronne, colonneDebut;
    int flocons=120;
    EnnemiActif* ennemis=NULL;
    int nbEnnemis=0;
    int compteur=0, vague=0;
    int score=0; // Initialisation du score

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

    generer_attaquant(carte, colonneDebut, &ennemis, &nbEnnemis, &compteur);
    afficher_carte(carte, taillecarte);
	
	for(vague; vague<16; vague++){
		compteur=0;
		while (carte[taillecarte-1][colonneCouronne].type==7){
		    usleep(500000); // Pause

		    deplacement_attaquant(carte, ennemis, nbEnnemis, taillecarte);

		    // Vérifier si un ennemi atteint la couronne
		    for (int i = 0; i < nbEnnemis; i++) {
		        if (ennemis[i].x == taillecarte - 1 && ennemis[i].y == colonneCouronne) {
		            defaite(&score);
        			// Libérer mémoire proprement avant de quitter
        			free(ennemis);
        			for (int k = 0; k < taillecarte; k++) free(carte[k]);
        			free(carte);
        			return;
		        }
		    }

		    // Génère un nouvel attaquant seulement si la case est vide
		    if (carte[0][colonneDebut].type == 6 && compteur<=8){
		        generer_attaquant(carte, colonneDebut, &ennemis, &nbEnnemis, &compteur);
		    }
		    afficher_carte(carte, taillecarte);
		}
		printf("\n \tScore=%d\n", score);
		sleep(2);
	}
	victoire(&score);
    // Libération de la mémoire
    free(ennemis);
    for (int i = 0; i < taillecarte; i++) {
        free(carte[i]);
    }
    free(carte);
}
