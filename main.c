#include <stdio.h>
#include <stdlib.h>
#include "library.h"

/**
*\file main.c
*\author Martin Thomas Clément Achraf
*\version 1.0
*\date 03/02/2020
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
				  printf("Votre choix doit etre compris entre 1 et 3\n");
        }
		  }while (rep < 1 || rep > 2);


		  // Traitement du choix de l'utilisateur
		  switch (rep){
			  case 1: printf("\n \n /******* LE JEU VA DEMARRER *******/ \n \n");jeu(); break;

			  case 2 : printf("Merci d'avoir joué à notre jeu !\n"); //Le joueur décide de quitter le jeu
			  break;
			}


		//if(debog)
		//	afficher_table();
	}
	while (rep != 2);

	return EXIT_SUCCESS;

}
