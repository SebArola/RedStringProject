#include "DescripSon.h"

//===================================================================================================
double endianSwap_double(double dbl)
{
	char ch[SIZEDOUBLE];
	double dblRet;
	
	memcpy(ch, &dbl, SIZEDOUBLE); // copie la chaîne de taille SIZEDOUBLE dans "dbl" vers "ch"
	ch[0] ^= ch[7] ^= ch[0] ^= ch[7]; // Swap between ch[0] and ch[7]
	ch[1] ^= ch[6] ^= ch[1] ^= ch[6]; // Swap between ch[1] and ch[6]
	ch[2] ^= ch[5] ^= ch[2] ^= ch[5]; // Swap between ch[2] and ch[5]
	ch[3] ^= ch[4] ^= ch[3] ^= ch[4]; // Swap between ch[3] and ch[4]
	memcpy(&dblRet, ch, SIZEDOUBLE); // copie la chaîne de taille SIZEDOUBLE dans "ch" vers "dblRet"
	return dblRet;
}
//===================================================================================================
SoundDesc * createSoundDesc(FILE* file)
{
	int doubleSize = sizeof(double),
		fSize = fileSize(file);
	double *tmp = malloc(sizeof(*tmp)),
		*intervalsThreshold = malloc(sizeof(*intervalsThreshold) * globs_nbInterval);
		
	SoundDesc * desc = malloc(sizeof(*desc));
	int iInterval, iElem, iWindow;	
	int nbWindows = (fSize / doubleSize) / globs_windowSize + 2;
	
	desc->nbWindows = nbWindows;
	desc->histogram = malloc(sizeof(int*) * nbWindows);

	for(iInterval = 0; iInterval < globs_nbInterval; iInterval++)
	{
		intervalsThreshold[iInterval] = ((iInterval + 1) / (double)globs_nbInterval) * (globs_maxFrequency - globs_minFrequency)
					+ globs_minFrequency;
	}
	
	//Histogramme initialisé à zéro 
	for(iWindow = 0; iWindow < nbWindows; iWindow++)
	{
		desc->histogram[iWindow] = malloc(sizeof(int) * globs_nbInterval);

		for(iInterval = 0; iInterval < globs_nbInterval; iInterval++)
			desc->histogram[iWindow][iInterval] = 0;
	}
	free(desc->histogram[iWindow - 1]);
	desc->histogram[iWindow - 1] = NULL;
	//////////	

	iElem = iWindow = iInterval = 0;
	while(readStruct(file, tmp, doubleSize))
	{
		if(iElem == globs_windowSize)
		{
			iElem = 0;
			iWindow++;
		}
		*tmp = endianSwap_double(*tmp);
		if(*tmp <= intervalsThreshold[0])
			(desc->histogram[iWindow][0])++;
		else
		{
			for(iInterval = 0; iInterval < globs_nbInterval; iInterval++)
			{
				if(*tmp <= intervalsThreshold[iInterval])
				{
					(desc->histogram[iWindow][iInterval])++;
					break;		
				}				
			}
			if(*tmp > intervalsThreshold[globs_nbInterval - 1])
				(desc->histogram[iWindow][globs_nbInterval - 1])++;
		}
		
		iElem++;
	}

	free(tmp);
	free(intervalsThreshold);
	return desc;
}
//===================================================================================================
int soundDescSize(SoundDesc const * desc)
{
	int size = 0;
	size += sizeof(desc->address);
	size += sizeof(desc->nbWindows);
	size += sizeof(int) * globs_nbInterval * (desc->nbWindows - 1);
	size += sizeof(int *);
	
	return size;
}
//===================================================================================================
void printSoundDesc(SoundDesc const * desc)
{
	int iInterval, iWindow, nbWindows = desc->nbWindows - 1;
	// car dernière valeur desc->histogram[iWindow] == NULL
	printf("\nId: %ld", (long int)desc->address);
	
	for(iWindow = 0; iWindow < nbWindows; iWindow++)
	{
		for(iInterval = 0; iInterval < globs_nbInterval; iInterval++)
			printf("%d|", desc->histogram[iWindow][iInterval]);
		printf("\n");
	}
}
//===================================================================================================
void writeSoundDesc(FILE* file, SoundDesc* desc)
{
	int iInterval, iWindow, nbWindows = desc->nbWindows - 1;
	// nbWindows  -1 car dernière valeur desc->histogram[iWindow] == NULL
	
	// ecrire desc->address
	writeStruct(file, &desc->address, sizeof(desc->address));
	
	// ecrire desc->nbWindows
	writeStruct(file, &desc->nbWindows, sizeof(int));

	// ecrire desc->histogram
	for(iWindow = 0; iWindow < nbWindows; iWindow++)
		writeStruct(file, desc->histogram[iWindow], sizeof(int) * globs_nbInterval);
	writeStruct(file, &desc->histogram[iWindow], sizeof(int*));
}
//===================================================================================================
SoundDesc * readSoundDesc(FILE* file){
	SoundDesc * desc = malloc(sizeof(*desc));
	const int histUpperSize = 5;
	int iElem, iWindow;	// k et m de la matrice
	int nbWindows;
	

	// lecture de desc->address
	if(!readStruct(file, &desc->address, sizeof(desc->address)))
	{
		free(desc);
		return NULL;
	}
	
	// lecture de desc->nbWindows
	if(!readStruct(file, &desc->nbWindows, sizeof(int)))
	{
		free(desc);
		return NULL;
	}
	nbWindows = desc->nbWindows - 1;// la dernière case sera fixée à NULL
	
	desc->histogram = malloc(sizeof(int*) * desc->nbWindows);	
	// lecture de  desc->id
	for(iWindow = 0; iWindow < nbWindows; iWindow++)
	{
		desc->histogram[iWindow] = malloc(sizeof(int) * globs_nbInterval);
		if(!readStruct(file, desc->histogram[iWindow], sizeof(int) * globs_nbInterval))
		{
			free(desc);
			return NULL;
		}
	}

	// Fin de la dernière fenêtre par NULL
	desc->histogram[iWindow] = NULL;
	
	return desc;
}

int main(int argc, char *argv[]){
    FILE * fichier = NULL;
    fichier = fopen("test.txt", "r+");
    printf("DEBUG DEBUT\n");
    SoundDesc * desc = createSoundDesc(fichier);
    printf("DEBUG 1\n");
    desc->address = "DescripSon.txt";
    printf("DEBUG 2\n");   
    writeSoundDesc(fichier,desc);
    printf("DEBUG 3\n");
    int i = fclose(fichier);
    return 0;
}

