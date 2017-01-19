#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interfaceMoteur.h"
#include "../Indexation/controlleurIndexation.h"
#include "../Comparaison/comparaison.h"
#include "../Comparaison/recherche_index.h"


#define TAILLECHAINE 500

char* choixIndexation=NULL;
char* choixDescripComp=NULL;//memorise le choix du type de descripteurs a tester
int *seuilDescripImg1=NULL;
char chaineSansEspace[TAILLECHAINE]={'a'};//nvelle chaine contenant le critere de recherche

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
  t_PileDescripteur pile_image;
  t_PileDescripteur pile_texte;
  init_pile(&pile_image);
  init_pile(&pile_texte);

  genPileDescripteur(&pile_image,"image");
  genPileDescripteur(&pile_texte,"texte");

  printf("\t++++++++++++++++++\n\t+Projet Fil Rouge+\n\t+RedStringGroupe 5        +\n\t++++++++++++++++++\n");
  /*cette fonction permet de réaliser des tests basiques dans notre appli*/
  int  seuilIndexTexte=0;
  int nbitQuantif=0;//correspond au mode choisi par l'user

  char choixIndexation1[2],  choixTestDescrip[2], choixUser1[2], continuer[2];//(permet de choisir de continuer ou non le test);;
  char choixMode[2];
  char continuerCompar[2]={'0', '\0'};

  int seuilDescripImg=0;  //correspond au seuil de Comparaison descripteurs images
  int seuilDescripText=0; //correspond au seuil de Comparaison descripteurs textes
  int seuilDescripSon=0;  //correspond au seuil de Comparaison descripteurs Sons
  int nbreEchantillon=0, nbreIntervalles=0; //parametre pour creer descripteurs son.
  int c;//pour le vidage du buffer d'entrée

  char chaine[TAILLECHAINE]={'a'};//tableau contenant le critere de recherche de,
  //char chaineSansEspace[TAILLECHAINE]={'a'};//nvelle chaine contenant le critere de recherche
  char imageRecherchee[2], cheminImage[TAILLECHAINE], cheminFicAudio[TAILLECHAINE];           //type d'image recherchee par l'user et chemin de l'imagee
  char resumePartie[2];
//  char *positionEntree=NULL;

  do
  {
    system("clear");
    printf("\t++++++++++++++++++\n\t+Projet Fil Rouge+\n\t+RedStringGroupe 5+\n\t++++++++++++++++++\n");
    printf("\n\nQuel type d'utilisateur etes-vous?\n*1.Admin\n*2.Utilisateur\n");
    scanf("%s", choixMode);
    printf("%s\n", choixMode);
    while ( ((c = getchar()) != '\n') && c != EOF);
    system("clear");

      switch (choixMode[0]) {
        case '1':
          do /*|| (continuerCompar=='1')*/
          {
            printf("+++++++Vous etes en mode administrateur!++++++++\n\n");
            printf("\t+++++++++++++++++++++++++\n\t+Que voulez-vous tester?+\n\t+++++++++++++++++++++++++\n\n");
            printf("*1.Indexation image\n*2.Indexation texte\n*3.Indexation son\n*4.Comparaison\n");
            scanf("%s", choixIndexation1);
            while ( ((c = getchar()) != '\n') && c != EOF);
            switch (choixIndexation1[0])
            {
              case '1':
                nbitQuantif=0;
                printf("Definir le nombre de bits pour la quantification! ");
                scanf("%d",&nbitQuantif);
                while ( ((c = getchar()) != '\n') && c != EOF);
                //choixIndexation=&choixIndexation1;
                if (nbitQuantif>0) {
                  //indexationImage(nbitQuantif);
                  printf("\n\t//ICI affichage des descripteurs images apres execution\n\n");
                  //visualisation des descripteurs apres execution de la fonction precedente.
                }
                else {
                  printf("\tLe nombre de bits de quantification doit etre un nombre positif\n");
                }
                break;

              case '2':
                seuilIndexTexte=0;//on reinitialise
                printf("Definir le seuil de l'indexation!(nbres d'occs de mots) ");
                scanf("%d", &seuilIndexTexte);
                while ( ((c = getchar()) != '\n') && c != EOF);
                //choixIndexation=&choixIndexation1;
                if(seuilIndexTexte>0) {
                  //indexationTexte(seuilIndexTexte);
                  //visualisation des descripteurs textes apres cette fonction
                  printf("\n\tICI********visualisation des descripteurs textes\n\n");
                }
                else{
                  printf("\n\tVous n'avez pas choisi un bon seuil d'indexation!\n");
                }
                break;

              case '3':
                nbreEchantillon=0;
                nbreIntervalles=0;
                //choixIndexation=&choixIndexation1;
                printf("Definir le nombre d'echantillon(s) pour une fenetre! ");
                scanf("%d", &nbreEchantillon);
                while ( ((c = getchar()) != '\n') && c != EOF);
                printf("Definir le nombre d'intervalle(s) pour le calcul de l'histogramme ");
                scanf("%d", &nbreIntervalles);
                while ( ((c = getchar()) != '\n') && c != EOF);
                if (nbreEchantillon>0 && nbreIntervalles>0) {
                  //indexationSon(nbreEchantillon, nbreIntervalles);
                  //on appele la fonction d'indexationSon et on lui passe les param de configuration.
                  printf("\n\tICI********visualisation des descripteurs\n\n");
                }
                else{
                  printf("\tCes deux valeurs doivent etre positives!\n");
                }
                break;
              case '4':
                system("clear");
                do
                {
                  printf("+++++++Vous etes en mode administrateur!++++++++\n\n");//on reecrit vous etes en mode admin
                  //choixIndexation=&choixIndexation1;
                  printf("\t\n+++++Test de la Comparaison++++++\n\n");
                  printf("\t++++++++++++++++++++++++++++++++++++++++\n\t+Quels descripteurs voulez-vous tester?+\n\t++++++++++++++++++++++++++++++++++++++++\n");
                  printf("**1.Descripteur image\n**2.Descripteur texte\n**3.Descripteur son\n");
                  scanf("%s",choixTestDescrip);

                  switch (choixTestDescrip[0])
                  {
                    case '1':
                      //choixDescripComp=&choixTestDescrip;
                      seuilDescripImg=0;
                      printf("Entrez le seuil de Comparaison des descripteurs type image\n");
                      scanf("%d", &seuilDescripImg);
                      while ( ((c = getchar()) != '\n') && c != EOF);
                      if (seuilDescripImg>0) {
                        //valeur a envoyer a la fonction de comparaison
                        //en retour, affichage de descripteurs similaires
                        printf("\n\tICI***affichage des descripteurs similaires!\n\n");
                      }
                      else{
                        printf("\tVous n'avez pas entre le bon seuil de comparaison!\n");
                      }
                      break;

                    case '2':
                      //choixDescripComp=&choixTestDescrip;
                      seuilDescripText=0;
                      printf("Entrez le seuil de Comparaison des descripteurs type textes\n");
                      scanf("%d", &seuilDescripText);
                      while ( ((c = getchar()) != '\n') && c != EOF);
                      if (seuilDescripText>0) {
                        //valeur a envoyer a la fonction de comparaison
                        //en retour, affichage de descripteurs similaires
                        printf("\n\tICI***affichage des descripteurs similaires!\n\n");
                      }
                      else{
                        printf("\tLe seuil doit etre un nombre positif \n");
                      }
                      break;

                    case '3':
                      //choixDescripComp=&choixTestDescrip;
                      seuilDescripSon=0;
                      printf("Entrez le seuil de Comparaison des descripteurs type son\n");
                      scanf("%d", &seuilDescripSon);
                      while ( ((c = getchar()) != '\n') && c != EOF);
                      if (seuilDescripSon) {
                        //valeur a envoyer a la fonction de comparaison
                        //en retour, affichage de descripteurs similaires
                        printf("\n\tICI***affichage des descripteurs similaires!\n\n");
                      }
                      else{
                        printf("\tLe seuil doit etre un nombre positif!\n");
                      }

                      break;
                    default:
                      printf("\tVous n'avez pas fait le bon choix du type de descripteurs a tester\n");
                  }
                  printf("\nvoulez-vous poursuivre le test des descripteurs ?\n**1:oui\n**0: non\n");
                  scanf("%s", continuerCompar);
                  while ( ((c = getchar()) != '\n') && c != EOF);
                  system("clear");
                }while(continuerCompar[0]=='1');
                break;
              default:
                  printf("\n\nVous n'avez pas fait le bon choix du type d'indexation!\n");
            }
            printf("\nvoulez-vous poursuivre le test de l'indexation et de la comparaison?\n**1:oui\n**0: non\n");
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
            printf("**3.Fichier Audio\n");
            scanf("%s", choixUser1);
            while ( ((c = getchar()) != '\n') && c != EOF);
            switch (choixUser1[0])
            {
              case '1':
                printf("\t+++++++++recherche d'un fichier texte++++++++++\n");
                printf("Entrez le chemin du document a rechercher ou un mot clé a rechercher!\n");
                //scanf("%s", chaine);//
                //fgets(chaine, TAILLECHAINE, stdin);

                if(fgets(chaine, TAILLECHAINE, stdin)!=NULL){
                  retirerEspaceChaine(chaine);
                  //printf("\n\n%s\n", chaineSansEspace);
                  printf("\t**Documents +++ trouves ICI!\n");
                }//*/
                break;
              case '2':
                system("clear");
                printf("++++++++ mode utilisateur!++++++++\n\n++++++++ Image ++++++++\n\n");

                 char ext[5];
                char nom[30];
                int fic_trouve = 1;
                do{
                      printf("Entrez le nom de l'image (avec extension):\n");
                      if (fgets(cheminImage, TAILLECHAINE, stdin)!=NULL) {

    //                    retirerEspaceChaine(cheminImage);
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
                                      printf("%s\n",ligne );
                                  }
                                  //affiche_pile(resultat);
                              }else{
                                  printf("ERREUR : Fichier introuvable.\n" );
                                  fic_trouve = 0;
                              }
                          }

                      }
                }while(strlen(ext)<=0 ||fic_trouve == 0);
                //     printf("\tICI affichage des images correspondant au chemin saisie par l'user!\n");

                break;
              case '3':
                printf("Entrez le chemin du fichier Audio a rechercher!\n");
                if (fgets(cheminFicAudio, TAILLECHAINE, stdin)!=NULL) {
                  retirerEspaceChaine(cheminFicAudio);
                  printf("\tICI affichage des sons contenant le mot saisie par l'user!\n");
                  printf("%s\n", chaineSansEspace);
                }
                break;
              default:
                  printf("\tVous n'avez pas fait le bon choix du type de fichier a rechercher!\n");
            }
            printf("\nvoulez-vous poursuivre la recherche?\n**1:oui\n**0: non\n");
            scanf("%s", continuer);
            while ( ((c = getchar()) != '\n') && c != EOF);
            system("clear");
          }while (continuer[0]=='1');
          break;

        default:
          printf("Vous n'avez pas fait le bon choix de mode!\n");
      }
      printf("\nvoulez-vous poursuivre la recherche?\n**1:oui\n**0: non\n");
      scanf("%s", resumePartie);
      while ( ((c = getchar()) != '\n') && c != EOF);
      system("clear");
      if (resumePartie[0]!=1) {
        printf("Ravi de vous avoir eu parmi nous!\n");
      }

}while(resumePartie[0]=='1');
return 1;
}//fin de la fonction

int main(int argc, char const *argv[]) {
  interfaceMoteur();
  return 0;
}
