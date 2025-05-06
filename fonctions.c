void placement_de_defenseur(int carte[][], int taillecarte, int monnaie, Defenseur liste_defenseur[], int nb_defenseur){
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
                Defenseur nouv_def;
                }
                if(choix_defenseur == 1){
                        nouv_def = constructeur_PinguPatrouilleur(nouv_def, coord_x, coord_y);
                }
                else if(choix_defenseur == 2){
                        nouv_def = constructeur_FloconPerceCiel(nouv_def, coord_x, coord_y);
                }
                else if(choix_defenseur == 3){
                        nouv_def = constructeur_GardePolaire(nouv_def, coord_x, coord_y);
                }
                else{
                        exit(1)
                }
                while(monnaie < nouv_def.prix){
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
                monnaie -= nouv_def.prix;
                liste_defenseur[nb_defenseur] = nouv_def;
                nb_defenseur += 1;
        }
}



void amelioration(int carte[][], int taillecarte, int monnaie, Defenseur liste_defenseur[], int nb_defenseur[]){
  
//choix de l'amélioration d'un défenseur
      
        int placer = -1;
        int coord_x = 0;
        int coord_y = 0;
        printf("A présent, souhaitez vous améliorer un défenseur ?\n1 pour oui, 0 pour non\n");
        scanf("%d", &placer);
        
        while(placer != 0 || placer != 1){
                printf("La valeur entrée est incorrecte, veuillez réessayer.\n");
                scanf("%d", &placer);
        }
        while(placer == 1){
                printf("Veuillez insérer la coordonnée x du défenseur a améliorer\n");
                scanf("%d", &coord_x);
          
                while(coord_x > taillecarte || coord_x < 0){
                        printf("La valeur entrée est incorrecte veuillez réessayer.\n");
                        printf("Veuillez insérer la coordonnée x du défenseur a améliorer\n");
                        scanf("%d", &coord_x);
                }
                printf("Veuillez maintenant choisir la coordonnée y.\n");
                scanf("%d", &coord_y);
          
                while(coord_y > taillecarte || coord_y < 0){
                        printf("La valeur entrée est incorrecte veuillez réessayer.\n");
                        printf("Veuillez maintenant choisir la coordonnées y.\n");
                        scanf("%d", &coord_y);
                }
                while(carte[coord_x][coord_y] != 11 || carte[coord_x][coord_y] != 12 || carte[coord_x][coord_y] != 13){ //tant que la case n'est pas occupée par un défenseur
                        printf("Il n'y a pas de défenseur a améliorer sur cette case veuillez en choisir une autre.\n");
                        printf("Veuillez insérer la coordonnée x du défenseur a améliorer\n");
                        scanf("%d", &coord_x);
                  
                        while(coord_x > taillecarte || coord_x < 0){
                                printf("La valeur entrée est incorrecte veuillez réessayer.\n");
                                printf("Veuillez insérer la coordonnée x du défenseur a améliorer\n");
                                scanf("%d", &coord_x);
                        }
                        printf("Veuillez maintenant choisir la coordonnée y.\n");
                        scanf("%d", &coord_y);
                  
                        while(coord_y > taillecarte || coord_y < 0){
                                printf("La valeur entrée est incorrecte veuillez réessayer.\n");
                                printf("Veuillez maintenant choisir la coordonnées y.\n");
                                scanf("%d", &coord_y);
                        }
        
                }
                Defenseur defenseur_a_ameliorer;
                for(int i = 0; i<nb_defenseur; i++){
                        if(liste_defenseur[i].coordx == coord_x){
                                if(liste_defenseur[i].coordy == coord_y){
                                        defenseur_a_ameliorer = liste_defenseur[i];
                                }
                        }
                        
                }
                while(defenseur_a_ameliorer.niveau*10 > monnaie){ //prix a modifier si besoin (le prix est le niveau du defenseur fois 10)
                  
                        if(placer == 0){
                          break;
                        }
                        printf("Vous n'avez pas assez d'argent, souhaitez vous toujours améliorer ?\n1 pour oui, 0 pour non\n");
                        scanf("%d", &placer);
        
                        while(placer != 0 || placer != 1){
                                printf("La valeur entrée est incorrecte, veuillez réessayer.\n");
                                scanf("%d", &placer);
                        }
                        
                        printf("Veuillez insérer la coordonnée x du défenseur a améliorer\n");
                        scanf("%d", &coord_x);
                        while(coord_x > taillecarte || coord_x < 0){
                                printf("La valeur entrée est incorrecte veuillez réessayer.\n");
                                printf("Veuillez insérer la coordonnée x du défenseur a améliorer\n");
                                scanf("%d", &coord_x);
                        }
                        printf("Veuillez maintenant choisir la coordonnée y.\n");
                        scanf("%d", &coord_y);
                        while(coord_y > taillecarte || coord_y < 0){
                                printf("La valeur entrée est incorrecte veuillez réessayer.\n");
                                printf("Veuillez maintenant choisir la coordonnées y.\n");
                                scanf("%d", &coord_y);
                        }
                        while(arte[coord_x][coord_y] != 11 || carte[coord_x][coord_y] != 12 || carte[coord_x][coord_y] != 13){ //tant que la case n'est pas occupée par un défenseur
                                printf("Il n'y a pas de défenseur a améliorer sur cette case veuillez en choisir une autre.\n");
                                printf("Veuillez insérer la coordonnée x du défenseur a améliorer\n");
                                scanf("%d", &coord_x);
                                while(coord_x > taillecarte || coord_x < 0){
                                        printf("La valeur entrée est incorrecte veuillez réessayer.\n");
                                        printf("Veuillez insérer la coordonnée x du défenseur a améliorer\n");
                                        scanf("%d", &coord_x);
                                }
                                printf("Veuillez maintenant choisir la coordonnée y.\n");
                                scanf("%d", &coord_y);
                                while(coord_y > taillecarte || coord_y < 0){
                                        printf("La valeur entrée est incorrecte veuillez réessayer.\n");
                                        printf("Veuillez maintenant choisir la coordonnées y.\n");
                                        scanf("%d", &coord_y);
                                }
        
                        }
                }
                monnaie -= defenseur_a_ameliorer.niveau*10;
                defenseur_a_ameliorer.niveau += 1; //le défenseur a été amélioré
        }  
}



int generer_attaquant(Case carte[], Attaquant liste_attaquant[], int nb_attaquant){
  //avancee_vague représente ou on en est dans une vague tandis que numero vague est pour savoir a quelle vague on en est cela donnera donc vague[numero_vague][avancee_vague] pour generer un ennemi
  
  if(rand()%4) == 0){ //une chance sur 4 qu'un ennemi apparaisse
        nb_attaquant+=1;
        Attaquant nouv_ennemi;
        int difficulte = rand() % 6;
        if(difficulte == 0 || difficulte == 1 || difficulte == 2){
                constructeur_SkieurFrenetique(nouv_ennemi);
        }
        else if(difficulte == 3 || difficulte == 4){
                constructeur_SnowboarderAcrobate(nouv_ennemi);
        }
        else if(difficulte == 5){
                constructeur_LugisteBarjo(nouv_ennemi);
        }
        liste_attaquant[nb_attaquant]=nouv_ennemi;
        }
        return nb_attaquant;
}



void deplacement_attaquant(int** carte, int i, int j) {
				
		if(carte[i][j+1]==8 || carte[i][j+1]==9 || carte[i][j+1]==10) {
			carte[i][j]=carte[i][j+1];
			carte[i][j+1]=6;
			deplacement_attaquant(carte,i,j+1);
		}	
		else if(carte[i][j-1]==8 || carte[i][j-1]==9 || carte[i][j-1]==10) {
			carte[i][j]=carte[i][j-1];
			carte[i][j-1]=6;
			deplacement_attaquant(carte,i,j-1);
		}	
		else if(i<1) {//deuxieme condition d'arrêt	
		}
		else if(carte[i-1][j]==8 || carte[i-1][j]==9 || carte[i-1][j]==10){
			carte[i][j]=carte[i-1][j];
			carte[i-1][j]=6;
			deplacement_attaquant(carte,i-1,j);
		}
		else{
			printf("erreur : deplacement attaquant");
		}
}

/*	while(taillecarte>0) {
		if(carte[taillecarte-2][j]==13 || carte[taillecarte-2][j]==14 || carte[taillecarte-2][j]==15) {				
			carte[taillecarte-1][j]=carte[taillecarte-2][j];		
	}
			
			else if(carte[taillecarte-2][j-1]==13 || carte[taillecarte-2][j-1]==14 || carte[taillecarte-2][j-1]==15) {
				carte[taillecarte-1][j-1]=carte[taillecarte-2][j];
			j--;	
			}
			
			else if(carte[taillecarte-2][j+1]==13 || carte[taillecarte-2][j+1]==14 || carte[taillecarte-2][j+1]==15) {
			
				carte[taillecarte-1][j+1]=carte[taillecarte-2][j];
			j++;	
			}
			
			
			
		
		
		taillecarte--;
		}*/
