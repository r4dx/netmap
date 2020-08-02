#include "btree.h"
#include <stdio.h>
#include <stdlib.h>

typedef void (test_func)();

void fail(char* msg) {
	fprintf(stderr, "%s\n", msg);
	exit(1);
}


void init_creates_btree() {
	fail("Yes it fails!");
}

static test_func* tests[] = { *init_creates_btree };

int main(void) {
	for (int i = 0; i < sizeof(tests) / sizeof(tests[0]); i++) {
		tests[i]();
	}
	return 0;
}
