#nom de l'executable
EXEC = operation_flocon

#fichier source
SRCS = main.c fonctions.c interface_utilisateur.c

#fichier objets
OBJS = $(SRCS:.c=.o)

#le compilateur
CC=gcc

#option de compilation
CFLAGS = -Wall -Wextra -std=c11

all: $(EXEC)

$(EXEC): $(OBJS) fonctions.h
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)

#nettoyage des fichiers objets
clean:
	rm -f $(OBJS) $(EXEC)

#force la recompilation complete
rebuild: clean all
