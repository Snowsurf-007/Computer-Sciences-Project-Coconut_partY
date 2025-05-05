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
        	printf(" %c ", 'a'+i);// minuscules jusqu'à 26
    	}
    	else{
    		printf(" %c ", 'A'+(i-26));// majuscules après
    	}
    }
    printf("\n");
    printf("    ");
    for (int i=0; i<taillecarte; i++){
        printf(" _ ");
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
        		case 4:
        		case 5:
        		case 6:
           			printf("%s  ", EMOJI_NEIGE);
            			break;

        		case 7:
        		case 8:
            			printf("%s ", EMOJI_PIERRE);
            			break;

        		case 9:
        		case 10:
            			printf("%s ", EMOJI_SAPIN);
           			break;

        		case 11:
         			printf("%s ", EMOJI_DRAPEAU);
            			break;

        		case 12:
            			printf("%s ", EMOJI_COURONNE);
            			break;
            			
            		case 13:
            			printf("%s ", EMOJI_SKIEUR);
            			break;
            			
            		case 14:
            			printf("%s ", EMOJI_SNOWBOARDER);
            			break;
            			
            		case 15:
            			printf("%s ", EMOJI_LUGISTE);
            			break;

        		default:
            			exit(5);
    		}
    	}
    printf("|\n");
    }
    printf("    ");
    for (int i=0; i<taillecarte; i++){
        printf(" ‾ ");
    }
    printf("\n");
    printf("\nLégende :\n");
	printf("%s : Neige   ", EMOJI_NEIGE);
	printf("%s : Pierre   ", EMOJI_PIERRE);
	printf("%s : Sapin   ", EMOJI_SAPIN);
	printf("%s : Drapeau (chemin)   ", EMOJI_DRAPEAU);
	printf("%s : Couronne (arrivée)\n", EMOJI_COURONNE);
}

void creer_carte(int **carte, int taillecarte) {
    for (int i=0; i<taillecarte; i++){
        carte[i]=(int*)malloc(taillecarte*sizeof(int));
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
    int direction, directionprecedente;
    
    // Premier mouvement, on va tout droit (vers le bas)
    direction=0;
    carte[0][j]=11; // Placement du drapeau sur la premiere case
    carte[1][j]=11; // Placement du drapeau sur la deuxieme case
    
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
            carte[i-1][nouvellecolonne]=11;
        }

        //Mise à jour de la position j
        j=nouvellecolonne;

        //On place le drapeau sur la case actuelle
        carte[i][j]=11;
    }
    //On place la couronne sur la derniere case en allant tout droit (vers le bas)
	carte[taillecarte-1][j]=12;
}

int main (){
    srand(time(NULL));
    int taillecarte; //Variable pour la taille de la carte

    // On génère une taille de carte aléatoire entre 30 et 40
    taillecarte=rand()%11+40;

    int **carte=(int**)malloc(taillecarte*sizeof(int*)); //Allocation dynamique de la mémoire pour la carte
    
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
    free(carte);
    return 0;
}
