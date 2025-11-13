/* For simplicity, I will assume that "size" fits into 4 bytes */

#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

extern int bin_s(int *arr, int size, int key);

// Comparison function for qsort
int compare_ints(const void *a, const void *b) {
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;

    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

int main(int argc, char *argv[]) {

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <array_size> <key_to_search>\n", argv[0]);
        fprintf(stderr, "Example: %s 100 42\n", argv[0]);
        return 1; 
    }

    int size = atoi(argv[1]);
    int key = atoi(argv[2]);

    if (size <= 0) {
        fprintf(stderr, "Error: Array size must be a positive integer.\n");
        return 1;
    }

    // Seed the random number generator
    srand(time(NULL));

    int *sorted_array = (int *)malloc(size * sizeof(int));
    
    if (sorted_array == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for the array.\n");
        return 1;
    }

    // Fill the array with random numbers
    for (int i = 0; i < size; i++) {
        sorted_array[i] = rand() % (size * 2);
    }

    qsort(sorted_array, size, sizeof(int), compare_ints);

    printf("Generated sorted array of size %d.\n", size);

    printf("Array: [");
    for (int i = 0; i < size; i++) {
        printf("%d", sorted_array[i]);
        if (i < size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
    
    printf("Key to search for: %d\n", key);
    printf("----------------------\n");

    int idx = bin_s(sorted_array, size, key);

    if (idx != -1) {
        printf("Key %d found at index %d.\n", key, idx);
    } else {
        printf("Key %d not found in the array.\n", key);
    }

    free(sorted_array);

    printf("----------------------\n");

    return 0;
}

