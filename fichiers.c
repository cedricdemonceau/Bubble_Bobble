#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXTAB 50
#define NB_VAL_TAB 2500     // nbre d'éléments requis pour remplir le tableau
#include "constantes.h"
#include "fichiers.h"
/*********************************************************************************************************************************************************************************************/

//                                                      AFFICHAGE DE CARACTERES A L'ECRAN

/*********************************************************************************************************************************************************************************************/


void affiche_caract(int x, int y, char *chaine, void *police){
	int long_chaine,i;                                                          // len donne la longueur de la chaîne de caractères
	glRasterPos2f(x,y);                                                         // Positionne le premier caractère de la chaîne
	long_chaine = strlen(chaine);                                               // Calcule la longueur de la chaîne
	for (i = 0; i < long_chaine; i++) glutBitmapCharacter(police,chaine[i]);    // Affiche chaque caractère de la chaîne
}

/*********************************************************************************************************************************************************************************************/

//                                                FONCTION CHARGEFICHIER - CHARGEMENT DU FICHIER TEXTE CONTENANT LA MAP DE JEU

/*********************************************************************************************************************************************************************************************/

void chargeFichier(int tableau_jeu[MAXTAB][MAXTAB]){

FILE *fp;       //Création pointeur vers le fichier

int i=0;        //compteur lignes
int j=0;        //compteur colonnes
int n=0;        //nb de valeurs dans le tableau


fp=fopen("mapJeu.txt","rt");    //Ouverture du fichier en mode lecture


    if(fp==NULL){   //Gestion d'erreur

        puts("Erreur d'ouverture de fichier:");
        puts("Fichier inexistant ou permissions insuffisantes");
        exit(1);                                                    // Termine le programme avec le code erreur 1

    }

    while(i < MAXTAB && fscanf(fp, "%d", &tableau_jeu[i][j])==1){   //fscan va retourner la valeur de 1 si la valeur a pu être récupérée

        n++;    // compteur du nombre de valeurs récupérées

            if(j==(MAXTAB-1)){  // si on se trouve à la dernière colonne

                i++;            // on passe à la ligne suivante
                j=0;            // on donne la valeur 0 à la colonne pour recommencer la lecture de la ligne
            }

            else    j++;        // sinon, on continue la ligne et on incrémente j (colonne)

    }

    fclose(fp);         // Fermeture du fichier


    if(n!=NB_VAL_TAB){ // Gestion d'erreur

        puts("Erreur, le nombre d'éléments du fichier n'a pas permis de remplir le tableau."); // Si le nombre de valeurs récupérées n'est pas de 2500 (50*50)
        puts("Données manquantes");
        exit(1);
    }
}

/*********************************************************************************************************************************************************************************************/

//                                                          CHOIX DU SPRITE A CHARGER

/*********************************************************************************************************************************************************************************************/

void charger_sprites(char fich[30],sprite *img_sprite,sprite *img_sprite2,sprite *img_sprite3,sprite *img_sprite4,sprite *img_sprite5,sprite *img_sprite6,sprite *img_sprite7,sprite *img_sprite8,sprite *img_sprite9){

int i;

            for(i=0;i<NB_SPRITES;i++){

                switch(i){

                case 0: strcpy(fich,"new_bubble.bmp");
                        load_sprite(img_sprite,fich);
                        break;

                case 1: strcpy(fich,"badboy_right.bmp");
                        load_sprite(img_sprite2,fich);
                        break;

                case 2: strcpy(fich,"bulle.bmp");
                        load_sprite(img_sprite3,fich);
                        break;

                case 3: strcpy(fich,"new_bubble_left.bmp");
                        load_sprite(img_sprite4,fich);
                        break;

                case 4: strcpy(fich,"bulle_rouge.bmp");
                        load_sprite(img_sprite5,fich);
                        break;

                case 5: strcpy(fich,"badboy_left.bmp");
                        load_sprite(img_sprite6,fich);
                        break;

                case 6: strcpy(fich,"fraise.bmp");
                        load_sprite(img_sprite7,fich);
                        break;

                case 7: strcpy(fich,"orange.bmp");
                        load_sprite(img_sprite8,fich);
                        break;

                case 8: strcpy(fich,"pasteque.bmp");
                        load_sprite(img_sprite9,fich);
                        break;

                default: break;
            }
        }
}

/*********************************************************************************************************************************************************************************************/

//                                                      FONCTION CHARGEMENT DE L'IMAGE DE FOND

/*********************************************************************************************************************************************************************************************/

void load_interface(image *img_menu){

//cette fonction charge une image d'interface nommee "interface.bmp"
	int x, y, couleur; //position x,y dans le tableau rgb 450x459
	FILE *lecteur;
	lecteur = fopen("fond.bmp", "r");
	if(lecteur==NULL) {printf("impossible d'ouvrir le fichier\n"); exit(1);}
	fseek(lecteur,10,0);
	fread(&img_menu->debut_tableau, 4, 1, lecteur);
	fseek(lecteur,img_menu->debut_tableau,0);
	for(x=0; x<1000; x++)
	{
		for(y=0; y<1000; y++)
		{
			for(couleur=0; couleur<3; couleur++)
			{
				fread(&img_menu->tableau[x][y][couleur], 1, 1, lecteur);
			}
		}
	}
	img_menu->alpha=0;
}

/*********************************************************************************************************************************************************************************************/

//                                                FONCTION CHARGEMENT DES SPRITES

/*********************************************************************************************************************************************************************************************/

void load_sprite(sprite *img_sprite, char fich[]){

	int x, y, couleur; //position x,y dans le tableau rgb 450x459
	FILE *lecteur;
	lecteur = fopen(fich, "r");
	if(lecteur==NULL) {printf("impossible d'ouvrir le fichier\n"); exit(1);}
	fseek(lecteur,10,0);
	fread(&img_sprite->debut_tableau, 4, 1, lecteur);
	fseek(lecteur,img_sprite->debut_tableau,0);
	for(x=0; x<40; x++)
	{
		for(y=0; y<40; y++)
		{
			for(couleur=0; couleur<3; couleur++)
			{
				fread(&img_sprite->tableau[x][y][couleur], 1, 1, lecteur);
			}
		}
	}
	img_sprite->alpha=0;

}

/*********************************************************************************************************************************************************************************************/

//                                                FONCTION CHARGEMENT DE LA TEXTURE POUR LES PLATEFORMES

/*********************************************************************************************************************************************************************************************/

void load_plateforme(plateforme *img_plateforme){

//cette fonction charge une image nommée "plateforme.bmp"
	int x, y, couleur;
	FILE *lecteur;
	lecteur = fopen("plateforme.bmp", "r");
	if(lecteur==NULL) {printf("impossible d'ouvrir le fichier\n"); exit(1);}
	fseek(lecteur,10,0);
	fread(&img_plateforme->debut_tableau, 4, 1, lecteur);
	fseek(lecteur,img_plateforme->debut_tableau,0);
	for(x=0; x<20; x++)
	{
		for(y=0; y<20; y++)
		{
			for(couleur=0; couleur<3; couleur++)
			{
				fread(&img_plateforme->tableau[x][y][couleur], 1, 1, lecteur);
			}
		}
	}
	img_plateforme->alpha=0;
}
