typedef struct{
        char emoji[TAILLECHAINE]; //code UTF8 emoji du defenseur
        int portee;
        int degats;
        float vitessetir;
        int prix;
        int coordx;
        int coordy;
}Defenseur;

typedef struct{
        char emoji[TAILLECHAINE]; //code UTF8 emoji de l'attaquant
        int vie;
        float esquive;
        int gain;
}Attaquant;

Defenseur constructeur_PinguPatrouilleur(Defenseur a){
        strcpy(a.emoji, EMOJI_PINGOUIN);
        a.portee=5;
        a.degats=30;
        a.vitessetir=0.5;
        a.prix=100;
        return a;
}

Defenseur constructeur_FloconPerceCiel(Defenseur a){
        strcpy(a.emoji, EMOJI_BONHOMMENEIGE);
        a.portee=10;
        a.degats=300;
        a.vitessetir=2;
        a.prix=200;
        return a;
}

Defenseur constructeur_GardePolaire(Defenseur a){
        strcpy(a.emoji, EMOJI_OURS);
        a.portee=2;
        a.degats=70;
        a.vitessetir=1;
        a.prix=150;
        return a;
}

Attaquant constructeur_SkieurFrenetique(Attaquant a){ //attaquant rapide et faible, petit taux d'esquive 
        strcpy(a.emoji, EMOJI_SKIEUR);
        a.vie=250;
        a.esquive=0.15;
        a.gain=20;
        return a;
}

Attaquant constructeur_SnowboarderAcrobate(Attaquant a){ //attaquant vitesse moyenne, vie moyenne mais bonne esquive
        strcpy(a.emoji, EMOJI_SNOWBOARDER);
        a.vie=500;
        a.esquive=0.30;
        a.gain=30;
        return a;
}

Attaquant constructeur_LugisteBarjo(Attaquant a){ //attaquant lent et resistant
        strcpy(a.emoji, EMOJI_LUGISTE);
        a.vie=2000;
        a.esquive=0;
        a.gain=50;
        return a;
}
