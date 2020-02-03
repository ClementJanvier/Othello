include <stdio.h>
#include <stdlib.h>

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
			printf("Votre choix [1-3] ? ");
			scanf("%d",&rep);
			if (rep < 1 || rep > 3) 
				printf("Votre choix doit etre compris entre 1 et 3\n");
		}
		while (rep < 1 || rep > 3);
		
		
		// Traitement du choix de l'utilisateur
		switch (rep){
			case 1: {
        printf("Le jeu va démarrer");
        
        
        
        
        
        
        
        
        break;
      }
			case 2: 
			case 3 : {
				printf("Merci d'avoir joué à notre jeu !\n"); 
				break;
			}
		}

		if(debog)
			afficher_table();
	}
	while (rep != 3);

	return EXIT_SUCCESS;
}
