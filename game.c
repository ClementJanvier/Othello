/**
*\ file game.c
*\ author: Martin Achraf Clément Thomas
*\ version 1.0
*\date 03/02/2020
*/

#include <stdio.h>
#include <stdlib.h>
#include "library.h"

#define N 8
#define VRAI 1
#define FAUX 0



void tour(int othellier[N][N],joueur* X){

  pion* pion_1;
  pion_1 = malloc(sizeof(pion));
  affichage_coup(othellier,X);
  choix_coup(othellier,pion_1);
  MAJ_othellier(othellier,pion_1,X);
  afficher_otthelier(othellier);
}

void jeu(){

  //Initialisation de la matrice de jeu
  int othellier[N][N];

  joueur* A;
  A = malloc(sizeof(joueur));

  joueur* B;
  B = malloc(sizeof(joueur));

  int fin_partie = 0;
  int nb_tour = 0;

  initialiser_othellier(othellier); //initialise la matrice à 0, soit défini l'othellier comme vide
  config_othellier(othellier); //Met en place la configuration de départ

  //Joueurs

  choix_pseudo(A,B); //Création de la structure des 2 joueurs et choix de leur pseudos.
  choix_cote(A,B);

  //Affichage de l'othellier avec sa configuration initialise
  afficher_otthelier(othellier);

  //Choix de qui commence
  if(A->couleur_j==2){
    //joueur A commence
    tour(othellier,A);
    nb_tour=1;
  }else{
    //joueur B commence
    tour(othellier,B);
    nb_tour=0;
  }

  printf("test apres premier tour du premier joueur\n");

  while(fin_partie!=1){
    if(nb_tour%2!=0){
      tour(othellier,B);
    }else{
      tour(othellier,A);
    }
    compte_pion(othellier,A,B);
    nb_tour++;
    if(A->nb_pions==0 || B->nb_pions==0)
      fin_partie = 1;
  }

  if(A->nb_pions==0)
    printf("%s a gagner!\n", B->pseudo);
  if(B->nb_pions==0)
    printf("%s a gagner!\n", A->pseudo);


  free(A->pseudo);
  free(B->pseudo);
  free(A);
  free(B);
}
