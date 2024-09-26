#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

int PVj /*Pv du joueur*/,
PVm /*PV du monstre*/,
Potion /*Nombre de potion*/,
loop = 1 /*Booleen pour faire tourner le programme */,
choix = 1 /*Savoir quel choix le joueur fait*/,
attJ /*Combien vaut l'attaque du joueur*/,
attM /*Combien vaut l'attaque du monstre*/,
hJ /*Combien vaut le soin du joueur*/;

int random(int min, int max) { //Fonction pour générer un mobre pseudo-aléatoire
    return (rand() % (max - min)) + min;
}

void Color(int couleurDuTexte,int couleurDeFond){ // fonction d'affichage de couleurs
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}

int main(void) {
    while(loop == 1) { //Si le jeu tourne
        PVj = 1000; //PV du joueur à 1000
        PVm = 1000; //PV du monstre à 1000
        Potion = 3; //3 potion aux départ
        srand(time(0)); //initialisation du temps pour le générateur de nombre aléatoire
        do { //boucle pour savoir si le joueur veux jouer
            printf("------------------------------------\n"
                    "|voulez-vous jouer (Oui(1)/Non(0)) : ");
            scanf("%d", &choix);
        }while((choix != 0) && (choix != 1)) ;

        if(choix == 1) { //boucle du jeu
            printf("\n\n\n");
            while((PVj > 0) && (PVm > 0)) { //tant que les deux entiter sont vivant le jeu tourne
                printf("----------------------------------\n"
                       "Que voulez-vous faire ?\n"
                       "Soin(1) ou attaquer(2)\n"
                       "action : ");
                scanf("%d", &choix);
                printf("\n\n\n");
                if(choix == 1) { //Si le joueur veux se soigner
                    if(Potion > 0) { //Si le joueur à des potions
                        hJ = random(50, 300); //Valeur potion
                        PVj += hJ;
                        attJ = 0;
                        PVj = PVj%1000; //Permet de ne pas dépasser les 1000 PV
                        attM = random(50, 100); //Valeur attaque du monstre
                        PVj -= attM;
                        Potion --; //Enlève une potion
                        printf("----------------------------------\n"
                            "Vous avez %d PV (+%d)(-%d)\n"
                            "Le montre a %d PV\n"
                            "il vous reste %d potion(s)\n", PVj,hJ,attM,PVm , Potion);
                    }
                    else {
                        printf("Vous n'avez plus de potion");
                    }
                }
                else if(choix == 2) { //Si le joueur décide d'attaquer
                    attM = random(50, 100); //Valeur attaque Monstre
                    PVj -= attM;
                    attJ = random(50, 100); // Valeur attaque joueur
                    PVm -= attJ;
                    printf("----------------------------------\n"
                        "Vous avez %d PV(-%d)\n"
                        "Le montre a %d PV(-%d)\n"
                        "il vous reste %d potion(s)\n", PVj,attM,PVm, attJ , Potion);
                }


            }

            if (PVj > 0) { //Si le joueur est en vie
                Color(2,0);
                printf("\n\n\n"
                       "Bravo vous avez gagner\n");
                Color(15,0);
            }


            else if(PVm > 0) { //Si le monstre est en vie
                Color(4,0);
                printf("\n\n\n"
                       "Vous etes mort\n");
                Color(15,0);
            }

            else { //Si le deux sont mort
                printf("\n\n\n"
                       "Vous etes mort mais le montre aussi\n"
                       "ceci est un semi echec\n");
            }
        }
        else if(choix == 0) { // Si le joueur veux arreter de jouer avant le combat(Première condition)
            loop = 0;
            printf("Bonne journee");
        }
    }
    return 0;
}