CC=gcc
CFLAGS= -std=c99 -lm -W -Wall -ansi -pedantic
LDFLAGS=
EXEC=main
DIREXEC=./Exec/
DIRSRC=./Src/
SRC=$(wildcard ./Src/*.c)
OBJS=$(SRC:.c=.o)


all: clean $(EXEC)
	mv ./$(EXEC) $(DIREXEC)

main: $(OBJS)
			$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c %.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
		rm -rf *.o

mrproper: clean
		rm -rf $(EXEC)
