#ifndef _COMPARAISON_H
#define _COMPARAISON_H

#include "../Indexation/Fichier.h"
#include "../Indexation/pileDescripteur.h"
#include "../Indexation/indexationImage.h"
#include "../Indexation/indexationTexte.h"
#include "../Indexation/indexationSon.h"



/*
Ces méthodes permettent de comparer un fichier a un autre de la base.
*/
int comparaisonImage(t_Fichier fichierDonne, t_PileDescripteur pileImage, t_PileDescripteur *descripteur_similaire);

int comparaisonSon(t_Fichier fichierDonne, t_PileDescripteur pileSon,t_PileDescripteur *descripteur_similaire);

int comparaisonTexte(t_Fichier fichierDonne, t_PileDescripteur pileTexte,t_PileDescripteur *descripteur_similaire);

//On utilise les méthodes suivantes pour comparer deux fichier en particulier.
int compareFichierImage(char * fichierDonne , char * fichierCompare);

int compareFichierSon(char * fichierDonne , char * fichierCompare);

int compareFichierTexte(char * fichierDonne , char * fichierCompare);


#endif
