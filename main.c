/**************************************************************
 * Flight log Homework
 * CS 305 Spring 2021
 * 
 * This .c file is the main function. It recieves user input 
 * from the command line and then calls runFlights 
 * 
 * Author: Jude Gabriel
 * 
 * Version: 3/24/2021
 ************************************************************/


#include "LLNode.h"
#include "flight.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argv, char* argc[]){
    char* file_name;
    //Checks if a flight text file is passed in
    if(argv != 2){
        file_name = NULL;
    }
    else{
        file_name = argc[1];
    }
    //Calls runFlights
    runFlights(file_name);
}