CC=gcc
CFLAGS= -std=c99 -lm -W -Wall -ansi -pedantic
LDFLAGS=
EXEC=main
EXEC_TEST=test_main
DIREXEC=./Exec/
DIRSRC=./Src/
DIRTEST=./Test/
SRC=$(wildcard ./Src/*.c)
OBJS=$(SRC:.c=.o)
SRC_TEST=$(wildcard ./Test/*.c)
OBJS_TEST=$(SRC_TEST:.c=.o)

all: clean $(EXEC) $(EXEC_TEST)
	mv ./$(EXEC) $(DIREXEC)
	mv ./$(EXEC_TEST) $(DIRTEST)

test_main :$(OBJS_TEST)
	$(CC) -o $@ $^ $(LDFLAGS)

main: $(OBJS)
			$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c %.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
		rm -rf *.o

mrproper: clean
		rm -rf $(EXEC)
