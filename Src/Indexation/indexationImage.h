#ifndef _INDEXATIONIMAGE_H
#define  _INDEXATIONIMAGE_H

#include "Fichier.h"
#include "pileDescripteur.h"

/*
Méthode prenant un Fichier ainsi que la pile de descripteur image. Cette méthode
crée le descripteur du fichier dans un string et l'enregistre dans la pile.
*/
void genDescripteurImage(t_Fichier fichier, t_PileDescripteur *ptrPileImage);
void decimalToBinaire(int x, int *res, int bit);
int binaireToDecimal(int *bin, int bit);
int quantif(int *binR, int *binV, int *binB, int nbQuantif);
void imageNB(char ** descripteur, t_Fichier fichier);
void imageRVB(char ** descripteur, t_Fichier fichier);
//MODIF
#endif
