/**
  *\file game.c
  *\brief Fichier contenant la fonction principal pour jouer
  *\author: Martin JOUFFLINEAU, Achraf LAGCHOUR, Clément JANVIER et Thomas JAVELLE
  *\version 1.0
  *\date 2020
  */

#include <stdio.h>
#include <stdlib.h>
#include "library.h"


/**
  \*def N
  Defini la taille de l'othellier
  */
#define N 8

/**
  *\fn void tour(int othellier[N][N],joueur* X)
  *\brief Tour de jeu
  *\param othellier Matrice du jeu
  *\param X Joueur en train de joueur
*/
void tour(int othellier[N][N],joueur* X){

  pion* pion_1;
  pion_1 = malloc(sizeof(pion));
  printf(" \n  Joueur %s , à votre tour ! \n",X->pseudo);
  affichage_coup(othellier,X, pion_1);
  MAJ_othellier(othellier,pion_1,X);
  afficher_othellier(othellier);
  free(pion_1);
}

/**
  *\fn void jeu()
  *\brief Permet de jouer à une partie entière en utilsant la fonction tour
*/
void jeu(){

  int num_tour = 1;
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
  printf("\n \n /******* INITIALISATION DE L'OTHELLIER *******/ \n \n");
  afficher_othellier(othellier);

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

  while(fin_partie!=1){


    if(nb_tour%2!=0){
      if(peux_jouer(othellier,B)!=0){
        tour(othellier,B);
      }
      else{
        fin_partie++;
      }


    }else{
      if(peux_jouer(othellier,A)!=0){
        tour(othellier,A);
      } else {
        fin_partie++;
      }
    }
    compte_pion(othellier,A,B);
    affiche_nb_pions(A,B);
    nb_tour++;
    num_tour++;
  }
  printf("\n /******* PARTIE TERMINE *******/ \n");
  if(A->nb_pions>B->nb_pions)
    printf("%s est le joueur gagnant",A->pseudo);
  else
    printf("%s est le joueur gagnant",B->pseudo);




  free(A->pseudo);
  free(B->pseudo);
  free(A);
  free(B);
}
