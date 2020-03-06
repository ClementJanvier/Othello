#include<stdlib.h>
#include<stdio.h>

typedef struct element{int entier; struct element* suivant;}t_element;
t_element*pile;

void initpile(void){ //Initialise la pile à vide
  pile=NULL;
}

int pilevide(void){ //Vérifie que la pile est vide, si elle l'est retourne 1 sinon retourne 0
  return(pile==NULL);
}

void empiler(int x){
  t_element*nouv;

  nouv = malloc(sizeof(t_element));
  nouv->entier=x;
  nouv->suivant=pile;
  pile=nouv;
}

void depiler(int *x){
  t_element* sommet;

  if(pile!=NULL){
    *x=pile->entier;
    sommet=pile;
    pile=sommet->suivant;
    free(sommet);
  }
}

void sommetpile(int *x){
  if(pile!=NULL){
    *x=pile->entier;
  }
}
