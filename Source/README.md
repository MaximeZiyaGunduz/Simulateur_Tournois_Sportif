- Nom : README.md
- Auteur : GUNDUZ Maxime
- Année : 2023
- Description : Information sur le projet

############### Guide de l’utilisateur: ###############

Description du programme:


Le programme réalisé en C a pour objectif de simuler un tournoi sportif dont les équipes peuvent être choisies par l’utilisateur (un nombre d'équipes en puissance de 2). Ici, le sport sélectionné a été le tir à l'arc entre 2 équipes sur une cible.

Les équipes lancent 3 fois une flèche sur une cible et remportent des points entre 0 et 100. Si le match est nul, alors le match continue. Ceci est fait pour tous les matchs du tournoi.

Les matchs durant un tournoi sont réalisés simultanément à l'aide de threads. 

À la fin du tournoi, le vainqueur est affiché.Une fois l'exécution terminée, vous pourrez retrouver l'historique du tournoi dans un fichier créé par le programme nommé “resultat.txt”.

Exécution du programme : 

Pour exécuter le programme, des prérequis sont nécessaire qui sont les suivante : 

	- Être sur un système Linux (ou WSL pour Windows).
- Avoir le compilateur gcc 
  sinon non l’installer avec la commande : “sudo apt install gcc”
- Avoir l’outil “make” sinon non l’installer avec la commande : “sudo apt install make”
- Avoir l’outil “doxygen” sinon non l’installer avec la commande : “sudo apt install doxygen”

Comment exécuter le programme ?


Veuillez télécharger le projet.
-Veuillez ouvrir un terminal et vous placer à l'emplacement dans lequel se trouve le projet.
Veuillez faire la commande “make” 
Veuillez donné le droit à l'exécution au fichier “SystemTournois” (chmod u+x SystemTournois)

Si vous souhaitez exécuter le programme sans arguments, une liste d'équipes sera prise par défaut. Pour exécuter le programme sans argument faite la commande “make run”

Si vous souhaitez exécuter avec votre propre équipe, veuillez créer un fichier texte avec la commande “touch nom_du_fichier.txt”, puis faire la commande “nano nom_du_fichier.txt”. De la vous pouvez créer votre fichier d’équipe (chaque équipe sur une ligne, le nombre d’équipe doit être une puissance de 2 et ne doit pas dépasser 1024). Une fois cela fait, pour exécuter avec votre équipe faite “make run USER_ARGS=equipe.txt” (Si vous mettez plusieurs arguments, le programme vous met une erreur avec un message (“make run USER_ARGS=equipe.txt default.txt”)).

Si vous ne souhaitez pas utiliser le Makefile, vous pouvez faire la commande: “gcc main.c Function.c -pthread” puis faire ‘./a.out” pour exécuter le programme, vous pouvez accompagner la commande d’argument comme par exemple “./a.out equipe.txt ”.

Création d’un document doxygen : 

Un document doxygen et une documentation du projet sous format HTML.

Pour créer un document doxygen, placez vous à l'emplacement du projet, de la vous devez écrire sur un terminal les 2 commande suivantes:

- “doxygen -g Doxyfile”
- “make doc”

Une fois les 2 commandes tapées, un répertoire nommé “html” sera créé. Allez dans ce répertoire “html” et executer le fichier “globals.html” avec votre navigateur internet.

Commande Makefile :  

-”make all” (ou make) construira l'exécutable “SystemTournois” à partir des fichiers source.

-”make run” exécutera le programme “SystemTournois” avec les arguments par défaut ou spécifiés par l’utilisateur.

-”make doc” : Permet de générer la documentation du projet avec doxygen. Veuillez exécuter la commande “doxygen -g Doxyfile” avant “make doc”.

-”make clean” supprimera les fichiers objets générés lors de la compilation.

-”make mrproper” supprimera les fichiers objets, le fichier “resultatT.txt”, l’exécutable, et tous les document lié à doxygen.

############### Guide du développeur: ###############

Les Structures:

Le programme réalisé utilise 2 structure que sont les suivantes : 

-Une Structure Équipe qui permet de représenter une équipes dans le tournois, elle est caractérisé par : 

- nom : chaîne de caractères représentant le nom de l'équipe.
- score : Entier qui représente le score de l'équipe.
- continuePlaying : Booléen qui permet de savoir si l’équipe peut continuer à faire des matchs dans les prochains tours.

-Une structure Match qui permet de représenter un match entre deux équipes, elle est caractérisé par :

-eq1 : Pointeur vers la première équipe
-eq2 : Pointeur vers la deuxième équipe
-round : Entier indiquant le tour dans lequel le match est joué

Les Fonctions

Le programme réalisé nécessite l’utilise des fonctions suivantes :

- readFile:

Prend en entrée le nom d'un fichier texte contenant les équipes et renvoie un tableau de chaînes de caractères qui contient les noms d’équipes. Elle utilise la fonction malloc pour allouer de la mémoire pour le tableau.

- melange:

Prend en entrée un tableau d'équipes et un entier qui représente  le nombre d'équipes. La fonction rand pour générer des nombres aléatoires est utilisée pour réaliser un mélange.

- JouerUnMatch:

Prend en entrée un pointeur vers une structure Match et permet de réaliser un match. Cette fonction nécessite l’utilisation d’un mutex pour synchroniser l'accès aux équipes pendant un match.

- estPuissanceDe2:

Prend en entrée un entier et renvoie un booléen indiquant si l'entier est une puissance de 2.

- checkArgs:

Prend en entrée le nombre d'arguments passés au programme et renvoie un entier représentant le nombre d'arguments passés en paramètres.

- Verif_Result_File:

Elle vérifie si le fichier “resultatT.txt” existe. Si ce fichier n'existe pas, alors elle est crée.

- WriteResult:
Prends en entrée un texte et écris ce texte dans le fichier “resultatT.txt”. La fonction utilise un mutex pour synchroniser l'accès au fichier.

Fonctionnalité futur à ajouter:

Améliorer l’affichage des résultats
Permettre à l'utilisateur d’intervenir durant les matchs en sélectionnant un vainqueur de match
Ajouter une interface graphique


