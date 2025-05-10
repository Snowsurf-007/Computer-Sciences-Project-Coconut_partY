int menuDemarrage(){
    int choix_menu=0; //Variable pour stocker le choix de l'utilisateur
    
    printf("\n \t=== %s%s%s OPERATION FLOCON %s %s%s === \n", EMOJI_PINGOUIN, EMOJI_BONHOMMENEIGE, EMOJI_OURS, EMOJI_SKIEUR, EMOJI_SNOWBOARDER, EMOJI_LUGISTE);

    printf("\n \t=== MENU PRINCIPAL === \n");
    printf("\n \t Nouvelle Partie (1) \t \n");
    printf("\n \t Reprendre une partie (2) \t \n");
    printf("\n \t Quitter (3) \t \n\n");
    printf("Votre choix : ");
    scanf("%d", &choix_menu);

    while (choix_menu<1 || choix_menu>3) {
        printf("\n Veuillez entrer une valeur correcte : \n");
        printf("1 pour démarrer une nouvelle partie \n");
        printf("2 pour reprendre une ancienne partie \n");
        printf("3 pour quitter le jeu \n");
        printf("Votre choix : ");
        scanf("%d", &choix_menu);
    }
    return choix_menu; // Retourne le choix de l'utilisateur
}
