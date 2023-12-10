//
// Created by alexa on 06/12/2023.
//

#ifndef PROJETC2_AGENDA_H
#define PROJETC2_AGENDA_H

#endif //PROJETC2_AGENDA_H

#include <stdlib.h>
#include <stdio.h>
#include "list.h"

typedef struct contact{
    char* name;
    char* surname;
} contact;

typedef struct rdv{
    int date[3];
    int hour[2];
    int duration[2];
    char* purpose;
} rdv;

typedef struct agenda{
    contact ctt;
    int nbRdvs;
    rdv *aps;
    struct agenda **nexts;
} agenda;

typedef struct directory{
    agenda **heads;
    int nbElements;
} directory;

int compareNames(const char* name1, const char* name2);
char* strToLower(const char* str);

agenda **automaticCompletion(directory* list, char* name, int* nbList);
agenda *contactSearch(directory* list);

void contactRdvs(agenda *ctt);

int insertionDirectory(directory* dr, agenda* agd);

agenda *createContact(directory* dr);
void createAppointment(directory* dr);