//
// Created by alexa on 23/10/2023.
//

#include "cell.h"

t_d_cell* createCell(int value, int nbLevels){
    t_d_cell *newcell = (t_d_cell*) malloc(sizeof (t_d_cell));
    newcell->nbLevels = nbLevels;
    newcell->nexts = (t_d_cell**)malloc(nbLevels * sizeof(t_d_cell*));
    for (int i=0;i<nbLevels;i++){
        newcell->nexts[i] = NULL;
    }
    newcell->value = value;
    return newcell;
}