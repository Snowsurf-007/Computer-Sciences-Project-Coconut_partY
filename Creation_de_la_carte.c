void afficher_carte(Case** carte, int taillecarte) {
    printf("    ");
    for (int i = 0; i < taillecarte; i++) {
        if (i < 26) {
            printf("%c ", 'a' + i);
        } else {
            printf("%c ", 'A' + (i - 26));
        }
    }
    printf("\n    ");
    for (int i = 0; i < taillecarte; i++) {
        printf("__");
    }
    printf("\n");

    for (int i = 0; i < taillecarte; i++) {
        printf("%02d |", i + 1);
        for (int j = 0; j < taillecarte; j++) {
            switch (carte[i][j].type) {
                case 0:
                case 1:
                case 2:
                case 3:
                    printf("%s ", EMOJI_NEIGE);
                    break;
                case 4:
                    printf("%s", EMOJI_PIERRE);
                    break;
                case 5:
                    printf("%s", EMOJI_SAPIN);
                    break;
                case 6:
                    printf("%s", EMOJI_DRAPEAU);
                    break;
                case 7:
                    printf("%s", EMOJI_COURONNE);
                    break;
                case 8:
                    printf("%s ", EMOJI_SKIEUR);
                    break;
                case 9:
                    printf("%s", EMOJI_SNOWBOARDER);
                    break;
                case 10:
                    printf("%s", EMOJI_LUGISTE);
                    break;
                case 11:
                    printf("%s", EMOJI_PINGOUIN);
                    break;
                case 12:
                    printf("%s", EMOJI_BONHOMMENEIGE);
                    break;
                case 13:
                    printf("%s", EMOJI_OURS);
                    break;
                default:
                    exit(5);
            }
        }
        printf("|\n");
    }
    printf("    ");
    for (int i = 0; i < taillecarte; i++) {
        printf("‾‾");
    }
    printf("\n");
}
