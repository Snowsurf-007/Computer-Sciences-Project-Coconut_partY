#include "fonctions.h"
Defenseur constructeur_PinguPatrouilleur(Defenseur a){
        a.portee=5;
        a.degats=30;
        a.vitessetir=0.5;
        a.prix=100;
        return a;
}

Defenseur constructeur_FloconPerceCiel(Defenseur a){
        a.portee=10;
        a.degats=300;
        a.vitessetir=2;
        a.prix=200;
        return a;
}

Defenseur constructeur_GardePolaire(Defenseur a){
        a.portee=2;
        a.degats=70;
        a.vitessetir=1;
        a.prix=150;
        return a;
}

Attaquant constructeur_SkieurFrenetique(Attaquant a){ //attaquant rapide et faible, petit taux d'esquive 
        a.vie=250;
        a.esquive=0.15;
        a.gain=20;
        return a;
}

Attaquant constructeur_SnowboarderAcrobate(Attaquant a){ //attaquant vitesse moyenne, vie moyenne mais bonne esquive
        a.vie=500;
        a.esquive=0.30;
        a.gain=30;
        return a;
}

Attaquant constructeur_LugisteBarjo(Attaquant a){ //attaquant lent et resistant
        a.vie=2000;
        a.esquive=0;
        a.gain=50;
        return a;
}

void defaite(int* score) {
    printf("\n \t== Vous avez perdu ! ==\n");
    printf("\n \tScore=%d\n", *score);
    sleep(2);
    printf("\nRetour au menu principal...\n");
    sleep(2);
}

void victoire(int* score) {
    printf("\n \t== Vous avez gagné ! ==\n");
    printf("\n \tScore=%d\n", *score);
    sleep(2);
    printf("\nRetour au menu principal...\n");
    sleep(2);
}

void placement_de_defenseur(Case** carte, int taillecarte, int monnaie){
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

		//choix du defenseur
		printf("choisissez le défenseur à placer :\n 1 pour le Pingu-Patrouilleur\n");
		printf("2 pour le Flocon_Perce-Ciel\n3 pour le garde polaire\n");
		scanf("%d", &choix_defenseur);
		
		while(choix_defenseur != 1 || choix_defenseur != 2 || choix_defenseur != 3){
			printf("La valeur entrée est incorrecte, veuillez réessayer.\n");
			scanf("%d", &choix_defenseur);
		}
                
                Defenseur nouv_def;
                if(choix_defenseur == 1){
                        nouv_def = constructeur_PinguPatrouilleur(nouv_def);
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
                if(monnaie < nouv_def.prix){
                        printf("monnaie insuffisante, souhaitez vous toujours placer un defenseur ?\n");
                        printf("1 pour oui ou 0 pour non\n");
                        scanf("%d", &placer);
                        
                        while(placer != 0 || placer != 1){
                                printf("La valeur entrée est incorrecte, veuillez réessayer.\n");
                                scanf("%d", &placer);
                        }
		}
                else{
			printf("Où souhaitez-vous placer le défenseur, choisissez une coordonnée x.\n");
	                scanf("%d", &coord_x);
	                if(coord_x > taillecarte || coord_x < 0){
	                        printf("La valeur entrée est incorrecte.\n");
				printf("souhaitez-vous toujours placer un défenseur ?\n1 pour oui ou 0 pour non\n");
			        scanf("%d", &placer);
			        
			        while(placer != 0 || placer != 1){
			                printf("La valeur entrée est incorrecte, veuillez réessayer.\n");
			                scanf("%d", &placer);
			        }
	                }
			else{
		                printf("Veuillez maintenant choisir la coordonnées y.\n");
		                scanf("%d", &coord_y)
		                if(coord_y > taillearte || coord_y < 0){
		                        printf("La valeur entrée est incorrecte.\n");
					printf("souhaitez-vous toujours placer un défenseur ?\n1 pour oui ou 0 pour non\n");
				        scanf("%d", &placer);
				        
				        while(placer != 0 || placer != 1){
				                printf("La valeur entrée est incorrecte, veuillez réessayer.\n");
				                scanf("%d", &placer);
				        }
		                }
				else{
			                if(carte[coord_x][coord_y].type != 0 || carte[coord_x][coord_y].type != 1 || carte[coord_x][coord_y].type != 2 || carte[coord_x][coord_y] != 3){ //la case doit etre une case avec de la neige
			                        printf("Impossible de mettre un defenseur sur cette case.\n");
			                        
						printf("souhaitez-vous toujours placer un défenseur ?\n1 pour oui ou 0 pour non\n");
						scanf("%d", &placer);
						
						while(placer != 0 || placer != 1){
							printf("La valeur entrée est incorrecte, veuillez réessayer.\n");
							scanf("%d", &placer);					                
						}
			                }
					else{ //selection réussie
				                carte[coord_x][coord_y].type == choix_defenseur + 10;
				                monnaie -= nouv_def.prix;
						carte[coord_x][coord_y].defenseur = nouv_def; //placement du defenseur
					}
				}
			}
		}
	}
}

int** chargement(const char* nom_fichier, int* ligne, int* colonne) {

    // Ouverture du fichier en mode lecture 
    FILE* fichier = fopen(nom_fichier, "r");
    // Vérification du bon déroulement de l'ouverture
    if(fichier == NULL) {
        printf("Erreur : le fichier %s n'a pas pu être ouvert \n", nom_fichier);
        exit(1);
    }

    else {
        fscanf(fichier,"%d %d", ligne, colonne); // Lecture des dimensions du tableau
        int** carte = malloc(*ligne * sizeof(int*)); // Allocation de mémoire pour le tableau
        for(int i = 0; i < *ligne; i++) {
            carte[i] = malloc(*colonne * sizeof(int)); // Allocation de mémoire pour chaque ligne
            for(int j = 0; j < *colonne; j++) {
                fscanf(fichier,"%d", &carte[i][j]); // Lecture de chaque élément du tableau
            }
        }
        return carte; // Retourne le tableau chargé
    }

    fclose(fichier); // Fermeture du fichier
    
}


//choix de la case ou placer le defenseur
		

void amelioration(Case** carte, int taillecarte, int monnaie){
  
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
          
                if(coord_x > taillecarte || coord_x < 0){
	                        printf("La valeur entrée est incorrecte.\n");
                          printf("souhaitez-vous toujours placer un défenseur ?\n1 pour oui ou 0 pour non\n");
                          scanf("%d", &placer);
                      
                          while(placer != 0 || placer != 1){
                                  printf("La valeur entrée est incorrecte, veuillez réessayer.\n");
                                  scanf("%d", &placer);
                          }
                }
                else{
                        printf("Veuillez maintenant choisir la coordonnées y.\n");
                        scanf("%d", &coord_y);
                        if(coord_y > taillecarte || coord_y < 0){
                                printf("La valeur entrée est incorrecte.\n");
                                printf("souhaitez-vous toujours placer un défenseur ?\n1 pour oui ou 0 pour non\n");
                                scanf("%d", &placer);
                            
                                while(placer != 0 || placer != 1){
                                        printf("La valeur entrée est incorrecte, veuillez réessayer.\n");
                                        scanf("%d", &placer);
                                }
                        }
                        else{
                                if(carte[coord_x][coord_y].type != 11 || carte[coord_x][coord_y].type != 12 || carte[coord_x][coord_y].type != 13){ //tant que la case n'est pas occupée par un défenseur
                                        printf("Il n'y a pas de défenseur a améliorer sur cette case.\n");
                                        printf("souhaitez-vous toujours placer un défenseur ?\n1 pour oui ou 0 pour non\n");
                                        scanf("%d", &placer);
                                    
                                        while(placer != 0 || placer != 1){
                                                printf("La valeur entrée est incorrecte, veuillez réessayer.\n");
                                                scanf("%d", &placer);
                                        }
                                }
                                else{
                                        if(carte[coord_x][coord_y].defenseur.niveau*10 > monnaie){ //prix a modifier si besoin (le prix est le niveau du defenseur fois 10)
                                          
                                                printf("Vous n'avez pas assez d'argent, souhaitez vous toujours améliorer ?\n1 pour oui, 0 pour non\n");
                                                scanf("%d", &placer);
                                
                                                while(placer != 0 || placer != 1){
                                                        printf("La valeur entrée est incorrecte, veuillez réessayer.\n");
                                                        scanf("%d", &placer);
                                                }
                                        }
                                        else{
                                                monnaie -= carte[coord_x][coord_y].defenseur.niveau*10;
                                                carte[coord_x][coord_y].defenseur.niveau += 1; //le défenseur a été amélioré
                                        }
                                }  
                        }
        	}
	}
}


void generer_attaquant(Case** carte, int debut, EnnemiActif** ennemis, int* nbEnnemis, int* compteur){
	int attaquant=rand()%3;
	Attaquant nouv_ennemi;

	if(attaquant==0){
		nouv_ennemi=constructeur_SkieurFrenetique(nouv_ennemi);
		carte[0][debut].type=8;
	}
	else if(attaquant==1){
		nouv_ennemi=constructeur_SnowboarderAcrobate(nouv_ennemi);
		carte[0][debut].type=9;
	}
	else if(attaquant==2){
		nouv_ennemi=constructeur_LugisteBarjo(nouv_ennemi);
		carte[0][debut].type=10;
	}
	// Ajouter l'ennemi au tableau dynamique
    	EnnemiActif* temp=(EnnemiActif*)realloc(*ennemis,(*nbEnnemis+1)*sizeof(EnnemiActif));
   	if (temp==NULL){
        	printf("Erreur d'allocation mémoire.\n");
        	free(*ennemis);
        	exit(1);
    	}
    	*ennemis=temp;
    	(*ennemis)[*nbEnnemis].attaquant=nouv_ennemi;
    	(*ennemis)[*nbEnnemis].x=0;
    	(*ennemis)[*nbEnnemis].y=debut;
    	(*nbEnnemis)++;
    	
    	(*compteur)++;
}


void deplacement_attaquant(Case** carte, EnnemiActif* ennemis, int nbEnnemis, int taillecarte){
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
