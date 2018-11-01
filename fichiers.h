#ifndef FICHIERS_H_INCLUDED
#define FICHIERS_H_INCLUDED

void chargeFichier(int tableau_jeu[MAXTAB][MAXTAB]);
void affiche_caract(int x, int y, char *chaine, void *police);
void load_interface(image *img_menu);
void load_sprite(sprite *img_sprite, char fich[]);
void load_plateforme(plateforme *img_plateforme);
void charger_sprites(char fich[],sprite *img_sprite,sprite *img_sprite2,sprite *img_sprite3,sprite *img_sprite4,sprite *img_sprite5,sprite *img_sprite6,sprite *img_sprite7,sprite *img_sprite8,sprite *img_sprite9);

#endif // FICHIERS_H_INCLUDED
