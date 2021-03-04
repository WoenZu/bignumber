// ARRAY_LEN is estimated length of result array
// arr_1 and arr_2 is two array which contaun digits for calculate

#include <stdio.h>
#include <stdlib.h>
#define ARRAY_LEN 10
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

int *add(int *arr_1, int *arr_2, int len_1, int len_2);
int *mul(int *arr_1, int *arr_2, int len_1, int len_2);
void printArr(int *arr, int len);

int main()
{
	printf("\nBE AWARE! Constant ARRAY_LEN is %d", ARRAY_LEN);
	int *res;

	// int arr_1[] = {8,5,3,7,5,2,6,7,8,7,4,0,2,5,8,5,7,7,1,3};
	// int arr_2[] = {4,3,0,9,6,9,2,5,3,0,0,7,5,0,0,0,2,5,4,3,7,1,4,3,8};

	int arr_1[] = {5,9,4};
	int arr_2[] = {5,7};

	int len_1 = ARRAY_SIZE(arr_1);
	int len_2 = ARRAY_SIZE(arr_2);
	//res = add(arr_1, arr_2, len_1, len_2);
	res = mul(arr_1, arr_2, len_1, len_2);
	printf("\n");
	printf("\nArray 1: ");
	printArr(arr_1, len_1);
	printf("\nArray 2: ");
	printArr(arr_2, len_2);
	printf("\nSum/mul of arrays is: ");
	printArr(res, ARRAY_LEN);
	printf("\n ");
	free(res);
	return 0;
}

int *add(int *arr_1, int *arr_2, int len_1,int len_2)
{
	int mem = 0;
	int i;
	int lbig;
	int lsmall;
	int delta;
	int *big;
	int *small;
	int *sum = calloc(ARRAY_LEN, sizeof(int));
	
	if(len_1 > len_2) { // TODO what will happend when both have the same length?
		// arr_1 is BIG
		lbig = len_1;
		big = arr_1;

		lsmall = len_2;
		small = arr_2;
	} else {
		// arr_2 is BIG
		lbig = len_2;
		big = arr_2;

		lsmall = len_1;
		small = arr_1;
	}

	delta = lbig - lsmall;

	for (i = lbig - 1; i >= 0; i--) {
		if (i - delta < 0) {
			sum[i] = big[i] + mem;
			mem = 0;
		} else {
			if (big[i] + small[i - delta] + mem >= 10) {
				sum[i] = (big[i] + small[i - delta]) - 10 + mem;
				mem = 1;
			} else {
				sum[i] = big[i] + small[i - delta] + mem;
				mem = 0;
			}
		}			
	}

	free(big);
	free(small);

	return sum;
}

int *mul(int *arr_1, int *arr_2, int len_1, int len_2)
{
	int mem;
	int offset = 0;
	int i, j, z, k = 0;
	int lbig;
	int lsmall;
	int *big;
	int *small;
	int *res = calloc(ARRAY_LEN, sizeof(int));
	int *stage = calloc(ARRAY_LEN, sizeof(int));
	
	if(len_1 > len_2) { // TODO what will happend when both have the same length?
		// arr_1 is BIG
		lbig = len_1;
		big = arr_1;

		lsmall = len_2;
		small = arr_2;
	} else {
		// arr_2 is BIG
		lbig = len_2;
		big = arr_2;

		lsmall = len_1;
		small = arr_1;
	}

	for (i = lsmall - 1; i >= 0; i--) {
		int temp;
		mem = 0;
		k = ARRAY_LEN - 1;
		printf("\n\n#Iteration: %d", i);
		for(j = lbig - 1; j >= 0; j--) {
			printf("\n>Segment: %d", j);
			printf("\nsmall[%d]:%d * big[%d]:%d + mem:%d ", i, small[i], j, big[j], mem);
			temp = small[i] * big[j] + mem;
			mem = temp / 10; printf("\ntemp: %d, mem: %d", temp, temp / 10);
			stage[k] = temp % 10; printf(", stage: %d to stage[%d]", stage[k], k);
			k--;
			if (j == 0)
				stage[k] = mem;
		}

		for(z = 0; z < ARRAY_LEN; z++) {
			res[z + offset] = res[z + offset] + stage[z]; // FIX
		}
		offset++;
		printf("\nmiddle result: ");
		printArr(stage, 10);
	}

	// free(big);
	// free(small);
	
	return res;
}

void printArr(int *arr, int len)
{
	int i;
	for (i = 0; i < len; i++)
		printf("%d ", arr[i]);
}
