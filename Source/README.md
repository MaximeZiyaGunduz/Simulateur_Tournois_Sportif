# Simulation d'un tournoi sportif de tir à l'arc en C

Ce projet a pour but de simuler un tournoi sportif de tir à l'arc entre des équipes choisies par l'utilisateur. Les équipes lancent 3 flèches sur une cible pour marquer des points. Les matchs se jouent simultanément à l'aide de threads et de mutex, jusqu'à ce qu'un vainqueur soit déterminé.

## Technologies utilisées

Ce projet a été réalisé en langage C, en utilisant les bibliothèques standard et la bibliothèque pthread. Il utilise également le logiciel Doxygen pour la documentation et le logiciel Make pour la compilation.

## Fonctionnalités

Le programme peut être exécuté avec les équipes par défaut ou avec un fichier texte contenant les équipes spécifiées par l'utilisateur. Le programme utilise deux structures : Équipe et Match, et nécessite l'utilisation de la fonction readFile pour lire un fichier texte contenant les équipes. Le programme affiche le déroulement du tournoi et le nom de l'équipe gagnante.

## Comment exécuter

Le programme nécessite d'être dans un système Linux ou Windows avec WSL (Windows Subsystem for Linux) pour pouvoir utiliser les commandes Makefile. Le programme peut être compilé et exécuté à l'aide des commandes Makefile suivantes :

- `make` : construit l'exécutable `tournoi`
- `make run` : exécute le programme avec les équipes par défaut
- `make run FILE=<nom du fichier>` : exécute le programme avec le fichier texte contenant les équipes
- `make doc` : génère la documentation Doxygen dans le dossier `doc`
- `make clean` : supprime les fichiers objets et les fichiers liés à Doxygen
