/* 
 * cc main.c -I .
 * ./a.out 5
 */
#include <stdlib.h>
#include <stdio.h>
#include <array.h>

int main(int argc, char **argv)
{
    int len = 13;
    if (argc > 1) {
        len = atoi(argv[1]);
    }

    ARRAY_CREATE(int, arr);
    for (int i=0; i < len; i++) {
        ARRAY_PUSH(arr, i);
        printf("%d, %d, %lu\n", i, arr[i], ARRAY_CAPACITY(arr));
    }

    ARRAY_SHRINK_TO_FIT(arr);
    for (int i=0; i < ARRAY_SIZE(arr); i++) {
        printf("%d, %d, %lu\n", i, arr[i], ARRAY_CAPACITY(arr));
    }
    ARRAY_DESTROY(arr);
}

