void deplacement_attaquant(int** carte, int i, int j) {
				
		if(carte[i][j+1]==13 || carte[i][j+1]==14 || carte[i][j+1]==15) {
			carte[i][j]=carte[i][j+1];
			carte[i][j+1]=11;
			deplacement_attaquant(carte,i,j+1);
		}	
		else if(carte[i][j-1]==13 || carte[i][j-1]==14 || carte[i][j-1]==15) {
			carte[i][j]=carte[i][j-1];
			carte[i][j-1]=11;
			deplacement_attaquant(carte,i,j-1);
		}	
		else if(i<1) {//deuxieme condition d'arrêt	
		}
		else if(carte[i-1][j]==13 || carte[i-1][j]==14 || carte[i-1][j]==15){
			carte[i][j]=carte[i-1][j];
			carte[i-1][j]=11;
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
