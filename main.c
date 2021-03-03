// ARRAY_LEN is estimated length of result array
// arr_1 and arr_2 is two array which contaun digits for add
#include <stdio.h>
#include <stdlib.h>
#define ARRAY_LEN 3
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

int *add(int *arr_1, int *arr_2, int len_1, int len_2);
void printArr(int *arr, int len);
void reverse(int *destArr, int *sourceArr, int slen);

int main()
{
	int *res;

	// int arr_1[] = {8,5,3,7,5,2,6,7,8,7,4,0,2,5,8,5,7,7,1,3};
	// int arr_2[] = {4,3,0,9,6,9,2,5,3,0,0,7,5,0,0,0,2,5,4,3,7,1,4,3,8};
	int arr_1[] = {8,5,3};
	int arr_2[] = {6,3};

	int len_1 = ARRAY_SIZE(arr_1);
	int len_2 = ARRAY_SIZE(arr_2);
	res = add(arr_1, arr_2, len_1, len_2);

	printf("\nsum: ");
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
	int *res;
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

	// printf("\nbig arr: ");
	// printArr(big, lbig);
	// printf("\nsmall arr: ");
	// printArr(small, lsmall);

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
				// printf("\n<10");
				// printf(" sum[%d]: %d", i, sum[i]);
				// printf(" big[%d]: %d + small[%d]: %d", i, big[i], i, small[i]);
			}
		}			
	}
	
	res = calloc(ARRAY_LEN, sizeof(int));
	reverse(res, sum, ARRAY_LEN);

	free(sum);
	free(big);
	free(small);

	return res;
}

void printArr(int *arr, int l)
{
	int i;
	for (i = 0; i < l; i++)
		printf("%d", arr[i]);
	
}

void reverse(int *destArr, int *sourceArr, int i)
{
	int j = 0;
	while(i > 0)
		destArr[j++] = sourceArr[--i];

}
