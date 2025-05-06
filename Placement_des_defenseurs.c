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
