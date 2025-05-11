void attaquer_defenseurs(Case** carte, Defenseur* defenseurs, int nbDefenseurs, EnnemiActif* ennemis, int nbEnnemis, int* score) {
    for (int i = 0; i < nbDefenseurs; i++) {
        Defenseur def = defenseurs[i]; // Défenseur actuel
        for (int j = 0; j < nbEnnemis; j++) {
            EnnemiActif* ennemi = &ennemis[j]; // Ennemi actuel

            // Vérifie si l'ennemi est encore en vie
            if (ennemi->attaquant.vie <= 0) {
                continue; // Passe à l'ennemi suivant
            }

            // Calcul de la distance entre le défenseur et l'ennemi
            double distance = calculerDistance(def.coordx, def.coordy, ennemi->x, ennemi->y);

            // Si l'ennemi est à portée
            if (distance <= def.portee) {
                // Applique les dégâts en fonction de l'esquive
                if ((rand() % 100) / 100.0 > ennemi->attaquant.esquive) {
                    ennemi->attaquant.vie -= def.degats;
                    printf("Défenseur en (%d, %d) attaque ennemi en (%d, %d). PV restants de l'ennemi : %d\n",
                           def.coordx, def.coordy, ennemi->x, ennemi->y, ennemi->attaquant.vie);

                    // Si l'ennemi est éliminé
                    if (ennemi->attaquant.vie <= 0) {
                        printf("Ennemi en (%d, %d) est éliminé !\n", ennemi->x, ennemi->y);
                        carte[ennemi->x][ennemi->y].type = 6; // Remet la case à "chemin"
                        (*score)++; // Incrémente le score
                    }
                } else {
                    printf("Ennemi en (%d, %d) esquive l'attaque du défenseur en (%d, %d) !\n",
                           ennemi->x, ennemi->y, def.coordx, def.coordy);
                }
            }
        }
    }
}

//attaquer_defenseurs(*carte, *defenseurs, *nbDefenseurs, *ennemis, *nbEnnemis, &score); à mettre dans la boucle de lancer partie juste après déplacement attaquant 
