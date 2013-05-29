/*
 * Implementation of the Huffman tree module.
 *
*/
 
 #include <stdlib.h>
 #include <assert.h>
 #include "HuffmanTree.h"

 /*
  * Helper function to create a new tree from two subtrees and
  * the desired root node label. The root node count is the sum
  * of the counts of the subtrees.
 */
 HTreeNode *mk_tree( char lab, int count, HTreeNode *left, HTreeNode *right)  {

	//Creates a new node based on the given parameters	
	HTreeNode *newNode = malloc(sizeof(HTreeNode));

	newNode -> ht_label = lab;
	newNode -> ht_count = count;
	newNode -> ht_left = left;
	newNode -> ht_right = right;

	return newNode;
 }
