void lancerpartie (){
	srand(time(NULL));
	int taillecarte; //Variable pour la taille de la carte
	int colonneCouronne;
	int flocons=120;
	
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
        	placement_de_defenseur(Case carte[], flocons);
        	amelioration(flocons);
    	}
    
    	//On libère la mémoire allouée pour la carte
    	for (int i=0; i<taillecarte; i++) {
    		free(carte[i]);
   	}
    	free(carte);
}
