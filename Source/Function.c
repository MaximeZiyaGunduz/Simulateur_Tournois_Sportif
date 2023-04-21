/**
 * @file : Function.c
 * @author : GUNDUZ Maxime
 * @date : 2023
 * @brief : Contient les fonctions necessaire au tournois.
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#include "Function.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/**
 * @brief si un entier est une puissance de 2.
 * @param n l'entier à vérifier
 * @return true si n est une puissance de 2, false sinon
 */

bool estPuissanceDe2(int n)
{
    if (n <= 0)
    {
        return false;
    }
    while (n > 1)
    {
        if (n % 2 != 0)
        {
            return false;
        }
        n /= 2;
    }
    return true;
}

/**
 * @brief Compte le nombre de lignes dans un fichier donné.
 * @param fileteams le nom du fichier à lire
 * @return le nombre de lignes dans le fichier, ou 0 si le fichier n'a pas pu être ouvert.
 */

int cpt_line(const char *fileteams)
{
    FILE *file;
    char line[256];
    int nbr_line = 0;

    // Ouverture fichier en argument
    file = fopen(fileteams, "r");

    if (file == NULL)
    {
        printf("Le fichier n'a pas pu etre ouvert");
        return 0;
    }

    // Parcourir tout le fichier
    while (fgets(line, sizeof(line), file))
    {
        nbr_line++;
    }
    fclose(file);

    return nbr_line;
}

/**
 * @brief Lit un fichier contenant des équipes et retourne un tableau de chaînes de caractères contenant les noms des équipes.
 * @param fileteams le nom du fichier à lire
 * @param nbr_line un pointeur vers un entier qui contiendra le nombre de lignes du fichier
 * @return un tableau de chaînes de caractères contenant les noms des équipes, ou NULL si une erreur s'est produite.
 */

char **readFile(const char *fileteams, int *nbr_line)
{
    FILE *file;
    char line[256];
    char **teams = NULL;
    int i = 0;
    *nbr_line = cpt_line(fileteams);

    // Vérification
    if (*nbr_line == 0)
    {
        printf("Le fichier est vide");
        return NULL;
    }
    if (!estPuissanceDe2(*nbr_line))
    {
        printf("\nLe nombre de lignes n'est pas une puissance de 2");
        return NULL;
    }
    if (*nbr_line > 1024)
    {
        printf("\nLe nombre d'équipes ne peut pas dépasser 1024.");
        return NULL;
    }
    printf("\nVous avez %d equipes", *nbr_line);

    // Ouverture fichier
    file = fopen(fileteams, "r");
    if (file == NULL)
    {
        printf("Le fichier n'a pas pu etre ouvert");
        return NULL;
    }

    // Allocation tableau qui va contenir tout les équipes
    teams = malloc(*nbr_line * sizeof(char *));
    if (teams == NULL)
    {
        printf("Erreur d'allocation memoire");
        fclose(file);
        return NULL;
    }
    // Ajouter tout les équipes au tableau
    while (fgets(line, sizeof(line), file))
    {
        teams[i] = malloc((strlen(line) + 1) * sizeof(char));
        if (teams[i] == NULL)
        {
            printf("Erreur d'allocation memoire");
            fclose(file);
            for (int j = 0; j < i; j++)
            {
                free(teams[j]);
            }
            free(teams);
            return NULL;
        }
        strcpy(teams[i], line);
        i++;
    }
    fclose(file);

    return teams;
}

/**
 * @brief Vérifie le nombre d'arguments passés en arguments.
 * @param argc le nombre d'arguments passés au programme
 * @return le nombre d'arguments passés au programme, ou une erreur si plus d'un argument est passé.
 */

int checkArgs(int argc)
{
    int nbArg = argc - 1;

    if (nbArg >= 2)
    {
        printf("Erreur : vous avez fourni plus d'un argument. Veuillez fournir un seul argument.\n");
        exit(EXIT_FAILURE);
    }
    return nbArg;
}

/**
 * @brief Mélange un tableau d'équipes.
 * @param eq le tableau d'équipes à mélanger
 * @param nbr_line le nombre d'équipes dans le tableau
 */

void melange(Equipe *eq, int nbr_line)
{
    srand(time(NULL));

    for (int i = 0; i < nbr_line; i++)
    {
        int j = rand() % nbr_line;
        Equipe tmp = eq[i];
        eq[i] = eq[j];
        eq[j] = tmp;
    }
}

/**
 * @brief Vérifie si le fichier de résultats existe et le supprime s'il existe.
 */

void Verif_Result_File(void)
{
    char *f = "resultatT.txt";
    FILE *file = fopen(f, "r");
    if (file != NULL)
    {
        fclose(file);
        remove(f);
    }
    file = fopen(f, "w");
    if (file == NULL)
    {
        printf("Erreur: impossible de créer le fichier %s\n", f);
        exit(EXIT_FAILURE);
    }
    fclose(file);
}

/**
 * @brief Écrit un message dans le fichier "resultatT.txt" et l'affiche sur la console.
 * @param msg le message à écrire et afficher
 */

void WriteResult(const char *msg)
{
    // Ouvre fichier "resultatT.txt"
    FILE *file = fopen("resultatT.txt", "a");
    if (file == NULL)
    {
        printf("Erreur : impossible d'ouvrir le fichier resultatT.txt\n");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s", msg);
    fclose(file);
    printf("%s", msg);
}

/**
 * @brief Génère un score aléatoire entre 0 et 100.
 * @return le score généré
 */

int random_score()
{
    int score = rand() % 101;
    return score;
}

/**
 * @brief Joue un match entre deux équipes, met à jour leurs scores et écrit le résultat dans le fichier "resultatT.txt".
 * @param eq1 la première équipe
 * @param eq2 la deuxième équipe
 */

void JouerMatchs(Equipe *eq1, Equipe *eq2)
{
    int score1 = 0, score2 = 0;
    int i = 0;

    // Jeu
    while (i < 3)
    {
        score1 += random_score();
        score2 += random_score();
        i++;
    }
    // Vérification  si les 2 équipe on le meme score
    while (score1 == score2)
    {
        score1 += random_score();
        score2 += random_score();
    }

    pthread_mutex_lock(&mutex);

    // Vérification qui a gagner
    if (score1 > score2)
    {
        eq1->score += 1;
    }
    else
    {
        eq2->score += 1;
    }
    pthread_mutex_unlock(&mutex);
}

/**
 * @brief Joue un match entre deux équipes et écrit le résultat dans le fichier "resultatT.txt".
 * @param arg un pointeur vers une structure Match contenant les deux équipes et le numéro de round
 */

void *JouerUnMatch(void *arg)
{
    Match *match = (Match *)arg;

    // Réalise le jeu
    JouerMatchs(match->eq1, match->eq2);

    char result[2048];
    char *vainqueur;

    // Determiner le vainqueur du match
    if (match->eq1->score > match->eq2->score)
    {
        vainqueur = match->eq1->nom;
    }
    else
    {
        vainqueur = match->eq2->nom;
    }

    // Ecrire dans le fichier resultatT.txt
    sprintf(result, "Round %d - Match entre %s et %s: %d - %d, Vainqueur : %s",
            match->round, match->eq1->nom, match->eq2->nom, match->eq1->score, match->eq2->score, vainqueur);
    WriteResult(result);
    pthread_exit(NULL);
}