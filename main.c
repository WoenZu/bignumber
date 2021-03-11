// ARRAY_LEN is estimated length of result array
// arr_1 and arr_2 is two array which contaun digits for calculate

#include <stdio.h>
#include <stdlib.h>
#define ARRAY_LEN 100
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#define PRINT_ARR(x, y)			\
	do {				\
		int i;			\
		for (i = 0; i < y; i++)	\
		printf("%d ", x[i]);	\
	} while (0)

#define RESULT					\
	do {					\
		printf("\n\nmiddle stage: ");	\
		PRINT_ARR(stage, ARRAY_LEN);	\
		printf("\nmiddle result: ");	\
		PRINT_ARR(res, ARRAY_LEN);	\
		printf("\n");			\
	} while(0)

#define BUG_INFO printf("\nres[%d]: %d + stage[%d]: %d", z - offset, res[z - offset], z, stage[z]);
#define BUG_INF	printf(" = res[%d]: %d, mem: %d offset: %d", z - offset, res[z - offset], mem, offset);

int *add(int *arr_1, int *arr_2, int len_1, int len_2);
int *mul(int *arr_1, int *arr_2, int len_1, int len_2);
int *sub(int *arr_1, int *arr_2, int len_1, int len_2);
int *comb(int *arr, int len);

int main()
{
	printf("\nBE AWARE! Constant ARRAY_LEN is %d\n", ARRAY_LEN);
	int *res;

	// int arr_1[] = {8,5,3,7,5,2,6,7,8,7,4,0,2,5,8,5,7,7,1,3};
	// int arr_2[] = {4,3,0,9,6,9,2,5,3,0,0,7,5,0,0,0,2,5,4,3,7,1,4,3,8};
	
	int arr_1[] = {8,5,3,7,5,2};
	int arr_2[] = {4,3,0,9,6}; // 36.793.296.192

	// int arr_1[] = {1,0,0,9}; // = 586
	// int arr_2[] = {4,2,3}; // Zero test

	int len_1 = ARRAY_SIZE(arr_1);
	int len_2 = ARRAY_SIZE(arr_2);
	res = add(arr_1, arr_2, len_1, len_2);
	//res = mul(arr_1, arr_2, len_1, len_2);
	//res = sub(arr_1, arr_2, len_1, len_2);
	comb(res, 6);
	printf("\n\nArray 1: ");
	PRINT_ARR(arr_1, len_1);
	printf("\nArray 2: ");
	PRINT_ARR(arr_2, len_2);
	printf("\nSum/mul of arrays is: ");
	PRINT_ARR(res, ARRAY_LEN);
	printf("\n ");
	//free(res);
	return 0;
}

int *add(int *arr_1, int *arr_2, int len_1,int len_2)
{
	int mem = 0;
	int i, j;
	int lbig;
	int lsmall;
	int delta;
	int *big;
	int *small;
	int *res = calloc(ARRAY_LEN, sizeof(int));
	
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

	for (i = lbig - 1, j = ARRAY_LEN -1; i >= 0; i--, j--) {
		if (i - delta < 0) {
			res[j] = big[i] + mem;
			mem = 0;
		} else {
			if (big[i] + small[i - delta] + mem >= 10) {
				res[j] = (big[i] + small[i - delta]) - 10 + mem;
				mem = 1;
			} else {
				res[j] = big[i] + small[i - delta] + mem;
				mem = 0;
			}
		}			
	}
	return res;
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
					l = (res[z - offset] + stage[z] + mem) / 10;
					res[z - offset] = (res[z - offset] + stage[z] + mem) % 10 ;
					mem = l;	
				} else {	
					res[z - offset] = res[z - offset] + stage[z] + mem;
					mem = 0;
				}
			}			
		}
		offset++;
	}
	return res;
}

int *sub(int *big, int *small, int lbig, int lsmall)
{
	// big[lbig] - small[lsmall] = res
	// option when big < small not implemented

	int mem = 0;
	int i, j;
	int delta;
	int *res = calloc(ARRAY_LEN, sizeof(int));

	delta = lbig - lsmall;
	
	for (i = lbig - 1, j = ARRAY_LEN - 1; i >= 0; i--, j--) {
		if (lsmall - delta < 0) {
			res[i] = big[i];
			mem = 0;
		} else {
			if(big[i] - mem - small[i - delta] < 0) {
				res[j] = big[i] - mem + 10 - small[i - delta];
				mem = 1;
			} else {
				res[j] = big[i] - mem - small[i - delta];
				mem = 0;
			}
		}
	}

	return res;
}

int *comb(int *arr, int len)
{
	int i, j = 0;
	int *res;
	for(i = 0; arr[i] == 0 || i > ARRAY_LEN - 1; i++);

	res = calloc(ARRAY_LEN - i, sizeof(arr[0]));
	for(i; i < ARRAY_LEN; i++)
		res[j++] = arr[i];
	PRINT_ARR(res, 6);
	return res;
}

