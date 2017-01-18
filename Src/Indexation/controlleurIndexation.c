#include <stdio.h>
#include "pileDescripteur.h"
#include "Fichier.h"
#include <stdlib.h>
#include <string.h>
#include "indexationTexte.h"
#include "indexationImage.h"
#include "indexationSon.h"

//Constante contenant le chemin en local. Sera remplacé par le fichier de
//configuration.
//#define CHEMIN "/home/sebastien/Documents/UPSSITECH/RedStringProject"
//#define CHEMIN "/users/1anneesri/dlt1727a/RedStringProject-master"
//#define CHEMIN "/home/etienne/RedStringProject"
char CHEMIN[100];
//Méthode ecrivant les déscripteur dans le fichier de la base descripteur
void ecrireDescripteur(t_PileDescripteur pileDescripteur, char * type){
    char chemin[100];
    FILE * base_descripteur;
    strcpy(chemin,CHEMIN);
    strcat(chemin,"/Data");
    strcat(chemin,"/base_descripteur_");
    strcat(chemin,type);
    strcat(chemin,".txt");

    base_descripteur = fopen(chemin,"w");
    t_CellDescripteur *suivant;
    suivant = pileDescripteur.premier;
    //affiche_pile(pileDescripteur);
    while(suivant->p_suivant!=NULL){
        fprintf(base_descripteur,"%s;\n",suivant->descripteur);
        suivant = suivant->p_suivant;
    }
    fprintf(base_descripteur,"%s", suivant->descripteur);

    fclose(base_descripteur);
}

//Méthode gérant l'indexation de toute la base.
void runIndexation(){
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

    //Variable pour les commandes
    char cmd_touch[150] ;
    char cmd_ls[150] ;

    //Les différentes pile
    t_PileDescripteur pile_texte;
    t_PileDescripteur pile_image;
    t_PileDescripteur pile_son;
    init_pile(&pile_texte);
    init_pile(&pile_image);
    init_pile(&pile_son);

    FILE * ptr_ficListe;
    char nomFic[100];
    char infoFic[100];

    //Création des fichiers base_descripteur_*
    strcpy(cmd_touch, "touch ");
    system(strcat(strcat(cmd_touch,CHEMIN),"/Data/base_descripteur_image.txt"));

    strcpy(cmd_touch,"touch ");
    system(strcat(strcat(cmd_touch,CHEMIN),"/Data/base_descripteur_texte.txt"));

    strcpy(cmd_touch,"touch ");
    system(strcat(strcat(cmd_touch,CHEMIN),"/Data/base_descripteur_son.txt"));

    //Generation des descripteur textes
    //Copie de tous les noms de textes dans le fichier all_textes. ls avec redirection
    strcpy(cmd_ls, "ls ");
    strcat(cmd_ls,CHEMIN) ;
    strcat(cmd_ls,"/Data/Textes/");
    strcat(cmd_ls," > ");
    strcat(cmd_ls,CHEMIN);
    strcat(cmd_ls,"/Data/all_textes.txt");
    system(cmd_ls); //Copie

    char alltxtPath[100];//Chemin vers le fichier all_textes
    strcpy(alltxtPath,CHEMIN);
    strcat(alltxtPath,"/Data/all_textes.txt");

    char cmd_wc[110];
    int nbLigne;
    strcpy(cmd_wc,"wc -l ");
    strcat(cmd_wc,alltxtPath);
    system(strcat(cmd_wc," > temp_wc.txt"));
    FILE * temp_file;
    temp_file = fopen("temp_wc.txt","r");
    fscanf(temp_file,"%d",&nbLigne);
    fclose(temp_file);
    system("rm temp_wc.txt");

    //Ouverture du fichier contenant les noms de tous les textes
    ptr_ficListe = fopen(alltxtPath, "r");
    t_Fichier *temp_fichier= malloc(sizeof(t_Fichier));
    for(int i=0; i< nbLigne;i++){//Tant qu'on est pas a la fin du document
        fscanf(ptr_ficListe, "%s", nomFic);//On recupère la ligne courante
        temp_fichier->chemin_nom = nomFic;//Création du fichier
        //Ajout du fichier dans la pile_texte. Voir indexationImage.h pour
        //des détails sur la méthode.
        genDescripteurTexte(*temp_fichier, &pile_texte, CHEMIN);
    }

    fclose(ptr_ficListe);
    free(temp_fichier);

    genTabIndex(&pile_texte);

    //Descripteur image
    strcpy(cmd_ls, "ls ");
    strcat(cmd_ls,CHEMIN) ;
    strcat(cmd_ls,"/Data/IMG_NG/*");
    strcat(cmd_ls," > ");
    strcat(cmd_ls,CHEMIN);
    strcat(cmd_ls,"/Data/all_IMG_NG.txt");
    system(cmd_ls); //Copie

    char allimgPath[150];//Chemin vers le fichier all_IMG_NG
    strcpy(allimgPath,CHEMIN);
    strcat(allimgPath,"/Data/all_IMG_NG.txt");

    ptr_ficListe = fopen(allimgPath, "r");
    temp_fichier= malloc(sizeof(t_Fichier));
    while(!feof(ptr_ficListe)){//Tant qu'on est pas a la fin du document
        fscanf(ptr_ficListe, "%s", nomFic);//On recupère le nom du fichier
        temp_fichier->chemin_nom = nomFic;//Création du fichier
        fscanf(ptr_ficListe, "%s", infoFic);//On recupère le nom du fichier info
        temp_fichier->chemin_info = infoFic;
        //Ajout du fichier dans la pile_texte. Voir indexationImage.h pour
        //des détails sur la méthode.
        genDescripteurImage(*temp_fichier, &pile_image);
    }

    fclose(ptr_ficListe);

    strcpy(cmd_ls, "ls ");
    strcat(cmd_ls,CHEMIN) ;
    strcat(cmd_ls,"/Data/IMG_RGB/*");
    strcat(cmd_ls," > ");
    strcat(cmd_ls,CHEMIN);
    strcat(cmd_ls,"/Data/all_IMG_RGB.txt");
    system(cmd_ls); //Copie

    char all_IMG_RGB_Path[150];//Chemin vers le fichier all_IMG_NG
    strcpy(all_IMG_RGB_Path,CHEMIN);
    strcat(all_IMG_RGB_Path,"/Data/all_IMG_RGB.txt");

    ptr_ficListe = fopen(all_IMG_RGB_Path, "r");
    temp_fichier= malloc(sizeof(t_Fichier));
    while(!feof(ptr_ficListe)){//Tant qu'on est pas a la fin du document
        fscanf(ptr_ficListe, "%s", nomFic);//On recupère la ligne courante
        temp_fichier->chemin_nom = nomFic;//Création du fichier
        fscanf(ptr_ficListe, "%s", infoFic);//On recupère le nom du fichier info
        temp_fichier->chemin_info = infoFic;
        //Ajout du fichier dans la pile_img. Voir indexationImage.h pour
        //des détails sur la méthode.
        genDescripteurImage(*temp_fichier, &pile_image);

    }
    fclose(ptr_ficListe);

    //Son
    strcpy(cmd_ls, "ls ");
    strcat(cmd_ls,CHEMIN) ;
    strcat(cmd_ls,"/Data/SON_REQUETE/*");
    strcat(cmd_ls," > ");
    strcat(cmd_ls,CHEMIN);
    strcat(cmd_ls,"/Data/all_SON.txt");
    system(cmd_ls); //Copie

    char all_SON_Path[150];//Chemin vers le fichier all_SON
    strcpy(all_SON_Path,CHEMIN);
    strcat(all_SON_Path,"/Data/all_SON.txt");

    ptr_ficListe = fopen(all_SON_Path, "r");

    while(!feof(ptr_ficListe)){//Tant qu'on est pas a la fin du document

        fscanf(ptr_ficListe, "%s", nomFic);//On recupère la ligne courante
        //t_Fichier *temp_fichier= malloc(sizeof(t_Fichier));
        temp_fichier->chemin_nom = nomFic;//Création du fichier
        fscanf(ptr_ficListe, "%s", infoFic);//On recupère le nom du fichier info
        temp_fichier->chemin_info = infoFic;
        //Ajout du fichier dans la pile_img. Voir indexationImage.h pour
        //des détails sur la méthode.
        //printf("DEBUG B1\n" );
        //genDescripteurSon(*temp_fichier, &pile_son);
        //printf("DEBUG B\n" );

    }
    fclose(ptr_ficListe);

    //Enregistrement des déscripteur dans les fichiers base_descripteur_*
//    printf("ecrireDescripteurTexte non activé\n");
    ecrireDescripteur(pile_texte, "texte");

    ecrireDescripteur(pile_image,"image");

    //printf("ecrireDescripteurSon non activé\n");
//    ecrireDescripteur(pile_son,"son");
}



// //Main de test.
int main(){
    printf("Lancement indexation. RETIREZ MOI AVANT LA RECETTE\n");
    runIndexation();
}
