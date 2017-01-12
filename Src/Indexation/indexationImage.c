#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
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
    res = res + (bin[i]*(int) pow(2, (bit-1-i)));
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
  char * descripteur=NULL, * nombreChar=NULL, * temp_descripteur=NULL;
  int lig, col, nbCouleur, i, j, k, nombre, nbQuantif=2, nb;
  int dim=pow(2, (3*nbQuantif));
  int * tabDesc;
  tabDesc=malloc(dim*sizeof(int));
  descripteur = malloc(4000*sizeof(char));
  nombreChar = malloc(sizeof(int));
  ptr_ficImage = fopen (fichier.chemin_info, "r");
  fscanf(ptr_ficImage, "%d %d %d", &lig, &col, &nbCouleur);
  if(nbCouleur==1)
  {
    int tab[256]={0};
    for(i=0; i<lig; i++)
    {
      for(j=0; j<col; j++)
      {
        fscanf(ptr_ficImage, "%d", &nb);
        tab[nb]++;
      }
    }
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
    int tabRVB[3][lig][col];
    int *ptr_R, *ptr_V, *ptr_B;
    ptr_R=malloc(8*sizeof(int));
    ptr_V=malloc(8*sizeof(int));
    ptr_B=malloc(8*sizeof(int));
    for(i=0; i<dim; i++)
    {
    	tabDesc[i]=0;
    }
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
    for(i=0; i<lig; i++)
    {
      for(j=0; j<col; j++)
      {
        decimalToBinaire(tabRVB[0][i][j], ptr_R, 8);
        decimalToBinaire(tabRVB[1][i][j], ptr_V, 8);
        decimalToBinaire(tabRVB[2][i][j], ptr_B, 8);
        tabDesc[quantif(ptr_R, ptr_V, ptr_B, nbQuantif)]++;
      }
    }
    strcat(descripteur, fichier.chemin_nom);
    strcat(descripteur, "\n");
    for(i=0; i<dim; i++)
    {
  	  sprintf(nombreChar, "%d", i);
  	  strcat(descripteur, nombreChar);
      strcat(descripteur, " ");
      sprintf(nombreChar, "%d", tabDesc[i]);
      strcat(descripteur, nombreChar);
      strcat(descripteur, "\n");
    }
  }
  fclose(ptr_ficImage);
  /*temp_descripteur=malloc(strlen(descripteur)*sizeof(char));
  for(i=0; i<strlen(descripteur); i++)
  {
  	temp_descripteur[i]=descripteur[i];
  }*/
  //realloc(descripteur, strlen(descripteur)*sizeof(char));
  empile(ptrPileImage, descripteur);
}
