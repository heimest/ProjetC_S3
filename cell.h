//
// Created by alexa on 23/10/2023.
//

#ifndef PROJETC2_CELL_H
#define PROJETC2_CELL_H

#include <stdlib.h>
#include <stdio.h>

typedef struct s_d_cell
{
    int value;
    int nbLevels;
    struct s_d_cell ** nexts;
} t_d_cell;

t_d_cell* createCell(int value, int nb_level);

#endif //PROJETC2_CELL_H
