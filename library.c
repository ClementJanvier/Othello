#include <stdio.h>
#include <stdlib.h>
#include "library.h"

#define N 8
#define VOISINS 8


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


int dans_matrice(int x, int y){
  if(x>=0 && x<N && y>=0 && y<N)
    return 1;
  else
    return 0;
}

void choix_pseudo(){ //Choix du pseudo dans le cas du JcJ
  
  joueur A;
  joueur B;
  
  printf(" Entrez un pseudo pour le joueur A : ");
  scanf("%s \n",A.pseudo);
  
  printf(" Entrez un pseudo pour le joueur B : ");
  scanf("%s \n",B.pseudo);
}

void choix_cote(){
  char *couleur;
  do{
    printf(" %s entrez la couleur que vous jouerez (noir ou blanc): ",A.pseudo);
    scanf("%s \n",couleur);
  
  while((*couleur)!='noir'&&(*couleur)!='blanc');
  
  if(*couleur == 'noir'){
    A.couleur=2; //Le joueur A a la couleur noire
    B.couleur=1; // Le joueur B a la couleur blanche
  }else{
    A.couleur=1; // Inverse de ci-dessus
    B.couleur=2;
  }
  
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

void affichage_coup(int othellier[N][N], joueur X){
  
  int nb_coup = 0;
  int i, j, x, y, xx, yy;
  int pion_coul;
  int nb_choix=1;
  
  if(X->couleur_j==2){  //joueur avec pion noir
    c_pion=1;
    c_pion_adv=2;
  }
  else if(X->couleur_j==1){  //joueur avec pion blanc
    c_pion=2;
    c_pion_adv=1;
  }
  
  initpile();
  
  if(!pilevide()){
    while(!pilevide()){
      depiler();  
    }
  }
    
  
  
  //8 directions différentes à observer
  if(X.couleur=='noir'){
    pion_coul=2;
  }else{
    pion_coul=1;
  }
  
  //Parcours de l'othellier à la recherche d'un pion de couleur correspondante.
  for(i = 0; i<N ; i++){
    for( j=0 ; j<N ; j++){
       if(othellier[i][j]==pion_coul){
         empiler(i);
         empiler(j);
       }
     }
  }
  
  //pour chaque pion trouvé on regarde ses voisins et on voit si un coup est possible
  while(!pilevide()){
    depiler(y);
    depiler(x);
    
    for(z=0;z<nb_voisins;z++){
      if(othellier[x][y++]==c_pion_adv){ //droite
        yy=y+1;
        while(othellier[x][yy]==c_pion_adv){
          yy++; //Source erreur a voir si ça pointe sur le dernier de la couleur du joueur ou si ça pointe sur une case vide
        }
        if(othellier[x][yy]==0){
          //c'est une possibilité de jouer
          printf("choix %d : X=%d Y=%d \n",nb_choix,x,y);
          nb_choix++;
        }
      }
      else if(othellier[x--][y++]==c_pion_adv){ //bas droite
        xx=x-1;
        yy=y+1;
        while(othellier[xx][yy]==c_pion_adv){
          xx--;
          yy++;
        }
        
        if(othellier[xx][yy]==0){
          //c'est un coup jouable
          printf("choix %d : X=%d Y=%d \n",nb_choix,x,y);
          nb_choix++;
        }
      }
      
      else if(othellier[x--][y]==c_pion_adv){ //bas
        xx=x-1;
        while(othellier[xx][y]=c_pion_adv){
          xx--;
        }
        if(othellier[xx][yy]==0){
          //c'est un coup jouable
          printf("choix %d : X=%d Y=%d \n",nb_choix,x,y);
          nb_choix++;
        }
      }
      
      else if(othellier[x--][y--]==c_pion_adv){ //bas gauche
        yy=y-1;
        xx=x-1;
        while(othellier[xx][yy]==c_pion_adv){
          xx--;
          yy--; //Source erreur a voir si ça pointe sur le dernier de la couleur du joueur ou si ça pointe sur une case vide
        }
        if(othellier[xx][yy]==0){
          //c'est une possibilité de jouer
          printf("choix %d : X=%d Y=%d \n",nb_choix,x,y);
          nb_choix++;
        }
      }
      
      else if(othellier[x][y--]==c_pion_adv){ //gauche
        yy=y-1;
        while(othellier[x][yy]==c_pion_adv){
          yy--; //Source erreur a voir si ça pointe sur le dernier de la couleur du joueur ou si ça pointe sur une case vide
        }
        if(othellier[x][yy]==0){
          //c'est une possibilité de jouer
          printf("choix %d : X=%d Y=%d \n",nb_choix,x,y);
          nb_choix++;
        }
      }
      
      else if(othellier[x++][y++]==c_pion_adv){ //haut gauche
        xx=x+1;
        yy=y+1;
        while(othellier[xx][yy]==c_pion_adv){
          xx+;
          yy++; //Source erreur a voir si ça pointe sur le dernier de la couleur du joueur ou si ça pointe sur une case vide
        }
        if(othellier[xx][yy]==0){
          //c'est une possibilité de jouer
          printf("choix %d : X=%d Y=%d \n",nb_choix,x,y);
          nb_choix++;
        }
      }
      else if(othellier[x++][y]==c_pion_adv){ //haut
        xx=x+1;
        while(othellier[xx][y]==c_pion_adv){
          xx++; //Source erreur a voir si ça pointe sur le dernier de la couleur du joueur ou si ça pointe sur une case vide
        }
        if(othellier[xx][y]==0){
          //c'est une possibilité de jouer
          printf("choix %d : X=%d Y=%d \n",nb_choix,x,y);
          nb_choix++;
        }
      }
      else if(othellier[x++][y--]==c_pion_adv){ //haut droite
        xx=x+1;
        yy=y-1;
        while(othellier[xx][yy]==c_pion_adv){
          xx++;
          yy--; //Source erreur a voir si ça pointe sur le dernier de la couleur du joueur ou si ça pointe sur une case vide
        }
        if(othellier[xx][yy]==0){
          //c'est une possibilité de jouer
          printf("choix %d : X=%d Y=%d \n",nb_choix,x,y);
          nb_choix++;
        }
      }
    }  
  }
  
  
  
  
}

  
int choix_coup(int othellier[N][N],pion pion_1){ //Choix du coup effectué par le joueur
  
  do{
    prinf("Donnez les coordonnées du pion choisi");
    scanf("%d %d",pion_1->PosX, pion_1->PosY);
  }
  while(othellier[pion_1.PosX][pion_1.PosY]!=0&&dans_matrice(pion_1.PosX, pion_1.PosY));
  
  //Faire la fonction avec SDL pour le choix avec un click de la souris (Plus tard)
}

int MAJ_othellier(int othellier[N][N],pion pion_1,joueur X){
    othellier[pion_1.PosX][pion_1.PosY]=X.couleur_j;
    retourne(othellier[N][N],joueur X);
}

  
// Cette fonction parcours les pions et grâce a la pos du dernier pion posé,
// elle met à jour la matrice en retournant les pions si nécéssaires.
void retourne(int othellier[N][N],joueur X, pion pion_1){
  int x=pion_1->PosX;  //coordonnée X du dernier pion placé
  int y=pion_1->PosY;  //coordonnée Y du dernier pion placé
  int i=x;
  int j=y;
  
  int c_pion, c_pion_adv; //couleur pion et couleur pion adverse

  
  if(X->couleur_j==1){  //joueur avec pion noir
    c_pion=1;
    c_pion_adv=2;
  }
  else if(X->couleur_j==2){  //joueur avec pion blanc
    c_pion=2;
    c_pion_adv=1;
  }
  
//Verfication de toutes les directions possibles et retournements des pinns nécessaires
  
  //Ligne vers la gauche
  i--;
  while(dans_matrice(i,j)==1){
    if(othellier[i][j]==c_pion_adv){  //si le pion est adverse, on vérifie la case suivante
      i--;
    }
    else if(othellier[i][j]==c_pion){ //quand le pion est au joueur, on retourne les pions adverses situés entre les deux pions du joueur
      i++;
      while(i!=x&&j!=y){
        othellier[i][j]=c_pion;
        i++;
      }
    }
  }
  //Vers la droite
  i=x;
  j=y;
  i++;
  
  while(dans_matrice(i,j)==1){
    if(othellier[i][j]==c_pion_adv){
      i++:
    }
    else if(othellier[i][j]==c_pion){
      i--;
      while(i!=x&&j!=y){
        othellier[i][j]=c_pion;
        i--;
      }
    }
  }
  
  //Vers le haut 
  i=x;
  j=y;
  j++;
  
  while(dans_matrice(i,j)==1){
    if(othellier[i][j]==c_pion_adv){
      j++;
    }
    else if(othellier[i][j]==c_pion){
      j--;
      while(i!=x&&j!=y){
        othellier[i][j]=c_pion;
        j--;
      }
    }
  }
  
  //Vers le bas
  i=x;
  j=y;
  j--;

  while(dans_matrice(i,j)==1){
    if(othellier[i][j]==c_pion_adv){
      j--;
    }
    else if(othellier[i][j]==c_pion){
      j++;
      while(i!=x&&j!=y){
        othellier[i][j]=c_pion;
        j++;
      }
    }
  }
  
  //Diago haut gauche
  i=x;
  j=y;
  i--;
  j++;

  while(dans_matrice(i,j)==1){
    if(othellier[i][j]==c_pion_adv){
      i--;
      j++;
    }
    else if(othellier[i][j]==c_pion){
      i++;
      j--;
      while(i!=x&&j!=y){
        othellier[i][j]=c_pion;
        i++;
        j--;
      }
    }
  }
  
  //Diago haut droite 
  i=x;
  j=y;
  i++;
  j++;

  while(dans_matrice(i,j)==1){
    if(othellier[i][j]==c_pion_adv){
      i++;
      j++;
    }
    else if(othellier[i][j]==c_pion){
      i--;
      j--;
      while(i!=x&&j!=y){
        othellier[i][j]=c_pion;
        i--;
        j--;
      }
    }
  }
  
  //Diago bas gauche
  i=x;
  j=y;
  i--;
  j--;
  
  while(dans_matrice(i,j)==1){
    if(othellier[i][j]==c_pion_adv){
      i--;
      j--;
    }
    else if(othellier[i][j]==c_pion){
      i++;
      j++;
      while(i!=x&&j!=y){
        othellier[i][j]=c_pion;
        i++;
        j++;
      }
    }
  }
  
  //Diago bas droite
  i=x;
  j=y;
  i++;
  j--;
  
  while(dans_matrice(i,j)==1){
    if(othellier[i][j]==c_pion_adv){
      i++;
      j--;
    }
    else if(othellier[i][j]==c_pion){
      i--;
      j++;
      while(i!=x&&j!=y){
        othellier[i][j]=c_pion;
        i--;
        j++;
      }
    }
  }
  
}
