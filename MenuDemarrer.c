#include<stdio.h>
#include<stdlib.h>

	
	void menuDemarrage() {
	
		int choix_menu=0;  //choix + vérification de la valeur entrée au clavier 
		
		printf("\n \t Nouvelle Partie (1) \t \n");
		printf("\n \t Charger Sauvegarde (2) \t \n");
		printf("\n \t Quitter (3) \t \n");
		
		scanf("%d",&choix_menu);
		
		while(choix_menu<1 || choix_menu>3) {
		
			printf("\n Veuillez entrer une valeur correcte : \n");
			printf("1 pour démarrer une nouvelle partie \n");
			printf("2 pour charger une sauvegarde \n");
			printf("3 pour quitter le jeu \n");
			
			printf("\n \t Nouvelle Partie (1) \t \n");
			printf("\n \t Charger Sauvegarde (2) \t \n");
			printf("\n \t Quitter (3) \t \n");
			
			scanf("%d",&choix_menu);
		}
		
		//application du choix fait par l'utilisateur 
		if(choix_menu==1) {
		
			nouvellePartie;
		}
		
		else if(choix_menu==2) {
		
			chargerSauvegarde;
		}
		
		else if(choix_menu==3) {
		
			quitter;
		}
		
		else {
		
			printf("Erreur : Le choix n'a pas pu être pris en compte \n");
			printf("Veuillez relancer \n");
			exit(1);
		}
	
	
	}	












































