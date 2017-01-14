#include <stdio.h>
#include <stdlib.h>
#include "comparaison.h"

#define seuil 90

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

    genDescripteurTexte(fichierCompare, &descripteurs_ficCompare);
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
    //TODO
    return 0;
}

int compareFichierSon(char * fichierDonne , char * fichierCompare){
    //TODO
    return 0;
}
int compareFichierTexte(char * fichierDonne , char * fichierCompare){
    //TODO
    return 0;
}
