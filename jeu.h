#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED
#include <stdbool.h>
#include "constantes.h"

void saut(player *joueur, int tableau_jeu[MAXTAB][MAXTAB]);

void leftright(player *joueur, int last_move);

void depl_bulle(Bulle tableau_bubble[MAXBUBBLE], BadBoy tableau_badboy[MAXENNEMIES]);

void depl_badboy(int tableau_jeu[MAXTAB][MAXTAB], jeuO *game, player *joueur, BadBoy tableau_badboy[MAXENNEMIES]);

void test_victoire(BadBoy tableau_badboy[MAXENNEMIES], Bulle tableau_bubble[MAXBUBBLE], jeuO *game);

void saut_badboy(BadBoy tableau_badboy[MAXENNEMIES], int tableau_jeu[MAXTAB][MAXTAB], int i);

void change_coord(BadBoy tableau_badboy[MAXENNEMIES], int i);

void bb_plus_haut(jeuO *game, player *joueur, int tableau_jeu[MAXTAB][MAXTAB], BadBoy tableau_badboy[MAXENNEMIES], int i);

bool compteur_bb_vivants(jeuO *game, BadBoy tableau_badboy[MAXENNEMIES]);

#endif // JEU_H_INCLUDED
