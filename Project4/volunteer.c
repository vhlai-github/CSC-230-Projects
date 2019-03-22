/**
   @file volunteer.c
   @Vincent Lai (vhlai

   Volunteer
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "volunteer.h"

Volunteer *makeVolunteer( char *name ){
    Volunteer *v = (Volunteer*) malloc (sizeof(Volunteer));
    strcpy(v->name, name);

    v->tcount = 0;

    v->tcap = 1;

    v->tlist = (Task *)malloc((v->tcap)*sizeof(Task));

    return v;
}

Task newTask(char *tName, char *tStart, char *tEnd){
    Task *t = (Task *)malloc(sizeof(Task));
    strcpy(t->name, tName);
    strcpy(t->startTime, tStart);
    strcpy(t->endTime, tEnd);

    //printf("%s %s %s\n", t->name, t->startTime, t->endTime);

    int sH;
    int sM;
    sscanf(tStart, "%d%*[:]%d", &sH, &sM);

    int eH;
    int eM;
    sscanf(tEnd, "%d%*[:]%d", &eH, &eM);

    if (sH < 8){
        sH += 12;
    }

    t->sMinutes = sH*60+sM;

    //printf("%d\n", t->sMinutes);

    if (eH < 8 || ((eH == 8) && (eM == 0))){
        eH = eH+12;
    }

    t->eMinutes = eH*60+eM;


    //printf("%d\n", t->eMinutes);
    return *t;
}

int compTask(const void *task1, const void *task2){

    Task t1 = *(Task*)task1;
    Task t2 = *(Task*)task2;

    int value = 0;
    if (t2.sMinutes < t1.sMinutes) {
        value = -1;
    }
    if (t2.sMinutes > t1.sMinutes) {
        value = 1;
    }
    return (value);
}

void freeVolunteer( Volunteer *v ){
    for (int i = 0; i < v->tcount; i++){
        free(&(v->tlist[i]));
    }
    free(v);
}

void sortTasks( Volunteer *v ){
    qsort(v->tlist, v->tcount, sizeof(Task), compTask);
}



void reportVolunteer( Volunteer *v ){
    //sortTasks(v);
    int totalTime = 0;

    for(int i = 0; i < v->tcount; i++){
        Task currTask = v->tlist[i];
        totalTime = totalTime + currTask.eMinutes - currTask.sMinutes;
    }

    printf("%s (%d)\n", v->name, totalTime);

    for(int i = 0; i < v->tcount; i++){
        Task currTask = v->tlist[i];
        printf("%24s %5s %5s\n", currTask.name, currTask.startTime, currTask.endTime);
    }
}

