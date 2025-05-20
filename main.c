#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Buffer.h"


//push_back, pop, insert, delete, resize, free

int main(void)
{
    Buffer buffer = createBuffer();

    printf("Empty buffer:\n");
    buffer.print(&buffer);

    buffer.append(&buffer, "Record #1!");
    buffer.append(&buffer, "My second recordeee");

    printf("Half filled buffer:\n");
    buffer.print(&buffer);

    buffer.addLine(&buffer);
    buffer.addLine(&buffer);
    buffer.addLine(&buffer);

    buffer.append(&buffer, "The last record today");
    printf("Last buffer:\n");
    buffer.print(&buffer);

    printf("========\n");
    buffer.insert(&buffer, 0, 10, "Anton is busy today");
    buffer.print(&buffer);

    size_t result = buffer.search(&buffer, "today");
    printf("Matches: %lu", result);
}

