#include"stdio.h"
#include"stdlib.h"

#define N 8

typedef struct joueur {
  char * pseudo;
  int couleur_j; // 0 = noir, 1 = blanc
  int nb_pions; // nombre de pions de sa couleur sur l'othellier
  int nb_tour; // nomnbre de tour que le joueur a joué depuis le début de la partie
  int plus_gros_coup; //coup prenant le plus de pions adverses 
  int palmares [3]={0,0,0}; //victoire,nuls,défaites
};

typedef struct pion {
  int couleur_p;
  int PosX; //position en X du pion
  int PosY; // position en Y du pion
};

void initialiser_othellier(int othellier[N]); //Initialise l'othellier à 0;
void config_othellier(int othellier[N]); // Mets en place la configuration de départ de l'initialiser_othellier
void afficher_otthelier(int othellier[N]);

/*Tour*/
//on change le joueur de qui c'est le tour
void affichage_coup(int othellier[N], joueur X);
void choix_coup(int othellier[N])
int MAJ_othellier(int othellier[N],);

