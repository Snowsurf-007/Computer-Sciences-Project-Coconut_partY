int main() {
    system("clear");
    int jeu_en_cours=1; // Variable pour contrôler la boucle principale
    srand(time(NULL));   
    // Initialisation des variables
    Case** carte=NULL; 
    int taillecarte=0;
    int nbDefenseurs=0;
    EnnemiActif* ennemis = NULL;
    int nbEnnemis=0;
    int score=0;
    int flocons=350;
    int vague=0;
    Defenseur* defenseurs=(Defenseur*)malloc(100 * sizeof(Defenseur)); // Pre-allocation d'espace pour 100 defenseurs
    if (defenseurs == NULL) {
        printf("\t Erreur d'allocation mémoire pour les défenseurs\n");
        exit(2);
    }

    while (jeu_en_cours==1){
        int choix_menu=menuDemarrage(); // Affiche le menu principal et récupère le choix

        switch (choix_menu){
            case 1:
                lancerpartie(&carte, &taillecarte, &defenseurs, &nbDefenseurs, &ennemis, &nbEnnemis, &score, &flocons, &vague); // Lance une nouvelle partie
                system("make");
                break;
            case 2:
                chargement("sauvegarde.txt", &carte, &taillecarte, &defenseurs, &nbDefenseurs, &ennemis, &nbEnnemis, &score, &flocons, &vague);
                lancerpartie(&carte, &taillecarte, &defenseurs, &nbDefenseurs, &ennemis, &nbEnnemis, &score, &flocons, &vague); // Reprend la partie chargée
                system("make");
            break;
            case 3:
                printf("\t A plus 👋😊\n");
                jeu_en_cours=0; // Quitte la boucle principale
                break;
            default:
                printf("\t Choix invalide. Veuillez réessayer.\n");
        }
    }
    
    free(defenseurs);
    defenseurs = NULL;
    
    return 0;
}
