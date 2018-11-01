#ifndef SCORES_H_INCLUDED
#define SCORES_H_INCLUDED
#include "constantes.h"


void sauve_score(jeuO *game, scores *top);
void ecriture_score(scores *top);
void lecture_score(scores *top);
int test_score(scores *top,int score_a_tester);
void insertion_score(scores *top, int score_a_tester);
void ordonner_tableau(scores *top);


#endif // SCORES_H_INCLUDED
