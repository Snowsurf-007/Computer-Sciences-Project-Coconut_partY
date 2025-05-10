void lancerpartie(Case*** carte, int* taillecarte, Defenseur** defenseurs, int* nbDefenseurs, EnnemiActif** ennemis, int* nbEnnemis, int* score, int* monnaie, int* vague) {
    int colonneCouronne, colonneDebut;
    int compteur=0;
    
    *taillecarte=rand()%19+27; //aléatoire entre 27 et 45
    creer_carte(carte, *taillecarte);
    creer_chemin(*carte, *taillecarte);
    
    printf("\nPour cette partie, la carte est de taille %d x %d\n", *taillecarte, *taillecarte);
    afficher_carte(*carte, *taillecarte);

    for (int i=0; i<*taillecarte; i++) {
        if ((*carte)[0][i].type==6) {
            colonneDebut=i;
            break;
        }
    }
    for (int j=0; j<*taillecarte; j++) {
        if ((*carte)[*taillecarte-1][j].type==7) {
            colonneCouronne=j;
            break;
        }
    }

    generer_attaquant(*carte, colonneDebut, ennemis, nbEnnemis, &compteur);
    afficher_carte(*carte, *taillecarte);
	
	for((*vague); (*vague)<16; (*vague)++){
	    printf("\n \tScore = %d\n", *score);
	    printf("\n \tFlocons = %d\n\n", *monnaie);
		compteur=0;
		placement_de_defenseur(*carte, *taillecarte, monnaie, *defenseurs, nbDefenseurs);
		afficher_carte(*carte, *taillecarte);
		while ((*carte)[*taillecarte-1][colonneCouronne].type==7){
		    usleep(400000); // Pause

		    deplacement_attaquant(*carte, *ennemis, *nbEnnemis, *taillecarte);

		    // Vérifier si un ennemi atteint la couronne
		    for (int i=0; i<*nbEnnemis; i++) {
                if ((*ennemis)[i].x==*taillecarte-1 && (*ennemis)[i].y==colonneCouronne) {
		            defaite(score);
        			// Libérer mémoire proprement avant de quitter
        			free(*ennemis);
        			for (int k=0; k<*taillecarte; k++){
						free((*carte)[k]);
					}
        			free(*carte);
        			return;
		        }
		    }

		    // Génère un nouvel attaquant seulement si la case est vide
		    if ((*carte)[0][colonneDebut].type==6 && compteur<=8){
		        generer_attaquant(*carte, colonneDebut, ennemis, nbEnnemis, &compteur);
		    }
		    afficher_carte(*carte, *taillecarte);
		}
		printf("\n \tScore=%d\n", *score);
		sleep(2);
	}
	victoire(score);
    // Libération de la mémoire
    free(*ennemis);
    for (int i = 0; i<*taillecarte; i++) {
        free((*carte)[i]);
    }
    free(*carte);
}
