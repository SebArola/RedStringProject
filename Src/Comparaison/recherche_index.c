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

void strremove(char * string, int n){
    char * temp = malloc(sizeof(char*)*(strlen(string)-n));
    for (int i=0; i<strlen(string);i++){
        if(i>=n){
                temp[i-n]=string[i];
                //printf("%c",temp[i-n] );
        }
    }

    for (int i=0; i<strlen(string);i++){
        string[i] = temp[i];

    }
    //free(temp);
}

void recherche_motcle(char * mot, char ** resultat){
    FILE * ptr_ficIndex;
    char index_path[100];
    strcpy(index_path,CHEMIN);
    strcat(index_path,"/Data/tab_index.txt");
    ptr_ficIndex = fopen(index_path,"r");
    while(!feof(ptr_ficIndex)){
        char ligne[20];
        fscanf(ptr_ficIndex,"%s",ligne);
        if( strrchr(ligne,'<')!= NULL && strlen(strrchr(ligne,'<'))>6){
            strremove(ligne,5);
            if(strcmp(ligne,mot)==0){
                char nbOcc[10];
                char nomFic[30];
                int i=0;
                fscanf(ptr_ficIndex,"%s",nbOcc);
                fscanf(ptr_ficIndex,"%s",nomFic);
                while(strcmp(nbOcc,"</mot>")!=0){
                    strcat(nbOcc," ");
                    strcat(nbOcc,nomFic);
                    resultat[i] = malloc(sizeof(char)*(strlen(nbOcc)));
                    strcpy(resultat[i],nbOcc);
                    fscanf(ptr_ficIndex,"%s",nbOcc);
                    fscanf(ptr_ficIndex,"%s",nomFic);
                    i++;
                }
            }
        }
    }
}


int main(){
    init_recherche_index();
    char ** resultat = malloc(sizeof(char*)*10);
    char mot[20];
    scanf("%s",mot);
    recherche_motcle(mot,resultat);
    for(int i=0;i<10;i++){
        printf("R :%s\n",resultat[i] );
    }
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
