#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Buffer.h"


//push_back, pop, insert, delete, resize, free

int main(void)
{
    Buffer buffer;
    initBuffer(&buffer);

    printf("Empty buffer:\n");
    printBuffer(&buffer);

    appendText(&buffer, "Record #1!");
    appendText(&buffer, " My second record");
    printf("Half filled buffer:\n");
    printBuffer(&buffer);
    addLine(&buffer);
    addLine(&buffer);
    addLine(&buffer);
    appendText(&buffer, "The last record today");
    printf("Last buffer:\n");
    printBuffer(&buffer);
}

