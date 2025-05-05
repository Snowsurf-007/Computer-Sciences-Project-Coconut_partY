void Deplacement_Attaquant2(int carte[][], int taillecarte, int j) {
		
			if(j<=taillecarte-1 || j>=taillecarte-1) {//premiere condition d'arrêt
			
				
			}
			
			
				
			if(carte[i][j+1]==13 || carte[i][j+1]==14 || carte[i][j+1]==15) {
			
				carte[i][j]=carte[i][j+1];
				deplacement(carte,i,j+1);
			}
			
			else if(carte[i][j-1]==13 || carte[i][j-1]==14 || carte[i][j-1]==15) {
			
				carte[i][j]=carte[i][j-1];
				deplacement(carte,i,j-1);
			}
			
			else if(i<1) {//deuxieme condition d'arrêt
			
				
			}
			
			else if(carte[i-1][j]==13 || carte[i-1][j]==14 || carte[i-1][j]==15) {
			
				carte[i][j]=carte[i-1][j];
				deplacement(carte,i-1,j);
			}
			
			else {
				printf("erreur : deplacement attaquant");
			}
			
		
			
					
		
}
