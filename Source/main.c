/**
 * @file : main.c
 * @author : GUNDUZ Maxime
 * @date : 2023
 * @brief : Execute le tournois
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#include "Function.h"

/**
* @brief Fonction principale qui exécute un tournoi de tir a l'arc.
* Cette fonction lit les équipes à partir d'un fichier texte.
* Réalise un tournoi en utilisant des threads pour gérer les matchs.
* Détermine le vainqueur du tournoi.
* Les résultats du tournoi sont enregistrés dans un fichier "resultatT.txt".
* @param argc Nombre d'arguments passés à la fonction.
* @param argv Tableau des arguments passés à la fonction.
* @return 0 si le programme s'exécute avec succès, 1 si une erreur se produit.
*/

int main(int argc, char *argv[])
{
    // Vérifier si resultatT.txt existe
    Verif_Result_File();

    // Déclaration variable
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    char **teams;
    int nbr_line;
    int round = 1;
    int nbArg = checkArgs(argc);

    // Vérification nombre d'argument
    if (nbArg == 0)
    {
        printf("Vous n'avez pas mis d'argument, une equipe par defaut vous seras attribuer\n");
        teams = readFile("default.txt", &nbr_line);
        if (!estPuissanceDe2(nbr_line))
        {
            printf("Le fichier présent de dispose pas d'un nombre d'équipe de puissance de 2.\nTournois Impossible a réalisé.\n");
        }
    }
    else
    {
        teams = readFile(argv[1], &nbr_line);
        if (!estPuissanceDe2(nbr_line))
        {
            printf("Le fichier présent de dispose pas d'un nombre d'équipe de puissance de 2.\nTournois Impossible a réalisé.\n");
        }
    }

    if (teams == NULL)
    {
        return 1;
    }

    // Créer un tableau d'équipes
    Equipe *equipes = malloc(nbr_line * sizeof(Equipe));

    // Remplir le tableau d'équipes avec les noms des équipes
    for (int i = 0; i < nbr_line; i++)
    {
        equipes[i].nom = teams[i];
        equipes[i].score = 0;
        equipes[i].continuePlaying = true;
    }

    // Mélanger les équipes
    melange(equipes, nbr_line);

    printf("\nLes informations du tounois ont etais generer dans le fichier texte resultatT.txt\n");

    // Tournois
    int nbMatchs = nbr_line / 2;

    pthread_t *threads = malloc(nbMatchs * sizeof(pthread_t));
    Match *matches = malloc(nbMatchs * sizeof(Match));

    while (nbMatchs > 0)
    {
        printf("\nTour %d\n", round);
        for (int i = 0; i < nbMatchs; i++)
        {
            // Determiner les équipes qui peuvent réaliser un match
            int j = i * 2;
            while (j < nbr_line && !equipes[j].continuePlaying)
                j++;
            if (j == nbr_line)
                break;
            matches[i].eq1 = &equipes[j];
            j++;
            while (j < nbr_line && !equipes[j].continuePlaying)
                j++;
            if (j == nbr_line)
                break;
            matches[i].eq2 = &equipes[j];

            matches[i].round = round;

            pthread_create(&threads[i], NULL, JouerUnMatch, &matches[i]);
        }

        // Attendre la fin de tous les threads
        for (int i = 0; i < nbMatchs; i++)
        {
            pthread_join(threads[i], NULL);
        }

        // Actualiser les équipes qui ont perdu
        for (int i = 0; i < nbMatchs; i++)
        {
            Equipe *loser;
            if (matches[i].eq1->score > matches[i].eq2->score)
            {
                loser = matches[i].eq2;
            }
            else
            {
                loser = matches[i].eq1;
            }
            loser->continuePlaying = false;
        }

        nbMatchs /= 2;
        round++;
    }

    // Fin du tounois

    // Déterminer le vainqueur du tournoi
    Equipe *winner = NULL;
    for (int i = 0; i < nbr_line; i++)
    {
        if (equipes[i].continuePlaying)
        {
            if (winner == NULL || equipes[i].score > winner->score)
            {
                winner = &equipes[i];
            }
        }
    }

    // Afficher le vaiqueur du tournoi

    if (winner != NULL)
    {
        char Vainqueur[100];
        sprintf(Vainqueur, "\n############################\n Le gagnant du tournoi est %s avec un score de %d\n", winner->nom, winner->score);
        WriteResult(Vainqueur);
    }

    // Libérer les ressources
    for (int i = 0; i < nbr_line; i++)
    {
        free(equipes[i].nom);
    }
    free(equipes);
    free(teams);
    free(matches);

    // Détruire le mutex.
    pthread_mutex_destroy(&mutex);

    // Libérer la mémoire allouée pour les threads.
    free(threads);

    return 0;
}