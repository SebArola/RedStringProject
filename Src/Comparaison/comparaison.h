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
int comparaisonImage(t_Fichier fichierDonne, t_PileDescripteur pileImage);

int comparaisonSon(t_Fichier fichierDonne, t_PileDescripteur pileSon);

int comparaisonTexte(t_Fichier fichierDonne, t_PileDescripteur pileTexte);

int compareFichierImage(char * fichierDonne , char * fichierCompare);

int compareFichierSon(char * fichierDonne , char * fichierCompare);

int compareFichierTexte(char * fichierDonne , char * fichierCompare);


#endif
