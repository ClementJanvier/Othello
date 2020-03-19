#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"
#include "pile.h"

#define N 8
#define VOISINS 8


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

void choix_pseudo(joueur* A,joueur* B){ //Choix du pseudo dans le cas du JcJ

  char strA[30];
  char strB[30];

  printf(" Entrez un pseudo pour le joueur A : ");
  scanf("%s",strA);
  A->pseudo=malloc(sizeof(strlen(strA)+1));
  strcpy(A->pseudo,strA);


  printf(" Entrez un pseudo pour le joueur B : ");
  scanf("%s",strB);
  B->pseudo=malloc(sizeof(strlen(strB)+1));
  strcpy(B->pseudo,strB);


}

void choix_cote(joueur *A,joueur* B){
  int rep;
  do{
    printf("%s, Pour jouer la couleur Noir rentrez 1 ou 2 pour la couleur blanche :",A->pseudo);
    scanf("%d",&rep);
  } while( (rep!=1 && rep!=2 ) );

  if( rep == 1){
    A->couleur_j=1; //Le joueur A a la couleur noire
    B->couleur_j=2; // Le joueur B a la couleur blanche
  }
  else{
    A->couleur_j=2; // Inverse de ci-dessus
    B->couleur_j=1;
  }
}

void initialiser_othellier(int othellier[N][N]){  //Initialise le plateau de jeu à 0;
int i,j;

	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			othellier[i][j] = 0; // Initialiser la case à 0
		}
	}
}


void config_othellier(int othellier[N][N]){ // Mets en place la configuration de départ de l'initialiser_othellier
  //Mise en place des pions blancs
  othellier[3][3]=2;
  othellier[4][4]=2;
  othellier[2][3]=2;
  othellier[5][4]=2;
  //Mise en place des pions noirs
  othellier[4][3]=1;
  othellier[3][4]=1;
  othellier[4][4]=1;
  othellier[2][4]=1;
}

void afficher_otthelier(int othellier[N][N]){

  //Déclaration des variables
  char affiche[N][N];
  int i,j;

  //Parcours des matrices et remplissage de la matrice affichage
  for(i =0 ; i<N ; i++){
    for(j=0 ; j<N ; j++){
      if(othellier[i][j]==0){          //si la case est vide (case=0) on l'affiche par un espace
        printf("* ");
      }else if(othellier[i][j]==1){    // si la case contient un pion blanc (case=1) on affiche la lettre B pour illustrer
        printf("B ");
      }else if(othellier[i][j]==2){    //Même principe avec un pion noir
        printf("N ");
      }
    }
    printf("\n");          // A la fin de la ligne on saute une ligne pour rendre l'affichage pertinent
  }
}


void affichage_coup(int othellier[N][N], joueur *X){
  int nb_choix =0;
  int i, j;
  int x, y;
  
  int c_pion, c_pion_adv; //couleur du pion du joueur et celle de son adversaire.
  
  if(X->couleur_j==1){ //si le joueur a les pions noir
    c_pion = 1; //noir est repertorié comme étant égal à 1 sur l'othellier
    c_pion_adv = 2; // blanc comme étant égal à 2
  }else{
    c_pion = 2;
    c_pion_adv = 1;
  }
  
  for(i = 0; i<N ; i++){
      for( j=0; j<N ; j++){
         if(othellier[i][j]==c_pion){
            
           if((othellier[i+1][j]==c_pion_adv && dans_matrice(i+1,j)==1)){ //haut et dans la matrice
              x = i+1; //x prend les coordonées de la case en cours dont on sait quelle est blanche
              y = j;
              while(othellier[x][y]==c_pion_adv){ 
                if(othellier[x+1][y]==c_pion_adv){
                  x++;
                }else if (othellier[x+1][y]==0){
                  printf("Choix %d : PosX = %d et PosY = %d \n",nb_choix,x+1,y);
                  x++;
                  nb_choix++;
                }
              }
            }             
            if((othellier[i+1][j+1]==c_pion_adv && dans_matrice(i+1,j+1)==1)){ //diagonale haut droite 
              x = i+1; //x prend les coordonées de la case en cours dont on sait quelle est blanche
              y = j+1;
              
              while(othellier[x][y]==c_pion_adv){ 
                if(othellier[x+1][y+1]==c_pion_adv){
                  x++;
                  y++;
                }else if (othellier[x+1][y+1]==0){
                  printf("Choix %d : PosX = %d et PosY = %d \n",nb_choix,x+1,y+1);
                  x++;
                  y++;
                  nb_choix++;
                }
              }
              
            }
            if(othellier[i][j+1]==c_pion_adv && dans_matrice(i,j+1)==1){ // droite et dans la matrice
              x = i;
              y = j+1;
              while(othellier[x][y]==c_pion_adv){ 
                if(othellier[x][y+1]==c_pion_adv){
                  y++;
                }else if (othellier[x][y+1]==0){
                  printf("Choix %d : PosX = %d et PosY = %d \n",nb_choix,x,y+1);
                  y++;
                  nb_choix++;
                }
              }
            }
            if(othellier[i-1][j+1]==c_pion_adv && dans_matrice(i-1,j+1)==1){ //diagonale bas droite et dans la matrice
              x = i-1;
              y = j+1;
              while(othellier[x][y]==c_pion_adv){ 
                if(othellier[x-1][y+1]==c_pion_adv){
                  x--;
                  y++;
                }else if (othellier[x-1][y+1]==0){
                  printf("Choix %d : PosX = %d et PosY = %d \n",nb_choix,x-1,y+1);
                  x--;
                  y++;
                  nb_choix++;
                }
              }
            }
            if(othellier[i-1][j]==c_pion_adv && dans_matrice(i-1,j)==1){ //bas et dans la matrice 
              x = i-1;
              y = j;
              while(othellier[x][y]==c_pion_adv){ 
                if(othellier[x-1][y]==c_pion_adv){
                  x--;
                }else if (othellier[x-1][y]==0){
                  printf("Choix %d : PosX = %d et PosY = %d \n",nb_choix,x-1,y);
                  x--;
                  nb_choix++;
                }
              }
            }
            if(othellier[i-1][j-1]==c_pion_adv && dans_matrice(i-1,j-1)==1){ //diagonale bas gauche et dans la matrice
              x = i-1;
              y = j-1;
              while(othellier[x][y]==c_pion_adv){ 
                if(othellier[x-1][y-1]==c_pion_adv){
                  x--;
                  y--;
                }else if (othellier[x-1][y-1]==0){
                  printf("Choix %d : PosX = %d et PosY = %d \n",nb_choix,x-1,y-1);
                  x--;
                  y--;
                  nb_choix++;
                }
              }
            }
            if(othellier[i][j-1]==c_pion_adv && dans_matrice(i,j-1)==1){ //gauche et dans la matrice
              x = i;
              y = j-1;
              while(othellier[x][y]==c_pion_adv){ 
                if(othellier[x][y-1]==c_pion_adv){
                  y--;
                }else if (othellier[x][y-1]==0){
                  printf("Choix %d : PosX = %d et PosY = %d \n",nb_choix,x,y-1);
                  y--;
                  nb_choix++;
                }
              }
            }
            if(othellier[i+1][j-1]==c_pion_adv && dans_matrice(i+1,j-1)==1){ //diagonale haut gauche et dans la matrice
              x = i+1;
              y = j -1;
              while(othellier[x][y]==c_pion_adv){ 
                if(othellier[x+1][y-1]==c_pion_adv){
                  x++;
                  j--;
                }else if (othellier[x+1][y-1]==0){     
                  printf("Choix %d : PosX = %d et PosY = %d \n",nb_choix,x+1,y-1);
                  x++;
                  y--;
                  nb_choix++;
                }
              }
            }
         }
       }
    }
  
  
}



void choix_coup(int othellier[N][N],pion* pion_1){ //Choix du coup effectué par le joueur
    printf("Donnez les coordonnées du pion choisi \n");

    printf("X = ");
    scanf("%d",&pion_1->PosX);

    printf("Y = ");
    scanf("%d",&pion_1->PosY);
  
  //Compléter la fonction avec SDL pour le choix avec un click de la souris (Plus tard)
  }




// Cette fonction parcours les pions et grâce a la pos du dernier pion posé,
// elle met à jour la matrice en retournant les pions si nécéssaires.
void retourne(int othellier[N][N],joueur* X, pion *pion_1){
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
      i++;
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
void MAJ_othellier(int othellier[N][N], pion *pion_1,joueur* X){
    othellier[pion_1->PosX][pion_1->PosY]=X->couleur_j;
    retourne(othellier,X, pion_1); // rajoute joueur X
}
