#include <stdio.h>
#include "pileDescripteur.h"
#include "Fichier.h"
#include <stdlib.h>
#include <string.h>

#define CHEMIN "/home/sebastien/Documents/UPSSITECH/RedStringProject"

//Méthode gérant l'indexation de toute la base.
void runIndexation(){
    char cmd_touch[150] ;
    char cmd_ls[150] ;
    
    FILE * ptr_ficListe;
    // FILE * ptr_ficImage;
    // FILE * ptr_ficDescripteur;
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
    strcat(alltxtPath,CHEMIN);
    ptr_ficListe = fopen(strcat(alltxtPath,"/Data/all_textes.txt"), "r");
    printf("HEY1\n");

    while(!feof(ptr_ficListe)){
        printf("HEYFIN\n");

        fscanf(ptr_ficListe, "%s", nomFic);
        t_Fichier *temp_fichier= malloc(sizeof(t_Fichier));
        printf("%s\n",nomFic);
        temp_fichier->chemin_nom = nomFic;

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
