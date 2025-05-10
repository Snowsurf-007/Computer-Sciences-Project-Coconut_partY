int main() {
    srand(time(NULL));
    int jeu_en_cours=1; // Variable pour contrôler la boucle principale
    // Initialisation des variables
    Case** carte=NULL; 
    int taillecarte=0;
    Defenseur* defenseurs=NULL;
    int nbDefenseurs=0;
    EnnemiActif* ennemis=NULL;
    int nbEnnemis=0;
    int score=0;
    int flocons=120;
    int vague=0;


    while (jeu_en_cours==1){
        int choix_menu=menuDemarrage(); // Affiche le menu principal et récupère le choix

        switch (choix_menu){
            case 1:
                lancerpartie(&carte, &taillecarte, &defenseurs, &nbDefenseurs, &ennemis, &nbEnnemis, &score, &flocons, &vague); // Lance une nouvelle partie
                break;
            case 2:
                chargement("sauvegarde.txt", &carte, &taillecarte, &defenseurs, &nbDefenseurs, &ennemis, &nbEnnemis, &score, &flocons, &vague);
                lancerpartie(&carte, &taillecarte, &defenseurs, &nbDefenseurs, &ennemis, &nbEnnemis, &score, &flocons, &vague); // Reprend la partie chargée
            break;
            case 3:
                printf("A plus 👋😊\n");
                jeu_en_cours=0; // Quitte la boucle principale
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    }

    return 0;
}
