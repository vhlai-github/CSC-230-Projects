/**
   @file volunteer.h
   @author

   Header for the volunteer component, defining part of the schedule
   representation.
 */

/** Maximum length of a volunteer or a task name. */
#define MAX_WORD 20

/** Initial capacity for resizable arrays. */
#define INITIAL_CAP 3

#define MAX_TIME 5

/** Representation ofr a task that a volunteer is responsible for. */
typedef struct {
  /** Name of the task (e.g. an attraction name) where the volunteer is
      working. */
  char name[ MAX_WORD + 1 ];

  char startTime[MAX_TIME + 1];

  char endTime[MAX_TIME +1 ];

  int sMinutes;

  int eMinutes;

} Task;

/** Representation for a volunteer, with a resizable array holding a set
    of tasks. */
typedef struct {
  /** Name of the volunteer. */
  char name[ MAX_WORD + 1 ];

  /** List of tasks for this volunteer. */
  Task *tlist;

  /** Number of tasks on tlist. */
  int tcount;

  /** Capacity of the task list. */
  int tcap;
} Volunteer;
/**
    Creates a new volunteer, dynamically allocates space for a new instance of Volunteer.
    @param
char *name: name of the new volunteer
  */
Volunteer *makeVolunteer( char *name );

/**
    Removes Volunteer and all their tasks from the list
    @param
Volunteer *v: The volunteer who's tasks are to be removed
  */
void freeVolunteer( Volunteer *v );
/**
    Sorts Tasks of a volunteer based on time
    @param
Volunteer *v: volunteer who's tasks are to be sorted
**/
void sortTasks( Volunteer *v );
/**
    Lists the tasks of a Volunteer a long with the total minutes worked
    @param
Volunteer *v: The volunteer who's tasks are to be listed
  */
void reportVolunteer( Volunteer *v );
/**
    Creates a new Task
    @param
char tName: name of the task
    @param:
char tStart: start time of the task
    @param:
char tEnd: end time of the Task
  */
Task newTask(char *tName, char *tStart, char *tEnd);
