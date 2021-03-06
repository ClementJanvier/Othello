/**
  *\file main.c
  *\author: Martin JOUFFLINEAU, Achraf LAGCHOUR, Clément JANVIER et Thomas JAVELLE
  *\version 1.0
  *\date 2020
  */

#include <stdio.h>
#include <stdlib.h>
#include "library.h"

/**
  *\fn int main()
  *\return EXIT_SUCCESS Permet de avoir le bon fonctionnement du programme
*/
int main(){

  int rep;

  do{
		  affichage_menu();

	  // Lecture et verification du choix de l'utilisateur
		  do{
			  printf("Votre choix [1-2] ? ");
			  scanf("%d",&rep);
			  if (rep < 1 || rep > 2){
				  printf("Votre choix doit etre compris entre 1 et 2\n");
        }
		  }while (rep < 1 || rep > 2);


		  // Traitement du choix de l'utilisateur
		  switch (rep){
			  case 1: printf("\n \n /******* LE JEU VA DEMARRER *******/ \n \n");jeu(); break;

			  case 2 : printf("Merci d'avoir joué à notre jeu !\n"); //Le joueur décide de quitter le jeu
			  break;
			}


		
	}
	while (rep != 2);

	return EXIT_SUCCESS;

}
