//
// Created by alexa on 23/10/2023.
//

#ifndef PROJETC2_LIST_H
#define PROJETC2_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include "cell.h"

typedef struct s_d_list
{
    int nbLevels;
    t_d_cell ** heads;
} t_d_list;

t_d_list *createList(int nb_heads);
t_d_list *createHalfList(int nbLevels);

int addCellToHead(t_d_cell *cell, t_d_list *list);
void insertCell(t_d_list *list, t_d_cell *cell);

void displayLevelList(t_d_list *list,int level);
void displayList(t_d_list *list);


#endif //PROJETC2_LIST_H
