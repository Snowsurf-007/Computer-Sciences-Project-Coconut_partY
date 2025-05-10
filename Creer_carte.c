void creer_carte(Case*** carte, int taillecarte) {
    *carte = (Case**)malloc(taillecarte * sizeof(Case*));
    for (int i = 0; i < taillecarte; i++) {
        (*carte)[i] = (Case*)malloc(taillecarte * sizeof(Case));
        if ((*carte)[i] == NULL) {
            printf("Erreur d'allocation mémoire\n");
            exit(1);
        }
        for (int j = 0; j < taillecarte; j++) {
            (*carte)[i][j].type = rand() % 6;
        }
    }
}
