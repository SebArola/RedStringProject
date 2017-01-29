#include "indexationSon.h"

int taille_fenetre = 8192; // taille des fenêtres de 8192 échantillons
int nb_Intervalles = 50;   // nombre d'intervalles entre -1 et 1 fixe 
double valMax = 1.;      /*Intervalles max*/
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
		printf("Erreur : fichier inexistant");
		return -1;
	}
	return size;
}

/*lireDonnees lit le fichier binaire et renvoie -1 si on se trouve à la fin*/
int lireDonnees(FILE* file, void * typeDonnee, size_t tailleDonnee)
{
	fread(typeDonnee, 1, tailleDonnee, file);
	if(!feof(file)) return 0;
	else	return -1;
}

/*echangeDouble échange les octets d'une variable de type double*/
double echangeDouble(double dbl)
{
	char ch[8];
	double dblRet;
	memcpy(ch, &dbl, 8); 
	char temp;
	temp = ch[0];
	ch[0] = ch[7];
	ch[7] = temp;
	temp = ch[1];
	ch[1] = ch[6];
	ch[6] = temp;
	temp = ch[3];
	ch[3] = ch[4];
	ch[4] = temp;
	memcpy(&dblRet, ch, 8);
	return dblRet;
}

/*Créer un descripteur son de type t_DescSon défini dans le header en binaire*/
t_DescSon * CreerDescSon(FILE* file){
	int doubleSize = 8; 			  		//taille d'une variable de type double
	int fSize = fileSize(file); 	   	 		//fSize contient la taille du fichier
	double tmp; 				 		//variable temporaire pour chaque valeur du fichier
	double seuil[nb_Intervalles];		  		//Tableau des différents seuils
	t_DescSon * desc = malloc(sizeof(*desc));	 	//Création du descripteur
	int ind_Interval=0, ind_Elem=0, ind_Window=0; 	        //indices
	int nbWindow = (fSize/doubleSize) / taille_fenetre + 2; //nombre de fenêtres
	(desc->nbWindows) = nbWindow; 				//On écrit le nombre de fenetre dans le descripteur
	desc->histogram = malloc(sizeof(int*)*nbWindow);	//histogramme de taille k*m

	/*Définition des intervalles*/
	for(ind_Interval = 0; ind_Interval < nb_Intervalles; ind_Interval++)
	{
		seuil[ind_Interval]=((ind_Interval+1)/(double)nb_Intervalles)*(valMax-valMin)+valMin;
	}

	//Histogramme initialisé à zéro
	for(ind_Window = 0; ind_Window < nbWindow; ind_Window++)
	{
		desc->histogram[ind_Window] = malloc(sizeof(int) * nb_Intervalles);
		for(ind_Interval = 0; ind_Interval < nb_Intervalles; ind_Interval++)
			desc->histogram[ind_Window][ind_Interval] = 0;
	}

	//Tant qu'on n'est pas à la fin du fichier on incrémente le compteur de la case de la matrice si la valeur lue est dans l'intervalle
	while(lireDonnees(file, &tmp, doubleSize) == 0){ 
		if(ind_Elem == taille_fenetre){
			ind_Elem = 0;
			ind_Window++; 
		}
		tmp = echangeDouble(tmp);
		if(tmp <= seuil[0])
			(desc->histogram[ind_Window][0])++;
		else{
			for(ind_Interval = 0; ind_Interval < nb_Intervalles; ind_Interval++){
				if(tmp <= seuil[ind_Interval]){
					(desc->histogram[ind_Window][ind_Interval])++;
					break;
				}
			}
			if(tmp > seuil[nb_Intervalles-1])
				(desc->histogram[ind_Window][nb_Intervalles-1])++;
		}
		ind_Elem++;
	}
	return(desc);
	free(desc);
}

/*Génère le descripteur Son en fichier .txt à partir du descripteur de type binaire*/
void genDescripteurSon(t_Fichier fichier, t_PileDescripteur *ptr_PileSon){
	FILE * ptr_fichierSon; 				  // fichier son binaire fourni
	t_DescSon * DescSon; 				  // descripteur de type t_DescSon
	ptr_fichierSon = fopen(fichier.chemin_info,"rb"); // fichier ouvert en lecture binaire

	char charTemp[10]; /*variables temporaires pour copier DescSon dans une chaine*/
	char nbFenTemp;

	char * descripteur = malloc(10000*sizeof(char)); //Pour la pile
	DescSon = CreerDescSon(ptr_fichierSon); // Descripteur Son binaire
	
	/*Copie le descripteur Son sous format binaire dans la chaine descripteur*/
	strcat(descripteur,"Nom fichier: ");
	strcat(descripteur, fichier.chemin_nom);
	strcat(descripteur, "\n");
	strcat(descripteur,"Nombre de fenêtres:"); 
	sprintf(&nbFenTemp,"%d",DescSon->nbWindows);
	strcat(descripteur, &nbFenTemp);	
	strcat(descripteur,"\n");
	for(int i=0;i<(DescSon->nbWindows);i++){
		for(int j=0; j<nb_Intervalles; j++){
			sprintf(charTemp,"%d",DescSon->histogram[i][j]);
			strcat(descripteur, charTemp);
			strcat(descripteur," |");
		}
		strcat(descripteur,"\n");
	}
	strcat(descripteur,"\n/*************************************************************/\n");
	empile(ptr_PileSon, descripteur);
	fclose(ptr_fichierSon);
	free(descripteur);
	free(DescSon->histogram);
	free(DescSon);
}

/*int main(){
	t_PileDescripteur * PileDesc;
	t_Fichier Fichier;
	init_pile(PileDesc);
	Fichier.chemin_nom = "jingle_m6";
	Fichier.chemin_info = "/home/matahi/Projet_fils_rouge/fichiers/requete/jingle_m6.bin2";
	genDescripteurSon(Fichier, PileDesc);
}*/
