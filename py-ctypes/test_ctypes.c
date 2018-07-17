#include <stdio.h>
#include <array.h>


//typedef struct {
//    size_t size;
//    size_t capacity;
//    int *data;
//} Array;


int add_one(int i)
{
    return i+1;
}

typedef struct {
    int x;
    int y;
} Vector2i;

typedef struct {
    double vals[3];
    int i;
} MyStruct;

void print_list()
{
    ARRAY_CREATE(int, arr);
    ARRAY_CREATE(Vector2i, arr2);
    ARRAY_CREATE(MyStruct, arr3);

    // Check resize and push data
    for(int i = 0; i < 15; ++i) {
        ARRAY_PUSH(arr, i*i - i);
        ARRAY_PUSH(arr2, ((Vector2i){i*i, -i}));
        //ARRAY_PUSH(arr3, ((MyStruct){{3.1*i, 4.1, 5.1}, 99*i}));
        ARRAY_PUSH(arr3, ((MyStruct){}));
    }

    for(size_t i = 0; i < ARRAY_SIZE(arr); ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");

    for(size_t i = 0; i < ARRAY_SIZE(arr2); ++i) {
        printf("(%d, %d)", arr2[i].x, arr2[i].y);
    }
    printf("\n\n");

    for(size_t i = 0; i < ARRAY_SIZE(arr3); ++i) {
        printf("(%.1f, %d)", arr3[i].vals[0], arr3[i].i);
    }
    printf("\n\n");
     // Free array
    ARRAY_DESTROY(arr);
    ARRAY_DESTROY(arr2);
    ARRAY_DESTROY(arr3);
}

void show_array(double *a, long n)
{
    while (n--) {
        printf("(%.1f, %ld)\n", *a, n);
        a++;
    }
}


double *get_array(long n)
{
    ARRAY_CREATE(double, a2);
    for(int i = 0; i < n; ++i) {
        ARRAY_PUSH(a2, i);
    }

    long n2 = ARRAY_SIZE(a2);
    double *pa2 = a2;
    while (n2--) {
        printf("(%.1f, %ld)\n", *pa2, n2);
        pa2++;
    }
    return a2;
}
