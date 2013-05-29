/*
 * Program to create a Huffman code for letters in a document read from standard input.
 */

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>

#include "HuffmanTree.h"
#include "OrderedList.h"

#define NLETTERS (26)

/*
 * Array of structions, one per letter, holding the count of occurrences of the letter and
 * the final Huffman code for the letter (generated during tree traversal).
* This combines the declaration of the structure type and its fields with an array whose
 * elements are of the structure type.
 */
 
 static struct letter_data {
    int ld_count ;
    char *ld_code ;
 } data[NLETTERS] ;

/*****
 * Local functions.
 *****/
 
 /*
  * Read the standard input file and accumulate the letter counts in array "count".
  */
static void read_file() ;

/*
 * Initialize the ordered list with 26 HTreeNodes, one for each letter (with its count).
 */
static void initialize_ordered_list() ;

/*
 * Build the huffman coding tree. Assumes the ordered list is populated with leaf nodes
 * holding letters and their counts.
 * At exit, there is one node in the ordered list, namely the root of the whole Huffman coding
 * tree.
*/
static void build_huffman_tree() ;

/*
 * Traverse the tree given in the first argument, using the prefix to the final code given in the
 * second argument.
 *    For leaf nodes, the prefix *is* the final code, so we store it in the structure in the original
 *      table reserved for the given letter.
 *    For interior nodes, the prefix has "0" appended for the left subtree and "1" appended for the
 *      right subtree. By appending we end up with a code that is parsed left to right.
 */
static void traverse_tree( HTreeNode *root, char *prefix ) ;
 
 /*
  * Print the final code for each letter in the table.
  */
static void print_codes() ;

/*
 * Main driver program.
 * The arguments are ignored.
 */
int main ( int ac, char **av ) {
 
    read_file() ;
    initialize_ordered_list() ;
    build_huffman_tree();
    traverse_tree( ol_remove(), "" ) ;
    print_codes() ;

    exit(0) ;
}

 /*
  * Read the standard input file and accumulate the letter counts in the "ld_count" fields
  * array "data".
  */
static void read_file()  {
    int next_char ;
    
    while ( (next_char = getchar()) != EOF ) {
        if ( isalpha( next_char ) ) {
            int index = next_char - ( isupper( next_char ) ? 'A' : 'a' ) ;
            ++data[index].ld_count ;
        }
    }
    return ;
}

/*
 * Initialize the ordered list with HTreeNodes, one for each letter (with its count).
 * At the end the list will have the HTreeNode for the letter with the lowest count at
 * the front, and the HTreeNode for the most frequent letter at the end.
 */
static void initialize_ordered_list() {
    
    int x;
    
    for(x=0; x < NLETTERS; x++){
       
        data[x].ld_code = malloc(sizeof(char));
	*data[x].ld_code = x + 65;
       
	
	ol_insert(mk_tree(x+65,data[x].ld_count,NULL,NULL));
    } 
    
    assert( ol_size() == NLETTERS ) ;  /* invariant at this point */
    return ; 
    
}

/*
 * Build the huffman coding tree. Assumes the ordered list is initially populated with leaf nodes
 * holding letters and their counts.
 *
 * While there are at least two nodes left in the list, remove the first two (with the lowest
 * counts) and:
 *      + create a new new with these two nodes as children, smallest count to the left.
 *      + set the new node's count to the sum of the children's counts.
 *      + insert the new node into the list.
 * This is a linear process, in that for every two nodes removed, one is inserted, so the
 * length of the list decreases by 1 each time through the loop.
 *
 * On return, there is one node in the ordered list, namely the root of the whole Huffman coding
 * tree.
*/
static void build_huffman_tree() {

	HTreeNode *rem1;
	HTreeNode *rem2; 

	int newCount;

	while (ol_size() >= 2){
		rem1 = ol_remove();
		rem2 = ol_remove();

		newCount = rem1 ->ht_count + rem2 ->ht_count;

		ol_insert(mk_tree(' ',newCount,rem1,rem2));	
			
	}
	return;
}

/*
 * Traverse the Huffman coding tree given in the first argument,
 * with the prefix so far as a string second argument.
 *    For leaf nodes, the prefix *is* the final code, so we store *a copy* of the prefix string in
 *       the structure in the original data table associated this letter. That is, the copy is stored
 *       in the letter's "ld_code" field.
 *    For interior nodes, a local string is allocated to hold the prefix with "0" appended to
 *        traverse the left subtree and the prefix with "1" appended to traverse the
 *        right subtree. By appending we end up with a code that is parsed left to right.
 */
static void traverse_tree( HTreeNode *root, char *prefix ) {
    /*
       * The node is a leaf it it has no descendant nodes. Since the tree is a complete
       *  binary tree we need only check one of the two descendant links. If this
       * is a leaf, the code for the letter is the prefix - make a copy and then free
       * up storage for the Huffman Tree Node (we don't need it any longer).
    */

    
    if(root ->ht_label == ' '){
         char* newString;
	 newString = malloc(sizeof(prefix+1));
         strcpy(newString,prefix);

     	 newString = strcat(newString,"0");
         traverse_tree(root ->ht_left,newString); 
	 free(newString);

	 char* newStringR;
	 newStringR = malloc(sizeof(prefix+1));
	 strcpy(newStringR,prefix);

	 newStringR = strcat(newStringR,"1");
         traverse_tree(root ->ht_right,newStringR);
	 
	 free(newStringR);
     }
     else{ //Hit a leaf node

          int l = 0;
	  l = root ->ht_label-65;
	  data[l].ld_code = malloc(sizeof(prefix));
	  strcpy(data[l].ld_code,prefix);
	  free(root);
	  return;
	  			
     }
    
    /*
       * Allocate space a string to hold the prefix plus one additional
       * character (be careful in computing the amount of space you need!).
       * Extend the prefix with a "0" and process the left tree.
       * Extend the prefix with a "1" and process the right tree.
       * When done, free up the space used by the local string used for
       *    extension *as well as* the space used by the Huffman Tree Node
       *    just processed - we don't need it any longer.
    */

}
 
 /*
  * Print the final code for each letter in the table.
  */
static void print_codes() {
	int i;
	for(i = 0; i < NLETTERS; i++){
		printf("%c %s\n",i+65,data[i].ld_code);
	}
}
