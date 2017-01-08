#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "indexationSon.h"

#define chemin /home/sebastien/Documents/UPSSITECH/RedStringProject/

void genDescripteurSon(t_Fichier fichier, t_PileDescripteur *ptr_PileSon){
  FILE* ptr_fichSon;
  char* descripteur = NULL;
  const int n = 1024; //taille des fenêtres
  const int m = 30; //nombre d'intervalles entre -1 et 1
  descripteur = malloc(nb_lignes*sizeof(int));
  ptr_fichSon = fopen(fichier.chemin_info,"r");
  float val;
  int tab_occurences[m];
  int nb_lignes; //nombre de ligne du fichier
  int c, c2 = '\0';
  ////////////////////
  while((c=fgetc(ptr_fichier)) != EOF){
	if(c=='\n')
		nb_lignes++;
	c2 = c;
  }
  if(c2 != '\n')
	  nb_lignes++;
  ////////// Récup le nombre de lignes du fichier
  for (int i=0; i<nb_lignes; i++){//parcourir tout le fichier .txt
    fscanf(ptr_fichSon, "%f", &val);
    for (int j=0; j<m; j++){
      if((val < ??) && (val > ??)) // intervalle des fenêtres entre -1 et +1
	      tab_occurences[j]++;
}

int main(int argc, char *argv[]){
  t_PileDescripteur pile;
  t_Fichier fichier;
  fichier.chemin_info = malloc(100*sizeof(char));
  fichier.chemin_info = "/Test/fichiers_tests_son/jingle_m6.txt";
  init_pile(&pile);
  genDescripteurSon(fichier, &pile);
}
