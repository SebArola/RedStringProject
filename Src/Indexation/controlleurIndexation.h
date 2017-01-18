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

void runIndexation();
void ecrireDescripteur(t_PileDescripteur pileDescripteur, char * type);


#endif
