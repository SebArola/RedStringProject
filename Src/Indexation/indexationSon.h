#ifndef _INDEXATIONSON_H
#define _INDEXATIONSON_H

#include "Fichier.h"
#include "pileDescripteur.h"

typedef struct DescSon{
  char id[10];	      /*  identifiant du descripteur */
  int nbWindows;      /*  nombre de fenêtre dans l'histogramme */
  int** histogram;    /*  Histogram de taille k*m.
                            k : nombre fenetre
                            m : nombre intervalles entre -1 et 1*/
}t_DescSon;

int readStruct(FILE* file, void * wStruct, size_t structSize);
int fileSize(FILE* file); // renvoie la taille du fichier passer en paramètre
double Swap_double(double dbl); // memcpy d'un double vers un autre double
t_DescSon * CreerDescSon(FILE* file); // créer un t_DescSon ave un fichier binaire
void genDescripteurSon(t_Fichier fichier, t_PileDescripteur *ptr_PileSon);
#endif
