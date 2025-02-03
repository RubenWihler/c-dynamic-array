// Description: Main file for the project.
// Author: Wihler Ruben
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "dyn_array/dyn_array.h"

typedef struct _complex_t{
    int id;
    char* dynamic_data;
} complex_t;

static void print_int(void* ptr) { printf("%d", *(int*)ptr); }

static complex_t complex_create(int id);
static void complex_destroy(void* ptr);
static void print_complex(void* ptr);

void primitive_type_exemple(void);
void complex_type_exemple(void);

int main(void)
{
    srand(time(NULL));
    
    primitive_type_exemple();
    complex_type_exemple();

    return 0;
}


void primitive_type_exemple(void)
{
    printf("----------- UTILISATION AVEC UN TYPE PRIMITIF -----------\n");
    dyn_array_t* arr = dyn_array_create(1, sizeof(int), NULL);
    dyn_array_print(arr, print_int);
    
    //push_back
    printf("\najout de 3 éléments\n");
    dyn_array_push_back(arr, &(int){11});
    dyn_array_push_back(arr, &(int){22});
    dyn_array_push_back(arr, &(int){33});
    dyn_array_print(arr, print_int);
    
    //set
    printf("\nmodification de l'élément à l'index 1 -> 99\n");
    dyn_array_set(arr, 1, &(int){99});
    dyn_array_print(arr, print_int);

    //pop_back
    printf("\nsuppression du dernier élément\n");
    dyn_array_pop_back(arr);
    dyn_array_print(arr, print_int);

    //insert
    printf("\ninsertion de 88 à l'index 1\n");
    dyn_array_insert(arr, 1, &(int){88});
    dyn_array_print(arr, print_int);

    //remove
    printf("\nsuppression de l'élément à l'index 0\n");
    dyn_array_remove(arr, 0);
    dyn_array_print(arr, print_int);

    //clear
    printf("\nclear\n");
    dyn_array_clear(arr);
    dyn_array_print(arr, print_int);

    //shrink_to_fit
    printf("\nshrink_to_fit pour libérer la mémoire inutilisée\n");
    dyn_array_shrink_to_fit(arr);
    dyn_array_print(arr, print_int);

    //reserve
    printf("\najout de 100 éléments\n");
    int *reserved = dyn_array_reserve(arr, 100);
    for(size_t i = 0; i < 100; i++) reserved[i] = i;
    dyn_array_print(arr, print_int);
    
    //informations sur le tableau
    printf("\ninformations sur le tableau\n");
    printf("    - nombre d'éléments: %ld\n", dyn_array_count(arr));
    printf("    - capacité: %ld\n", dyn_array_capacity(arr));
    printf("    - taille d'un élément: %ld\n", dyn_array_size(arr));
    printf("    - est vide: %s\n", dyn_array_is_empty(arr) ? "true" : "false");

    //pop_back de 90 éléments
    printf("\nsuppression de 90 éléments\n");
    for(size_t i = 0; i < 90; i++) dyn_array_pop_back(arr);
    dyn_array_print(arr, print_int);

    //resize à 100 éléments
    dyn_array_resize(arr, 100);
    dyn_array_print(arr, print_int);

    //libération de la mémoire
    dyn_array_destroy(arr);
}

void complex_type_exemple(void)
{
    printf("\n----------- UTILISATION AVEC UN TYPE COMPLEXE -----------\n");
    dyn_array_t* arr = dyn_array_create(30, sizeof(complex_t), complex_destroy);
    dyn_array_print(arr, print_complex);
    
    printf("\najout de 30 éléments\n");
    complex_t *reserved = dyn_array_reserve(arr, 30);
    for(size_t i = 0; i < 30; i++) reserved[i] = complex_create(i);
    dyn_array_print(arr, print_complex);

    printf("\nsuppression des éléments avec un id paire\n");
    for(size_t i = 0; i < dyn_array_count(arr); i++)
    {
        complex_t* c = dyn_array_get(arr, i);
        if(c->id % 2 == 0)
        {
            dyn_array_remove(arr, i);
            i--;//on décrémente i car les éléments sont décalés
        }
    }
    dyn_array_print(arr, print_complex);

    printf("\ninsertion d'un nouvel élément à l'index 5\n");
    complex_t c = complex_create(999);
    dyn_array_insert(arr, 5, &c);
    dyn_array_print(arr, print_complex);

    printf("\nsuppression de l'élément à l'index 5\n");
    dyn_array_remove(arr, 5);
    dyn_array_print(arr, print_complex);

    printf("\ndestruction du tableau\n");
    dyn_array_destroy(arr);
}

static complex_t complex_create(int id)
{
    const size_t char_count = 16;

    complex_t c;
    c.id = id;

    c.dynamic_data = malloc((char_count + 1) * sizeof(char));
    if(!c.dynamic_data) { perror("malloc"); exit(EXIT_FAILURE); }

    //random letter between a and z
    for(size_t i = 0; i < char_count; i++)
        c.dynamic_data[i] = 'a' + (rand() % 26);
    c.dynamic_data[char_count] = '\0';

    return c;
}

static void complex_destroy(void* ptr)
{
    complex_t* c = (complex_t*)ptr;
    free(c->dynamic_data);
    printf("destroyed complex_t with id: %d\n", c->id);
}

static void print_complex(void* ptr)
{
    complex_t* c = (complex_t*)ptr;
    printf("{ id: %d, dynamic_data: \"%s\" }", c->id, c->dynamic_data);
}


