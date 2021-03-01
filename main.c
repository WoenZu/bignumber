#include <stdio.h>
#include <stdlib.h>

int *add(int *nl, int *n2, int l1, int l2);
int main() {
	int n1[] = {1,3,5};
	int n2[] = {4,3,9};
	int l1 = sizeof(n1)/sizeof(n1[0]);
	int l2 = sizeof(n2)/sizeof(n2[0]);
	add(n1, n2, l1, l2);
	
	return 0;
}

int *add(int *n1, int *n2, int l1,int l2) {
	int *sum = calloc(100, sizeof(int));
	int mem = 0;
	// find biggest array
	
	// calculate summ
	for() {
	}
	return sum;	
}

