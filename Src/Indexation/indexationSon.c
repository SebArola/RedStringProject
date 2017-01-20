#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include "indexationSon.h"

	int taille_fenetre = 8192; // taille des fenêtres fixe pour le moment
	int nb_Intervalles = 50;   // intervalle entre -1 et 1 fixe aussi
	double valMax = 1.;
	double valMin = -1.;

/*Renvoie la taille du fichier binaire passé en paramètre*/
int fileSize(FILE* file)
{
	int size;
	if(file != NULL)
	{
		fseek(file, 0, SEEK_END);
		size = ftell(file);
		fseek(file, 0, SEEK_SET);
	}
	else
	{
		errno = EBADF;
		perror("fileSize file");
		return -1;
	}
	return size;
}

int readStruct(FILE* file, void * wStruct, size_t structSize)
{
	errno = 0;
	fread(wStruct, 1, structSize, file);

	if(!feof(file) && !ferror(file))
		return 0;
	else
	{
		perror("readStruct fread");
		clearerr(file);
		return 1;
	}
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
	printf("DEBUG 3.1\n");
	//contient la type du fichier
	int fSize = fileSize(file);
	printf("taille fichier : %d\n", fSize);
	printf("DEBUG 3.2\n");
	double *tmp = malloc(sizeof(*tmp));
	printf("DEBUG 3.3\n");
	double *seuil = malloc(sizeof(*seuil)*nb_Intervalles);
	printf("DEBUG 3.4\n");
	//Création du descSon
	t_DescSon * desc = malloc(sizeof(*desc));
	printf("DEBUG 3.5\n");
	//indices
	int ind_Interval, ind_Elem, ind_Window;
	printf("DEBUG 3.6\n");
	// nombre de fenetres k
	int nbWindow = (fSize/doubleSize) / taille_fenetre + 2;
	printf("nombre fenetres : %d\n", nbWindow);
	printf("DEBUG 3.7\n");
	// init du nombre de fenetres du descripteur
	(desc->nbWindows) = nbWindow;
	printf("DEBUG 3.8\n");
	//histogramme de taille k*m
	desc->histogram = malloc(sizeof(int*) * nbWindow);
	printf("DEBUG 3.9\n");
	for(ind_Interval = 0; ind_Interval < nb_Intervalles; ind_Interval++)
	{
		seuil[ind_Interval]=((ind_Interval+1)/(double)nb_Intervalles)*(valMax-valMin)+valMin;
	}
	printf("DEBUG 4\n");
	//Histogramme initialisé à zéro
	ind_Interval=0;
	for(ind_Window = 0; ind_Window < nbWindow; ind_Window++)
	{
		desc->histogram[ind_Window] = malloc(sizeof(int) * nb_Intervalles+1);
		for(ind_Interval = 0; ind_Interval < nb_Intervalles; ind_Interval++)
		{
			desc->histogram[ind_Window][ind_Interval] = 0;
		}
	}
	printf("DEBUG 4.1\n");
	//free(desc->histogram[ind_Window-1]);
	printf("DEBUG 4.2\n");
	//desc->histogram[ind_Window-1] = NULL;
	printf("DEBUG 4.3\n");
	ind_Elem = 0;
	ind_Window = 0;
	ind_Interval = 0;
	printf("DEBUG 4.4\n");
	while(readStruct(file, tmp, doubleSize) == 0)
	{
		//printf("DEBUG 4.5\n");
		if(ind_Elem == taille_fenetre)//Si on est à la fin de la fenetre
		{
			ind_Elem = 0;
			ind_Window++; // on va à la fenetre suivante

		}
	//while(fread(tmp, 1, doubleSize, file)!=0)
	//{
	//	printf("DEBUG 4.5\n");
	//	if(ind_Elem == taille_fenetre)
	//	{
	//		ind_Elem = 0;
	//		ind_Window++;
	//	}
		*tmp = Swap_double(*tmp);
		//printf("DEBUG 4.7\n");
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
	//free(tmp);
	//free(seuil);
	return desc;
}

////////////////////////////////////////////////////////////////////////////////
void genDescripteurSon(t_Fichier fichier, t_PileDescripteur *ptr_PileSon){
	printf("DEBUG 1\n");
	int add=1;
	char charTemp[10];
	FILE * ptr_fichierSonBin; // fichier son binaire fourni
	t_DescSon * DescSon; // descripteur de type t_DescSon
	printf("DEBUG 2\n");
	ptr_fichierSonBin = fopen(fichier.chemin_info,"rb");
	char * descripteur = malloc(1000000000*sizeof(char));
	printf("DEBUG 3\n");
	DescSon = CreerDescSon(ptr_fichierSonBin); // DescSon de type t_DescSon
	printf("DEBUG sorti CreerDescSon\n");
	strcpy(descripteur, fichier.chemin_nom);
	printf("%s\n", descripteur);
	printf("DEBUG 1er strcat\n");
	strcat(descripteur, "\nInd:");
	printf("%s\n", descripteur);
	printf("DEBUG 2e strcat\n");
	sprintf(DescSon->id,"%d",add);
	printf("DEBUG sprintf 1\n");
	strcat(descripteur, DescSon->id);
	printf("%s\n", descripteur);
	add++;
	printf("DEBUG 3e strcat\n");
	strcat(descripteur, "Nombre fenetres:");
	sprintf(charTemp,"%d",DescSon->nbWindows);
	printf("DEBUG 5\n");
	printf("%s\n", descripteur);
	for(int i=0;i<(DescSon->nbWindows);i++){
		for(int j=0; j<nb_Intervalles; j++){
			sprintf(charTemp,"%d",DescSon->histogram[i][j]);
			strcat(descripteur, charTemp);
			strcat(descripteur," |");
		}
		strcat(descripteur,"\n");
	}
	//printf("%s",descripteur);
	printf("DEBUG 6\n");
	//free(DescSon);
	//fflush(stdout);
	fclose(ptr_fichierSonBin);
	printf("DEBUG 7\n");
	empile(ptr_PileSon, descripteur);
	printf("DEBUG 8\n");

}
