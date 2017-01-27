#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "recherche_index.h"
#include "../Librairies/string_perso.h"

char CHEMIN[100];

/*
* Cette fonction initialise la Variable global CHEMIN en recupérant le chemin
* dans le fichier de configuration.
*/
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
/*
* Cette fonction cerche tous les textes qui contiennent le paramètre mot
* et rempli le tableau résultat avec les résultats.
*/
void recherche_motcle(char * mot, char ** resultat){
    FILE * ptr_ficIndex;
    char index_path[100];
    strcpy(index_path,CHEMIN);
    strcat(index_path,"/Data/tab_index.txt");//Chemin vers la table d'index
    ptr_ficIndex = fopen(index_path,"r"); //Ouverture du fichier
    while(!feof(ptr_ficIndex)){//Tant qu'on est pas a la fin du fichier
        char ligne[50];
        fgets(ligne,50,ptr_ficIndex);
        if( strstr(ligne,"<mot>")){
            strremove(ligne,5);
            if(strstr(ligne,mot)!=NULL){//Si on la ligne courante contient le mot
                char nbOcc[10];
                char nomFic[30];
                int i=0;
                fscanf(ptr_ficIndex,"%s",nbOcc); //On récupère le nombre d'occurence
                fscanf(ptr_ficIndex,"%s",nomFic);//Et le nom du fichier
                //Tant qu'on a pas atteint la fin des textes dans lesquels le mot est présent
                while(strstr(nbOcc,"</mot>")==NULL){
                    strcat(nbOcc," ");
                    strcat(nbOcc,nomFic);
                    resultat[i] = malloc(sizeof(char)*(strlen(nbOcc)));
                     // On copie le récultat dans la case courante du tableau
                    strcpy(resultat[i],nbOcc);
                    fscanf(ptr_ficIndex,"%s",nbOcc);
                    fscanf(ptr_ficIndex,"%s",nomFic);
                    i++;
                }
            }
        }
    }
}


/*int main(){
    init_recherche_index();
    char ** resultat = malloc(sizeof(char*)*10);
    char mot[20];
    scanf("%s",mot);
    recherche_motcle(mot,resultat);
    for(int i=0;i<10;i++){
        printf("R :%s\n",resultat[i] );
    }
}*/
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
