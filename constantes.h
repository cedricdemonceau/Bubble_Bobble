#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED

/*------------Les constantes-----------------------------------------------------------------------------------------------------------------------------------*/

#define MAXTAB 50           // nbre de lignes et de colonnes du tableau
#define NB_VIES_MAX 3       // nbre de vie initialisé à 3 au début du jeu
#define MAXPSEUDO 3         // nbre de caractères MAX du pseudo pour les meilleurs scores
#define DELAY 20            // délai de rafraîchissment en milisecondes
#define DELAY2 3000         // délai pour la fonction 'attente'
#define TAILLE 1000         // hauteur et largeur en pixels de la fentre du jeu (fenêtre carrée)
#define NB_BAD_BOY 4        // nbre d'ennemis
#define HEIGHT 20           // taille d'une case du tableau en pixels
#define NB_VAL_TAB 2500     // nbre d'éléments requis pour remplir le tableau
#define MAXBUBBLE 20        // nbre maximum de bulles disponibles
#define MAXENNEMIES 7       // nbre maximum d'ennemis
#define RGB 3               // valeur max du tableau tab_color représentant les couleurs RGB utilisées dans la fonction glColor
#define NB_SPRITES 9        // nbre de sprites à charger au début du jeu
#define MAX_NB_SCORE 10     // nbre de chiffres maximum pour le score
/*-----------Definitions structures----------------------------------------------------------------------------------------------------------------------------*/

typedef struct {                                        // structure player correspondant au joueur
    int posx;                                   // position horizontale joueur
    int posy;                                   // position verticale joueur
    int vit_vert;                               // vitesse verticale
    int vit_horiz;                              // vitesse horizontale
    int nb_vies;                                // nombre de vies du joueur
    int score;                                  // score en cours du joueur
    int saut;                                   // savoir si position AIR ou SOL

}player;

player p1;                                      // création d'une structure player portant le nom de p1


typedef struct {                                        // structure Badboy correspondant aux ennemis

    int posx;                                   // position horizontale ennemi
    int posy;                                   // position verticale ennemi
    int vit_vert;                               // vitesse verticale ennemi
    int vit_horiz;                              // vitesse horizontale ennemi
    int sens_bb;                                // sens vers lequel doit se déplacer l'ennemi
    int etat;                                   // 0 = mort - 1 = vivant
    int pos;                                    // savoir si position AIR ou SOL

}BadBoy;


typedef struct {                                       // structure des bulles lancées par le joueur

    int posx;                                   // position horizontale d'une bulle
    int posy;                                   // position verticale d'une bulle
    int vit_vert;                               // vitesse verticale d'une bulle
    int vit_horiz;                              // vitesse horizontale d'une bulle
    int sens_bulle;                             // sens vers lequel doit se déplacer la bulle
    int coll;                                   // collision avec ennemi - valeur à 0 si pas de collision et 1 si collision
    int etat;                                   // 1 = doit être dessinée - 0 = disparaît de l'écran

}Bulle;

typedef struct {                                        // structure contenant toutes les données nécessaires au bon fonctionnement du jeu

    int pos_init;                               // position initiale
    int nb_bulles;                              // nombre de bulles déjà lancées
    int x;                                      // position horizontale de départ du premier ennemi
    int y;                                      // position verticale de départ du premier ennemi
    int menu_id;                                // valeur représentant l'élément choisi dans le menu
    int window_id;                              // valeur représentant l'écran qui doit être affiché
    int score;                                  // score
    int vies;                                   // vies
    int compt_actu;                             // compteur qui servira à la mise à joueur des ennemis par rapport  au joueur dans la fonction depl_badboy appelée dans le Timer
    int perdu;
    int pause_id;
    int niveau_id;                              // 0 = facile - 1 = intermédiaire - 2 = difficile
    char bull_rest[2];                          // tableau de char pour afficher le nombre de bulles restantes
    int fruit;                                  // nb de fruits déjà distribués
    int enregistre_score;                       // Savoir si l'on doit enregister le score 0 = NON, 1 = OUI
    int nb_ennemis;                             // nombre  d'ennemis en fonction du choix du niveau
    int val_fruit;                              // valeur du fruit attrapé qui va varier en fonction du nombre d'ennemis encore vivants

}jeuO;

jeuO jeu;                                       // Création d'une structure jeuO portant le nom de jeu


typedef struct{

	int debut_tableau;
	unsigned char tableau[1000][1000][3]; //450-459-3
	float alpha;

} image;

image img;

typedef struct{                                 // structure des sprites

	int debut_tableau;
	unsigned char tableau[40][40][3]; //450-459-3
	float alpha;
	int posx;
	int posy;
	int etat;
	int coll;

} sprite;

sprite bubble;
sprite bubble_left;
sprite ennemies;
sprite ennemies_left;
sprite bulle;
sprite bulle_rouge;
sprite fraise;
sprite orange;
sprite pasteque;

typedef struct{                                 // structure concernant les scores

int top_scores[MAX_NB_SCORE];
char score[10];
char record[10];

}scores;

scores meill_score;


typedef struct{                                  // structure pour la texture des plateformes

	int debut_tableau;
	unsigned char tableau[20][20][3]; //450-459-3
	float alpha;

} plateforme;

plateforme mur;

                                                // Début des énumérations permettant une lecture plus aisée du code
typedef enum{                                   // énumération permettant plus de clarté pour identifier si un objet est en l'ai ou au sol

    AIR,
    SOL
}position;

typedef enum{                                   //utilisé dans les structure pour définir le sens des objets

    GAUCHE,
    DROITE,

}last_movement;

last_movement last_move;                        // enregistre le dernier mouvement  effectué (gauche ou droite)


typedef enum{                                   // représente les différentes fenêtres du jeu

    EXIT,
    MENU,
    JEU,
    REGLES,
    COMMANDES,
    SCORES,
    PAUSE,
    NIVEAU,
    GAGNE,

}window;

typedef enum{                                   // représente les niveaux de difficulté du jeu

    FACILE,
    INTERMEDIAIRE,
    DIFFICILE,

}level;


/*----------------Initialisation tableau de jeu (variables globales)-------------------------------------------------------------------------------------------*/

int num_bulle_col;
int tableau_jeu[MAXTAB][MAXTAB];                // tableau de la map du jeu (matrice carrée de MAXTAB)
Bulle tableau_bubble[MAXBUBBLE];                // tableau contenant des structures de type Bulle (le maximum MABUBBLE correspond au nombre maximum de bulles disponibles)
BadBoy tableau_badboy[MAXENNEMIES];             // tableau contenant des structures de type BadBoy(le maximum MAXENNEMIES correspond au nombre maximum d'ennemis dans la partie)


#endif // CONSTANTES_H_INCLUDED
