#ifndef FLIGHT_H
#define FLIGHT_H


#include "LLNode.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM_LENGTH 2

/* flight struct definition */
typedef struct flight {
    char airlines[MAX_NUM_LENGTH];
    int flight_num;
    int arrival_time;
    int dep_time;
}flight;



/* Function prototypes */
flight* makeFlight(char* name, int num, int arr_time, int d_time);
int runFlights(char* flight_file);



#endif