#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "affichage.h"
#include "jeu.h"
#include "constantes.h"
#include "fichiers.h"
#include "scores.h"


/*********************************************************************************************************************************************************************************************/

//                                                        POINTEURS SUR LES STRUCTURES

/*********************************************************************************************************************************************************************************************/

player *joueur=&p1;
jeuO *game=&jeu;
image *img_menu=&img;
sprite *img_sprite=&bubble;
sprite *img_sprite2=&ennemies;
sprite *img_sprite3=&bulle;
sprite *img_sprite4=&bubble_left;
sprite *img_sprite5=&bulle_rouge;
sprite *img_sprite6=&ennemies_left;
sprite *img_sprite7=&fraise;
sprite *img_sprite8=&orange;
sprite *img_sprite9=&pasteque;
scores *top=&meill_score;
plateforme *img_plateforme=&mur;

/*********************************************************************************************************************************************************************************************/

//                                                         FONCTION D'INITIALISATION DU JEU

/*********************************************************************************************************************************************************************************************/
void init_all(int first){

int i;      // Compteur boucle
char fich[30];

    chargeFichier(tableau_jeu);               // Charger et vérifier le tableau de la map de jeu depuis un fichier texte
    load_interface(img_menu);
    load_plateforme(img_plateforme);

        last_move=DROITE;                       // direction de départ choisie puisque le joueur démarre la partie en bas à gauche de l'écran, il doit donc regarder à droite
        game->compt_actu=0;                     // compteur qui servira à la miseà joueur des ennemis par rapport  au joueur dans la fonction depl_badboy appelée dans le Timer
        game->x=500;                             // Position de départ pour ennemis
        game->y=200;
        joueur->posx=HEIGHT;                    // Position de départ du joueur (coin inférieur gauche)
        joueur->posy=TAILLE-2*HEIGHT;

        strcpy(top->score,"");


        if(first==1){

            img_sprite7->coll=0;
            img_sprite8->coll=0;
            img_sprite9->coll=0;

            game->enregistre_score=1;

            charger_sprites(fich,img_sprite,img_sprite2,img_sprite3,img_sprite4,img_sprite5,img_sprite6,img_sprite7,img_sprite8,img_sprite9);

            game->vies=3;                       // Nbre de vies initialisé à 3
            game->nb_bulles=0;                  // Compteur pour le nombre de bulles à lancer
            game->score=0;                      // Variable du score en cours
            game->val_fruit=400;                // valeur initiale ajoutée au score lorsqu'un fruit est attrapé

                for(i=0;i<MAXBUBBLE;i++){               // Boucle pour les bulles - Initialisation des valeurs

                    tableau_bubble[i].coll=0;
                    tableau_bubble[i].etat=0;
                }


        }
        game->menu_id=1;                        // Choix du menu à colorer su jouer par défaut au démarrage, d'où affichage de >Jouer< en rouge.
        game->pause_id=1;
        game->niveau_id=1;
        game->window_id=MENU;
        game->perdu=1;
        game->fruit=0;




}

/*********************************************************************************************************************************************************************************************/

//                                                      FONCTION LIEE AU CALLBACK glutDisplayFunc(display)

/*********************************************************************************************************************************************************************************************/




void display(void){

    if(game->window_id==MENU)    dessiner_menu();  // Choix par défaut à l'initialisation du jeu - Menu

    if(game->window_id==JEU)    dessiner_map();   // Dessiner la map du jeu chargée à partir de mapJeu.txt

    if(game->window_id==REGLES)    dessiner_regles();// Afficher l'écran des règles du jeu

    if(game->window_id==COMMANDES)    dessiner_comm();  // Afficher l'écran des commandes du jeu

    if(game->window_id==PAUSE)      dessiner_pause();

    if(game->window_id==NIVEAU)     dessiner_niveau();

    if(game->window_id==GAGNE)      dessiner_victoire();

    if(game->window_id==SCORES)    dessiner_scores();

}


/*********************************************************************************************************************************************************************************************/

//                                       FONCTION DESSINANT LA MAP DU JEU CONTENUE DANS LE TABLEAU "tableau_jeu[MAXTAB][MAXTAB]"

/*********************************************************************************************************************************************************************************************/



void dessiner_map(void){

int i,j;

    glClear(GL_COLOR_BUFFER_BIT);

    for(i=0;i<MAXTAB;i++){                                  // Dessin de quads sur toutes les valeurs du tableau dont la valeur est de 1
                                                            // Si la valeur est de 0, rien n'est dessiné et la couleur de fond choisie sera alors le noir
        for(j=0;j<MAXTAB;j++){

            if(tableau_jeu[i][j]==1){

                    glLoadIdentity();
                    glRasterPos2i(j*HEIGHT,TAILLE-(i*HEIGHT)-HEIGHT);
                    glDrawPixels(20, 20, GL_BGR, GL_UNSIGNED_BYTE, img_plateforme->tableau);
                    glEnable(GL_BLEND);
                    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                    glColor4f(0,0,0,img_plateforme->alpha);
                    glRectf(0,20, 0, 20);

            }
        }
    }

dessiner_fruits();      // dessiner fruits

dessiner_joueur();      // Dessin du joueur

dessiner_badboy();      // Dessin des ennemis

dessiner_bulle();       // dessiner bulles

infos_jeu();            // affichage à l'écran des informations liées au score et nombre de vies restantes

glutSwapBuffers();

}


/*********************************************************************************************************************************************************************************************/

//                                                      FONCTION DESSINANT L'ECRAN DU menu general

/*********************************************************************************************************************************************************************************************/

void dessiner_menu(void){

 glClear(GL_COLOR_BUFFER_BIT);



    glLoadIdentity();
	glRasterPos2i(0,0);
	glDrawPixels(1000, 1000, GL_BGR, GL_UNSIGNED_BYTE, img_menu->tableau);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(0,0,0,img_menu->alpha);
	glRectf(0,1000, 0, 1000);





        glColor3d(1,1,1); // Texte en blanc                                         // Affichage du menu

        if(game->menu_id==5) glColor3d(1,0,0);
            affiche_caract(455,250,"Quitter",GLUT_BITMAP_TIMES_ROMAN_24);
            glColor3d(1,1,1);
        if(game->menu_id==4) glColor3d(1,0,0);
            affiche_caract(410,350,"Meilleurs scores",GLUT_BITMAP_TIMES_ROMAN_24);
            glColor3d(1,1,1);
        if(game->menu_id==3) glColor3d(1,0,0);
            affiche_caract(465,450,"Regles",GLUT_BITMAP_TIMES_ROMAN_24);
            glColor3d(1,1,1);
        if(game->menu_id==2) glColor3d(1,0,0);
            affiche_caract(430,550,"Commandes",GLUT_BITMAP_TIMES_ROMAN_24);
            glColor3d(1,1,1);
        if(game->menu_id==1) glColor3d(1,0,0);
            affiche_caract(465,650,"Jouer",GLUT_BITMAP_TIMES_ROMAN_24);

            glFlush();

    glutSwapBuffers();

}


void dessiner_regles(void){

 glClear(GL_COLOR_BUFFER_BIT);

    dessiner_fond();

        glColor3d(1,1,1); // Texte en blanc

affiche_caract(440,700,"REGLES",GLUT_BITMAP_TIMES_ROMAN_24);
affiche_caract(432,690,"________",GLUT_BITMAP_TIMES_ROMAN_24);
affiche_caract(30,550,"Le jeu met en scene Bub, un enfant devenu dragon et dont la fiancee a ete enlevee par le Baron von Blubba.",GLUT_BITMAP_HELVETICA_18);
affiche_caract(30,520,"Bub doit gagner le niveau pour la liberer !",GLUT_BITMAP_HELVETICA_18);
affiche_caract(30,460,"Le but du jeu est de ramasser le plus de fruits possible. Ceux-ci apparaissent de maniere aleatoire.  ",GLUT_BITMAP_HELVETICA_18);
affiche_caract(30,430,"Ces fruits ont une valeur de 400 points mais celle-ci diminue en fonction du nombre de monstres encore vivants.  ",GLUT_BITMAP_HELVETICA_18);
affiche_caract(30,400,"Ces monstres evoluent dans ce decor et le but est également de tous les eliminer sans se faire toucher, mais en ayant ",GLUT_BITMAP_HELVETICA_18);
affiche_caract(30,370,"attrape un max de fruits auparavant. La partie se termine lorsque vous avez tue tous les monstres.  ",GLUT_BITMAP_HELVETICA_18);
affiche_caract(30,310,"Pour tuer ceux-ci vous devez lancer des bulles bleues. Lorsqu'elles touchent un ennemi, celui-ci est emprisonne ",GLUT_BITMAP_HELVETICA_18);
affiche_caract(30,280,"dans la bulle qui devient rouge et monte au-dessus de l'ecran. Lorsque vous attrapez la bulle rouge, le monstre meurt. ",GLUT_BITMAP_HELVETICA_18);
affiche_caract(30,250,"Attention, plus le temps passe et plus les monstres se deplacent rapidement.",GLUT_BITMAP_HELVETICA_18);
affiche_caract(30,220,"De plus le nombre de bulles que vous pouvez lancer est limite à 20 ! ",GLUT_BITMAP_HELVETICA_18);
affiche_caract(350,20,"Pour retourner au menu principal, appuyez sur q",GLUT_BITMAP_HELVETICA_12);


    glutSwapBuffers();

}

void dessiner_comm(void){

 glClear(GL_COLOR_BUFFER_BIT);

dessiner_fond();


        glColor3d(1,1,1); // Texte en blanc


affiche_caract(440,700,"COMMANDES",GLUT_BITMAP_TIMES_ROMAN_24);
affiche_caract(432,690,"_____________",GLUT_BITMAP_TIMES_ROMAN_24);
affiche_caract(30,550,"Valider choix menu :                     Enter",GLUT_BITMAP_HELVETICA_18);
affiche_caract(30,520,"Revenir ecran precedent :             q",GLUT_BITMAP_HELVETICA_18);
affiche_caract(30,490,"Se deplacer (gauche et droite) :   touches directionnelles",GLUT_BITMAP_HELVETICA_18);
affiche_caract(30,460,"Se deplacer (sauter) :                    touche directionnelle UP",GLUT_BITMAP_HELVETICA_18);
affiche_caract(30,430,"Lancer bulle:                                  a",GLUT_BITMAP_HELVETICA_18);
affiche_caract(30,400,"Mode Pause:                                 p",GLUT_BITMAP_HELVETICA_18);
affiche_caract(350,20,"Pour retourner au menu principal, appuyez sur q",GLUT_BITMAP_HELVETICA_12);


    glutSwapBuffers();

}


void dessiner_pause(void){


 //glClear(GL_COLOR_BUFFER_BIT);

    glColor3d(1,1,1);

affiche_caract(850,950,"PAUSE", GLUT_BITMAP_HELVETICA_18);




        if(game->pause_id==1) glColor3d(1,0,0);
            affiche_caract(800,930,"Continuer",GLUT_BITMAP_HELVETICA_12);
            glColor3d(1,1,1);
        if(game->pause_id==2) glColor3d(1,0,0);
            affiche_caract(900,930,"Quitter",GLUT_BITMAP_HELVETICA_12);


            glFlush();



glutSwapBuffers();

}




void dessiner_niveau(void){


 glClear(GL_COLOR_BUFFER_BIT);

dessiner_fond();


    glColor3d(1,1,1);

affiche_caract(360,700,"CHOISIR NIVEAU",GLUT_BITMAP_TIMES_ROMAN_24);




        if(game->niveau_id==1) glColor3d(1,0,0);
            affiche_caract(420,550,"FACILE",GLUT_BITMAP_TIMES_ROMAN_24);
            glColor3d(1,1,1);
        if(game->niveau_id==2) glColor3d(1,0,0);
            affiche_caract(370,450,"INTERMEDIAIRE",GLUT_BITMAP_TIMES_ROMAN_24);
            glColor3d(1,1,1);
        if(game->niveau_id==3) glColor3d(1,0,0);
            affiche_caract(410,350,"DIFFICILE",GLUT_BITMAP_TIMES_ROMAN_24);


            glFlush();



glutSwapBuffers();

}

void dessiner_victoire(void){


    if(game->enregistre_score==1 && game->window_id==GAGNE){


        sauve_score(game, top);
        game->enregistre_score=0;


    }



    glClear(GL_COLOR_BUFFER_BIT);

    dessiner_fond();

    glColor3d(1,1,1);

    affiche_caract(360,700,"VOUS AVEZ GAGNE",GLUT_BITMAP_TIMES_ROMAN_24);
    sprintf(top->score,"%i",jeu.score);
    affiche_caract(400,550,top->score,GLUT_BITMAP_TIMES_ROMAN_24);
    affiche_caract(450,550,"points",GLUT_BITMAP_TIMES_ROMAN_24);
    affiche_caract(400,20,"Appuyez sur la touche 'q' pour quitter",GLUT_BITMAP_HELVETICA_12);


    glFlush();



glutSwapBuffers();


}

/*********************************************************************************************************************************************************************************************/

//                                                      FONCTION DESSINANT L'ECRAN DES SCORES

/*********************************************************************************************************************************************************************************************/

void dessiner_scores(void){

 glClear(GL_COLOR_BUFFER_BIT);


    dessiner_fond();



        glColor3d(1,1,1); // Texte en blanc

        affiche_caract(380,700,"MEILLEURS SCORES",GLUT_BITMAP_TIMES_ROMAN_24);

        affiche_top_scores();


    glutSwapBuffers();

}

void affiche_top_scores(void){

int i, posy = 600;
int temp;
char max [10];

    for(i=0;i<MAX_NB_SCORE;i++){

        temp=top->top_scores[i];
        sprintf(max,"%i",temp);                                                                 // sprintf change to fprintf
        affiche_caract(480,posy,max,GLUT_BITMAP_HELVETICA_18);
        posy-=40;
    }

}


void dessiner_fond(void){


    glLoadIdentity();
	glRasterPos2i(0,0);
	glDrawPixels(1000, 1000, GL_BGR, GL_UNSIGNED_BYTE, img_menu->tableau);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(0,0,0,img_menu->alpha);
	glRectf(0,1000, 0, 1000);

}


/*********************************************************************************************************************************************************************************************/

//                                                      FONCTION PERMETTANT D'UTILISER LES TOUCHES FLECHEES

/*********************************************************************************************************************************************************************************************/


void SpecialKeys(int key, int x, int y){

x=x;
y=y;

    switch(key)  {

        case GLUT_KEY_UP:       if(tableau_jeu[(joueur->posy/HEIGHT)+1][joueur->posx/HEIGHT]==1 && joueur->saut==SOL){       // Si on se trouve sur une plateforme et que la touche UP est enclenchée :

                                joueur->vit_vert=-16;                                                   // on donne au joueur une vitesse verticale de -15.

                                }


                                if(game->window_id==MENU){

                                    if(game->menu_id>1) game->menu_id-=1;                   // Attention, ajouter un if pour vérifier que la
                                    else game->menu_id=5;

                                }

                                if(game->window_id==NIVEAU){

                                    if(game->niveau_id>1) game->niveau_id-=1;
                                    else game->niveau_id=3;

                                }

                                break;


        case GLUT_KEY_DOWN:     if(game->window_id==MENU){

                                    if(game->menu_id<5)  game->menu_id+=1;                  // A revoir -> ajouter condition de window-id pour éviter de changer position lorsque l'on est sur une autre fenêtre
                                    else    game->menu_id=1;

                                }

                                if(game->window_id==NIVEAU){

                                    if(game->niveau_id<3) game->niveau_id+=1;
                                    else    game->niveau_id=1;
                                }

                                break;


        case GLUT_KEY_LEFT:     joueur->vit_horiz=-5;
                                last_move=GAUCHE;
                                if(game->pause_id>1) game->pause_id-=1;
                                else game->pause_id=2;

                                break;

        case GLUT_KEY_RIGHT:    joueur->vit_horiz=5;
                                last_move=DROITE;
                                if(game->pause_id<2) game->pause_id+=1;
                                else    game->pause_id=1;
                                break;

    }

}

/*********************************************************************************************************************************************************************************************/

//                                             INITIALISATION DES VARIABLES D'UNE BULLE LANCEE A CHAQUE APPUI SUR LA TOUCHE A

/*********************************************************************************************************************************************************************************************/

void init_bulle(void){


tableau_bubble[game->nb_bulles-1].posx=joueur->posx;                // Valeurs données à la bulle à son initialisation
tableau_bubble[game->nb_bulles-1].posy=joueur->posy;
tableau_bubble[game->nb_bulles-1].vit_vert=3;
tableau_bubble[game->nb_bulles-1].coll=0;
tableau_bubble[game->nb_bulles-1].etat=1;

    if(last_move==GAUCHE){

        tableau_bubble[game->nb_bulles-1].sens_bulle=GAUCHE;        //On donne un sens à la bulle
        tableau_bubble[game->nb_bulles-1].vit_horiz=-3;             //Vitesse horizontale négative si gauche pour ne pas répéter deux fois le même code pour chaque direction

    }
    else{

        tableau_bubble[game->nb_bulles-1].sens_bulle=DROITE;        //idem
        tableau_bubble[game->nb_bulles-1].vit_horiz=3;              //vitesse horizontale positive si vers la droite

    }

}


/*********************************************************************************************************************************************************************************************/

//                                                                      DESSIN DU JOUEUR

/*********************************************************************************************************************************************************************************************/

void dessiner_joueur(void){                         // On donne les valeurs nécessaires à la génération du dessin dans draw_object


    glLoadIdentity();
	glRasterPos2i(joueur->posx,(TAILLE-joueur->posy)-HEIGHT);

        if(last_move==DROITE){

            glDrawPixels(40, 40, GL_BGR, GL_UNSIGNED_BYTE, img_sprite->tableau);
            glEnable(GL_BLEND);
            glAlphaFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);
            glColor4f(0,0,0,img_sprite->alpha);
            glRectf(0,40, 0, 40);

        }

        else{

            glDrawPixels(40, 40, GL_BGR, GL_UNSIGNED_BYTE, img_sprite4->tableau);
            glEnable(GL_BLEND);
            glAlphaFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);
            glColor4f(0,0,0,img_sprite4->alpha);
            glRectf(0,40, 0, 40);

        }

}

/*********************************************************************************************************************************************************************************************/

//                                                                      DESSIN DES ENNEMIS

/*********************************************************************************************************************************************************************************************/
void dessiner_badboy(void){                         // On donne les valeurs nécessaires à la génération du dessin dans draw_object pour tous les ennemis

int i;

    for(i=0;i<game->nb_ennemis;i++){


            if(tableau_badboy[i].etat==1){              // Si vivant il doit être dessiné autrement non

                glLoadIdentity();
                glRasterPos2i(tableau_badboy[i].posx,(TAILLE-tableau_badboy[i].posy)-HEIGHT);



                if(tableau_badboy[i].sens_bb==DROITE){

                glDrawPixels(40, 40, GL_BGR, GL_UNSIGNED_BYTE, img_sprite2->tableau);
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                glColor4f(0,0,0,img_sprite2->alpha);

                }

                else{

                glDrawPixels(40, 40, GL_BGR, GL_UNSIGNED_BYTE, img_sprite6->tableau);
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                glColor4f(0,0,0,img_sprite6->alpha);

                }

            glRectf(0,40, 0, 40);

            }
    }

}

/*********************************************************************************************************************************************************************************************/

//                                                              DESSIN DE LA BULLE

/*********************************************************************************************************************************************************************************************/
void dessiner_bulle(void){                          // On donne les valeurs nécessaires à la génération du dessin dans draw_object pour toutes les bulles

int i;

    for(i=0;i<game->nb_bulles;i++){


        if(tableau_bubble[i].etat==1){

            glLoadIdentity();
            glRasterPos2i(tableau_bubble[i].posx,(TAILLE-tableau_bubble[i].posy)-HEIGHT);


                if(tableau_bubble[i].coll==0){

                    glDrawPixels(40, 40, GL_BGR, GL_UNSIGNED_BYTE, img_sprite3->tableau);
                    glEnable(GL_BLEND);
                    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                    glColor4f(0,0,0,img_sprite3->alpha);
                }

                else{

                    glDrawPixels(40, 40, GL_BGR, GL_UNSIGNED_BYTE, img_sprite5->tableau);
                    glEnable(GL_BLEND);
                    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                    glColor4f(0,0,0,img_sprite5->alpha);
                }

                glRectf(0,40, 0, 40);
        }
    }
}

/*********************************************************************************************************************************************************************************************/

//                                                      FONCTION QUI DESSINE LES FRUITS DE MANIERE ALEATOIRE

/*********************************************************************************************************************************************************************************************/

void dessiner_fruits(void){

int x,y,ran;
bool vivants;   // variable dont la valeur correspond à la valeur de retour de la fonction compteur_bb_vivants afin de signaler s'il y a encoredes ennemis vivants sur le tableau de jeu


vivants=compteur_bb_vivants(game, tableau_badboy);



    if(img_sprite7->etat==0 && img_sprite8->etat==0 && img_sprite9->etat==0){               // Si aucun fruit n'est affiché à l'écran, on va en afficher un


        do{


            x=rand()%50;                                                                    // Calcul d'une position x et y aléatoire, de nouvelles positions seront générées tant que x et y ne respecteront
            y=rand()%50;                                                                    // pas les conditions établies dans la boucle do-while


        }while(y<9 || y>MAXTAB-2 || x<1 || x>MAXTAB-3 || tableau_jeu[x][y]==1);






    ran=rand()%50;                                                                          // On choisi une variable dont la valeur est aléatoire entre 0 et 49 grâce à random.

        if      (ran%3==0 && vivants==true){

            img_sprite7->posx=x*HEIGHT;
            img_sprite7->posy=y*HEIGHT;
            img_sprite7->etat=1;

        }                                             // On effectue un modulo 3 sur 'ran' afin de choisir l'affichage d'un des trois fruits
        else if (ran%3==1 && vivants==true){

            img_sprite8->posx=x*HEIGHT;
            img_sprite8->posy=y*HEIGHT;
            img_sprite8->etat=1;

        }
        else{

            if(vivants==true){

            img_sprite9->posx=x*HEIGHT;
            img_sprite9->posy=y*HEIGHT;
            img_sprite9->etat=1;

            }
        }
    }

        if(img_sprite7->etat==1){                                               // Affichage des sprites


            glLoadIdentity();
            glRasterPos2i(img_sprite7->posx,TAILLE-img_sprite7->posy);
            glDrawPixels(40, 40, GL_BGR, GL_UNSIGNED_BYTE, img_sprite7->tableau);
            glEnable(GL_BLEND);
            glAlphaFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);
            glColor4f(0,0,0,img_sprite7->alpha);
            glRectf(0,40, 0, 40);

        }


        if(img_sprite8->etat==1){

            glLoadIdentity();
            glRasterPos2i(img_sprite8->posx,TAILLE-img_sprite8->posy);
            glDrawPixels(40, 40, GL_BGR, GL_UNSIGNED_BYTE, img_sprite8->tableau);
            glEnable(GL_BLEND);
            glAlphaFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);
            glColor4f(0,0,0,img_sprite8->alpha);
            glRectf(0,40, 0, 40);

        }


        if(img_sprite9->etat==1){

            glLoadIdentity();
            glRasterPos2i(img_sprite9->posx,TAILLE-img_sprite9->posy);
            glDrawPixels(40, 40, GL_BGR, GL_UNSIGNED_BYTE, img_sprite9->tableau);
            glEnable(GL_BLEND);
            glAlphaFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);
            glColor4f(0,0,0,img_sprite9->alpha);
            glRectf(0,40, 0, 40);

        }


}

/*********************************************************************************************************************************************************************************************/

//                                        FONCTION DESSINANT LE TEXTE POUR LE SCORE ET LES VIES RESTANTES DANS L'ECRAN DU JEU

/*********************************************************************************************************************************************************************************************/


void infos_jeu(void){

    lecture_score(top);
    glColor3d(1,1,1); // Texte en blanc
    affiche_caract(10,980,"Vies: ",GLUT_BITMAP_HELVETICA_18);                            // Cette fonction prend en paramètres les positions x et y de l'affichage, un pointeur sur une chaîne de caractères
	affiche_caract(800,980,"Meilleur score: ",GLUT_BITMAP_HELVETICA_18);                  // à aficher et un pointeur sur la police utilisée.
    sprintf(top->record,"%i",top->top_scores[0]);
    affiche_caract(930,980,top->record,GLUT_BITMAP_HELVETICA_18);




	affiche_caract(400,980,"Score: ",GLUT_BITMAP_HELVETICA_18);
	sprintf(top->score,"%i",jeu.score);
	affiche_caract(500,980,top->score,GLUT_BITMAP_HELVETICA_18);

        switch(game->vies){                                                     // Affichage du nombre de vies restantes

            case 0: affiche_caract(80,980,"0",GLUT_BITMAP_HELVETICA_18);
                    break;
            case 1: affiche_caract(80,980,"1",GLUT_BITMAP_HELVETICA_18);
                    break;
            case 2: affiche_caract(80,980,"2",GLUT_BITMAP_HELVETICA_18);
                    break;
            case 3: affiche_caract(80,980,"3",GLUT_BITMAP_HELVETICA_18);
                    break;
            default : break;
        }

        if(game->nb_bulles!=MAXBUBBLE){

            affiche_caract(10,920,"BULLES RESTANTES:",GLUT_BITMAP_HELVETICA_12);
            sprintf(game->bull_rest,"%i",MAXBUBBLE-(game->nb_bulles));
            affiche_caract(150,920,game->bull_rest,GLUT_BITMAP_HELVETICA_12);

        }
        else    affiche_caract(10,920,"PLUS DE BULLES",GLUT_BITMAP_HELVETICA_18);       // On affiche à l'utilisateur qu'il n'a plus de bulles si le quota est atteint

        if(game->perdu==0 && game->vies !=0)  affiche_caract(420,920,"PERDU",GLUT_BITMAP_HELVETICA_18);      // On affiche perdu si encore des vies
        if(game->vies==0)   affiche_caract(390,920,"GAME OVER",GLUT_BITMAP_HELVETICA_18);                    // Si on en est à 0 vies


	glFlush();

}

/*********************************************************************************************************************************************************************************************/

//                                                          FONCTION CALLBACK TOUCHES CLAVIER

/*********************************************************************************************************************************************************************************************/
void Clavier(unsigned char key, int x, int y){

x=x;
y=y;

  switch(key) {

    case 'q': if(game->window_id==MENU)  exit(0) ; // q => « quitter »
              else if(game->window_id==GAGNE)   game->window_id=SCORES;
              else if(game->window_id==JEU)     init_all(1);
              else if(game->window_id==SCORES)   init_all(1);
              else  game->window_id=MENU;           // si on était pas sur le menu principal on y revient

              break;

    case 'a':   if(game->nb_bulles<MAXBUBBLE){    // si on a pas atteint le maximum de bulles

                    game->nb_bulles+=1;             // on ajoute 1 au nombre de bulles lancées
                    init_bulle();                   // on lance la fonction init_bulle() qui va initier les valeurs de la structure bulle

                }

              game->pos_init=1;
              break;

    case 'p': if(game->window_id==JEU)  game->window_id=PAUSE;
                printf("%i\n",jeu.score);

                break;

    case 13:    if(game->window_id==NIVEAU){                    // A placer avant le test de la fenêtre menu, autrement ce test ne sera pas effectué

                init_niveau();


                game->window_id=JEU;
              }

                if(game->window_id==MENU){           // Si l'on est sur la page du menu principal

                if(game->menu_id==5)  exit(0);  // en fonction du choix effectué dans le menu, on affiche un autre écran ou on quitte
                if(game->menu_id==1)    game->window_id=NIVEAU;
                if(game->menu_id==3)  game->window_id=REGLES;
                if(game->menu_id==2)  game->window_id=COMMANDES;
                if(game->menu_id==4){

                    lecture_score(top);
                    game->window_id=SCORES;

                }

              }

              if(game->window_id==PAUSE){

                if(game->pause_id==1)   game->window_id=JEU;
                else game->window_id=MENU;

              }

              break;

    default: break;
 }

  glutPostRedisplay();	// Affichage - Mise à jour
}

/*********************************************************************************************************************************************************************************************/

//                                                  FONCTION TIMER - UPDATE DES POSITIONS DES OBJETS

/*********************************************************************************************************************************************************************************************/

void Timer(int no){

no=no;

// Code pour effectuer un saut

if(game->perdu==1 && game->window_id==2){                               // Si le joueur n'a pas perdu et que l'on est sur la fenêtre de la map du jeu

saut(joueur,tableau_jeu);

// Code pour effectuer un déplacement sur la droite ou sur la gauche

leftright(joueur,last_move);

// Code pour le déplacement d'une bulle

depl_bulle(tableau_bubble, tableau_badboy);

// Code pour le déplacement des ennemis

depl_badboy(tableau_jeu, game, joueur, tableau_badboy);

}

test_victoire( tableau_badboy, tableau_bubble, game);


glutPostRedisplay();

glutTimerFunc(DELAY,Timer,0);                                       // Actualisation de l'affichage via la fonction Timer après un temps'DELAY' exprimé en ms (DELAY défini dans constantes.h

}


/*********************************************************************************************************************************************************************************************/

//                                                      FONCTION DE TYPE TIMER POUR GERER LE TEMPS D'ATTENTE LORSQU'UNE VIE EST PERDUE

/*********************************************************************************************************************************************************************************************/

void attente(int no){

no=no;

    if(game->perdu==0){


        if(game->vies!=0){

            init_all(0);
            game->window_id=2;

        }
        else{

            if(game->window_id==JEU){

                game->window_id=MENU;      // si on est sur l'écran de jeu et que l'on a perdu (nb_vies = 0), alors on revient à l'écran du menu

                init_all(1);

            }

        }

    }


glutPostRedisplay();

glutTimerFunc(DELAY2,attente,1);

}

/*********************************************************************************************************************************************************************************************/

//                                                      FONCTION RESHAPE

/*********************************************************************************************************************************************************************************************/
void reshape(int w, int h){

    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,w,0,h,-w,w);
	glMatrixMode(GL_MODELVIEW);

}

/*********************************************************************************************************************************************************************************************/

//                                                      FONCTION PERMETTANT LE TEST DE COLLISION ENTRE LE JOUEUR ET UN ENNEMI

/*********************************************************************************************************************************************************************************************/
void collision_player(player *joueur, BadBoy tableau_badboy[game->nb_ennemis]){

int i;

    for(i=0;i<game->nb_ennemis;i++){

        if(tableau_badboy[i].etat==1){


          if((abs(joueur->posy-tableau_badboy[i].posy))<(2*HEIGHT/2)){

            if((abs(joueur->posx-tableau_badboy[i].posx))<(2*HEIGHT/2)){

                game->vies-=1;
                game->perdu=0;
                                                                              // attention initier variable avant pour valeu
            }
          }
        }
    }
}
/*********************************************************************************************************************************************************************************************/

//                                                  FONCTION PERMETTANT LE TEST DE COLLISION ENTRE UNE BULLE ET UN ENNEMI

/*********************************************************************************************************************************************************************************************/

void collision_bubble(BadBoy tableau_badboy[game->nb_ennemis], Bulle tableau_bubble[MAXBUBBLE], int i){

int k;

    for(k=0;k<game->nb_ennemis && tableau_bubble[i].coll==0;k++){

        if(tableau_badboy[k].etat==1){

            if(abs(tableau_bubble[i].posx-tableau_badboy[k].posx)<(2*HEIGHT) && abs(tableau_bubble[i].posy-tableau_badboy[k].posy)<(2*HEIGHT)){

                tableau_bubble[i].coll=1;       // l'état de collision de la bulle passe à 1 -> elle devient rouge et monte jusqu'au dessus du plateau de jeu

                game->score+=50;        // points gagnés lorsque l'on touche un ennemi avec une bulle.

                tableau_badboy[k].etat=0;       // l'ennemi est mort

                tableau_badboy[k].vit_horiz=0;
            }
        }
    }
}
/*********************************************************************************************************************************************************************************************/

//                                                     FONCTION APPELEE LORSQUE LE JOUEUR MANGE UNE BULLE AVEC UN ENNEMI EMPRISONNE DEDANS

/*********************************************************************************************************************************************************************************************/

void attrape_bubble(Bulle tableau_bubble[MAXBUBBLE]){

int i;

    for(i=0;i<MAXBUBBLE;i++){

        if(tableau_bubble[i].coll==1){

            if(abs(tableau_bubble[i].posx-joueur->posx)<HEIGHT && abs(tableau_bubble[i].posy-joueur->posy)<HEIGHT){

                if(tableau_bubble[i].etat==1){

                    game->score+=100;                   // ajout de 100 au score du joueur si celui-ci mange une bulle avec un ennemi emprisonné
                    game->fruit+=1;                     // nbre de fruites mangés

                }

                tableau_bubble[i].etat=0;
            }

        }
    }
}

/*********************************************************************************************************************************************************************************************/

//                                                      FONCTION APPELEE LORSQU'UN FRUIT EST ATTRAPE PAR LE JOUEUR

/*********************************************************************************************************************************************************************************************/
void attrape_fruit(player *joueur){





    if(img_sprite7->etat==1){

        if(abs(img_sprite7->posx-joueur->posx)<2*HEIGHT && abs(img_sprite7->posy-joueur->posy)<2*HEIGHT){

            img_sprite7->etat=0;
            game->score+=game->val_fruit;
        }

    }


    if(img_sprite8->etat==1){

        if(abs(img_sprite8->posx-joueur->posx)<2*HEIGHT && abs(img_sprite8->posy-joueur->posy)<2*HEIGHT){

            img_sprite8->etat=0;
            game->score+=game->val_fruit;
        }

    }

    if(img_sprite9->etat==1){

        if(abs(img_sprite9->posx-joueur->posx)<2*HEIGHT && abs(img_sprite9->posy-joueur->posy)<2*HEIGHT){

            img_sprite9->etat=0;
            game->score+=game->val_fruit;
        }

    }


}

/*********************************************************************************************************************************************************************************************/

//                                                      FONCTION D'INITIALISATION DES VALEURS EN FONCTION DU NIVEAU DE DIFFICULTE CHOISI

/*********************************************************************************************************************************************************************************************/
void init_niveau(void){

int vit, i;

    switch(game->niveau_id){


        case 1: vit=2;
                game->nb_ennemis=MAXENNEMIES-4;
                break;
        case 2: vit=3;
                game->nb_ennemis=MAXENNEMIES-2;
                break;
        case 3: vit=5;
                game->nb_ennemis=MAXENNEMIES;
                break;
        default: break;

    }


    for(i=0; i<(game->nb_ennemis); i++){

        tableau_badboy[i].vit_horiz=vit;
        tableau_badboy[i].pos=SOL;
        tableau_badboy[i].etat=1;
        tableau_badboy[i].posx=game->x+i*HEIGHT;            // position et vitesse de déplacement des ennemis avec déclage de position entre chaque ennemi
        tableau_badboy[i].posy=game->y+i*7*HEIGHT;
    }

}


