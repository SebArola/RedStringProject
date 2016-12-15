#include <stdio.h>
#include <stdlib.h>
#include "pileDescripteur.h"



void init_pile(t_PileDescripteur* p_pileDescripteur){
	p_pileDescripteur->premier = NULL;
}

int pile_est_vide(t_PileDescripteur pileDescripteur){
	return pileDescripteur.premier==NULL;
}

void affiche_pile(t_PileDescripteur pileDescripteur){
	printf("[");
	if(!pile_est_vide(pileDescripteur)){
		t_CellDescripteur *suivant;
		suivant = pileDescripteur.premier;;
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
	nouvCell->p_suivant=NULL;
	if(p_pileDescripteur->premier!=NULL){
		t_CellDescripteur *suivant;
		suivant = p_pileDescripteur->premier;
		while(suivant->p_suivant!=NULL){
			suivant = suivant->p_suivant;
		}
		suivant->p_suivant = nouvCell;
	}else{
		p_pileDescripteur->premier=nouvCell;
	}
}

int depile(t_PileDescripteur *p_pileDescripteur,char *descripteurDepile){
	if(!pile_est_vide(*p_pileDescripteur)){
		t_CellDescripteur *suivant;
		suivant = p_pileDescripteur->premier;
		while(suivant->p_suivant->p_suivant!=NULL){
			suivant = suivant->p_suivant;
		}
		descripteurDepile=suivant->p_suivant->descripteur;
		suivant->p_suivant=NULL;
		return 1;
	}else{
		return 0;
	}
}
