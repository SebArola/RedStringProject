#ifndef _INDEXATIONSON_H
#define _INDEXATIONSON_H

#include "Fichier.h"
#include "pileDescripteur.h"

int taille_fenetre; 
int nb_Intervalles; 
double valMax; 
double valMin; 

typedef struct DescSon{
  char address;      /*  adresse dans la base descripteur */
  int nbWindows;     /*  nombre de fenêtre dans l'histogramme */
  int** histogram;   /*  Histogram de taille k*m.
                            k : nombre fenetre
                            m : nombre intervalles entre -1 et 1*/
}t_DescSon;

int fileSize(FILE* file); // renvoie la taille du fichier passer en paramètre
double endianSwap_double(double dbl); // memcpy d'un double vers un autre en inversant les octets 
t_DescSon * CreerDescSon(FILE* file); // créer un t_DescSon ave un fichier binaire
void genDecripteurSon(t_Fichier fichier, t_PileDescripteur *ptr_PileSon);
#endif
