#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interfaceMoteur.h"
#include "../Indexation/controlleurIndexation.h"

#define TAILLECHAINE 500

int* choixIndexation=NULL;
int* choixDescripComp=NULL;//memorise le choix du type de descripteurs a tester
int *seuilDescripImg1=NULL;


int interfaceMoteur()
{
    char CHEMIN[100];
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
  printf("\t++++++++++++++++++\n\t+Projet Fil Rouge+\n\t+RedStringGroupe 5        +\n\t++++++++++++++++++\n");
  /*cette fonction permet de réaliser des tests basiques dans notre appli*/
  char choixUser;
  int choixIndexation1, seuilIndexTexte, nbitQuantif, choixTestDescrip;//correspond au mode choisi par l'user
  int seuilDescripImg;  //correspond au seuil de Comparaison descripteurs images
  int seuilDescripText; //correspond au seuil de Comparaison descripteurs textes
  int seuilDescripSon;  //correspond au seuil de Comparaison descripteurs Sons
  int continuer=1;      //permet de continuer ou non le test
  int nbreEchantillon, nbreIntervalles; //parametre pour creer descripteurs son.
  int continuerCompar=0;
  int choixUser1;//represente, le type de fichiers que l'user recherche.
  char chaine[TAILLECHAINE];//tableau contenant le critere de recherche de,
  char *position = NULL;//(capte la position du "\n" dana la chaine recu de l'entrée")
  //while(continuer)
  //{
  while(1){

      printf("\n\nQuel type d'utilisateur etes-vous?\n*1.Admin\n*2.Utilisateur\n");
      scanf("%s", &choixUser);
      system("clear");
    //  if(strcmp(choixUser,"1"));
      switch (choixUser) {
        case '1':
        while(continuer==1 || continuerCompar!=1)
        {
          printf("\n\n+++++++Vous etes en mode administrateur!++++++++\n\n");
          printf("\t+++++++++++++++++++++++++\n\t+Que voulez-vous tester?+\n\t+++++++++++++++++++++++++\n\n");
          printf("*1.Indexation image\n*2.Indexation texte\n*3.Indexation son\n*4.Comparaison\n");
          scanf("%d", &choixIndexation1);
          system("clear");
          switch (choixIndexation1)
          {

            case 1:
              printf("Definir le nombre de bits pour la quantification! ");
              scanf("%d",&nbitQuantif);
              choixIndexation=&choixIndexation1;

              //indexationImage(nbitQuantif);
              printf("\n\t//ICI affichage des descripteurs images apres execution\n\t de la fonction precedente.\n\n");//visualisation des descripteurs apres execution de la fonction precedente.
              printf("\nvoulez-vous poursuivre le test ?\n**1:oui\n**0: non\n");
              scanf("%d", &continuer);
              //return nbitQuantif;
              break;

            case 2:
              printf("Definir le seuil de l'indexation!(nbres d'occs de mots)\n");
              scanf("%d", &seuilIndexTexte);
              choixIndexation=&choixIndexation1;

              //indexationTexte(seuilIndexTexte);
              //visualisation des descripteurs textes apres cette fonction
              printf("\n\tICI********visualisation des descripteurs\n\n");

              printf("\nvoulez-vous poursuivre le test ?\n**1:oui\n**0: non\n");
              scanf("%d", &continuer);
              //return seuilIndexTexte;
              break;

            case 3:
              choixIndexation=&choixIndexation1;
              printf("Definir le nombre d'echantillon pour une fenetre!");
              scanf("%d", &nbreEchantillon);
              printf("Definir le nombre d'intervalles pour le calcul de l'histogramme ");
              scanf("%d", &nbreIntervalles);

              //indexationSon(nbreEchantillon, nbreIntervalles);
              //on appele la fonction d'indexationSon et on lui passe les param de configuration.
              printf("\n\tICI********visualisation des descripteurs\n\n");

              printf("\nvoulez-vous poursuivre le test ?\n**1:oui\n**0: non\n");
              scanf("%d", &continuer);
              break;
            case 4:
            continuerCompar=1;
            do
            {
              choixIndexation=&choixIndexation1;
              printf("\t\n+++++Test de la Comparaison++++++\n\n");
              printf("\t++++++++++++++++++++++++++++++++++++++++\n\t+Quels descripteurs voulez-vous tester?+\n\t++++++++++++++++++++++++++++++++++++++++\n");
              printf("**1.Descripteur image\n**2.Descripteur texte\n**3.Descripteur son\n");
              scanf("%d",&choixTestDescrip);

              if (choixTestDescrip==1)
              {
                choixDescripComp=&choixTestDescrip;
                printf("Entrez le seuil de Comparaison des descripteurs type image\n");
                scanf("%d", &seuilDescripImg);
                //valeur a envoyer a la fonction de comparaison
                //en retour, affichage de descripteurs similaires
                printf("\n\tICI***affichage des descripteurs similaires!\n\n");

                printf("\nvoulez-vous poursuivre le test des descripteurs ?\n**1:oui\n**0: non\n");
                scanf("%d", &continuerCompar);
                //return seuilDescripImg;
              }
              else if (choixTestDescrip==2)
              {
                choixDescripComp=&choixTestDescrip;
                printf("Entrez le seuil de Comparaison des descripteurs type textes\n");
                scanf("%d", &seuilDescripText);
                //valeur a envoyer a la fonction de comparaison
                //en retour, affichage de descripteurs similaires
                printf("\n\tICI***affichage des descripteurs similaires!\n\n");

                printf("\nvoulez-vous poursuivre le test des descripteurs ?\n**1:oui\n**0: non\n");
                scanf("%d", &continuerCompar);
                //return seuilDescripText;
              }

              else if (choixTestDescrip==3)
              {
                choixDescripComp=&choixTestDescrip;
                printf("Entrez le seuil de Comparaison des descripteurs type son\n");
                scanf("%d", &seuilDescripSon);
                //valeur a envoyer a la fonction de comparaison
                //en retour, affichage de descripteurs similaires
                printf("\n\tICI***affichage des descripteurs similaires!\n\n");

                printf("\nvoulez-vous poursuivre le test des descripteurs ?\n**1:oui\n**0: non\n");
                scanf("%d", &continuerCompar);
                //return seuilDescripSon;
              }

            }while(continuerCompar==1);
            break;
            default:
                printf("\n\nVous n'avez pas fait le bon choix\n");
          }
          if(continuer==0)
            printf("Merci d'etre passer!\n");
        }
        break;
        case '2':
          while (continuer==1) {
            printf("\n\n+++++++Vous etes en mode utilisateur!++++++++\n\n");
            printf("\t+++++++++++++++++++++++++++++\n\t+Que voulez-vous rechercher?+\n\t+++++++++++++++++++++++++++++\n");
            printf("\n**1.Fichier Texte\n");
            printf("**2.Fichier Image\n");
            printf("**3.Fichier Audio\n");
            scanf("%d", &choixUser1);
            switch (choixUser1)
            {
              case 1 :
                printf("Entrez le nom d'un document a rechercher ou un mot clé a rechercher!\n");
                fgets(chaine, TAILLECHAINE, stdin);
                printf("%s", chaine);
                /* On lit le texte saisi au clavier
                if (fgets(chaine, TAILLECHAINE, stdin) != NULL)  // Pas d'erreur de saisie ?
                {
                    position = strchr(chaine, '\n'); // On recherche l'"\n"
                    if (position != NULL)
                        *position = '\0'; // On remplace ce caractère par \0
                }
                else
                  fprintf(stderr,"saisie pas bonne:taille trop grande!\n");//En cas d'erreur
                printf("%s", chaine);//*/

                printf("\nvoulez-vous poursuivre la recherche?\n**1:oui\n**0: non\n");
                scanf("%d", &continuer);
              break;
              case 2:
                printf("Quel type d'images recherchez-vous?\n**1.noir/blanc\n**2.couleur");
                //scanf("%d")

                printf("\nvoulez-vous poursuivre la recherche?\n**1:oui\n**0: non\n");
                scanf("%d", &continuer);
                break;
              case 3:
                printf("Entrez le mot prononcé á rechercher dans le fichier Audio!\n");
                scanf("%s", chaine);

                //

                printf("\nvoulez-vous poursuivre la recherche?\n**1:oui\n**0: non\n");
                scanf("%d", &continuer);
                break;
            }
          }
          break;

        default:
          printf("Choix incorrect !\n");

      }
  }
  return 1;
  //}

}

int main(int argc, char const *argv[]) {

  int resultat= interfaceMoteur();
  return 0;
}
