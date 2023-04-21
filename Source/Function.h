/**
 * @file : Function.h
 * @author : GUNDUZ Maxime
 * @date : 2023
 * @brief : Contient les structure nécessaire et les signature de fonction
 */

#ifndef FUNCTION_H_INCLUDED
#define FUNCTION_H_INCLUDED

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

// Contient les informations sur une équipe
typedef struct equipe
{
    char *nom;
    int score;
    bool continuePlaying;
} Equipe;

// Contient les informations sur les matchs
typedef struct match
{
    Equipe *eq1;
    Equipe *eq2;
    int round;
} Match;

// Signature de fonction
bool estPuissanceDe2(int n);
int cpt_line(const char *fileteams);
char **readFile(const char *fileteams, int *nbr_line);
int checkArgs(int argc);
void melange(Equipe *equipes, int nbr_line);
void Verif_Result_File(void);
void WriteResult(const char *message);
int random_score();
void JouerMatchs(Equipe *eq1, Equipe *eq2);
void *JouerUnMatch(void *arg);

#endif // FUNCTION_H_INCLUDED