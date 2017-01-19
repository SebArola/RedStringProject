#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "indexationSon.h"

	int add = 1;
	int taille_fenetre = 1024; //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! taille des fenêtres fixe pour le moment
	int nb_Intervalles = 50;   //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! intervalle entre -1 et 1 fixe aussi
	double valMax = 1.;
	double valMin = -1.;

/*Renvoie la taille du fichier binaire passé en paramètre*/
int fileSize(FILE* file){
  	int size;
  	fseek(file, 0, SEEK_END);
  	size = ftell(file);
	fseek(file, 0, SEEK_SET);
	return size;
}

double Swap_double(double dbl)
{
	char ch[8];
	double dblRet;
	memcpy(ch, &dbl, 8); // copie de "dbl" vers "ch"
	//Echange entre 0 et 7
	char temp;
	temp = ch[0];
	ch[0] = ch[7];
	ch[7] = temp;
	//Echange entre 1 et 6
	temp = ch[1];
	ch[1] = ch[6];
	ch[6] = temp;
	//Echange entre 3 et4
	temp = ch[3];
	ch[3] = ch[4];
	ch[4] = temp;

	memcpy(&dblRet, ch, 8); // copie de "ch" vers "dblRet"
	return dblRet;
}

/*Créer un descripteur son de type t_DescSon*/
t_DescSon * CreerDescSon(FILE* file){
	//contient la taille d'une variable de type double
	int doubleSize = sizeof(double);

	//contient la type du fichier
	int fSize = fileSize(file);
	double *tmp = malloc(sizeof(*tmp));
	double *seuil = malloc(sizeof(*seuil)*nb_Intervalles);
	//Création du descSon
	t_DescSon * desc = malloc(sizeof(*desc));
	//indices
	int ind_Interval, ind_Elem, ind_Window;

	// nombre de fenetres k
	int nbWindows = (fSize/doubleSize) / taille_fenetre + 2;
	// init du nombre de fenetres du descripteur
	desc->nbWindows = nbWindows;
	//histogramme de taille k*m
	desc->histogram = malloc(sizeof(int*) * nbWindows);
	for(ind_Interval = 0; ind_Interval < nb_Intervalles; ind_Interval++)
	{
		seuil[ind_Interval]=((ind_Interval+1)/(double)nb_Intervalles)*(valMax-valMin)+valMin;
	}

	//Histogramme initialisé à zéro
	for(ind_Window = 0; ind_Window < nbWindows; ind_Window++)
	{
		desc->histogram[ind_Window] = malloc(sizeof(int) * nb_Intervalles);
		for(ind_Interval = 0; ind_Interval < nb_Intervalles; ind_Interval++)
			desc->histogram[ind_Window][ind_Interval] = 0;
	}
	free(desc->histogram[ind_Window-1]);
	desc->histogram[ind_Window-1] = NULL;
	ind_Elem = 0;
	ind_Window = 0;
	ind_Interval = 0;
	while(fread(tmp, 1, doubleSize, file)!=0)
	{
		if(ind_Elem == taille_fenetre)
		{
			ind_Elem = 0;
			ind_Window++;
		}
		*tmp = Swap_double(*tmp);
		if(*tmp <= seuil[0])
			(desc->histogram[ind_Window][0])++;
		else
		{
			for(ind_Interval = 0; ind_Interval < nb_Intervalles; ind_Interval++)
			{
				if(*tmp <= seuil[ind_Interval])
				{
					(desc->histogram[ind_Window][ind_Interval])++;
					break;
				}
			}

			if(*tmp > seuil[nb_Intervalles-1])
				(desc->histogram[ind_Window][nb_Intervalles-1])++;
		}
		ind_Elem++;
	}
	free(tmp);
	free(seuil);
	return desc;

}
void genDescripteurSon(t_Fichier fichier, t_PileDescripteur *ptr_PileSon){
	printf("DEBUG 1\n");
	FILE * ptr_ficSon; // fichier son binaire fourni
	t_DescSon * DescSon; // descripteur de type t_DescSon
	printf("DEBUG 2\n");

	ptr_ficSon = fopen(fichier.chemin_info,"r");
	char descripteur[500];
	printf("DEBUG 3\n");

	DescSon = CreerDescSon(ptr_ficSon); // DescSon de type t_DescSon
	printf("DEBUG 3\n");

	strcpy(descripteur, fichier.chemin_nom);
	strcat(descripteur, "\nInd:");
	sprintf(DescSon->address,"%d",add);
	strcat(descripteur, DescSon->address);
	add++;
	strcat(descripteur, "Nombre fenetres:");
	sprintf(descripteur,"%d",DescSon->nbWindows);
	printf("DEBUG 4\n");
	printf("%d\n",DescSon->nbWindows );
	printf("%d\n",nb_Intervalles );

	for(int i=0;i<DescSon->nbWindows-1;i++){
		for(int j=0; j<nb_Intervalles; j++){
			char t[5];
			sprintf(t,"%d",DescSon->histogram[i][j]);
			//printf("->%s\n",t );
			strcat(descripteur,t);
			strcat(descripteur," |");
			//printf("%d\n",DescSon->histogram[i][j]);
		}
		strcat(descripteur,"\n");
	}
	//printf("%s",descripteur);
	printf("DEBUG 5\n");

	//free(DescSon);
	fclose(ptr_ficSon);
	printf("DEBUG 6\n");

	empile(ptr_PileSon, descripteur);
	printf("DEBUG 7\n");

}
/*int main(){
}
  FILE * fichierTestBinaire = fopen("jingle_m6.bin2", "rb");
  DescSon = CreerDescSon(fichierTestBinaire);
  printf("Ind: %d\n", DescSon->address);
  printf("Nombre fenetres: %d\n", DescSon->nbWindows);
  ///////////////////
  int nbWindows = (fileSize(fichierTestBinaire)/8) / 4096 + 2;
  for(int iWindow = 0; iWindow < nbWindows; iWindow++)
	{
		for(int iInterval = 0; iInterval < 50; iInterval++)
			printf("%d|", DescSon->histogram[iWindow][iInterval]);
		printf("\n");
	}*/
