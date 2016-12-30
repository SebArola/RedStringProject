#ifndef _COMPARAISON_H
#define _COMPARAISON_H

#include "../Indexation/Fichier.h"
#include "../Indexation/pileDescripteur.h"

/*
Ces méthodes permettent de comparer un fichier a un autre de la base.
*/
int comparaisonImage(t_Fichier fichierDonne, t_PileDescripteur pileImage);

int comparaisonSon(t_Fichier fichierDonne, t_PileDescripteur pileSon);

int comparaisonTexte(t_Fichier fichierDonne, t_PileDescripteur pileTexte);

int compareFichierImage(t_Fichier fichierDonne , t_Fichier fichierCompare);

int compareFichierSon(t_Fichier fichierDonne , t_Fichier fichierCompare);

int compareFichierTexte(t_Fichier fichierDonne , t_Fichier fichierCompare);


#endif
