#ifndef _PILEDESCRIPTEUR_H
#define _PILEDESCRIPTEUR_H

#include <stdio.h>
#include <string.h>

typedef struct CelluleDescripteur{
	char *descripteur;
	struct CelluleDescripteur *p_suivant;
}t_CellDescripteur;

typedef struct pileDescripteur{
	t_CellDescripteur *premier;
} t_PileDescripteur;

void init_pile( t_PileDescripteur* p_pileDescripteur);

int pile_est_vide( t_PileDescripteur pileDescripteur);

int pile_est_pleine( t_PileDescripteur pileDescripteur);

void affiche_pile( t_PileDescripteur pileDescripteur);

void empile( t_PileDescripteur *p_pileDescripteur, char * descripteur);

int depile( t_PileDescripteur *p_pileDescripteur,char *descripteurDepile);

#endif
