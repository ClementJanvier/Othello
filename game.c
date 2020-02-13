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


//Initialisation de la matrice de jeu
int othellier[N][N];

void tour(int othellier[N][N],joueur X){
  pions pion_1;
  affichage_coup(othellier);
  choix_coup(othellier,pion_1);
  MAJ_othellier(othellier,pion_1);
  retourne(othellier);

}

void jeu(){

  int nb_tour = 0;

  initialiser_othellier(othellier); //initialise la matrice à 0, soit défini l'othellier comme vide
  config_othellier(othellier); //Met en place la configuration de départ

  //Joueurs
  choix_pseudo(); //Création de la structure des 2 joueurs et choix de leur pseudos.
  choix_cote();

  //Affichage de l'othellier avec sa configuration initialise
  afficher_otthelier(othellier);

  //Choix de qui commence
  if(A.couleur_j==2){
    //joueur A commence
    Tour(othellier,A);
    nb_tour=1;
  }else{
    //joueur B commence
    Tour(othellier,B);
    nb_tour=0;
  }

  while(!fin_partie){
    if(nb_tour%2!=0){
      Tour(othellier,B);
    }else{
      Tour(othellier,A);
    }
    nb_tour++;
  }


}
