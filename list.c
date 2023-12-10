//
// Created by alexa on 23/10/2023.
//

#include "list.h"
#include <stdio.h>
#include <math.h>

t_d_list *createList(int nb_heads){
    t_d_list *newlist = (t_d_list*) malloc(sizeof(t_d_list));
    newlist->nbLevels = nb_heads;
    newlist->heads = (t_d_cell **)malloc(nb_heads * sizeof(t_d_cell *));
    for (int i=0;i<nb_heads;i++){
        newlist->heads[i] = NULL;
    }

    return newlist;
}

t_d_list *createHalfList(int nbLevels){
    t_d_list  *newlist = (t_d_list*) malloc(sizeof(t_d_list));
    newlist->nbLevels = nbLevels;
    newlist->heads = (t_d_cell **) malloc(nbLevels * sizeof(t_d_cell*));
    for (int i=0;i<nbLevels;i++){
        newlist->heads[i] = NULL;
    }
    int n;
    t_d_cell *newcell;
    for (int i=1;i< pow(2,(double)nbLevels);i++){
        n=0;
        while(i%(int)pow(2,(double)n) == 0){n++;}
        newcell = createCell(i, n);
        insertCell(newlist, newcell);
    }
    return newlist;
}

int addCellToHead(t_d_cell *cell, t_d_list *list){
    if (cell->nbLevels > list->nbLevels){
        return 1;
    } else{
        t_d_cell *temp;
        for (int i=0;i<cell->nbLevels;i++){
            temp = list->heads[i];
            list->heads[i] = cell;
            cell->nexts[i] = temp;
        }
        return 0;
    }
}

void displayLevelList(t_d_list *list,int level){
    if(level>list->nbLevels-1){
        printf("error : nexts too high");
    }else{
        printf("[list head_%d @-] ", level);
        t_d_cell *current = list->heads[level];
        while (current != NULL){
            printf("-->[%d|@-] ", current->value);
            current = current->nexts[level];
        }
        printf("-->NULL");
    }
}

void displayList(t_d_list *list){
    for (int i=0;i<list->nbLevels;i++){
        printf("[list head_%d @-] ", i);
        t_d_cell *current = list->heads[i];
        while (current != NULL){
            printf("-->[%d|@-] ", current->value);
            current = current->nexts[i];
        }
        printf("-->NULL");
        printf("\n");
    }
}

void insertCell(t_d_list *list, t_d_cell *cell){
    if(cell->nbLevels<=list->nbLevels){
        if (list->heads[0] == NULL){
            addCellToHead(cell, list);
        }else{
            t_d_cell  *current = list->heads[0];
            t_d_cell *prev = NULL;
            t_d_cell *next = current->nexts[0];
            for (int i=0;i<cell->nbLevels;i++) {
                int state = 0;
                current = list->heads[i];
                prev = NULL;
                if (current != NULL){
                    next = current->nexts[i];
                }
                while (current != NULL && state == 0) {
                    if (current->value >= cell->value) {
                        state = 1;
                    } else {
                        prev = current;
                        current = next;
                        if (current == NULL) {
                            next = NULL;
                        } else {
                            next = current->nexts[i];
                        }
                    }
                }
                if (prev == NULL){
                    list->heads[i] = cell;
                    cell->nexts[i] = current;
                }else{
                    prev->nexts[i] = cell;
                    cell->nexts[i] = current;
                }
            }
            return;
        }

    }else{
        return;
    }
}
