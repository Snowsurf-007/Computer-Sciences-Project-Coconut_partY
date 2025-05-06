void menuDemarrage() {
	int choix_menu=0;  //choix + vérification de la valeur entrée au clavier 

	printf("\n=== MENU PRINCIPAL ===\n");
	printf("\n \t Nouvelle Partie (1) \t \n");
	printf("\n \t Reprendre (2) \t \n");
	printf("\n \t Quitter (3) \t \n");
	printf("Votre choix : ");
	scanf("%d",&choix_menu);
		
	while(choix_menu<1 || choix_menu>3) {
		
		printf("\n Veuillez entrer une valeur correcte : \n");
		printf("1 pour démarrer une nouvelle partie \n");
		printf("2 pour reprendre la dernière partie \n");
		printf("3 pour quitter le jeu \n");
			
		printf("\n \t Nouvelle Partie (1) \t \n");
		printf("\n \t Reprendre (2) \t \n");
		printf("\n \t Quitter (3) \t \n");
			
		scanf("%d",&choix_menu);
	}
		
	//application du choix fait par l'utilisateur 
	if(choix_menu==1) {
		lancer_partie();
	}
	else if(choix_menu==2) {
		reprendrePartie();
	}
	else if(choix_menu==3) {
		printf("A plus 👋😊\n");
		exit(0);
	}
	else {
		printf("Erreur : Le choix n'a pas pu être pris en compte \n");
		printf("Veuillez relancer \n");
		exit(1);
	}
}
