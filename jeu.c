#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "jeu.h"
#include "affichage.h"

/*********************************************************************************************************************************************************************************************/

//                                                      FONCTION POUR LE SAUT DU JOUEUR

/*********************************************************************************************************************************************************************************************/

void saut(player *joueur,int tableau_jeu[MAXTAB][MAXTAB]){

// Code pour effectuer un saut

        if(joueur->vit_vert<0){                                                           // tant que vitesse verticale <= 0, on monte

                joueur->saut=AIR;

                joueur->posy+=joueur->vit_vert;

                joueur->vit_vert+=1;
        }
        else{                                                                         // Si vitesse verticale >0, alors on redescend

            if(tableau_jeu[(joueur->posy/HEIGHT)+1][(joueur->posx+(HEIGHT/2))/HEIGHT]!=1){               // jusqu'à ce qu'on tombe sur une plateforme

                joueur->posy+=5;
            }
            else{

                joueur->vit_vert=0;                                          // On mettra alors la valeur de la vitesse verticale à 0

                joueur->saut=SOL;
            }
        }

        attrape_bubble(tableau_bubble);
        attrape_fruit(joueur);
}

/*********************************************************************************************************************************************************************************************/

//                                        FONCTION POUR LES DEPLACEMENTS HORIZONTAUX DU JOUEUR

/*********************************************************************************************************************************************************************************************/
void leftright(player *joueur, int last_move){              // la fonction prend en paramètre la structure du joueur ainsi que last_move qui permettra de savoir si l'on va vers la gauche ou la droite


    if(joueur->vit_horiz!=0){           // Si il y a une vitesse horizontale

        if((joueur->posx+joueur->vit_horiz)>=HEIGHT && (joueur->posx+joueur->vit_horiz) < 940){         // Si l'on se trouve dans les limites du plateau de jeu

            joueur->posx+=joueur->vit_horiz;        // On se déplace de : vitesse horizontale
            joueur->vit_horiz=0;                    // si cette ligne n'était pas présente, le joueur avancerai continuellement dès que les touches left ou right auraient été pressée une fois
        }

        else{

            if(last_move==GAUCHE){

                joueur->posx-=joueur->posx-HEIGHT;
                joueur->vit_horiz+=1;

            }
            if(last_move==DROITE){

                joueur->posx+=((TAILLE-3*HEIGHT)-joueur->posx);
                joueur->vit_horiz-=1;
            }
        }

        attrape_bubble(tableau_bubble);
        attrape_fruit(joueur);
    }
}

/*********************************************************************************************************************************************************************************************/

//                                                  FONCTIONS POUR LE DEPLACEMENT DES BULLES

/*********************************************************************************************************************************************************************************************/

void depl_bulle(Bulle tableau_bubble[MAXBUBBLE], BadBoy tableau_badboy[MAXENNEMIES]){

int i;




    for(i=0;i<MAXBUBBLE;i++){

    collision_bubble(tableau_badboy,tableau_bubble,i);
    attrape_bubble(tableau_bubble);

        if(tableau_bubble[i].vit_horiz!=0 && tableau_bubble[i].coll==0){

            if((tableau_bubble[i].posx+tableau_bubble[i].vit_horiz)>HEIGHT && tableau_bubble[i].posx+tableau_bubble[i].vit_horiz<TAILLE-3*HEIGHT){

                tableau_bubble[i].posx+=tableau_bubble[i].vit_horiz;
            }
            else    tableau_bubble[i].vit_horiz=0;

        }

        if(tableau_bubble[i].vit_horiz==0 && tableau_bubble[i].coll==0){

            if(tableau_bubble[i].posy-tableau_bubble[i].vit_vert>6*HEIGHT) tableau_bubble[i].posy-=tableau_bubble[i].vit_vert;
        }

        if(tableau_bubble[i].coll==1){

            if(tableau_bubble[i].posy-tableau_bubble[i].vit_vert>6*HEIGHT) tableau_bubble[i].posy-=tableau_bubble[i].vit_vert;
            else{

                if(tableau_bubble[i].posx<(TAILLE/2))   tableau_bubble[i].posx+=1;

            }

        }

    }

}

/*********************************************************************************************************************************************************************************************/

//                                                          DEPLACEMENT DES ENNEMIS

/*********************************************************************************************************************************************************************************************/

void depl_badboy(int tableau_jeu[MAXTAB][MAXTAB], jeuO *game, player *joueur, BadBoy tableau_badboy[MAXENNEMIES]){


int i;

game->compt_actu+=1;                            // compteur qui permet de gérer le nombre de rafraîchissement de la position de l'annemi par rapport au joueur via un modulo



    for(i=0;i<game->nb_ennemis;i++){                 // boucle pour affecter les changements aux différents ennemis

        if(game->compt_actu%1000 == 0)  tableau_badboy[i].vit_horiz+=1;         // On incrémente la vitesse de déplacement toutes les 20 secondes



        if(tableau_badboy[i].posy<=(joueur->posy))   bb_plus_haut(game, joueur, tableau_jeu, tableau_badboy, i);                     // si ennemi est plus haut que joueur


        else if(abs(tableau_badboy[i].posy - joueur->posy) < HEIGHT)    bb_plus_haut(game, joueur, tableau_jeu, tableau_badboy, i);


        else{

            if((game->compt_actu)%10==0 && tableau_jeu[(tableau_badboy[i].posy/HEIGHT)+1][tableau_badboy[i].posx/HEIGHT] == 1)     tableau_badboy[i].vit_vert=-27;          // Permet d'ajuster la vitesse à laquelle l'ennemi réagit avant de sauter si le joueurse trouve sur une plateforme supérieur à lui

            else{

                if(tableau_badboy[i].posx<=TAILLE && tableau_badboy[i].posx>HEIGHT){                // si on est dans les limites de l'écran


                    if(tableau_jeu[(tableau_badboy[i].posy/HEIGHT)+1][tableau_badboy[i].posx/HEIGHT]!=1)    tableau_badboy[i].posy+=10;        // Si on est plus sur une plateforme


                    change_coord(tableau_badboy, i);
                }
            }

            if(tableau_badboy[i].vit_vert < 0)  saut_badboy(tableau_badboy, tableau_jeu, i);            // lancement du saut de l'ennemi si vitesse vertical < 0
        }
    }

    collision_player(joueur,tableau_badboy);        // véification si collision
}

/*********************************************************************************************************************************************************************************************/

//                                                      SAUT DES ENNEMIS

/*********************************************************************************************************************************************************************************************/


void saut_badboy(BadBoy tableau_badboy[MAXENNEMIES], int tableau_jeu[MAXTAB][MAXTAB], int i){



            // Code pour effectuer un saut                                  // Si l'addition en pxls est plus grande que la hauteur max

            if(tableau_badboy[i].vit_vert<0 && tableau_badboy[i].posy+tableau_badboy[i].vit_vert>6*HEIGHT){                                                           // tant que vitesse verticale <= 0, on monte


                tableau_badboy[i].posy+=tableau_badboy[i].vit_vert;

                tableau_badboy[i].vit_vert+=1;
            }
            else{                                                                         // Si vitesse verticale >0, alors on redescend

                if(tableau_jeu[(tableau_badboy[i].posy/HEIGHT)+1][(tableau_badboy[i].posx+(HEIGHT/2))/HEIGHT]!=1){               // jusqu'à ce qu'on tombe sur une plateforme

                    tableau_badboy[i].posy+=5;
                }

                else{

                    tableau_badboy[i].vit_vert=0;
                }
            }

}

/*********************************************************************************************************************************************************************************************/

//                                                      ADAPTATION DES COORDONNEES

/*********************************************************************************************************************************************************************************************/


void change_coord(BadBoy tableau_badboy[MAXENNEMIES], int i){


    if(tableau_badboy[i].sens_bb==DROITE){

        if((tableau_badboy[i].posx+tableau_badboy[i].vit_horiz)<(TAILLE-2*HEIGHT))  tableau_badboy[i].posx+=tableau_badboy[i].vit_horiz;// Si on ne sort pas de l'écran de jeu à droite

    }


    if(tableau_badboy[i].sens_bb==GAUCHE){

        if((tableau_badboy[i].posx-tableau_badboy[i].vit_horiz)>HEIGHT)  tableau_badboy[i].posx-=tableau_badboy[i].vit_horiz;// Si on ne sort pas de l'écran de jeu à droite

    }
}

/*********************************************************************************************************************************************************************************************/

//                                                      FONCTION SI ENNEMI PLUS HAUT QUE JOUEUR

/*********************************************************************************************************************************************************************************************/


void bb_plus_haut(jeuO *game, player *joueur, int tableau_jeu[MAXTAB][MAXTAB], BadBoy tableau_badboy[MAXENNEMIES], int i){


    if(tableau_badboy[i].posx<=TAILLE && tableau_badboy[i].posx>HEIGHT){                // si on est dans les limites de l'écran

        if(tableau_jeu[(tableau_badboy[i].posy/HEIGHT)+1][tableau_badboy[i].posx/HEIGHT]!=1)    tableau_badboy[i].posy+=15;        // Si on est plus sur une plateforme


        change_coord(tableau_badboy, i);



        if(tableau_badboy[i].posy==joueur->posy){

            if((game->compt_actu)%100==0){

                if(tableau_badboy[i].posx>=joueur->posx) tableau_badboy[i].sens_bb=GAUCHE;

                else    tableau_badboy[i].sens_bb=DROITE;

            }

        }
        else{

            if(tableau_badboy[i].sens_bb==DROITE){

                if((tableau_badboy[i].posx+tableau_badboy[i].vit_horiz)<(TAILLE-3*HEIGHT))  tableau_badboy[i].posx+=tableau_badboy[i].vit_horiz;// Si on ne sort pas de l'écran de jeu à droite

                else   tableau_badboy[i].sens_bb=GAUCHE;

            }

            if(tableau_badboy[i].sens_bb==GAUCHE){

                if((tableau_badboy[i].posx-tableau_badboy[i].vit_horiz)>HEIGHT)  tableau_badboy[i].posx-=tableau_badboy[i].vit_horiz;// Si on ne sort pas de l'écran de jeu à droite

                else     tableau_badboy[i].sens_bb=DROITE;
            }
        }
    }

}

/*********************************************************************************************************************************************************************************************/

//                                                      FONCTION POUR TESTER SI LE JOUEUR A GAGGNE LA PARTIE

/*********************************************************************************************************************************************************************************************/


void test_victoire(BadBoy tableau_badboy[MAXENNEMIES], Bulle tableau_bubble[MAXBUBBLE], jeuO *game){


int i, compt_bulles=0, compt_bb=0;                    // compteurs


    if(game->window_id==JEU){

        for(i=0;i<game->nb_ennemis;i++){

            if(tableau_badboy[i].etat==1)   compt_bb++;         // test s'il y a encore des ennemis qui se déplacent
        }

        for(i=0;i<MAXBUBBLE;i++){

            if(tableau_bubble[i].coll==1 && tableau_bubble[i].etat==1)   compt_bulles++;     // test s'il y a encore des ennemis emprisonnés dans des bulles

        }


        if(compt_bb==0 && compt_bulles==0)  game->window_id=GAGNE;


    }

}

/*********************************************************************************************************************************************************************************************/

//                                                      FONCTION POUR TESTER LE NOMBRE D'ENNEMIS ENCORE VIVANTS

/*********************************************************************************************************************************************************************************************/
bool compteur_bb_vivants(jeuO *game, BadBoy tableau_badboy[MAXENNEMIES]){

int i;
int compt=0;          // Compteur du nombre d'ennemis encore en vie
bool ennemis_vivants;    // Variable booléenne signalant s'il y a encore des ennemis vivants ou non

    for(i=0;i<game->nb_ennemis;i++){

        if(tableau_badboy[i].etat == 1)     compt++;

    }


if(compt == 0)  ennemis_vivants = false;
else            ennemis_vivants = true;

game->val_fruit=400;
game->val_fruit-=50*(game->nb_ennemis-compt);              // Permet de diminuer la valeur gagnée lorsqu'on attrape un fruit, en fonction du nombred'ennemis déjà tués


return ennemis_vivants;
}





