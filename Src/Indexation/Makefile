FileManager.o: FileManager.h FileManager.c
	gcc -c FileManager.h FileManager.c -o FileManager.o

TypeDescripSon.o: TypeDescripSon.h
	gcc -c TypeDescripSon.h -o TypeDescripSon.o

Type_Bool.o: Type_Bool.h
	gcc -c Type_Bool.h -o Type_Bool.o


indexationSon.o: DescripSon.h DescripSon.c
	gcc -c DescripSon.h DescripSon.c -o DescripSon.o -lm

testDescripSon.out: indexationSon.o Type_Bool.o TypeDescripSon.o FileManager.o
	gcc indexationSon.o Type_Bool.o TypeDescripSon.o FileManager.o -o testDescripSon.out -lm
