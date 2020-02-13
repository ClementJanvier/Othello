# Othello
Projet L2 Informatique S4 - Othello

Projet S4 : Othello

Règles;
    Othello est un jeu de stratégie à deux joueurs : Noirs et Blanc. Il se joue sur un plateau unicolore de 64 cases, 8 sur 8, appelé othellier. Ces joueurs disposent de 64 pions bicolores, noirs d’un côté et blancs de l’autre. Par commodité, chaque joueur a devant lui 32 pions mais ils ne lui appartiennent pas et il doit en donner à son adversaire si celui-ci n’en a plus. Un pion est noir si sa face noir est visible et blanc si sa face blanche est visible.
    
But du Jeu :
    Avoir plus de pions de sa couleur que l’adversaire a la fin de la partie. Celle-ci s’achève lorsque aucun des joueurs ne peut plus jouer de coup légal. Cela intervient lorsque les 64 cases sont occupées.

Position de départ:
Au début de la partie, les deux pions noirs sont placés en e4 et d5 et les deux pions blancs en d4 et e5.
Les Noirs commencent toujours et les deux adversaires jouent ensuite à tour de rôle.

Pose d’un pion:
A son tour de jeu, le joueur doit poser un pion de sa couleur sur une case vide de l’othellier, adjacente à un pion adverse. Il doit également, en posant son pion, encadrer un ou plusieurs pions adverses entre le pion qu’il pose et un pion à sa couleur, déjà placé sur l’othellier. Cette prise en sandwich peut se faire aussi bien horizontalement que verticalement, qu’en diagonale. Le joueur retourne le ou les pions qu‘il vient d’encadrer, qui devient ainsi de sa couleur. Les pions ne sont ni retirés de l’othellier, ni déplacés d’une case à l’autre.

Organisation


-matrice de 8x8 ( case = 0 : case libre, case = 1 : case blanche, case = 2 : case noir)


Fonctions:
Fichier répertoire des fonctions matrices:
- création de la matrice et des pions au début du jeu
     - Initialisation de la matrice à 0
    - Mise en place de la configuration de départ
    - Mise à jour de la matrice 
Structure joueur:
Pseudo joueur
Couleur
nombre pions
nombre tour 
plus gros coup réalisé 
? Nombre de victoires/défaites/nuls
Structure pions:
Couleur pion
PosX
PosY

Fonction jeu contre ‘bot’( 2nde Partie)




FONCTIONS :

       
