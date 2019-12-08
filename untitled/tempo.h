#ifndef TEMPO_H
#define TEMPO_H

/*
    Biblioteca desenvolvida pelo aluno José Eduardo de Freitas Batista com o intuito de
    coletar a data e o tempo no instante em que o usuário realiza alguma ação.
*/

#include <QString>

#include <iostream>
#include <stdio.h>
#include <ctime>
#include <time.h>


int getempo(char x);

int getDia();
int getMes();
int getAno();

int getSegundo();
int getMinuto();
int getHora();

QString getData();
QString getTempo();

#endif




