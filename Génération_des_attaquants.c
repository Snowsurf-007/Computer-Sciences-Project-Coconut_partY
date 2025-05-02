int generer_attaquant(Case carte[], Attaquant liste_attaquant[], int avancee_vague, int vagues[][], int numero_vague){
  
  //avancee_vague représente ou on en est dans une vague tandis que numero vague est pour savoir a quelle vague on en est cela donnera donc vague[numero_vague][avancee_vague] pour generer un ennemi
  
  if(vague[numero_vague][avancee_vague] != 0){
    nb_attaquant += 1;
    Attaquant nouv_ennemi;
    if(vague[numero_vague][avancee_vague] == 1){
      constructeur_SkieurFrenetique(nouv_ennemi);
    }
    else if(vague[numero_vague][avancee_vague] == 2){
      constructeur_SnowboarderAcrobate(nouv_ennemi);
    }
    else if(vague[numero_vague][avancee_vague] == 3){
      constructeur_LugisteBarjo(nouv_ennemi);
    }
    liste_attaquant[nb_attaquant] = nouv_ennemi;
  }
  return nb_attaquant;
}
