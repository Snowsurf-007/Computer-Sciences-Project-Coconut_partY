void creer_chemin(Case** carte, int taillecarte){
    int j=rand()%(taillecarte-6)+3;
    int direction, directionprecedente=0;

    carte[0][j].type=6;
    carte[1][j].type=6;

    for (int i=2; i<taillecarte-1; i++) {
        do {
            direction=rand()%3-1;
        }while (directionprecedente==-direction);

        directionprecedente=direction;
        int nouvellecolonne=j+direction;

        if (nouvellecolonne<0){
            nouvellecolonne=0;
        }
        if (nouvellecolonne>=taillecarte){
            nouvellecolonne=taillecarte-1;
        }
        if (direction!=0 && i>0) {
            carte[i-1][nouvellecolonne].type=6;
        }

        j = nouvellecolonne;
        carte[i][j].type=6;
    }
    carte[taillecarte-1][j].type=7;
}
