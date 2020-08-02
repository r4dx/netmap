#include "btree.h"
#include <stddef.h>
#include <stdlib.h>

/*
 * All leaves are at the same level
 * The root contains minimum 1 key, maximum 2t-1
 * Each of every other nodes contain number of keys in a range: [t-1, 2t-1]
 * All keys inside a node are sorted
 *
 */

BTree* bt_init(int t_degree) {
	BTree* result = malloc(sizeof(BTree));
	result->t_degree = t_degree;
	result->root = malloc(sizeof(BTNode));

	return result;
}

SearchResult bt_search(BTree* tree, BT_KEY k) {
	return (SearchResult){ true, NULL };
}

void bt_insert(BTree* tree, BT_KEY k, void* v) {
	
}
