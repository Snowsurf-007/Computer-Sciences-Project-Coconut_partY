void sauvegarde(const char* nom_fichier, int** tab, int ligne, int colonne) {
        // Ouverture du fichier en mode écriture
        FILE* fichier=fopen(nom_fichier, "w");

        //vérification du bon déroulement de l'ouverture
        if(fichier==NULL) {
                printf("Erreur : le fichier %s n'a pas pu être ouvert \n", nom_fichier);
                exit(1);
        }
        else {
                fprintf(fichier,"%d %d", ligne, colonne); // Ecriture des dimensions du tableau
                for(int i=0; i<ligne; i++) {
                        for (int j=0; j<colonne; j++) {
                                fprintf(fichier," %d", tab[i][j]); // Ecriture de chaque élément du tableau
                        }
                }

        }
        fclose(fichier); // Fermeture du fichier
}
