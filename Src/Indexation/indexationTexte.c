#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAILLE_MAX 2000   //taille des chaine content les mots,
#define TAILLE_BALISE 100 // Taille des chaine comptenant les balises
#define TAILLE_MOT 26   // Taille max des mot lu
#define LONGEUR_MOT_MIN 3 // Longeur minium des mot selectionné dnas le texte. (nb-1)
#define TAILLE_CHAINE 10000 //Longeur des lignes max.(et du descipteur)
#define NB_MOT_IMPORTANT_CHOISI 5 // Nombre de mot gardé dans le top recurrence.

typedef struct{
  char mot[TAILLE_MOT];
  int nb_recurrence;
}MOT_RECURRENCE;  // Structure des mot recurrent

MOT_RECURRENCE TAB_RECURRENCE[TAILLE_MAX];  // Tab des mot recurrent

char TAB_LIGNE[TAILLE_MAX][TAILLE_MAX];  // tab content la ligne lu
char CHAINE_DESCRIPTEUR[TAILLE_CHAINE]; // Le descripteur
int TOTAL_MOT=0; // Total mot dans le TEXTE
int NB_MOT=0; // Nombre de mot lu et gardé
int NB_MOT_RECU=0; // Nombre de mot dans le tableau recurrent
int NB_CHAINE_DESCRIPTEUR=0; //Nombre de caractere dans le descripteur

void ajout_mot_chaine(char* mot){
  int cpt,longeur;
  longeur=strlen(mot);
  for(cpt=0;cpt<longeur;cpt++){
    CHAINE_DESCRIPTEUR[NB_CHAINE_DESCRIPTEUR]=mot[cpt];
    NB_CHAINE_DESCRIPTEUR++;
  }
}

void ajout_rc_chaine(){
  CHAINE_DESCRIPTEUR[NB_CHAINE_DESCRIPTEUR]='\n';
  NB_CHAINE_DESCRIPTEUR++;
}

void ajout_chiffre_chaine(int nombre){
  char nb_char[TAILLE_MOT];
  sprintf(nb_char,"%d",nombre );
  ajout_mot_chaine(nb_char);
}

void ajout_mot_important_chaine(){
  int cpt;

  for(cpt=0;cpt<NB_MOT_IMPORTANT_CHOISI;cpt++){
    ajout_mot_chaine(strcat (TAB_RECURRENCE[cpt].mot," "));
    ajout_chiffre_chaine(TAB_RECURRENCE[cpt].nb_recurrence);
    ajout_rc_chaine();
  }
}

void afficher_tab_ligne(){
  int cpt;
  //printf("\nTAB LIGNE:\n");
  for(cpt=0;cpt<NB_MOT;cpt++)
    printf(" %s \n",TAB_LIGNE[cpt]);
}

void afficher_tab_recurrence(){
  int cpt;
  for(cpt=0;cpt<NB_MOT_RECU;cpt++)
    printf("%s\t\t%d \n",TAB_RECURRENCE[cpt].mot ,TAB_RECURRENCE[cpt].nb_recurrence);
}

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

  //On orde le Tableau
  for(cpt1=0;cpt1<NB_MOT_RECU;cpt1++)
    for(cpt2=0;cpt2<NB_MOT_RECU;cpt2++)
      if(TAB_RECURRENCE[cpt1].nb_recurrence>TAB_RECURRENCE[cpt2].nb_recurrence){
         mot=TAB_RECURRENCE[cpt1];
         TAB_RECURRENCE[cpt1]=TAB_RECURRENCE[cpt2];
         TAB_RECURRENCE[cpt2]=mot;
      }
}

void lire_ligne(char* ligne,char* nom_fichier,int num_lig){
  FILE* fichier = NULL;
  char lecture[TAILLE_MAX];
  char *lecture2;
  int cpt;

  fichier=fopen(nom_fichier,"r");
  if (fichier != NULL)
    for(cpt=0;cpt<num_lig;cpt++)
      lecture2=fgets(lecture,TAILLE_MAX,fichier);
  else
      printf("\nImpossible d'ouvrir le fichier %s\n",nom_fichier);
  fclose(fichier);
  strcpy (ligne, lecture2);
}

void inser_mot(char* mot, int longeur_mot){
  int cpt=0;
  for (cpt=0;cpt<longeur_mot-1;cpt++){
    TAB_LIGNE[NB_MOT][cpt]=mot[cpt];
  }
  NB_MOT++;
}

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
  }

 }

void suppr_carac(char* ligne,int nb){
  int cpt,i;
  for(cpt=0;cpt< nb;cpt++)
    for(i = 0 ; ligne[i] ; i++)
      ligne[i] = ligne[i+1];
}

void ligne_tableau(char* ligne, int* retour){
  int cpt,i,longeur_balise,longeur_mot,longeur_ligne;
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
    // printf("Ne rien Faire1");
  }
  else if(strcmp(balise,"<date>")==0){
    //printf("XXXDate");
  }
  else if(strcmp(balise,"<auteur>")==0){
    //printf("XXXAut");
     cpt=0;
     do {
       lettre =ligne[cpt];
       mot[cpt] = lettre;
       cpt++;
     } while(lettre !='<');
     mot[cpt-1] = '\0';
     ajout_mot_chaine(mot);
     ajout_rc_chaine();
  }
  else if(strcmp(balise,"<texte>")==0){
    //printf("Ne rien faire2");
  }
  else if(strcmp(balise,"<phrase>")==0 || strcmp(balise,"<resume>")==0 || strcmp(balise,"<titre>")==0 || test==1){
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
  else if(strcmp(balise,"< article>")==0){
    //printf("\nFIN");
    *retour=1;
  }
  else {
  //  printf("Ne rien faire3");
  }
}

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
  ajout_mot_important_chaine(); // AJOUT DES MOTS RÉCURRENTS DANS LE DESCRIPTEUR
  ajout_mot_chaine("</descripteur>"); // BALISE FIN DESCRIPTEUR

}

// int main(){
//   char nom_fichier[]="jj.xml"; //"22-Sursaut_des_Monégasques_après_le.xml";
//   conception_descripteur(nom_fichier);
// printf("\n\n%s\n",CHAINE_DESCRIPTEUR);
//
//
//
//   // AFFICHAGE POUR LE DEBUG
// /*int cpt;
//   int val=0;
//   printf("\n\n");
//   afficher_tab_ligne();
//   printf("\n\n");
//   afficher_tab_recurrence();
//
//
//   printf("\n  TOTAL MOT TABLEAU = %d\n  ",NB_MOT);
//   printf("TOTAL MOT = %d\n  ",TOTAL_MOT);
//   printf("TOTAL MOT RECU = %d\n  ",NB_MOT_RECU);
//   for(cpt=0;cpt<NB_MOT_RECU;cpt++)
//     val=val+TAB_RECURRENCE[cpt].nb_recurrence;
//   printf("TOTAL MOT RECU ADD = %d\n  ",val);
//   printf(" DESCRIPTEUR => \n\n%s\n",CHAINE_DESCRIPTEUR);*/
//
// }
//
//
//
// //////FORMA DESCRIPETEUR/////////
// /*
// <descripteur>NOM_FICHIER
// NB_MOT_DU_TEXTE
// NOM_AUTEUR
// MOT_RECURENT_1 Nb_recurrence
// MOT_RECURENT_2 Nb_recurrence
// MOT_RECURENT_3 Nb_recurrence
// MOT_RECURENT_4 Nb_recurrence
// ..etc..
// MOT_RECURENT_X Nb_recurrence
// </descripteur>













//*/
