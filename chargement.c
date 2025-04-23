int** chargement(const char* nom_fichier, int* ligne, int* colonne) {

    // Ouverture du fichier en mode lecture 
    FILE* fichier = fopen(nom_fichier, "r");
    // Vérification du bon déroulement de l'ouverture
    if(fichier == NULL) {
        printf("Erreur : le fichier %s n'a pas pu être ouvert \n", nom_fichier);
        exit(1);
    }

    else() {
        fscanf("%d %d", ligne, colonne); // Lecture des dimensions du tableau
        char** tab = malloc(*ligne * sizeof(char*)); // Allocation de mémoire pour le tableau
        for(int i = 0; i < *ligne; i++) {
            tab[i] = malloc(*colonne * sizeof(char)); // Allocation de mémoire pour chaque ligne
            for(int j = 0; j < *colonne; j++) {
                fscanf("%s", tab[i][j]); // Lecture de chaque élément du tableau
            }
        }
    }

    fclose(fichier); // Fermeture du fichier
    return tab; // Retourne le tableau chargé
}