#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "indexationTexte.h"

/*Define / Typedef */
#define LONGEUR_NOM 200 // Longeur nom fichier
#define NB_FICHIER 90 // nb de fichier
#define TAILLE_MAX 4000   //taille des chaine content les mots,
#define TAILLE_BALISE 100 // Taille des chaine comptenant les balises
#define TAILLE_MOT 50   // Taille max des mot lu
#define LONGEUR_MOT_MIN 4 // Longeur minium des mot selectionné dnas le texte. (nb-1)
#define TAILLE_CHAINE 5000 //Longeur des lignes max.(et du descipteur)
#define TAILLE_LIGNE 1000 // TAille LIGNE des descipteur

typedef struct{
  char mot[LONGEUR_NOM];
  int nb_recurrence;
}MOT_RECURRENCE;  // Structure des mot recurrent

typedef struct{
  char mot[TAILLE_MOT];
  int nb_descipteur_correspondent;
  MOT_RECURRENCE TAB_INDEX_MOT[NB_FICHIER];
}MOT_TAB_INDEX;

/* Variable global*/
char CHEMIN[100];
int NB_MOT_IMPORTANT_CHOISI; // Nombre de mot gardé dans le top recurrence.
MOT_TAB_INDEX TAB_INDEX[TAILLE_MAX];  // Tab des mots index
int NB_MOT_INDEX=0; // nombre de mot différent dans tab index
MOT_RECURRENCE TAB_RECURRENCE[TAILLE_MAX];  // Tab des mot recurrent
char** TAB_LIGNE;  // tab content la ligne lu
char* CHAINE_DESCRIPTEUR; // Le descripteur
int TOTAL_MOT=0; // Total mot dans le TEXTE
int NB_MOT=0; // Nombre de mot lu et gardé
int NB_MOT_RECU=0; // Nombre de mot dans le tableau recurrent
int NB_CHAINE_DESCRIPTEUR=0; //Nombre de caractere dans le descripteur

/* Fonctions */

/*Permet d'ajouter le mot en parametre a la CHAINE_DESCRIPTEUR*/
void ajout_mot_chaine(char* mot){
  int cpt,longeur;
  longeur=strlen(mot);
  for(cpt=0;cpt<longeur;cpt++){
    CHAINE_DESCRIPTEUR[NB_CHAINE_DESCRIPTEUR]=mot[cpt];
    NB_CHAINE_DESCRIPTEUR++;
  }
}

/*Permet d'ajouter un retour chariot a la CHAINE_DESCRIPTEUR*/
void ajout_rc_chaine(){
  CHAINE_DESCRIPTEUR[NB_CHAINE_DESCRIPTEUR]='\n';
  NB_CHAINE_DESCRIPTEUR++;
}

/* Convertie un INT en CHAR pour le rajouter a la CHAINE_DESCRIPTEUR*/
void ajout_chiffre_chaine(int nombre){
  char nb_char[TAILLE_MOT];
  sprintf(nb_char,"%d",nombre );
  ajout_mot_chaine(nb_char);
}

/* Permet d'ajouter les X mots recurrent dans la CHAINE_DESCRIPTEUR (X etant le nombre de mot definie par le seuil)*/
void ajout_mot_important_chaine(){
  int cpt;
  int fin= NB_MOT_IMPORTANT_CHOISI;
  for(cpt=0;cpt<fin;cpt++){
    if((strcmp(TAB_RECURRENCE[cpt].mot,"dans")==0) || (strcmp(TAB_RECURRENCE[cpt].mot,"plus")==0) || (strcmp(TAB_RECURRENCE[cpt].mot,"pour")==0) || (strcmp(TAB_RECURRENCE[cpt].mot,"avec")==0) || (strcmp(TAB_RECURRENCE[cpt].mot,"avoir")==0) || (strcmp(TAB_RECURRENCE[cpt].mot,"avait")==0))
        fin++;
    else{
      ajout_mot_chaine(strcat (TAB_RECURRENCE[cpt].mot," "));
      ajout_chiffre_chaine(TAB_RECURRENCE[cpt].nb_recurrence);
      ajout_rc_chaine();
    }
  }
}

/* Permet d'afficher TAB_LIGNE pour des debugs eventuels */
void afficher_tab_ligne(){
  int cpt;
  for(cpt=0;cpt<NB_MOT;cpt++)
    printf(" %s \n",TAB_LIGNE[cpt]);
}

/* Permet d'afficher TAB_RECURRENCE pour des debugs eventuels */
void afficher_tab_recurrence(){
  int cpt;
  for(cpt=0;cpt<NB_MOT_RECU;cpt++)
    printf("%s\t\t%d \n",TAB_RECURRENCE[cpt].mot ,TAB_RECURRENCE[cpt].nb_recurrence);
}

/*Permet de remplir le tableau TAB_RECURRENCE avec les mots contenus dans TAB_LIGNE */
void calcul_recurrence(){
  int cpt1,cpt2,longeur_mot;
  int test;
  MOT_RECURRENCE mot;
  //On Remplie le Tableau
  for(cpt1=0;cpt1<NB_MOT;cpt1++){
    longeur_mot=strlen(TAB_LIGNE[cpt1]);
    for (cpt2=0;cpt2<longeur_mot;cpt2++){
      mot.mot[cpt2]=TAB_LIGNE[cpt1][cpt2];
    }
    mot.mot[cpt2]='\0';
    mot.nb_recurrence=0;
    test=0;
    for(cpt2=0;cpt2<NB_MOT;cpt2++)
        if(strcmp(TAB_RECURRENCE[cpt2].mot,mot.mot)==0)
          test=1; // deja présent
    if(test!=1){
      for(cpt2=0;cpt2<NB_MOT;cpt2++)
        if(strcmp(TAB_LIGNE[cpt2],mot.mot)==0)
          mot.nb_recurrence++;
      TAB_RECURRENCE[NB_MOT_RECU]=mot;
      NB_MOT_RECU++;
    }
  }
  //On ordonne le Tableau
  for(cpt1=0;cpt1<NB_MOT_RECU;cpt1++)
    for(cpt2=0;cpt2<NB_MOT_RECU;cpt2++)
      if(TAB_RECURRENCE[cpt1].nb_recurrence>TAB_RECURRENCE[cpt2].nb_recurrence){
         mot=TAB_RECURRENCE[cpt1];
         TAB_RECURRENCE[cpt1]=TAB_RECURRENCE[cpt2];
         TAB_RECURRENCE[cpt2]=mot;
      }
}

/*Permet de lire dans le fichier la ligne choisi*/
void lire_ligne(char* ligne,char* nom_fichier,int num_lig){
  FILE* fichier = NULL;
  char lecture[TAILLE_MAX];
  char *lecture2;
  char chemin[100];
  int cpt;
  strcpy(chemin,CHEMIN);
  strcat(chemin,"/Data/Textes/");
  strcat(chemin,nom_fichier);
  fichier=fopen(chemin,"r");
  if (fichier != NULL)
    for(cpt=0;cpt<num_lig;cpt++)
      lecture2=fgets(lecture,TAILLE_MAX,fichier);
  else
    printf("\nImpossible d'ouvrir le fichier : %s\n",chemin);
  fclose(fichier);
  strcpy (ligne, lecture2);
}

/* Permet d'ajouter un mot dans TAB_LIGNE*/
void inser_mot(char* mot, int longeur_mot){
  int cpt=0;
  for (cpt=0;cpt<longeur_mot-1;cpt++){
    TAB_LIGNE[NB_MOT][cpt]=mot[cpt];
  }
  NB_MOT++;
}

/*Permet de supprimer les ponctuations dans une chaine de caractere*/
void suppr_ponctuation(char* ligne){
  char lettre;
  int longeur_ligne,cpt,i;
  longeur_ligne= strlen(ligne);
  for(cpt=0;cpt<longeur_ligne;cpt++){
    lettre = ligne[cpt];
    if(lettre==',' || lettre ==';' || lettre=='.' || lettre=='(' || lettre==')' || lettre==(char)39 || lettre=='-' || lettre=='/')
      ligne[cpt]=' ';
    if(lettre==' ' && ligne[cpt+1]==' ')
      for(i = cpt ; i<longeur_ligne ; i++)
        ligne[i] = ligne[i+1];
    if((lettre>=65)  && (lettre <= 90))
      ligne[cpt]=ligne[cpt]+32;
  }
 }

/*Permet de supprimer des caracteres dans une chaine de caratère*/
void suppr_carac(char* ligne,int nb){
  int cpt,i;
  for(cpt=0;cpt< nb;cpt++)
    for(i = 0 ; ligne[i] ; i++)
      ligne[i] = ligne[i+1];
}

/*Fonction qui traite une ligne pour géré l'indexation */
void ligne_tableau(char* ligne, int* retour){
  int cpt,longeur_balise,longeur_mot,longeur_ligne;
  char balise[TAILLE_BALISE]="";
  char mot[TAILLE_MOT]="";
  char lettre;
  int test=0;
  cpt=0;
  do {
    lettre =ligne[cpt];
    if(cpt==0 && lettre !='<')
      test=1;//ERREUR BALISE
    else{
      balise[cpt] = lettre;
      cpt++;
    }
  } while(lettre != '>' && test==0);
  if(test==0){
     longeur_balise=strlen(balise);
     suppr_carac(ligne,longeur_balise);
   }

  if(strcmp(balise,"<article>")==0){
  //Ne rien faire
  }
  else if(strcmp(balise,"<date>")==0){
  //Ne rien faire
  }
  else if(strcmp(balise,"<auteur>")==0){
     cpt=0;
     do {
       lettre =ligne[cpt];
       mot[cpt] = lettre;
       cpt++;
     } while(lettre !='<');
     mot[cpt-1] = '\0';
     if(cpt!=1){
       ajout_mot_chaine(mot);
       ajout_rc_chaine();
     }
     else{
       ajout_mot_chaine("INCONNU");
       ajout_rc_chaine();
   }
  }
  else if(strcmp(balise,"<texte>")==0){
    // Ne rien faire
  }
  else if(strcmp(balise,"<phrase>")==0 || strcmp(balise,"<resume>")==0 || strcmp(balise,"<titre>")==0 || test==1){
    if((ligne[0]>=65  && ligne[0] <=90) || (ligne[0]>=97  && ligne[0] <=122) || ligne[0]==' '){
      do{
        cpt=0;
        do {
          lettre =ligne[cpt];
          mot[cpt] = lettre;
          cpt++;
        } while(lettre != ' ' && lettre !='<');
        mot[cpt] = '\0';
        longeur_mot=strlen(mot);
        if (longeur_mot>LONGEUR_MOT_MIN+1)
          inser_mot(mot,longeur_mot);
        TOTAL_MOT++;
        suppr_carac( ligne,longeur_mot);
        longeur_ligne=strlen(ligne);
      }while(lettre !='<' && longeur_ligne!=1);
      if(lettre == '<')
        TOTAL_MOT--;
    }
  }
  else if(strcmp(balise,"< article>")==0){
    *retour=1;
  }
  else {
    // Ne rien faire
  }
}

/*Fonction qui réalise la conception du descripteur a partir de l'emplacement du fichier*/
void conception_descripteur(char* nom_fichier){
  NB_MOT=0;
  int fin=0;
  char ligne[TAILLE_MAX];
  int cpt=1;
  // DEBUT DESCRIPTEUR
  ajout_mot_chaine("<descripteur>");// BALISE DEBUT DESCRIPTEUR
  ajout_mot_chaine(nom_fichier);
  ajout_rc_chaine();
  // ON LIS LES LIGNES
  do{
    lire_ligne(ligne,nom_fichier,cpt); // ON LIS 1 LIGNE
    //printf("\nLue = %s\n",ligne);
    suppr_ponctuation(ligne); // ON ENELEVE LES CARACTERES SPECIAUX
    //printf("\nLue2 = %s\n",ligne);
    ligne_tableau(ligne,&fin); // ON TRAITE LA LIGNE LUE
    cpt++;
  }while(fin!=1);
  calcul_recurrence(); // CALCUL DES MOTS RECURENTS
  ajout_chiffre_chaine(TOTAL_MOT);//AJOUTE LE NOMBRE TOTAL DE MOT DANS LE DESCRIPTEUR
  ajout_rc_chaine();
  ajout_mot_chaine("<mot>");
  ajout_rc_chaine();
  ajout_mot_important_chaine(); // AJOUT DES MOTS RÉCURRENTS DANS LE DESCRIPTEUR
  ajout_mot_chaine("</mot>");
  ajout_rc_chaine();
  ajout_mot_chaine("</descripteur>"); // BALISE FIN DESCRIPTEUR
  ajout_rc_chaine();
}

/*genere le descripteur*/
void genDescripteurTexte(t_Fichier fichier, t_PileDescripteur *ptrPileTexte,char* chemin, int nbMot){
  strcpy(CHEMIN,chemin);
  NB_MOT_IMPORTANT_CHOISI = nbMot;
  TOTAL_MOT=0;
  NB_MOT=0;
  NB_MOT_RECU=0;
  NB_CHAINE_DESCRIPTEUR=0;
  CHAINE_DESCRIPTEUR=malloc(sizeof(char)*TAILLE_MAX);
  TAB_LIGNE=malloc(sizeof(char*)*TAILLE_MAX);
  for (int i =0; i< TAILLE_MAX;i++)
    TAB_LIGNE[i]=malloc(sizeof(char)* TAILLE_MAX);
  conception_descripteur(fichier.chemin_nom);
  empile(ptrPileTexte,CHAINE_DESCRIPTEUR);
}

/* Permet d'affciher le tableau TAB_INDEX pour des debugs eventuels*/
void afficher_tab_index(){
  int cpt,cpt2;
  cpt=0;
  for(cpt=0;cpt<NB_MOT_INDEX-1;cpt++){
    printf("\n\nMOT=>%s  => %d =>NB=> %d\n\n",TAB_INDEX[cpt].mot,cpt,TAB_INDEX[cpt].nb_descipteur_correspondent);
    for(cpt2=0 ; cpt2<TAB_INDEX[cpt].nb_descipteur_correspondent ;cpt2++)
      printf("%d %s\n",TAB_INDEX[cpt].TAB_INDEX_MOT[cpt2].nb_recurrence,TAB_INDEX[cpt].TAB_INDEX_MOT[cpt2].mot);
  }
}

/*remplie le tableau d'indexation*/
void envoie_tableau(char* nom_document,char* mot,int nb_recurrence){
  int cpt,cpt2;
  int new_mot=1;
  int position=0;
  int position_des=0;
  for(cpt=0;cpt<NB_MOT_INDEX;cpt++)
    if(strcmp(mot,TAB_INDEX[cpt].mot)==0){
      new_mot=0;
      position=cpt;
    }
  if(new_mot ==1){
    strcpy (TAB_INDEX[cpt].mot,mot);
    TAB_INDEX[NB_MOT_INDEX].nb_descipteur_correspondent=1;
    strcpy (TAB_INDEX[NB_MOT_INDEX].TAB_INDEX_MOT[0].mot,nom_document);
    TAB_INDEX[NB_MOT_INDEX].TAB_INDEX_MOT[0].nb_recurrence=nb_recurrence;
    NB_MOT_INDEX++;
  }
  else{
    position_des=TAB_INDEX[position].nb_descipteur_correspondent;
    for(cpt=0;cpt<TAB_INDEX[position].nb_descipteur_correspondent;cpt++){
      if(TAB_INDEX[position].TAB_INDEX_MOT[cpt].nb_recurrence<nb_recurrence){
        position_des=cpt;
        cpt=TAB_INDEX[position].nb_descipteur_correspondent;
      }
    }
    if( position_des==TAB_INDEX[position].nb_descipteur_correspondent){
      strcpy (TAB_INDEX[position].TAB_INDEX_MOT[position_des].mot,nom_document);
      TAB_INDEX[position].TAB_INDEX_MOT[position_des].nb_recurrence=nb_recurrence;
      TAB_INDEX[position].nb_descipteur_correspondent++;
    }
    else{
      for(cpt2=TAB_INDEX[position].nb_descipteur_correspondent;cpt2>position_des;cpt2--){
        strcpy (TAB_INDEX[position].TAB_INDEX_MOT[cpt2].mot,TAB_INDEX[position].TAB_INDEX_MOT[cpt2-1].mot);
        TAB_INDEX[position].TAB_INDEX_MOT[cpt2].nb_recurrence=TAB_INDEX[position].TAB_INDEX_MOT[cpt2-1].nb_recurrence;
      }
      strcpy (TAB_INDEX[position].TAB_INDEX_MOT[position_des].mot,nom_document);
      TAB_INDEX[position].TAB_INDEX_MOT[position_des].nb_recurrence=nb_recurrence;
      TAB_INDEX[position].nb_descipteur_correspondent++;
    }
  }
}

/*selectionne les mots importants dans le descripteur*/
void gere_tab_index(char* ligne){
  int cpt,cpt_mot;
  char mot[TAILLE_MOT];
  char txt_nb_recurrence[4];
  int nb_recurrence;
  char nom_document[LONGEUR_NOM];
  char lettre;
  cpt=0;
  do {
    cpt++;
  } while(ligne[cpt] != '>');
  cpt++;

  cpt_mot=0;
  while(ligne[cpt]!=10){
    nom_document[cpt_mot]=ligne[cpt];
    cpt_mot++;
    cpt++;
  }
  nom_document[cpt_mot]='\0';
  do {
    cpt++;
  } while(ligne[cpt] != '<' || ligne[cpt+1]!='m');
  cpt +=6;

  while(ligne[cpt] != '<' || ligne[cpt+1]!='/'){
    cpt_mot=0;
    do {
      lettre=ligne[cpt];
      mot[cpt_mot]=lettre;
      cpt++;
      cpt_mot++;
    } while(lettre != ' ');
    mot[cpt_mot-1]='\0';

    cpt_mot=0;
    while(ligne[cpt]!=10){
      txt_nb_recurrence[cpt_mot]=ligne[cpt];
      cpt_mot++;
      cpt++;
    }
    cpt++;
    txt_nb_recurrence[cpt_mot]='\0';

    sscanf(txt_nb_recurrence,"%d",&nb_recurrence);
    envoie_tableau(nom_document,mot,nb_recurrence);

  }
}

/* Ecrit le tableau d'indexation dans le fichier tab_index.txt*/
void conception_index(){
  int cpt,cpt2;
  NB_CHAINE_DESCRIPTEUR=0;
  char cmd_touch[100];
  strcpy(cmd_touch,"touch ");
  strcat(cmd_touch,CHEMIN);
  system(strcat(cmd_touch,"/Data/tab_index.txt"));
  char index_path[100];
  strcpy(index_path,CHEMIN);
  strcat(index_path,"/Data/tab_index.txt");
  FILE * fic_index;
  fic_index = fopen(index_path,"w");

  CHAINE_DESCRIPTEUR=malloc(sizeof(char)*TAILLE_MAX);
  for (cpt=0;cpt<NB_MOT_INDEX;cpt++){
    ajout_mot_chaine("<mot>");
    ajout_mot_chaine(TAB_INDEX[cpt].mot);
    ajout_rc_chaine();
    for (cpt2=0;cpt2<TAB_INDEX[cpt].nb_descipteur_correspondent;cpt2++){
      if(TAB_INDEX[cpt].TAB_INDEX_MOT[cpt2].nb_recurrence !=0){
        ajout_chiffre_chaine(TAB_INDEX[cpt].TAB_INDEX_MOT[cpt2].nb_recurrence);
        ajout_mot_chaine(" ");
        ajout_mot_chaine(TAB_INDEX[cpt].TAB_INDEX_MOT[cpt2].mot);
        ajout_rc_chaine();
      }
    }
    ajout_mot_chaine("</mot>");
    ajout_rc_chaine();
    ajout_rc_chaine();
    fprintf(fic_index, "%s\n", CHAINE_DESCRIPTEUR);
    NB_CHAINE_DESCRIPTEUR=0;
    CHAINE_DESCRIPTEUR=calloc(TAILLE_MAX,sizeof(char));
  }
  fclose(fic_index);
}

/*genere tab_index a partir de la pile des descripteurs*/
void genTabIndex(t_PileDescripteur* pile_texte){
  t_CellDescripteur *suivant;
  suivant = (*pile_texte).premier;
  while(suivant!=NULL){
    gere_tab_index(suivant->descripteur);
      suivant = suivant->p_suivant;
  }
 conception_index();
}
