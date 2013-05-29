/*
 * Implementation of a module supporting an ordered list of HTreeNodes - ordering is by increasing
 * count field.
 *
*/
 
#include <stdlib.h>
#include <assert.h>
 
#include "OrderedList.h"
#include "HuffmanTree.h"

/*
 * Node structure for nodes in the ordered list. Not defined as a typedef as
 * this is purely a local implementation detail and is invisible outside this module.
 *
 * Each node points to the HTreeNode is contains and to its successor node in the
 * ordered list (or NULL if it is the end of the list).
 */
struct ol_node {
    HTreeNode *ol_tn ;
    struct ol_node *ol_next ;
} ;

/*
 * Module state: Pointer to the head of the list (NULL => empty) and the
 * current size of the list. The latter is an optimization - we could compute
 * the size on each call to ol_size, but this would turn an O(1) algorithm
 * into O(n).
*/

static struct ol_node *head = NULL ;
static int size = 0 ;

/*
 * Insert the specified HTreeNode into the ordered list in the proper position
 * according to increasing count.
 *
 * Record the increase in size.
 * Traverse the list until either (a) find a node with a value larger than that
 *    in the tree node or (b) hit the list end. This tells us where the new node.
 *    belongs.
 * Aborts if we run out of memory.
 */

void ol_insert(HTreeNode *t)  {
     	
	//Create the new node containing an HTreeNode
	struct ol_node* newNode;
	newNode = malloc(sizeof(struct ol_node));
	newNode->ol_tn = t;
	size++;	
	//Variable to easily access the count of the selected HTreeNode
	int count = newNode->ol_tn->ht_count;
	
	/*
	If the list is empty or the arguments count is less than
	the count of the head. 
	*/
	if(head == NULL){
		head = newNode;
		head ->ol_next = NULL;
		return;
			
	}
	if(head -> ol_next == NULL){
		if(count < head ->ol_tn ->ht_count){
			newNode -> ol_next = head;
			head = newNode;
		}
		else{
			head ->ol_next = newNode;
			newNode ->ol_next = NULL;
		}

		return;
	}
	
	//Declared variables to iterate over the ordered list.
	struct ol_node  *cur;
	cur = head;

	while((cur -> ol_next != NULL) && (count > cur->ol_next ->ol_tn->ht_count)){
		cur = cur -> ol_next;
		
	}
	if(cur -> ol_next != NULL){
		newNode->ol_next = cur ->ol_next;
	}

	cur -> ol_next = newNode;
	
	
}	
        
/*
 * Return the current size of the list of HTreeNodes.
 */

int ol_size() {
    return size ;
}

/*
 * Remove the first HTreeNode in the list and return a pointer
 * to it, adjusting the list size appropriately.
 * If the list is empty, NULL is returned and the size is unchanged.
 */

HTreeNode *ol_remove() {
	
	//If the list is empty
	if(head == NULL){ 
		return NULL;
	}
	else{
		HTreeNode* returnTree;
		returnTree = head ->ol_tn;
		head = head ->ol_next;
		
		size-=1;
		return returnTree;
		
	}
		
}
