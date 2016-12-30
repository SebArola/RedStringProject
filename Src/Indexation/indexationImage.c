#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "indexationImage.h"

int main ()
{
  FILE * ptr_ficListe;
  FILE * ptr_ficImage;
  FILE * ptr_ficDescripteur;
  char CHEMIN[100];
  char commande[1000] ;
  int lig, col, nbCouleur, i, j, nb;
  system("touch base_descripteur_image.txt");
  ptr_ficDescripteur = fopen("base_descripteur_image.txt", "w");
  printf("Indiquez le chemin d'accès des fichiers\n");
  scanf("%s", CHEMIN);
  strcpy(commande, "ls ");
  strcat(commande, CHEMIN);
  strcat(commande, "*.txt > base_fichiers.txt");
  system(commande);
  system("cat base_fichiers.txt");
  printf("---------------------------------\n");
  ptr_ficListe = fopen("base_fichiers.txt", "r");
  while(!feof(ptr_ficListe))
  {
    int tab[256]={0};
    float taux[256]={0};
    fscanf(ptr_ficListe, "%s", CHEMIN);
    ptr_ficImage = fopen(CHEMIN, "r");
    fscanf(ptr_ficImage, "%d %d %d", &lig, &col, &nbCouleur);
    for(i=0; i<lig; i++)
    {
      for(j=0; j<col; j++)
      {
        fscanf(ptr_ficImage, "%d", &nb);
        tab[nb]++;
      }
    }
    int fclose(FILE * ptr_ficImage);
    for(i=0; i<256; i++)
    {
      taux[i]=(float)tab[i]/(lig*col);
    }
    fprintf(ptr_ficDescripteur, "%s\n", CHEMIN);
    for (i=0; i<256; i++)
    {
      fprintf(ptr_ficDescripteur, "%d\t%d\n", i, tab[i]);
    }
    fprintf(ptr_ficDescripteur, "\n");
    printf("%f\n", taux[255]);
    printf("%f\n", taux[0]);
  }
  int fclose(FILE * ptr_ficListe);
  int fclose(FILE * ptr_ficDescripteur);
}
