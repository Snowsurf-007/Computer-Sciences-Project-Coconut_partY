void defaite(){
	int choix=0;
	do{ 
		printf("== Vous avez perdu ! ==\n");
		printf("Taper 1 pour relancer une partie\n");
		printf("Taper 2 pour quitter\n");
		printf("\nVotre choix : ");
		scanf("%d", &choix);
	}while(choix!=1 && choix!=2);
	
	if(choix==1){
		Lancer_partie();
	}
	else if(choix==2){
		printf("A plus 👋😊\n");
		exit(0);
	}
}
