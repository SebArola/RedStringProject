#include <stdio.h>
#include "pileDescripteur.h"
#include "pileFichier.h"
#include <stdlib.h>
#include <string.h>

#define CHEMIN "/home/sebastien/Documents/UPSSITECH/RedStringProject"

//Méthode gérant l'indexation de toute la base.
void runIndexation(){
    char commande[1000] ;
    FILE * ptr_ficListe;
    FILE * ptr_ficImage;
    FILE * ptr_ficDescripteur;
    system(strcat(strcat("touch",CHEMIN),"/Data/base_descripteur_image.txt"));
    system(strcat(strcat("touch",CHEMIN),"/Data/base_descripteur_texte.txt"));
    system(strcat(strcat("touch",CHEMIN),"/Data/base_descripteur_son.txt"));

    strcpy(commande, "ls ");
    strcat(commande, strcat(CHEMIN,"/Data/Textes"));
    strcat(commande,strcat("*.txt > ",strcat(CHEMIN,"/Data/all_textes.txt")));
    system(commande);
    system("cat base_fichiers.txt");
    ptr_ficListe = fopen(strcat(CHEMIN,"/Data/all_textes.txt"), "r");
    while(!feof(ptr_ficListe))
    {}

}

//Méthode ecrivant les déscripteur dans le fichier de la base descripteur
void ecrireDescripteur(t_PileDescripteur pileDescripteur, char * type){
    //TODO
}
