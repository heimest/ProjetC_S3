//
// Created by alexa on 06/12/2023.
//

#include "agenda.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

char* strToLower(const char* str) {
    char* lowerStr = (char*)malloc(strlen(str) + 1);
    if (!lowerStr) return NULL;

    for (int i = 0; str[i]; i++) {
        lowerStr[i] = tolower(str[i]);
    }
    lowerStr[strlen(str)] = '\0';
    return lowerStr;
}

// Fonction pour comparer les noms de l'agenda
int compareNames(const char* name1, const char* name2) {
    char* lowerName1 = strToLower(name1);
    char* lowerName2 = strToLower(name2);

    if (!lowerName1 || !lowerName2) {
        free(lowerName1);
        free(lowerName2);
        return 0; // Gestion des erreurs
    }

    int result = strcmp(lowerName1, lowerName2);

    free(lowerName1);
    free(lowerName2);
    return result;
}

agenda *contactSearch(directory* list){
    agenda ** agdList;
    printf("Welcome to the search menu : \n");
    if (list->heads[0] == NULL){
        printf("I'm sorry, but the directory is currently empty. Please press Enter to continue.\n");
        return NULL;
    }
    int characNumber = 0;
    char nameInput[100];
    getchar(); //Permet de clear le contenu de stdin.
    printf("Please enter at least the first three characters of the person you search : \n");
    while (characNumber < 99 && (nameInput[characNumber] = getchar()) != '\n'){
        characNumber++;
    }
    nameInput[characNumber] = '\0';
    if (characNumber >= 3){
        int* nbList = NULL;
        agdList = automaticCompletion(list, nameInput, nbList);
        if (agdList == NULL){
            printf("There is no person matching your entry in the directory.\n");
            return NULL;
        } else{
            printf("This is a list of suggestion : \n");
            for (int i=0;i<*nbList;i++){
                printf("The suggestion 1 is %s %s", agdList[i]->ctt.name, agdList[i]->ctt.surname);
            }
            int choice = 0;
            printf("Please select the suggestion that you want : \n");
            scanf("%d", &choice);
            return agdList[choice-1];
        }
    }else{
        printf("You didn't give enough character.\n");
        return contactSearch(list);
    }
}

agenda **automaticCompletion(directory* list, char* name, int* nbList){
    char *nameLow = strToLower(name);
    agenda* current = list->heads[3];
    agenda* prev = current;
    for (int i=3;i>=1;i--){
        while (strToLower(current->ctt.name)[3-i] < nameLow[3-i] && current->nexts[i] != NULL){
            prev = current;
            current = current->nexts[i];
        }
        if (strToLower(current->ctt.name)[3-i] != nameLow[3-i]){
            return NULL;
        }
    }
    int nbCharac = strlen(name);
    for (int i=3;i<nbCharac;i++) {
        while (strToLower(current->ctt.name)[i] < nameLow[i]) {
            prev = current;
            current = current->nexts[0];
        }
        if (strToLower(current->ctt.name)[i] != nameLow[i]){
            return NULL;
        }
    }
    agenda ** agdList = (agenda**) malloc(sizeof(agenda*));
    agdList[0] = current;
    *nbList = 1;
    return agdList;
}

void contactRdvs(agenda *agd){
    printf("The appointments of %s %s are : \n", agd->ctt.name, agd->ctt.surname);
    for (int i=0;i<agd->nbRdvs;i++){
        printf("Appointment number %d : \n", i+1);
        printf("The purpose of this appointment is : %s\n", agd->aps[i].purpose);
        printf("The appointment start on %d/%d/%d at %d:%d and have a duration of %d hours and %d minutes.\n", agd->aps[i].date[0], agd->aps[i].date[1], agd->aps[i].date[2], agd->aps[i].hour[0], agd->aps[i].hour[1], agd->aps[i].duration[0], agd->aps[i].duration[1]);
    }
}

int insertionDirectory(directory *dr, agenda* agd) {
    if (dr->nbElements == 0) {

        for (int i = 0; i <= 3; i++) {
            dr->heads[i] = agd;
        }
        dr->nbElements++;
        return 1;
    }
    char fullName[256];
    snprintf(fullName, sizeof(fullName), "%s_%s", agd->ctt.surname, agd->ctt.name);

    agenda* current = dr->heads[3];
    agenda* prev = NULL;
    int level = 3;

    while (current && level >= 0) {
        char currentName[256];
        snprintf(currentName, sizeof(currentName), "%s_%s", current->ctt.surname, current->ctt.name);

        if (compareNames(fullName, currentName) < 0) {
            agd->nexts = (agenda**)malloc((level + 1) * sizeof(agenda*));
            if (!agd->nexts) return 0;

            for (int i = 0; i <= level; i++) {
                if (prev) prev->nexts[i] = agd;
                agd->nexts[i] = current;
            }
            dr->nbElements++;
            return 1;
        } else {
            prev = current;
            current = current->nexts[level];
            if (level > 0 && strncmp(fullName, currentName, level) != 0) {
                level--;
            }
        }
    }

    return 0;
}

agenda *createContact(directory* dr){
    char name[100];
    int nameNumber = 0;
    char familyName[100];
    int surnameNumber = 0;
    agenda* agd = (agenda*) malloc(sizeof(agenda));
    printf("Welcome to the contact creation menu : \n");
    printf("Please enter the name of the person : \n");
    while(nameNumber < 99 && (name[nameNumber] = getchar()) != '\n'){
        nameNumber++;
    }
    agd->ctt.name = name;
    printf("Please enter the surname of the person : \n");
    while(surnameNumber < 99 && (familyName[surnameNumber] = getchar()) != '\n'){
        surnameNumber++;
    }

    agd->ctt.surname = familyName;
    agd->nbRdvs = 0;
    agd->aps = NULL;
    agd->nexts = NULL;
    insertionDirectory(dr, agd);
    printf("%s", dr->heads[0]->ctt.surname);
    return agd;
}

void createAppointment(directory* dr){
    printf("Welcome to the appointment creation menu : \n");
    printf("Does this appointment involve a new contact ? y/n\n");
    char answer = getchar();
    agenda *agd = NULL;
    if (answer == 'y'){
        printf("You are about to be redirected to the contact creation page.\n");
        agd = createContact(dr);
    } else{
        printf("You are about to be redirected to the contact search page.\n");
        agd = contactSearch(dr);
    }
    if (agd->nbRdvs == 0){
        agd->aps = (rdv*) malloc(sizeof(rdv));
    } else{
        agd->aps = realloc(agd->aps, (agd->nbRdvs + 1)* sizeof(rdv));
    }
    printf("What is the purpose of this appointment : ");
    char *purpose = NULL;
    scanf("%s", purpose);
    printf("What day is your appointment ? (format dd/mm/yyyy) : ");
    int date[3];
    scanf("%d/%d/%d", &date[0], &date[1], &date[2]);
    printf("At what hour starts this appointment ? (format hh:mm) : ");
    int hour[2];
    scanf("%d:%d",&hour[0], &hour[1]);
    printf("What is the duration of this appointement ? (format hh:mm) ? ");
    int duration[2];
    scanf("%d:%d", &duration[0], &duration[1]);
    agd->aps[agd->nbRdvs - 1].purpose = purpose;
    for (int i=0;i<=1;i++){
        agd->aps[agd->nbRdvs - 1].hour[i] = hour[i];
        agd->aps[agd->nbRdvs - 1].duration[i] = duration[i];
    }
    for (int i=0;i<=2;i++){
        agd->aps[agd->nbRdvs - 1].date[i] = date[i];
    }
}