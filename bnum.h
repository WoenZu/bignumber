/*
 *
 *
 *
 *
 */

#ifndef bnum_h
#define bnum_h

#define ARRAY_LEN 1000
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#define SPACE printf("\n");
#define PRINT_ARR(x, y)			\
        do {				\
                int i;			\
                for (i = 0; i < y; i++)	\
                printf("%d ", x[i]);	\
        } while (0)

char *cadd(char *arg1, char *arg2);
char *csub(char *arg1, char *arg2);
char *cmul(char *arg1, char *arg2);
int *zerofree(int *arr, int *z);
int *fill(char *s);

#endif
