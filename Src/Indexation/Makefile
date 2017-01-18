Son.out: pileDescripteur.o indexationSon.o
	gcc -g -o Son.out pileDescripteur.o indexationSon.o

pileDescripteur.o : pileDescripteur.c pileDescripteur.h
	gcc -g -c pileDescripteur.c

indexationSon.o : indexationSon.c indexationSon.h Fichier.h pileDescripteur.h
	gcc -g -c indexationSon.c
