/******************************************************************************
 * This .c file consists of functions called on by runFLights.
 * These functions are used to create a node, add the node to the list,
 * delete a node from the list, save the list to a file, print the list,
 * and clear all data stored when exiting the program.
 * 
 * Author: Jude Gabriel 
 * 
 * Version: 3/26/2021
 *****************************************************************************/


#include "LLNode.h"
#include "flight.h"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"


/** insert
 * args: LLNode* -pointer to the node to be added, LLNode* -pointer to be linked list
 * out: LLNode* -pointer to the updated linked list
 * 
 * This function adds node containing a flight object to the linked list.
 * The flights are added in ascending order by flight number.
 * This function is recursive. It continues through the list until 
 * it finds the proper section for the flight. Then recursively returns
 * the list to 'reconnect' it before returning the final linked list
 */
LLNode* insert(LLNode* node_ptr, LLNode* list){   
    //Checks if the node being added exists
    if(node_ptr == NULL){
        printf("Cannot add blank flight");                 
        return list;
    }
    //Case 1: The list is empty
    else if(list == NULL){                              
        return node_ptr;
    }
    //Case 2: Correct poosition found, adds flight and recursively reconnects list
    else if(list->data->flight_num >= node_ptr->data->flight_num){                                                      
        node_ptr->next = list;                                                      
        return node_ptr;                                                            
    }
    //Case 3: Need to recursivley move through the list to find correct spot
    else if(list->data->flight_num < node_ptr->data->flight_num){                                                         
        list->next = insert(node_ptr, list->next);                                   
        return list;
    }  
}




/** makeNode
 * args: LLnode* -pointer to the node to be created, flight* - pointer to the flight object
 * out: LLnode* -pointer to the initialized node
 * 
 * This function creates a new node and stores the flight data in it.
 */
LLNode* makeNode(flight* flt_ptr){
    //Malloc size of a node and initialize node data with the flight
    LLNode* my_node = (LLNode*)malloc(sizeof(LLNode));
    my_node->data = flt_ptr;
    
    //Print the flight info that is being added and set the nodes next position to NULL   
    printf("Inserting flight: %c%c %d %d %d\n", flt_ptr->airlines[0], flt_ptr->airlines[1], 
            flt_ptr->flight_num, flt_ptr->arrival_time, flt_ptr->dep_time);  
    my_node->next = NULL;  

    //Returns the created node
    return my_node;
}




/** deletes
 * args: LLnode* -pointer to node, LLNode** -double node pointer, int -flight to delete
 * out: LLnode* -pointer to the updated linked list
 * 
 * This function will use recursion to delete a given node.
 * Similarly to how the flights were added, recursion is used to find the 
 * correct flight. Once it is deleted recursion pops each return and 
 * reconnects the linked list.
 */
LLNode* deletes(LLNode* node_ptr, int num){
    LLNode* new_node = node_ptr;
   
   //Case 1: List is empty
    if(node_ptr == NULL){                                    
        printf("Cannot find flight.\n");
        return node_ptr;
    }
    
    //Case 2: The flight is found and deleted
    else if(node_ptr->data->flight_num == num){              
        new_node = node_ptr->next;
        //Free the node and recursivley pop back to reconnect list
        free(node_ptr->data);
        free(node_ptr);
        return new_node;
    }    
    
    //Case 3: Current node is not the one to delete. Recursively move through list
    else{                                                              
        node_ptr->next = deletes(node_ptr->next, num);           
        return node_ptr;
    }  
}




/** save
 * args: LLNode* -poiinter to linked list, char* name of file to save under
 * out: void
 * 
 * This function takes a user input string name to save the flight list in a text file.
 */
void save(LLNode* node_ptr, char* name){
    //If list is empty print error message
    if(node_ptr == NULL){
        printf("Cannot save an empty list.\n\n");
        return;                     
    }
    
    //Create a file to save under
    else{
        FILE* out = fopen(name, "w");
        if(out == NULL){
            printf("NULL\n");
        }       
        
        //Uses a loop to add each flight to the file 
        while(node_ptr != NULL){
            fprintf(out, "%c%c %d %d %d\n", node_ptr->data->airlines[0], node_ptr->data->airlines[1], 
                        node_ptr->data->flight_num, node_ptr->data->dep_time, node_ptr->data->arrival_time);
            node_ptr = node_ptr->next;
        }
        
        //Frees the name that was created in teh function call and closes the file
        free(name);
        fclose(out);
    }
}




/** printList
 * args: LLnode* -pointer to linked list
 * out: void
 * 
 * This function will recursively print each each flight in the linked list.
 */
void printList(LLNode* node_ptr){
    //If list is empty quit function
    if(node_ptr == NULL){
         return;
    }
    
    //Recursivly print each flight until end of list is hit
    printf("%c%c %d %d %d\n", node_ptr->data->airlines[0], node_ptr->data->airlines[1],
                node_ptr->data->flight_num, node_ptr->data->arrival_time, node_ptr->data->dep_time);
    printList(node_ptr->next);
    
}
  



/** freeNode
 * args: LLNode * -pointer to the linked list
 * out: void
 * 
 * This function recursively free's each node in the linked list.
 * First the flight is freed, then the recursion is called. 
 * Finally the list itself is free'd by recursively popping backwards
 * and free'ing each node.
 */
void freeNode(LLNode* node_ptr){
    //If the list is empty quit the function
    if(node_ptr == NULL){
    return;
    }   
    
    //Recursivly free's each flight before popping backwards and free'ing each node.
    //Then free's the pointer to the list.                                              
    else{
        free(node_ptr->data);
        freeNode(node_ptr->next);
        free(node_ptr);                                      
    } 
}




