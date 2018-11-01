#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>
#include <time.h>
#include "affichage.h"

/*********************************************************************************************************************************************************************************************/

//                                                  FONCTION MAIN - initialisation de glut et création d'une fenêtre

/*********************************************************************************************************************************************************************************************/


int main(int argc, char *argv[]){

srand(time(NULL));

    int first_time=1;

  glutInit(&argc, argv); 			       // initialise GLUT
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE); 	// On travaille en RGBA - Double buffer pour éviter le probème de scintillement
  glutInitWindowSize(1000,1000);   	    // taille de la fenêtre
  glutInitWindowPosition(50,0);
  glutCreateWindow("Bubble Bobble");    // Nom de la fenêtre

  glClearColor(0, 0, 0, 0); 	        // Noir
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0,1000,0,1000);		// vue en ortho 2d de 0 à 1000 pixels en largeur comme en hauteur

  glutDisplayFunc(display); 		// Callback de la fenêtre
  glutKeyboardFunc(Clavier); 		// Callback du clavier
  glutSpecialFunc(SpecialKeys);     // Callback du clavier (caractères spéciaux)
  glutTimerFunc(DELAY,Timer,0);     // La fonction Timer qui permettra de mettre à jour, dans un délai en ms (DELAY), l'affichage des différents objets sur la map de jeu
  glutTimerFunc(DELAY2,attente,1);
  glutReshapeFunc(reshape);



      if(first_time) {

      init_all(first_time);                   // lancement de la fonction init_all contenue dans affichage.c et donnant aux variables concernées dans cette fonction les valeurs nécessaires au démarrage du jeu
      first_time=0;

      }

  glutMainLoop();					// Boucle infinie

  /* Le programme n'atteint jamais ce point */

  return 0;
}
