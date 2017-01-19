#include <stdio.h>
#include <stdlib.h>
#include "pileDescripteur.h"



void init_pile(t_PileDescripteur* p_pileDescripteur){
	p_pileDescripteur->premier = NULL;
}

int taille_pile(t_PileDescripteur pileDescripteur){
	int taille = 0;
	if(!pile_est_vide(pileDescripteur)){
		t_CellDescripteur *suivant;
		suivant = pileDescripteur.premier;;
		while(suivant->p_suivant!=NULL){
			taille ++;
			suivant = suivant->p_suivant;
		}
		taille ++;
	}
	return taille;
}

int pile_est_vide(t_PileDescripteur pileDescripteur){
	return pileDescripteur.premier==NULL;
}

void affiche_pile(t_PileDescripteur pileDescripteur){
	printf("[");
	if(!pile_est_vide(pileDescripteur)){
		t_CellDescripteur *suivant;
		suivant = pileDescripteur.premier;
		while(suivant->p_suivant!=NULL){
			printf("%s ; ",suivant->descripteur);
			suivant = suivant->p_suivant;
		}
		printf("%s", suivant->descripteur);
	}
	printf("]");
}



void empile(t_PileDescripteur *p_pileDescripteur, char * descripteur){
	t_CellDescripteur *nouvCell= malloc(sizeof(t_CellDescripteur));
	nouvCell->descripteur = malloc(sizeof(char)*strlen(descripteur));
	nouvCell->p_suivant=p_pileDescripteur->premier;
	nouvCell->descripteur= descripteur;
	p_pileDescripteur->premier = nouvCell;

}

int depile(t_PileDescripteur *p_pileDescripteur,char *descripteurDepile){
	if(!pile_est_vide(*p_pileDescripteur)){
		descripteurDepile=p_pileDescripteur->premier->descripteur;
		p_pileDescripteur->premier = p_pileDescripteur->premier->p_suivant;
		return 1;
	}else{
		return 0;
	}
}
