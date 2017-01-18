#include <stdio.h>
#include <stdlib.h>
#include "comparaison.h"

int seuil;
char CHEMIN[100];

void init_comparaison(){
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

    //Variable pour le seuil et recupération dans le fichier config.txt
    char seuil_txt[10];
    char seuiTXTBON[4];
    system("cat ../config.txt | grep seuil>temp.txt");
    FILE * ptr_tempSeuil;
    ptr_tempSeuil = fopen("temp.txt","r");
    while(!feof(ptr_tempSeuil)){
        fscanf(ptr_tempSeuil,"%s",seuil_txt);
    }
    fclose(ptr_ficChemin);
    system("rm temp.txt");
    strtok(seuil_txt,":");
    seuiTXTBON[0] =seuil_txt[1] ;
    seuiTXTBON[1] = seuil_txt[2];
    sscanf(seuiTXTBON,"%d",&seuil);
}

int comparaisonImage(t_Fichier fichierCompare, t_PileDescripteur pileImage,t_PileDescripteur * descripteur_similaire){
    char * fichierDonne;//Descripteur du fichier a comparer.
    int pourcentage =0; //Pourcentage de similarité du document comparé.

    //Initialisation des piles
    t_PileDescripteur descripteurs_ficCompare;//Pile utilisée pour gen le descripteur du fichier donné.
    init_pile(&descripteurs_ficCompare);
    init_pile(descripteur_similaire);

    //Génération du déscripteur du fichier donné
    genDescripteurImage(fichierCompare, &descripteurs_ficCompare);
    fichierDonne = descripteurs_ficCompare.premier->descripteur;

    if(!pile_est_vide(pileImage)){
		t_CellDescripteur *suivant;
		suivant = pileImage.premier;

		while(suivant->p_suivant!=NULL){//On parcours la pile
            //Comparaison du fichier courant a celui donné en paramétre.
            pourcentage = compareFichierImage(fichierDonne,suivant->descripteur );
            //On compare le pourcentage au seuil passé en paramètre
            if(pourcentage >= seuil){
                //Si vrai on rajoute le descripteur dans la pile des descripteur similaire.
                empile(descripteur_similaire,suivant->descripteur);
            }
			suivant = suivant->p_suivant;
		}
        //Comparaison avec le dernier descripteur.
         pourcentage = compareFichierImage(fichierDonne,suivant->descripteur );
         if(pourcentage >= seuil){
             empile(descripteur_similaire,suivant->descripteur);
         }

         return 1;//Vrai si tout c'est bien passé
	}
    return 0;//Faux si la pile de descripteur est vide.
}

//Fonctionnement identique a comparaisonImage
int comparaisonSon(t_Fichier fichierCompare, t_PileDescripteur pileSon,t_PileDescripteur *descripteur_similaire){
    char * fichierDonne;
    int pourcentage =0;

    t_PileDescripteur descripteurs_ficCompare;
    init_pile(&descripteurs_ficCompare);
    init_pile(descripteur_similaire);

    genDescripteurSon(fichierCompare, &descripteurs_ficCompare);
    fichierDonne = descripteurs_ficCompare.premier->descripteur;

    if(!pile_est_vide(pileSon)){
		t_CellDescripteur *suivant;
		suivant = pileSon.premier;

		while(suivant->p_suivant!=NULL){
            pourcentage = compareFichierSon(fichierDonne,suivant->descripteur );
            if(pourcentage >= seuil){
                empile(descripteur_similaire,suivant->descripteur);
            }
			suivant = suivant->p_suivant;
		}
         pourcentage = compareFichierSon(fichierDonne,suivant->descripteur );
         if(pourcentage >= seuil){
             empile(descripteur_similaire,suivant->descripteur);
         }

         return 1;
	}
    return 0;
}

//Fonctionnement identique a comparaisonImage
int comparaisonTexte(t_Fichier fichierCompare, t_PileDescripteur pileTexte,t_PileDescripteur *descripteur_similaire){
    char * fichierDonne;
    int pourcentage =0;

    t_PileDescripteur descripteurs_ficCompare;
    init_pile(&descripteurs_ficCompare);
    init_pile(descripteur_similaire);

    genDescripteurTexte(fichierCompare, &descripteurs_ficCompare, CHEMIN);
    fichierDonne = descripteurs_ficCompare.premier->descripteur;

    if(!pile_est_vide(pileTexte)){
        t_CellDescripteur *suivant;
        suivant = pileTexte.premier;

        while(suivant->p_suivant!=NULL){
            pourcentage = compareFichierTexte(fichierDonne,suivant->descripteur );
            if(pourcentage >= seuil){
                empile(descripteur_similaire,suivant->descripteur);
            }
            suivant = suivant->p_suivant;
        }
         pourcentage = compareFichierTexte(fichierDonne,suivant->descripteur );
         if(pourcentage >= seuil){
             empile(descripteur_similaire,suivant->descripteur);
         }

         return 1;
    }
    return 0;
}

int compareFichierImage(char * fichierDonne , char * fichierCompare){
  ILE * ptr_ficDonne;
  FILE * ptr_ficCompare;
  int valDonne, valCompare, nbCouleurDonne, nbCouleurCompare, cpt=0, diff=0;
  float resultat;
  ptr_ficDonne=fopen("tempDonne", "w");
  fprintf(ptr_ficDonne, "%s", fichierDonne);
  fclose(ptr_ficDonne);
  ptr_ficCompare=fopen("tempCompare", "w");
  fprintf(ptr_ficCompare, "%s", fichierCompare);
  fclose(ptr_ficCompare);

  ptr_ficDonne=fopen("tempDonne", "r");
  ptr_ficCompare=fopen("tempCompare", "r");
  fscanf(ptr_ficDonne, "%*s %d", &nbCouleurDonne);
  fscanf(ptr_ficCompare, "%*s %d", &nbCouleurCompare);

  if(nbCouleurDonne==nbCouleurCompare)
  {
    while(!feof(ptr_ficDonne))
    {
      fscanf(ptr_ficDonne, "%*d %d", &valDonne);
      fscanf(ptr_ficCompare, "%*d %d", &valCompare);
      cpt+=valDonne;
      diff+=abs(valDonne-valCompare);
    }

    fclose(ptr_ficDonne);
    fclose(ptr_ficCompare);
    resultat=(1-((float)diff/cpt))*100;
    diff=resultat;
    system("rm tempCompare");
    system("rm tempDonne");
    if(resultat<0)
    {
      return 0;
    }
    return abs(resultat);
  }
  system("rm tempCompare");
  system("rm tempDonne");
  return -1;
}

int compareFichierSon(char * fichierDonne , char * fichierCompare){
    //TODO
    return 0;
}
int compareFichierTexte(char * fichierDonne , char * fichierCompare){
    //TODO
    return 0;
}
