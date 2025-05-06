CC=gcc
SRC=$(wildcard*.c)
OBJ=$(SRC:.c=.o)
all:projet

projet:$(OBJ)
        $(CC).$^-o$@
%.o:%.c
        $(CC)-c$<-o$@
