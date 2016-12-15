#ifndef _PILEDESCRIPTEUR_H
#define _PILEDESCRIPTEUR_H

#include <stdio.h>
#include <string.h>
#include "Fichier.h"
typedef struct CelluleFichier{
	t_Fichier fichier;
	struct CelluleFichier *p_suivant;
}t_CellFichier;

typedef struct pileFichier{
	t_CellFichier *premier;
} t_PileFichier;

void init_pile( t_PileFichier* p_pileFichier);

int pile_est_vide( t_PileFichier pileFichier);

int pile_est_pleine( t_PileFichier pileFichier);

void affiche_pile( t_PileFichier pileFichier);

void empile( t_PileFichier *p_pileFichier, t_Fichier fichier);

int depile( t_PileFichier *p_pileFichier,t_Fichier *fichierDepile);

#endif
