#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "dyn_array/dyn_array.h"

typedef struct {
    int id;
} foo_t;

#define TYPE foo_t

static TYPE create_data(size_t i)
{
    TYPE s;
    s.id = i;
    return s;
}

int main(int argc, char** argv)
{
    srand(time(NULL));

    if(argc != 2)
    {
        fprintf(stderr, "Usage: %s <count>\n", argv[0]);
        return EXIT_FAILURE;
    }

    struct timespec start, end;
    const size_t count = strtol(argv[1], NULL, 0);

    printf("count = %ld\n", count);
    printf("sizeof(TYPE) = %ld\n", sizeof(TYPE));
    printf("total bytes = %ld\n", count * sizeof(TYPE));

    //initialisation des données
    printf("\ninitializing data...\n");
    TYPE *data = malloc(count * sizeof(TYPE));
    for(size_t i = 0; i < count; i++) data[i] = create_data(i);
    printf("data initialized\n");
    
    //------------- insertion avec reservation -------------//
    printf("\ntesting insertion with reservation...\n");
    clock_gettime(CLOCK_MONOTONIC, &start);
    dyn_array_t* arr = dyn_array_create(count, sizeof(TYPE), NULL);
    TYPE *reserved = dyn_array_reserve(arr, count);
    
    for(size_t i = 0; i < count; i++)
        reserved[i] = data[i];

    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_taken = (end.tv_sec - start.tv_sec) * 1e9;
    time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9;

    printf("[%fs] : Insertion with reservation\n", time_taken);
    dyn_array_destroy(arr);


    //------------- push_back - initial capacity -------------//
    printf("\ntesting insertion with push_back...\n");
    clock_gettime(CLOCK_MONOTONIC, &start);
    arr = dyn_array_create(count, sizeof(TYPE), NULL);
    
    for(size_t i = 0; i < count; i++)
    {
        dyn_array_push_back(arr, &data[i]);
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    time_taken = (end.tv_sec - start.tv_sec) * 1e9;
    time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9;
    printf("[%fs] : Insertion with push_back (initial capacity = %ld)\n", time_taken, count);
    dyn_array_destroy(arr);

    //------------- push_back - empty array -------------//
    printf("\ntesting insertion with push_back (empty array)...\n");
    clock_gettime(CLOCK_MONOTONIC, &start);
    arr = dyn_array_create(0, sizeof(TYPE), NULL);

    for(size_t i = 0; i < count; i++)
    {
        dyn_array_push_back(arr, &data[i]);
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    time_taken = (end.tv_sec - start.tv_sec) * 1e9;
    time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9;
    printf("[%fs] : Insertion with push_back (empty array)\n", time_taken);
    dyn_array_destroy(arr);

    printf("\nfinished test with %ld elements\n", count);

    return 0;
}
