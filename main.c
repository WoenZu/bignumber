// ARRAY_LEN is estimated length of result array
// arr_1 and arr_2 is two array which contaun digits for calculate

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_LEN 100
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#define PRINT_ARR(x, y)			\
	do {				\
		int i;			\
		for (i = 0; i < y; i++)	\
		printf("%d ", x[i]);	\
	} while (0)
#define SPACE 	printf("\n");

char *cadd(char *arg1, char *arg2);
char *csub(char *arg1, char *arg2);
char *cmul(char *arg1, char *arg2);
int *comb(int *arr, int len, int *z);
int *fill(char *s, int len);
int f(char *n);

int main()
{
	printf("\nBE AWARE! Constant ARRAY_LEN is %d\n", ARRAY_LEN);
	//int *res;
	char *res;
	// int arr_1[] = {8,5,3,7,5,2,6,7,8,7,4,0,2,5,8,5,7,7,1,3};
	// int arr_2[] = {4,3,0,9,6,9,2,5,3,0,0,7,5,0,0,0,2,5,4,3,7,1,4,3,8};
	
	int arr_1[] = {8,5,3,7,5,2}; //summ 896848, sub 810656
	int arr_2[] = {4,3,0,9,6}; // 36.793.296.192
	
	char *arg1 = "853752";
	char *arg2 = "43096";

	int len_1 = ARRAY_SIZE(arr_1);
	int len_2 = ARRAY_SIZE(arr_2);

	//res = mul(arr_1, arr_2, len_1, len_2);
	//res = cadd(arg1, arg2);
	res = cmul(arg1, arg2);
	//res = csub(arg1, arg2);
	printf("\nResult (main) = %s", res);
	// printf("\n\nArray 1: ");
	// PRINT_ARR(arr_1, len_1);
	// printf("\nArray 2: ");
	// PRINT_ARR(arr_2, len_2);
	// printf("\nSum/mul of arrays is: ");
	// PRINT_ARR(res, ARRAY_LEN);
	// printf("\n ");
	//free(res);
	return 0;
}

char *cadd(char *arg1, char *arg2)
{	
	char *res;
	int lbig, lsmall;
	int *big, *small;
	int i, z = 0;
	int mem = 0;
	int len1 = strlen(arg1), len2= strlen(arg2);
	int *tmp = calloc(ARRAY_LEN, sizeof(int));
	int j = ARRAY_LEN - 1;

	if(len1 > len2) {
		lbig = len1;
		big = calloc(len1, sizeof(int));
		big = fill(arg1, len1);
		lsmall = len2;
		small = calloc(len2, sizeof(int));
		small = fill(arg2, len2);
	
	} else {
		lbig = len2;
		big = calloc(len2, sizeof(int));
		big = fill(arg2, len2);
		lsmall = len1;
		small = calloc(len1, sizeof(int));
		small = fill(arg1, len1);
	}

	i = lbig - 1;
	int delta = lbig - lsmall;


	for (i = lbig - 1; i >= 0; i--) {
		if (i - delta < 0) {
			tmp[j--] = big[i] + mem;
			mem = 0;
		} else {
			if (big[i] + small[i - delta] + mem >= 10) {
				tmp[j--] = (big[i] + small[i - delta]) - 10 + mem;
				mem = 1;
			} else {
				tmp[j--] = big[i] + small[i - delta] + mem;
				mem = 0;
			}
		}			
	}

	tmp = comb(tmp, ARRAY_LEN, &z);
	res = calloc(z, sizeof(char));
	for (i = 0; i < z; i++) {
		res[i] = tmp[i] + '0';
	}

	return res;
}

char *csub(char *arg1, char *arg2)
{
	// big[lbig] - small[lsmall] = res
	// option when big < small not implemented

	char *res;
	int *big, *small;
	int i, z = 0;
	int mem = 0;

	int lbig = strlen(arg1), lsmall= strlen(arg2);
	int *tmp = calloc(ARRAY_LEN, sizeof(int));
	int j = ARRAY_LEN - 1;
	int delta = lbig - lsmall;

	big = fill(arg1, lbig);
	small = fill(arg2, lsmall);

	for (i = lbig - 1; i >= 0; i--) {
		if (i - delta < 0) {
			tmp[j--] = big[i];
			mem = 0;
		} else {
			if(big[i] - mem - small[i - delta] < 0) {
				tmp[j--] = big[i] - mem + 10 - small[i - delta];
				mem = 1;
			} else {
				tmp[j--] = big[i] - mem - small[i - delta];
				mem = 0;
			}
		}
	}

	tmp = comb(tmp, ARRAY_LEN, &z);
	res = calloc(z, sizeof(char));
	for (i = 0; i < z; i++) {
		res[i] = tmp[i] + '0';
	}

	return res;
}

char *cmul(char *arg1, char *arg2)
{
	char *res;
	int lbig, lsmall;
	int *big, *small;
	int i, j, l, z = 0, k = 0;
	int mem;
	int offset = 0;

	int len1 = strlen(arg1), len2= strlen(arg2);
	int *tmp = calloc(ARRAY_LEN, sizeof(int));
	int *stage = calloc(ARRAY_LEN, sizeof(int));

	if(len1 > len2) {
		lbig = len1;
		big = calloc(len1, sizeof(int));
		big = fill(arg1, len1);
		lsmall = len2;
		small = calloc(len2, sizeof(int));
		small = fill(arg2, len2);
	
	} else {
		lbig = len2;
		big = calloc(len2, sizeof(int));
		big = fill(arg2, len2);
		lsmall = len1;
		small = calloc(len1, sizeof(int));
		small = fill(arg1, len1);
	}

	for (i = lsmall - 1; i >= 0; i--) {
		int t;
		mem = 0;
		k = ARRAY_LEN - 1;
		for(j = lbig - 1; j >= 0; j--) {
			t = small[i] * big[j] + mem;
			mem = t / 10;
			stage[k] = t % 10;
			k--;
			if (j == 0)
				stage[k] = mem;
		}

		mem = 0;
		int z = 0;
		for (z = ARRAY_LEN - 1; z >= 0; z--) {
			if (z <= 0) {
				tmp[z - offset] = stage[z] + mem;
				mem = 0;
			} else {
				if (tmp[z - offset] + stage[z] + mem >= 10) {
					l = (tmp[z - offset] + stage[z] + mem) / 10;
					tmp[z - offset] = (tmp[z - offset] + stage[z] + mem) % 10 ;
					mem = l;	
				} else {	
					tmp[z - offset] = tmp[z - offset] + stage[z] + mem;
					mem = 0;
				}
			}			
		}
		offset++;
	}



	tmp = comb(tmp, ARRAY_LEN, &z);
	res = calloc(z, sizeof(char));
	for (i = 0; i < z; i++) {
		res[i] = tmp[i] + '0';
	}

	return res;
}

int *comb(int *arr, int len, int *z) // make array without zeros
{
	// z is the len of res array
	int i, j = 0;
	int *r;
	for(i = 0; arr[i] == 0; i++)
		;
	*z = ARRAY_LEN - i;
	r = calloc(*z, sizeof(arr[0]));
	for(; i < ARRAY_LEN; i++)
		r[j++] = arr[i];
	return r;
}

int *fill(char *s, int len) // fill array with numbers from string
{
	int i;
	int *arr = calloc(len, sizeof(int));
	for(i = 0; i < len; i++) {
		arr[i] = s[i] - '0';
	}
	return arr;

}

// int f(char *n)
// {	// n need to be translated to int here for checking n == 0
// 	printf("\nlen of n%I64d", strlen(n));
//   //return n == 0 ? 1 : f(n-1)*n;
//   return 0; // placeholder
// }
