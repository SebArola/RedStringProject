FILE * ptr_ficDonne;
char mot[100]="";
int nbCommun=0, nbMots=0, pourcentage, cestUnMot=0;
ptr_ficDonne=fopen("tempDonne", "w");   //création d'un fichier contenant le premier desc
fprintf(ptr_ficDonne, "%s", fichierDonne);    //on écrit le 1er desc dans le fichier
fclose(ptr_ficDonne);
ptr_ficDonne=fopen("tempDonne", "r");


while(!feof(ptr_ficDonne))
{
  fscanf(ptr_ficDonne, "%s ", mot);    //on lit le mot
  if(strcmp("</mot>", mot)==0)
  {
    cestUnMot=0;
  }
  if(cestUnMot)
  {
    fscanf(ptr_ficDonne, "%*s");    //on ignore le nombre d'occurences
    nbMots++;   //on incrémente le nombre de mots
    if (strstr(fichierCompare, mot) != NULL)    //si le 2eme desc contient le mot
    {
      nbCommun++;   //on incrémente le nombre de mots communs entre les 2
    }
  }
  if(strcmp("<mot>", mot)==0)
  {
    cestUnMot=1;
  }
}
pourcentage=(100*nbCommun)/nbMots;    //pourcentage de ressemblance
system("rm tempDonne");   //on supprime le fichier temp qui contenait le 1er descripteur
return pourcentage;
