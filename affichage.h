#ifndef AFFICHAGE_H_INCLUDED
#define AFFICHAGE_H_INCLUDED
#include "jeu.h"

// Description des fonctions dans affichage.c

void init_all(int first);
void display(void);
void dessiner_map(void);
void dessiner_menu(void);
void dessiner_regles(void);
void dessiner_comm(void);
void dessiner_victoire(void);
void SpecialKeys(int key, int x, int y);
void init_bulle(void);
void dessiner_joueur(void);
void dessiner_badboy(void);
void dessiner_bulle(void);
void dessiner_fruits(void);
void infos_jeu(void);
void Clavier(unsigned char key, int x, int y);
void Timer(int no);
int main(int argc, char *argv[]);
void reshape(int w, int h);
void collision_player(player *joueur, BadBoy tableau_badboy[MAXENNEMIES]);
void collision_bubble(BadBoy tableau_badboy[MAXENNEMIES], Bulle tableau_bubble[MAXBUBBLE],int no_bulle);
void attrape_bubble(Bulle tableau_bubble[MAXBUBBLE]);
void attente(int no);
void dessiner_pause(void);
void dessiner_niveau(void);
void attrape_fruit(player *joueur);
void dessiner_scores(void);
void affiche_top_scores(void);
void dessiner_fond(void);
void init_niveau(void);

#endif // AFFICHAGE_H_INCLUDED
