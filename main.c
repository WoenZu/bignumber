#include <stdio.h>
#include <stdlib.h>

int *add(int *nl, int *n2, int l1, int l2);
void PrintArr(int *arr, int len);

int main() {
	int n1[] = {8};
	int n2[] = {4, 3};
	int l1 = sizeof(n1)/sizeof(n1[0]);
	int l2 = sizeof(n2)/sizeof(n2[0]);
	add(n1, n2, l1, l2);
	
	return 0;
}

int *add(int *n1, int *n2, int l1,int l2) {
	int arrayLen = 5;
	int *sum = calloc(arrayLen, sizeof(int));
	int mem = 0;
	int i;
	int count;
	
	count = l1 < l2 ? l1 : l2;

	// debug info
	printf("\nDEBUG================================");
	printf("\nsum array len: %d, shortest digit: %d", arrayLen, count);
	printf("\n\narrays:");
	printf("\nn1: ");
	PrintArr(n1, l1);
	printf("\nn2: ");
	PrintArr(n2, l2);
	//printf("\nl1: %d, l2: %d", l1, l2);
	
	// debug

	for(i = 0; i >= 0; i--) {
		printf("\n\niteration: %d", i); // debug
		printf("\nn1: %d, n2: %d", n1[i], n2[i]);
		
		if (n1[i] + n2[i] > 10) {
			printf("\n\n > 10 ");
			
			mem = 1;
			sum[i] = n1[i] + n2[i] - 10;
			printf("\ninner sum: %d", sum[i]);
			
		} else if(n1[i] + n2[i] < 10) {
			sum[i] = n1[i] + n2[i];
			printf("\n\ninner sum: %d", sum[i]);
			mem = 0;
		}
	}
	printf("\n\nsum: ");
	PrintArr(sum, arrayLen);
	
	return sum;
}

void PrintArr(int *arr, int l) {
	int i;
	for (i = 0; i < l; i++) {
		printf("%d ", arr[i]);
	}
}