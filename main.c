#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//push_back, pop, insert, delete, resize, free

// Можна зробити generic версію через

typedef struct Vector {
    int* data;
    int size;
    int capacity;
} Vector;

void initVector(Vector * vec, int capacity) {
    (*vec).data = malloc(capacity * sizeof(int));
    (*vec).size = 0;
    (*vec).capacity = capacity;
}

void freeVector(Vector * vec) {
    free((*vec).data);
    (*vec).data = NULL;
    (*vec).size = 0;
    (*vec).capacity = 0;
    free(vec);
}

void vectorResize(Vector * vec, int newCapacity) {
    int * newData = realloc((*vec).data, newCapacity * sizeof(int));
    if(!newData) {
        perror("Failed to realloc.");
        exit(EXIT_FAILURE);
    }

    (*vec).data = newData;
    (*vec).capacity = newCapacity;
}

void pushBack(Vector * vec, int el) {
    if ((*vec).size == (*vec).capacity) {
        vectorResize(vec, (*vec).capacity * 2);
    }

    (*vec).data[vec->size] = el;
    (*vec).size++;
}

void pop(Vector * vec) {
    if ((*vec).size == 0) return;
    (*vec).size--;
}

void insert(Vector * vec, int index, int el) {
    if (index > (*vec).size) {
        pushBack(vec, el);
        return;
    }

    if ((*vec).size == (*vec).capacity) {
        vectorResize(vec, (*vec).capacity * 2);
    }

    // Split data by index -> move right part 'sizeof(int)' right -> insert 'el' in index
    memmove(&(*vec).data[index+1], &(*vec).data[index], sizeof(int) * ((*vec).size - index));
    (*vec).data[index] = el;
    (*vec).size++;
}

void delete(Vector * vec, int index) {
    if (index < 0 || index >= (*vec).size) {
        perror("Failed to delete at given index.");
        exit(EXIT_FAILURE);
    }

    if (index == (*vec).size - 1) {
        pop(vec);
        return;
    }

    memmove(&(*vec).data[index], &(*vec).data[index+1], sizeof(int) * ((*vec).size - index - 1));
    (*vec).size--;
}

int main(void)
{
    Vector vector;
    initVector(&vector, 12);
    printf("%d\n", vector.capacity);
    printf("%d\n", vector.size);
    printf("=====\n");
    for(int i = 0; i < 13; i++) {
        pushBack(&vector, i);
    }

    printf("%d\n", vector.capacity);
    printf("%d\n", vector.size);
    printf("=====\n");

    int index = 10;
    printf("%d\n", vector.data[index]);
    insert(&vector, index, 55);
    printf("%d\n", vector.data[index]);
    printf("=====\n");

    delete(&vector, index);
    delete(&vector, index);

    printf("%d\n", vector.data[index]);
    printf("=====\n");
    printf("Going out of bounds");
    for(int j = 0; j < 50; j++) {
        printf("%d: %d\n", j, vector.data[j]);
        if (j == 48) {
            printf("");
        }
    }

    freeVector(&vector);
}

