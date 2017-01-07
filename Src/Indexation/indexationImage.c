#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "indexationImage.h"

void decimalToBinaire(int x, int *res, int bit)
{
  int i;
  for(i=bit-1; i>=0; i--)
  {
    res[i]=x%2;
    x=x/2;
  }
}

int binaireToDecimal(int *bin, int bit)
{
  int res=0, i;
  for(i=0; i<bit; i++)
  {
    res = res + (bin[i]*(int)pow(2, (bit-1-i)));
  }
  return res;
}

int quantif(int *binR, int *binV, int *binB, int nbQuantif)
{
  int *binRVB, i, j;
  binRVB=malloc(3*nbQuantif*sizeof(int));
  for(i=0; i<3; i++)
  {
    for(j=0; j<nbQuantif; j++)
    {
      if(i==0)
        binRVB[j]=binR[j];
      if(i==1)
        binRVB[j+nbQuantif]=binV[j];
      if(i==2)
        binRVB[j+(2*nbQuantif)]=binB[j];
    }
  }
  return binaireToDecimal(binRVB, nbQuantif*3);
}

void genDescripteurImage(t_Fichier fichier, t_PileDescripteur *ptrPileImage)
{
  FILE * ptr_ficImage;
  char * descripteur=NULL, * nombreChar=NULL;
  int lig, col, nbCouleur, i, j, k, nombre, nbQuantif, *bin;
  bin=malloc(8*sizeof(int));
  descripteur = malloc(10000*sizeof(char));
  nombreChar = malloc(sizeof(int));
  ptr_ficImage = fopen (fichier.chemin_info, "r");
  int tab[256]={0};
  fscanf(ptr_ficImage, "%d %d %d", &lig, &col, &nbCouleur);
  int tabRVB[3][lig][col];
  if(nbCouleur==1)
  {
    for(i=0; i<lig; i++)
    {
      for(j=0; j<col; j++)
      {
        fscanf(ptr_ficImage, "%d", &nb);
        tab[nb]++;
      }
    }
    int fclose(FILE * ptr_ficImage);
    strcat(descripteur, fichier.chemin_nom);
    strcat(descripteur, "\n");
    for(i=0; i<256; i++)
    {
  	  sprintf(nombreChar, "%d", i);
  	  strcat(descripteur, nombreChar);
      strcat(descripteur, " ");
      sprintf(nombreChar, "%d", tab[i]);
      strcat(descripteur, nombreChar);
      strcat(descripteur, "\n");
    }
  }
  if(nbCouleur==3)
  {
    for(k=0; k<3; k++)
    {
      for(i=0; i<lig; i++)
      {
        for(j=0; j<col; j++)
        {
          fscanf(ptr_ficImage, "%d", &nb);
          tabRVB[k][i][j]=nb;
        }
      }
    }
  }
  realloc(descripteur, strlen(descripteur)*sizeof(char));
  empile(ptrPileImage, descripteur);
}

int main ()
{
  t_Fichier fichier;
  t_PileDescripteur pile;
  fichier.chemin_info=malloc(100*sizeof(char));
  fichier.chemin_nom=malloc(100*sizeof(char));
  fichier.chemin_info="/home/etienne/projet/FICHIER_PROJET/IMG_NG/51.txt";
  fichier.chemin_nom="/home/etienne/projet/FICHIER_PROJET/IMG_NG/51.bmp";
  init_pile(&pile);
  genDescripteurImage(fichier, &pile);
  fichier.chemin_info="/home/etienne/projet/FICHIER_PROJET/IMG_NG/52.txt";
  fichier.chemin_nom="/home/etienne/projet/FICHIER_PROJET/IMG_NG/52.bmp";
  genDescripteurImage(fichier, &pile);
  fichier.chemin_info="/home/etienne/projet/FICHIER_PROJET/IMG_NG/61.txt";
  fichier.chemin_nom="/home/etienne/projet/FICHIER_PROJET/IMG_NG/61.bmp";
  genDescripteurImage(fichier, &pile);
  fichier.chemin_info="/home/etienne/projet/FICHIER_PROJET/IMG_NG/62.txt";
  fichier.chemin_nom="/home/etienne/projet/FICHIER_PROJET/IMG_NG/62.bmp";
  genDescripteurImage(fichier, &pile);
  affiche_pile(pile);
  /*FILE * ptr_ficListe;
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
  int fclose(FILE * ptr_ficDescripteur);*/
}
