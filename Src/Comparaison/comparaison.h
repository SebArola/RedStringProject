#ifndef _COMPARAISON_H
#define _COMPARAISON_H

#include "../Indexation/Fichier.h"
#include "../Indexation/pileDescripteur.h"

/*
Ces méthodes permettent de comparer un fichier a un autre de la base.
*/
int comparaisonImage(t_Fichier fichierCompare, t_PileDescripteur pileImage);

int comparaisonSon(t_Fichier fichierCompare, t_PileDescripteur pileSon);

int comparaisonTexte(t_Fichier fichierCompare, t_PileDescripteur pileTexte);

#endif
