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


void get_array(double *in, long n_in, double *out, long n_out)
{
    ARRAY_CREATE(double, a);
    for(int i = 0; i < n_in; ++i) {
        ARRAY_PUSH(a, in[i]);
    }
    for(int i = 0; i < 3; ++i) {
        ARRAY_PUSH(a, (double)i);
    }


    long np = ARRAY_SIZE(a);
    double *pa = a;
    printf("printing from c: %p\n", pa);
    while (np--) {
        printf("(%.1f, %ld)\n", *pa, np);
        pa++;
    }

    out = a;
    n_out = ARRAY_SIZE(a);
    //n_out = ARRAY_CAPACITY(a);
}
