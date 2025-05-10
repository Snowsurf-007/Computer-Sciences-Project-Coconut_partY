void placement_de_defenseur(Case** carte, int taillecarte, int* monnaie, Defenseur* liste_defenseur, int* nb_defenseur) {
    int placer=-1;
    int choix_defenseur=0;
    char coord_x_char;
    int coord_x_index=0;
    int coord_y=0;
    Defenseur nouv_def;

    printf("Souhaitez-vous placer un défenseur ?\n1 pour oui ou 0 pour non\n");
    scanf("%d", &placer);

    while (placer!=0 && placer!=1) {
        printf("Valeur incorrecte. Veuillez entrer 1 pour oui ou 0 pour non :\n");
        scanf("%d", &placer);
    }

    while (placer==1) {
        printf("Choisissez le défenseur à placer :\n1 - Pingu-Patrouilleur(100 flocons)\n2 - Flocon-Perce-Ciel(200 flocons)\n3 - Garde Polaire(150 flocons)\n");
        scanf("%d", &choix_defenseur);

        while (choix_defenseur<1 || choix_defenseur>=4) {
            printf("Valeur incorrecte. Veuillez réessayer :\n");
            scanf("%d", &choix_defenseur);
        }

        if (choix_defenseur==1)
            nouv_def=constructeur_PinguPatrouilleur(nouv_def);
        else if (choix_defenseur==2)
            nouv_def=constructeur_FloconPerceCiel(nouv_def);
        else
            nouv_def=constructeur_GardePolaire(nouv_def);

        while (*monnaie<nouv_def.prix){
            printf("Flocons insuffisants. Souhaitez-vous toujours placer un défenseur ?\n1 pour oui ou 0 pour non\n");
            printf("Choisissez le défenseur à placer :\n1 - Pingu-Patrouilleur(100 flocons)\n2 - Flocon-Perce-Ciel(200 flocons)\n3 - Garde Polaire(150 flocons)\n");
            scanf("%d", &placer);

            while (placer!=0 && placer!=1){
                printf("Valeur incorrecte. Réessayez :\n");
                scanf("%d", &placer);
            }

            if (placer==0){
                return;
            }

            printf("Choisissez un défenseur à placer :\n1 - Pingu-Patrouilleur\n2 - Flocon-Perce-Ciel\n3 - Garde Polaire\n");
            scanf("%d", &choix_defenseur);
        }

        do{
            // Lecture de la coordonnée X (lettre)
            do{
                printf("Choisissez une coordonnée x (lettre a-%c) :\n", 'A'+taillecarte-27);
                scanf(" %c", &coord_x_char);

                if (coord_x_char>='a' && coord_x_char<='z'){
                    coord_x_index=coord_x_char-'a';
                }
                else if (coord_x_char>='A' && coord_x_char<='Z'){
                    coord_x_index=coord_x_char-'A';
                }
                while((coord_x_char<'a' || coord_x_char>'z') && (coord_x_char<'A' || coord_x_char>'Z')){
                    printf("Lettre invalide, Réessayez.\n");
                }
            }while((coord_x_char<'a' || coord_x_char>'z') && (coord_x_char<'A' || coord_x_char>'Z'));

            // Lecture de la coordonnée Y (entier)
            do{
                printf("Choisissez une coordonnée y (entre 0 et %d) :\n", taillecarte);
                scanf("%d", &coord_y);
                coord_y=coord_y-1;//index de tableau (0 à taille-1 au lieu de 1 à taille)
                if (coord_y<0 || coord_y>=taillecarte){
                    printf("Coordonnée y invalide, Réessayez.\n");
                }
            }while(coord_y<0 || coord_y>=taillecarte);

            // Vérification case valide pour un défenseur
            printf("DEBUG: type case = %d\n", carte[coord_x_index][coord_y].type);
            if (carte[coord_x_index][coord_y].type!=0){
                printf("Cette case ne contient pas de neige. Choisissez une autre case.\n");
            }
        }while(carte[coord_x_index][coord_y].type!=0);
        
        // Placement du défenseur
        carte[coord_x_index][coord_y].type=choix_defenseur+10;
        carte[coord_x_index][coord_y].defenseur=nouv_def;
        *monnaie-=nouv_def.prix;
        liste_defenseur[*nb_defenseur]=nouv_def;
        (*nb_defenseur)++;

        // Nouvelle demande de placement
        printf("Souhaitez-vous placer un autre défenseur ?\n1 pour oui ou 0 pour non\n");
        scanf("%d", &placer);

        while (placer!=0 && placer!=1) {
            printf("Valeur incorrecte. Réessayez :\n");
            scanf("%d", &placer);
        }
    }
}
