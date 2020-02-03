#include <stdio.h>
#include <stdlib.h>
#include "library.h"

#define N 8


typedef struct joueur {
  char * pseudo;
  int couleur_j; // 2 = noir, 1 = blanc
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

void affichage_menu(){ // Affiche le menu de jeu
  printf("\n  Menu:\n");
	printf("1) Joueur contre joueur\n");
	printf("2) Jouer contre ordinateur\n");
	printf("3) Quitter\n\n");
}

void affichage_difficulte(){
  printf("-1- FACILE -1-");
  printf("-2- NORMAL -2-");
  printf("-3- INSANE -3-");
  printf("-4- RETOUR -4-");
}

void choix_pseudo(){ //Choix du pseudo dans le cas du JcJ
  
  joueur A;
  joueur B;
  
  printf(" Entrez un pseudo pour le joueur A : ");
  scanf("%s \n",A.pseudo);
  
  printf(" Entrez un pseudo pour le joueur B : ");
  scanf("%s \n",B.pseudo);
}

void initialiser_othellier(int othellier[N][N]){  //Initialise le plateau de jeu à 0;
int x,y;

	for(x=0; x<N; i++){
		for(y=0; y<N; j++){
			othellier[x][y] = '0'; // Initialiser la case à 0 
		}
	}
}  


void config_othellier(int othellier[N][N]){ // Mets en place la configuration de départ de l'initialiser_othellier
  //Mise en place des pions blancs
  othellier[3][3]=1;
  othellier[4][4]=1;
  
  //Mise en place des pions noirs
  othellier[4][3]=2;
  othellier[3][4]=2;
}

void afficher_otthelier(int othellier[N][N]){
  
  //Déclaration des variables
  char affiche[N][N];
  int i,j;
  
  //Parcours des matrices et remplissage de la matrice affichage
  for(i =0 ; i<N ; i++){
    for(j=0 ; j<N ; j++){
      if(othellier[i][j]==0){          //si la case est vide (case=0) on l'affiche par un espace
        printf(" ");
      }else if(othellier[i][j]==1){    // si la case contient un pion blanc (case=1) on affiche la lettre B pour illustrer
        printf("B");
      }else{             a             //Même principe avec un pion noir
        printf("N");
      }
    }
    printf("\n");          // A la fin de la ligne on saute une ligne pour rendre l'affichage pertinent
  }
}
