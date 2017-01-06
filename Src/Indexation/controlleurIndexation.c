#include <stdio.h>
#include "pileDescripteur.h"
#include "Fichier.h"
#include <stdlib.h>
#include <string.h>

#define CHEMIN "/home/sebastien/Documents/UPSSITECH/RedStringProject"
#define DEBUG 1

//Méthode gérant l'indexation de toute la base.
void runIndexation(){
    char cmd_touch[150] ;
    char cmd_ls[150] ;

    FILE * ptr_ficListe;
    char nomFic[100];
    strcpy(cmd_touch, "touch ");

    system(strcat(strcat(cmd_touch,CHEMIN),"/Data/base_descripteur_image.txt"));

    strcpy(cmd_touch,"touch ");
    system(strcat(strcat(cmd_touch,CHEMIN),"/Data/base_descripteur_texte.txt"));

    strcpy(cmd_touch,"touch ");
    system(strcat(strcat(cmd_touch,CHEMIN),"/Data/base_descripteur_son.txt"));

    strcpy(cmd_ls, "ls ");
    strcat(cmd_ls,CHEMIN) ;
    strcat(cmd_ls,"/Data/Textes/");
    strcat(cmd_ls," > ");
    strcat(cmd_ls,CHEMIN);
    strcat(cmd_ls,"/Data/all_textes.txt");
    system(cmd_ls);
    char alltxtPath[150];
    strcpy(alltxtPath,CHEMIN);
    strcat(alltxtPath,"/Data/all_textes.txt");

    //Ouverture du fichier contenant les noms de tous les textes
    ptr_ficListe = fopen(alltxtPath, "r");
    while(!feof(ptr_ficListe)){
        fscanf(ptr_ficListe, "%s", nomFic);
        t_Fichier *temp_fichier= malloc(sizeof(t_Fichier));
        temp_fichier->chemin_nom = nomFic;
        printf("%s\n",temp_fichier->chemin_nom );
    }

}

//Méthode ecrivant les déscripteur dans le fichier de la base descripteur
void ecrireDescripteur(t_PileDescripteur pileDescripteur, char * type){
    //TODO
}

int main(){
    printf("HEYDEBUT\n");
    runIndexation();
}
