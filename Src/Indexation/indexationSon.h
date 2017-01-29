#ifndef _INDEXATIONSON_H
#define _INDEXATIONSON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Fichier.h"
#include "pileDescripteur.h"

typedef struct DescSon{
  char id[10];	      /*  identifiant du descripteur */
  int nbWindows;      /*  nombre de fenêtre dans l'histogramme */
  int** histogram;    /*  Histogram de taille k*m.
                            k : nombre fenetre
                            m : nombre intervalles entre -1 et 1*/
}t_DescSon;

/*fileSize renvoie la taille en octet du fichier passé en paramètre*/
int fileSize(FILE* file);

/*lireDonnees lit le fichier binaire et renvoie -1 si on se trouve à la fin*/
int lireDonnees(FILE* file, void * typeDonnee, size_t tailleDonnee);

/*echangeDouble échange les octets d'une variable de type double*/
double echangeDouble(double dbl);

/*Créer un descripteur son de type t_DescSon défini plus haut en binaire*/
t_DescSon * CreerDescSon(FILE* file); 

/*Génère le descripteur Son en fichier .txt à partir du descripteur de type binaire*/
void genDecripteurSon(t_Fichier fichier, t_PileDescripteur *ptr_PileSon);
#endif
