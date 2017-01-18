CC=gcc
CFLAGS=
LDFLAGS= -lm -std=c99 -ansi
EXEC=main
EXEC_INDEX = index
EXEC_TEST=test_pile
DIREXEC=./Exec/
DIRSRC=./Src/
DIRTEST=./Test/
SRC=$(DIRSRC)Interface/interfaceMoteur.c $(wildcard ./Src/Indexation/*.c)
OBJS=$(SRC:.c=.o)
SRC_INDEXATION=$(wildcard ./Src/Indexation/*.c)
OBJS_INDEXATION=$(SRC_INDEXATION:.c=.o)
SRC_TEST=$(DIRTEST)test_pileDescripteur.c $(wildcard ./Src/*.c)
OBJS_TEST=$(SRC_TEST:.c=.o)

all: clean  $(EXEC)
	mv ./$(EXEC) $(DIREXEC)

test_pile :$(OBJS_TEST)
	$(CC) -o $@ $^ $(LDFLAGS)

index: $(OBJS_INDEXATION)
	$(CC) -o $@ $^ $(LDFLAGS)

main: $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
		rm -rf *.o

mrproper: clean
		rm -rf $(EXEC)
