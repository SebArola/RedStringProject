#ifndef _INDEXATIONIMAGE_H
#define  _INDEXATIONIMAGE_H

#include "Fichier.h"
#include "pileDescripteur.h"

/*
Méthode prenant un Fichier ainsi que la pile de descripteur image. Cette méthode
crée le descripteur du fichier dans un string et l'enregistre dans la pile.
*/
void genDescripteurImage(t_Fichier fichier, t_PileDescripteur *ptrPileImage);
//MODIF
#endif
