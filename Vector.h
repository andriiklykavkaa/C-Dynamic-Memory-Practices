//
// Created by Andrii Klykavka on 20.05.2025.
//

#ifndef VECTOR_H
#define VECTOR_H

typedef struct Vector {
    int * data;
    int size;
    int capacity;
} Vector;

void initVector(Vector * vec, int capacity);
void freeVector(Vector * vec);

void pushBack(Vector * vec, int el);
void pop(Vector * vec);
void insert(Vector * vec, int index, int el);
void delete(Vector * vec, int index);
void vectorResize(Vector * vec, int newCapacity);

#endif
