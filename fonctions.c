#include "biblio.h"

Defenseur constructeur_PinguPatrouilleur(Defenseur a){
    a.portee=10;
    a.degats=50;
    a.prix=100;
    return a;
}

Defenseur constructeur_FloconPerceCiel(Defenseur a){
    a.portee=15;
    a.degats=30;
    a.prix=200;
    return a;
}

Defenseur constructeur_GardePolaire(Defenseur a){
    a.portee=6;
    a.degats=100;
    a.prix=150;
    return a;
}

Attaquant constructeur_SkieurFrenetique(Attaquant a){ //attaquant rapide et faible, petit taux d'esquive 
    a.vie=250;
    a.esquive=0.15;
    return a;
}

Attaquant constructeur_SnowboarderAcrobate(Attaquant a){ //attaquant vitesse moyenne, vie moyenne mais bonne esquive
    a.vie=500;
    a.esquive=0.30;
    return a;
}

Attaquant constructeur_LugisteBarjo(Attaquant a){ //attaquant lent et resistant
    a.vie=2000;
    a.esquive=0.01;
    return a;
}

void nettoyer_cache() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF); // Nettoyer le buffer
    // Cela consommera tous les caractères jusqu'à ce qu'une nouvelle ligne ou une fin de fichier (EOF) soit trouvée.
}

// Fonction pour calculer la distance de manhattan entre deux unités
int calculerDistance(int x1, int y1, int x2, int y2) {
    int dis = 0;
    int disx = (x2 - x1);
    int disy = (y2 - y1);
    if (disx < 0) {
        disx = -disx;
    }
    if (disy < 0) {
        disy = -disy;
    }
    dis = disx + disy;
    return dis;
}

void attaquer_defenseurs(Case** carte, Defenseur* defenseurs, int* nbDefenseurs, EnnemiActif* ennemis, int* nbEnnemis, int* score) {
    for (int i = 0; i < *nbDefenseurs; i++) {
        Defenseur* def = &defenseurs[i]; // Pointeur vers le défenseur actuel
        for (int j = 0; j < *nbEnnemis; j++) {
            EnnemiActif* ennemi = &ennemis[j]; // Ennemi actuel

            if (ennemi->attaquant.vie <= 0) {
                printf("DEBUG3\n");
                continue;
            }

            // Calcul de la distance entre le défenseur et l'ennemi
            // Calcul de la distance entre le défenseur et l'ennemi
            float distance = calculerDistance(def->coordx, def->coordy, ennemi->x, ennemi->y);

            // Si l'ennemi est à portée
            if (distance <= def->portee) {
                //printf("  Ennemi %d est à portée du défenseur %d.\n", j, i);
                // Applique les dégâts en fonction de l'esquive
               
                if ((rand() % 99 +1) / 100.0 > ennemi->attaquant.esquive) {
                    
                    ennemi->attaquant.vie -= def->degats;
                    // Si l'ennemi est éliminé
                    if (ennemi->attaquant.vie <= 0) {
                        int x1 = ennemi->x;
                        int y1 = ennemi->y;
                        carte[x1][y1].type = 6; // Remet la case à "chemin"
                        (*score)++; // Incrémente le score

                        // Supprime l'ennemi de la liste
                        for (int k = j; k < *nbEnnemis - 1; k++) {
                            ennemis[k] = ennemis[k + 1];
                        }
                        (*nbEnnemis)--; // Réduit le nombre d'ennemis
                        j--; // Réajuste l'indice pour ne pas sauter un ennemi
                    }
                } 
            }
        }
    }
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

void deplacement_attaquant(Case** carte, EnnemiActif* ennemis, int nbEnnemis, int taillecarte) {
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

void generer_attaquant(Case** carte, int debut, EnnemiActif** ennemis, int* nbEnnemis, int* compteur, int* vague) {
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
        printf("\t Erreur : le fichier %s n'existe pas \n", nom_fichier);    
        exit(3);
    }

    fscanf(fichier, "%d", taillecarte);

    *carte = (Case**)malloc(*taillecarte * sizeof(Case*));
    for (int i = 0; i < *taillecarte; i++) {
        (*carte)[i] = (Case*)malloc(*taillecarte * sizeof(Case));
    }

    for (int i = 0; i < *taillecarte; i++) {
        for (int j = 0; j < *taillecarte; j++) {
        		int type;
            fscanf(fichier, "%d", &type);
            (*carte)[i][j].type = (TypeCase)type;
        }
    }

    fscanf(fichier, "%d", nbDefenseurs);
    *defenseurs = (Defenseur*)malloc(*nbDefenseurs * sizeof(Defenseur));
    for (int i = 0; i < *nbDefenseurs; i++) {
        fscanf(fichier, "%d %d %f %d %d %d", &(*defenseurs)[i].portee, &(*defenseurs)[i].degats, &(*defenseurs)[i].vitessetir,&(*defenseurs)[i].prix, &(*defenseurs)[i].coordx, &(*defenseurs)[i].coordy);
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
        fprintf(fichier, "%d %d %f %d %d %d\n", defenseurs[i].portee, defenseurs[i].degats, defenseurs[i].vitessetir, defenseurs[i].prix, defenseurs[i].coordx, defenseurs[i].coordy);
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
