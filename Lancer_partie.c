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
		    usleep(400000); // Pause

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
