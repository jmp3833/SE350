/*
 * Implementation file for the doubly ended queue (dequeue)
 */

#include <stdlib.h>
#include <string.h>
#include "dequeue.h"

/********
 **
 ** INSTRUCTIONS
 **
 ** This the empty skeleton file for the implemenation of the
 ** double ended queue. Read the header file dequeue.h and 
 ** to see the documentation for each of the functions as well as how these
 ** are used in practice. To receive full credit, you must implement all of
 ** the following deq_* functions:
 */

bool deq_is_empty(node *deqhead){

	//If the head of the list has no size
        if(deqhead == NULL){
                return true;  
        } 

        return false; 

}

int deq_size( node *deqhead){
       
       	node *cur;
	int sizeCount = 0;
	cur =  deqhead;
	       
	//If the next node in the list is null,stop counting.         
	while (cur != NULL){
		sizeCount +=1;
		cur = cur ->link;
	} 
	 
	return sizeCount;   
}


void deq_put_head(node **deqhead, char *value){
	
	//Creates a refrence to a new node
        node *newnode;
       	newnode = malloc(sizeof(node));
	
	//Populates the values of the new node
	newnode->contents = &value;
	newnode->link = *deqhead;
	
	//sets the old head to the newnode value
	*deqhead = newnode;
    
}

void deq_put_tail(node **deqhead, char *value){
    
}

void deq_get_head(node **deqhead, char *value){
	
	if(deq_is_empty(*deqhead)){
		return;
	}
	//unlink the node at the head of the list
	node* cur;
	cur = *deqhead;

	//copy over contents
	*deqhead = cur ->link;
	value = cur ->contents;

	
	//free the storage of the previous head
	free(cur);
	return;

}

void deq_get_tail(node **deqhead, char *value){

}
