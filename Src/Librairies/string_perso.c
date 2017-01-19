#include "string_perso.h"
void strremove(char * string, int n){
    char * temp = malloc(sizeof(char*)*(strlen(string)-n));
    for (int i=0; i<strlen(string);i++){
        if(i>=n){
                temp[i-n]=string[i];
        }
    }
    for (int i=0; i<strlen(string);i++){
        string[i] = temp[i];

    }
}
