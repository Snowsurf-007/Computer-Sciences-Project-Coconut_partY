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
