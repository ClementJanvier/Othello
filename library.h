/**
  *\file library.h
  *\brief Fichier contenant les structures et les prototypes de fonctions
  *\author: Martin JOUFFLINEAU, Achraf LAGCHOUR, Clément JANVIER et Thomas JAVELLE
  *\version 1.0
  *\date 2020
  */

  #include <stdio.h>
  #include <stdlib.h>

  /**
    \*def N
    Defini la taille de l'othellier
    */
  #define N 8
  /**
    \*def NOIR
    Les pions noirs sont définis sur 1
    */
  #define NOIR 1
  /**
    \*def BLANC
    Les pions blancs sont définis sur 1
    */
  #define BLANC 2

  /**
    *\struct joueur_s
    *\brief Contient le pseudo du joueur, la couleur de ses pions, le nombre de pions resants, le nombre de tour qu'il a effectué...A finir
    */
  typedef struct joueur_s{
    char *pseudo; /** Pseudo du joueur */
    int couleur_j; /** Couleur du joueur 1 (1 pour noir et 2 pour blanc) */
    int nb_pions; /** Nombre de pions de sa couleur sur l'othellier */
    int nb_tour; /** Nombre de tour que le joueur a joué depuis le début de la partie */
    int plus_gros_coup; /** Coup prenant le plus de pions adverses */
    int palmares[3]; /** Victoire,nuls,défaites */
  }joueur;

  /**
    *\struct pion_s
    */
  typedef struct pion_s{
    int couleur_p; /** Couleur du pion */
    int PosX; /** Position en X du pion */
    int PosY; /** Position en X du pion */
  }pion;

  /*Fonctions relatives à la matrice */
  void initialiser_othellier(int othellier[N][N]); //Initialise le plateau de jeu à 0; FAIT
  void config_othellier(int othellier[N][N]); // Mets en place la configuration de départ de l'initialiser_othellier; FAIT
  void afficher_othellier(int othellier[N][N]); //FAIT
  int dans_matrice(int x, int y); //Verifie si la position n'est pas en dehors de la matrice : renvoie 1 si oui, 0 sinon

  /*Création Profil Joueur */
  void choix_pseudo(joueur* A,joueur *B); // FAIT
  void choix_cote(joueur* A,joueur *B); // Choix de la couleur utilisée par les joueurs //FAIT

  /*Menu Démarrage */
  void affichage_menu();//Affiche le menu de jeu; FAIT


  /*Tour*/
  //on change le joueur de qui c'est le tour
  int peux_jouer(int othellier[N][N], joueur *X);
  void affichage_coup(int othellier[N][N], joueur* X,pion* pion_1); //affichage coups possibles
  void choix_coup(int othellier[N][N],pion* pion_1,int TabX[],int TabY[],int nb_coup); //Choix du coup effectué par le joueur, return les pos du pion à poser
  void MAJ_othellier(int othellier[N][N],pion *pion_1,joueur* X); // Grâce aux PosX et PosY et à l'id du joueur, on place le nouveau pion et on retourne les pions nécéssaires
  // Dans le fonction ci-dessus on appelera la fonction ci-dessous.
  void retourne(int othellier[N][N],joueur* X, pion *pion_1); // Cette fonction parcours les pions et grâce a la pos du dernier pion posé elle met à jour la matrice en retournant les pions si nécéssaires.
  void compte_pion(int othellier[N][N], joueur* A, joueur* B); //Compte le nombre de pion restant sur l'othellier et met à jour la structure du joueur
  void affiche_nb_pions(joueur* A, joueur* B);
  /*JEU*/
  void jeu();//La fonction est la fonction qui gère le déroulement du jeu, l'enchainement de toutes les fonctions ci-des
