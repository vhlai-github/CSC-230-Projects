/**
   @file schedule.c
   @Vincent Lai

   Main component for the schedule application.  For a collection of
   volunteers, it keeps a set of times when they're responsible for
   tasks.
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "volunteer.h"

/** Representation for the whole schedule. */
typedef struct {
  /** List of volunteers. */
  Volunteer **vlist;

  /** Number of volunteers */
  int vcount;

  /** Capacity of the volunteer list. */
  int vcap;
} Schedule;

/**
    Will clear the schedule
    @param
Schedule *sched: The instance of SChedule to be cleared.
  */
void freeSchedule( Schedule *sched){
    for (int i = 0; i < sched->vcount; i++){
        freeVolunteer(sched->vlist[i]);
    }
    free(sched);
}
/**
    Will check for a particular task given a schedule. It contains ability to add new tasks.
    @param
FILE *fp: input stream
    @param
Schedule *sched: The instance of SChedule to be checked.
  */
bool parseTask(FILE *fp, Schedule *sched){

    char name[MAX_WORD + 1];

        fscanf(fp, "%s", name);

        int vPos = 0;
        int volExist = 0;

        //check if name is already on the list
        for(int i = 0; i < sched->vcount; i++){
            if (strcmp(name, (sched->vlist[i])->name)==0){
                vPos = i;
                volExist = 1;
            }
        }

        if (volExist == 0){
            sched->vlist[sched->vcount] = makeVolunteer(name);
            vPos = sched->vcount;

            sched->vcount = sched->vcount + 1;

            if (sched->vcount == sched->vcap){
                sched->vcap *= 2;
                sched->vlist = (Volunteer **)realloc(sched->vlist, (sched->vcap)*sizeof(Volunteer));
            }
        }

        Volunteer *currVol = (sched->vlist[vPos]);

        char task[MAX_WORD+1];
        char tstart[6];
        char tstartM[3];
        char tend[6];
        char tendM[3];
        scanf(" %s %[0-9]%*[:]%[0-9] %[0-9]%*[:]%[0-9]", task, tstart, tstartM, tend, tendM);

        //printf("%s %s %s %s %s\n", task, tstart, tstartM, tend, tendM);


        strcat(tstart, ":");
        if (sizeof(tstartM) == 2){
            char temp[2];
            strcpy(temp, tstartM);
            strcpy(tstartM, "0");
            strcat(tstartM, temp);
        }
        strcat(tstart, tstartM);

        //printf("%s\n", tstart);

        strcat(tend, ":");
        if (sizeof(tendM) == 2){
            char temp[2];
            strcpy(temp, tendM);
            strcpy(tendM, "0");
            strcat(tendM, temp);
        }
        strcat(tend, tendM);

        //printf("%s\n", tend);

        currVol->tlist[currVol->tcount] = newTask(task, tstart, tend);
        currVol->tcount += 1;
        if (currVol->tcount == currVol->tcap){
            currVol->tcap *= 2;
            currVol->tlist = (Task *)realloc(currVol->tlist, currVol->tcap*sizeof(Task));
        }

        return true;
}
/**
    Removes a task
    @param
Schedule *sched: The instance of SChedule to be checked.
    @param
char name: person of which the task is to be cleared from
    @param
startT: the start time of the task to be cleared.
  */
bool cancel(Schedule *sched, char *name, char *startT){

        int vPos = 0;
        int volExist = 0;

        //check if name is already on the list
        for(int i = 0; i < sched->vcount; i++){
            if (strcmp(name, sched->vlist[i]->name)==0){
                vPos = i;
                volExist = 1;
            }
        }

        if (volExist == 0){
            return 0;
        }
        else{
            Volunteer *currVol = (sched->vlist[vPos]);

            for(int i = 0; i < currVol->tcount; i++){
                if (strcmp(startT, currVol->tlist[i].startTime) == 0){
                    for(int k = 0; k < currVol->tcount-1; k++){
                        currVol->tlist[i] = currVol->tlist[i+1];
                    }
                    currVol->tcount -= 1;
                    return 1;
                }
            }
        }

        return 0;

}

/**
    Used for qsort for sorting the Volunteer list by name
    @param
v1, v2: Two volunteer instances passed as void pointesr. Converted inside function

  */
int compVol(const void *v1,const void *v2){

    Volunteer vol1 = *(Volunteer*)v1;
    Volunteer vol2 = *(Volunteer*)v2;

    char* a = vol1.name;
    char* b = vol2.name;

    //printf("Comparing %s and %s\n", a, b);
//strcmp returns the same notion as the compare functions should
//using the aschii values of each letter
return (strcmp(a, b));
}
/**
    Calls qsort on the schedule
    @param
Schedule *sched: The instance of SChedule to be sorted
  */
void sortSchedule( Schedule *sched){
    qsort(sched->vlist[0], sched->vcount, sizeof(Volunteer), compVol);
}

/**
    Main Function. Parses for the proper command and sends parameters to respective functions.
  */
//report and list command will be in here. main should parse for commands
int main(){

    Schedule *Sched = (Schedule *)malloc(sizeof(Schedule));
    Sched->vcount = 0;
    Sched->vcap = 1;

    Sched->vlist = (Volunteer **)malloc((Sched->vcap)*sizeof(Volunteer));

    char command[7]; //max command length is 6+null

    int cont = 1;

    while(cont){

    scanf("%s", command);


    if (strcmp(command, "add")==0){
        parseTask(stdin, Sched);
    }

    else if (strcmp(command, "cancel")==0){
        char name[MAX_WORD+1];
        char tstart[6];
        char tstartM[3];
        scanf("%s %[0-9]%*[:]%[0-9] ", name, tstart, tstartM);

        strcat(tstart, ":");
        if (sizeof(tstartM) == 2){
            char temp[2];
            strcpy(temp, tstartM);
            strcpy(tstartM, "0");
            strcat(tstartM, temp);
        }
        strcat(tstart, tstartM);

        cancel(Sched, name, tstart);
    }


    else if (strcmp(command, "list")==0){

        sortSchedule(Sched);

        for (int i = 0; i <Sched->vcount; i++){
            printf("%s\n", Sched->vlist[i]->name);
        }
    }

    else if (strcmp(command, "report")==0){
        char name[MAX_WORD + 1];

        scanf("%s", name);

        int vPos = 0;
        int volExist = 0;

        //check if name is already on the list
        for(int i = 0; i < Sched->vcount; i++){
            if (strcmp(name, Sched->vlist[i]->name)==0){
                vPos = i;
                volExist = 1;
            }
        }
        if (volExist == 1){
            //printf("made it here");
            reportVolunteer(Sched->vlist[vPos]);
        }
        else{
            printf("Invalid command");
        }


    }

    //maybe use while loop with quit to loop the program
    else if (strcmp(command, "quit")==0){
        return 0;
    }

    else (cont=0)

    }
    return 0;
}
