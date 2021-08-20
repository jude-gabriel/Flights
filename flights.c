/******************************************************************************
 * This .c file will collect user input from the command line.
 * Functions are called to create a flight, create a node and initialize it 
 * with flight data, and populate the linked list. Valid oeprations are
 * a: add flight, d: delete flight, s: save to a file, p: print list,
 * q: exit program.
 * 
 * Author: Jude Gabriel 
 * 
 * Version: 3/24/2021
 *****************************************************************************/


#include "LLNode.h"
#include "flight.h"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"



/** runFlights
 * args: user entered file 
 * out: int to return program status 
 * 
 * This function runs the program. 
 * It takes user input and converts it to a flight object which is then added
 * to the linked list. Operations include add flight, delete flight
 * save to a file, print flight list, and exit program.
 * 
 * Optional file arguement adds all flights from the file to the linked list.
 */
int runFlights(char* flight_file){
    //Create and intialize variables for flight, LL, and nodes.
    char user_char;
    flight* my_flight;
    LLNode* a_node = NULL;
    LLNode* new_node = NULL;
    char file_name[20];
    char flight_name[2];
    int flight_num;
    int dep_time;
    int arr_time;
    char c = ' ';

    //Checks if the user input a file when running program
    if(flight_file != NULL){
        //Opens file and checks if it exists
        FILE* in = fopen(flight_file, "r");
        if(in == NULL){
            printf("File cannot be opened.\n");
        }
        else{
            //Scans data from file to populate the list
            while(fscanf(in, "%2s %d %d %d", flight_name, &flight_num, &dep_time, &arr_time) != EOF){
                //Error check for invalid parameters               
                if((strlen(flight_name) < 2) || flight_num <= 0 || dep_time <= 0 || arr_time <= 0){
                    printf("Invalid entry.\n");
                    continue;     
                }

                //Creates flight and populates list with created nodes
                my_flight = makeFlight(flight_name, flight_num, dep_time, arr_time);           
                a_node = makeNode(my_flight);
                new_node = insert(a_node, new_node);
                printf("\nFLight List:\n");       
                printList(new_node);
                printf("\n");  
            }
        }
        //Closes File
        fclose(in);
    }

    while(1){
        //Asks user to enter which operation they'd like to use
        printf("Press 'a' to add a flight, 'd' to delete a flight, 's' to save the ");
        printf("flight list, 'p' to print the flight list, and 'q' to exit the program.\n");
        scanf("%c", &user_char);
        while((c = getchar()) != '\n' && c != EOF);
        fflush(NULL);
        
        //User adds a flight
        if(user_char == 'a'){
            //Collects data from user to add a flight
            //Lines 89 & 90 provided by Dr. Cenek 
            printf("Please list the airline, flight number, departure time and arrival time.\n");
            scanf("%2s %d %d %d", flight_name, &flight_num, &dep_time, &arr_time);
            while((c = getchar()) != '\n' && c != EOF);  
            fflush(NULL);
            
            //Error checks user's entry
            if((strlen(flight_name) < 2) || flight_num <= 0 || dep_time <= 0 || arr_time <= 0){
                printf("Invalid entry.\n");
                continue;
            }
            
            //Creates a flight and populates linked list
            my_flight = makeFlight(flight_name, flight_num, dep_time, arr_time);           
            a_node = makeNode(my_flight);
            new_node = insert(a_node, new_node); 
            printf("\nFLight List:\n");       
            printList(new_node);
            printf("\n");
        }

        //User deletes a flight
        else if(user_char == 'd'){
            //Collects user input on which flight to delete
            printf("Please enter the number of the flight you'd like to delete.\n");
            scanf("%d", &flight_num);
            while((c = getchar()) != '\n' && c != EOF);
            fflush(NULL);
            
            //Checks if list is empty
            if(new_node == NULL){
                printf("Cannot delete from empty list.\n\n");
                continue;
            }
            
            //Deletes flight and prints new list
            new_node = deletes(new_node, flight_num);
            printf("\nFLight List:\n");                              
            printList(new_node);
            printf("\n");
        }

        //User saves list to a file
        else if(user_char == 's'){
            //Collects user input for file to save under
            printf("Please enter a file name to save under\n");                   
            scanf("%s", file_name); 
            while((c = getchar()) != '\n' && c != EOF);
            fflush(NULL);
           
            //Saves input in the file
            save(new_node, strdup(file_name));

        }

        //User prints the list
        else if(user_char == 'p'){
            //Error checks if list is empty
            if(new_node == NULL){
                printf("Flight list is empty.\n\n");
                continue;
            }
           
            //Prints flight list
            printf("Flight list:\n");
            printList(new_node);
        }

        //User exits the program
        else if(user_char == 'q'){
            //Free's all data stored and exits program
            freeNode(new_node);
            return EXIT_SUCCESS;
        }

        //User input is invalid
        else{
            printf("Invalid input. Please try again.\n");
        }
    }
}



/** makeFLight
 * args: char* -flight name, int -flight number, int -arrival time, int depart time
 * out: pointer to a flight object
 * 
 * This function takes the input from the user and creates a flight object.
 * The flight is mallocked and all fields are intialized.
 */
flight* makeFlight(char* name, int num, int arr_time, int d_time){
    //Creates space in memory for a flight object
    flight* my_flight = (flight*)malloc(sizeof(flight));

    //Initializes flight paramters
    strcpy(my_flight->airlines, name);
    my_flight->flight_num = num;
    my_flight->arrival_time = arr_time;                                        
    my_flight->dep_time = d_time;

    //Returns created flight object
    return my_flight;
}












