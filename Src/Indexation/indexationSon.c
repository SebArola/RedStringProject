#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "indexationSon.h"

#define chemin /home/sebastien/Documents/UPSSITECH/RedStringProject/

void genDecripteurSon(t_Fichier fichier, t_PileDescripteur *ptr_PileSon){
  FILE* ptr_fichSon;
  char* descripteur = NULL;
  const int n = 1024; //taille des fenêtres
  const int m = 30; //nombre d'intervalles entre -1 et 1
  descripteur = malloc(nb_lignes*sizeof(int));
  ptr_fichSon = fopen(fichier.chemin_info,"r");
  float val;
  int tab_occurences[m];
  int nb_lignes; //nombre de ligne du fichier 
  
  while ((getc(ptr_fichSon)) != EOF){           //
    if (getc(ptr_fichSon) == '\n') nb_lignes++; // Récupérer le nombre de lignes du fichier texte fourni
  }                                             //
  
  for (int i=0; i<nb_lignes; i++){//parcourir tout le fichier .txt
    fscanf(ptr_fichSon, "%f", &val);
    for (int j=0; j<m; j++){
      if(val > 
}

int main(int argc, char *argv[]){
  t_PileDescripteur pile;
  t_Fichier fichier;
  fichier.chemin_info = malloc(100*sizeof(char));
  fichier.chemin_info = "/Test/fichiers_tests_son/jingle_m6.txt";
  init_pile(&pile);
  genDescripteurSon(fichier, &pile);
}
