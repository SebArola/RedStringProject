#include <stdio.h>
#include <stdlib.h>
#include "pileFichier.h"



void init_pile(t_PileFichier* p_pileFichier){
	p_pileFichier->premier = NULL;
}

int pile_est_vide(t_PileFichier pileFichier){
	return pileFichier.premier==NULL;
}

void affiche_pile(t_PileFichier pileFichier){
	printf("[");
	if(!pile_est_vide(pileFichier)){
		t_CellFichier *suivant;
		suivant = pileFichier.premier;;
		while(suivant->p_suivant!=NULL){
			printf("%s ; ",suivant->fichier.chemin);
			suivant = suivant->p_suivant;
		}
		printf("%s", suivant->fichier.chemin);
	}
	printf("]");
}



void empile(t_PileFichier *p_pileFichier, t_Fichier fichier){
	t_CellFichier *nouvCell= malloc(sizeof(t_CellFichier));
	nouvCell->fichier.chemin =fichier.chemin ;
	nouvCell->fichier.type = fichier.type;
	nouvCell->p_suivant=NULL;
	if(p_pileFichier->premier!=NULL){
		t_CellFichier *suivant;
		suivant = p_pileFichier->premier;
		while(suivant->p_suivant!=NULL){
			suivant = suivant->p_suivant;
		}
		suivant->p_suivant = nouvCell;
	}else{
		p_pileFichier->premier=nouvCell;
	}
}

int depile(t_PileFichier *p_pileFichier,t_Fichier *fichierDepile){
	if(!pile_est_vide(*p_pileFichier)){
		t_CellFichier *suivant;
		suivant = p_pileFichier->premier;
		while(suivant->p_suivant->p_suivant!=NULL){
			suivant = suivant->p_suivant;
		}
		fichierDepile=&suivant->p_suivant->fichier;
		suivant->p_suivant=NULL;
		return 1;
	}else{
		return 0;
	}
}
