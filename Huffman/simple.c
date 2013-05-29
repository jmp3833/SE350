/*
 * This demonstrates the simplest way to do some tests using simplectest.
 * See "readme.txt" for more information, or the website at
 * http://simplectest.sf.net/.
 *
 * Jevon Wright 2004-05
 */
#include "tests.h"
#include "OrderedList.c"
#include "HuffmanTree.h"
// Start the overall test suite
START_TESTS()

// A new group of tests, with an identifier
START_TEST("Add to the singly linked list")
	// We then write the tests we want to check
	HTreeNode *node;
	node->ht_count = 10;
	ol_insert(node);

	ASSERT_EQUALS(ol_size(),1);
END_TEST()


// End the overall test suite
END_TESTS()
