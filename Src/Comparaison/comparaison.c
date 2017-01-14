#include <stdio.h>
#include <stdlib.h>
#include "comparaison.h"

int comparaisonImage(t_Fichier fichierCompare, t_PileDescripteur pileImage){
    char * descript_ficC;
    t_PileDescripteur descripteurs_ficCompare;
    init_pile(&descripteurs_ficCompare);
    genDescripteurImage(fichierCompare, & descripteurs_ficCompare);

    return 0;
}

int comparaisonSon(t_Fichier fichierCompare, t_PileDescripteur pileSon){
    //TODO
    return 0;
}

int comparaisonTexte(t_Fichier fichierCompare, t_PileDescripteur pileTexte){
    //TODO
    return 0;
}

int compareFichierImage(char * fichierDonne , char * fichierCompare){
    //TODO
    return 0;
}

int compareFichierSon(char * fichierDonne , char * fichierCompare){
    //TODO
    return 0;
}
int compareFichierTexte(char * fichierDonne , char * fichierCompare){
    //TODO
    return 0;
}
