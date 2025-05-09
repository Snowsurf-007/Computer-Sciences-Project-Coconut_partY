void amelioration(Case carte[], int taillecarte){
  
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
                while(carte[coord_x][coord_y].type != 11 || carte[coord_x][coord_y].type != 12 || carte[coord_x][coord_y].type != 13){ //tant que la case n'est pas occupée par un défenseur
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
                while(carte[coord_x][coord_y].defenseur.niveau*10 > monnaie){ //prix a modifier si besoin (le prix est le niveau du defenseur fois 10)
                  
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
                        while(carte[coord_x][coord_y].type != 11 || carte[coord_x][coord_y].type != 12 || carte[coord_x][coord_y].type != 13){ //tant que la case n'est pas occupée par un défenseur
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
                monnaie -= carte[coord_x][coord_y].defenseur.niveau*10;
                carte[coord_x][coord_y].defenseur.niveau += 1; //le défenseur a été amélioré
        }  
}
