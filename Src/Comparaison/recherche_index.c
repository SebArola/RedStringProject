#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "recherche_index.h"

char CHEMIN[100];

void init_recherche_index(){
    //Variable pour le chemin et recupération dans le fichier config.txt
    char chemin[150];
    system("cat ../config.txt | grep chemin>temp.txt");
    FILE * ptr_ficChemin;
    ptr_ficChemin = fopen("temp.txt","r");
    while(!feof(ptr_ficChemin)){
        fscanf(ptr_ficChemin,"%s",chemin);
    }
    fclose(ptr_ficChemin);
    system("rm temp.txt");
    strtok(chemin,":");
    for(int i=0; i<strlen(chemin)-1;++i){
        CHEMIN[i]=chemin[i+1];
    }
}

void recherche_motcle(char * mot, char ** resultat){
    
}

/*
Fomre du fichier index :
<mot>MOT
nb_iteration NOM_FICHIER
nb_iteration NOM_FICHIER
.....
nb_iteration NOM_FICHIER
</mot>

<mot>MOT
nb_iteration NOM_FICHIER
nb_iteration NOM_FICHIER
.....
nb_iteration NOM_FICHIER
</mot>*/
