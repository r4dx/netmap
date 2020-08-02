#ifndef BTREE_H
#define BTREE_H

#include <stdbool.h>

typedef long BT_KEY;

typedef struct BTNode BTNode;

typedef struct BTRange {
	int start;
	int end;
	BTNode* node;
} BTRange;

typedef struct BTNode {
	BT_KEY* keys;
	
	int nranges;
	BTRange* ranges;
} BTNode;

typedef struct BTree {
	BTNode* root;
	int t_degree;

} BTree;

typedef struct SearchResult {
	bool found;
	void* value;
} SearchResult;


BTree* bt_init(int t_degree);
void bt_unload(BTree* tree);

SearchResult bt_search(BTree* tree, BT_KEY k);
void bt_insert(BTree* tree, BT_KEY k, void* v);
bool bt_delete(BTree* tree, BT_KEY k);
#endif
