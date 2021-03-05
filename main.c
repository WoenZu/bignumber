// ARRAY_LEN is estimated length of result array
// arr_1 and arr_2 is two array which contaun digits for calculate

#include <stdio.h>
#include <stdlib.h>
#define ARRAY_LEN 30
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#define PRINT_ARR(x, y)			\
	do {				\
		int i;			\
		for (i = 0; i < y; i++)	\
		printf("%d ", x[i]);	\
	} while (0)


int *add(int *arr_1, int *arr_2, int len_1, int len_2);
int *mul(int *arr_1, int *arr_2, int len_1, int len_2);

int main()
{
	printf("\nBE AWARE! Constant ARRAY_LEN is %d", ARRAY_LEN);
	int *res;

	// int arr_1[] = {8,5,3,7,5,2,6,7,8,7,4,0,2,5,8,5,7,7,1,3};
	// int arr_2[] = {4,3,0,9,6,9,2,5,3,0,0,7,5,0,0,0,2,5,4,3,7,1,4,3,8};
	
	int arr_1[] = {8,5,3,7,5,2};
	int arr_2[] = {4,3,0,9,6};

	// int arr_1[] = {5,9,4};
	// int arr_2[] = {5,7};

	int len_1 = ARRAY_SIZE(arr_1);
	int len_2 = ARRAY_SIZE(arr_2);
	res = add(arr_1, arr_2, len_1, len_2);
	//res = mul(arr_1, arr_2, len_1, len_2);
	printf("\n");
	printf("\nArray 1: ");
	PRINT_ARR(arr_1, len_1);
	printf("\nArray 2: ");
	PRINT_ARR(arr_2, len_2);
	printf("\nSum/mul of arrays is: ");
	PRINT_ARR(res, ARRAY_LEN);
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
	return sum;
}

int *mul(int *arr_1, int *arr_2, int len_1, int len_2)
{
	int mem;
	int offset = 0;
	int i, j, l, k = 0;
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
		for(j = lbig - 1; j >= 0; j--) {
			temp = small[i] * big[j] + mem;
			mem = temp / 10;
			stage[k] = temp % 10;
			k--;
			if (j == 0)
				stage[k] = mem;
		}

		mem = 0;
		int z = 0;
		for (z = ARRAY_LEN - 1; z >= 0; z--) {
			if (z <= 0) {
				res[z - offset] = stage[z] + mem;
				mem = 0;
			} else {
				if (res[z - offset] + stage[z] + mem >= 10) {	
					l = (res[z - offset] + stage[z]) / 10 + mem;
					res[z - offset] = (res[z - offset] + stage[z] + mem) % 10 ; 
					mem = l;	
				} else {	
					res[z - offset] = res[z - offset] + stage[z] + mem;
					mem = 0;
				}
			}			
		}
		offset = 1;
	}
	return res;
}
