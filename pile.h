#include<stdlib.h>
#include<stdio.h>

typedef struct element{int entier; struct element* suivant;}t_element;
t_element*pile;

void initpile(void);
int pilevide(void);
void empiler(int x);
void depiler(int *x);
void sommetpile(int *x);
