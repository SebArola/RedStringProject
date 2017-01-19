#ifndef _CONTROLLEURINDEXATION_H
#define _CONTROLLEURINDEXATION_H

#include <stdio.h>
#include "pileDescripteur.h"
#include "Fichier.h"
#include <stdlib.h>
#include <string.h>
#include "indexationTexte.h"
#include "indexationImage.h"
#include "indexationSon.h"


void ecrireDescripteur(t_PileDescripteur pileDescripteur, char * type);
void indexationImage(t_PileDescripteur *pile_image);
void indexationTexte(t_PileDescripteur *pile_texte, int NBMOT);
void indexationSon(t_PileDescripteur *pile_son);
void runIndexation();

#endif
