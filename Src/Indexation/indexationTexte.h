#ifndef _INDEXATIONTEXTE_H
#define  _INDEXATIONTEXTE_H
#include "Fichier.h"
#include "pileDescripteur.h"
/*
Méthode prenant un Fichier ainsi que la pile de descripteur texte. Cette méthode
crée le descripteur du fichier dans un string et l'enregistre dans la pile.
*/
void ajout_mot_chaine(char* mot);
void ajout_rc_chaine();
void ajout_chiffre_chaine(int nombre);
void ajout_mot_important_chaine();
void afficher_tab_ligne();
void afficher_tab_recurrence();
void calcul_recurrence();
void lire_ligne(char* ligne,char* nom_fichier,int num_lig);
void inser_mot(char* mot, int longeur_mot);
void suppr_ponctuation(char* ligne);
void suppr_carac(char* ligne,int nb);
void ligne_tableau(char* ligne, int* retour);
void conception_descripteur(char* nom_fichier);
void genDescripteurTexte(t_Fichier fichier, t_PileDescripteur *ptrPileTexte,char* chemin);

void afficher_tab_index();
void envoie_tableau(char* nom_document,char* mot,int nb_recurrence);
void gere_tab_index(char* ligne);
void conception_index();
void genTabIndex(t_PileDescripteur* pile_texte);


//<mot>MOT
//nb_iteration NOM_FICHIER
//nb_iteration NOM_FICHIER
//.....
//nb_iteration NOM_FICHIER
//</mot>



// //////FORMAT DESCRIPETEUR/////////
// /*
// <descripteur>NOM_FICHIER
// NOM_AUTEUR
// NB_MOT_DU_TEXTE
//<mot>
// MOT_RECURENT_1 nb_recurrence
// MOT_RECURENT_2 nb_recurrence
// MOT_RECURENT_3 nb_recurrence
// MOT_RECURENT_4 nb_recurrence
// ..etc..
// MOT_RECURENT_X nb_recurrence
//</mot>
// </descripteur>

//*/


#endif
