#ifndef LLNODE_H
#define LLNODE_H


#include "flight.h"
#include <stdio.h>
#include <stdlib.h>

/* LLNode struct definition */
typedef struct Node LLNode;

struct Node{
     LLNode* next;
     flight* data;
};



/* Function protoypes */
LLNode* insert(LLNode* node_ptr, LLNode* list);
LLNode* deletes(LLNode* node_ptr, int num);
void save(LLNode* node_ptr, char* name);
void printList(LLNode* node_ptr);
void freeNode(LLNode* node_ptr);
LLNode* makeNode(flight* flt_ptr);



#endif