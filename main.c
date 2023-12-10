//
// Created by alexa on 23/10/2023.
//
#include "cell.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "list.h"
#include "timer.h"
#include "search.h"
#include "agenda.h"

int main(){
    int choice = 0;
    printf("What part of the project do you want to test ?\n");
    scanf("%d", &choice);

    if (choice == 1) {
        t_d_list *list = createList(4);
        t_d_cell *newcell = createCell(5, 3);
        t_d_cell *newcell2 = createCell(4, 2);
        t_d_cell *newcell3 = createCell(3, 1);
        t_d_cell *newcell4 = createCell(2, 4);
        insertCell(list, newcell);
        insertCell(list, newcell2);
        insertCell(list, newcell3);
        insertCell(list, newcell4);
        printf("This is the entire list : \n");
        displayList(list);
        printf("This is the nexts 2 of the list : \n");
        displayLevelList(list, 2);
        return 0;
    }

    if (choice == 2) {
        srand(time(NULL));
        t_d_list *list;
        printf("How many levels do you want ?");
        int choice2 = 0;
        scanf("%d", &choice2);
        list = createHalfList(choice2);
        printf("How many research do you want to do ?");
        int choice3 = 0;
        scanf("%d", &choice3);
        startTimer();
        for (int i = 1; i <= choice3; i++) {
            int n = rand() % ((int) pow(2, choice2));
            if (n == 0) { n = 1; }
            int result = classicSearch(list, n);
            if (result != 1) {
                printf("Value not found !\n");
            }
        }
        stopTimer();
        printf("Temps pour la recherche classique : ");
        displayTime();
        startTimer();
        for (int i = 0; i <= choice3; i++) {
            int n = rand() % ((int) pow(2, choice2));
            if (n == 0) { n = 1; }
            int result = levelSearch(list, n);
            if (result != n) {
                printf("Value not found !\n");
            }
        }
        stopTimer();
        printf("Temps pour la recherche sur liste a niveaux : ");
        displayTime();
    }

    if (choice == -1) {
        srand(time(NULL));
        t_d_list *list = createHalfList(3);
        displayList(list);
        printf("\n");
        int n = rand() % ((int) pow(2, 3));
        printf("%d\n", n);
        printf("%d", levelSearch(list, n));
        return 0;
    }

    if (choice == 3){
    directory *dr = (directory*) malloc(sizeof(directory));
    if (!dr) {
        return 1;
    }
    dr->heads = (agenda**)malloc(4 * sizeof(agenda*));
    if (!dr->heads) {
        free(dr);
        return 1;
    }
    for (int i = 0; i < 4; i++) {
        dr->heads[i] = NULL;
    }
    dr->nbElements = 0;

    createContact(dr);
    if (dr->heads[0] && dr->heads[0]->ctt.surname) {
        printf("%s", dr->heads[0]->ctt.surname);
        printf("\n");
    } else {
        printf("Contact information is not available.\n");
    }

    createAppointment(dr);
    contactRdvs(dr->heads[0]);
    printf("Fini");
    }
}