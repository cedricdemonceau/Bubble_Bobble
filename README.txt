Projet d'un jeu 2d "Bubble Bobble"

J'ai réalisé ce projet dans le cadre de ma première année de BAC universitaire en Sciences informatiques.

Le jeu avait pour contrainte de devoir être codé en 'C' avec OPENGL et GLUT pour la partie graphique.


Le but du jeu est de ramasser des fruits qui apparaissent 1 à 1 sur l'écran. Pour ce faire, 'Bubble' se déplace
sur l'écran grâce aux touches flèchées du clavier. Des ennemis se lancent à la poursuite de 'Bubble' afin de le manger,
ce qui lui complique la tâche. Le nombre d'ennemis et leur vitesse dépend du niveau de difficulté choisi (Facile-Moyen-Difficile).

Plus le temps passe et plus les ennemis se déplacent rapidement. Le nombre de point acquis lorsque 'Bubble' mange un fruit dépend
du nombre d'ennemis encore en vie. Plus il y a d'ennemis en vie, plus les gains sont importants.

Pour tuer ses ennemis, 'Bubble' doit lancer des bulles qui vont emprisonner les ennemis et les faire monter sur le dessus du plateau
de jeu. 'Bubble' doit alors manger les bulles. Les bulles sont bleues lorsqu'elles sont lancées et rouges lorsq'un ennemi est emprisonné
à l'intérieur.

Le jeu se termine lorsque tous les ennemis sont mangés par 'Bubble'.



Le programme est divisé en plusieurs fichiers:

- main.c qui est exécuté au lancement du jeu et permet l'ouverture de la première fenêtre graphique
- affichage.c qui gère toutes les mises à jour de l'affichage grâce aux fonctions GLUT
- jeu.c qui gère toutes les fonctions liées aux mises à jour des variables des joueurs et des ennemis sur le plateau de jeu
- scores.c qui gère les fonctions liées aux scores
- fichier.c qui gère les accès aux fichiers, notamment pour la sauvegarde et la récupration des meilleurs score à l'ouverture et la fermeture du programme.

Le fichier 'constantes.h' contient quant à lui toutes les déclarations de constantes, énumérations et structures utilisées dans ce jeu.

Toutes les formes graphiques ont été crées grâce au concept du PixelArt.

Le jeu, après récupération du repository, peut être compilé grâce au Makefile (make bubble_bobble)
