#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "indexationImage.h"

//Donne la représentation en binaire d'un décimal
void decimalToBinaire(int x, int *res, int bit)
{
  int i;
  for(i=bit-1; i>=0; i--)
  {
    res[i]=x%2;
    x=x/2;
  }
}

//Donne la valeur en décimal d'un binaire
int binaireToDecimal(int *bin, int bit)
{
  int res=0, i;
  for(i=0; i<bit; i++)
  {
    res = res + (bin[i]*(int) pow(2, (bit-1-i)));
  }
  return res;
}

//Quantifie les 3 pixels, assemble leur valeurs en binaire, renvoie le nombre en décimal
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

void imageNB(char ** descripteur, t_Fichier fichier)
{
  FILE * ptr_ficImage;
  ptr_ficImage = fopen (fichier.chemin_info, "r");
  int lig, col, i, j, nb;
  char * nombreChar=NULL;
  fscanf(ptr_ficImage, "%d %d %*d", &lig, &col);
  nombreChar = malloc(sizeof(int));
  *descripteur = malloc(4000*sizeof(char));
  int tab[256]={0};	//initialise l'histogramme
  for(i=0; i<lig; i++)
  {
    for(j=0; j<col; j++)
    {
      fscanf(ptr_ficImage, "%d", &nb);
      tab[nb]++;	//comptabilise le nombre d'occurences de chaque niveau
    }
  }
  strcat(*descripteur, fichier.chemin_nom);	//écriture du descripteur
  strcat(*descripteur, "\n");
  strcat(*descripteur, "1\n");
  for(i=0; i<256; i++)  //écriture de l'histogramme dans le descripteur
  {
    sprintf(nombreChar, "%d", i);
    strcat(*descripteur, nombreChar);
    strcat(*descripteur, " ");
    sprintf(nombreChar, "%d", tab[i]);
    strcat(*descripteur, nombreChar);
    strcat(*descripteur, "\n");
  }
  fclose(ptr_ficImage);
}

void imageRVB(char ** descripteur, t_Fichier fichier)
{
  FILE * ptr_ficImage;
  char * nombreChar=NULL;
  int lig, col, i, j, k, nbQuantif=2, nb;
  int dim=pow(2, (3*nbQuantif));
  int * tabDesc;
  tabDesc=malloc(dim*sizeof(int));
  nombreChar = malloc(sizeof(int));
  ptr_ficImage = fopen (fichier.chemin_info, "r");
  fscanf(ptr_ficImage, "%d %d %*d", &lig, &col);
  *descripteur = malloc(4000*sizeof(char));
  int tabRVB[3][lig][col];
  int *ptr_R, *ptr_V, *ptr_B;
  ptr_R=malloc(8*sizeof(int));	//valeur rouge binaire
  ptr_V=malloc(8*sizeof(int));	//valeur vert binaire
  ptr_B=malloc(8*sizeof(int));	//valeur bleu binaire
  for(i=0; i<dim; i++)	//initialisation tableau
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
        tabRVB[k][i][j]=nb;	//stocke les 3 matrices d'intensité dans un tableau
      }
    }
  }
  for(i=0; i<lig; i++)
  {
    for(j=0; j<col; j++)
    {
      decimalToBinaire(tabRVB[0][i][j], ptr_R, 8);	//pixel rouge en binaire
      decimalToBinaire(tabRVB[1][i][j], ptr_V, 8);	//pixel vert en binaire
      decimalToBinaire(tabRVB[2][i][j], ptr_B, 8);	//pixel bleu en binaire
      tabDesc[quantif(ptr_R, ptr_V, ptr_B, nbQuantif)]++;	//comptabilise le nombre d'occurences de chaque niveau quantifié
    }
  }
  strcat(*descripteur, fichier.chemin_nom);	//écriture du descripteur
  strcat(*descripteur, "\n");
  strcat(*descripteur, "3\n");
  for(i=0; i<dim; i++)
  {
    sprintf(nombreChar, "%d", i);
    strcat(*descripteur, nombreChar);
    strcat(*descripteur, " ");
    sprintf(nombreChar, "%d", tabDesc[i]);
    strcat(*descripteur, nombreChar);
    strcat(*descripteur, "\n");
  }
  fclose(ptr_ficImage);
}

void genDescripteurImage(t_Fichier fichier, t_PileDescripteur *ptrPileImage)
{

  FILE * ptr_ficImage;
  char * descripteur=NULL;
  int nbCouleur;
  ptr_ficImage = fopen (fichier.chemin_info, "r");
  fscanf(ptr_ficImage, "%*d %*d %d", &nbCouleur);
  fclose(ptr_ficImage);
  if(nbCouleur==1)	//pour une image N&B
  {
    imageNB(&descripteur, fichier);
  }
  if(nbCouleur==3)	//pour une image couleur
  {
    imageRVB(&descripteur, fichier);
  }
  empile(ptrPileImage, descripteur);
}
