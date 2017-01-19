#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interfaceMoteur.h"
#include "../Indexation/controlleurIndexation.h"
#include "../Comparaison/comparaison.h"
#include "../Comparaison/recherche_index.h"
#include "../Librairies/string_perso.h"

#define TAILLECHAINE 500

char* choixIndexation=NULL;
char* choixDescripComp=NULL;//memorise le choix du type de descripteurs a tester
int *seuilDescripImg1=NULL;
char chaineSansEspace[TAILLECHAINE]={'a'};//nvelle chaine contenant le critere de

void retirerEspaceChaine(char* chaine)
{
  int i=0, j=0;
  char* positionEntree=NULL;
  positionEntree = strchr(chaine, '\n'); // On recherche l'"Entrée", positionEntree pointe sur le caractere trouve
  if (positionEntree != NULL) {
      *positionEntree = '\0'; // On remplace ce caractère par \0
  }
  //printf("%s", chaine);//on retire les espaces dans le chemin
  j=0;
  for(i=0;i<TAILLECHAINE;i++) {
    if (chaine[i]!=' ') {
      chaineSansEspace[j]=chaine[i];//chaine1 est la nouvelle chaine sans espace
      j++;
    }
  }
  chaineSansEspace[j]='\0';
}

char CHEMIN[100];

void genPileDescripteur(t_PileDescripteur *pile, char * type){
    FILE * ptr_ficBaseDesc;
    char base_path[100];
    strcpy(base_path,CHEMIN);
    strcat(base_path,"/Data/base_descripteur_");
    strcat(base_path,type);
    strcat(base_path,".txt");

    char cmd_wc[110];
    int nbLigne;
    strcpy(cmd_wc,"wc -l ");
    strcat(cmd_wc,base_path);
    system(strcat(cmd_wc," > temp_wc.txt"));
    FILE * temp_file;
    temp_file = fopen("temp_wc.txt","r");
    fscanf(temp_file,"%d",&nbLigne);
    fclose(temp_file);
    //system("rm temp_wc.txt");
    ptr_ficBaseDesc = fopen(base_path,"r");
    char * descripteur;
    char * ligne;
    while(!feof(ptr_ficBaseDesc)){
        ligne = malloc(sizeof(char)*100);
        descripteur = malloc(sizeof(char)*5000);
        strcpy(descripteur,"");
        fgets(ligne,strlen(CHEMIN)+20,ptr_ficBaseDesc);
        while(strpbrk(ligne,";")==NULL){
            strcat(descripteur,ligne);
            fgets(ligne,100,ptr_ficBaseDesc);
        }
        //printf("%s\n",descripteur );
        empile(pile,descripteur);
        // free(descripteur);
        // free(ligne);
    //    printf("DEBUG 1.4\n" );
    }
}

void comparaison_moteur_texte(t_PileDescripteur pile_texte){

  int fic_trouve_txt =1 ;
  do{
      fic_trouve_txt = 1;
      printf("Entrez le nom du fichier :\n");
      char nomFic[50];
      scanf("%s",nomFic);
      if(strpbrk(nomFic,".")==NULL){
          strcat(nomFic,".xml");
      }
      char chemin_fic[200];
      strcpy(chemin_fic,CHEMIN);
      strcat(chemin_fic,"/Data/Textes/");
      strcat(chemin_fic,nomFic);
  //    printf("DEBUG 1\n" );
      if(fopen(chemin_fic,"r")!=NULL){
          t_Fichier temp;
          t_PileDescripteur pile_resultat;
          init_pile(&pile_resultat);
          temp.chemin_nom = nomFic;
          comparaisonTexte(temp, pile_texte,&pile_resultat);
          printf("\nRésultat :\n\n" );
          if(!pile_est_vide(pile_resultat)){
              t_CellDescripteur *suivant;
              suivant = pile_resultat.premier;
              char * ligne;
              char currentCar;
              int i;
              while(suivant->p_suivant!=NULL){
                  ligne = malloc(sizeof(char)*200);
                  i=0;
                  strremove(suivant->descripteur,13);
                  currentCar = suivant->descripteur[i];
                  while(currentCar != '\n'){
                      strcat(ligne,&currentCar);
                      i++;
                      currentCar = suivant->descripteur[i];
                  }
                  if(strstr(temp.chemin_nom,ligne)==NULL)
                        printf("%s\n",ligne );
                  suivant = suivant->p_suivant;
              }
              ligne = malloc(sizeof(char)*200);
              i=0;
              strremove(suivant->descripteur,13);
              currentCar = suivant->descripteur[i];
              while(currentCar != '\n'){
                  strcat(ligne,&currentCar);
                  i++;
                  currentCar = suivant->descripteur[i];
              }
              if(strstr(temp.chemin_nom,ligne)==NULL)
                    printf("%s\n",ligne );
          }
      }else{
          printf("ERREUR : fichier introuvable\n");
          fic_trouve_txt = 0;
      }
  }while (fic_trouve_txt == 0);
}

void recherche_index(t_PileDescripteur pile_texte){
    char mot_cles[25];
    int c;
    char **resultat = malloc(sizeof(char*)*20);
    printf("Entrez un mot a rechercher :\n" );
    if(scanf("%s",mot_cles)!=0){
        while ( ((c = getchar()) != '\n') && c != EOF);
        recherche_motcle(mot_cles,resultat);
        printf("\nRésultat (nb occurence par fichier):\n");
        if(resultat[0]==NULL){
            printf("Aucun résutat\n" );
        }else{
            for(int i=0;i<20;i++){
                if(resultat[i]==NULL){
                    i=20;
                }else{
                    printf("->%s\n",resultat[i] );
                }
            }
        }
    }
}

int interfaceMoteur()
{

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

  //printf("Mise à jour de la base, veuillez patienter\n");
  runIndexation();
  init_comparaison();
  init_recherche_index();
  t_PileDescripteur pile_image;
  t_PileDescripteur pile_texte;
  t_PileDescripteur * temp_texte;
  t_PileDescripteur * temp_image;
  init_pile(&pile_image);
  init_pile(&pile_texte);

  genPileDescripteur(&pile_image,"image");
  genPileDescripteur(&pile_texte,"texte");

  printf("\t++++++++++++++++++\n\t+Projet Fil Rouge+\n\t+RedStringGroupe 5        +\n\t++++++++++++++++++\n");
  /*cette fonction permet de réaliser des tests basiques dans notre appli*/
  char  seuilIndexTexte[4];

  char choixIndexation1[2],  choixUser1[2], continuer[2];//(permet de choisir de continuer ou non le test);;
  char choixMode[2];
 // char continuerCompar[2]={'0', '\0'};
  int c;//pour le vidage du buffer d'entrée

  char  cheminImage[TAILLECHAINE];           //type d'image recherchee par l'user et chemin de l'imagee
  char resumePartie[2];
  do{
    int choixAdmin = 1;
    do{
        int retour = 1;
        do{

        }while(retour == 0);
        system("clear");
        printf("\t++++++++++++++++++\n\t+Projet Fil Rouge+\n\t+RedStringGroupe 5+\n\t++++++++++++++++++\n");
        printf("\n\nQuel type d'utilisateur etes-vous?\n*1.Admin\n*2.Utilisateur\n*3.Quitter\n");
        scanf("%s", choixMode);
        printf("%s\n", choixMode);
        while ( ((c = getchar()) != '\n') && c != EOF);
        system("clear");

        choixAdmin = 1;
        switch (choixMode[0]) {
              case '1':
                do /*|| (continuerCompar=='1')*/
                {
                  printf("+++++++Vous etes en mode administrateur!++++++++\n\n");
                  printf("\t+++++++++++++++++++++++++\n\t+Que voulez-vous faire ?+\n\t+++++++++++++++++++++++++\n\n");
                  printf("*1.Indexation image\n*2.Indexation texte\n*3.Indexation son\n*4.Fichier config\n*5.Quitter\n");
                  scanf("%s", choixIndexation1);
                  while ( ((c = getchar()) != '\n') && c != EOF);
                  switch (choixIndexation1[0])
                  {
                    case '1':
                        printf("Indexation des images ...\n" );
                        temp_image = malloc(sizeof(t_PileDescripteur));
                        init_pile(temp_image);
                        indexationImage(temp_image);
                        int nbDesc = 0;
                        do{
                            printf("%d ont été généré, combien voulez-vous en afficher ?\n",taille_pile(*temp_image) );
                            char nbDesc_ch[10];
                            scanf("%s",nbDesc_ch);
                            while ( ((c = getchar()) != '\n') && c != EOF);
                            nbDesc = strtol(nbDesc_ch,(char**)NULL,10);
                        }while(nbDesc>taille_pile(*temp_image));
                        int i = 0;
                        if(!pile_est_vide(*temp_image)){
                    		t_CellDescripteur *suivant;
                    		suivant = temp_image->premier;
                    		while(suivant->p_suivant!=NULL && i<nbDesc-1){
                    			printf("%s \n",suivant->descripteur);
                                i++;
                    			suivant = suivant->p_suivant;
                                printf("Entrer pour continuer...");
                                while((c = getchar())!= '\n' && c!=EOF);
                                system("clear");
                    		}
                    		printf("%s", suivant->descripteur);
                    	}
                        free(temp_image);

                    break;

                    case '2':
                      printf("Entrer le nombre de mot récurrent maximum (0<nbMot<6):\n");
                      scanf("%s", seuilIndexTexte);
                      while ( ((c = getchar()) != '\n') && c != EOF);
                      int nbMot = 5;
                      nbMot = strtol(seuilIndexTexte,(char**)NULL,10);
                      int correct = 1;
                      do{
                          correct = 1;
                          if(nbMot>0 && nbMot <6){
                                  printf("Indexation des textes ...\n" );
                                  temp_texte = malloc(sizeof(t_PileDescripteur));
                                  init_pile(temp_texte);
                                  indexationTexte(temp_texte, nbMot);
                                  int nbDesc = 0;
                                  do{
                                      printf("%d ont été généré, combien voulez-vous en afficher?\n",taille_pile(*temp_texte) );
                                      char nbDesc_ch[10];
                                      scanf("%s",nbDesc_ch);
                                      while ( ((c = getchar()) != '\n') && c != EOF);
                                      nbDesc = strtol(nbDesc_ch,(char**)NULL,10);
                                  }while(nbDesc>taille_pile(*temp_texte));
                                  int i = 0;
                                  if(!pile_est_vide(*temp_texte)){
                                      t_CellDescripteur *suivant;
                                      suivant = temp_texte->premier;
                                      while(suivant->p_suivant!=NULL && i<nbDesc-1){
                                          printf("%s \n",suivant->descripteur);
                                          i++;
                                          suivant = suivant->p_suivant;
                                          printf("Entrer pour continuer...");
                                          while((c = getchar())!= '\n' && c!=EOF);
                                          system("clear");
                                      }
                                      printf("%s", suivant->descripteur);
                                  }
                                  free(temp_texte);
                          }else{
                            printf("\n\tVous n'avez pas choisi un bon seuil d'indexation!\n");
                            correct = 0;
                          }
                      }while(correct == 0);
                      break;

                    case '3':
                        printf("WORK IN PROGRESS\n");
                    break;
                    case '4':
                        printf("Ouverture du fichier config.txt");
                        char chemin[100];
                        strcpy(chemin,"gedit ");
                        strcat(chemin,CHEMIN);
                        strcat(chemin,"/config.txt");
                        strcat(chemin, " &");
                        system(chemin);
                    break;
                    case '5':
                    break;
                    default:
                        printf("\n\nVous n'avez pas fait le bon choix du type d'indexation!\n");
                    break;
                  }
                  printf("\nvoulez-vous oursuivre les textes ?\n**1:oui\n**0: non\n");
                  scanf("%s", continuer);
                  while ( ((c = getchar()) != '\n') && c != EOF);
                  system("clear");
                  if(continuer[0]!='1')// s'il choisit de ne pas continuer les tests!
                    printf("Merci d'etre passer!\n");
                }while(continuer[0]=='1');
                break;

              case '2':
                do
                {
                  printf("+++++++++++ Mode utilisateur!++++++++\n\n");
                  printf("\t+++++++++++++++++++++++++++++\n\t+Que voulez-vous rechercher?+\n\t+++++++++++++++++++++++++++++\n");
                  printf("\n**1.Fichier Texte\n");
                  printf("**2.Fichier Image\n");
                  printf("**3.Fichier Audio\n**.4Quitter\n");
                  scanf("%s", choixUser1);
                  while ( ((c = getchar()) != '\n') && c != EOF);
                  switch (choixUser1[0])
                  {
                    case '1':
                      printf("\t+++++++++recherche d'un fichier texte++++++++++\n");
                      char choixTexte[10];
                      int choix_incorrect =1;
                      do{
                          choix_incorrect=1;
                          printf("**1.Comparaison de document\n**2.Recherche mot cles\n");
                          if(scanf("%s",choixTexte)){
                              while ( ((c = getchar()) != '\n') && c != EOF);
                              switch(choixTexte[0]){
                                  case '1' :
                                        comparaison_moteur_texte(pile_texte);
                                  break;
                                  case '2':
                                        recherche_index(pile_texte);
                                  break;
                                  default :
                                      printf("ERREUR : choix incorrect\n" );
                                      choix_incorrect = 0;
                                  break;
                              }
                          }
                      }while(choix_incorrect == 0);
                      break;
                    case '2':
                      system("clear");
                      printf("++++++++ mode utilisateur!++++++++\n\n++++++++ Image ++++++++\n\n");

                      char ext[5];
                      char nom[30];
                      int fic_trouve = 1;
                      do{
                          printf("Entrez le nom de l'image (avec extension) (appuyer deux foix sur entrer après la saisie):\n");
                          if (fgets(cheminImage, 10, stdin)!=0){
                              while ( ((c = getchar()) != '\n') && c != EOF);
                                char *token;
                                /* get the first token */
                                token = strtok(cheminImage,".");
                                /* walk through other tokens */
                                while( token != NULL ){
                                    if(strpbrk(token,"bmp")|| strpbrk(token,"jpg")){
                                        strcpy(ext,token);
                                    }else{
                                        strcpy(nom,token);
                                    }
                                   token = strtok(NULL, cheminImage);
                                }
                                if(strlen(ext)>0){
                                    char chemin[TAILLECHAINE+strlen(CHEMIN)];
                                    strcpy(chemin, CHEMIN);
                                    if(strpbrk(ext,"bm")){
                                        strcat(chemin,"/Data/IMG_NG/");
                                    }else if(strpbrk(ext,"jg")){
                                        strcat(chemin,"/Data/IMG_RGB/");
                                    }
                                    t_Fichier temp;
                                    temp.chemin_nom = malloc(sizeof(char)*strlen(chemin)+20);
                                    temp.chemin_info = malloc(sizeof(char)*strlen(chemin)+20);
                                    strcpy(temp.chemin_nom,chemin) ;
                                    strcat(temp.chemin_nom,strcat(strcat(cheminImage,"."),ext));
                                    printf("Recherche d'image semblable à :%s\n",cheminImage );
                                    strcpy(temp.chemin_info,chemin);
                                    strcat(temp.chemin_info,nom);
                                    strcat(temp.chemin_info,".txt");
                                    if(fopen(temp.chemin_info,"r")!=NULL){
                                        temp.type = "image";
                                        t_PileDescripteur resultat;
                                        init_pile(&resultat);
                                        comparaisonImage(temp, pile_image,&resultat);
                                        if(!pile_est_vide(resultat)){
                                            t_CellDescripteur *suivant;
                                            suivant = resultat.premier;
                                            char * ligne;
                                            char currentCar;
                                            int i;
                                            while(suivant->p_suivant!=NULL){
                                                ligne = malloc(sizeof(char)*200);
                                                i=0;
                                                currentCar = suivant->descripteur[i];
                                                while(currentCar != '\n'){
                                                    strcat(ligne,&currentCar);
                                                    i++;
                                                    currentCar = suivant->descripteur[i];
                                                }
                                                if(strstr(temp.chemin_nom,ligne)==NULL)
                                                    printf("%s\n",ligne );
                                                suivant = suivant->p_suivant;
                                            }
                                            ligne = malloc(sizeof(char)*200);
                                            i=0;
                                            currentCar = suivant->descripteur[i];
                                            while(currentCar != '\n'){
                                                strcat(ligne,&currentCar);
                                                i++;
                                                currentCar = suivant->descripteur[i];
                                            }
                                            if(strstr(temp.chemin_nom,ligne)==NULL)
                                                printf("%s\n",ligne );
                                            break;
                                        }
                                    }else{
                                        printf("ERREUR : Fichier introuvable.\n" );
                                        fic_trouve = 0;
                                    }
                                }
                          }
                      }while(strlen(ext)<=0 || fic_trouve == 0);
                      break;
                    case '3':
                      printf("WORK IN PROGRESS\n\nRecherche de fichier son non implémentée.");
                      /*printf("Entrez le chemin du fichier Audio a rechercher!\n");
                      if (fgets(cheminFicAudio, TAILLECHAINE, stdin)!=NULL) {
                        retirerEspaceChaine(cheminFicAudio);
                        printf("\tICI affichage des sons contenant le mot saisie par l'user!\n");
                        printf("%s\n", chaineSansEspace);
                    }*/
                      break;
                    case '4':
                    break;
                    default:
                        printf("\tVous n'avez pas fait le bon choix du type de fichier a rechercher!\n");
                    break;
                  }
                  printf("\nvoulez-vous poursuivre la recherche?\n**1:oui\n**0: non\n");
                  scanf("%s", continuer);
                  while ( ((c = getchar()) != '\n') && c != EOF);
                  system("clear");
                }while (continuer[0]=='1');
                break;

              case '3':
              break;
              default:
                printf("Vous n'avez pas fait le bon choix de mode!\n");
                choixAdmin = 0;
                break;
            }

      }while(choixAdmin == 0);
      printf("\nVoulez-vous quittez ?\n**1:oui\n**2: non\n");
      scanf("%s", resumePartie);
      while ( ((c = getchar()) != '\n') && c != EOF);
      system("clear");
      if (resumePartie[0]!='2') {
        printf("Ravi de vous avoir eu parmi nous!\n");
      }

}while(resumePartie[0]=='2');
return 1;
}//fin de la fonction

int main(int argc, char const *argv[]) {
  interfaceMoteur();
  return 0;
}
