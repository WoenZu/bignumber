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
int *comb(int *arr, int *z);
int *fill(char *s);
char *f(char *n);

int main()
{
	printf("\nBE AWARE! Constant ARRAY_LEN is %d\n", ARRAY_LEN);
	char *res;
	// char *arg1 = "85375267874025857713";
	// char *arg2 = "4309692530075000254371438";

	// char *arg1 = "853752"; // summ 896848, sub 810656
	// char *arg2 = "43096"; // mul 36.793.296.192
	printf("csub>> %s", csub("85", "6"));

   	int count = 0;
	int n = 15;
	int t = n;	   
	while (n != 0) {
        	n /= 10;
        	++count;
    	}

	//char *arg = calloc(count, sizeof(char));
	//sprintf(arg, "%d", t);
	//printf("arg: %s", arg);
	//res = f(arg); // !5 = 120, !15 = 1307674368000
	//printf("\n result> %s", res); 
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
		big = fill(arg1);
		lsmall = len2;
		small = calloc(len2, sizeof(int));
		small = fill(arg2);
	
	} else {
		lbig = len2;
		big = calloc(len2, sizeof(int));
		big = fill(arg2);
		lsmall = len1;
		small = calloc(len1, sizeof(int));
		small = fill(arg1);
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

	tmp = comb(tmp, &z);
	res = calloc(z, sizeof(char));
	for (i = 0; i < z; i++) {
		res[i] = tmp[i] + '0';
	}

	return res + '\0';
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

	big = fill(arg1);
	small = fill(arg2);

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

	for (i = 0; i < ARRAY_LEN; i++) {
		if(tmp[i] != 0) {
			tmp = comb(tmp, &z);
			res = calloc(z, sizeof(char));
			for (i = 0; i < z; i++) {
				res[i] = tmp[i] + '0';
			}
		res[z] = '\0';
		return res;
		} 
	}
	return "0";
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
		big = fill(arg1);
		lsmall = len2;
		small = calloc(len2, sizeof(int));
		small = fill(arg2);
	
	} else {
		lbig = len2;
		big = calloc(len2, sizeof(int));
		big = fill(arg2);
		lsmall = len1;
		small = calloc(len1, sizeof(int));
		small = fill(arg1);
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



	tmp = comb(tmp, &z);
	res = calloc(z, sizeof(char));
	for (i = 0; i < z; i++) {
		res[i] = tmp[i] + '0';
	}
	res[z] = '\0';
	return res;
}

int *comb(int *arr, int *z) // make array without zeros
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

int *fill(char *s) // fill array with numbers from string
{	
	int len = strlen(s);
	int i;
	int *arr = calloc(len, sizeof(int));
	for(i = 0; i < len; i++) {
		arr[i] = s[i] - '0';
	}
	return arr;

}

char *f(char *n)
{	
 	return !strcmp(n,"0") ? "1" : cmul( f( csub(n, "1") ), n);
}
