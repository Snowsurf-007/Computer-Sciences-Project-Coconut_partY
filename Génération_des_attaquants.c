int generer_attaquant(Case carte[], Attaquant liste_attaquant[], int nb_attaquant){
  
  //une chance sur 2 de générer un nouvel ennemi, renvoie le nombre d'attaquant actuel
  
  if(rand()%4){
    nb_attaquant += 1;
    Attaquant nouv_ennemi;
    int numero = -1; //permet de choisir quel attaquant faire apparaitre
    numero = rand() % 3;
    
    if(numero == 0){
      constructeur_SkieurFrenetique(nouv_ennemi);
    }
    else if(numero == 1){
      constructeur_SnowboarderAcrobate(nouv_ennemi);
    }
    else if(numero == 2){
      constructeur_LugisteBarjo(nouv_ennemi);
    }
    liste_attaquant[nb_attaquant] = nouv_ennemi;
  }
  return nb_attaquant;
}
