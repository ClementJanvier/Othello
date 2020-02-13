/**
*\file library.h
*\author Martin Thomas Clément Achraf
*\version 1.0
*\date 29/01/2020
*/

#include <stdio.h>
#include <stdlib.h>

#define N 8

typedef struct joueur {
  char * pseudo;
  int couleur_j; // 1 = noir, 2 = blanc
  int nb_pions; // nombre de pions de sa couleur sur l'othellier
  int nb_tour; // nombre de tour que le joueur a joué depuis le début de la partie
  int plus_gros_coup; //coup prenant le plus de pions adverses 
  int palmares [3]={0,0,0}; //victoire,nuls,défaites
};

typedef struct pion {
  int couleur_p;
  int PosX; //position en X du pion
  int PosY; // position en Y du pion
};

/*Fonctions relatives à la matrice */
void initialiser_othellier(int othellier[N][N]); //Initialise le plateau de jeu à 0; FAIT
void config_othellier(int othellier[N][N]); // Mets en place la configuration de départ de l'initialiser_othellier; FAIT
void afficher_otthelier(int othellier[N][N]); //FAIT
int dans_matrice(int x, int y); //Verifie si la position n'est pas en dehors de la matrice : renvoie 1 si oui, 0 sinon

/*Création Profil Joueur */
void choix_pseudo(); // FAIT
void choix_cote(); // Choix de la couleur utilisée par les joueurs //FAIT

/*Menu Démarrage */
void affichage_menu();//Affiche le menu de jeu; FAIT
void affichage_difficulté();//Affiche les difficultés possibles; FAIT


/*Tour*/
//on change le joueur de qui c'est le tour
void affichage_coup(int othellier[N][N], joueur X); //affichage coups possibles
int choix_coup(int othellier[N][N],pion pion_1); //Choix du coup effectué par le joueur, return les pos du pion à poser
int MAJ_othellier(int othellier[N][N],pion pion_1,joueur X); // Grâce aux PosX et PosY et à l'id du joueur, on place le nouveau pion et on retourne les pions nécéssaires
// Dans le fonction ci-dessus on appelera la fonction ci-dessous.
void retourne(int othellier[N][N],joueur X, pion pion_1); // Cette fonction parcours les pions et grâce a la pos du dernier pion posé elle met à jour la matrice en retournant les pions si nécéssaires.

/*JEU*/
void jeu();//La fonction est la fonction qui gère le déroulement du jeu, l'enchainement de toutes les fonctions ci-des
