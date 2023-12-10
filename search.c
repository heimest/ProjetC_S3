//
// Created by alexa on 18/11/2023.
//

#include "search.h"

int classicSearch(t_d_list *list, int value){
    t_d_cell *current = list->heads[0];
    while (current != NULL){
        if (current->value == value){
            return 1;
        } else{
            current = current->nexts[0];
        }
    }
    return -1;
}

int levelSearch(t_d_list *list, int value){
    if (list == NULL || list->heads == NULL) {
        return -1;
    }

    t_d_cell *current = list->heads[list->nbLevels - 1];
    t_d_cell *prev = current;

    for (int i=list->nbLevels - 1; i>=0; i--) {
        while (current->nexts[i] != NULL && current->value < value) {
            prev = current;
            current = current->nexts[i];
        }

        if (current != NULL && current->value == value) {
            return current->value;
        }

        if (i > 0 && current != NULL) {
            if (!(current->nexts[i] == NULL && current->value == value)) {
                if (current == prev) {
                    current = list->heads[i - 1];
                    prev = current;
                } else {
                    current = prev;
                }
            }
        }
    }

    return -1;
}


int dichotomicSearch(t_d_list *list, int value){
    int level = list->nbLevels-1;
    t_d_cell *current = list->heads[level];
    t_d_cell *prev = NULL;
    t_d_cell *next = current->nexts[level];
    while (level >= 0){
        int state = 0;
        current = list->heads[level];
        prev = NULL;
        if (current != NULL){
            next = current->nexts[level];
        }
        while (current != NULL && state == 0 && current->value <= value) {
            if (current->value == value) {
                state = 1;
            } else {
                prev = current;
                current = next;
                if (current == NULL) {
                    next = NULL;
                } else {
                    next = current->nexts[level];
                }
            }
        }
        if (state == 1){
            return 1;
        }else{
            level--;
        }
    }
    return -1;
}