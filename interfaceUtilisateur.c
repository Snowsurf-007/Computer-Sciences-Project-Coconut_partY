#include"interfaceUtilisateur.h"

void menuDemarrage() {
	int choix_menu=0;  //choix + vérification de la valeur entrée au clavier 

	printf("\n=== MENU PRINCIPAL ===\n");
	printf("\n \t Nouvelle Partie (1) \t \n");
	printf("\n \t Reprendre (2) \t \n");
	printf("\n \t Quitter (3) \t \n");
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
		lancer_partie();
	}
	else if(choix_menu==2) {
		reprendrePartie();
	}
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

void afficher_carte(int **carte, int taillecarte) {
    printf("\nPour cette partie, la carte est de taille %d x %d\n", taillecarte, taillecarte); // On affiche la taille de la carte
    sleep(2); // On fait une pause de deux secondes pour laisser le temps de lire
    printf("La carte est en cours de création...\n");
    sleep(2); // On fait une pause de deux secondes pour laisser le temps de lire
    printf("Voici la carte :\n\n");
    sleep(1); // On fait une pause d'une seconde pour laisser le temps de lire
    
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
    		switch (carte[i][j]){
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
            			printf("%s", EMOJI_SKIEUR);
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

void creer_carte(int **carte, int taillecarte) {
    for (int i=0; i<taillecarte; i++){
        carte[i]=(int*)malloc(taillecarte*sizeof(int));
        if (carte[i]==NULL) {
            printf("Erreur d'allocation mémoire\n");
            exit(1); //Terminer le programme si l'allocation échoue
        }
        for (int j=0; j<taillecarte; j++){
            carte[i][j]=rand()%6; //Remplir la carte avec des valeurs aléatoires
        }
    }
}

void creer_chemin(int **carte, int taillecarte){
    int j=rand()%(taillecarte-6)+3; //Colonne de départ
    int direction, directionprecedente;
    
    // Premier mouvement, on va tout droit (vers le bas)
    direction=0;
    carte[0][j]=6; // Placement du drapeau sur la premiere case
    carte[1][j]=6; // Placement du drapeau sur la deuxieme case
    
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
            carte[i-1][nouvellecolonne]=6;
        }

        //Mise à jour de la position j
        j=nouvellecolonne;

        //On place le drapeau sur la case actuelle
        carte[i][j]=6;
    }
    //On place la couronne sur la derniere case en allant tout droit (vers le bas)
	carte[taillecarte-1][j]=7;
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

void lancerpartie (){
    srand(time(NULL));
    int taillecarte; //Variable pour la taille de la carte
	int colonneCouronne;	
	
    // On génère une taille de carte aléatoire entre 35 et 50
    taillecarte=rand()%16+35;

    int **carte=(int**)malloc(taillecarte*sizeof(int*)); //Allocation dynamique de la mémoire pour la carte
    
    creer_carte(carte, taillecarte);
    colonneCouronne=creer_chemin(carte, taillecarte);
    afficher_carte(carte, taillecarte);
    placement_de_defenseur(Case carte[]);

    while(carte[taillecarte-1][colonneCouronne]==12){
        sleep(1);
        deplacement_attaquant();
        generer_attaquant();
        afficher_carte(carte, taillecarte);
        attaque_defenseurs();
        placement_de_defenseur(Case carte[]);
        amelioration();
    }
    
    //On libère la mémoire allouée pour la carte
    for (int i=0; i<taillecarte; i++) {
    free(carte[i]);
    }
    free(carte);
    return 0;
}
