void lancerpartie (){
	srand(time(NULL));
    	int taillecarte; //Variable pour la taille de la carte
    	int colonneCouronne, colonneDebut;
	int flocons=120;
	EnnemiActif* ennemis=NULL;
	int nbEnnemis=0;


    	// On génère une taille de carte aléatoire entre 25 et 40
    	taillecarte=rand()%16+25;

    	Case** carte=(Case**)malloc(taillecarte*sizeof(Case*)); //Allocation dynamique de la mémoire pour la carte
    
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
    	
	while (carte[taillecarte-1][colonneCouronne].type==7) {
		usleep(500000);  // pause

    		deplacement_attaquant(carte, ennemis, nbEnnemis, taillecarte);

    		// Génère un nouvel attaquant seulement si la case est vide
    		if (carte[0][colonneDebut].type==6){
        		generer_attaquant(carte, colonneDebut, &ennemis, &nbEnnemis);
    		}

    		afficher_carte(carte, taillecarte);
    		//attaque_defenseurs();
        	//placement_de_defenseur(Case carte[], flocons);
        	//amelioration(flocons);
	}
    	
	// Libération de la mémoire pour les ennemis
	free(ennemis);
    	//On libère la mémoire allouée pour la carte
    	for (int i=0; i<taillecarte; i++){
		free(carte[i]);
    	}
    	free(carte);
	return 0;
}
