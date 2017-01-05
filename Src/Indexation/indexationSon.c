#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "indexationSon.h"

void genDecripteurSon(t_Fichier fichier, t_PileDescripteur *ptr_PileSon){
  FILE* ptr_fichSon;
  char* descripteur = NULL;
  int nb_lignes;
  descripteur = malloc(nb_lignes*sizeof(int));
  ptr_fichSon = fopen(fichier.chemin,"r");
  float tab[];
}

int main(int argc, char *argv[]){
  t_PileDescripteur pile;
  t_Fichier fichier;
  fichier.chemin=malloc(50*sizeof(char));
  fichier.chemin="/home/matahi/documents/Roger_fils_rouge/fichiers_tests_son/jingle_m6.txt";
  init_pile(&pile);
  genDescripteurSon(fichier, &pile);
}
