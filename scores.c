#include <stdio.h>
#include <stdlib.h>
#include "affichage.h"
#include "scores.h"
#include "constantes.h"
#include "fichiers.h"
#include <string.h>

/*********************************************************************************************************************************************************************************************/

//                                                      FONCTION PRINCIPALE

/*********************************************************************************************************************************************************************************************/

void sauve_score(jeuO *game, scores *top){


int score_a_tester = game->score;                   // Le résultat de la partie devient la valeur de la variable "score_a_tester"
int position_score;                              // Valeur plus grande que 10 (nbre maximum de meilleurs scores)



lecture_score(top);


position_score=test_score(top,score_a_tester);


if(position_score<MAX_NB_SCORE){

    insertion_score(top, score_a_tester);

    ordonner_tableau(top);

    ecriture_score(top);

}

lecture_score(top);



}
/*********************************************************************************************************************************************************************************************/

//                                                                      ECRITURE FICHIER

/*********************************************************************************************************************************************************************************************/

void ecriture_score(scores *top){

int i=0;

FILE *fichier=fopen("scores.txt","w");


    if(fichier==NULL){   //Gestion d'erreur

        puts("Erreur d'ouverture de fichier:");
        exit(1);                                                    // Termine le programme avec le code erreur 1
    }

    else
    {
        while(i<MAX_NB_SCORE){

            fprintf (fichier, "%i ", top->top_scores[i]);
            i++;
        }

        fclose (fichier);
    }

}

/*********************************************************************************************************************************************************************************************/

//                                                                      LECTURE FICHIER

/*********************************************************************************************************************************************************************************************/


void lecture_score(scores *top){

int i=0;

FILE *fichier=fopen("scores.txt","r");

    if(fichier==NULL){   //Gestion d'erreur

        puts("Erreur d'ouverture de fichier:");
        exit(1);                                                    // Termine le programme avec le code erreur 1
    }

    else
    {

        while(fscanf(fichier, "%i", &top->top_scores[i]) == 1){

            i++;

        }

   fclose (fichier);

    }
}

/*********************************************************************************************************************************************************************************************/

//                                                     FONCTION DE TEST SI RESULTAT FAIT PARTIE DES MEILLEURS SCORES

/*********************************************************************************************************************************************************************************************/

int test_score(scores *top,int score_a_tester){

int position=MAX_NB_SCORE+1;       // position actuelle de la valeur de "score_a_tester" dans le tableau
int i=MAX_NB_SCORE;            // compteur tableau de scores



        while(score_a_tester > top->top_scores[i-1] && i>0){

            position-=1;
            i--;
        }

    return position;

}
/*********************************************************************************************************************************************************************************************/

//                                                      INSERTION SCORE DANS LE TABLEAU DES MEILLEURS SCORES SI POSITION < MAX_NB_SCOE

/*********************************************************************************************************************************************************************************************/




void insertion_score(scores *top, int score_a_tester){


    top->top_scores[MAX_NB_SCORE-1]=score_a_tester;

}

/*********************************************************************************************************************************************************************************************/

//                                                      ORDONNER LE TABLEAU EN FONCTION DU NOUVEAU SCORE

/*********************************************************************************************************************************************************************************************/

void ordonner_tableau(scores *top){

int i;
int temp;


i=MAX_NB_SCORE-1;

    while(top->top_scores[i]>top->top_scores[i-1] && i>=1){

        temp=top->top_scores[i-1];
        top->top_scores[i-1]=top->top_scores[i];
        top->top_scores[i]=temp;
        i--;


    }

}

