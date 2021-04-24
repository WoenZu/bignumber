/* ARRAY_LEN is estimated length of result array
 * arr_1 and arr_2 is two array which contaun digits for calculate
*/

#include <stdio.h>
#include <string.h>
#include "bnum.h"

char *factorial(int n);

int main()
{
        printf("\nBE AWARE! Constant ARRAY_LEN is %d\n", ARRAY_LEN);
        // char *arg1 = "85375267874025857713";
        // char *arg2 = "4309692530075000254371438";
        // char *arg1 = "853752"; // summ 896848, sub 810656
        // char *arg2 = "43096"; // mul 36.793.296.192

        //res = csub("78", "1");
        //res = cmul("25", "2");
        //res = cadd("78", "1");

        //char *res;
        //int count = 0;
        //int input = 2; // after 33 memory will buggy
        //int tmp = input; 
        //
        //while (tmp != 0) {
        //        tmp /= 10;
        //        ++count;
        //}

        //char *arg = calloc(count + 1, sizeof(arg));
        //sprintf(arg, "%d", input);
        //printf("\n!%s", arg);
        //res = f(arg); // !5 = 120, !15 = 1307674368000


        //printf("\nfactorial !%s", factorial(5));

        char *result;
        result = cmul("2", "9");
        printf("result> %s\n", result);
        
        //free(res);
        //free(arg);
        return 0;
}

//char *f(char *n)
//{
//        //        n == 0 return 1; else return  f(n - 1) * n;
//        return !strcmp(n,"0") ? "1" : cmul( f( csub(n, "1") ), n);
//}

char *factorial(int n)
{
        int result = 1;
        int i;

        for (i = 2; i <= n; i++) {
                // result = result * i;
        }
        printf("\nresult>> %d", result);
        return "1";
}

