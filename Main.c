int main() {
    int jeu_en_cours=1; // Variable pour contrôler la boucle principale

    while (jeu_en_cours==1){
        int choix_menu=menuDemarrage(); // Affiche le menu principal et récupère le choix

        switch (choix_menu){
            case 1:
                lancerpartie(); // Lance une nouvelle partie
                break;
            case 2:
            	//reprendre la partie
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
