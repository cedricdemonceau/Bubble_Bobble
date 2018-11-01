CC=gcc
CFLAGS=-W -Wall -pedantic
LIBS=-lGL -lGLU -lglut -lm -lXxf86vm
LDFLAGS=
EXEC=bubble_bobble

all: $(EXEC)

bubble_bobble: main.o affichage.o fichiers.o jeu.o scores.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)

main.o: main.c affichage.h
	$(CC) -o $@ -c $< $(CFLAGS)

affichage.o: affichage.c affichage.h jeu.h constantes.h fichiers.h
	$(CC) -o $@ -c $< $(CFLAGS)

fichiers.o: fichiers.c fichiers.h
	$(CC) -o $@ -c $< $(CFLAGS)

scores.o: scores.c scores.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
