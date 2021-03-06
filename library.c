/**
  *\file library.c
  *\brief Fichier contenant toutes les fonctions nécéssaires au fonctionnement du jeu
  *\author: Martin JOUFFLINEAU, Achraf LAGCHOUR, Clément JANVIER et Thomas JAVELLE
  *\version 1.0
  *\date 2020
  */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

/**
  \*def N
  Defini la taille de l'othellier
  */
#define N 8
/**
  \*def VOISINS
  Nombre de voisins maximums
  */
#define VOISINS 8


/**
  *\fn void affichage_menu()
  *\brief Affichage du menu
*/
void affichage_menu(){ // Affiche le menu de jeu
  printf("\n \n  /******* Menu *******/ \n \n");
	printf("1) Joueur contre joueur\n");
	printf("2) Quitter\n\n");
}


/**
  *\fn int dans_matrice(int x, int y)
  *\brief Vérification d'une coordonnée présent ou non dans la matrice
  *\param x, y Coordonées d'un case de la matrice
  *\return 1 si la case est dans la matrice et 0 sinon
  */
int dans_matrice(int x, int y) {
    return ((y >= 0) && (y < N) && (x >= 0) && (x < N));
}


/**
  *\fn void choix_pseudo(joueur* A,joueur* B)
  *\brief Choix des pseudos pour les deux joueurs
  *\param A, B Joueur A et B
  */
void choix_pseudo(joueur* A,joueur* B){ //Choix du pseudo dans le cas du JcJ

  char strA[30];
  char strB[30];
  printf("\n \n /******* CHOIX DES PSEUDOS *******/ \n \n");
  printf(" Entrez un pseudo pour le joueur A : ");
  scanf("%s",strA);
  A->pseudo=malloc(sizeof(strlen(strA)+1));
  strcpy(A->pseudo,strA);


  printf(" Entrez un pseudo pour le joueur B : ");
  scanf("%s",strB);
  B->pseudo=malloc(sizeof(strlen(strB)+1));
  strcpy(B->pseudo,strB);


}


/**
  *\fn void choix_cote(joueur * A,joueur* B)
  *\brief Choix des côtés pour les deux joueurs
  *\param A, B Joueur A et B
  */
void choix_cote(joueur *A,joueur* B){
  int rep;
  printf("\n \n /******* CHOIX DE LA COULEUR *******/ \n \n");
  do{
    printf(" Joueur %s, \n --> Choisissez 1 pour jouer la couleur noir <-- \n --> Choisissez 2 pour jouer la couleur blanche<-- \n",A->pseudo);
    printf("CHOIX : ");
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


/**
  *\fn void initialiser_othellier(int othellier[N][N])
  *\brief Initialisation de l'othellier à 0
  *\param othellier Matrice du jeu
  */
void initialiser_othellier(int othellier[N][N]){  //Initialise le plateau de jeu à 0;
int i,j;

	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			othellier[i][j] = 0; // Initialiser la case à 0
		}
	}
}


/**
  *\fn void config_othellier(int othellier[N][N])
  *\brief Mise en place des pions de base pour commencer une partie
  *\param othellier Matrice du jeu
  */
void config_othellier(int othellier[N][N]){ // Mets en place la configuration de départ de l'initialiser_othellier
  //Mise en place des pions blancs
  othellier[3][3]=2;
  othellier[4][4]=2;

  //Mise en place des pions noirs
  othellier[4][3]=1;
  othellier[3][4]=1;
}


/**
  *\fn void afficher_othellier(int othellier[N][N])
  *\brief Affichage de l'othellier
  *\param othellier Matrice du jeu
  */
void afficher_othellier(int othellier[N][N]){
  //Déclaration des variables
  int i, j;

  //Parcours des matrices et remplissage de la matrice affichage
  printf("  Y ");
  for (j = 0; j < N; j++) {
    printf("%d ", j);
  }
  printf("\n");
  printf("X\n");

  for(i =0 ; i<N ; i++){
    if(i!=8)
      printf("%d ", i);
      printf("  ");
    for(j=0 ; j<N ; j++){
      if(othellier[i][j]==0){          //si la case est vide (case=0) on l'affiche par un espace
        printf("* ");
      }else if(othellier[i][j]==2){    // si la case contient un pion blanc (case=1) on affiche la lettre B pour illustrer
        printf("B ");
      }else if(othellier[i][j]==1){    //Même principe avec un pion noir
        printf("N ");
      }
    }
    printf("\n");          // A la fin de la ligne on saute une ligne pour rendre l'affichage pertinent
  }
}


/**
  *\fn void affichage_coup(int othellier[N][N], joueur* X,pion* pion_1)
  *\brief Affichage de chaque coup possible pour le tour du joueur donné et utilise la fonction choix coup
  *\param othellier Matrice du jeu
  *\param X Joueur en train de joueur
  *\param pion_1 Pion qui vient d'être joué
  */
void affichage_coup(int othellier[N][N], joueur* X,pion* pion_1){
      int nb_choix =0;
      int i, j;
      int x, y;
      int sortir=0;
      int c_pion, c_pion_adv; //couleur du pion du joueur et celle de son adversaire.
      int TabX[25];
      int TabY[25];
      int indice = 0; // Variable supplémentaire pour parcourir le tableau de stockage des coups
      int deja_present = 0; // Variable permettant de savoir si un choix est déjà présent dans le tableau pour éviter les doublons
      int nb_pions_pris = 0;
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


               if(othellier[i+1][j]==c_pion_adv && dans_matrice(i+1,j)==1){ //bas et dans la matrice
                  x = i+1; //x prend les coordonées de la case en cours dont on sait quelle est blanche
                  y = j;

                  while( sortir != 1 && dans_matrice(x,y)==1){
                    x++;
                    nb_pions_pris++;
                    if(othellier[x][y]==0 && dans_matrice(x,y)==1){

                        for(indice = 0; indice<nb_choix ; indice++){ // On vérifie si le coup n'est pas déjà dans le tableau
                            if((TabX[indice]==x) && (TabY[indice]==y)){
                                deja_present = 1;
                            }
                        }

                        if(deja_present == 0){ // Si le coup n'est pas dans le tableau alors on le rentre dedans
                            printf("Choix %d : PosX = %d et PosY = %d || Pions pris = %d\n",nb_choix+1,x,y,nb_pions_pris);
                            TabX[nb_choix]=x;
                            TabY[nb_choix]=y;
                            nb_choix++;
                        }
                        deja_present=0;
                        sortir=1;
                    }else if(othellier[x][y]==c_pion)
                      sortir=1;
                  }
                }
                nb_pions_pris=0;
                sortir=0;
                if(othellier[i+1][j+1]==c_pion_adv && dans_matrice(i+1,j+1)==1){ //diagonale bas droite
                  x = i+1; 
                  y = j+1;
                  while( sortir != 1 && dans_matrice(x,y)==1){
                    x++;
                    y++;
                    nb_pions_pris++;
                    if(othellier[x][y]==0 && dans_matrice(x,y)==1){

                        for(indice = 0; indice<nb_choix ; indice++){ 
                            if((TabX[indice]==x) && (TabY[indice]==y)){
                                deja_present = 1;
                            }
                        }

                        if(deja_present == 0){ 
                            printf("Choix %d : PosX = %d et PosY = %d || Pions pris = %d\n",nb_choix+1,x,y,nb_pions_pris);
                            TabX[nb_choix]=x;
                            TabY[nb_choix]=y;
                            nb_choix++;
                        }
                        deja_present=0;
                        sortir=1;
                    }else if(othellier[x][y]==c_pion)
                      sortir=1;
                  }
                }
                nb_pions_pris=0;
                sortir=0;
                if(othellier[i][j+1]==c_pion_adv && dans_matrice(i,j+1)==1){ // droite et dans la matrice
                  x = i;
                  y = j+1;
                  while( sortir != 1 && dans_matrice(x,y)==1){
                    y++;
                    nb_pions_pris++;
                    if(othellier[x][y]==0 && dans_matrice(x,y)==1){

                        for(indice = 0; indice<nb_choix ; indice++){ 
                            if((TabX[indice]==x) && (TabY[indice]==y)){
                                deja_present = 1;
                            }
                        }

                        if(deja_present == 0){ 
                            printf("Choix %d : PosX = %d et PosY = %d || Pions pris = %d\n",nb_choix+1,x,y,nb_pions_pris);
                            TabX[nb_choix]=x;
                            TabY[nb_choix]=y;
                            nb_choix++;
                        }
                        deja_present=0;
                        sortir=1;
                    }else if(othellier[x][y]==c_pion)
                      sortir=1;
                  }
                }
                nb_pions_pris=0;
                sortir=0;

                if(othellier[i-1][j+1]==c_pion_adv && dans_matrice(i-1,j+1)==1){ //diagonale haut droite et dans la matrice
                  x = i-1;
                  y = j+1;
                  while( sortir != 1 && dans_matrice(x,y)==1){
                    x--;
                    y++;
                    nb_pions_pris++;
                    if(othellier[x][y]==0 && dans_matrice(x,y)==1){

                        for(indice = 0; indice<nb_choix ; indice++){ 
                            if((TabX[indice]==x) && (TabY[indice]==y)){
                                deja_present = 1;
                            }
                        }

                        if(deja_present == 0){ 
                            printf("Choix %d : PosX = %d et PosY = %d || Pions pris = %d\n",nb_choix+1,x,y,nb_pions_pris);
                            TabX[nb_choix]=x;
                            TabY[nb_choix]=y;
                            nb_choix++;
                        }
                        deja_present=0;
                        sortir=1;
                    }else if(othellier[x][y]==c_pion)
                      sortir=1;
                  }
                }
                nb_pions_pris=0;
                sortir=0;
                if(othellier[i-1][j]==c_pion_adv && dans_matrice(i-1,j)==1){ //haut et dans la matrice
                  x = i-1;
                  y = j;
                  while( sortir != 1 && dans_matrice(x,y)==1){
                    nb_pions_pris++;
                    x--;
                    if(othellier[x][y]==0 && dans_matrice(x,y)==1){

                        for(indice = 0; indice<nb_choix ; indice++){ 
                            if((TabX[indice]==x) && (TabY[indice]==y)){
                                deja_present = 1;
                            }
                        }

                        if(deja_present == 0){ 
                            printf("Choix %d : PosX = %d et PosY = %d || Pions pris = %d\n",nb_choix+1,x,y,nb_pions_pris);
                            TabX[nb_choix]=x;
                            TabY[nb_choix]=y;
                            nb_choix++;
                        }
                        deja_present=0;
                        sortir=1;
                    }else if(othellier[x][y]==c_pion)
                      sortir=1;
                  }
                }
                nb_pions_pris=0;
                sortir=0;
                if(othellier[i-1][j-1]==c_pion_adv && dans_matrice(i-1,j-1)==1){ //diagonale haut gauche et dans la matrice
                  x = i-1;
                  y = j-1;
                  while( sortir != 1 && dans_matrice(x,y)==1){
                    x--;
                    y--;
                    nb_pions_pris++;
                    if(othellier[x][y]==0 && dans_matrice(x,y)==1){

                        for(indice = 0; indice<nb_choix ; indice++){ 
                            if((TabX[indice]==x) && (TabY[indice]==y)){
                                deja_present = 1;
                            }
                        }

                        if(deja_present == 0){ 
                            printf("Choix %d : PosX = %d et PosY = %d || Pions pris = %d\n",nb_choix+1,x,y,nb_pions_pris);
                            TabX[nb_choix]=x;
                            TabY[nb_choix]=y;
                            nb_choix++;
                        }
                        deja_present=0;
                        sortir=1;
                    }else if(othellier[x][y]==c_pion)
                      sortir=1;
                  }
                }
                nb_pions_pris=0;
                sortir=0;
                if(othellier[i][j-1]==c_pion_adv && dans_matrice(i,j-1)==1){ //gauche et dans la matrice
                  x = i;
                  y = j-1;
                 while( sortir != 1 && dans_matrice(x,y)==1){
                    y--;
                    nb_pions_pris++;
                    if(othellier[x][y]==0 && dans_matrice(x,y)==1){

                        for(indice = 0; indice<nb_choix ; indice++){ 
                            if((TabX[indice]==x) && (TabY[indice]==y)){
                                deja_present = 1;
                            }
                        }

                        if(deja_present == 0){ 
                            printf("Choix %d : PosX = %d et PosY = %d || Pions pris = %d\n",nb_choix+1,x,y,nb_pions_pris);
                            TabX[nb_choix]=x;
                            TabY[nb_choix]=y;
                            nb_choix++;
                        }
                        deja_present=0;
                        sortir=1;
                    }else if(othellier[x][y]==c_pion)
                      sortir=1;
                  }
                }
                nb_pions_pris=0;
                sortir=0;
                if(othellier[i+1][j-1]==c_pion_adv && dans_matrice(i+1,j-1)==1){ //diagonale bas gauche et dans la matrice
                  x = i+1;
                  y = j -1;
                  while( sortir != 1 && dans_matrice(x,y)==1){
                    x++;
                    y--;
                    nb_pions_pris++;
                    if(othellier[x][y]==0 && dans_matrice(x,y)==1){

                        for(indice = 0; indice<nb_choix ; indice++){ 
                            if((TabX[indice]==x) && (TabY[indice]==y)){
                                deja_present = 1;
                            }
                        }

                        if(deja_present == 0){ 
                            printf("Choix %d : PosX = %d et PosY = %d || Pions pris = %d\n",nb_choix+1,x,y,nb_pions_pris);
                            TabX[nb_choix]=x;
                            TabY[nb_choix]=y;
                            nb_choix++;
                        }
                        deja_present=0;
                        sortir=1;
                    }else if(othellier[x][y]==c_pion)
                      sortir=1;
                  }
                }
                nb_pions_pris=0;
                sortir=0;
             }
           }
        }
        choix_coup(othellier,pion_1,TabX,TabY,nb_choix);
}


/**
  *\fn void choix_coup(int othellier[N][N],pion* pion_1,int TabX[],int TabY[],int nb_coup)
  *\brief Choix du coup du joueur (fonction utilisée dans la fonction affichage_coup)
  *\param othellier Matrice du jeu
  *\param pion_1 Pion qui vient d'être joué
  *\param TabX[] Tableau des coordonnées x des choix possibles
  *\param TabY[] Tableau des coordonnées y des choix possibles
  *\param nb_coup Nombre de coups possibles pour le tour en cours
  */
void choix_coup(int othellier[N][N],pion* pion_1,int TabX[],int TabY[],int nb_coup){ //Choix du coup effectué par le joueur

  int choix=0;

  do{
    printf("Choississez le numéro du coup à jouer :");
    scanf("%d",&choix);

    if(choix<1 || choix>nb_coup)
      printf("Veuillez choisir un bon numéro \n");
  }while(choix<1 || choix>nb_coup);

  choix -= 1;
  pion_1->PosX=TabX[choix];
  pion_1->PosY=TabY[choix];
  
}


/**
  *\fn void retourne(int othellier[N][N],joueur* X, pion* pion_1)
  *\brief Retourne les pions nécéssaires après le choix d'un coup par un joueur
  *\param othellier Matrice du jeu
  *\param pion_1 Pion qui vient d'être joué
  *\param X Joueur en train de joueur
  */
void retourne(int othellier[N][N],joueur* X, pion* pion_1){
// Cette fonction parcours les pions et grâce a la pos du dernier pion posé,
// elle met à jour la matrice en retournant les pions si nécéssaires.
  int x=pion_1->PosX;  //coordonnée X du dernier pion placé
  int y=pion_1->PosY;  //coordonnée Y du dernier pion placé
  int i;
  int j;

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
  j=y-1;

  while(dans_matrice(x,j) && othellier[x][j]==c_pion_adv){ //on attend de recontrer un pion adverse
    j--;
  }
  if(dans_matrice(x,j) && othellier[x][j]==c_pion){  //si le pion est adverse, on vérifie la case suivante
    j=y-1;

    while(othellier[x][j]==c_pion_adv){ // on retourne les pions adverses pour les gagner
      othellier[x][j]=c_pion;
      j--;
    }
  }

  //Vers la droite
  j=y+1;

  while(dans_matrice(x,j) && othellier[x][j]==c_pion_adv){ 
     j++;
  }
  if(dans_matrice(x,j) && othellier[x][j]==c_pion){  
    j=y+1;

    while(othellier[x][j]==c_pion_adv){ 
      othellier[x][j]=c_pion;
      j++;
    }
  }

  //Vers le haut
  i=x-1;

  while(dans_matrice(i,y) && othellier[i][y]==c_pion_adv){ 
     i--;
   }
  if(dans_matrice(i,y) && othellier[i][y]==c_pion){  
    i=x-1;

    while(othellier[i][y]==c_pion_adv){ 
      othellier[i][y]=c_pion;
      i--;
    }
  }

  //Vers le bas
  i=x+1;

  while(dans_matrice(i,y) && othellier[i][y]==c_pion_adv){ 
     i++;
  }
  if(dans_matrice(i,y) && othellier[i][y]==c_pion){  
    i=x+1;

    while(othellier[i][y]==c_pion_adv){ 
      othellier[i][y]=c_pion;
      i++;
    }
  }

  //Diagonale haut gauche
  i=x-1;
  j=y-1;

  while(dans_matrice(i,j) && othellier[i][j]==c_pion_adv){
    i--;
    j--;
  }
  if(dans_matrice(i,j) && othellier[i][j]==c_pion){ 
    i=x-1;
    j=y-1;

    while(othellier[i][j]==c_pion_adv){ 
      othellier[i][j]=c_pion;
      i--;
      j--;
    }
  }

  //Diagonale haut droite
  i=x-1;
  j=y+1;

  while(dans_matrice(i,j) && othellier[i][j]==c_pion_adv){
    i--;
    j++;
  }
  if(dans_matrice(i,j) && othellier[i][j]==c_pion){ 
    i=x-1;
    j=y+1;

    while(othellier[i][j]==c_pion_adv){ 
      othellier[i][j]=c_pion;
      i--;
      j++;
    }
  }
  //Diagonale bas gauche
  i=x+1;
  j=y-1;

  while(dans_matrice(i,j) && othellier[i][j]==c_pion_adv){
    i++;
    j--;
  }
  if(dans_matrice(i,j) && othellier[i][j]==c_pion){ 
    i=x+1;
    j=y-1;

    while(othellier[i][j]==c_pion_adv){ 
      othellier[i][j]=c_pion;
      i++;
      j--;
    }
  }

  //Diagonale bas droite
  i=x+1;
  j=y+1;

  while(dans_matrice(i,j) && othellier[i][j]==c_pion_adv){
    i++;
    j++;
  }
  if(dans_matrice(i,j) && othellier[i][j]==c_pion){  
    i=x+1;
    j=y+1;

    while(othellier[i][j]==c_pion_adv){ 
      othellier[i][j]=c_pion;
      i++;
      j++;
    }
  }
}


/**
  *\fn void MAJ_othellier(int othellier[N][N], pion* pion_1,joueur* X)
  *\brief Mise à jour del'othellier en positionant le dernier pion joué et en exécutant la fonction "retourne"
  *\param othellier Matrice du jeu
  *\param pion_1 Pion qui vient d'être joué
  *\param X Joueur en train de joueur
  */
void MAJ_othellier(int othellier[N][N], pion* pion_1,joueur* X){
    othellier[pion_1->PosX][pion_1->PosY]=X->couleur_j;
    retourne(othellier,X, pion_1);
}


/**
  *\fn int peux_jouer(int othellier[N][N], joueur *X)
  *\brief Permet de savoir si un joueur peut jouer un coup et s'il ne peut pas la partie se finie
  *\param othellier Matrice du jeu
  *\param X Joueur en train de joueur
  *\return Un entier correspondant au nombre de choix du joueur
  */
int peux_jouer(int othellier[N][N], joueur *X){
    int nb_choix =0;
    int i, j;
    int x, y;
    int sortir=0;
    int c_pion, c_pion_adv; //couleur du pion du joueur et celle de son adversaire.

    if(X->couleur_j==2){ //si le joueur a les pions noir
      c_pion = 2; //noir est repertorié comme étant égal à 1 sur l'othellier
      c_pion_adv = 1; // blanc comme étant égal à 2
    }else{
      c_pion = 1;
      c_pion_adv = 2;
    }

    for(i = 0; i<N ; i++){
        for( j=0; j<N ; j++){
           if(othellier[i][j]==c_pion){


             if(othellier[i+1][j]==c_pion_adv && dans_matrice(i+1,j)==1){ //bas et dans la matrice
                x = i+1; //x prend les coordonées de la case en cours dont on sait quelle est blanche
                y = j;

                while( sortir != 1 && dans_matrice(x,y)==1){
                  x++;
                  if(othellier[x][y]==0 && dans_matrice(x,y)==1){
                    nb_choix++;
                    sortir=1;
                  }else if(othellier[x][y]==c_pion)
                    sortir=1;
                }
              }
              sortir=0;
              if(othellier[i+1][j+1]==c_pion_adv && dans_matrice(i+1,j+1)==1){ //diagonale bas droite
                x = i+1; 
                y = j+1;

                while( sortir != 1 && dans_matrice(x,y)==1){
                  x++;
                  y++;
                  if(othellier[x][y]==0 && dans_matrice(x,y)==1){
                    nb_choix++;
                    sortir=1;
                  }else if(othellier[x][y]==c_pion)
                    sortir=1;
                }
              }

              sortir=0;
              if(othellier[i][j+1]==c_pion_adv && dans_matrice(i,j+1)==1){ // droite et dans la matrice
                x = i;
                y = j+1;

                while( sortir != 1 && dans_matrice(x,y)==1){
                  y++;
                  if(othellier[x][y]==0 && dans_matrice(x,y)==1){
                    nb_choix++;
                    sortir=1;
                  }else if(othellier[x][y]==c_pion)
                    sortir=1;
                }
              }
              sortir=0;

              if(othellier[i-1][j+1]==c_pion_adv && dans_matrice(i-1,j+1)==1){ //diagonale haut droite et dans la matrice
                x = i-1;
                y = j+1;

                while( sortir != 1 && dans_matrice(x,y)==1){
                  x--;
                  y++;
                  if(othellier[x][y]==0 && dans_matrice(x,y)==1){
                    nb_choix++;
                    sortir=1;
                  }else if(othellier[x][y]==c_pion)
                    sortir=1;
                }
              }
              sortir=0;
              if(othellier[i-1][j]==c_pion_adv && dans_matrice(i-1,j)==1){ //haut et dans la matrice
                x = i-1;
                y = j;

                while( sortir != 1 && dans_matrice(x,y)==1){
                  x--;
                  if(othellier[x][y]==0 && dans_matrice(x,y)==1){
                    nb_choix++;
                    sortir=1;
                  }else if(othellier[x][y]==c_pion)
                    sortir=1;
                }
              }
              sortir=0;
              if(othellier[i-1][j-1]==c_pion_adv && dans_matrice(i-1,j-1)==1){ //diagonale haut gauche et dans la matrice
                x = i-1;
                y = j-1;

                while( sortir != 1 && dans_matrice(x,y)==1){
                  x--;
                  y--;
                  if(othellier[x][y]==0 && dans_matrice(x,y)==1){
                    nb_choix++;
                    sortir=1;
                  }else if(othellier[x][y]==c_pion)
                    sortir=1;
                }
              }
              sortir=0;
              if(othellier[i][j-1]==c_pion_adv && dans_matrice(i,j-1)==1){ //gauche et dans la matrice
                x = i;
                y = j-1;

               while( sortir != 1 && dans_matrice(x,y)==1){
                  y--;
                  if(othellier[x][y]==0 && dans_matrice(x,y)==1){
                    nb_choix++;
                    sortir=1;
                  }else if(othellier[x][y]==c_pion)
                    sortir=1;
                }
              }
              sortir=0;
              if(othellier[i+1][j-1]==c_pion_adv && dans_matrice(i+1,j-1)==1){ //diagonale bas gauche et dans la matrice
                x = i+1;
                y = j -1;

                while( sortir != 1 && dans_matrice(x,y)==1){
                  x++;
                  y--;
                  if(othellier[x][y]==0 && dans_matrice(x,y)==1){
                    nb_choix++;
                    sortir=1;
                  }else if(othellier[x][y]==c_pion)
                    sortir=1;
                }
              }
              sortir=0;
           }
         }
      }
  return nb_choix;
}


/**
  *\fn void compte_pion(int othellier[N][N], joueur* A, joueur* B)
  *\brief Compte le nombre de pions restants de chaque joueurs
  *\param othellier Matrice du jeu
  *\param A, B Joueur A et B
  */
void compte_pion(int othellier[N][N], joueur* A, joueur* B){ //compte le nombre de pions de chaque joueurs
  int i, j;
  A->nb_pions = 0;
  B->nb_pions = 0;
  for(i=0; i<N; i++){
    for(j=0; j<N; j++){
      if(A->couleur_j==1){ // si le joueur A possede les pions blancs
        if(othellier[i][j]==1)
          A->nb_pions++;
        else if(othellier[i][j]==2)
          B->nb_pions++;
      }
      if(A->couleur_j==2){ // si le joueur A possede les pions noirs
        if(othellier[i][j]==2)
          A->nb_pions++;
        else if(othellier[i][j]==1)
          B->nb_pions++;
      }
    }
  }
}


/**
  *\fn void affiche_nb_pions(joueur* A, joueur* B)
  *\brief Affiche le nombre de pions restants pour les deux joueurs
  *\param A, B Joueur A et B
  */
void affiche_nb_pions(joueur* A, joueur* B){
    printf("\n \n /******* TOTAL DES POINTS *******/ :\n \n");
    printf(" %s à %d pions \n",A->pseudo,A->nb_pions);
    printf(" %s à %d pions \n",B->pseudo,B->nb_pions);
  }