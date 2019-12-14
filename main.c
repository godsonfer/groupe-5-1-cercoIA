#include <stdio.h>
#include <stdlib.h>

#define NB_COLONNE 3
#define NB_LIGNE 3

/*Prototypes de quelque fonctions*/

void regleDuJeu(void);
void bienvenuUtilisateur(void);
void menu(void);
void retour_recommencer (void);
void jouer(void);
void quitter_Menu (void);


// soit dans notre grille nous avons un rond, une croix ou c'est vide

typedef enum {VIDE, ROND, CROIX} ValeurGrille;
typedef enum {FALSE,  TRUE} Boolean;

// grille
static ValeurGrille grille[NB_LIGNE][NB_COLONNE];

//initialisattion du premier joeur
static int prochainJoeur =  CROIX;

// affichage de la grille de morpion a vide

void initialiserGrille(){
    int i, j;

    for(i=0; i<NB_LIGNE; i++){

        for(j=0;  j<NB_COLONNE; j++){
            grille[i][j] =  VIDE;
            printf(" - ");
        }
        printf("\n \n");
    }
     printf("A x de commencer le jeu \n");
}


//Affichage de la grille de Morpion quqnd on commence le jeux.  O pour joueur 1 et X joeur 2
//mis a jour de la grille

void afficheGrille (){
    int i,j;
    for(i=0; i<NB_LIGNE; i++){
        for(j=0; j<NB_COLONNE;  j++){
            switch(grille[i][j]){
            case VIDE:
                printf(" - ");
                break;

            case ROND:
                printf(" O ");
                break;

            case CROIX:
                printf(" X ");
                break;
            }
        }
        printf("\n \n");
    }

}


/*
Coodonnees du nouveau pion sur la grille. Ces coodonnees doivent etre sur la grille en non en
dehors de la grille.  si la cage contient un pion, il faut alerter l'utilisateur. Et le joeur doit
 reprendre le jeux
*/
 void metUnPionSurLaGrille(){
    int ligne, colonne;
    Boolean saisieCorrecte =  FALSE;

 do{
        printf("Entrez les numero de ligne  et de colonne \n");
    scanf("%d %d",  &ligne,  &colonne);
    printf("\n");

    if((ligne > 0 )&& (ligne<=NB_LIGNE) && (colonne > 0 )&& (colonne<=NB_COLONNE ))
    {
        //deecrement les ligne et les colonnes
        ligne--;
        colonne--;
        // verification  de la disponibilite de la cage
            if(grille[ligne][colonne] != VIDE){
                printf("Cette cage nest pas vide. Veuillez recommencer ! \n");
            }else{
                saisieCorrecte =  TRUE;
                // Si la grille est dispo alors  il faut identifier les prochain joueur
                grille[ligne][colonne] = (ValeurGrille)prochainJoeur;
                if(prochainJoeur == ROND){
                        printf("A votre tour X \n");
                    prochainJoeur = CROIX;
                }else {
                    printf("A votre tour O \n");
                    prochainJoeur =  ROND;
                }
            }

    }else {
        printf("Coodonnee  incorrect. Veuillez reesayer ! \n ");
        }
    }while(!saisieCorrecte);
 }

/* Test si l'un des joueurs a gagner.
*/
Boolean testeFinJeu() {
        int i,j;
        int joueurGagnant;

        Boolean estFini = FALSE;


        /* si la case 1,1 est VIDE, cela signifie que les diagonales, la ligne 1 et la colonne 1 ne sont
     pas gagnantes*/

      if (grille[1][1] != VIDE) {
        if (/* colonne 1 */ ((grille[0][1] == grille[1][1]) && (grille[1][1] == grille[2][1])) ||
            /* ligne 1 */ ((grille[1][0] == grille[1][1]) && (grille[1][1] == grille[1][2])) ||
            /* diagonale */ ((grille[0][0] == grille[1][1]) && (grille[1][1] == grille[2][2])) ||
            /* autre diag */ ((grille[0][2] == grille[1][1]) && (grille[1][1] == grille[2][0]))) {
          joueurGagnant = grille[1][1]; /* ie ROND ou CROIX */
          estFini = TRUE;
        }
      }

        /* si la case 0,0 est vide, cela signifie que la ligne 0 et le colonne 0 ne sont pas gagnantes */

      if ((!estFini) && (grille[0][0] != VIDE)) {
        if ( /* ligne 0 */ ((grille[0][0] == grille[0][1]) && (grille[0][1] == grille[0][2])) ||
            /* colonne 0*/ ((grille[0][0] == grille[1][0]) && (grille[1][0] == grille[2][0]))) {
          joueurGagnant = grille[0][0];
          estFini = TRUE;
        }
      }

      /* si la case 2,2 est vide, cela signifie que la ligne 2 et la colonne 2 ne sont gagnantes */

      if ((!estFini) && (grille[2][2] != VIDE)) {
        if ( /* ligne 2 */ ((grille[2][0] == grille[2][1]) && (grille[2][1] == grille[2][2])) ||
            /* colonne 2 */ ((grille[0][2] == grille[1][2]) && (grille[1][2] == grille[2][2]))) {
          joueurGagnant = grille[2][2];
          estFini = TRUE;
        }
      }
        if (estFini) {

            printf("Felicitations au joueur ");
            if (joueurGagnant == ROND)
              printf(" O ");
            else
              printf("X ");
            printf("qui a gagne le jeux.\n");
            return  TRUE;
            }

     /* teste si la grille n'est pas pleine */
      for (i=0; i<NB_LIGNE; i++) {
        for (j=0; j<NB_COLONNE; j++) {
          if (grille[i][j] == VIDE ) /* Au moins une case est vide donc le jeu n'est pas fini */
        return FALSE;
        }
      }
      return TRUE;

}



void quitter_Menu(){
int quitter;
    printf("\n \n 1- Menu 0- Quitter \n \n");
    scanf("%d", &quitter);
    switch(quitter){
        case 1:
            menu();
        break;
        case 0:
           return;
        break;
        default :
            printf("Choississez la bonne option");
        break;
    }}

/*
fonction permettant d'afficher les regles du jeux
*/


void regleDuJeu(){
    printf("1 - Chaque joueur a un tour \n \n");
    printf("2 - Le premier joeur a aligner 3 pions soit verticalement, horizontalement ou dans les diagonales gagne le jeu \n \n");
    quitter_Menu();
}

/*
    fonctions permettant de souhaiter la bienvenue a l'utilisateur
*/

void jouer(){
    initialiserGrille();
    do {
        metUnPionSurLaGrille();
        afficheGrille();
    }while (!testeFinJeu());
    retour_recommencer();

}

void menu(){
    printf("===========JEU DE MORPION========= \n \n");
    printf("1-Jouer \n \n");
    printf("2-Regles du jeux \n \n");
    printf("0-Quitter \n \n ");
}


void retour_recommencer(){
    int retourner;
    printf("\n \n1- Menu \n \n2- Recommencer \n \n");
    scanf("%d", &retourner);
    switch(retourner){
        case 1:
            menu();
        break;
        case 2:
            jouer();
        break;
        default :
            printf("Choississez la bonne option");
        break;
    }
}


void bienvenuUtilisateur (){
    int parametres;
    menu();
    scanf("%d", &parametres);

    while(parametres !=1 && parametres !=2 && parametres !=3  && parametres !=4){
        printf("Veuillez selectionner le bon numero \n \n Numero = ");
        scanf("%d", &parametres);
    }

        switch(parametres){
            case 1:
                printf("Jouer \n \n \n");
              jouer();
            break;
            case 2:
                printf("Regles du Jeu \n \n \n");
                regleDuJeu();
            break;

            case 0:
                return;


        }


}
/*
    fonction main (), nous initialison la grille, puis permettons de jouer suivant de la
    nouvelle version de la grille et ainsi de suite tant que le jeux n'est pas terminer

*/
int main()
{
    bienvenuUtilisateur();
    return 1;
}
